#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 20
int calculateParityBits(int dataLength)
{
    int r = 0;
    while ((1 << r) < (dataLength + r + 1))
    {
        r++;
    }
    return r;
}
void generateHammingCode(char *data, char *code)
{
    int dataLength = strlen(data);
    int r = calculateParityBits(dataLength);
    int codeLength = dataLength + r;
    int j = 0;
    for (int i = 1; i <= codeLength; i++)
    {
        if ((i & (i - 1)) != 0)
        {
            code[codeLength - i] = data[dataLength - 1 - j];
            j++;
        }
        else
        {
            code[codeLength - i] = '0';
        }
    }
    for (int i = 0; i < r; i++)
    {
        int parity = 0;
        for (int j = 1; j <= codeLength; j++)
        {
            if (j & (1 << i))
            {
                parity ^= (code[codeLength - j] - '0');
            }
        }
        code[codeLength - (1 << i)] = parity + '0';
    }
    code[codeLength] = '\0';
}
int detectError(char *receivedCode)
{
    int codeLength = strlen(receivedCode);
    int errorPosition = 0;
    for (int i = 0; i < codeLength; i++)
    {
        int parity = 0;
        for (int j = 1; j <= codeLength; j++)
        {
            if (j & (1 << i))
            {
                parity ^= (receivedCode[codeLength - j] - '0');
            }
        }
        if (parity)
        {
            errorPosition += (1 << i);
        }
    }
    return errorPosition;
}
int main()
{
    char dataWord[MAX_LENGTH];
    char hammingCode[MAX_LENGTH * 2];
    char receivedCode[MAX_LENGTH * 2];
    printf("Enter the data word: ");
    scanf("%s", dataWord);
    generateHammingCode(dataWord, hammingCode);
    printf("Generated Hamming code: %s\n", hammingCode);
    printf("Enter the received code word to check for errors: ");
    scanf("%s", receivedCode);
    int errorPosition = detectError(receivedCode);
    if (errorPosition == 0)
    {
        printf("No error detected.\n");
    }
    else
    {
        printf("Error detected at position %d.\n", errorPosition);
    }
    return 0;
}