#include <iostream>
#include <bitset>

using namespace std;

template <size_t size>
string toHex(bitset<size> in) 
{
    string fix = "";

    for (int i = 0; i < size % 4; i++)
        fix += "0";

    const char *c_fixed = (fix + in.to_string()).c_str();

    int leangth = (fix + in.to_string()).length();

    string result = "";
    for (int i = 0; i < leangth; i += 4) 
    {
        char arr[4];
        arr[0] = c_fixed[i];
        arr[1] = c_fixed[i + 1];
        arr[2] = c_fixed[i + 2];
        arr[3] = c_fixed[i + 3];

        string test = string(arr);

        if (test == "0000") result += "0";
        else if (test == "0001") result += "1";
        else if (test == "0010") result += "2";
        else if (test == "0011") result += "3";
        else if (test == "0100") result += "4";
        else if (test == "0101") result += "5";
        else if (test == "0110") result += "6";
        else if (test == "0111") result += "7";
        else if (test == "1000") result += "8";
        else if (test == "1001") result += "9";
        else if (test == "1010") result += "a";
        else if (test == "1011") result += "b";
        else if (test == "1100") result += "c";
        else if (test == "1101") result += "d";
        else if (test == "1111") result += "e";
    }

    return result;
}

template <size_t size>
inline bitset<size> rotate(bitset<size> &b, unsigned m)
{
    return b << m | b >> (size - m);
}

string sha1(string in) 
{
    cout << "Input: " << in << endl << endl;

    bitset<32> h0("10101001110110101001010101111");
    bitset<32> h1("11011010100001010010101001001");
    bitset<32> h2("10101000100010101010101010101");
    bitset<32> h3("00010100100010101110100101011");
    bitset<32> h4("10010101010010010111010101110");

    cout << "Value h0: " << h0.to_ulong() << endl;
    cout << "Value h1: " << h1.to_ulong() << endl;
    cout << "Value h2: " << h2.to_ulong() << endl;
    cout << "Value h3: " << h3.to_ulong() << endl;
    cout << "Value h4: " << h4.to_ulong() << endl << endl;

    bitset<512> h("");

    const char *c_in = in.c_str();
    for (int i = 0; i < in.length(); i++) 
    {
        bitset<8>d(c_in[i]);

        for (int ii = 0; ii < 8; ii++) 
        {
            h[i * 8 + ii] = d[ii];
        }
    }

    cout << "Input to number: " << h.to_ullong() << endl << endl;

    bitset<32> words[80];

    for (int i = 0; i < 16; i++) 
    {
        for (int ii = 0; ii < 32; ii++)
            words[i][ii] = h[32 * i + ii];
    }

    for (int i = 16; i < 80; i++) 
    {
        words[i] = words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16];
        words[i] = rotate<32>(words[i], 1);
    }

    bitset<32> a(h0);
    bitset<32> b(h0);
    bitset<32> c(h0);
    bitset<32> d(h0);
    bitset<32> e(h0);
    bitset<32> f;
    bitset<32> k;

    for (int i = 0; i < 1; i++) 
    {
        if (i < 20) 
        {
            f = (b & c) | ((~b) & d);
            k = bitset<32>(1518500249);
        }
        else if (i < 40) 
        {
            f = b ^ c ^ d;
            k = bitset<32>(1859775393);
        }
        else if (i < 60) 
        {
            f = (b & c) | (b & d) | (c & d);
            k = bitset<32>(2400959708);
        }
        else 
        {
            f = b ^ c ^ d;
            k = bitset<32>(3395469782);
        }

        bitset<32> temp(rotate<32>(a, 5).to_ullong() + f.to_ullong() + e.to_ullong() + k.to_ullong() + words[i].to_ullong());
        e = d;
        d = c;
        c = rotate<32>(b, 30);
        b = a;
        a = temp;
    }

    h0 = a;
    h1 = b;
    h2 = c;
    h3 = d; 
    h4 = e;

    bitset<160> result(h0.to_string() + h1.to_string() + h2.to_string() + h3.to_string() + h4.to_string());

    return toHex(result);
}

main(int argc, char const *argv[])
{
    string result = sha1("Lola");
    cout << "Result: " << result << endl;

    return 0;
}