
#include <iostream>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

// checks speciafically for the validity of ipv4
bool is_valid_ip4(std::string str)
{
    std::vector<int> ip_list; // = tokenize_at(str, '.');

    int port = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            ip_list.push_back(port);
            port = 0;
            continue;
        }

        port = (port * 10) + (str[i] - 48);
    }

    ip_list.push_back(port);

    if (ip_list.size() != 4)
    {
        return false;
    }

    for (int i = 0; i < ip_list.size(); i++)
    {
        if (ip_list[i] <= 0 && ip_list[i] >= 255)
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    int i;
    struct hostent *he;
    struct in_addr **addr_list;
    struct in_addr addr;

    if (!is_valid_ip4(argv[1]))
    {
        // get the addresses of website passed
        he = gethostbyname(argv[1]);
        if (he == NULL)
        {                            
            herror("gethostbyname"); 
            return 0;
        }

        printf("Official name is: %s\n", he->h_name);
        printf("IP address: %s\n", inet_ntoa(*(struct in_addr *)he->h_addr));
        printf("All addresses: ");
        addr_list = (struct in_addr **)he->h_addr_list;
        for (i = 0; addr_list[i] != NULL; i++)
        {
            printf("%s ", inet_ntoa(*addr_list[i]));
        }
        printf("\n");
    }
    else
    {
        // get the host name of given ip
        inet_aton(argv[1], &addr);
        he = gethostbyaddr(&addr, sizeof(addr), AF_INET);
        if (he == NULL)
        {                            
            herror("gethostbyaddr"); 
            return 0;
        }
        printf("Official name is: %s\n", he->h_name);
        printf("IP address: %s\n", inet_ntoa(*(struct in_addr *)he->h_addr));
        printf("All addresses: ");
        addr_list = (struct in_addr **)he->h_addr_list;
        for (i = 0; addr_list[i] != NULL; i++)
        {
            printf("%s ", inet_ntoa(*addr_list[i]));
        }
        printf("\n");
    }
    return 0;
}
