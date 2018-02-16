#include <vector>
#include "tsl/htrie_map.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>

std::string removeLetters(std::string input, std::string word)
{

}

int main()
{
    tsl::htrie_map<char, int> map;
    std::unordered_map <int, std::vector<std::string>> dict;

    //read file
    std::ifstream txt;
    txt.open("dictionary.txt");
    std::string line;
    int key_buffer;


    //insert
    int i = 1;
    while(txt.eof() != true)
    {   
        std::getline(txt, line);

        std::string sortedWord = line;
        std::sort(sortedWord.begin(), sortedWord.end());
        
        if(map[sortedWord] != 0)
        {   
            dict[map[sortedWord]].push_back(line);
        }
        else
        {
            std::vector<std::string> lst;
            lst.push_back(line);
            map[sortedWord] = i;
            dict[i] = lst;
        }
        i++;
    }

}

