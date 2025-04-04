#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class SentenceSplitter
{
public:
    std::vector<std::vector<std::wstring>> split(const std::wstring& str)
    {
        std::vector<std::vector<std::wstring>> result;
        std::wstringstream ss(str);
        std::wstring sentence;

        while (std::getline(ss, sentence, L'.'))
        {
            if (!sentence.empty())
            {
                std::vector<std::wstring> words = splitWords(sentence);
                result.push_back(words);
            }
        }

        return result;
    }

private:
    std::vector<std::wstring> splitWords(const std::wstring& sentence)
    {
        std::vector<std::wstring> words;
        std::wstringstream ss(sentence);
        std::wstring word;

        while (ss >> word)
            words.push_back(word);

        return words;
    }
};