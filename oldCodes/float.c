#include <stdio.h>

void print_float(float n[])
{
    FILE *open = fopen("float.dat", "wb");
    if (open == NULL)
    {
        printf("File open failed\n");
        return;
    }
    for (int i = 0; i < 10; i++)
    {
        fwrite(&n[i], sizeof(float), 1, open);
    }
    fclose(open);

    FILE *read = fopen("float.dat", "rb");
    if (read == NULL)
    {
        printf("File open failed\n");
        return;
    }

    float x;
    unsigned int b;
    for (int i = 0; i < 10; i++)
    {
        fread(&x, sizeof(float), 1, read);
        memcpy(&b, &x, sizeof(float));

        for (int j = 31; j >= 0; j--)
        {
            printf("%d", (b >> j) & 1);
        }
        printf("\n");
    }
}

int main()
{
    float n[10];
    for (int i = 0; i < 10; i++)
    {
        scanf("%f", &n[i]);
    }
    print_float(n);
    return 0;
}