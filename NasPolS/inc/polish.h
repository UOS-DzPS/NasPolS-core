#pragma once

#include <map>
#include <string>
#include <tuple>

#define PATAL_I_STR	L"#"
#define PATAL_I_CHR	L'#'
#define I_OR_Y_STR	L"$"
#define I_OR_Y_CHR	L'$'

class Polish
{
public:
	enum Person { FIRST, SECOND, THIRD };
	enum Count { SINGULAR, PLURAL } ;
	enum Time { PRESENT, PAST };
	enum Gender { MASCULINE, NEUTER, FEMININE, UNKNOWN };
	enum VerbType { I, II };
	enum NounType { NOM, ACC, INS, LOC, GEN, DAT };
	enum Alive { ALIVE, NONALIVE, NOCARE };

	static const wchar_t* lower_alphabet;
	static const wchar_t* upper_alphabet;

	static wchar_t ToUpper(wchar_t);
	static wchar_t ToLower(wchar_t);

	static void PrintVerbInfo(std::tuple<Polish::Person, Polish::Count, Polish::Time, Polish::Gender, Polish::VerbType>);
	static void PrintNounInfo(std::tuple<Polish::Count, Polish::Gender, Polish::NounType, Polish::Alive>);

	static bool IsPatalized(wchar_t);
	static bool IsUnPatalized(wchar_t);

	static bool IsConsonant(wchar_t);
	static bool IsVowel(wchar_t);

	static bool IsLetter(std::wstring::reverse_iterator);
};

typedef std::tuple<Polish::Person, Polish::Count, Polish::Time, Polish::Gender, Polish::VerbType> VerbInfo;
typedef std::tuple<Polish::Count, Polish::Gender, Polish::NounType, Polish::Alive> NounInfo;

// Stands for Tuple Helper
class TH
{
public:
	static Polish::Person Per(VerbInfo);
	static Polish::Count Cou(VerbInfo);
	static Polish::Time Tim(VerbInfo);
	static Polish::Gender Gen(VerbInfo);
	static Polish::VerbType Ver(VerbInfo);

	static Polish::Count Cou(NounInfo);
	static Polish::Gender Gen(NounInfo);
	static Polish::NounType Nou(NounInfo);
	static Polish::Alive Ali(NounInfo);
};