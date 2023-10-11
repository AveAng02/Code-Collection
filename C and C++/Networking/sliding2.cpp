
#include<iostream>
#include<stdio.h>
#include <string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include <unistd.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>

 
#define cls() std::cout << "33[H33[J"

//structure definition for accepting the packets.
struct frame
{
    int packet[40];
};


//structure definition for constructing the acknowledgement frame
struct ack
{
    int acknowledge[40];
};

 

int main()
{
    int clientsocket;
    sockaddr_in serveraddr;
    socklen_t len;
    hostent* server;
    frame f1;
    int windowsize, totalpackets, totalframes, i=0, j=0, framesreceived=0, k, l, m, repacket[40];
    ack acknowledgement;
    char req[50];

    clientsocket=socket(AF_INET,SOCK_DGRAM,0);

    bzero((char*)&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;

    serveraddr.sin_port = htons(5018);

    server = gethostbyname("127/.0/.0/.1");

    bcopy((char*)server->h_addr, (char*)&serveraddr.sin_addr.s_addr, sizeof(server->h_addr));

    //establishing the connection.
    std::cout << "\nSending request to the client.\n" << std::endl;

    sendto(clientsocket, "HI I AM CLIENT.", sizeof("HI I AM CLIENT."),0,(sockaddr*)&serveraddr,sizeof(serveraddr));

    std::cout << "\nWaiting for reply.\n" << std::endl;

    recvfrom(clientsocket,req,sizeof(req),0,(sockaddr*)&serveraddr,&len);

    std::cout << "\nThe server has send:\t" << req << "\n" << std::endl;

    //accepting window size from the user.
    std::cout << "\nEnter the window size:\t";
    std::cin >> windowsize;

    //sending the window size.
    std::cout << "\n\nSending the window size." << std::endl;

    sendto(clientsocket,(char*)&windowsize,sizeof(windowsize),0,(sockaddr*)&serveraddr,sizeof(serveraddr));

    cls();

    //collecting details from server
    std::cout << "\nWaiting for the server response.\n" << std::endl;

    recvfrom(clientsocket,(char*)&totalpackets,sizeof(totalpackets),0,(sockaddr*)&serveraddr,&len);

    std::cout << "\nThe total packets are:\t" << totalpackets << std::endl;

    sendto(clientsocket, "RECEIVED.", sizeof("RECEIVED."), 0, (sockaddr*)&serveraddr, sizeof(serveraddr));

    recvfrom(clientsocket, (char*)&totalframes, sizeof(totalframes), 0, (sockaddr*)&serveraddr, &len);

    std::cout << "\nThe total frames/windows are:\t" << totalframes << std::endl;

    sendto(clientsocket, "RECEIVED.", sizeof("RECEIVED."), 0, (sockaddr*)&serveraddr, sizeof(serveraddr));

    //starting the process.
    std::cout << "\nStarting the process of receiving." << std::endl;

    j=0;

    l=0;

    while(l<totalpackets)
    {                                                
        //initialising the receive buffer.
        std::cout << "\nInitialising the receive buffer." << std::endl;
        std::cout << "\nThe expected frame is" << framesreceived << " with packets:  ";

        for(m=0;m<j;m++)
        {                                    
            //readjusting for packets with negative acknowledgement.
            std::cout << repacket[m] << "\t";
        }

        while(j<windowsize && i<totalpackets)
        {
            std::cout << i << "\t";
            i++;
            j++; 
        }

        std::cout << "\n\nWaiting for the frame." << std::endl;

        //accepting the frame.  
        recvfrom(clientsocket, (char*)&f1, sizeof(f1), 0, (sockaddr*)&serveraddr, &len);

        std::cout << "\nReceived frame " << framesreceived << "\n\nEnter -1 to send negative acknowledgement for the following packets." << std::endl;

        //constructing the acknowledgement frame.
        j=0;
        m=0;
        k=l;

        while(m<windowsize && k<totalpackets)
        {
            std::cout << "\nPacket: " << f1.packet[m] << std::endl;

            //accepting acknowledgement from the user.
            std::cout << acknowledgement.acknowledge[m] << std::endl;

            if(acknowledgement.acknowledge[m]==-1)
            {
                repacket[j]=f1.packet[m];
                j++;
            }
            else
            {
                l++;
            }

            m++;
            k++;
        }

        framesreceived++;

        //sending acknowledgement to the server.
        sendto(clientsocket,(char*)&acknowledgement,sizeof(acknowledgement),0,(sockaddr*)&serveraddr,sizeof(serveraddr));

        cls();
    }

    std::cout << "\nAll frames received successfully.\n\nClosing connection with the server.\n" << std::endl;

    close(clientsocket);

    return 0;
} 