
#include <stdio.h>
#include <stdlib.h>


int binaryData[64] = {
    0, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 1, 0, 1, 0,
    0, 0, 1, 1, 0, 0, 1, 1,
    1, 1, 0, 0, 1, 1, 0, 0,
    0, 1, 1, 0, 0, 1, 1, 0,
    1, 1, 0, 0, 1, 1, 0, 0,
    0, 1, 1, 0, 1, 0, 1, 0,
    0, 1, 0, 1, 0, 1, 0, 1
};


int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9, 1,
    58, 50, 42, 34, 26, 18, 10, 2,
    59, 51, 43, 35, 27, 19, 11, 3,
    60, 52, 44, 36, 63, 55, 47, 39,
    31, 23, 15, 7, 62, 54, 46, 38,
    30, 22, 14, 6, 61, 53, 45, 37,
    29, 21, 13, 5, 28, 20, 12, 4
};


int PC2[48] = {
    14, 17, 11, 24, 1, 5, 3, 28, 
    15, 6, 21, 10, 23, 19, 12, 4, 
    26, 8, 16, 7, 27, 20, 13, 2, 
    41, 52, 31, 37, 47, 55, 30, 40, 
    51, 45, 33, 48, 44, 49, 39, 56, 
    34, 53, 46, 42, 50, 36, 29, 32
};


int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 
    64, 56, 48, 40, 32, 24, 16, 8, 
    57, 49, 41, 33, 25, 17, 9, 1, 
    59, 51, 43, 35, 27, 19, 11, 3, 
    61, 53, 45, 37, 29, 21, 13, 5, 
    63, 55, 47, 39, 31, 23, 15, 7
};


void leftShiftBlock(int* cN, int* cNplusOne, int shift) {

    // can be optimized with memcpy

    for(int i = 0; i < 28 - shift; i++) {
        cNplusOne[i] = cN[i + shift];
    }

    if(shift == 1)
    {
        cNplusOne[27] = cN[0];
    }

    if(shift == 2)
    {
        cNplusOne[26] = cN[0];
        cNplusOne[27] = cN[1];
    }

}

void desEncryption(int givenMsg[64], int encryptedMsg[64]) {

    int kPlus[56];
    int c[17][28];
    int d[17][28];
    int cd[16][56];
    int k[16][56];

    for(int i = 0; i < 56; i++) {
        kPlus[i] = binaryData[PC1[i]];
    }

    // can be replaced with memcpy
    for(int i = 0; i < 28; i++) {
        c[0][i] = kPlus[i];      // loading first 28 bits 
        d[0][i] = kPlus[i + 28]; // loading next set of 28 bits
    }

    // left shyfting the c blocks
    leftShiftBlock(c[0], c[1], 1); // left shift by 1
    leftShiftBlock(c[1], c[2], 1); // left shift by 1
    
    for(int i = 3; i < 9; i++) {   // shifting left by 2 places from 3 to 8
        leftShiftBlock(c[i - 1], c[i], 2);
    }

    leftShiftBlock(c[8], c[9], 1); // left shift by 1

    for(int i = 10; i < 16; i++) {   // shifting left by 2 places from 10 to 16
        leftShiftBlock(c[i - 1], c[i], 2);
    }

    leftShiftBlock(c[15], c[16], 1); // left shift by 1


    // left shyfting the d blocks
    leftShiftBlock(d[0], d[1], 1); // left shift by 1
    leftShiftBlock(d[1], d[2], 1); // left shift by 1
    
    for(int i = 3; i < 9; i++) {   // shifting left by 2 places from 3 to 8
        leftShiftBlock(d[i - 1], d[i], 2);
    }

    leftShiftBlock(d[8], d[9], 1); // left shift by 1

    for(int i = 10; i < 16; i++) {   // shifting left by 2 places from 10 to 16
        leftShiftBlock(d[i - 1], d[i], 2);
    }

    leftShiftBlock(d[15], d[16], 1); // left shift by 1


    // Generating the subkeys
    for(int j = 0, i = 0; i < 16; i++) {
        for(j = 0; j < 28; j++) {
            cd[i][j] = c[i][j];
        }
    }

    for(int j = 0, i = 0; i < 16; i++) {
        for(j = 28; j < 56; j++) {
            cd[i][j] = d[i][j - 28];
        }
    }

    for(int j = 0, i = 0; i < 16; i++) {
        for(j = 0; j < 48; j++) {
            k[i][j] = cd[i][PC2[j]];
        }
    }


    // Getting permutation of message
    int ipPermute[64];

    for(int i = 0; i < 64; i++) {
        ipPermute[i] = givenMsg[IP[i]];
    }

    


}


int main() {

    int permutationArray[28] = {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 
                                0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1};

    int* newArray = malloc(sizeof(int) * 28);

    printf(" \n 1 space shift \n ");

    for(int i = 0; i < 28; i++) {
        
        printf(" %d ", permutationArray[i]);
    }

    printf(" \n ");

    leftShiftBlock(permutationArray, newArray, 1);

    for(int i = 0; i < 28; i++) {
        
        printf(" %d ", newArray[i]);
    }

    printf(" \n ");

    printf(" \n 2 space shift \n ");

    for(int i = 0; i < 28; i++) {
        
        printf(" %d ", permutationArray[i]);
    }

    printf(" \n ");

    leftShiftBlock(permutationArray, newArray, 2);

    for(int i = 0; i < 28; i++) {
        
        printf(" %d ", newArray[i]);
    }

    printf(" \n ");

    int givenStr[64];
    int encryptedStr[64];

    desEncryption(givenStr, encryptedStr);

    return 0;
}


