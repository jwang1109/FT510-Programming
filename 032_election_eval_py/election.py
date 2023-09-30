from sys import argv
import sys
import pdb

def parse_state_information(filename):
    """
    Opens the state information file named in filename, loads all of the 
    values, placing them in a single data structure. Returns that data 
    structure.  You may created nested data structures.
    """
    ans = {}
    f = open(filename,"r")
    for line in f:
        line = line.strip()
        line = line.replace("\n","")
        l = line.split(":")
        value = l[1:]
        value = [int(x) for x in value]
        ans[l[0]] = value
    f.close()    
    return ans
    
def print_state_information(state_info):
    """
    For the state_info data structure (produced as a result),
    print all statues in alphabetical order using the string:
    "{}: Population - {:,d}, Electoral Votes: {:d}"
    """
    for s in sorted(state_info):
        print("{}: Population - {:,d}, Electoral Votes: {:d}".format(s,state_info[s][0],state_info[s][1]))

def parse_vote_information(filename):
    """
    Opens the vote information file and returns the information 
    in a data structure
    """
    ans = {}
    f = open(filename,"r")
    for line in f:
        line = line.strip()
        line = line.replace("\n","")
        l = line.split(":")
        ans[l[0]] = int(l[1])
    f.close()
    return ans

def count_electoral_votes(state_info,vote_info):
    """
    Counts and returns the number of electoral votes received by 
    Candidate A in the election.

    For our purposes, Candidate A receives ALL electoral votes for a
    state if Candidate A receives strictly more than 50% of the votes in
    that State.  [Yes, we know that in the US there are a few states
    with more complex rules, but we will ignore them.  We will also
    ignore the electoral complexities of what would happen if a
    candidate received exactly 50%, and in this case, just say that
    Candidate A does not receive those electoral votes.  We are also
    assuming everyone in every state votes--while this doesn't happen in
    a real election, it is what we are doing here].
    """

    count = 0
    for s in state_info:
        if  vote_info[s]/state_info[s][0] > 0.5:
           count += state_info[s][1]
    return count

def determine_winner(state_info, candidate_a_electoral_votes):

    """
    Determines whether Candidate A or Candidate B won based upon who
    won the majority of the electoral votes. If there is a tie, return None.
    Returns "A", "B", or None    the last one is the value None
    """
    a_votes = candidate_a_electoral_votes
    total = 0
    for s in state_info:
        total += int(state_info[s][1])
        
    b_votes = total - candidate_a_electoral_votes
    if b_votes == a_votes:
        return None
    elif b_votes < a_votes:
        return "A"
    elif b_votes > a_votes:
        return "B"

def print_winner(winner_name, number_of_votes):
    """
    Prints the winner.  If Candidate A or B wins, print
    "Candidate {} wins the election with {:d} votes" using the winner_name
    and number of Electoral Collage.

    If neither won the vote, print "It's a tie in the Electoral Collage."
    """
    votes_n = []
    if winner_name == None:
        print("It's a tie in the Electoral Collage.")
    elif winner_name == "A":
        votes_n = number_of_votes[0]
    elif winner_name == "B":
        votes_n = number_of_votes[1]
        
    print("Candidate {} wins the election with {:d} votes".format(winner_name,votes_n))

def determine_recounts(state_info, vote_info):
    """
    Produces a list of strings, where each string represents information
    about a state the requires a recount. Recounts are required when a 
    Candidate A is within +/ 0.5% of 50% of the votes.  So 49.50% or 50.50%
    require a recount, while 49.49% and 50.51% do not require a recount.
    
    Only include states that require a recount in the result. For each state
    that requires a recount, include a line of the form:
    "{} requires a recount (Candidate A has {:.2f}% of the vote)".
    """
    ans =[]
    for s in state_info:
        pcnt = vote_info[s]/state_info[s][0]
        if 0.495 <= pcnt <= 0.505:
            ans.append("{} requires a recount (Candidate A has {:.2f}% of the vote)\n".format(s,pcnt*100))  
    return ans

def save_recounts(recount_list):
    """
    saves each entry of the list to a file named "recounts.txt".  The
    entries must be printed in alphabetical order.
    """
    sorted_l = sorted(recount_list)
    f = open("recounts.txt", "w")
    for r in sorted_l:
        f.write(r)
    f.close()

def determine_largest_win(state_info, vote_info):
    """
    Determines in which state Candidate A won the largest percentage 
    of the vote.

    returns a string with the following format:
    "Candidate A won {} with {:.2f}% of the vote"

    where the first {} should be the name of the state, and the {.2f} 
    should be the percentage of the vote won.  For example, it might return
    "Candidate A won California with 73.24% of the vote"

    None is returned if candidate A did not win a state
    """
    pcnt_d = {}
    for s in state_info:
        pcnt = vote_info[s]/state_info[s][0]
        pcnt_d[s] = pcnt
    max_state = max(pcnt_d,key=pcnt_d.get)
    return "Candidate A won {} with {:.2f}% of the vote".format(max_state,pcnt_d[max_state]*100)

def process(state_info_filename, voter_info_filename):
    """
    Implements the "Several steps exist for this assignment" section
    """
    #read_info
    state_info = parse_state_information(state_info_filename)
    vote_info = parse_vote_information(voter_info_filename)
    elec_A_count = count_electoral_votes(state_info, vote_info)
    winner_name = determine_winner(state_info,elec_A_count)

    #determine the total of electoral votes and calculate electoral votes of B then
    elec_total = 0
    for s in state_info:
        elec_total += int(state_info[s][1])    
    elec_B_count = elec_total - elec_A_count
    votes_number = [] # 0th store electoral votes of A, 1th store electoral votes of B
    votes_number.append(elec_A_count)
    votes_number.append(elec_B_count)

    #print result and save_recounts
    save_recounts(determine_recounts(state_info,vote_info))
    print_state_information(state_info)
    print_winner(winner_name, votes_number)
    print(determine_largest_win(state_info,vote_info))
    



if __name__ == "__main__":
    """implement checking command line arguments, call process()"""
    if len(argv) != 3:
        print("Usage:python3 states.txt votes.txt")
        sys.exit(1)
    try:
        process(argv[1],argv[2])
    except Exception as e:
        print(e)
        sys.exit(1)
