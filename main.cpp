#include <vector>
#include "tsl/htrie_map.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <unistd.h>
#include <proc/readproc.h>
 using std::cout;
using std::endl;
std::string removeLetters(std::string input, std::string word)
{

}

int main()
{
    tsl::htrie_map<char, int> map;
    std::unordered_map <int, std::vector<std::string>> dict;

    //read file
    std::ifstream txt;
    txt.open("2of12inf.txt");
    std::string line;
    int key_buffer;


    //insert
    int i = 1;
    while(txt.eof() != true)
    {   
        std::getline(txt, line);

        std::string sortedWord = line;
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

    /*
    double vm, rss;
    process_mem_usage(vm, rss);
    cout << "VM: " << vm << "; RSS: " << rss << endl;
    
    int max = 0;
    for(auto it = map.begin(); it != map.end(); ++it) 
    {
        int a = it.value();
        int tmp = dict[a].size();
        if(tmp > max) { max = tmp;}
    }

    std::cout << "max: " << max << std::endl;
    std::cin >> max;
    process_mem_usage(vm, rss);
    cout << "VM: " << vm << "; RSS: " << rss << endl;
    */
    
}

/*
void process_mem_usage(double& vm_usage, double& resident_set)
{
    vm_usage     = 0.0;
    resident_set = 0.0;

    // the two fields we want
    unsigned long vsize;
    long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
}
*/