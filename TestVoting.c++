//---------
//includes
//---------

#include <sstream>
#include <string>
#include <iostream>
#include "gtest/gtest.h"
#include "Voting.h"


TEST(Voting, voting_solve_simple1) {
    std::istringstream r("1\n\n2\nBuddy\nGuy\n1 2\n1 2\n");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("Buddy\n", w.str());
}

TEST(Voting, voting_solve_simple2) {
    std::istringstream r("1\n\n2\nBuddy\nGuy\n1 2\n1 2\n1 2\n1 2\n1 2\n1 2\n1 2\n1 2\n1 2\n1 2\n");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("Buddy\n", w.str());
}

TEST(Voting, voting_solve_single) {
    std::istringstream r("1\n\n1\nAlone\n1");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("Alone\n", w.str());
}


TEST(Voting, voting_solve_tie) {
    std::istringstream r("1\n\n2\nBuddy\nGuy\n1 2\n2 1\n");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("Buddy\nGuy\n", w.str());
}

TEST(Voting, voting_solve_triple) {
    std::istringstream r("1\n\n3\nBuddy\nGuy\nDude\n1 2 3\n2 1 3\n3 1 2\n3 2 1\n");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("Dude\n", w.str());
}

TEST(Voting, voting_solve_triple_tie) {
    std::istringstream r("1\n\n3\nBuddy\nGuy\nDude\n1 2 3\n2 3 1\n3 1 2\n");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("Buddy\nGuy\nDude\n", w.str());
}

TEST(Voting, voting_solve_weird_names) {
    std::istringstream r("1\n\n3\n12353462fgsdfg\n!@!)*(*(#@^)#$\n<>?:{}+_@))$)##)#)#)#\n1 2 3\n2 3 1\n3 1 2\n3 2 1\n");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("<>?:{}+_@))$)##)#)#)#\n", w.str());
}

TEST(Voting, voting_solve_max_candidates) {
    std::istringstream r("1\n\n20\n111\n222\n333\n444\n555\n666\n777\n888\n999\n101010\n111111\n121212\n131313\n141414\n151515\n161616\n171717\n181818\n191919\n202020\n1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\n");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("111\n", w.str());
}

TEST(Voting, voting_solve_multi_case) {
    std::istringstream r("2\n\n2\nSam\nMax\n1 2\n 1 2\n\n2\nGreg\nMike\n1 2\n");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("Sam\n\nGreg\n", w.str());
}

TEST(Voting, voting_solve_multi_case2) {
    std::istringstream r("3\n\n2\nSam\nMax\n1 2\n 1 2\n\n2\nGreg\nMike\n1 2\n\n2\nGreglikestowin\nMikedoesntwin\n1 2\n");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("Sam\n\nGreg\n\nGreglikestowin\n", w.str());
}

TEST(Voting, voting_solve_repeat) {
    std::istringstream r("2\n\n2\nSam\nMax\n1 2\n 1 2\n\n2\nSam\nMax\n1 2\n");
    std::ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("Sam\n\nSam\n", w.str());
}


TEST(Voting, voting_eval1) {
    std::ostringstream w;
    std::vector<Candidate> candidates;

    Candidate c1;
    Line l1;
    l1.vote_to.push_back(1);
    l1.vote_to.push_back(2);
    l1.preference_number = 0;
    c1.name = "c1";
    c1.lose = false;
    c1.vote_line.push_back(l1);
    candidates.push_back(c1);

    Candidate c2;
    Line l2;
    l2.vote_to.push_back(1);
    l2.vote_to.push_back(2);
    l2.preference_number = 0;
    c2.name = "c2";
    c2.lose = false;
    c1.vote_line.push_back(l2);
    candidates.push_back(c2);

    voting_eval (candidates, w);
    ASSERT_EQ("c1\n", w.str());
}

TEST(Voting, voting_eval2) {
    std::ostringstream w;
    std::vector<Candidate> candidates;

    Candidate c1;
    Line l1; Line l3;
    l1.vote_to.push_back(1);
    l1.vote_to.push_back(2);
    l1.preference_number = 0;
    l3.vote_to.push_back(1);
    l3.vote_to.push_back(2);
    l3.preference_number = 0;
    c1.name = "c1";
    c1.lose = false;
    c1.vote_line.push_back(l1);
    c1.vote_line.push_back(l3);

    Candidate c2;
    Line l2;    
    l2.vote_to.push_back(2);
    l2.vote_to.push_back(1);    
    l2.preference_number = 0;
    c2.name = "c2";
    c2.lose = false;
    
    c2.vote_line.push_back(l2);

    candidates.push_back(c1);
    candidates.push_back(c2);

    voting_eval (candidates, w);
    ASSERT_EQ("c1\n", w.str());
}
