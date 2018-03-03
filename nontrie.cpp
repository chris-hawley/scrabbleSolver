#include <vector>
#include "tsl/htrie_map.h"
#include "tsl/htrie_set.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <unistd.h>
#include <sstream>
using std::cout;
using std::endl;
using std::istringstream;
using std::string;
using std::vector;



string removeLetters(string word, string input)
{
    int c, b;
    for(auto i: word)
    {
        c = input.length();
        b=1;
        while( (c>-1) && b )
        {
            if(input[c] == i)
            {
                b = 0;
                input.erase(c,1);
            }
            c--;
        }
    }
    return input;
}


int numCombs = 0;

//used to generate the combinations of letter indexes
void comb(int N, int K, string input, std::unordered_map <string, vector<string>>& dict, vector<string>& out)
{
    string bitmask(K, 1); // K leading 1's
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
        if( !dict[tmp].empty() )
        {
            for(auto i: dict[tmp])
            {
                string tmp2 = i;                
                vector<string> out2;
                int len = i.length();
                for(int c = 1; c<len; c++)
                {
                    comb(len, c, removeLetters(i, input), dict, out2);
                }
                out.push_back(i);
                for(auto str: out2)
                {
                    out.push_back(i+" , "+str);
                }
            }
            
        }
        //std::cout << tmp << std::endl;
        tmp = "";
        
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}

int main()
{
    std::unordered_map <std::string, std::vector<std::string>> dict;

    //read file
    std::ifstream txt;
    txt.open("2of12inf.txt");
    std::string line;


    //insert words into list
    //starting "index" at 1 so the default
    //no value found value for hat_trie can be distinguished
    int i = 1;
    std::string sortedWord;
    std::string tmpLine;
    while(txt.eof() != true)
    {   
        std::getline(txt, line);

        istringstream iss(line);

        tmpLine = "";
        iss >> tmpLine;

        line = tmpLine;

        sortedWord = line;
        std::sort(sortedWord.begin(), sortedWord.end());
        if(!dict[sortedWord].empty())
        {   
            dict[sortedWord].push_back(line);
        }
        else
        {
            std::vector<std::string> lst;
            lst.reserve(5);
            lst.push_back(line);
            dict[sortedWord] = lst;
        }
        i++;
    }

    std::string input = "thequickbrownfox";
    string word = "quick";
    int len = input.length();
    vector<string> out;
    //let's get this boi started
    for(i = 1; i<len; i++)
    {
        comb(len, i, input, dict, out);
    }

    cout << numCombs << endl;

    
    /*
    for(auto str: out)
    {
        cout << str << endl;
    }
    */
    
}