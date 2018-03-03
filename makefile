CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wshadow -Werror=old-style-cast -Werror=return-type -O3

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

scrabble: trie.o
	$(CXX) -o $@ $^

scrabble-nontrie: nontrie.o
	$(CXX) -o $@ $^

trie.o: trie.cpp
nontrie.o: nontrie.cpp