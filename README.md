# What is Unicodia?

It is a simple Unicode encyclopedia and the most comprehensive character map ever. Right now Windows only.

**Lifecycle phase: 5** (production/stable). Minor troubles with sustainability, but generally survived two releases of Unicode. And will survive the third if I survive.

**I’m in Ukraine torn with war, so I’ll release often.** See “war release” tag in Issues.

# How to translate?
* Ask programmer to add localized buttons if needed. One button is international for now, A-Z, and it already has Cyrillic version. The rest are unchangeable for now… until needed.
* Download Lang-src/en.uorig from this repo.
  * If you are able to use Git, better use it. We’ll be able to work together on one translation.
* Put Unicodia to writeable location.
* Create language directory, edit locale.xml for that language.
* Download [UTranslator](https://github.com/Mercury13/utranslator). New → Translation of *.uorig.
  * If you don’t know English, use other \*.utran file as reference translation.
* Press F12 in Unicodia to reload translation without reopening the entire program.
  * Warning, it reloads strings only; all locales are loaded on startup.
* When new original arrived: File → Update data, Go → Find warnings → All.
* nspk template parameters: 1=language name (other script for now, non-localizable), 2=pre-comment (e.g. synonym, localizable).
  * If there’s no {{nspk}} in languages and there’s language data, default {{nspk}} is added automatically. So: {{nspk}} at the end → delete, it’ll be added! Need e.g. synonym → add {{nspk||=Klingon}}. Synonym is the SECOND parameter. See _Script.Mroo_ in English/Russian.

## Language policy
**Common.** No war jargon. Describe 2022 war as neutral as possible. Every _lingua franca_ (English, Russian, French) in its international form. Make examples as patriotic as possible for language we’re writing in: the same letter is Russian and Ukrainian in respective L10n’s. And English if the same phenomenon exists in English language. Apostrophe is U+2019.

**English.** International: truck > lorry, petrol > gas. Prefer British form if both are good. Punctuation around quotes is British/international: it’s inside quotes if it’s a part of “phrase being quoted”.

**Russian.** Ё is mandatory. No grammatical concessions to Ukrainian.

_(May apply to new languages as well.)_ Adjectives like _Georgian_ may agree to _script_ (_письменность_, female in Russian), or to _language_ (_язык_, male). The rules are…
* BLOCKS: strongly connected to language → to language _(грузинский=Georgian [language])_. Otherwise to script _(батакская=Batak [script])_.
* SCRIPTS: of course agree to script _(грузинская=Georgian [script])_.

**Ukrainian.** Avoid 2019 reform, earlier changes (e.g. frequent Ґ in loanwords) are embraced. Describe topics sensitive to nationalists as delicately as possible.

**New languages.**
* As English uses lots of capital letters, translations to other languages may use small where English is capital. Refer to Russian/Ukrainian for letter case.
* See Russian script/language rule.

# How to build?
* Slight C++20 and std::filesystem here → so need either MSYS or recent Qt with MinGW 11.
* Also need cURL (present in W10 18H2+), [7-zip](https://7-zip.org), [UTransCon](https://github.com/Mercury13/utranslator).
* Configure and run tape.bat file.
* Configure and run rel.bat file.

# How to develop?
See [develop.md](develop.md).

# Compatibility and policies

## Platforms
**Win7/10/11 x64 only.** Rationale:
* WXP, WVista and W8 are completely abandoned by all imaginable software. Though I did some improvements specially for W8.
* No obstacles for x86, just untested because no one compiled Qt for x86.
* Recently checked Windows 11, and it works.

## Tofu/misrenderings
* **W10/11 should support everything possible, W7 just runs somehow.** At the time of testing still no BMP tofu, per old policy.
* Previously W7 supported the entire base plane and three important plane 1 scripts. I dropped that guarantee, though I did nothing against it, just did not test
* Small misrenderings in descriptions are tolerable, I’ll fix them only if samples are bad, or if the font has other problems.

## Update Unicode
Wartime: as soon as base arrives, and release date is frozen, even on alpha review stage

Peacetime (probably): stable release + some big font covering a major set arrives. Han too if the coverage is really high

Emergency releases of a few characters (e.g. currency, Japanese era): instantly, even if they are tofu

## Fonts
Fonts are always updated to release versions. Font is updated to alpha/beta if fixes a major misrender, and/or professionally implements a new character.

Naming: Noto if tables and existing glyphs are surely untouched; Uto otherwise.

These fonts are taken to Unicodia without author’s consent:
* Craggy font with missing/trivial tables. Examples: Sunuwar, Garay
* Font without license belonging to author of Unicode request and released by him/her. Examples: Makasar (now replaced), Tangsa
* Author is surely SIL, even if found elsewhere. Example: Toto
* ASCII mapping is NOT a reason. Example: Ol Onal (wrote own)

There’s no special policy for CJK Han ideographs, but mainland Chinese is preferred. All such fonts tend to recreate hypothetical mainland ideographs even if unseen in Chinese bases: SimSun does it for 25 of 100 ideographs from CJK A block. Anyway, Unicodia will never be a good ideograph guide, everything I write about ideographs I suck from other sources.

## Data
Data is as neutral as possible. Examples.
* Number of people speaking Russian. Its current status is Lingua franca, so # of L2 speakers is always shaky, especially under current world war. So just # of L1 speakers
* Number of people speaking Ukrainian. Under this war people tend to conceal native Russian, and Ukrainian’s status is Alive, so # of L1 speakers is ⪢ L2 → so total number
* Disputable territory. Disputable, who currently controls, and maybe who is disputing

## Future functionality
* Finish GlyphWiki loader.
* Better CJK reference.
* Plane map.
