#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 1024
#define TOTAL_FRAMES 5

int send_frame(int frame_num)
{
    return rand() % 2;
}

int receive_ack(int frame_num)
{
    return rand() % 2;
}

int main()
{
    int frame_num = 0;
    int ack_received;

    srand(2);

    printf("Starting ARQ Stop-and-Wait Protocol\n");

    while (frame_num < TOTAL_FRAMES)
    {
        printf("Sending frame %d\n", frame_num);

        if (send_frame(frame_num))
        {
            printf("Frame %d sent successfully.\n", frame_num);

            ack_received = receive_ack(frame_num);

            if (ack_received)
            {
                printf("ACK received for frame %d.\n", frame_num);
                frame_num++;
            }
            else
            {
                printf("NACK received for frame %d. Resending...\n");
            }
        }
        else
        {
            printf("Frame %d was lost. Resending...\n");
        }
    }

    printf("All frames sent successfully.\n");

    return 0;
}
