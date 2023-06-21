#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define OUTPUT_RATE 1
int main()
{
    int bucket_capacity,bucket_size;
    printf("Enter the bucket capacity: ");
    scanf("%d",&bucket_capacity);
    
    while(true)
    {
        int incoming_packets=rand()%5;
        printf("\nIncoming Packet is %d",incoming_packets);
        bucket_size+=incoming_packets;
        
        if(bucket_size>bucket_capacity)
        {
            printf("\nOverflow!! Dropping packets %d",bucket_size-bucket_capacity);
            bucket_size=bucket_capacity;
        }
        
        if(bucket_size>0)
        {
            int outgoing_packets=bucket_size<OUTPUT_RATE?bucket_size:OUTPUT_RATE;
            printf("\nOutgoing Packet is %d",outgoing_packets);
            bucket_size-=outgoing_packets;
        }
        printf("\nBucket Size: %d\n",bucket_size);
        sleep(1);
    }
    
}
