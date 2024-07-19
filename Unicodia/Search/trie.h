#pragma once

// STL
#include <unordered_map>
#include <memory>

// Libs
#include <u_Vector.h>

// Search
#include "engine.h"

namespace srh {

    template <class T>
    concept IsResult = std::is_default_constructible_v<T>;

    ///
    ///  @tparam  R result
    ///
    template <class R> requires IsResult<R>
    struct TrieNode {
    public:
        constexpr TrieNode() {}

        const R& result() const { return fResult; }
        bool isFinal() const { return fIsFinal; }

        inline TrieNode* add(char32_t c);
        inline void setFinal(R res)
        {
            fIsFinal = true;
            fResult = res;
        }

        inline const TrieNode* unsafeFind(char32_t c) const;
        const TrieNode* find(char32_t c) const;
    protected:
        R fResult {};
        using M = std::unordered_map<char32_t, TrieNode>;
        std::unique_ptr<M> children;
        bool fIsFinal = false;

        TrieNode(M* init) : children(init) {}
    };

    template <class R> requires IsResult<R>
    struct TrieRoot : public TrieNode<R> {
    private:
        using Super = TrieNode<R>;
        using Node = TrieNode<R>;
        using typename Super::M;
        using Super::children;
    public:
        TrieRoot() : Super(new M) {}
        void add(std::u32string_view s, const R& res);
        template <class... Args>
            void addMulti(const R& res, Args&&... args)
            {
                char32_t v[] { std::forward<Args...>(args)... };
                add({ v, std::size(v), res });
            }
        SafeVector<Decoded<R>> decode(std::u32string_view s);
    };


}

template <class R> requires srh::IsResult<R>
inline const srh::TrieNode<R>* srh::TrieNode<R>::unsafeFind(char32_t c) const
{
    if (auto x = children->find(c); x != children->end())
        return &x->second;
    return nullptr;
}

template <class R> requires srh::IsResult<R>
const srh::TrieNode<R>* srh::TrieNode<R>::find(char32_t c) const
{
    if (!children)
        return nullptr;
    return unsafeFind(c);
}

template <class R> requires srh::IsResult<R>
inline srh::TrieNode<R>* srh::TrieNode<R>::add(char32_t c)
{
    if (!children)
        children = std::make_unique<M>();
    return &children->operator[](c);
}

template <class R> requires srh::IsResult<R>
void srh::TrieRoot<R>::add(std::u32string_view s, const R& res)
{
    Node* p = this;
    for (auto c : s) {
        p = p->add(c);
    }
    p->setFinal(res);
}

template <class R> requires srh::IsResult<R>
SafeVector<srh::Decoded<R>> srh::TrieRoot<R>::decode(std::u32string_view s)
{
    static constexpr size_t NO_RESULT = -1;
    struct Last {
        R result {};
        ssize_t iLastPos = NO_RESULT;
    } lastKnown;

    SafeVector<srh::Decoded<R>> r;

    size_t index = 0;

    auto registerResult = [&]() {
        // Why +1? We do not search for single-char emoji, but if…
        //   iLastPos == 0, length == 1 → how to make 0 out of them?
        r.emplace_back(
            lastKnown.iLastPos + 1 - lastKnown.result->value.length(),
            lastKnown.result);
        // I do not want to make true Aho-Corasick here, so back down
        // Need backing down, counter-example: incomplete multi-racial kiss + A
        //  WOMAN RACE1 ZWJ HEART VS16 ZWJ KISS_MARK ZWJ MAN (no race2) A
        // After A we have WOMAN RACE1, but still want to identify HEART VS16
        index = lastKnown.iLastPos;
        lastKnown.iLastPos = NO_RESULT;
    };

    for (; ; ++index) {
        const Node* p = this;
        for (; index < s.length(); ++index) {
            char32_t c = s[index];
            if (auto child = p->find(c)) {
                p = child;
                if (p->isFinal()) {
                    lastKnown.result = p->result();
                    lastKnown.iLastPos = index;
                }
            } else if (p != this) {
                // p==&trieRoot → we already tried and no need 2nd time
                // We are at dead end!
                // Anyway move to root
                p = this;
                // Found smth? (never in root)
                if (lastKnown.iLastPos >= 0) {
                    registerResult();
                // Run through last character again, root’s children are always present
                } else if (auto child = p->unsafeFind(c)) {
                    p = child;
                    // 1st is never decodeable
                }
            }
        }
        // Went out of loop — what have?
        if (lastKnown.iLastPos >= 0) {
            registerResult();
            // Back down even here! (incomplete multi-pacial kiss, but no A afterwards)
        } else {
            break;  // The only exit from loop
        }
    }
    return r;
}
