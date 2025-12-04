// #include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
int INDEX[] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O,
                P, Q, R, S, T, U, V, W, X, Y, Z};
int index[] = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o,
                p, q, r, s, t, u, v, w, x, y, z};
*/

bool only_digits(string s);
int switch_string(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }

    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plaintext = get_string("plaintext:  ");
    int key = switch_string(argv[1]);
    char ciphertext[strlen(plaintext) + 1];

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = ((plaintext[i] - 'A' + key) % 26) + 'A';
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = ((plaintext[i] - 'a' + key) % 26) + 'a';
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
}

bool only_digits(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

int switch_string(string s)
{
    return atoi(s);
}
