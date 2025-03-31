#pragma once

#include <string>
#include <vector>

typedef wchar_t Key;

template <typename Data>
class SuffixTrie
{
public:
	SuffixTrie(void) : SuffixTrie(0) { }
	SuffixTrie(Key k) : key(k), childs(), data(NULL) { };
	~SuffixTrie()
	{
		for (auto it = childs.begin(); it != childs.end(); it++)
			delete* it;
	};
	void Add(const wchar_t* str, Data d)
	{
		std::wstring newstr(str);

		Add(&newstr, newstr.rbegin(), d);
	}
	std::vector<Data>* Search(const wchar_t* str, std::wstring* stem)
	{
		std::wstring newstr(str);

		return Search(&newstr, newstr.rbegin(), stem);
	}
	Key GetKey(void) { return key; }

protected:
	Key key;
	std::vector<Data> data;

	void Add(std::wstring* str, std::wstring::reverse_iterator it, Data d)
	{
		SuffixTrie<Data>* childptr;

		if (it == str->rend())
		{
			data.push_back(d);
			return;
		}

		childptr = MakeChild(*it);
		childptr->Add(str, it + 1, d);
	}
	std::vector<Data>* Search(std::wstring* str, std::wstring::reverse_iterator rit, std::wstring* stem)
	{
		if (rit == str->rend())
			return MakeStem(str, rit, stem, new std::vector<Data>(data));
		else if (*rit == 0)
			rit++;

		for (auto it = childs.begin(); it != childs.end(); it++)
			if ((*it)->GetKey() == *rit)
				return (*it)->Search(str, ++rit, stem);
		return MakeStem(str, rit, stem, new std::vector<Data>(data));
	}
	std::vector<Data>* MakeStem(std::wstring* str, std::wstring::reverse_iterator rit, std::wstring* stem, std::vector<Data>* ret)
	{
		for (; rit != str->rend(); rit++)
			stem->insert(0, 1, *rit);
		return ret;
	}
	SuffixTrie<Data>* MakeChild(Key key)
	{
		SuffixTrie<Data>* childptr;

		for (auto it = childs.begin(); it != childs.end(); it++)
			if ((*it)->GetKey() == key)
				return *it;

		childptr = new SuffixTrie<Data>(key);
		childs.push_back(childptr);
		return childptr;
	}

private:
	std::vector<SuffixTrie<Data>*> childs;
};