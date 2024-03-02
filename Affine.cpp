#include<iostream>
#include<cstdlib>
#include<string.h>

using namespace std;

int a_key[12]     = {1,3,5,7,9,11,15,17,19,21,23,25};
int a_inv_key[12] = {1,9,21,15,3,19,7,23,11,5,17,25};
int error_flag = 0;

int binarySearch(int a[], int l, int h, int target)
{
    if(l > h) return -1;
    int mid = l + (h - l)/2;
    if(a[mid] == target) return mid;
    if(target > a[mid])
    {
        l = mid + 1;
    }
    else
    {
        h = mid - 1;
    }
    return binarySearch(a, l, h, target);
}

string encrypt(string text, int a, int b)
{
    string cipher = "";
    for(int i = 0; i < text.length(); i++)
    {
        if(text[i] != ' ')
        {
            if(text[i] >= 'A' && text[i] <= 'Z')
            {
                cipher += ((a * (text[i] - 'A') + b) % 26) + 'A';
            }
            else if(text[i] >= 'a' && text[i] <= 'z')
            {
                cipher += ((a * (text[i] - 'a') + b) % 26) + 'a';
            }
            else
            {
                cout << "Plain text has unique character, cannot encrypt!";
                cipher = "";
                error_flag = 1;
                break;
            }
        }
        else
        {
            cipher += text[i];
        }
    }
    return cipher;
}
string decrypt(string cipher, int a_inv, int b)
{
    string text = "";
    for(int i = 0; i < cipher.length(); i++)
    {
        if(error_flag == 1)
        {
            break;
        }
        if(cipher[i] != ' ')
        {
            if(cipher[i] >= 'A' && cipher[i] <= 'Z')
            {
                text += (a_inv * (cipher[i] + 'A' - b)) % 26 + 'A';
            }
            else if(cipher[i] >= 'a' && cipher[i] <= 'z')
            {
                text += (26 + (a_inv * (cipher[i] - 'a' - b)) % 26) % 26 + 'a';
            }
            else
            {
                text = "";
                break;
            }
        }
        else
        {
            text += cipher[i];
        }
    }
    return text;
}

int main()
{   
    int a, a_inv, b;
    int choice;
    string plaintext;
    string ciphertext;
    cout << "------------------*Affine cipher*------------------" << endl;
    do
    { 
        cout << "1. Encrypt" << endl;
        cout << "2. Decrypt" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (Must be a number): ";
        cin >> choice;
        if(choice == 1)
        {
            cin.ignore();
            cout << "Enter your message: ";
            getline(cin, plaintext);
            cout << "Enter key pair value!" << endl;
            int index;
            do
            {
                cout << "Enter value for a (Coprime with 26): ";
                cin >> a;
                index = binarySearch(a_key, 0, 11, a);
                if(index == -1)
                {
                    cout << "Invalid a! Re-enter a." << endl;
                }
            } while (index < 0);
            cout << endl;
            do
            {
                cout << "Enter value for b (0 <= b <= 25): ";
                cin >> b;
                if(b <0 || b > 25)
                {
                    cout << "Invalid b! Re-enter b." << endl;
                }
            } while (b < 0 || b > 25);
            
            string cipher = encrypt(plaintext, a, b);
            cout << "Encrypted message: " << cipher << endl << endl;
        }
        else if (choice == 2)
        {
            cout << "Enter key pair value!" << endl;
            int index;
            do
            {
                cout << "Enter value for a (Coprime with 26): ";
                cin >> a;
                index = binarySearch(a_key, 0, 11, a);
                if(index == -1)
                {
                    cout << "Invalid a! Re-enter a." << endl;
                }
                else
                {
                    a_inv = a_inv_key[index];
                }
            } while (index < 0);
            cout << endl;
            do
            {
                cout << "Enter value for b (0 <= b <= 25): ";
                cin >> b;
                if(b <0 || b > 25)
                {
                    cout << "Invalid b! Re-enter b." << endl;
                }
            } while (b < 0 || b > 25);
            cin.ignore();
            cout << "Enter your cipher text: ";
            getline(cin, ciphertext);
            cout << "Key pair value: " << "(" << a << "," << b << ")" << endl;
            string text = decrypt(ciphertext, a_inv, b);
            cout << "Decrypted message: " << text << endl << endl;
        }
        else if (choice  == 3){
            break;
        }
        else
        {
            cout << "Invalid input! Please re-enter your choice." << endl;
        }            
    } while (1);

    return 0;
}