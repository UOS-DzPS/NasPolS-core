#include <inc/analyzer.h>

Result::Result(Type t) : t(t) { }
Analyzer::Analyzer() { }

Result::Type Result::GetType() { return t; }

std::wstring Result::GetStem() { return stem; }
void Result::SetStem(std::wstring* str) { stem = *str; }

void* Result::GetInfo()
{
	if (t == NOUN)
		return &ni;
	else if (t == VERB)
		return &vi;
	return NULL;
}

void Result::SetInfo(void* ptr)
{
	if (t == NOUN)
		ni = *((NounInfo*)ptr);
	else if (t == VERB)
		vi = *((VerbInfo*)ptr);
}

std::vector<Result>* Analyzer::Analyze(const wchar_t* str)
{
	std::vector<Result>* ret = new std::vector<Result>();
	std::vector<NounInfo>* pni;
	std::vector<VerbInfo>* pvi;
	std::wstring stem;

	pvi = va.Search(str, &stem);
	AddVerbToResult(ret, pvi, &stem);
	stem.clear();

	pni = na.Search(str, &stem);
	AddNounToResult(ret, pni, &stem);
	stem.clear();

	return ret;
}

void Analyzer::AddVerbToResult(std::vector<Result>* pres, std::vector<VerbInfo>* pinfo, std::wstring* pstr)
{
	for (auto it = pinfo->begin(); it != pinfo->end(); it++)
	{
		Result r(Result::VERB);

		r.SetStem(pstr);
		r.SetInfo(&(*it));
		pres->push_back(r);
	}
}

void Analyzer::AddNounToResult(std::vector<Result>* pres, std::vector<NounInfo>* pinfo, std::wstring* pstr)
{
	for (auto it = pinfo->begin(); it != pinfo->end(); it++)
	{
		Result r(Result::NOUN);

		r.SetStem(pstr);
		r.SetInfo(&(*it));
		pres->push_back(r);
	}
}