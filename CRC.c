#include <stdio.h>
#include <string.h>

// Function to perform XOR operation
void xorOperation(char *dividend, const char *polynomial, int len) {
    for (int i = 0; i < len; i++) {
        dividend[i] = (dividend[i] == polynomial[i]) ? '0' : '1';
    }
}

// Function to perform the CRC calculation
void calculateCRC(char *data, const char *polynomial, char *remainder) {
    int dataLen = strlen(data);
    int polyLen = strlen(polynomial);

    // Append zeros (degree of the polynomial - 1) to the data
    char dividend[100];
    strcpy(dividend, data);
    for (int i = 0; i < polyLen - 1; i++) {
        strcat(dividend, "0");
    }

    // Perform division
    for (int i = 0; i <= dataLen; i++) {
        if (dividend[i] == '1') {
            xorOperation(&dividend[i], polynomial, polyLen);
        }
    }

    // Extract the remainder
    strncpy(remainder, &dividend[dataLen], polyLen - 1);
    remainder[polyLen - 1] = '\0';
}

int main() {
    char data[100], polynomial[100], remainder[100];

    // Input data and polynomial
    printf("Enter the binary data string: ");
    scanf("%s", data);
    printf("Enter the binary polynomial string: ");
    scanf("%s", polynomial);

    // Calculate CRC
    calculateCRC(data, polynomial, remainder);

    // Print the remainder (CRC)
    printf("The CRC remainder is: %s\n", remainder);

    return 0;
}