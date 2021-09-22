#pragma once

// STL
#include <string>

// Qt
#include <QFont>
#include <QFontDatabase>
#include <QPixmap>

// Misc
#include "u_TypedFlags.h"
#include "i_TempFont.h"

// Unicode data
#include "UcAutoDefines.h"

constexpr char32_t NO_TRIGGER = 0xDEADBEEF;

/// ALL NAMES HERE ARE IN UTF-8!

template <class T, size_t N>
const T* findInArray(std::string_view needle, const T (&haystack)[N])
{
    for (auto& v : haystack) {
        if (v.id == needle) {
            return &v;
        }
    }
    return nullptr;
}

class Percent
{
public:
    constexpr explicit Percent() = default;
    constexpr explicit Percent(int x) : fValue(x) {}
    constexpr int value() const { return fValue; }
    constexpr int apply(int x) const { return x * fValue / 100; }
private:
    int fValue = 100;
};

constexpr Percent operator "" _pc (unsigned long long x) { return Percent(x); }

namespace uc {

    constexpr unsigned NO_CHAR = std::numeric_limits<unsigned>::max();
    constexpr QChar STUB_CIRCLE(0x25CC);

    enum class EcLangLife
    {
        NOMATTER,       ///< Symbols (language’s life does not matter)
        ALIVE,          ///< UNESCO safe (Ukrainian)
        ENDANGERED,     ///< UNESCO vulnerable (Belorussian)
                        ///< UNESCO endangered (Walloon)
                        ///< UNESCO highly endangered (Crimean Tatar)
        COMPETING,      ///< Loses competition to another script
        DEAD,           ///< UNESCO elders only (Votic)
                        ///< UNESCO dead (Yugh)
        HISTORICAL,     ///< Dead long ago (Egyptian hieroglyphs)
        SACRED,         ///< Used nowadays as sacred (Coptic, Avestan)
        NEW,            ///< Newly-created (Adlam)
        REVIVED,        ///< Revived (Ahom)
        EXPERIMENTAL,   ///< Experimantal script for existing languages (Deseret)
        //ARTIFICIAL,     ///< Artificial languages (Esperanto); unencoded right now
        //FICTIONAL       ///< Fictional languages (Quenya, Klingon); unencoded right now
        NN
    };

    enum class EcScriptType
    {
        NONE,
        UNKNOWN,
        ALPHABET,       ///< Pure alphabet script (Latin, Cyrillic)
        ARGUABLE,       ///< Alphabet scripts that use syllables as units
        CONSONANT,      ///< Consonant script (Hebrew)
        SYLLABLE,       ///< Syllable script (Hiragana)
        ALPHASYLLABLE,  ///< Partly alphabet, partly syllable (Iberian)
        ABUGIDA,        ///< Syllable script where similar syllables have
                            ///<   similar symbols (Canadian syllable)
        ABUGIDA_BRAHMI, ///< … + based on Brahmi: K=ka, K*=ki, K’=K (Kannada, Thai)
        HIEROGLYPH,     ///< Pictures of things (CJK)
        SYLLABOHIEROGLYPH, ///< Syllable + hieroglyph (Linear A/B)
        CONSONANTHIEROGLYPH, ///< Consonant + hieroglyph (Egyptian)
        OTHER,          ///< Other systems
        //SYMBOL,         ///< Miscellaneous symbols
        //GAME,           ///< Tabletop games
        //EMOJI,          ///< Emoji pictures
        NN,
    };

    enum class UpCategory
    {
        CONTROL,
        FORMAT,
        LETTER,
        MARK,
        NUMBER,
        PUNCTUATION,
        SYMBOL,
        SEPARATOR
    };

    enum class EcIndustry
    {
        NONE,
        APPLIANCES,             ///< power, play, volume…
        ASTROLOGY,
        ASTRONOMY,
        BUSINESS,               ///< @, telephone, fax…
        CHEMISTRY,              ///< incl. alchemy
        COMPUTING,              ///< incl. \, box-drawing
        ELECTRIC,
        MACHINEBUILDING,
        MATHS,
        MATHS_MULTILINE,        ///< multiline formulae and so on
        MEDICINE,               ///< incl. dentistry
        MUSIC,
        NAVIGATION_TRAFFIC,     ///< traffic sings, detours…
        NAVIGATION_PEDESTRIAN,  ///< navigation in airports, tourist maps…
        POETRY,
        RELIGION,
        SPORT,
        NN
    };

