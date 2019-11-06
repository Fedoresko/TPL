#ifndef SPR_TEXTUTIL_BOR_H_
#define SPR_TEXTUTIL_BOR_H_

#include <string>
#include <map>
#include <list>

namespace textutil {
    class Node {
        friend class BOR;

        private:
            int link = -1;
            int parent = -1;
            char par_ch;
            std::vector<int> ends;
            std::map<char, int> child;

    };

    class BOR {
        private:
            std::vector<Node> nodes = { Node() }; //Root
            std::vector<std::string> words;
            int go(int nodn, char sym);
            int getLink(int nodn);
            void addRes(std::map<std::string, std::list<int>> & res, int noden, int position);

        public:
            void add(const std::string &word);
            std::map<std::string, std::list<int> > search(const std::string & text);
    };
}

#endif  // SPR_TEXTUTIL_BOR_H_