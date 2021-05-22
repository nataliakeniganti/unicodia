#include "UcData.h"

using namespace std::string_view_literals;


const uc::LangLife uc::langLifeInfo[static_cast<int>(EcLangLife::NN)] {
    { {} },
    { u8"живая <i>(основным языкам ничего не угрожает, как кириллица)</i>"sv },
    { u8"в опасности <i>(задавлена соседними языками, как чероки)</i>"sv },
    { u8"мёртвая <i>(скоро потеряет/недавно потеряла носителей, как нюй-шу)</i>"sv },
    { u8"историческая <i>(давно мертва, как глаголица)</i>"sv },
    { u8"новая <i>(как адлам)</i>"sv },
    { u8"возрождённая <i>(как ахом)</i>"sv },
    //{ u8"Ошибка"sv },
};


const uc::WritingDir uc::writingDirInfo[static_cast<int>(EcWritingDir::NN)] {
    { {} },
    { u8"→"sv },
    { u8"←"sv },
    { u8"→ (исторически ← по столбцам)"sv },
    //{ u8"Ошибка"sv },
};


const uc::ScriptType uc::scriptTypeInfo[static_cast<int>(EcScriptType::NN)] {
    { {} },
    { u8"неизвестно"sv },
    { u8"алфавитное <i>(гласные и согласные звуки, как кириллица)</i>"sv },
    { u8"консонантное <i>(согласные звуки, как иврит)</i>"sv },
    { u8"слоговое <i>(как японские катакана/хирагана)</i>"sv },
    { u8"алфавитно-слоговое <i>(как иберийский)</i>"sv },
    { u8"абугида <i>(слоговое, у сходных слогов похожие символы\u00A0— как деванагари. "
        u8"Многие абугиды кодируются как алфавиты: символ составляется из согласного и метки-огласовки.)</i>"sv },
    { u8"иероглифическое <i>(символ означает понятие, как китайский)</i>"sv },
    { u8"слогоиероглифическое <i>(как линейное письмо B)</i>"sv },
    { u8"код <i>(записывает символы другого языка, как код Брайля)</i>"sv },
    { u8"символы <i>(как ноты)</i>"sv },
    { u8"настольная игра <i>(как игральные карты)</i>"sv },
    { u8"эмодзи <i>(японские SMS-картинки)</i>"sv },
    //{ u8"Ошибка"sv },
};


const uc::Version uc::versionInfo[static_cast<int>(uc::EcVersion::NN)] {
    //{ "1.0"sv,  1991 },
    //{ "1.0.1"sv,1992 },
    { "1.1"sv,  1993 },
    { "2.0"sv,  1996 },
    { "2.1"sv,  1998 },
    { "3.0"sv,  1999 },
    { "3.1"sv,  2001 },
    { "3.2"sv,  2002 },
    { "4.0"sv,  2003 },
    { "4.1"sv,  2005 },
    { "5.0"sv,  2006 },
    { "5.1"sv,  2008 },
    { "5.2"sv,  2009 },
    { "6.0"sv,  2010 },
    { "6.1"sv,  2012 },
    { "6.2"sv,  2012 },
    { "6.3"sv,  2013 },
    { "7.0"sv,  2014 },
    { "8.0"sv,  2015 },
    { "9.0"sv,  2016 },
    { "10.0"sv, 2017 },
    { "11.0"sv, 2018 },
    { "12.0"sv, 2019 },
    { "12.1"sv, 2019 },
    { "13.0"sv, 2020 },
    //{ "14.0"sv, 2021 },       //check for equal number
};