    enum class EcWritingDir
    {
        NOMATTER,
        LTR,
        RTL,
        LTR_CJK,
        LTR_CUNEIFORM,
        LTR_BU,
        LTR_COL,
        TD,
        BOTH,
        TANGUT,
        RTL_COL,
        RTL_MOSTLY,
        SOGDIAN,
        NN,
    };

    enum class EcContinent {
        NONE,
        EUROPE,     ///< Europe, incl. Georgia and Mediterranean
        ASIA,       ///< Mainland Asia
        OCEAN,      ///< Indian and Pacific Ocean, incl. Japan
        AFRICA,
        AMERICA,
        CJK,
    };

    enum class EcFont
    {
        NORMAL,
          Z_NOR_1,
          Z_NOR_2,
          Z_NOR_3,
          Z_NOR_4,
          Z_NOR_5,
          Z_NOR_6,
         NOTO,
         TECHNICAL,
          Z_TEC_1,
          Z_TEC_2,
          Z_TEC_3,
          Z_TEC_4,
         NOTO_SYMBOL2,
         NOTO_SYMBOL2_BIGGER,
         SYMBOL,
         HISTORIC,
         HISTORIC_BIGGER,
         BLOCK,
         PUNCTUATION,
           Z_PUN_1,
         MATH,
         MUSIC,
         MUSIC_BIGGER,
         MUSIC_NORMAL,
         GADUGI,
         SEGOE,
         DEJAVU,
         FUNKY,
         FUNKY_BIGGER,
        ADLAM,
        AHOM,
        ARABIC,
        ARABIC_NOTO,
        ARAMAIC,
        ARMENIAN,
         Z_ARM_1,
        AVESTAN,
        BALINESE,
        BAMUM,
        BATAK,
        BENGALI,
        BHAIKSUKI,
        BRAHMI,
        BUGINESE,
        BUHID,
        CANADIAN_ABORIGINAL,
        CAUCASIAN_ALBANIAN,
        CHAKMA,
        CHAM,
        CHEROKEE,
        CJK,
         CJK_FALLBACK,
        CJK_STRUCTURE,
        COPTIC,
        CUNEIFORM,
        DEVANAGARI,
        DOGRA,
        EGYPTIAN,
        ELBASAN,
        ELYMAIC,
        ETHIOPIC,
        GEORGIAN,
        GLAGOLITIC,
        GUJARATI,
        GURMUKHI,
        HANUNOO,
        HATRAN,
        HEBREW,
        HENTAIGANA,
        JAVANESE,
        KAITHI,
        KANNADA,
        KAYAH_LI,
        KHAROSHTHI,
        KHITAN_SMALL,
        KHMER,
        KHOJKI,
        KHUDAWADI,
        LANNA,
        LAO,
        LEPCHA,
        LIMBU,
        LINEAR_A,
        LINEAR_B,
        LISU,
        MAHAJANI,
        MALAYALAM,
        MANDAIC,
        MANICHAEAN,
        MEETEI,
        MEROITIC,
        MONGOLIAN,
        MULTANI,
        MYANMAR,
        NABATAEAN,
        NKO,
        NORTH_ARABIAN,
        NP_HMONG,
        NUSHU,
        OGHAM,
        OLCHIKI,
        OLD_HUNGARIAN,
        OLD_ITALIC,
        OLD_PERMIC,
        OLD_PERSIAN,
        OLD_SOGDIAN,
        ORIYA,
        PALMYRENE,
        PHAGS_PA,
        PHAISTOS_DISC,
        PHOENICIAN,
        PSALTER_PAHLAVI,
        REJANG,
        ROHINGYA,
        RUNIC,
        SAMARITAN,
        SAURASHTRA,
        SHARADA,
        SIGNWRITING,
        SINHALA,
        SOGDIAN,
        SUNDANESE,
        SYLOTI_NAGRI,
        SYRIAC,
        TAGALOG,
        TAGBANWA,
        TAILE,
        TAILUE,
        TAI_VIET,
        TAMIL,
        TAMIL_SUPPLEMENT,
        TANGUT,
        TELUGU,
        THAANA,
        THAI,
        TIBETAN,
        TIFINAGH,
        VAI,
        YEZIDI,
        YI,
        NN
    };

