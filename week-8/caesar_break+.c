///////////////////////////////////////////////////////////
// CSC A48 - Exercise 8 - Breaking Caesar Cipher+ - Winter '22
// Complete where indicated below.
//
// Do not add any additional functions
// and do not leave any print statements
// in your final submission for testing!
//
// (C) F. Estrada, March 2022
//////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 2048

void caesar_cipher(unsigned char plaintext[MAX_STR_LEN], unsigned char password[MAX_STR_LEN]) {
    // This function encodes the input text in plaintext[] using the caesar
    // cipher process with the specified password
    //
    // It's very similar to the program you wrote that used a picture to provide the displacements
    // but in this case instead of a picture we have a simple text password. The way the
    // password is used is that each letter in the password provides the displacement for a
    // letter in the input text. For example:
    //
    // If the input text is:
    //   'This is a sample input'
    // and the password is:
    //   'password'
    // Then the encrypted text is computed as:
    //
    // T + p
    // h + a
    // i + s
    // s + s
    // <space> + w
    // i + o
    // s + r
    // <space> + d
    // a + p
    // <space> + a
    // s + s
    // a + s
    // .
    // .
    // .    and so on. The password repeats until the entire input text is encoded.
    //
    // Same rules apply as before: The end of line delimiter '\0' must not be changed,
    // and no other character should become '\0' after encoding.

    // TO DO:
    // Implement this function (correctly)

    int str_idx = 0, pwd_idx = 0;
    while (plaintext[str_idx] != '\0') {
        int flag = (plaintext[str_idx] + password[pwd_idx]) > 255;
        plaintext[str_idx] += password[pwd_idx] + flag;
        pwd_idx++, str_idx++;
        if (password[pwd_idx] == '\0') pwd_idx = 0;
    }
}

void caesar_decipher(unsigned char cryptotext[MAX_STR_LEN], unsigned char password[MAX_STR_LEN]) {
    // This function reverses the encryption process and returns the original
    // text given the encrypted string and the password used to encrypt it.
    //
    // The function has the same constraints as 'caesar_cipher()', that is, it
    // must respect the 'end-of-string' delimiter, and ensure no other
    // character becomes 'end-of-string' after decoding.

    int str_idx = 0, pwd_idx = 0;
    while (cryptotext[str_idx] != '\0') {
        int flag = (cryptotext[str_idx] - password[pwd_idx]) <= 0;
        cryptotext[str_idx] -= password[pwd_idx] + flag;
        pwd_idx++, str_idx++;
        if (password[pwd_idx] == '\0') pwd_idx = 0;
    }
}

void caesar_breaker(unsigned char crypto_message[MAX_STR_LEN], unsigned char password[MAX_STR_LEN],
                    unsigned char dictionary[10][MAX_STR_LEN]) {
    // This function takes as input
    // - One line of text encrypted using Caesar Cipher+
    //
    // - An array called 'password' that this function will update to contain the password that correctly decodes the
    // text.
    //
    // - A dictionary to be used for a dictionary-attack (here it only has 10 entries, each is a string). Each of these
    // is
    //    a possible word that was used as a password to encode the text. In a real case, this dictionary could contain
    //    thousands of entries, but the actual number of words doesn't matter, the process is the same whether the
    //    dictionary has 10 or 10,000 words.
    //
    // The function determines which is the word in the dictionary that cracks the cipher, and returns it
    // by updating the 'password' string with the correct password.
    //
    // TO DO: Complete this function
    //
    // Constraints: You can assume the input message contains only valid text characters (letters, numbers,
    //              and punctuation signs)
    //              The message is somehow related to A48, it was written by Paco
    //              That's it, you should think about how to use this information to solve your task.
    //              there are many ways to approach this problem, some better than others. Think carefully!

    for (int k = 0; k < 10; k++) {
        int str_idx = 0, pwd_idx = 0;
        int ok = 1;
        while (crypto_message[str_idx] != '\0') {
            int flag = (crypto_message[str_idx] - dictionary[k][pwd_idx]) <= 0;
            unsigned char decrypted_char = crypto_message[str_idx] - dictionary[k][pwd_idx] - flag;

            if ((decrypted_char < 32 || decrypted_char > 126) && decrypted_char != '\n') {
                // we count all printable characters in basic ascii table
                ok = 0;
                break;
            }

            pwd_idx++, str_idx++;
            if (dictionary[k][pwd_idx] == '\0') pwd_idx = 0;
        }
        if (ok) {
            pwd_idx = 0;
            while(dictionary[k][pwd_idx] != '\0') {
                password[pwd_idx] = dictionary[k][pwd_idx];
                pwd_idx++;
            }
            password[pwd_idx] = '\0';
            break;
        }
    }
}

#ifndef __testing

int main() {
    // YOU MUST TEST WITH OTHER INPUTS/DICTIONATIES - I shouldn't have to tell you at this points that the fact your
    // program decodes the text below, doesn't mean your code will work on other inputs and dictionaries. I WILL NOT
    // test your code using the passage below.
    unsigned char a_passage[5][MAX_STR_LEN] = {
        "Hello All, now that we have completed the A48 midterm, we\n",
        "can move on to the last part of the course where we will learn about graphs,\n",
        "and recursion. We will need to apply what we know about complexity, ADTs,\n",
        "binary trees, and the standard operations we do on data collections.\n",
        "Don't forget to complete your readings before class!\n"};

    unsigned char dictionary[10][MAX_STR_LEN] = {"Gerrymandering", "Lamprophony", "Gabelle",   "Bequeath",
                                                 "Jentacular",     "Cabotage",    "Kerfuffle", "Kakorrhaphiophobia",
                                                 "Ulotrichous",    "Erinaceous"};

    unsigned char password[MAX_STR_LEN];

    printf("**** Original input text lines:\n\n");
    for (int i = 0; i < 5; i++) printf("%s", a_passage[i]);

    // Encode the input test lines
    caesar_cipher(a_passage[0], dictionary[2]);
    caesar_cipher(a_passage[1], dictionary[4]);
    caesar_cipher(a_passage[2], dictionary[6]);
    caesar_cipher(a_passage[3], dictionary[8]);
    caesar_cipher(a_passage[4], dictionary[0]);

    printf("\n**** Encrypted text lines:\n\n");
    for (int i = 0; i < 5; i++) printf("%s", a_passage[i]);

    // Crack the passwords for each text line, and use them to decrypt the text
    printf("\n\n***** Decoding message! *****\n\n");
    for (int i = 0; i < 5; i++) {
        memset(&password[0], 0, MAX_STR_LEN * sizeof(unsigned char));  // Clear out password
        caesar_breaker(a_passage[i], password, dictionary);            // Try to get the password for this message
        caesar_decipher(a_passage[i], password);                       // Use the password to decrypt
        // You should check here that your code retrieved the correct password!
        printf("Password=%s, decoded message=%s", password, a_passage[i]);
    }

    return 0;
}

#endif
