#include <iostream>
#include <string.h>

using namespace std;

string toUpperLetter(string text)
{
    string newText = "";
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
            continue;
        if (text[i] <= 'z' && text[i] >= 'a')
        {
            newText += text[i] - 32;
        }
        else
        {
            newText += text[i];
        }
    }
    return newText;
}

// int makeEven(string text, int size)
// {
//     if (size % 2 != 0)
//     {
//         text.resize(text.length()+1, text[text.length()]);
//     }
//     return size;
// }

void createMatrix(string key, char matrix[5][5])
{
    int seen[26] = {0};
    string key1 = toUpperLetter(key);
    int a = 0, b = 0;
    for (int i = 0; i < key1.length(); i++)
    {
        if (key1[i] == 'I' || key1[i] == 'J')
        {
            seen['I' - 'A'] = 2;
            seen['J' - 'A'] = 2;
        }
        else
        {
            seen[key1[i] - 'A'] = 2;
        }
    }

    for (int i = 0; i < key1.length(); i++)
    {
        if (seen[key1[i] - 'A'] == 2)
        {
            if (key1[i] == 'I' || key1[i] == 'J')
            {
                matrix[a][b] = 'I';
                seen['I' - 'A'] -= 1;
                seen['J' - 'A'] -= 1;
            }
            else
            {
                matrix[a][b] = key1[i];
                seen[key1[i] - 'A'] -= 1;
            }
            b++;
            if (b == 5)
            {
                b = 0;
                a++;
            }
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (seen[i] == 0)
        {
            if (i + 'A' == 'I' || i + 'A' == 'J')
            {
                matrix[a][b] = 'I';
                seen['I' - 'A'] -= 1;
                seen['J' - 'A'] -= 1;
            }
            else
                matrix[a][b] = (char)(i + 'A');
            b++;
            if (b == 5)
            {
                b = 0;
                a++;
            }
            seen[i] -= 1;
        }
    }
}

void searchMatrix(char matrix[5][5], char a, char b, int arr[4])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (matrix[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            if (matrix[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
    // for(int i = 0; i < 4; i++) cout << arr[i] << " ";
    // cout << endl;
}

string playFairCipher(string text, string key)
{
    string cipher;
    char matrix[5][5];
    text = toUpperLetter(text);
    createMatrix(key, matrix);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << matrix[i][j] << " ";
            if (j == 4)
                cout << endl;
        }
    }
    if (text.length() % 2 != 0)
    {
        text.resize(text.length()+1, text[text.length()]);
    }
    int arr[4] = {0};
    // cout << text.length() << " " << text[text.length()] << endl;
    for (int i = 0; i < text.length(); i += 2)
    {
        // cout << text[i] << " and " << text[i+1] << endl;
        searchMatrix(matrix, text[i], text[i + 1], arr);
        if (text[i + 1] == '\0')
        {
            text[i + 1] = 'X';
        }
        else
        {
            if (arr[0] == arr[2] && arr[1] == arr[3])
            {
                text[i + 1] = 'X';
            }
            else if (arr[0] == arr[2])
            {
                text[i] = matrix[arr[0]][(arr[1] + 1) % 5];
                text[i + 1] = matrix[arr[0]][(arr[3] + 1) % 5];
            }
            else if (arr[1] == arr[3])
            {
                text[i] = matrix[(arr[0] + 1) % 5][arr[1]];
                text[i + 1] = matrix[(arr[2] + 1) % 5][arr[1]];
            }
            else
            {
                text[i] = matrix[arr[0]][arr[3]];
                text[i + 1] = matrix[arr[2]][arr[1]];
            }
        }
    }
    cipher = text;
    return cipher;
}

int main()
{
    string text, key;
    cout << "Enter your text: ";
    getline(cin, text);
    cout << "Enter your key: ";
    getline(cin, key);

    string cipher = playFairCipher(text, key);
    cout << "Cipher text: " << cipher;
    return 0;
}