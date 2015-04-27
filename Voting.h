#ifndef Voting_h
#define Voting_h
// --------
// includes
// --------
#include <cassert> // assert
#include <iostream> 
#include <vector> // vector
#include <sstream> 
#include <stdlib.h>

//store each line of votes
struct Line 
{
    std::vector<int> vote_to;
    int preference_number;
};

//data structure for each candidate
struct Candidate 
{
    std::string name;
    std::vector<Line> vote_line;
    bool lose;
};
/**
 * Takes the data from candidates and computes the winner(s) 
 * and sends them to ostream w
 * @param candidates vector that contains candidate data
 * @param w an std::istream used for output
 */
void voting_eval (std::vector<Candidate>& candidates, std::ostream& w);

/**
 * Reads in file data from the istream and store that data into candidates
 * @param r an std::istream of the input file
 * @param candidates vector for storing candidate data from the read
 */
void voting_read (std::istream& r, std::vector<Candidate>& candidates);

/**
 * Main execution function, calls voting_read and voting_eval
 * @param r an std::istream for the input
 * @param w an std::ostream to send output
 */
void voting_solve (std::istream& r, std::ostream& w);


#endif