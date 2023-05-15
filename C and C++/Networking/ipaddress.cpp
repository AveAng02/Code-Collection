
#include <iostream>
#include <vector>
#include <string>



std::string trim(std::string str)
{
    std::string st = "";

    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] != ' ')
        {
            st += str[i];
        }
    }

    return st;
}


// breaks down the given ip into tokens and returns them
std::vector<std::string> tokenize_at(std::string str_main, char str)
{
    std::vector<std::string> tokens;
    std::string st = "";

    for(int i = 0; i < str_main.length(); i++)
    {
        if(str_main[i] == str)
        {
            tokens.push_back(trim(st));
            st = "";
            continue;
        }

        st += str_main[i];
    }

    tokens.push_back(st);

    return tokens;
}


// checks the validity of ipv4 port
bool valid_port_ipv4(std::string str)
{
    int sum = 0;

    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] < 48 || str[i] > 57)
        {
            return false;
        }

        sum = (sum * 10) + (str[i] - 48);
    }

    if(sum >= 0 && sum <= 255)
    {
        return true;
    }

    return false;
}


// checks the validity of ipv6 port
bool valid_port_ipv6(std::string str)
{
    std::string st = "";

    if(str == st)
    {
        return true;
    }

    for(int i = 0; i < str.length(); i++)
    {
        if((str[i] >= '0' && str[i] <= '9') ||
        (str[i] >= 'A' && str[i] <= 'F') ||
        (str[i] >= 'a' && str[i] <= 'f'))
        {
            st += str[i];
        }
        else{
            return false;
        }
    }

    return true;
}


// checks speciafically for the validity of ipv4
bool is_valid_ip4(std::string str)
{
    std::vector<std::string> ip_list = tokenize_at(str, '.');
    if(ip_list.size() != 4)
    {
        return false;
    }

    for(int i = 0; i < ip_list.size(); i++)
    {
        if(!valid_port_ipv4(ip_list[i]))
        {
            return false;
        }
    }

    return true;
}


// checks speciafically for the validity of ipv6
bool is_valid_ip6(std::string str)
{
    std::vector<std::string> ip_list = tokenize_at(str, ':');

    int n = str.find("::");
    if(n)
    {
        if(str.find("::", n + 1))
        {
            return false;
        }

        if(ip_list.size() != 8)
        {
            return false;
        }
    }

    for(int i = 0; i < ip_list.size(); i++)
    {
        if(!valid_port_ipv6(ip_list[i]))
        {
            return false;
        }
    }

    return true;
}


int main()
{
    std::string ip = "";
    int n = 0;


    std::cout << "Enter\n1 for IPv4\n2 for IPv6\n";
    std::cin >> n;

    std::cout << "Enter the ip : ";
    std::cin >> ip;

    switch(n)
    {
        case 1:
            if(is_valid_ip4(ip))
                std::cout << "IP is Valid." << std::endl;
            else
                std::cout << "IP is invalid." << std::endl;
            
            break;

        case 2:
            if(is_valid_ip6(ip))
                std::cout << "IP is Valid." << std::endl;
            else
                std::cout << "IP is invalid." << std::endl;
            
            break;

        default:
            std::cout << "Wrong choice!" << std::endl;
    }

    return 0;
}

