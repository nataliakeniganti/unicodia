#pragma once

#include <string>

#include "u_Vector.h"

namespace srh {

    enum class Class { OTHER, LETTER, DIGIT };

    Class classify(char8_t x);

    struct Word {
        std::u8string v;
        Class ccFirst = Class::OTHER, ccLast = Class::OTHER;
        std::u8string_view dicWord;
        bool isDicWord = false;  ///< [+] v == dicWord
        bool alwaysLowPrio = false;

        Word() = default;
        Word(std::u8string x);

        std::u8string_view sv() const { return v; }
        size_t length() const { return v.length(); }
    };

    enum class Place { NONE, PARTIAL, INITIAL_SRIPT, INITIAL, EXACT_SCRIPT, EXACT };

    struct Prio {
        short high = 0;
        unsigned short exact = 0, exactScript = 0,
                       initial = 0, initialScript = 0,
                       partial = 0;
        std::partial_ordering operator <=>(const Prio& x) const = default;
        static const Prio EMPTY;
    };

    ///
    /// \brief The Needle struct
    ///    Compiled “needle” for searching
    ///    Avoid relying on any structs inside
    ///
    struct Needle
    {
        SafeVector<srh::Word> words;

        Needle(std::u8string_view x);
    };

    enum class IsScript : unsigned char { NO, YES };

    Place findWord(std::u8string_view haystack, const Word& needle,
                   IsScript isScript);
    Prio findNeedle(std::u8string_view haystack, const Needle& needle,
                    IsScript isScript);
    bool stringsCiEq(std::u8string_view s1, std::u8string_view s2);

}   // namespace srh
