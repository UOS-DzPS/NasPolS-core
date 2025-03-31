#pragma once

#include <inc/verb_analyzer.h>
#include <inc/noun_analyzer.h>

class Result
{
public:
	enum Type { NONE, NOUN, VERB };
	const Type type = NONE;

	Result();
};

class NounResult : Result
{
public:
	const Result::Type type = Result::NOUN;

	NounResult();

};

class Analyzer
{
public:
	Analyzer();
	std::vector<Result>* Analyze(const wchar_t*);

private:
	VerbAnalyzer va;
	NounAnalyzer na;
};