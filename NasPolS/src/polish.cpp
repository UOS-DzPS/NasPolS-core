#include <cstring>
#include <iostream>
#include <tuple>
#include <vector>

#include <inc/polish.h>
#include <inc/suffix_trie.h>

const wchar_t* Polish::lower_alphabet = L"aąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż";
const wchar_t* Polish::upper_alphabet = L"AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ";

std::vector<std::tuple<std::wstring, std::wstring>> patal_map = {
	{ L"r", L"rz" }, { L"c", L"ć" }, { L"k", L"c" }
};

std::vector<std::wstring> letters = {
	L"rz", L"sz", L"cz", L"gi",
	L"ch", L"dz", L"dź", L"dż"
};

wchar_t Polish::ToUpper(wchar_t ch)
{
	const wchar_t* ptr = wcschr(lower_alphabet, ch);
	long long offset;

	if (!ptr)
		return ch;
	
	offset = (long long)ptr - (long long)lower_alphabet;
	offset >>= 1;
	return upper_alphabet[offset];
}

wchar_t Polish::ToLower(wchar_t ch)
{
	const wchar_t* ptr = wcschr(upper_alphabet, ch);
	long long offset;

	if (!ptr)
		return ch;

	offset = (long long)ptr - (long long)upper_alphabet;
	offset >>= 1;
	return lower_alphabet[offset];
}

void Polish::PrintVerbInfo(std::tuple<Polish::Person, Polish::Count, Polish::Time, Polish::Gender, Polish::VerbType> v)
{
	switch (TH::Per(v))
	{
	case Polish::FIRST:
		std::wcout << L"First ";
		break;
	case Polish::SECOND:
		std::wcout << L"Second ";
		break;
	case Polish::THIRD:
		std::wcout << L"Third ";
		break;
	default:
		std::wcout << L"Unknown ";
		break;
	}
	std::wcout << L"person ";

	switch (TH::Cou(v))
	{
	case Polish::SINGULAR:
		std::wcout << L"singular ";
		break;
	case Polish::PLURAL:
		std::wcout << L"plural ";
		break;
	default:
		std::wcout << L"unknown ";
		break;
	}

	switch (TH::Tim(v))
	{
	case Polish::PRESENT:
		std::wcout << L"present ";
		break;
	case Polish::PAST:
		std::wcout << L"past ";
		break;
	default:
		std::wcout << L"unknown ";
		break;
	}

	switch (TH::Gen(v))
	{
	case Polish::MASCULINE:
		std::wcout << L"masculine ";
		break;
	case Polish::NEUTER:
		std::wcout << L"neuter ";
		break;
	case Polish::FEMININE:
		std::wcout << L"feminine ";
		break;
	default:
		std::wcout << L"unknown ";
		break;
	}

	std::wcout << L"type ";
	switch (TH::Ver(v))
	{
	case Polish::I:
		std::wcout << L"I ";
		break;
	case Polish::II:
		std::wcout << L"II ";
		break;
	default:
		std::wcout << L"unknown ";
		break;
	}

	std::wcout << L"verb.\n";
}

void Polish::PrintNounInfo(std::tuple<Polish::Count, Polish::Gender, Polish::NounType, Polish::Alive> n)
{
	switch (TH::Cou(n))
	{
	case Polish::SINGULAR:
		std::wcout << L"Singular ";
		break;
	case Polish::PLURAL:
		std::wcout << L"Plural ";
		break;
	default:
		std::wcout << L"Unknown ";
		break;
	}

	switch (TH::Ali(n))
	{
	case Polish::ALIVE:
		std::wcout << L"alive ";
		break;
	case Polish::NONALIVE:
		std::wcout << L"non-alive ";
		break;
	default:
		std::wcout << L"unknown ";
		break;
	}

	switch (TH::Gen(n))
	{
	case Polish::MASCULINE:
		std::wcout << L"masculine ";
		break;
	case Polish::NEUTER:
		std::wcout << L"neuter ";
		break;
	case Polish::FEMININE:
		std::wcout << L"feminine ";
		break;
	default:
		std::wcout << L"unknown ";
		break;
	}

	switch (TH::Nou(n))
	{
	case Polish::NOM:
		std::wcout << L"nominative ";
		break;
	case Polish::ACC:
		std::wcout << L"accusative ";
		break;
	case Polish::DAT:
		std::wcout << L"dative ";
		break;
	case Polish::GEN:
		std::wcout << L"genitive ";
		break;
	case Polish::INS:
		std::wcout << L"instrumental ";
		break;
	case Polish::LOC:
		std::wcout << L"locative ";
		break;
	default:
		std::wcout << L"unknown ";
		break;
	}

	std::wcout << L"noun.\n";
}

bool Polish::IsPatalized(wchar_t ch)
{
	const wchar_t* patals = L"cćlńśźż";
	const wchar_t* ptr;

	ptr = wcschr(patals, ToLower(ch));

	if (!ptr)
		return false;
	return true;
}

bool Polish::IsUnPatalized(wchar_t ch)
{
	return !IsPatalized(ch);
}

bool Polish::IsConsonant(wchar_t ch)
{
	const wchar_t* consonants = L"bcćdfghjklłmnńpqrsśtvwxzźż";
	const wchar_t* ptr;

	ptr = wcschr(consonants, ToLower(ch));

	if (!ptr)
		return false;
	return true;
}

bool Polish::IsVowel(wchar_t ch)
{
	return !IsConsonant(ch);
}

bool Polish::IsLetter(std::wstring::reverse_iterator rit)
{
	SuffixTrie<bool> suftree;
	std::vector<bool>* ptr;
	std::wstring temp;
	wchar_t digraphs[3] = { rit[1], rit[0], 0 };
	bool test = false;

	for (auto it = letters.begin(); it != letters.end(); it++)
		suftree.Add(it->c_str(), true);

	ptr = suftree.Search(digraphs, &temp);
	for (auto it = ptr->begin(); it != ptr->end(); it++)
		if (*it)
			test = true;
	delete ptr;
	return test;
}

Polish::Person TH::Per(VerbInfo vi) { return std::get<0>(vi); }
Polish::Count TH::Cou(VerbInfo vi) { return std::get<1>(vi); }
Polish::Time TH::Tim(VerbInfo vi) { return std::get<2>(vi); }
Polish::Gender TH::Gen(VerbInfo vi) { return std::get<3>(vi); }
Polish::VerbType TH::Ver(VerbInfo vi) { return std::get<4>(vi); }

Polish::Count TH::Cou(NounInfo ni) { return std::get<0>(ni); }
Polish::Gender TH::Gen(NounInfo ni) { return std::get<1>(ni); }
Polish::NounType TH::Nou(NounInfo ni) { return std::get<2>(ni); }
Polish::Alive TH::Ali(NounInfo ni) { return std::get<3>(ni); }