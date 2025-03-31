#include <iostream>
#include <clocale>
#include <cstdlib>

#include <inc/noun_analyzer.h>
#include <inc/polish.h>
#include <inc/verb_analyzer.h>

void VerbUnitTest(void)
{
	VerbAnalyzer va;
	std::vector<VerbInfo>* ptr;
	std::wstring stem;
	wchar_t str[128];

	while (true)
	{
		std::wcout << L">>> ";
		std::wcin >> str;

		ptr = va.Search(str, &stem);

		if (ptr->empty())
			std::wcout << "unknown\n";
		for (auto it = ptr->begin(); it != ptr->end(); it++)
		{
			Polish::PrintVerbInfo(*it);
			if (TH::Ver(*it) == Polish::I)
				std::wcout << L"Potential original form: " << stem << L"ać\n";
			else
			{
				std::wcout << L"Potential original form: " << stem << L"eć\n";
				std::wcout << L"Potential original form: " << stem << L"ić\n";
			}
		}

		delete ptr;
		stem.clear();
	}
}

void NounUnitTest(void)
{
	NounAnalyzer na;
	std::vector<NounInfo>* ptr;
	std::wstring stem;
	wchar_t str[128];

	while (true)
	{
		std::wcout << L">>> ";
		std::wcin >> str;

		ptr = na.Search(str, &stem);

		if (ptr->empty())
			std::wcout << "unknown\n";
		for (auto it = ptr->begin(); it != ptr->end(); it++)
		{
			Polish::PrintNounInfo(*it);
			std::wcout << L"Potential original form: " << stem;
			switch (TH::Gen(*it))
			{
			case Polish::MASCULINE:
				std::wcout << L"\n";
				break;
			case Polish::NEUTER:
				std::wcout << L"o\n";
				break;
			case Polish::FEMININE:
				std::wcout << L"a\n";
				break;
			default:
				break;
			}
		}

		delete ptr;
		stem.clear();
	}
}

int main(void)
{
	// Do not touch this code. This part sets the locale.
	std::setlocale(LC_ALL, "pl_PL.UTF-8");
	system("chcp 65001 > nul");
	// Do not touch this code. This part sets the locale.

	NounUnitTest();
	
	return 0;
}