    ///
    ///  @warning  Use several fonts → be sure to have STUB_xxx working for ALL
    ///            Better use STUB_VICEVERSA with temporary font (loaded from file, not system)
    ///
    enum class Ffg {
        BOLD          = 1<<0,   ///< Weight: bold
        SEMIBOLD      = 1<<1,   ///< Weight: semibold
        LIGHT         = 1<<2,   ///< Weight: light
        STUB_OFF      = 1<<3,   ///< Circle stub explicitly off (auto: off for Brahmic, on for the rest)
        STUB_ON       = 1<<4,   ///< Circle stub explicitly on
        STUB_VICEVERSA= 1<<5,   ///< Unglitch for missing circle (ZWSP + char + circle), currently unused
        DESC_STD      = 1<<6,   ///< Use standard font in descriptions, not this
        DESC_BIGGER   = 1<<7,   ///< Use bigger font in descriptions
        DESC_SMALLER  = 1<<8,   ///< Use smaller font in descriptions
        FALL_TO_NEXT  = 1<<9,   ///< Also use the next font if failed to find
        ALTERNATE     = 1<<10,  ///< Marked as “alternate”: works only for chars flagged as “alternate font”
    };

    DEFINE_ENUM_OPS(Ffg)

    struct LoadedFont;

    struct StyleSheet {
        std::string_view v;
        constexpr operator const std::string_view& () const { return v; }

        explicit constexpr StyleSheet() = default;
        explicit constexpr StyleSheet(std::string_view x) : v(x) {}
    };

    struct Font
    {
        static const QString qempty;

        std::string_view family;
        Flags<Ffg> flags {};
        std::string_view styleSheet {};
        Percent sizeAdjust {};

        mutable struct Q {
            std::shared_ptr<LoadedFont> loaded {};
            std::unique_ptr<QFont> table {};
            std::unique_ptr<QFont> big {};
            TempFont tempFont;
            constexpr Q() = default;
            consteval Q(const Q&) {};
        } q {};
        void load(char32_t trigger) const;
        const QFont& get(std::unique_ptr<QFont>& font, int size, char32_t trigger) const;
        bool doesSupportChar(char32_t x) const;
        const QString& onlyFamily(char32_t trigger) const;
        const QString& familiesComma(char32_t trigger) const;

        consteval Font(
                std::string_view aFamily,
                Flags<Ffg> aFlags = {},
                StyleSheet aStylesheet = StyleSheet{},
                Percent aSizeAdjust = Percent())
            : family(aFamily), flags(aFlags), styleSheet(aStylesheet),
              sizeAdjust(aSizeAdjust) {}
        consteval Font(
                std::string_view aFamily,
                Flags<Ffg> aFlags,
                Percent aSizeAdjust)
            : family(aFamily), flags(aFlags), sizeAdjust(aSizeAdjust) {}
        consteval Font(
                std::string_view aFamily,
                Percent aSizeAdjust)
            : family(aFamily), sizeAdjust(aSizeAdjust) {}
        consteval Font(
                std::string_view aFamily,
                StyleSheet aStylesheet,
                Percent aSizeAdjust = Percent())
            : family(aFamily), styleSheet(aStylesheet),
              sizeAdjust(aSizeAdjust) {}
        Font(const Font&) = delete;
    };
    extern const Font fontInfo[];

    struct LangLife
    {
        std::u8string_view locName;
    };
    extern const LangLife langLifeInfo[static_cast<int>(EcLangLife::NN)];


    struct ScriptType
    {
        std::u8string_view locName;
    };
    extern const ScriptType scriptTypeInfo[static_cast<int>(EcScriptType::NN)];


