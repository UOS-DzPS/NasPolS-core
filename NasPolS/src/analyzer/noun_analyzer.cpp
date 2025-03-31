#include <inc/noun_analyzer.h>

std::vector<std::tuple<const wchar_t*, NounInfo>> noun_map = {
	{ L"", { Polish::SINGULAR, Polish::MASCULINE, Polish::NOM, Polish::ALIVE }},
	{ L"a", { Polish::SINGULAR, Polish::MASCULINE, Polish::GEN, Polish::ALIVE }},
	{ L"owi", { Polish::SINGULAR, Polish::MASCULINE, Polish::DAT, Polish::ALIVE }},
	{ L"a", { Polish::SINGULAR, Polish::MASCULINE, Polish::ACC, Polish::ALIVE }},
	{ L"ia", { Polish::SINGULAR, Polish::MASCULINE, Polish::ACC, Polish::ALIVE }},
	{ L"em", { Polish::SINGULAR, Polish::MASCULINE, Polish::INS, Polish::ALIVE }},
	{ L"e", { Polish::SINGULAR, Polish::MASCULINE, Polish::LOC, Polish::ALIVE }},
	{ L"ie", { Polish::SINGULAR, Polish::MASCULINE, Polish::LOC, Polish::ALIVE }},

	{ L"", { Polish::SINGULAR, Polish::MASCULINE, Polish::NOM, Polish::NONALIVE }},
	{ L"a", { Polish::SINGULAR, Polish::MASCULINE, Polish::GEN, Polish::NONALIVE }},
	{ L"owi", { Polish::SINGULAR, Polish::MASCULINE, Polish::DAT, Polish::NONALIVE }},
	{ L"", { Polish::SINGULAR, Polish::MASCULINE, Polish::ACC, Polish::NONALIVE }},
	{ L"em", { Polish::SINGULAR, Polish::MASCULINE, Polish::INS, Polish::NONALIVE }},
	{ L"e", { Polish::SINGULAR, Polish::MASCULINE, Polish::LOC, Polish::NONALIVE }},
	{ L"ie", { Polish::SINGULAR, Polish::MASCULINE, Polish::LOC, Polish::NONALIVE }},

	{ I_OR_Y_STR, { Polish::PLURAL, Polish::MASCULINE, Polish::NOM, Polish::ALIVE }},
	{ L"ów", { Polish::PLURAL, Polish::MASCULINE, Polish::GEN, Polish::ALIVE }},
	{ L"om", { Polish::PLURAL, Polish::MASCULINE, Polish::DAT, Polish::ALIVE }},
	{ L"iom", { Polish::PLURAL, Polish::MASCULINE, Polish::DAT, Polish::ALIVE }},
	{ L"ów", { Polish::PLURAL, Polish::MASCULINE, Polish::ACC, Polish::ALIVE }},
	{ L"ami", { Polish::PLURAL, Polish::MASCULINE, Polish::INS, Polish::ALIVE }},
	{ L"ach", { Polish::PLURAL, Polish::MASCULINE, Polish::LOC, Polish::ALIVE }},

	{ I_OR_Y_STR, { Polish::PLURAL, Polish::MASCULINE, Polish::NOM, Polish::NONALIVE }},
	{ L"ów", { Polish::PLURAL, Polish::MASCULINE, Polish::GEN, Polish::NONALIVE }},
	{ L"om", { Polish::PLURAL, Polish::MASCULINE, Polish::DAT, Polish::NONALIVE }},
	{ L"iom", { Polish::PLURAL, Polish::MASCULINE, Polish::DAT, Polish::NONALIVE }},
	{ I_OR_Y_STR, { Polish::PLURAL, Polish::MASCULINE, Polish::ACC, Polish::NONALIVE }},
	{ L"ami", { Polish::PLURAL, Polish::MASCULINE, Polish::INS, Polish::NONALIVE }},
	{ L"ach", { Polish::PLURAL, Polish::MASCULINE, Polish::LOC, Polish::NONALIVE }},

	{ L"o", { Polish::SINGULAR, Polish::NEUTER, Polish::NOM, Polish::NOCARE }},
	{ L"a", { Polish::SINGULAR, Polish::NEUTER, Polish::GEN, Polish::NOCARE }},
	{ L"u", { Polish::SINGULAR, Polish::NEUTER, Polish::DAT, Polish::NOCARE }},
	{ L"o", { Polish::SINGULAR, Polish::NEUTER, Polish::ACC, Polish::NOCARE }},
	{ L"e", { Polish::SINGULAR, Polish::NEUTER, Polish::ACC, Polish::NOCARE }},
	{ L"em", { Polish::SINGULAR, Polish::NEUTER, Polish::INS, Polish::NOCARE }},
	{ L"e", { Polish::SINGULAR, Polish::NEUTER, Polish::LOC, Polish::NOCARE }},
	{ L"ie", { Polish::SINGULAR, Polish::NEUTER, Polish::LOC, Polish::NOCARE }},

	{ L"o", { Polish::PLURAL, Polish::NEUTER, Polish::NOM, Polish::NOCARE}},
	{ I_OR_Y_STR, { Polish::PLURAL, Polish::NEUTER, Polish::GEN, Polish::NOCARE }},
	{ L"om", { Polish::PLURAL, Polish::NEUTER, Polish::DAT, Polish::NOCARE }},
	{ L"iom", { Polish::PLURAL, Polish::NEUTER, Polish::DAT, Polish::NOCARE }},
	{ L"o", { Polish::PLURAL, Polish::NEUTER, Polish::ACC, Polish::NOCARE}},
	{ L"e", { Polish::PLURAL, Polish::NEUTER, Polish::ACC, Polish::NOCARE}},
	{ L"ami", { Polish::PLURAL, Polish::NEUTER, Polish::INS, Polish::NOCARE }},
	{ L"ach", { Polish::PLURAL, Polish::NEUTER, Polish::LOC, Polish::NOCARE }},

	{ L"a", { Polish::SINGULAR, Polish::FEMININE, Polish::NOM, Polish::NOCARE }},
	{ I_OR_Y_STR, { Polish::SINGULAR, Polish::FEMININE, Polish::GEN, Polish::NOCARE }},
	{ PATAL_I_STR L"e", {Polish::SINGULAR, Polish::FEMININE, Polish::DAT, Polish::NOCARE}},
	{ L"ę", {Polish::SINGULAR, Polish::FEMININE, Polish::ACC, Polish::NOCARE}},
	{ L"ą", { Polish::SINGULAR, Polish::FEMININE, Polish::INS, Polish::NOCARE }},
	{ PATAL_I_STR L"e", { Polish::SINGULAR, Polish::FEMININE, Polish::LOC, Polish::NOCARE }},
	{ L"ie", { Polish::SINGULAR, Polish::FEMININE, Polish::LOC, Polish::NOCARE }},
};

