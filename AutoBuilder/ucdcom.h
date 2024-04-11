#pragma once

#include <string_view>
#include <string>
#include <map>
#include <unordered_map>

///
/// @throw  if bad conversion
///
unsigned fromHex(std::string_view x);


namespace ucd {

    struct Range {
        char32_t first, last;
        auto operator <=> (const Range& x) const { return first <=> x.first; }
        auto operator <=> (char32_t x) const { return first <=> x; }
        bool contains(char32_t x) const { return first <= x && x <= last; }
        static Range from(std::string_view x);
    };

    struct RangeCmp : public std::less<Range> {
        using is_transparent = void;
        using std::less<Range>::operator();
        bool operator () (const Range& x, char32_t y) const { return (x.first < y); }
        bool operator () (char32_t x, const Range& y) const { return (x < y.first); }
    };

    struct Cmp {
        using is_transparent = void;
        inline bool operator() (std::string_view x, std::string_view y) const noexcept
            { return (x < y); }
    };

    struct Hash : public std::hash<std::string_view> {
        using is_transparent = void;
    };

    class PropBase
    {
    public:
        size_t nScripts() const { return scripts.size(); }
        std::string_view shortenScript(std::string_view text) const;

        void addScript(std::string_view longv, std::string_view shortv)
            { scripts.emplace(longv, shortv); }
    private:
        /// Strange, but need std::equal_to!
        using StoS = std::unordered_map<std::string, std::string, Hash, std::equal_to<>>;
        /// key = long, value = short
        StoS scripts;
    };

    PropBase loadPropBase();

    template <class Value>
    class RangeMap
    {
    public:
        template <class... Args>
        void add(const Range& pair, Args&& ... args)
            { m.insert_or_assign( pair, std::forward<Args>(args)...); }

        template <class... Args>
        void add(char32_t first, char32_t last, Args&& ... args)
            { add(Range{first, last}, std::forward<Args>(args)...); }

        const Value* find(char32_t key) const;

        /// Finds key, or returns default value
        /// @warning  Leaves reference
        const Value& findDefRef(char32_t key, const Value& def) const;

        size_t size() const { return m.size(); }
    private:
        std::map<Range, Value, RangeCmp> m;
    };

}   // namespace ucd


template <class Value>
const Value* ucd::RangeMap<Value>::find(char32_t key) const
{
    auto it = m.lower_bound(key + 1);
    if (it == m.begin())
        return nullptr;
    --it;
    if (!it->first.contains(key))
        return nullptr;
    return &it->second;
}


template <class Value>
const Value& ucd::RangeMap<Value>::findDefRef(char32_t key, const Value& def) const
{
    auto q = find(key);
    return q ? *q : def;
}
