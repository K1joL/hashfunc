﻿#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

vector<char> charset()
{
    return vector<char>(
        { '0','1','2','3','4',
        '5','6','7','8','9',
        'a','b','c','d','e','f',
        'g','h','i','j','k',
        'l','m','n','o','p',
        'q','r','s','t','u',
        'v','w','x','y','z'
        });
};

void StrRand(string *Str, int arrSize, int strlen)
{
    const auto ch_set = charset();
    for(int j = 0; j < arrSize; j++)
        for (int i = 0; i < strlen; i++)
            Str[j] += ch_set[rand() % 36];
}

string IntToHex(int64_t num)
{
    int base = 16;
    string res = "";
    for (int i = 0; num > 0; i++)
    {
        int rem = num % base;
        if (num == base)
        {
            res = "10" + res;
            break;
        }
        else
        {
            if (rem > 9)
                res = char('A' + rem - 10) + res;
            else
                res = char(rem + '0') + res;
        }

        num /= base;
    }

    return res;
}

template <typename T>
int Compare(const T* Arr, const int Arr_size)
{
    T Arr2[200]{};
    int k = 0, k1 = 0;
    int flag = 0;
    for (int i = 0; i < Arr_size; i++)
    {
        for (int j = 0; j < Arr_size; j++)
        {
            flag = 0;
            if (i != j && Arr[i] == Arr[j])
            {
                for (k1 = 0; k1 < k; k1++)
                    if (Arr2[k1] == Arr[j])
                        flag = 1;
                if (flag != 1)
                {
                    Arr2[k++] = Arr[j];
                }
            }
        }
    }
    
    return k;
}

uint32_t LojikHash32(string str)
{
    const int p = 19;
    uint64_t HashOut = 0, p_pow = 1;
    while (str.length() != 6)
    {
        int strlen = (int)str.length();
        char add = 0;

        while (!(((add <= 122) && (add >= 97)) || ((add <= 57) && (add >= 48))))
        {
            if (add < 48)
                add += 31 * strlen;
            else
                add -= 37 * strlen;
        }
        str += add;
    }
    for (int i = 0; i < str.length(); i++)
    {
        HashOut += str[i] * p_pow;
        p_pow *= p;
    }
    
    if (!((HashOut >> 31) & 1))
        HashOut |= 1UL << 31;

    return HashOut;
}

int main()
{
    clock_t start = 0, end = 0;
    double seconds = 0;

    srand(time(0));
    const int N = 2000;                                                 //Number of strings/hashs
    int str_size = 6;                                                   //String max length

    for (int str_size_now = 3; str_size_now <= str_size; str_size_now++)
    {
        string* StringArr = new string[N]{ "" };
        int64_t* HashArr = new int64_t[N]{ 0 };

        cout << "String size is " << str_size_now << endl;

        StrRand(StringArr, N, str_size_now);                            // Initialising strings array
        
        
        for (int k = 0; k < N; k++)
        {
            HashArr[k] = LojikHash32(StringArr[k]); 
            //cout << "hash: " << IntToHex(HashArr[k]) << " " << HashArr[k] << endl;
        }

        cout << "Number of collisions: " << Compare(HashArr, N) << endl;

        //Time of compare the hashs
        start = clock();
        Compare(HashArr, N);
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of compare the hash codes: " << seconds << endl;

        //Time of compare the strings
        start = clock();
        Compare(StringArr, N);
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of compare the strings: " << seconds << endl << endl;

        delete[] StringArr;
        delete[] HashArr;
    }

    return 32;
}