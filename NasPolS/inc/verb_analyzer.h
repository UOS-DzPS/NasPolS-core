#pragma once

#include <inc/polish.h>
#include <inc/suffix_trie.h>

class VerbAnalyzer
{
public:
	VerbAnalyzer();
	std::vector<VerbInfo>* Search(const wchar_t*, std::wstring*);

private:
	SuffixTrie<VerbInfo> suffix_tree;
};