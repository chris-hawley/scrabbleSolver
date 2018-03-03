#include <vector>
#include "tsl/htrie_map.h"
#include "tsl/htrie_set.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <unistd.h>
#include <sstream>
//#include <proc/readproc.h> 
using std::cout;
using std::endl;
using std::istringstream;

int numCombs = 0;

//TODO look ahead to the letters left after the word
//TODO score the each word and sort on the score

//recursive combination
/*
std::string removeChars(std::string input, std::string word)
{
    
}

std::vector<std::string> recurComb(tsl::htrie_set<char>* set, std::string input, std::string strComb)
{   
    std::string tmp = removeChars(input, strComb);
    std::vector<std::string> words;
    std::string tmpWord;
    int N = tmp.length();
    int K;
    for(K = 1; K<N; K++)
    {
        std::string bitmask(K, 1);
        bitmask.resize(N, 0);
        do {
            for (int i = 0; i < N; ++i) 
            {
                if (bitmask[i]) tmpWord.push_back(tmp[i]);
            }
        }while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    }
    

}
*/


//used to generate the combinations of letter indexes
void comb(int N, int K, tsl::htrie_set<char>* set, std::string input, tsl::htrie_map<char, int> map, std::unordered_map <int, std::vector<std::string>> dict)
{
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's
    std::string tmp;
    // print integers and permute bitmask
    do {
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) tmp.push_back(input[i]);
        }
        numCombs++;
        
        std::sort(tmp.begin(), tmp.end());
        if( map[tmp] != 0 )
        {
            for(auto i: dict[map[tmp]])
            {
                (*set).insert(i);
            }
            
        }
        //std::cout << tmp << std::endl;
        tmp = "";
        
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}

int main()
{
    tsl::htrie_map<char, int> map;
    std::unordered_map <int, std::vector<std::string>> dict;
    tsl::htrie_set<char> set;

    //read file
    std::ifstream txt;
    txt.open("2of12inf.txt");
    std::string line;


    //insert words into list
    //starting "index" at 1 so the default
    //no value found value for hat_trie can be distinguished
    int i = 1;
    std::string sortedWord, tmpLine;

    while(txt.eof() != true)
    {   
        std::getline(txt, line);

        istringstream iss(line);

        tmpLine = "";
        iss >> tmpLine;

        line = tmpLine;

        sortedWord = line;
        std::sort(sortedWord.begin(), sortedWord.end());
        int tmp = map[sortedWord];
        if(tmp != 0)
        {   
            dict[tmp].push_back(line);
        }
        else
        {
            std::vector<std::string> lst;
            lst.reserve(5);
            lst.push_back(line);
            map[sortedWord] = i;
            dict[i] = lst;
        }
        i++;
    }

    std::string input = "thequickbrownfox";
    int len = input.length();
    for(int i = 1; i<len; i++)
    {
        comb(input.length(), i, &set, input, map, dict);
    }

    cout << numCombs << endl;

    
    /*
    std::string key_buffer;
    for(auto it = set.begin(); it != set.end(); ++it) {
        it.key(key_buffer);
        std::cout <<  key_buffer << std::endl;
    }
    */
    
    
}
