#pragma once

#include <inc/verb_analyzer.h>
#include <inc/noun_analyzer.h>

class Result
{
public:
	enum Type { NONE, NOUN, VERB };

	Result(Type);

	Type GetType();

	std::wstring GetStem();
	void SetStem(std::wstring*);
	
	void* GetInfo();
	void SetInfo(void*);

private:
	std::wstring stem;
	Type t;
	NounInfo ni;
	VerbInfo vi;
};

class Analyzer
{
public:
	Analyzer();
	std::vector<Result>* Analyze(const wchar_t*);

private:
	VerbAnalyzer va;
	NounAnalyzer na;

	void AddVerbToResult(std::vector<Result>*, std::vector<VerbInfo>*, std::wstring*);
	void AddNounToResult(std::vector<Result>*, std::vector<NounInfo>*, std::wstring*);
};