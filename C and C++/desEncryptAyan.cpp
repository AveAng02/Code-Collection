#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

string convertHextoBin(string hex_str)
{
    int i=0;
    string bin_str="";
    while(hex_str[i])
    {
        switch(hex_str[i])
        {
            case '0':
                bin_str+="0000";
                break;
            case '1':
                bin_str+="0001";
                break;
            case '2':
                bin_str+="0010";
                break;
            case '3':
                bin_str+="0011";
                break;
            case '4':
                bin_str+="0100";
                break;
            case '5':
                bin_str+="0101";
                break;
            case '6':
                bin_str+="0110";
                break;
            case '7':
                bin_str+="0111";
                break;
            case '8':
                bin_str+="1000";
                break;
            case '9':
                bin_str+="1001";
                break;
            case 'A':
                bin_str+="1010";
                break;
            case 'B':
                bin_str+="1011";
                break;
            case 'C':
                bin_str+="1100";
                break;
            case 'D':
                bin_str+="1101";
                break;
            case 'E':
                bin_str+="1110";
                break;
            case 'F':
                bin_str+="1111";
                break;
            default:
                cout<<"Invalid character."<<endl;
        }
        i++;
    }
    return bin_str;
}

string PC1(string key64)
{
    int pc1[8][7]={{57,49,41,33,25,17,9},{1,58,50,42,34,26,18},{10,2,59,51,43,35,27},{19,11,3,60,52,44,36},
                   {63,55,47,39,31,23,15},{7,62,54,46,38,30,22},{14,6,61,53,45,37,29},{21,13,5,28,20,12,4}};
    
    string key56="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<7;j++)
            key56+=key64[pc1[i][j]-1];
    }

    return key56;
}

string circularLeftShift(string bin_str)
{
    string left_shifted_str=bin_str.substr(1)+bin_str[0];
    return left_shifted_str;
}

vector<string> roundKeyArrayGen(string key56)
{
    vector<string> roundKeyArray;
    string res_str=key56;
    for(int i=1;i<=16;i++)
    {
        if(i==1 || i==2 || i==9 || i==16)
        {
            res_str=circularLeftShift(res_str.substr(0,28))+circularLeftShift(res_str.substr(28));
            roundKeyArray.push_back(res_str);
        }
        else
        {
            res_str=circularLeftShift(res_str.substr(0,28))+circularLeftShift(res_str.substr(28));
            res_str=circularLeftShift(res_str.substr(0,28))+circularLeftShift(res_str.substr(28));
            roundKeyArray.push_back(res_str);
        }
    }
    return roundKeyArray;
}

vector<string> PC2(vector<string> roundKeyArray)
{
    int pc2[8][6]={{14,17,11,24,1,5},{3,28,15,6,21,10},{23,19,12,4,26,8},{16,7,27,20,13,2},
                   {41,52,31,37,47,55},{30,40,51,45,33,48},{44,49,39,56,34,53},{46,42,50,36,29,32}};
    
    vector<string> key48Array;

    for(int i=0;i<16;i++)
    {
        string perm_str="";
        for(int j=0;j<8;j++)
        {
            for(int k=0;k<6;k++)
                perm_str+=roundKeyArray[i][pc2[j][k]-1];
        }
        key48Array.push_back(perm_str);
    }
    return key48Array;
}

string IP(string pt64)
{
    int ip[8][8]={{58,50,42,34,26,18,10,2},{60,52,44,36,28,20,12,4},{62,54,46,38,30,22,14,6},{64,56,48,40,32,24,16,8},
                  {57,49,41,33,25,17,9,1},{59,51,43,35,27,19,11,3},{61,53,45,37,29,21,13,5},{63,55,47,39,31,23,15,7}};
    
    string perm_pt64="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
            perm_pt64+=pt64[ip[i][j]-1];
    }

    return perm_pt64;
}

string EP(string rpt)
{
    int ep[8][6]={{32,1,2,3,4,5},{4,5,6,7,8,9},{8,9,10,11,12,13},{12,13,14,15,16,17},
                  {16,17,18,19,20,21},{20,21,22,23,24,25},{24,25,26,27,28,29},{28,29,30,31,32,1}};
    
    string extend_rpt="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<6;j++)
            extend_rpt+=rpt[ep[i][j]-1];
    }

    return extend_rpt;
}

string XOR(string s1,string s2)
{
    string res_str="";
    for(int i=0;i<s1.length();i++)
        res_str+=(s1[i]==s2[i])?'0':'1';
    return res_str;
}

int convertBintoDecIndex(string bin_str)
{
    int index=0;
    for(int i=0;i<bin_str.length();i++)
    {
        index+=((int)(bin_str[i]-'0'))*pow(2,bin_str.length()-1-i);
    }
    return index;
}