    struct WritingDir
    {
        std::u8string_view locName;
    };
    extern const WritingDir writingDirInfo[static_cast<int>(EcWritingDir::NN)];

    struct Version
    {
        std::string_view name;
        unsigned year;

        //unsigned nNewChars = 0;
    };
    extern const Version versionInfo[static_cast<int>(EcVersion::NN)];

    constexpr int PLANE_BASE = 0;
    constexpr int PLANE_UNKNOWN = -1;

    struct Script
    {
        std::string_view id;
        QFontDatabase::WritingSystem qtCounterpart;
        EcScriptType ecType;
        EcLangLife ecLife;
        EcWritingDir ecDir;
        EcContinent ecContinent;
        std::u8string_view locName, locTime, locLangs, locDescription;
        EcFont ecFont = EcFont::NORMAL;

        mutable unsigned nChars = 0;
        mutable int plane = -1;
        mutable EcVersion ecVersion = EcVersion::UNKNOWN;

        inline const ScriptType& type() const { return scriptTypeInfo[static_cast<int>(ecType)]; }
        inline const LangLife& life() const { return langLifeInfo[static_cast<int>(ecLife)]; }
        inline const WritingDir& dir() const { return writingDirInfo[static_cast<int>(ecDir)]; }
        inline const Font& font() const { return fontInfo[static_cast<int>(ecFont)]; }
        const Version& version() const { return versionInfo[static_cast<int>(ecVersion)]; }
    };
    extern const Script scriptInfo[];
    const Script* findScript(std::string_view x);


//    struct Category
//    {
//        std::string name;
//    };

    struct Cp;

    enum class Bfg {
        COLLAPSIBLE     = 1<<0,     /// [+] collapsible CJK
        HAS_32_NONCHARS = 1<<1,     /// [+] block has 32 non-characters
        FORCE_FONT      = 1<<2,     /// [+] force NORMAL font
        UNGLITCH_MARKS  = 1<<3,     /// [+] every combining will be from NOTO
        EXPERIMENT      = 1<<8,     /// Left for experiments
    };

    DEFINE_ENUM_OPS(Bfg)

    struct Block
    {
        char32_t startingCp, endingCp;
        std::string_view name;
        std::u8string_view locName;

        std::u8string_view locDescription {};
        EcScript ecScript = EcScript::NONE;
        EcFont ecFont = EcFont::NORMAL;
        Flags<Bfg> flags {};

        mutable std::unique_ptr<QPixmap> icon {};
        mutable const Cp* firstAllocated = nullptr;
        mutable int nChars = 0;
        mutable EcVersion ecVersion = EcVersion::NN;
        mutable EcVersion ecLastVersion = EcVersion::FIRST;

        size_t index() const;
        const Version& version() const { return versionInfo[static_cast<int>(ecVersion)]; }
        const Version& lastVersion() const { return versionInfo[static_cast<int>(ecLastVersion)]; }
        const Script& script() const { return scriptInfo[static_cast<int>(ecScript)]; }
        const Font& font() const
        {
            return (ecFont != EcFont::NORMAL)
                ? fontInfo[static_cast<int>(ecFont)]
                : script().font();
        }
        unsigned nNonChars() const;
        unsigned nTotalPlaces() const { return endingCp - startingCp + 1; }
        unsigned nEmptyPlaces() const { return nTotalPlaces() - nChars - nNonChars(); }

        Block& operator = (const Block&) = delete;
        Block& operator = (Block&&) = delete;
    };


    struct Category
    {
        UpCategory upCat;
        std::string_view id;
        std::u8string_view locName;
        std::u8string_view locDescription;
        mutable unsigned nChars = 0;
    };

    extern const Category categoryInfo[static_cast<int>(EcCategory::NN)];
    inline const Category* findCategory(std::string_view x) { return findInArray(x, categoryInfo); }

    struct NumType
    {
        std::u8string_view locName;
    };
    extern const NumType numTypeInfo[static_cast<int>(EcNumType::NN)];

