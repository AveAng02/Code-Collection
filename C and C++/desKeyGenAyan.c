#include <stdio.h>
#include <stdlib.h>

// Permutation table for key generation
int PC1[] = {57, 49, 41, 33, 25, 17, 9,
             1, 58, 50, 42, 34, 26, 18,
             10, 2, 59, 51, 43, 35, 27,
             19, 11, 3, 60, 52, 44, 36,
             63, 55, 47, 39, 31, 23, 15,
             7, 62, 54, 46, 38, 30, 22,
             14, 6, 61, 53, 45, 37, 29,
             21, 13, 5, 28, 20, 12, 4};

// Permutation table for key schedule
int PC2[] = {14, 17, 11, 24, 1, 5, 3, 28,
             15, 6, 21, 10, 23, 19, 12, 4,
             26, 8, 16, 7, 27, 20, 13, 2,
             41, 52, 31, 37, 47, 55, 30, 40,
             51, 45, 33, 48, 44, 49, 39, 56,
             34, 53, 46, 42, 50, 36, 29, 32};

// Left shift schedule for key schedule
int left_shifts[] = {1, 1, 2, 2, 2, 2, 2, 2,
                     1, 2, 2, 2, 2, 2, 2, 1};

// Function to perform a circular left shift on a block of bits
void circularLeftShift(int* bits, int shifts, int size) {
    
    int a=size;
    int temp[10000];
    for (int i = 0; i < size; i++) {
        temp[i] = bits[(i + shifts) % size];
    }
    for (int i = 0; i < size; i++) {
        bits[i] = temp[i];
    }
}

// Function to perform key generation
void generateKey(char* key) {
    // Convert the 8-byte key to a 64-bit binary array
    int binaryKey[64];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            binaryKey[i * 8 + j] = (key[i] >> (7 - j)) & 1;
        }
    }

    // Apply the initial permutation (PC1)
    int permutedKey1[56];
    for (int i = 0; i < 56; i++) {
        permutedKey1[i] = binaryKey[PC1[i] - 1];
    }

    // Perform 16 rounds of key schedule generation
    for (int round = 0; round < 16; round++) {
        // Split the key into left and right halves
        int* leftHalf = permutedKey1;
        int* rightHalf = permutedKey1 + 28;

        // Perform circular left shifts on both halves
        circularLeftShift(leftHalf, left_shifts[round], 28);
        circularLeftShift(rightHalf, left_shifts[round], 28);

        // Combine the left and right halves
        for (int i = 0; i < 56; i++) {
            if (i < 28) {
                permutedKey1[i] = leftHalf[i];
            } else {
                permutedKey1[i] = rightHalf[i - 28];
            }
        }

        // Apply the permutation choice 2 (PC2) to obtain the subkey
        int subkey[48];
        for (int i = 0; i < 48; i++) {
            subkey[i] = permutedKey1[PC2[i] - 1];
        }

        // Print the subkey for the current round
        printf("Round %2d subkey: ", round + 1);
        for (int i = 0; i < 48; i++) {
            printf("%d", subkey[i]);
        }
        printf("\n");
    }
}

int main() {

    printf("Ayan Acharya\n21BCT0010\n");

    // Example 8-byte key (64 bits)
    char key[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};

    // Generate the subkeys
    generateKey(key);

    return 0;
}
