#pragma once

#include "Fonts/MemFont.h"


namespace mfs {

    enum class Type { FONT, BLOCK, CMAP };

    struct Text {
        std::string value;
        bool isConstantLength;
    };

    struct DataSpan {
        uint32_t fileOffset = 0, size = 0;
    };

    class Obj { // interface
    public:
        virtual Type type() const noexcept = 0;
        virtual size_t nChildren() const noexcept = 0;
        virtual const Obj& childAt(size_t i) const = 0;
        virtual Text text() const noexcept = 0;

        virtual std::optional<DataSpan> dataSpan() const noexcept = 0;

        // Need virtual dtor
        virtual ~Obj() = default;

        // Utils
        Buf1d<const char> body(Buf1d<const char> entireFile) const noexcept;
    };

    class Block : public Obj
    {
    public:
        const mf::Block& slave;

        Block(const mf::Block& aSlave) : slave(aSlave) {}

        // Obj
        Type type() const noexcept override { return Type::BLOCK; }
        size_t nChildren() const noexcept override { return 0; }
        const Obj& childAt(size_t i) const override;
        Text text() const noexcept override
            { return { std::string { slave.name.toSv() }, true }; };
        std::optional<DataSpan> dataSpan() const noexcept override
            { return DataSpan { .fileOffset = slave.posInFile, .size = slave.length }; }
    };

    template <class Child>
    class BlockEx : public Block
    {
    public:
        using Block::Block;
        size_t nChildren() const noexcept override { return fChildren.size(); }
        const Obj& childAt(size_t i) const override { return *fChildren.at(i); }
    protected:
        SafeVector<std::shared_ptr<Child>> fChildren;
    };

    class Cmap final : public Obj
    {
    public:
        const mf::Cmap& slave;

        Cmap(const mf::Cmap& aSlave) : slave(aSlave) {}

        // Obj
        Type type() const noexcept override { return Type::CMAP; }
        size_t nChildren() const noexcept override { return 0; }
        const Obj& childAt(size_t i) const override;
        Text text() const noexcept override { return { "Cmap", false }; }
        std::optional<DataSpan> dataSpan() const noexcept override
            { return DataSpan { .fileOffset = slave.posInFile, .size = slave.length }; }
    };

    class CmapBlock : public BlockEx<Cmap>
    {
    private:
        using Super = BlockEx<Cmap>;
    public:
        CmapBlock(const mf::Block& aBlock, Buf1d<const mf::Cmap> aCmaps);
    };

    class Font final : public Obj
    {
    public:
        void clear();
        void loadFrom(const MemFont& font);

        const Block* cmapBlock() const { return cmap.block.get(); }
        unsigned cmapIndex() const { return cmap.index; }

        // Obj
        Type type() const noexcept override { return Type::FONT; }
        size_t nChildren() const noexcept override;
        const Block& childAt(size_t i) const override;
        Text text() const noexcept override { return { "Font", false }; }
        std::optional<DataSpan> dataSpan() const noexcept override
            { return DataSpan { .fileOffset = 0, .size = fileSize }; }
    private:
        const MemFont* slave = nullptr;
        uint32_t fileSize = 0;
        struct Cmap {
            std::shared_ptr<Block> block {};
            unsigned index = 0;
        } cmap;

        SafeVector<std::shared_ptr<Block>> blocks;
    };

}   // namespace mf