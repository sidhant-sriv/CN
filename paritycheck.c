#include <stdio.h>
#include <string.h>

char calculate_parity_bit(const char *data, int odd_parity) {
    int count = 0;
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == '1') {
            count++;
        }
    }
    if (odd_parity) {
        return (count % 2 == 0) ? '1' : '0';
    } else {
        return (count % 2 == 0) ? '0' : '1';
    }
}

void add_parity_bit(char *data, char parity_bit) {
    int data_length = strlen(data);
    data[data_length] = parity_bit;
    data[data_length + 1] = '\0';
}

int main() {
    char data[256];
    printf("Enter the data unit (binary string): ");
    scanf("%255s", data);

    char odd_parity_bit = calculate_parity_bit(data, 1);
    char even_parity_bit = calculate_parity_bit(data, 0);

    printf("Data: %s\n", data);
    printf("Odd Parity bit: %c\n", odd_parity_bit);
    printf("Even Parity bit: %c\n", even_parity_bit);

    char data_with_odd_parity[258];
    char data_with_even_parity[258];

    strcpy(data_with_odd_parity, data);
    strcpy(data_with_even_parity, data);

    add_parity_bit(data_with_odd_parity, odd_parity_bit);
    add_parity_bit(data_with_even_parity, even_parity_bit);

    printf("Data with Odd Parity: %s\n", data_with_odd_parity);
    printf("Data with Even Parity: %s\n", data_with_even_parity);

    return 0;
}
