#pragma once

#include <inc/polish.h>
#include <inc/suffix_trie.h>

class NounSuffixTrie : public SuffixTrie<NounInfo>
{
public:
	NounSuffixTrie();
	NounSuffixTrie(Key k);
	~NounSuffixTrie();
	void Add(const wchar_t* str, NounInfo d);
	std::vector<NounInfo>* Search(const wchar_t* str, std::wstring* stem);
private:
	std::vector<NounSuffixTrie*> childs;

	void Add(std::wstring* str, std::wstring::reverse_iterator it, NounInfo d);
	std::vector<NounInfo>* Search(std::wstring* str, std::wstring::reverse_iterator rit, std::wstring* stem);
	bool CheckEqual(Key k, std::wstring::reverse_iterator rit);
	std::vector<NounInfo>* MakeStem(std::wstring* str, std::wstring::reverse_iterator rit, std::wstring* stem, std::vector<NounInfo>* ret);
	NounSuffixTrie* MakeChild(Key key);
};

class NounAnalyzer
{
public:
	NounAnalyzer();
	std::vector<NounInfo>* Search(const wchar_t*, std::wstring*);

private:
	NounSuffixTrie suffix_tree;
};