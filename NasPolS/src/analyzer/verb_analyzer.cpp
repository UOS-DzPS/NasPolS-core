#include <inc/verb_analyzer.h>

std::vector<std::tuple<const wchar_t*, VerbInfo>> verb_map = {
	{ L"am", { Polish::FIRST, Polish::SINGULAR, Polish::PRESENT, Polish::UNKNOWN, Polish::I }},
	{ L"ę", { Polish::FIRST, Polish::SINGULAR, Polish::PRESENT, Polish::UNKNOWN, Polish::II }},
	{ L"ałem", { Polish::FIRST, Polish::SINGULAR, Polish::PAST, Polish::MASCULINE, Polish::I }},
	{ L"iłem", { Polish::FIRST, Polish::SINGULAR, Polish::PAST, Polish::MASCULINE, Polish::II }},
	{ L"ałom", { Polish::FIRST, Polish::SINGULAR, Polish::PAST, Polish::NEUTER, Polish::I }},
	{ L"iłom", { Polish::FIRST, Polish::SINGULAR, Polish::PAST, Polish::NEUTER, Polish::II }},
	{ L"ałam", { Polish::FIRST, Polish::SINGULAR, Polish::PAST, Polish::FEMININE, Polish::I }},
	{ L"iłam", { Polish::FIRST, Polish::SINGULAR, Polish::PAST, Polish::FEMININE, Polish::II }},

	{ L"amy", { Polish::FIRST, Polish::PLURAL, Polish::PRESENT, Polish::UNKNOWN, Polish::I }},
	{ L"imy", { Polish::FIRST, Polish::PLURAL, Polish::PRESENT, Polish::UNKNOWN, Polish::II }},
	{ L"aliśmy", { Polish::FIRST, Polish::PLURAL, Polish::PAST, Polish::MASCULINE, Polish::I }},
	{ L"iliśmy", { Polish::FIRST, Polish::PLURAL, Polish::PAST, Polish::MASCULINE, Polish::II }},
	{ L"ałyśmy", { Polish::FIRST, Polish::PLURAL, Polish::PAST, Polish::NEUTER, Polish::I }},
	{ L"iłyśmy", { Polish::FIRST, Polish::PLURAL, Polish::PAST, Polish::NEUTER, Polish::II }},
	{ L"ałyśmy", { Polish::FIRST, Polish::PLURAL, Polish::PAST, Polish::FEMININE, Polish::I }},
	{ L"iłyśmy", { Polish::FIRST, Polish::PLURAL, Polish::PAST, Polish::FEMININE, Polish::II }},

	{ L"asz", { Polish::SECOND, Polish::SINGULAR, Polish::PRESENT, Polish::UNKNOWN, Polish::I }},
	{ L"isz", { Polish::SECOND, Polish::SINGULAR, Polish::PRESENT, Polish::UNKNOWN, Polish::II }},
	{ L"ałeś", { Polish::SECOND, Polish::SINGULAR, Polish::PAST, Polish::MASCULINE, Polish::I }},
	{ L"iłeś", { Polish::SECOND, Polish::SINGULAR, Polish::PAST, Polish::MASCULINE, Polish::II }},
	{ L"ałoś", { Polish::SECOND, Polish::SINGULAR, Polish::PAST, Polish::NEUTER, Polish::I }},
	{ L"iłoś", { Polish::SECOND, Polish::SINGULAR, Polish::PAST, Polish::NEUTER, Polish::II }},
	{ L"ałaś", { Polish::SECOND, Polish::SINGULAR, Polish::PAST, Polish::FEMININE, Polish::I }},
	{ L"iłaś", { Polish::SECOND, Polish::SINGULAR, Polish::PAST, Polish::FEMININE, Polish::II }},

	{ L"acie", { Polish::SECOND, Polish::PLURAL, Polish::PRESENT, Polish::UNKNOWN, Polish::I }},
	{ L"icie", { Polish::SECOND, Polish::PLURAL, Polish::PRESENT, Polish::UNKNOWN, Polish::II }},
	{ L"aliście", { Polish::SECOND, Polish::PLURAL, Polish::PAST, Polish::MASCULINE, Polish::I }},
	{ L"iliście", { Polish::SECOND, Polish::PLURAL, Polish::PAST, Polish::MASCULINE, Polish::II }},
	{ L"ałyście", { Polish::SECOND, Polish::PLURAL, Polish::PAST, Polish::NEUTER, Polish::I }},
	{ L"iłyście", { Polish::SECOND, Polish::PLURAL, Polish::PAST, Polish::NEUTER, Polish::II }},
	{ L"ałyście", { Polish::SECOND, Polish::PLURAL, Polish::PAST, Polish::FEMININE, Polish::I }},
	{ L"iłyście", { Polish::SECOND, Polish::PLURAL, Polish::PAST, Polish::FEMININE, Polish::II }},

	{ L"a", { Polish::THIRD, Polish::SINGULAR, Polish::PRESENT, Polish::UNKNOWN, Polish::I }},
	{ L"i", { Polish::THIRD, Polish::SINGULAR, Polish::PRESENT, Polish::UNKNOWN, Polish::II }},
	{ L"ał", { Polish::THIRD, Polish::SINGULAR, Polish::PAST, Polish::MASCULINE, Polish::I }},
	{ L"ił", { Polish::THIRD, Polish::SINGULAR, Polish::PAST, Polish::MASCULINE, Polish::II }},
	{ L"ało", { Polish::THIRD, Polish::SINGULAR, Polish::PAST, Polish::NEUTER, Polish::I }},
	{ L"iło", { Polish::THIRD, Polish::SINGULAR, Polish::PAST, Polish::NEUTER, Polish::II }},
	{ L"ała", { Polish::THIRD, Polish::SINGULAR, Polish::PAST, Polish::FEMININE, Polish::I }},
	{ L"iła", { Polish::THIRD, Polish::SINGULAR, Polish::PAST, Polish::FEMININE, Polish::II }},

	{ L"ają", { Polish::THIRD, Polish::PLURAL, Polish::PRESENT, Polish::UNKNOWN, Polish::I }},
	{ L"ą", { Polish::THIRD, Polish::PLURAL, Polish::PRESENT, Polish::UNKNOWN, Polish::II }},
	{ L"ali", { Polish::THIRD, Polish::PLURAL, Polish::PAST, Polish::MASCULINE, Polish::I }},
	{ L"ili", { Polish::THIRD, Polish::PLURAL, Polish::PAST, Polish::MASCULINE, Polish::II }},
	{ L"ały", { Polish::THIRD, Polish::PLURAL, Polish::PAST, Polish::NEUTER, Polish::I }},
	{ L"iły", { Polish::THIRD, Polish::PLURAL, Polish::PAST, Polish::NEUTER, Polish::II }},
	{ L"ały", { Polish::THIRD, Polish::PLURAL, Polish::PAST, Polish::FEMININE, Polish::I }},
	{ L"iły", { Polish::THIRD, Polish::PLURAL, Polish::PAST, Polish::FEMININE, Polish::II }},
};

VerbAnalyzer::VerbAnalyzer()
{
	for (auto it = verb_map.begin(); it != verb_map.end(); it++)
		suffix_tree.Add(std::get<0>(*it), std::get<1>(*it));
}

std::vector<VerbInfo>* VerbAnalyzer::Search(const wchar_t* str, std::wstring* stem)
{
	return suffix_tree.Search(str, stem);
}