const uc::Category uc::categoryInfo[static_cast<int>(uc::EcCategory::NN)] {
    { UpCategory::CONTROL,      "Cc"sv,     u8"Управляющий"sv,
            u8"В первые годы, когда часто требовалось повторить сессию обмена вручную (перфоратором или консолью), "sv
            u8"управляющие символы играли роль форматов данных и сетевых протоколов. "sv
            u8"В настоящее время используются немногие из них:<br>"sv
            u8"• нулевой символ 00;<br>"sv
            u8"• шаг назад (забой) 08;<br>"sv
            u8"• табуляция 09;<br>"sv
            u8"• перевод строки 0A;<br>"sv
            u8"• прогон листа 0C;<br>"sv
            u8"• возврат каретки 0D;<br>"sv
            u8"• конец файла 1A;<br>"sv
            u8"• Escape 1B."sv },
    { UpCategory::FORMAT,       "Cf"sv,     u8"Форматирующий"sv,
            u8"Используются в Юникоде для управления различными его алгоритмами, в первую очередь двунаправленным письмом "sv
            u8"(когда соседствуют текст слева направо и справа налево) и разбиением текста на строки."sv },
    // PRIVATE_USE,     -- unused as Unicodia has nothing to tell
    // SURROGATE,       -- unused as Unicodia has nothing to tell
    { UpCategory::LETTER,       "Ll"sv,     u8"Буква/строчная"sv,
            u8"Письмо «минускул», появившееся в раннее средневековье для экономии дорогого пергамента, "sv
            u8"превратилось в строчные буквы и сделало латиницу очень выразительным алфавитом." },
    { UpCategory::LETTER,       "Lm"sv,     u8"Буква/модифицирующая"sv,
            u8"Такие «недобуквы», приделывающие к букве оттенки смысла, чаще всего встречаются в фонетике. "sv
            u8"Так, модифицирующей буквой является штрих мягкости xʹ, в отличие от похожего математического штриха x′."sv },
    { UpCategory::LETTER,       "Lo"sv,     u8"Буква/другая"sv,
            u8"Символы различных письменностей, где нет деления на заглавные и строчные буквы. "sv
            u8"Например, иврит, арабская вязь и китайские иероглифы. Также особые символы вроде "sv
            u8"мужского/женского порядкового знака романских языков (1º\u00A0— первый, 1ª\u00A0— первая)."sv },
    { UpCategory::LETTER,       "Lt"sv,     u8"Буква/смешанный регистр"sv,
            u8"Символы-диграфы, состоящие из заглавной и строчной букв. "sv
            u8"Так, в хорватской латинице есть диграф ǈ. "sv
            u8"Сербский аналог Љ не является диграфом и потому смешанного регистра не имеет."sv },
    { UpCategory::LETTER,       "Lu"sv,     u8"Буква/заглавная"sv,
            u8"Те письменности, которые приняли маленькие (строчные) буквы, буквы старой формы стали "sv
            u8"называть большими, заглавными или прописными."sv },
    { UpCategory::MARK,         "Mc"sv,     u8"Метка/протяжённая"sv,
            u8"Протяжённые (обладающие шириной) комбинирующие метки встречаются в некоторых "sv
            u8"языках Юго-Восточной Азии: деванагари, бенгальском, каннаде, хангыле…"sv },
    { UpCategory::MARK,         "Me"sv,     u8"Метка/охватывающая"sv,
            u8"Охватывающие метки используются в древнерусских буквенных цифрах (А҈). "sv
            u8"Также существуют охватывающие квадрат, круг и другие фигуры. "sv
            u8"Ни один проверенный типографский движок на Windows 10 20H2 (GDI, Cairo, Skia) не поддерживает подобные символы идеально, "sv
            u8"но на хороших шрифтах вроде DejaVu результат очень неплох." },
    { UpCategory::MARK,         "Mn"sv,     u8"Метка/непротяжённая"sv,
            u8"Непротяжённые метки (например, знак ударе́ния) устроены как символы нулевой ширины, отсюда название. "sv
            u8"В хороших шрифтах дизайнер вручную помещает метки на наиболее распространённые буквы. "sv
            u8"Но если подобной комбинации не предусмотрели (8́), символы накладываются как попало, и результат обычно плох."sv },
    { UpCategory::NUMBER,       "Nd"sv,     u8"Числовой/десятичный"sv,
            u8"Люди считают десятками, поскольку у них десять пальцев. Слова «цифра» и «палец» во многих языках близки. "sv
            u8"Изобретённая в Индии позиционная система счисления используется всем миром, однако "sv
            u8"в языках Ближнего Востока и Юго-Восточной Азии цифры бывают причудливые."sv },
    { UpCategory::NUMBER,       "Nl"sv,     u8"Числовой/буквенный"sv,
            u8"Римские, китайские и другие цифры, основанные на буквах. Древнерусские также основаны на буквах, "sv
            u8"но в Юникоде для этого используются обычные А, Б, Г… с комбинирующими метками."sv },
    { UpCategory::NUMBER,       "No"sv,     u8"Числовой/другой"sv,
            u8"Монолитные дроби, верхние и нижние индексы, цифры в кругах, "sv
            u8"сокращения для больших чисел и другие цифровые символы."sv },
    { UpCategory::PUNCTUATION,  "Pc"sv, u8"Знак препинания/соединитель"sv,
            u8"Небольшая группа символов. Наиболее известный из них\u00A0— знак подчёркивания."sv },
    { UpCategory::PUNCTUATION,  "Pd"sv,     u8"Знак препинания/черта"sv,
            u8"Дефисы и тире. Минус также является чертой, но отнесён к математическим знакам."sv },
    { UpCategory::PUNCTUATION,  "Pe"sv,     u8"Знак препинания/закрывающая скобка"sv,
            u8"Скобки отнечены к отдельной категории, потому что играют важную роль в двунаправленном алгоритме."sv },
    { UpCategory::PUNCTUATION,  "Pf"sv,     u8"Знак препинания/конечный"sv,
            u8"В основном кавычки."sv },
    { UpCategory::PUNCTUATION,  "Pi"sv,     u8"Знак препинания/начальный"sv,
            u8"В основном кавычки."sv },
    { UpCategory::PUNCTUATION,  "Po"sv,     u8"Знак препинания/другой"sv,
            u8"Точка, запятая, процент, маркер списка и многое что ещё."sv },
    { UpCategory::PUNCTUATION,  "Ps"sv,     u8"Знак препинания/открывающая скобка"sv,
            u8"Скобки отнечены к отдельной категории, потому что играют важную роль в двунаправленном алгоритме."sv },
    { UpCategory::SYMBOL,       "Sc"sv,     u8"Символ/валютный"sv,
            u8"Валютный символ\u00A0— важная часть имиджа страны, и даже у монголов есть тугрик ₮, напоминающий могильный крест. "sv
            u8"Артемий Лебедев в конце 1990-х говорил, что рублю не нужен особый знак, "sv
            u8"но впоследствии именно его пиар сделал знак ₽ официальным."sv },
    { UpCategory::SYMBOL,       "Sk"sv,     u8"Символ/модифицирующий"sv,
            u8"Символы вроде крышки ^, внешне совпадающие с комбинирующими метками, но лишённые особых свойств. "sv
            u8"А также некоторые другие символы." },
    { UpCategory::SYMBOL,       "Sm"sv,     u8"Символ/математический"sv,
            u8"Изначально для математики использовались несколько разных систем, наиболее известные из них\u00A0— TᴇX (читается «тех») "sv
            u8"и MathType (он же Microsoft Equation). Юникод даёт надежду, что в компьютерной математике появится какая-то стандартизация\u00A0— "sv
            u8"а также ограниченная возможность писать формулы в системах общего назначения вроде интернет-форумов."sv },
    { UpCategory::SYMBOL,       "So"sv,     u8"Символ/другой"sv,
            u8"Юникод содержит множество разных символов, в том числе коммерческие, технические и эмодзи."sv },
    { UpCategory::SEPARATOR,    "Zl"sv,     u8"Разделитель/строк"sv,
            u8"Единственный символ 2028"sv },
    { UpCategory::SEPARATOR,    "Zp"sv,     u8"Разделитель/абзацев"sv,
            u8"Единственный символ 2029"sv },
    { UpCategory::SEPARATOR,    "Zs"sv,     u8"Разделитель/пробел"sv,
            u8"В хорошо проработанной типографике "sv
            u8"пустого места столько, сколько нужно: 146%\u00A0— мало, 146\u00A0%\u00A0— много, "sv
            u8"146<span style='font-size:3pt'>\u00A0</span>%\u00A0— самое то. Потому и пробелы бывают разные. "sv
            u8"Некоторые из них неразрывные: не расширяются при выключке, не переносятся на другую строку."sv },
    //{ u8"Ошибка"sv },     //check for equal number
};



