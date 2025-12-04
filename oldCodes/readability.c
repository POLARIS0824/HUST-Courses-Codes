// #include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    int Coleman_Liau;
    float index;
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float L = (float) letters / (float) words * 100.0000;
    float S = (float) sentences / (float) words * 100.0000;

    index = 0.0588 * L - 0.296 * S - 15.8;

    Coleman_Liau = round(index);

    if (Coleman_Liau < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (Coleman_Liau >= 16)
    {
        printf("After Grade 16\n");
    }
    else
    {
        printf("Grade %d\n", Coleman_Liau);
    }
}

int count_letters(string text)
{
    int sum1 = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            sum1++;
        }
    }

    return sum1;
}

int count_words(string text)
{
    int sum2 = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        {
            sum2++;
        }
    }
    return sum2;
}

int count_sentences(string text)
{
    int sum3 = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sum3++;
        }
    }
    return sum3;
}
