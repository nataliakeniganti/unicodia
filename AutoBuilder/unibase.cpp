#include "unibase.h"

// C++
#include <fstream>

// Unicode bases
#include "ucdcom.h"
#include "loader.h"
#include "data.h"

// Unicode
#include "UcCp.h"

// Misc
#include "u_Strings.h"

using namespace std::string_view_literals;

namespace {

    constinit ucd::NumType NUM_NONE { "NONE" };
    constinit ucd::NumType NUM_DIGIT { "DIGIT" };
    constinit ucd::NumType NUM_SPECIAL_DIGIT { "SPECIAL_DIGIT" };
    constinit ucd::NumType NUM_NUMBER { "NUMBER" };

    constinit ucd::CpInfo::Numeric NO_NUMERIC {
        .type = &NUM_NONE,
        .value{},
    };

    bool hasSubstr(std::string_view haystack, std::string_view needle)
    {
        auto pos = haystack.find(needle);
        return (pos != std::string_view::npos);
    }

    unsigned loadBlocks()
    {
        unsigned r = 0;
        std::ifstream is(UCD_BLOCKS);
        std::string line;
        while (std::getline(is, line)) {
            auto trimmed = str::trimSv(line);
            if (trimmed.empty() || trimmed.starts_with('#'))
                continue;

            auto vals = str::splitSv(trimmed, ';', false);
            if (vals.size() < 2)
                continue;

            auto name = vals.at(1);
            if (hasSubstr(name, "Private Use") || hasSubstr(name, "Surrogate"))
                continue;

            ++r;
        }

        return r;
    }

    std::vector<ucd::HangulLine> loadHangulLines()
    {
        std::vector<ucd::HangulLine> r;

        std::ifstream is(DER_NAME);
        std::string line;
        while (std::getline(is, line)) {
            auto trimmed = str::trimSv(line);
            if (trimmed.empty() || trimmed.starts_with('#'))
                continue;

            auto vals = str::splitSv(trimmed, ';', false);
            if (vals.size() < 2)
                continue;

            unsigned code;
            if (fromHexIf(vals.at(0), code)) {
                if (code >= cp::HANGUL_SYLL_FIRST && code <= cp::HANGUL_SYLL_LAST) {
                    auto name = decapitalize(vals.at(1), code);
                    r.emplace_back(code, name);
                }
            }
        }

        return r;
    }

    std::unordered_map<char32_t, std::string> loadHanNumValues()
    {
        /// @todo [future] Maybe load more CJK types?
        std::unordered_map<char32_t, std::string> r;

        std::string line;
        std::ifstream is(HAN_NUM_VALUE);
        while (std::getline(is, line)) {
            auto trimmed = str::trimSv(line);
            if (trimmed.empty() || trimmed.starts_with('#'))
                continue;

            auto vals = str::splitSv(trimmed, '\t', false);
            if (vals.size() < 3)
                continue;

            auto sCp = vals.at(0);
            if (sCp.starts_with("U+"))
                sCp = sCp.substr(2);

            auto cp = fromHex(sCp);
            auto type = vals.at(1);
            auto value = vals.at(2);

            if (type == "kOtherNumeric"sv || type == "kPrimaryNumeric"
                    || type == "kAccountingNumeric") {
                r[cp] = value;
            }
        }

        return r;
    }

}

ucd::SupportData ucd::loadSupportData()
{
    SupportData r;

    r.nBlocks = loadBlocks();
    r.hangulLines = loadHangulLines();
    r.hanNumValues = loadHanNumValues();

    return r;
}


