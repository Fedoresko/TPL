#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include "bor.h"

using namespace std;
using namespace textutil;

int BOR::go(int nodn, char sym) {
    Node & node = nodes[nodn];
    auto it = node.child.find(sym);
    if (it != node.child.end()) {
        return it->second;
    }
    if (nodn == 0) {
        return 0;
    }
    return go(getLink(nodn), sym);
}

int BOR::getLink(int nodn) {
    Node & node = nodes[nodn];
    if (node.link == -1) {
        if (nodn == 0 || node.parent == 0) {
            node.link = 0;  
        } else {
            node.link = go(getLink(node.parent), node.par_ch);
        }
    }
    return node.link;
}

void BOR::add(const string &word) {
    int curn = 0;
    words.push_back(word);
    for (const char& ch : word) {
        Node & node = nodes[curn];
        auto it = node.child.find(ch);
        if (it != node.child.end()) {
            curn = it->second;
        } else {
            Node newnode;
            newnode.parent = curn;
            newnode.par_ch = ch;
            curn = nodes.size();
            node.child[ch] = curn;
            nodes.push_back(newnode);
        }
    }
    nodes[curn].ends.push_back(words.size()-1);
}

void BOR::addRes(map<string, list<int>> & res, int nodn, int position) {
    for (int nword : nodes[nodn].ends) {
            string word = words[nword];
            auto it = res.find(word);
            if (it == res.end()) {
                res[word] = list<int>();
            }
            res[word].push_back(position - word.length() + 1);
        }

    int next = getLink(nodn);
    if (next > 0) {
        addRes(res, next, position);
    }
}

map<string, list<int> > BOR::search(const string & text) {
    int pos = 0;
    int state = 0;
    map<string, list<int> > res;
    for (int pos = 0; pos < text.length(); pos++) {
        state = go(state, text[pos]);
        addRes(res, state, pos);
    }
    return res;
}
