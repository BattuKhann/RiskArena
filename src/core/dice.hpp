#include <cstdint>

struct Xoshiro256 {
    uint64_t s[4];

    static inline uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

    Xoshiro256(uint64_t seed) {
        uint64_t z = seed;
        for (int i = 0; i < 4; ++i) {
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
            z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
            s[i] = z ^ (z >> 31);
        }
    }

    inline uint64_t next() {
        const uint64_t result = rotl(s[1] * 5, 7) * 9;
        const uint64_t t = s[1] << 17;

        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];

        s[2] ^= t;
        s[3] = rotl(s[3], 45);

        return result;
    }
    
    inline uint32_t next_bounded(uint32_t range) {
        uint32_t x = (uint32_t)(next() >> 32);
        uint64_t m = (uint64_t)x * (uint64_t)range;
        return (uint32_t)(m >> 32);
    }
};