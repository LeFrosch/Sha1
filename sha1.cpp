#include <iostream>
#include <iomanip>

using namespace std;

inline string printh(uint32_t in) 
{
    stringstream s;
    s << hex << in;
    string result(s.str());

    for (int i = result.length(); i < 8; i++) 
    {
        result = "0" + result;
    }

    return result;
}

static uint32_t rol(const uint32_t value, const size_t bits)
{
    return (value << bits) | (value >> (32 - bits));
}

void sha1(string in) 
{
    cout << endl << "Input: " << in << endl << endl;

    uint32_t puffers[5];

    puffers[0] = 0x67452301;
    puffers[1] = 0xefcdab89;
    puffers[2] = 0x98badcfe;
    puffers[3] = 0x10325476;
    puffers[4] = 0xc3d2e1f0;

    cout << "Puffers:" << endl;
    for (int i = 0; i < 5; i++) 
    {
        cout << "   Puffer " << i << ": " << printh(puffers[i]) << endl;
    }

    const char *c_in = in.c_str();
    int size = in.length();

    cout << endl << "Length in bits: " << (size * 8) << endl << endl;

    uint32_t words[80];

    for (int i = 0; i < 80; i++) 
    {
        words[i] = 0;
    }

    for (int i = 0; i < size / 4.0; i++) 
    {
        words[i] = (c_in[4 * i + 3] & 0xff)
                 | (c_in[4 * i + 2] & 0xff) << 8
                 | (c_in[4 * i + 1] & 0xff) << 16
                 | (c_in[4 * i + 0] & 0xff) << 24;
    }
    
    words[size / 4] |= 1 << (31 - (8 * (size % 4)));

    words[15] = size * 8;

    for (int i = 16; i < 80; i++) 
    {
        words[i] = words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16];
        words[i] = rol(words[i], 1);
    }

    cout << "Initial words: " << endl;
    for (int i = 0; i < 80; i++) 
    {
        if (i == 16)
            cout << endl << "Extended words: " << endl;
        cout << "   Word " << (i < 10? "0" + to_string(i) : to_string(i)) << ": " << printh(words[i]) << endl;
    }

    cout << endl << "Main loop:" << endl;

    uint32_t a = puffers[0];
    uint32_t b = puffers[1];
    uint32_t c = puffers[2];
    uint32_t d = puffers[3];
    uint32_t e = puffers[4];

    for (int i = 0; i < 80; i++) 
    {
        uint32_t f;
        uint32_t k;

        if (i < 20) 
        {
            f = (b & c) | ((~b) & d);
            k = 0x5A827999;
        }
        else if (i < 40) 
        {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        }
        else if (i < 60) 
        {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        }
        else 
        {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }

        uint32_t temp = rol(a, 5) + f + e + k + words[i];
        e = d;
        d = c;
        c = rol(b, 30);
        b = a;
        a = temp;

        cout << "[i = " << (i < 10? "0" + to_string(i) : to_string(i)) << "] a: " << printh(a) << " b: " << printh(b) << " c: " << printh(c) << " d: " << printh(d) << " e: " << printh(e) << endl;
    }

    puffers[0] += a;
    puffers[1] += b;
    puffers[2] += c;
    puffers[3] += d;
    puffers[4] += e;

    cout << endl << "Result: " << printh(puffers[0]) << " " << printh(puffers[1]) << " " << printh(puffers[2]) << " " << printh(puffers[3]) << " " << printh(puffers[4]) << endl;
}

main(int argc, char const *argv[])
{
    sha1(argv[1]);
    return 0;
}