#ifndef SHA256_HPP
#define SHA256_HPP

#include <vector>
#include <string>
#include <NTL/ZZ.h>

class SHA256 {
public:
    SHA256();
    void update(const std::string& msg);
    std::vector<uint8_t> digest();
    static std::string toHex(const std::vector<uint8_t>&);

private:
    std::vector<uint8_t> messageBytes;

    uint32_t ROTR(uint32_t x, uint32_t n);
    uint32_t SHR(uint32_t x, uint32_t n);
    uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
    uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);
    uint32_t Σ0(uint32_t x);
    uint32_t Σ1(uint32_t x);
    uint32_t σ0(uint32_t x);
    uint32_t σ1(uint32_t x);

    void transform(const std::vector<uint8_t>& chunk);

    uint32_t H[8];
    uint32_t K[64];
};

#endif

