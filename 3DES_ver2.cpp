#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

// Initial permutiation table (IP)
const int initialPermutationTable[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final permutation table (FP)
const int finalPermutationTable[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Expansion permutation table
const int expansionPermutationTable[48] = {
    32, 1, 2, 3, 4, 5, 4, 5,
    6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1
};

// P-box permutation table
const int pBox[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// S-boxes permutiation table
const int sBox[8][4][16]=  {
    { 
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7}, 
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8}, 
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, 
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} 
    }, 
    { 
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10}, 
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, 
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15}, 
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} 
    }, 
    { 
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8}, 
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1}, 
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7}, 
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    }, 
    { 
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15}, 
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9}, 
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4}, 
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    }, 
    { 
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9}, 
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6}, 
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14}, 
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} 
    }, 
    { 
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11}, 
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8}, 
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6}, 
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} 
    }, 
    { 
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1}, 
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6}, 
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2}, 
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} 
    }, 
    { 
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7}, 
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2}, 
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8}, 
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} 
    }
};

// The PC1 table
const int pc1[56] = {
	57,49,41,33,25,17,9, 
	1,58,50,42,34,26,18, 
	10,2,59,51,43,35,27, 
	19,11,3,60,52,44,36,		 
	63,55,47,39,31,23,15, 
	7,62,54,46,38,30,22, 
	14,6,61,53,45,37,29, 
	21,13,5,28,20,12,4 
};
// The PC2 table
const int pc2[48] = { 
	14,17,11,24,1,5, 
	3,28,15,6,21,10, 
	23,19,12,4,26,8, 
	16,7,27,20,13,2, 
	41,52,31,37,47,55, 
	30,40,51,45,33,48, 
	44,49,39,56,34,53, 
	46,42,50,36,29,32 
}; 

// Decimal to Binary
string convertDecimalToBinary(int decimal)
{
	string binary;
    while(decimal != 0) {
		binary = (decimal % 2 == 0 ? "0" : "1") + binary; 
		decimal = decimal/2;
	}
	while(binary.length() < 4){
		binary = "0" + binary;
	}
    return binary;
}

//Binary to Decimal
int convertBinaryToDecimal(string binary)
{
    int decimal = 0;
	int counter = 0;
	int size = binary.length();
	for(int i = size-1; i >= 0; i--)
	{
    	if(binary[i] == '1'){
        	decimal += pow(2, counter);
    	}
    counter++;
	}
	return decimal;
}

// Circular left shift by 1
string shift_left_once(string key_chunk){ 
    string shifted="";  
        for(int i = 1; i < 28; i++){ 
            shifted += key_chunk[i]; 
        } 
        shifted += key_chunk[0];   
    return shifted; 
} 
// Circular left shift by 2
string shift_left_twice(string key_chunk){ 
    string shifted=""; 
    for(int i = 0; i < 2; i++){ 
        for(int j = 1; j < 28; j++){ 
            shifted += key_chunk[j]; 
        } 
        shifted += key_chunk[0]; 
        key_chunk= shifted; 
        shifted =""; 
    } 
    return key_chunk; 
}
// Compute xor between two strings
string Xor(string a, string b){ 
	string result = ""; 
	int size = b.size();
	for(int i = 0; i < size; i++){ 
		if(a[i] != b[i]){ 
			result += "1"; 
		}
		else{ 
			result += "0"; 
		} 
	} 
	return result; 
} 

// Generate 16 keys for feistel function of each DES
vector<string> keyGens(string key)
{
    vector<string> round_keys;
    string permuted_key = "";
    for(int i = 0; i < 56; i++)
    {
        permuted_key += key[pc1[i] - 1];
    }
    string left = permuted_key.substr(0,28);
    string right = permuted_key.substr(28,28);
    for(int i = 0; i < 16; i++)
    {
        if(i == 0 || i == 1 || i == 8 || i == 15)
        {
            left = shift_left_once(left);
            right = shift_left_once(right);
        }
        else
        {
            left = shift_left_twice(left);
            right = shift_left_twice(right);    
        }
        string combined = left + right;
        string round_key = "";
        for(int i = 0; i < 48; i++)
        {
            round_key += combined[pc2[i] - 1];
        }
        round_keys.push_back(round_key);
    }
    return round_keys;
}

