#include <string>
#include <vector>
#include <iostream>

#include "bor.h"

using namespace std;
using namespace textutil;

int main() {
    vector<string> msg {"Hello", "C", "World", "from", "VS C", "A", "ADA"};

    BOR bor;
    
    for (const string& word : msg)
    {
        bor.add(word);
        cout << word << " ";
    }
    cout << endl;

    bor.search("Hello, my friend! ADADA good day to Code, from VS C World");
    return 0;
}