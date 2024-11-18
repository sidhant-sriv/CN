#include <stdio.h>

void encode(int data[4], int encoded[7])
{
    encoded[2] = data[0];
    encoded[4] = data[1];
    encoded[5] = data[2];
    encoded[6] = data[3];

    encoded[0] = data[0] ^ data[1] ^ data[3];
    encoded[1] = data[0] ^ data[2] ^ data[3];
    encoded[3] = data[1] ^ data[2] ^ data[3];
}

void decode(int encoded[7], int decoded[4])
{
    int p1, p2, p3, error_position;

    p1 = encoded[0] ^ encoded[2] ^ encoded[4] ^ encoded[6];
    p2 = encoded[1] ^ encoded[2] ^ encoded[5] ^ encoded[6];
    p3 = encoded[3] ^ encoded[4] ^ encoded[5] ^ encoded[6];

    error_position = (p3 << 2) | (p2 << 1) | p1;

    if (error_position != 0)
    {
        printf("Error detected at position: %d\n", error_position);
        encoded[error_position - 1] ^= 1;
        printf("Error corrected!\n");
    }
    else
    {
        printf("No errors detected.\n");
    }

    decoded[0] = encoded[2];
    decoded[1] = encoded[4];
    decoded[2] = encoded[5];
    decoded[3] = encoded[6];
}

int main()
{
    int data[4];
    int encoded[7];
    int decoded[4];

    printf("Enter 4 bits of data (space-separated): ");
    for (int i = 0; i < 4; i++)
    {
        scanf("%d", &data[i]);
    }

    encode(data, encoded);

    printf("Encoded 7-bit data: ");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", encoded[i]);
    }
    printf("\n");

    encoded[3] ^= 1;

    decode(encoded, decoded);

    printf("Decoded 4-bit data: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", decoded[i]);
    }
    printf("\n");

    return 0;
}