// Reverse keys generated for decryption
vector<string> reverse_key(vector<string> round_keys)
{
    vector<string> reversed;
    int i = 15;
    while(i >= 0)
    {
        reversed.push_back(round_keys[i]);
        i--;
    }
    return reversed;
}

// DES encryption
string DES(string text, vector<string> round_keys)
{
    string perm = "";
    // Initial permutation
    for(int i = 0; i < 64; i++)
    {
        perm += text[initialPermutationTable[i] - 1];
    }
    // Divide text into 2 halves
    string left = perm.substr(0,32);
    string right = perm.substr(32,32);
    // Feistel function
    for(int i = 0; i < 16; i++)
    {
        // Expand the half right to XOR with 48-bit key
        string expanded_right = "";
        for(int i = 0; i < 48; i++)
        {
            expanded_right += right[expansionPermutationTable[i] - 1];
        }
        string xored = Xor(round_keys[i], expanded_right);
        string result = "";
        for(int i = 0; i < 8; i++)
        {
            string row1 = xored.substr(i*6,1) + xored.substr(i*6 + 5,1);
            int row = convertBinaryToDecimal(row1);
            string col1 = xored.substr(i*6 + 1, 4);
            int col = convertBinaryToDecimal(col1);
            int val = sBox[i][row][col];
            result += convertDecimalToBinary(val);
        }
        // Permutation to 32-bit
        string perm2 = "";
        for(int i = 0; i < 32; i++)
        {
            perm2 += result[pBox[i] - 1];
        }
        // XOR with half left
        xored = Xor(perm2, left);
        // Swap the 2 values
        left = xored;
        if(i != 15)
        {
            string temp = right;
            right = xored;
            left = temp;
        }
    }

    // Combine 2 halves into one
    string combined_text = left + right;
    string ciphertext = "";
    // Final permutation
    for(int i = 0; i < 64; i++)
    {
        ciphertext += combined_text[finalPermutationTable[i] - 1];
    } 
    return ciphertext;
}

// Function to perform Triple DES encryption
string tripleDES_encrypt(string plaintext, vector<string> keys[3]) {
    string ciphertext = plaintext;

    // Encrypt with the first key
    ciphertext = DES(ciphertext, keys[0]);

    // Decrypt with the second key
    vector<string> reveresed = reverse_key(keys[1]);
    ciphertext = DES(ciphertext, reveresed);

    // Encrypt with the third key
    ciphertext = DES(ciphertext, keys[2]);

    return ciphertext;
}

// Function to perform Triple DES decryption
string tripleDES_decrypt(string ciphertext, vector<string> keys[3]) {
    string plaintext = ciphertext;

    // Decrypt with the third key
    vector<string> reveresed1 = reverse_key(keys[2]);
    plaintext = DES(plaintext, reveresed1);

    // Encrypt with the second key
    plaintext = DES(plaintext, keys[1]);

    // Decrypt with the first key
    vector<string> reveresed2 = reverse_key(keys[0]);
    plaintext = DES(plaintext, reveresed2);

    return plaintext;
}

int main() {
    // A 64 bit key
    string key1 = "1010101010111011000010010001100000100111001101101100110011011101";
    string key2 = "1101100110001101100110001101100110001101100110001101100110001101";
    string key3 = "1010101010111011000010010001100000100111001101101100110011011101";

    // A block of plain text of 64 bits
    string plaintext = "1010101111001101111001101010101111001101000100110010010100110110";
    string apt = plaintext;

    // Calling the function to generate keys for Triple DES
    vector<string> round_keys1 = keyGens(key1);
    vector<string> round_keys2 = keyGens(key2);
    vector<string> round_keys3 = keyGens(key3);

    vector<string> keys[3] = {round_keys1, round_keys2, round_keys3};

    cout << "Plain text: " << plaintext << endl;

    // Applying Triple DES encryption
    string ct = tripleDES_encrypt(plaintext, keys);
    cout << "Ciphertext: " << ct << endl;

    // Decrypting using Triple DES
    string decrypted = tripleDES_decrypt(ct, keys);
    cout << "Decrypted text: " << decrypted << endl;

    // Comparing the initial plain text with the decrypted text
    if (decrypted == apt) {
        cout << "Plain text encrypted and decrypted successfully." << endl;
    }

    return 0;
}