void ucd::processMainBase(const SupportData& supportData, const BaseSink& sink)
{
    std::ifstream is(UCD_MAIN);
    std::string line;
    CpInfo info;
    char32_t firstCp = 0;
    bool needNumeric = false;
    std::string_view repeatedText = "REPEAT!! #"sv;
    std::string replNameCache;
    while (std::getline(is, line)) {
        auto trimmed = str::trimSv(line);
        if (trimmed.empty())
            continue;

        auto vals = str::splitSv(trimmed, ';', false);
        if (vals.size() < 13)  // Actually 15, but used just 13
            continue;

        auto sCp = vals.at(0);
        info.cp = fromHex(sCp);
        info.generalCat = vals.at(2);
        info.bidiCat = vals.at(4);

        auto decimalDigitValue = vals.at(6);
        auto specialDigitValue = vals.at(7);
        auto numericValue = vals.at(8);

        // Check these numeric values, need smth
        info.numeric.value = numericValue;
        info.numeric.type = numericValue.empty() ? &NUM_NONE : &NUM_NUMBER;
        if (!decimalDigitValue.empty()) {
            if (decimalDigitValue != specialDigitValue || decimalDigitValue != numericValue) {
                throw std::logic_error(
                    str::cat("Cp ", sCp, " has decValue=", decimalDigitValue,
                             ", speValue=", specialDigitValue,
                             ", numValue=", numericValue));
            }
            info.numeric.type = &NUM_DIGIT;
        } else if (!specialDigitValue.empty())  {
            if (specialDigitValue != numericValue) {
                throw std::logic_error(
                    str::cat("Cp ", sCp, " has speValue=", specialDigitValue,
                             " and numValue=", numericValue));
            }
            info.numeric.type = &NUM_SPECIAL_DIGIT;
        }

        info.isMirrored = (vals.at(9) == "Y"sv);
        if (auto sUpper = vals.at(12); !sUpper.empty()) {
            info.upperCase = fromHex(sUpper);
        } else {
            info.upperCase = 0;
        }

        // Name is the last
        info.name = vals.at(1);
        if (info.name.starts_with('<')) { // SPECIAL NAMES
            if (info.name == "<control>"sv) {
                info.name = ""sv;
                sink.act(info);
            } else if (info.name == "<CJK Ideograph Extension A, First>"sv
                    || info.name == "<CJK Ideograph, First>"sv
                    || info.name == "<Hangul Syllable, First>"sv // Let it be for Hangul!
                    || info.name == "<CJK Ideograph Extension B, First>"sv
                    || info.name == "<CJK Ideograph Extension C, First>"sv
                    || info.name == "<CJK Ideograph Extension D, First>"sv
                    || info.name == "<CJK Ideograph Extension E, First>"sv
                    || info.name == "<CJK Ideograph Extension F, First>"sv
                    || info.name == "<CJK Ideograph Extension G, First>"sv
                    || info.name == "<CJK Ideograph Extension H, First>"sv
                    || info.name == "<CJK Ideograph Extension I, First>"sv
                    || info.name == "<CJK Ideograph Extension J, First>"sv) {
                firstCp = info.cp;
                needNumeric = true;
                repeatedText = "CJK unified ideograph-#"sv;  // Let it be for Hangul
            } else if (info.name == "<Tangut Ideograph, First>"sv
                    || info.name == "<Tangut Ideograph Supplement, First>"sv) {
                firstCp = info.cp;
                needNumeric = false;
                repeatedText = "Tangut ideograph-#"sv;
            } else if (info.name == "<CJK Ideograph Extension A, Last>"sv
                    || info.name == "<CJK Ideograph, Last>"sv
                    || info.name == "<Tangut Ideograph, Last>"sv
                    || info.name == "<Tangut Ideograph Supplement, Last>"sv
                    || info.name == "<CJK Ideograph Extension B, Last>"sv
                    || info.name == "<CJK Ideograph Extension C, Last>"sv
                    || info.name == "<CJK Ideograph Extension D, Last>"sv
                    || info.name == "<CJK Ideograph Extension E, Last>"sv
                    || info.name == "<CJK Ideograph Extension F, Last>"sv
                    || info.name == "<CJK Ideograph Extension G, Last>"sv
                    || info.name == "<CJK Ideograph Extension H, Last>"sv
                    || info.name == "<CJK Ideograph Extension I, Last>"sv
                    || info.name == "<CJK Ideograph Extension J, Last>"sv) {
                // CJK and Tangut — use repeated text
                auto lastCp = info.cp;
                info.name = repeatedText;
                for (char32_t i = firstCp; i <= lastCp; ++i) {
                    info.cp = i;
                    info.numeric = NO_NUMERIC;
                    if (needNumeric) {
                        if (auto q = supportData.hanNumValues.find(i);
                                q != supportData.hanNumValues.end()) {
                            info.numeric.type = &NUM_NUMBER;
                            info.numeric.value = q->second;
                        }
                    }
                    sink.act(info);
                }
                firstCp = 0;
            } else if (info.name == "<Hangul Syllable, Last>"sv) {
                for (auto& v : supportData.hangulLines) {
                    info.cp = v.cp;
                    info.name = v.name;
                    sink.act(info);
                }
                firstCp = 0;
            } else if (info.name == "<Non Private Use High Surrogate, First>"sv
                    || info.name == "<Non Private Use High Surrogate, Last>"sv
                    || info.name == "<Private Use High Surrogate, First>"sv
                    || info.name == "<Private Use High Surrogate, Last>"sv
                    || info.name == "<Low Surrogate, First>"sv
                    || info.name == "<Low Surrogate, Last>"sv
                    || info.name == "<Private Use, First>"sv
                    || info.name == "<Private Use, Last>"sv
                    || info.name == "<Plane 15 Private Use, First>"sv
                    || info.name == "<Plane 15 Private Use, Last>"sv
                    || info.name == "<Plane 16 Private Use, First>"sv
                    || info.name == "<Plane 16 Private Use, Last>"sv) {
                // do nothing
            } else {
                throw std::logic_error(
                    str::cat("Unknown special name ", info.name));
            }
        } else {    // NORMAL NAME
            // Decapitalise it here!
            if (firstCp != 0)
                throw std::logic_error("Unfinished special range");
            std::string decapped { info.name };
            str::replace(decapped, sCp, "#"sv);
            decapped = decapitalize(decapped, info.cp);
            info.name = decapped;
            sink.act(info);
        }
    }
}