NounAnalyzer::NounAnalyzer()
{
	for (auto it = noun_map.begin(); it != noun_map.end(); it++)
		suffix_tree.Add(std::get<0>(*it), std::get<1>(*it));
}

std::vector<NounInfo>* NounAnalyzer::Search(const wchar_t* str, std::wstring* stem)
{
	return suffix_tree.Search(str, stem);
}

NounSuffixTrie::NounSuffixTrie() : SuffixTrie<NounInfo>()
{

}

NounSuffixTrie::NounSuffixTrie(Key k) : SuffixTrie<NounInfo>()
{
	SuffixTrie::key = k;
}

NounSuffixTrie::~NounSuffixTrie()
{
	for (auto it = childs.begin(); it != childs.end(); it++)
		delete* it;
}

void NounSuffixTrie::Add(const wchar_t* str, NounInfo d)
{
	std::wstring newstr(str);

	Add(&newstr, newstr.rbegin(), d);
}

void NounSuffixTrie::Add(std::wstring* str, std::wstring::reverse_iterator it, NounInfo d)
{
	NounSuffixTrie* childptr;

	if (it == str->rend())
	{
		data.push_back(d);
		return;
	}

	childptr = MakeChild(*it);
	childptr->Add(str, it + 1, d);
}

std::vector<NounInfo>* NounSuffixTrie::Search(const wchar_t* str, std::wstring* stem)
{
	std::wstring newstr(str);

	return Search(&newstr, newstr.rbegin(), stem);
}

std::vector<NounInfo>* NounSuffixTrie::Search(std::wstring* str, std::wstring::reverse_iterator rit, std::wstring* stem)
{
	if (rit == str->rend())
		return MakeStem(str, rit, stem, new std::vector<NounInfo>(data));
	else if (*rit == 0)
		rit++;

	for (auto it = childs.begin(); it != childs.end(); it++)
		if (CheckEqual((*it)->GetKey(), rit))
			return (*it)->Search(str, ++rit, stem);
	return MakeStem(str, rit, stem, new std::vector<NounInfo>(data));
}

bool NounSuffixTrie::CheckEqual(Key k, std::wstring::reverse_iterator rit)
{
	switch (k)
	{
	case PATAL_I_CHR:
		return Polish::IsPatalized(*rit);
		break;
	case I_OR_Y_CHR:
		return *rit == L'i' || *rit == L'y';
		break;
	default:
		return k == *rit;
	}
	return k == *rit;
}

std::vector<NounInfo>* NounSuffixTrie::MakeStem(std::wstring* str, std::wstring::reverse_iterator rit, std::wstring* stem, std::vector<NounInfo>* ret)
{
	return SuffixTrie<NounInfo>::MakeStem(str, rit, stem, ret);
}

NounSuffixTrie* NounSuffixTrie::MakeChild(Key key)
{
	NounSuffixTrie* childptr;

	for (auto it = childs.begin(); it != childs.end(); it++)
		if ((*it)->GetKey() == key)
			return *it;

	childptr = new NounSuffixTrie(key);
	childs.push_back(childptr);
	return childptr;
}