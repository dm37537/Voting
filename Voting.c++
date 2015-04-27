
// --------
// includes
// --------
#include "Voting.h"

#include <cassert> // assert
#include <iostream> 
#include <vector> // vector
#include <sstream> 
#include <stdlib.h>

//global counter for voters
int number_of_vote_line = 0;

//take in the data, then compute and print
void voting_eval (std::vector<Candidate>& candidates, std::ostream& w) {
    
    using namespace std;
    int min = number_of_vote_line;
    int max = 0;
    int max_vote_candidate = 0;
    std::vector<int> lose_this_round;
    
    //cout << " get in " <<endl;
    
    //corner case : get rid of candidates who has already lost from start
    for(int i = 0; i < candidates.size(); i++) 
    {
        if(candidates[i].vote_line.size() == 0)
        {
            candidates[i].lose = true;
        }
    }

    //find max and min
    for(int i = 0; i < candidates.size(); ++i)
    {
        if(!candidates[i].lose)
        {
            int votes_of_this_candidate = candidates[i].vote_line.size();
            
            if (min > votes_of_this_candidate)
            {
                min = votes_of_this_candidate;
            }

            if (max < votes_of_this_candidate)
            {
                max = votes_of_this_candidate;
            }            
        }
    }
    
    //get the candidate with max votes
    for(int i = 0; i < candidates.size(); ++i)
    {
        if( max == candidates[i].vote_line.size())
        {
            max_vote_candidate = i;
        }
    }
    



    //return when someone get majority
    if(max > number_of_vote_line/2)
    {
        w << candidates[max_vote_candidate].name << endl;
        return;
    }

    //detect if there is a tie
    if(min == max)
    {
        for(int i = 0; i < candidates.size(); ++i)
        {
            if(!candidates[i].lose)
            {
                w << candidates[i].name << endl;
            }
        }
        return;
    }

    
    //find loser
    for(int i = 0; i < candidates.size(); ++i)
    {
        if(!candidates[i].lose && candidates[i].vote_line.size() == min)
        {
            candidates[i].lose = true;
            lose_this_round.push_back(i);         
        }
    }  
    
    //update preference number
    for(int i = 0; i < lose_this_round.size(); ++i) 
    {
        int loser = lose_this_round[i];

        for(int j = 0; j < candidates[loser].vote_line.size(); ++j) 
        {
            int preference_number = candidates[loser].vote_line[j].preference_number;   

            int candicate_try_vote_to = candidates[loser].vote_line[j].vote_to[preference_number] - 1;

            while(candidates[ candicate_try_vote_to ].lose) 
            {
                preference_number += 1;
                candicate_try_vote_to = candidates[loser].vote_line[j].vote_to[preference_number] - 1;
            }

            int candidate_decided_to_vote_to = candidates[loser].vote_line[j].vote_to[preference_number] - 1;

            candidates[ candidate_decided_to_vote_to ].vote_line.push_back(candidates[loser].vote_line[j]);
        }
    }
   

   voting_eval(candidates, w);
    
}


// ------------
// voting_read
// ------------
//read file data into our data structure
void voting_read (std::istream& r, std::vector<Candidate>& candidates) {
        
    using namespace std;
    int number_of_candidates;
    r >> number_of_candidates;
    assert (number_of_candidates > 0);

    char name[80];
    
    r.getline(name, 80);

    for (int i = 0; i < number_of_candidates; i++)
    {
        
        r.getline(name, 80);
        string candidate_name(name);

        Candidate c;
        c.name = candidate_name;
        c.lose = false;
        
        candidates.push_back(c);
        //cout << candidates[i].name << endl; // Delete later

    }

    char votes_list[80]; 
    while(r.getline(votes_list, 80) && votes_list[0] != '\0')
    {

        string str(votes_list);
        
        Line line_of_vote;
        line_of_vote.preference_number = 0;
        
        stringstream ss(str);
        string buf;
        while (ss >> buf)
        {
            line_of_vote.vote_to.push_back(atoi(buf.c_str()));
        }

        candidates[line_of_vote.vote_to[0] - 1].vote_line.push_back(line_of_vote);
        ++number_of_vote_line;
    }

    assert (number_of_vote_line > 0);

}
    
// -------------
// voting_solve
// -------------
//main path of the program
void voting_solve (std::istream& r, std::ostream& w) {
    
    using namespace std;
    int number_of_cases;  
    r >> number_of_cases;
    assert (number_of_cases > 0);
    
    for(int i = 0; i < number_of_cases; ++i)
    {               
        number_of_vote_line = 0;
        vector< Candidate > candidates;
        voting_read(r, candidates);        
        voting_eval(candidates, w);   
        if(i < number_of_cases - 1)  w << endl;
    }
} 