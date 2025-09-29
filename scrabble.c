#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int computer_score(string word);

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = computer_score(word1);
    int score2 = computer_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int computer_score(string word)
{
    int score = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
        }
        if (isupper(word[i])) // 可以else if吗
        {
            score += POINTS[word[i] - 'a'];
        }
    }

    return score;
}
/*
    int score = 0;

    for (int i = 0, m = strlen(word1); i < m; i++)
    {
        int WORD1 = toupper(word1[i]);
        score1 += POINTS[WORD1[i]];
    }

    for (int j = 0, n = strlen(word2); j < n; j++)
    {
        int WORD2 = toupper(word2[i]);
        score2 += POINTS[WORD2[i]];
    }

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("tie\n");
    }
*/