const uc::Script uc::scriptInfo[static_cast<int>(uc::EcScript::NN)] {
    { "Zyyy"sv, EcScriptType::NONE, EcLangLife::NOMATTER, EcWritingDir::NOMATTER,
            "Нет"sv, {}, {}, "Символы вне письменности."sv },
    { "Adlm"sv, EcScriptType::ALPHABET, EcLangLife::NEW, EcWritingDir::RTL,
        u8"Адлам"sv, u8"Конец 1980-х",
        u8"фулá <i>(семейство языков Западной Африки)</i>"sv,
        u8"<p>Алфавит придуман братьями Ибрагима и Абдулайе Барри, чтобы лучше передавать языки фулá, чем латиница или арабский. "
                u8"Новая письменность прижилась, и её учат в школах Гвинеи, Либерии и других стран, локализован Android.</p>"sv
            u8"<p>Алфавит назван по первым четырём буквам: A, D, L, M. "sv
                u8"Эти буквы означают «Alkule Dandayɗe Leñol Mulugol»\u00A0— «алфавит, защищающий народы от исчезновения».</p>"sv },
    { "Aghb"sv, EcScriptType::ALPHABET, EcLangLife::HISTORICAL, EcWritingDir::LTR,
        u8"Агванский"sv, u8"II век до н.э.",
        u8"агванский <i>(язык Кавказской Албании)</i>"sv,
        u8"<p>Предположительно создана Месропом Маштоцем, создателем армянского алфавита\u00A0— впрочем, непонятно, какова была его роль. "sv
                u8"Упоминалась с конца XIX века. Окончательно открыта в 1937 году советскими арменоведами. "sv
                u8"Первая расшифровка вышла в 2009 году.</p>"sv },
    { "Ahom"sv, EcScriptType::ABUGIDA, EcLangLife::REVIVED, EcWritingDir::LTR,
        u8"Ахом"sv, u8"XIII век",
        u8"тайско-ахомский"sv,
        u8"<p>Тайцы, переселившиеся в долину реки Брахмапутра, создали письменность на основе тогдашней индийской абугиды. "sv
                u8"К XIX веку язык окончательно заместился ассамским. Возрождается с 1954 года.</p>"sv },
    { "Arab"sv, EcScriptType::CONSONANT, EcLangLife::ALIVE, EcWritingDir::RTL,
        u8"Арабский"sv, u8"IV—VI век",
        u8"арабский, персидский, урду, уйгурский, пуштунский…"sv,
        u8"<p>Арабский язык тесно связан с исламом; на этом языке написан Коран (610—632). Арабский халифат насаждал как ислам, так и вязь. "sv
                u8"Многие исламские народы (турки, казахи, башкиры) пользовались арабицей до начала XX века.</p>"
            u8"<p>Компьютерная арабица осложняется написанием арабских букв: у каждой есть обособленная, начальная, средняя и конечная форма. "sv
                u8"В обычном тексте предпочтительнее «общая» форма буквы, подстраивающаяся под положение в слове. "sv
                u8"Но если нужна конечная форма в обособленной букве, в Юникоде есть и «жёсткие» варианты.</p>"sv },
    { "Armi"sv, EcScriptType::CONSONANT, EcLangLife::HISTORICAL, EcWritingDir::RTL,
        u8"Имперский арамейский"sv, u8"VII в. до н.э.",
        u8"имперский арамейский <i>(также канцелярский арамейский\u00A0— язык Персии 500—329 до н.э.)</i>"sv,
        u8"<p>Использовался в Ахеменидской империи как книжный язык. Был кодифицирован настолько, что крайне сложно опознать "sv
                u8"время и место конкретного документа. С завоеванием Персии Александром Македонским началась "sv
                u8"фрагментация языка и дальнейшее формирование сирийских языков (предков арабского) и иудейских (предков иврита).</p>"sv },
    { "Cyrl"sv, EcScriptType::ALPHABET, EcLangLife::ALIVE, EcWritingDir::LTR,
        u8"Кириллица"sv, u8"Конец IX в.",
        u8"русский, украинский, белорусский, русинский, болгарский, македонский, сербохорватский (Сербия), "sv
            u8"казахский, киргизский, таджикский, языки народов России"sv,
        u8"<p>До 900 года византийские монахи Кирилл и Мефодий придумали славянскую письменность; неизвестно, была ли это кириллица. "sv
                u8"Прообразом кириллицы стало византийское письмо унциал для греческого языка, с добавлением звуков, отсутствующих в греческом. "
                u8"Старшинство кириллицы и глаголицы (появившейся тогда же) спорно, большинство учёных считают, что "sv
                u8"глаголицу создал Кирилл, а кириллицу\u00A0— его ученик Климент Охридский, работавший в Болгарии.</p>"sv
            u8"<p>Кириллица распространилась среди южных славян и проникла на Русь с крещением. "sv
                u8"В странах, попавших под влияние Рима, кириллицу прямо запрещали.</p>"sv
            u8"<p>Современная кириллица восходит к гражданскому шрифту, введённому Петром\u00A0I. Шрифт стал компромиссом между сторонниками "sv
                u8"традиций и западниками.</p>"sv
            u8"<p>СССР сделал кириллическую письменность для многих языков союзных республик. С развалом СССР на латиницу перешли "sv
                u8"Азербайджан, Молдавия, Туркмения, Узбекистан.</p>"sv },
    { "Latn"sv, EcScriptType::ALPHABET, EcLangLife::ALIVE, EcWritingDir::LTR,
        u8"Латиница"sv, u8"I тысячелетие до н.э.",
        u8"большинство языков западного и тюркского мира (включая Восточную Европу, Прибалтику, Молдавию), Чёрной Африки, Океании; "sv
            u8"вьетнамский, карельский, курдский, эсперанто"sv,
        u8"<p>Латиница\u00A0— древнегреческое письмо, адаптированное около VII\u00A0в. до нашей эры "sv
                u8"для записи этрусских говоров, впоследствии ставших латинском языком.</p>"sv
            u8"<p>В средние века к латинице добавились буквы J, V и W. Минускульное письмо, изобретённое для экономии дорогого пергамента, "sv
                u8"превратилось в строчные буквы.</p>"sv
            u8"<p>Латинский язык давно мёртв, но широкая территория Римской империи, миссионерская деятельность Папского престола "sv
                u8"и Великие географические открытия, совершённые западным миром, сделали латиницу основным алфавитом мира. "sv
                u8"Латиница используется в математике, медицине, фонетике, программировании.</p>"sv
            u8"<p>С развалом СССР на латиницу перешли Азербайджан, Молдавия, Туркмения, Узбекистан.</p>" },
};



