#include "sha256.hpp"
#include <cstring>
#include <iomanip>
#include <sstream>
using namespace std;
using namespace NTL;

SHA256::SHA256() {
    uint32_t Hinit[8] = {
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x510e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19
    };
    memcpy(H, Hinit, sizeof(H));
    uint32_t Kinit[64] = {
        0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
        0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
        0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
        0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
        0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
        0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
        0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
        0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
    };
    memcpy(K, Kinit, sizeof(K));
}

void SHA256::update(const string& msg) {
    messageBytes.assign(msg.begin(), msg.end());
}

uint32_t SHA256::ROTR(uint32_t x, uint32_t n) { return (x >> n) | (x << (32-n)); }
uint32_t SHA256::SHR(uint32_t x, uint32_t n) { return x >> n; }
uint32_t SHA256::Ch (uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
uint32_t SHA256::Maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
uint32_t SHA256::Σ0(uint32_t x) { return ROTR(x,2) ^ ROTR(x,13) ^ ROTR(x,22); }
uint32_t SHA256::Σ1(uint32_t x) { return ROTR(x,6) ^ ROTR(x,11) ^ ROTR(x,25); }
uint32_t SHA256::σ0(uint32_t x) { return ROTR(x,7) ^ ROTR(x,18) ^ SHR(x,3); }
uint32_t SHA256::σ1(uint32_t x) { return ROTR(x,17) ^ ROTR(x,19) ^ SHR(x,10); }

void SHA256::transform(const vector<uint8_t>& chunk) {
    uint32_t w[64];

    // 16 words from chunk
    for (int i=0; i<16; i++) {
        w[i] = (chunk[4*i] << 24) | (chunk[4*i+1] << 16) |
               (chunk[4*i+2] << 8) | (chunk[4*i+3]);
    }

    // Extend to 64 words
    for (int i=16; i<64; i++)
        w[i] = σ1(w[i-2]) + w[i-7] + σ0(w[i-15]) + w[i-16];

    uint32_t a=H[0], b=H[1], c=H[2], d=H[3];
    uint32_t e=H[4], f=H[5], g=H[6], h=H[7];

    for (int i=0;i<64;i++) {
        uint32_t T1 = h + Σ1(e) + Ch(e,f,g) + K[i] + w[i];
        uint32_t T2 = Σ0(a) + Maj(a,b,c);
        h = g; g = f; f = e; e = d + T1;
        d = c; c = b; b = a; a = T1 + T2;
    }

    H[0] += a; H[1] += b; H[2] += c; H[3] += d;
    H[4] += e; H[5] += f; H[6] += g; H[7] += h;
}

vector<uint8_t> SHA256::digest() {
    vector<uint8_t> msg = messageBytes;

    uint64_t bitLen = msg.size() * 8;

    msg.push_back(0x80);

    while ((msg.size() % 64) != 56)
        msg.push_back(0x00);

    for (int i=7;i>=0;i--)
        msg.push_back((bitLen >> (8*i)) & 0xFF);

    for (size_t i=0; i<msg.size(); i += 64) {
        vector<uint8_t> chunk(msg.begin()+i, msg.begin()+i+64);
        transform(chunk);
    }

    vector<uint8_t> out(32);
    for (int i=0;i<8;i++) {
        out[4*i]   = (H[i] >> 24) & 0xFF;
        out[4*i+1] = (H[i] >> 16) & 0xFF;
        out[4*i+2] = (H[i] >> 8) & 0xFF;
        out[4*i+3] = H[i] & 0xFF;
    }
    return out;
}

string SHA256::toHex(const vector<uint8_t>& hash) {
    stringstream ss;
    for (uint8_t b : hash)
        ss << hex << setw(2) << setfill('0') << (int)b;
    return ss.str();
}