    struct BidiClass
    {
        std::string_view id;
        EcBidiStrength strength;
        std::u8string_view locName;
        std::u8string_view locShortName;
        std::u8string_view locId;
        std::u8string_view locDescription;
        bool isGraphical;
        mutable unsigned nChars = 0;
    };
    extern const BidiClass bidiClassInfo[static_cast<int>(EcBidiClass::NN)];
    inline const BidiClass* findBidiClass(std::string_view x) { return findInArray(x, bidiClassInfo); }

    extern const Block blocks[];
    constexpr int DEFAULT_BLOCK_HINT = N_BLOCKS / 2;

    constexpr int N_CHARS = 65536 * 17;
    extern Cp* cps[N_CHARS];

    // We’ll use this WS for Hani, we could take Japanese as well
    static constexpr auto WS_HANI = QFontDatabase::SimplifiedChinese;

    void completeData();
    const Block* blockOf(char32_t subj, const Block* hint);
    inline const Block* blockOf(char32_t subj, int iHint)
        { return blockOf(subj, blocks + std::max(iHint, 0)); }

    enum class EcTermCat {
        ENCODING, SERIALIZATION, SCRIPT_CLASS, CHAR_CLASS, ALGORITHM,
        PRINCIPLES, WRITING_STYLE, OTHER, NN
    };

    struct TermCat
    {
        std::u8string_view locName;
    };

    extern const TermCat termCats[];

    struct Term
    {
        std::string_view key;
        EcTermCat cat;
        std::u8string_view locName;
        std::u8string_view engName;
        std::u8string_view locDesc;

        const uc::Font& font() const { return fontInfo[0]; }
    };

    extern const Term terms[];
    size_t nTerms();

    const Term* findTerm(std::string_view id);

    constexpr bool isNonChar(char32_t cp)
    {
        // There’re also 32 positions in Arabics; they are unseen right now.
        return ((cp & 0xFFFF) >= 0xFFFE);
    }

    extern const std::u8string_view TX_NOCHAR;

    // Implementation of Numeric inlines
    inline const NumType& Numeric::type() const { return numTypeInfo[static_cast<int>(ecType)]; }

    // Implementations of Cp inlines
    inline const char8_t* Cp::Name::tech() const { return allStrings + iTech.val(); }
    inline const Numeric& Cp::numeric() const { return allNumerics[iNumeric]; }
    inline const Version& Cp::version() const { return versionInfo[static_cast<int>(ecVersion)]; }
    inline const Category& Cp::category() const { return categoryInfo[static_cast<int>(ecCategory)]; }
    inline const BidiClass& Cp::bidiClass() const { return bidiClassInfo[static_cast<int>(ecBidiClass)]; }
    inline const Script& Cp::script() const { return scriptInfo[static_cast<int>(ecScript)]; }
    inline const Script& Cp::scriptEx(const Block*& hint) const
        { return scriptInfo[static_cast<int>(ecScriptEx(hint))]; }
    inline bool Cp::isTrueSpace() const
            { return (ecCategory == EcCategory::SEPARATOR_SPACE &&
                      ecScript != EcScript::Ogam); }    // Ogham space is a continuing line (edge of stick)

    enum class OldComp {
        AMSTRAD     = 1 << 0,
        APPLE       = 1 << 1,
        AQUARIUS    = 1 << 2,
        ATARI_ST    = 1 << 3,
        ATARI_8BIT  = 1 << 4,
        MINITEL     = 1 << 5,
        MSX         = 1 << 6,
        ORIC        = 1 << 7,
        COMMODORE   = 1 << 8,
        RISC_OS     = 1 << 9,
        SINCLAIR    = 1 << 10,
        TELETEXT    = 1 << 11,
        TANDY_TRS80 = 1 << 12,
        TANDY_COCO  = 1 << 13,
        KORVET      = 1 << 14,
        LAST = KORVET
    };
    DEFINE_ENUM_OPS(OldComp)

    extern std::u8string_view oldCompNames[];

    Flags<OldComp> cpOldComps(char32_t cp);

}   // namespace uc

consteval uc::StyleSheet operator "" _sty (const char* data, size_t n)
    { return uc::StyleSheet{std::string_view { data, n }}; }