const uc::NumType uc::numTypeInfo[static_cast<int>(uc::EcNumType::NN)] {
    { ""sv },
    { u8"Цифра"sv },
    { u8"Особая цифра"sv },
    { u8"Число"sv },
};


const uc::BidiClass uc::bidiClassInfo[static_cast<int>(EcBidiClass::NN)] {
    { "DIR"sv, EcBidiStrength::EXPLICIT,    u8"Тэг направления"sv,
               u8"Форматирующие символы, корректирующие работу двунаправленного алгоритма Юникода"sv },
    { "AL"sv,  EcBidiStrength::STRONG,      u8"Арабская буква"sv,
               u8"Пишутся справа налево, переворачивают европейские цифры."sv },
    { "AN"sv,  EcBidiStrength::WEAK,        u8"Арабская цифра"sv,
               u8"Пишутся справа налево. Есть тонкие правила, связанные с уровнями вложенности." },

    { "B"sv,   EcBidiStrength::NEUTRAL,     u8"Разделитель абзацев"sv,
               u8"Каждый абзац обрабатывается двунаправленным алгоритмом по отдельности."sv },
    { "BN"sv,  EcBidiStrength::NEUTRAL,     u8"Неграфический"sv,
               u8"Управляющие, соединители и тэги, не имеющие своего написания." },
    { "CS"sv,  EcBidiStrength::WEAK,        u8"Цифровой разделитель"sv,
               u8"Оказавшись в арабском или европейском числе, эти символы становятся его частью." },

    { "EN"sv,  EcBidiStrength::WEAK,        u8"Европейская цифра"sv,
               u8"Европейские цифры в арабском тексте пишутся справа налево."sv },
    { "ES"sv,  EcBidiStrength::WEAK,        u8"Европейский ±"sv,
               u8"Символы + и − внутри европейского числа становятся его частью. Символ ± к этому классу не относится."sv },
    { "ET"sv,  EcBidiStrength::WEAK,        u8"Европейская единица измерения"sv,
               u8"Валютные и прочие символы, встречающиеся рядом с числами. Оказавшись рядом с европейским числом, они становятся частью числа."sv },

    { "L"sv,   EcBidiStrength::STRONG,      u8"Слева направо"sv,
               u8"Латиница, кириллица и прочие алфавиты с написанием слева направо."sv },
    { "NSM"sv, EcBidiStrength::WEAK,        u8"Непротяжённая метка"sv,
               u8"Непротяжённые и охватывающие комбинирующие метки. Направление написания\u00A0— как у основного символа."sv },
    { "ON"sv,  EcBidiStrength::NEUTRAL,     u8"Прочий нейтральный"sv,
               u8"Приспосабливается к направлению окружающего текста."sv },

    { "NM"sv,  EcBidiStrength::NEUTRAL,     u8"Нейтральный отзеркаливающийся"sv,
               u8"Скобки и похожие символы при написании справа налево отзеркаливаются."sv },
    { "R"sv,   EcBidiStrength::STRONG,      u8"Справа налево"sv,
               u8"Иврит, а также исторические письменности Ближнего Востока."sv },
    { "S"sv,   EcBidiStrength::NEUTRAL,     u8"Разделитель участков"sv,
               u8"Tab и некоторые другие символы. Посреди текстового абзаца встречаются редко, но обычно каждый участок обрабатывается двунаправленным алгоритмом по отдельности. Направление табуляции внутри абзаца постоянное."sv },
    { "WS"sv,  EcBidiStrength::NEUTRAL,     u8"Пробел"sv,
               u8"Нейтральны. Есть тонкие правила, касающиеся форматирования пробелами." },
    //{ u8"Ошибка"sv },  check for equal number
};


void uc::completeData()
{
    auto n = nCps();
    for (unsigned i = 0; i < n; ++i) {
        auto& cp = cpInfo[i];
        ++cp.bidiClass().nChars;
        ++cp.category().nChars;
        ++cp.script().nChars;
    }
}
