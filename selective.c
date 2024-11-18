#include <stdio.h>
#include <stdlib.h>
#define MAX_SEQ 5

typedef struct {
    int seq_num;
    char data[100];
} Frame;

void send_frame(Frame f) {
    printf("Sent Frame: %d\n", f.seq_num);
}

void receive_ack(int seq_num) {
    printf("ACK Received for Frame: %d\n", seq_num);
}

int main() {
    Frame frames[MAX_SEQ];
    int n = 10; // total number of frames to send
    int base = 0, next_seq = 0;
    int ack_received[MAX_SEQ] = {0};

    for (int i = 0; i < n; i++) {
        frames[i % MAX_SEQ].seq_num = i;
    }

    while (base < n) {
        while (next_seq < base + MAX_SEQ && next_seq < n) {
            if (!ack_received[next_seq % MAX_SEQ]) {
                send_frame(frames[next_seq % MAX_SEQ]);
            }
            next_seq++;
        }

        // Simulating ACK reception
        int ack = rand() % n;
        if (!ack_received[ack % MAX_SEQ]) {
            receive_ack(ack);
            ack_received[ack % MAX_SEQ] = 1;

            while (ack_received[base % MAX_SEQ]) {
                base++;
            }
        }
    }

    return 0;
}