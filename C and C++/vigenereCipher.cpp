#include <bits/stdc++.h>
using namespace std;

string vigenereEncrypt(const string &plaintext, const string &key)
{
    string ciphertext;

    for (int i = 0, j = 0; i < plaintext.length(); ++i)
    {
        char currentChar = plaintext[i];

        if (isalpha(currentChar))
        {
            char keyChar = isupper(currentChar) ? toupper(key[j % key.length()]) : tolower(key[j % key.length()]);

            char encryptedChar = 'A' + ((currentChar + keyChar - 2 * 'A') % 26);
            if (islower(currentChar))
            {
                encryptedChar = tolower(encryptedChar);
            }

            ciphertext += encryptedChar;
            ++j;
        }
        else
        {
            ciphertext += currentChar;
        }
    }
    return ciphertext;
}

string vigenereDecrypt(const string &ciphertext, const string &key)
{
    string decryptedText;

    for (int i = 0, j = 0; i < ciphertext.length(); ++i)
    {
        char currentChar = ciphertext[i];

        if (isalpha(currentChar))
        {
            char keyChar = isupper(currentChar) ? toupper(key[j % key.length()]) : tolower(key[j % key.length()]);

            char decryptedChar = 'A' + ((currentChar - keyChar + 26) % 26);
            if (islower(currentChar)) {
                decryptedChar = tolower(decryptedChar);
            }

            decryptedText += decryptedChar;
            ++j;
        }
        else
        {
            decryptedText += currentChar;
        }
    }
    return decryptedText;
}

int main()
{
    string plaintext, encryptedString, decryptedString, key;

    cout<<"Enter the Plain Text: ";
    cin>>plaintext;

    cout<<"Enter the Key: ";
    cin>>key;

    encryptedString = vigenereEncrypt(plaintext, key);
    cout<<"Encrypted String: "<<encryptedString<<endl;
    decryptedString = vigenereDecrypt(encryptedString, key);
    cout<<"Decrypted String: "<<decryptedString<<endl;
    return 0;
}
