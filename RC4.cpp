#include <iostream>
#include <vector>
#include <string>

using namespace std;

void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

vector<int> keyGen(vector<int> k, int size)
{
    vector<int> s, T, key;
    s.resize(256);
    T.resize(256);
    for (int i = 0; i < 256; i++)
    {
        s[i] = i;
        T[i] = k[i % k.size()];
    }
    // for(int i = 0; i < 256; i++)
    // {
    //     cout << T[i] << " ";
    // }
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + s[i] + T[i]) % 256;
        swap(s[i], s[j]);
    }
    // for(int i = 0; i < 256; i++)
    // {
    //     cout << s[i] << " ";
    // }
    int a = 0, b = 0;
    int t;
    while (true)
    {
        if (key.size() >= size)
            break;
        a = (a + 1) % 256;
        b = (b + s[a]) % 256;
        swap(s[a], s[b]);
        t = (s[a] + s[b]) % 256;
        key.push_back(s[t]);
    }
    return key;
}

void encrypt(string text, vector<int> seed, int size)
{
    vector<int> key = keyGen(seed, size);
    vector<int> encrypt;
    for (int i = 0; i < size; i++)
    {
        encrypt.push_back((key[i] ^ text[i]) % 256);
    }
    cout << "Text sau khi duoc ma hoa: ";
    for (int i = 0; i < encrypt.size(); i++)
    {
        cout << encrypt[i] << " ";
    }
    cout << endl << endl;
}

void decrypt(string encrypt, vector<int> seed, int size)
{
    vector<int> key = keyGen(seed, size);
    vector<int> decrypt;
    encrypt += ' ';
    int sum = 0;
    for(int i = 0; i < size + 1; i++)
    {
        if(encrypt[i] == ' ')
        {
            decrypt.push_back(sum % 256);
            sum = 0;
            continue;
        }
        sum = sum * 10 + (int(encrypt[i]) - 48);
    }
    // cout << "Dang so: ";
    // for(int i = 0; i < decrypt.size(); i++)
    // {
    //     cout << decrypt[i] << " ";
    // }
    // cout  << endl;
    string text;
    for(int i = 0; i < decrypt.size(); i++)
    {
        char letter;
        letter = ((decrypt[i] ^ key[i]) % 256);
        text += letter;
    }
    cout << "Text sau khi duoc giai ma: " << text << endl;
}

int main()
{
    int choice, n;
    vector<int> seed;
    do
    {
        cout << "----------RC4----------" << endl;
        cout << "1. Encode" << endl;
        cout << "2. Decode" << endl;
        cout << "3. Exit" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;
        if (choice == 1)
        {
            string text;
            cout << "Nhap so phan tu cua seed: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                int temp;
                cout << "Nhap phan tu thu " << i + 1 << " : ";
                cin >> temp;
                seed.push_back(temp);
            }
            cout << "Nhap plaintext: ";
            cin.ignore();
            getline(cin, text);
            string newS;
            for(int i = 0; i < text.length(); i++)
            {
                if(text[i] == ' ') continue;
                newS += text[i];
            }
            cout << newS << endl;
            encrypt(newS, seed, newS.length());
        }
        else if (choice == 2)
        {
            string cipher;
            cout << "Nhap so phan tu cua seed: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                int temp;
                cout << "Nhap phan tu thu " << i + 1 << " : ";
                cin >> temp;
                seed.push_back(temp);
            }
            cout << "Nhap cipher text: ";
            cin.ignore();
            getline(cin, cipher);
            decrypt(cipher, seed, cipher.length());
        }
    } while (choice != 3);

    // vector<int> k = {0, 4, 9, 8, 6};
    // vector<int> key = keyGen(k, 10);
    // for(int i = 0; i < 10; i++)
    // {
    //     cout << key[i] << " ";
    // }
    return 0;
}