#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DATA_LENGTH 1000
void print_binary(unsigned int num, int bits)
{
    for (int i = bits - 1; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
    }
}
unsigned int add_binary(unsigned int a, unsigned int b, int bits)
{
    unsigned int sum = a + b;
    return sum & ((1 << bits) - 1);
}
unsigned int ones_complement(unsigned int num, int bits)
{
    return (~num) & ((1 << bits) - 1);
}
unsigned int xor_operation(unsigned int a, unsigned int b, int bits)
{
    return (a ^ b) & ((1 << bits) - 1);
}
unsigned int calculate_checksum(char *data, int data_length, int checksum_bits)
{
    unsigned int sum = 0;
    printf("Dividing data into %d-bit parts and adding:\n", checksum_bits);
    for (int i = 0; i < data_length; i += checksum_bits)
    {
        unsigned int part = 0;
        for (int j = 0; j < checksum_bits; j++)
        {
            part = (part << 1) | (data[i + j] - '0');
        }
        printf("Part %d: ", i / checksum_bits + 1);
        print_binary(part, checksum_bits);
        printf("\n");
        sum = add_binary(sum, part, checksum_bits);
    }
    printf("Sum: ");
    print_binary(sum, checksum_bits);
    printf("\n");
    unsigned int checksum = ones_complement(sum, checksum_bits);
    printf("Checksum (1's complement of sum): ");
    print_binary(checksum, checksum_bits);
    printf("\n");
    return checksum;
}
int main()
{
    char data[MAX_DATA_LENGTH];
    char received_data[MAX_DATA_LENGTH];
    int data_length, checksum_bits;
    printf("Enter the data unit (binary string): ");
    scanf("%s", data);
    data_length = strlen(data);
    printf("Enter the number of bits for checksum: ");
    scanf("%d", &checksum_bits);
    if (data_length % checksum_bits != 0)
    {
        printf("Error: Data length must be a multiple of checksum bits.\n");
        return 1;
    }
    unsigned int data_checksum = calculate_checksum(data, data_length, checksum_bits);
    printf("Enter the received data unit (binary string): ");
    scanf("%s", received_data);
    int received_data_length = strlen(received_data);
    if (received_data_length % checksum_bits != 0)
    {
        printf("Error: Received data length must be a multiple of checksum bits.\n");
        return 1;
    }
    unsigned int received_checksum = calculate_checksum(received_data, received_data_length,
                                                        checksum_bits);
    printf("Performing XOR operation on checksums:\n");
    unsigned int xor_result = xor_operation(data_checksum, received_checksum, checksum_bits);
    printf("\n");
    if (xor_result == 0)
    {
        printf("The receiver got the correct data (all zeros).\n");
    }
    else
    {
        printf("Error detected in received data.\n");
    }
    return 0;
}