string sBoxBinaryConvertion(int sbox_res)
{
    int i=0;
    string bin_str="";
    switch(sbox_res)
    {
        case 0:
            bin_str="0000";
            break;
        case 1:
            bin_str="0001";
            break;
        case 2:
            bin_str="0010";
            break;
        case 3:
            bin_str="0011";
            break;
        case 4:
            bin_str="0100";
            break;
        case 5:
            bin_str="0101";
            break;
        case 6:
            bin_str="0110";
            break;
        case 7:
            bin_str="0111";
            break;
        case 8:
            bin_str="1000";
            break;
        case 9:
            bin_str="1001";
            break;
        case 10:
            bin_str="1010";
            break;
        case 11:
            bin_str="1011";
            break;
        case 12:
            bin_str="1100";
            break;
        case 13:
            bin_str="1101";
            break;
        case 14:
            bin_str="1110";
            break;
        case 15:
            bin_str="1111";
            break;
        default:
            cout<<"Invalid character."<<endl;
    }
    return bin_str;
}

string sBoxComputation(string xor_txt)
{
    int S[8][4][16]={{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                   {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
                   {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                   {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
                   {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                   {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
                   {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                   {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
                   {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                   {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
                   {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                   {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
                   {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                   {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
                   {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                   {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};

    string sbox_Output="";
    for(int i=0;i<8;i++)
    {
        string sBox_input=xor_txt.substr(i*6,6);
        string row=sBox_input.substr(0,1)+sBox_input.substr(sBox_input.length()-1,1);
        string col=sBox_input.substr(1,4);

        int sbox_res=S[i][convertBintoDecIndex(row)][convertBintoDecIndex(col)];
        string sbox_res_str=sBoxBinaryConvertion(sbox_res);
        sbox_Output+=sbox_res_str;
    }
    return sbox_Output;
}

string P32(string sbox_Output)
{
    int ep[8][4]={{16,7,20,21},{29,12,28,17},{1,15,23,26},{5,18,31,10},
                  {2,8,24,14},{32,27,3,9},{19,13,30,6},{22,11,4,25}};
    
    string perm_sbox="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<4;j++)
            perm_sbox+=sbox_Output[ep[i][j]-1];
    }

    return perm_sbox;
}

string FP(string rev64)
{
    int ip[8][8]={{40,8,48,16,56,24,64,32},{39,7,47,15,55,23,63,31},{38,6,46,14,54,22,62,30},{37,5,45,13,53,21,61,29},
                  {36,4,44,12,52,20,60,28},{35,3,43,11,51,19,59,27},{34,2,42,10,50,18,58,26},{33,1,41,9,49,17,57,25}};
    
    string cipher_text="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
            cipher_text+=rev64[ip[i][j]-1];
    }

    return cipher_text;
}

string convertBintoHex(string bin_str)
{
    string hex_str="";
    for(int i=0;i<bin_str.length();i=i+4)
    {
        string hex_digit=bin_str.substr(i,4);
        if(hex_digit=="0000")
            hex_str+='0';
        else if(hex_digit=="0001")
            hex_str+='1';
        else if(hex_digit=="0010")
            hex_str+='2';
        else if(hex_digit=="0011")
            hex_str+='3';
        else if(hex_digit=="0100")
            hex_str+='4';
        else if(hex_digit=="0101")
            hex_str+='5';
        else if(hex_digit=="0110")
            hex_str+='6';
        else if(hex_digit=="0111")
            hex_str+='7';
        else if(hex_digit=="1000")
            hex_str+='8';
        else if(hex_digit=="1001")
            hex_str+='9';
        else if(hex_digit=="1010")
            hex_str+='A';
        else if(hex_digit=="1011")
            hex_str+='B';
        else if(hex_digit=="1100")
            hex_str+='C';
        else if(hex_digit=="1101")
            hex_str+='D';
        else if(hex_digit=="1110")
            hex_str+='E';
        else if(hex_digit=="1111")
            hex_str+='F';
    }
    return hex_str;
}

int main()
{
    cout << "Ayan Acharya\n21BCT0010" << endl;
    cout<<"Enter Plain Text: ";
    string plain_text="";
    cin>>plain_text;

    cout<<"Enter Original key: ";
    string OG_key;
    cin>>OG_key;

    string key64=convertHextoBin(OG_key);
    string key56=PC1(key64);
    
    vector<string> roundKeyArray=roundKeyArrayGen(key56);
    vector<string> key48Array=PC2(roundKeyArray);

    string pt64=convertHextoBin(plain_text);
    string perm_pt64=IP(pt64);

    string res_str=perm_pt64;
    for(int i=0;i<16;i++)
    {
        string lpt=res_str.substr(0,32);
        string rpt=res_str.substr(32,32);

        string rpt48=EP(rpt);
        string xor48=XOR(rpt48,key48Array[i]);
        string sbox_Output=sBoxComputation(xor48);
        string perm_sbox=P32(sbox_Output);
        string right_res=XOR(perm_sbox,lpt);

        res_str=rpt+right_res;
    }
    string rev64=res_str.substr(32,32)+res_str.substr(0,32);
    string cipher_text=convertBintoHex(FP(rev64));

    cout << "Cipher Text: "<< cipher_text << endl;

    return 0;
}