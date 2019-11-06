#include "gtest/gtest.h"
#include "../src/bor.h"

using namespace textutil;
using namespace std;

TEST(BorTest, BorTestSimple) {
    BOR bor;
    bor.add("A");
    map<string, list<int> > result = bor.search("A");
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.find("A")->second.size(),1);
    EXPECT_EQ(*(result.find("A")->second.begin()), 0);
}

TEST(BorTest, BorTestTwoWord) {
    BOR bor;
    bor.add("A");
    bor.add("B");
    map<string, list<int> > result = bor.search("ABA AB");
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.find("A")->second, list<int>({0, 2, 4}));
    EXPECT_EQ(result.find("B")->second, list<int>({1, 5}));
}

TEST(BorTest, BorTestComplexWord) {
    BOR bor;
    bor.add("ABACABA");
    map<string, list<int> > result = bor.search("ABACABACABABACABAABACABA");
    EXPECT_EQ(result.find("ABACABA")->second, list<int>({0, 4, 10, 17}));
}

TEST(BorTest, BorTestMultiComplexWord) {
    BOR bor;
    bor.add("ABA");
    bor.add("BAB");
    bor.add("ABAB");
    map<string, list<int> > result = bor.search("ABABABA");
    EXPECT_EQ(result.find("ABA")->second, list<int>({0, 2, 4}));
    EXPECT_EQ(result.find("BAB")->second, list<int>({1, 3}));
    EXPECT_EQ(result.find("ABAB")->second, list<int>({0, 2}));
}

TEST(BorTest, BorTestMultiComplexWord2) {
    BOR bor;
    bor.add("ABACABA");
    bor.add("ABA");
    bor.add("ACA");
    bor.add("A");//                              012345678901234
    map<string, list<int> > result = bor.search("ABABACABACABABA");
    EXPECT_EQ(result.find("ABACABA")->second, list<int>({2, 6}));
    EXPECT_EQ(result.find("ABA")->second, list<int>({0, 2, 6, 10, 12}));
    EXPECT_EQ(result.find("ACA")->second, list<int>({4, 8}));
    EXPECT_EQ(result.find("A")->second, list<int>({0, 2, 4, 6, 8, 10, 12, 14}));
}

int main() {
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}