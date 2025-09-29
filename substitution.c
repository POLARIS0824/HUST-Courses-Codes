#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {

        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char OriginalKey[26];
    strcpy(OriginalKey, argv[1]);

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(OriginalKey[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        for (int j = i + 1; j < 26; j++)
        {
            if (OriginalKey[i] == OriginalKey[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    char key[26];
    char KEY[26];

    for (int i = 0; i < 26; i++)
    {
        key[i] = tolower(OriginalKey[i]);
        KEY[i] = toupper(OriginalKey[i]);
    }

    string plaintext = get_string("plaintext:  ");

    char ciphertext[strlen(plaintext) + 1];

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (islower(plaintext[i]))
        {
            ciphertext[i] = key[plaintext[i] - 'a'];
        }
        else if (isupper(plaintext[i]))
        {
            ciphertext[i] = KEY[plaintext[i] - 'A'];
        }
        else
        {
            ciphertext[i] = plaintext[i]; // 非字母字符保持不变
        }
    }

    ciphertext[strlen(plaintext)] = '\0'; // 添加字符串结束符
    printf("ciphertext: %s\n", ciphertext);
}
