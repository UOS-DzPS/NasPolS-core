#include <inc/unit_test.h>

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

void AnalyzerUnitTest(void)
{
	Analyzer a;
	std::wstring str;
	std::vector<Result>* res;

	while (true)
	{
		std::wcout << L">>> ";
		std::wcin >> str;

		res = a.Analyze(str.c_str());

		for (auto it = res->begin(); it != res->end(); it++)
		{
			if (it->GetType() == Result::NOUN)
			{
				NounInfo* ptr = (NounInfo*)it->GetInfo();

				if (ptr)
				{
					std::wcout << "NOUN! ";
					Polish::PrintNounInfo(*ptr);
					std::wcout << L"Potential stem: " << it->GetStem() << L'\n';
				}
			}
			if (it->GetType() == Result::VERB)
			{
				VerbInfo* ptr = (VerbInfo*)it->GetInfo();

				if (ptr)
				{
					std::wcout << "VERB! ";
					Polish::PrintVerbInfo(*ptr);
					std::wcout << L"Potential stem: " << it->GetStem() << L'\n';
				}
			}

			std::wcout << L'\n';
		}
	}
}