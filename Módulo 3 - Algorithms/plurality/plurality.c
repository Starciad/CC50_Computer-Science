#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
} candidate;

//______________________//

candidate candidates[MAX];
int candidate_count;

//______________________//

bool vote(string name);
void print_winner(void);

//______________________//

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0) {
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}

void print_winner(void)
{
    candidate selectedCandidate;
    candidate candidateToReplace;

    int maxVotes = 0;

    for(int i = 0; i < candidate_count; i++)
    {
        selectedCandidate = candidates[i];

        for (int j = (i + 1); j < i; j++)
        {
            if (selectedCandidate.votes < candidates[j].votes)
                candidateToReplace = candidates[j];
        }

        candidate temp = selectedCandidate;
        selectedCandidate = candidateToReplace;
        candidateToReplace = temp;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == maxVotes) {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}