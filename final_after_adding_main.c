#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define ROUNDS 16

/* Bit helpers (1-based positions; pos=1 is MSB) */
#define GETBIT64(x,pos) ( ( (x) >> (64 - (pos)) ) & 1ULL )
#define SETBIT64(result,pos,bit) do { \
    if ((bit) & 1ULL) (result) |= (1ULL << (64 - (pos))); \
} while(0)

#define GETBIT32(x,pos) ( ( (x) >> (32 - (pos)) ) & 1U )
#define SETBIT32(result,pos,bit) do { \
    if ((bit) & 1U) (result) |= (1U << (32 - (pos))); \
} while(0)

/* ---------- IP (Initial Permutation) ---------- */
/* input: 64-bit (MSB=pos1), output: 64-bit left-aligned (bits placed into positions 1..64) */
uint64_t IP(uint64_t in) {
    uint64_t out = 0ULL;

    SETBIT64(out, 1,  GETBIT64(in, 58));
    SETBIT64(out, 2,  GETBIT64(in, 50));
    SETBIT64(out, 3,  GETBIT64(in, 42));
    SETBIT64(out, 4,  GETBIT64(in, 34));
    SETBIT64(out, 5,  GETBIT64(in, 26));
    SETBIT64(out, 6,  GETBIT64(in, 18));
    SETBIT64(out, 7,  GETBIT64(in, 10));
    SETBIT64(out, 8,  GETBIT64(in, 2));

    SETBIT64(out, 9,  GETBIT64(in, 60));
    SETBIT64(out,10,  GETBIT64(in, 52));
    SETBIT64(out,11,  GETBIT64(in, 44));
    SETBIT64(out,12,  GETBIT64(in, 36));
    SETBIT64(out,13,  GETBIT64(in, 28));
    SETBIT64(out,14,  GETBIT64(in, 20));
    SETBIT64(out,15,  GETBIT64(in, 12));
    SETBIT64(out,16,  GETBIT64(in, 4));

    SETBIT64(out,17,  GETBIT64(in, 62));
    SETBIT64(out,18,  GETBIT64(in, 54));
    SETBIT64(out,19,  GETBIT64(in, 46));
    SETBIT64(out,20,  GETBIT64(in, 38));
    SETBIT64(out,21,  GETBIT64(in, 30));
    SETBIT64(out,22,  GETBIT64(in, 22));
    SETBIT64(out,23,  GETBIT64(in, 14));
    SETBIT64(out,24,  GETBIT64(in, 6));

    SETBIT64(out,25,  GETBIT64(in, 64));
    SETBIT64(out,26,  GETBIT64(in, 56));
    SETBIT64(out,27,  GETBIT64(in, 48));
    SETBIT64(out,28,  GETBIT64(in, 40));
    SETBIT64(out,29,  GETBIT64(in, 32));
    SETBIT64(out,30,  GETBIT64(in, 24));
    SETBIT64(out,31,  GETBIT64(in, 16));
    SETBIT64(out,32,  GETBIT64(in, 8));

    SETBIT64(out,33,  GETBIT64(in, 57));
    SETBIT64(out,34,  GETBIT64(in, 49));
    SETBIT64(out,35,  GETBIT64(in, 41));
    SETBIT64(out,36,  GETBIT64(in, 33));
    SETBIT64(out,37,  GETBIT64(in, 25));
    SETBIT64(out,38,  GETBIT64(in, 17));
    SETBIT64(out,39,  GETBIT64(in, 9));
    SETBIT64(out,40,  GETBIT64(in, 1));

    SETBIT64(out,41,  GETBIT64(in, 59));
    SETBIT64(out,42,  GETBIT64(in, 51));
    SETBIT64(out,43,  GETBIT64(in, 43));
    SETBIT64(out,44,  GETBIT64(in, 35));
    SETBIT64(out,45,  GETBIT64(in, 27));
    SETBIT64(out,46,  GETBIT64(in, 19));
    SETBIT64(out,47,  GETBIT64(in, 11));
    SETBIT64(out,48,  GETBIT64(in, 3));

    SETBIT64(out,49,  GETBIT64(in, 61));
    SETBIT64(out,50,  GETBIT64(in, 53));
    SETBIT64(out,51,  GETBIT64(in, 45));
    SETBIT64(out,52,  GETBIT64(in, 37));
    SETBIT64(out,53,  GETBIT64(in, 29));
    SETBIT64(out,54,  GETBIT64(in, 21));
    SETBIT64(out,55,  GETBIT64(in, 13));
    SETBIT64(out,56,  GETBIT64(in, 5));

    SETBIT64(out,57,  GETBIT64(in, 63));
    SETBIT64(out,58,  GETBIT64(in, 55));
    SETBIT64(out,59,  GETBIT64(in, 47));
    SETBIT64(out,60,  GETBIT64(in, 39));
    SETBIT64(out,61,  GETBIT64(in, 31));
    SETBIT64(out,62,  GETBIT64(in, 23));
    SETBIT64(out,63,  GETBIT64(in, 15));
    SETBIT64(out,64,  GETBIT64(in, 7));

    return out;
}

/* ---------- FP (Final Permutation) ---------- */
uint64_t FP(uint64_t in) {
    uint64_t out = 0ULL;

    SETBIT64(out, 1, GETBIT64(in, 40));
    SETBIT64(out, 2, GETBIT64(in, 8));
    SETBIT64(out, 3, GETBIT64(in, 48));
    SETBIT64(out, 4, GETBIT64(in, 16));
    SETBIT64(out, 5, GETBIT64(in, 56));
    SETBIT64(out, 6, GETBIT64(in, 24));
    SETBIT64(out, 7, GETBIT64(in, 64));
    SETBIT64(out, 8, GETBIT64(in, 32));

    SETBIT64(out, 9, GETBIT64(in, 39));
    SETBIT64(out,10, GETBIT64(in, 7));
    SETBIT64(out,11, GETBIT64(in, 47));
    SETBIT64(out,12, GETBIT64(in, 15));
    SETBIT64(out,13, GETBIT64(in, 55));
    SETBIT64(out,14, GETBIT64(in, 23));
    SETBIT64(out,15, GETBIT64(in, 63));
    SETBIT64(out,16, GETBIT64(in, 31));

    SETBIT64(out,17, GETBIT64(in, 38));
    SETBIT64(out,18, GETBIT64(in, 6));
    SETBIT64(out,19, GETBIT64(in, 46));
    SETBIT64(out,20, GETBIT64(in, 14));
    SETBIT64(out,21, GETBIT64(in, 54));
    SETBIT64(out,22, GETBIT64(in, 22));
    SETBIT64(out,23, GETBIT64(in, 62));
    SETBIT64(out,24, GETBIT64(in, 30));

    SETBIT64(out,25, GETBIT64(in, 37));
    SETBIT64(out,26, GETBIT64(in, 5));
    SETBIT64(out,27, GETBIT64(in, 45));
    SETBIT64(out,28, GETBIT64(in, 13));
    SETBIT64(out,29, GETBIT64(in, 53));
    SETBIT64(out,30, GETBIT64(in, 21));
    SETBIT64(out,31, GETBIT64(in, 61));
    SETBIT64(out,32, GETBIT64(in, 29));

    SETBIT64(out,33, GETBIT64(in, 36));
    SETBIT64(out,34, GETBIT64(in, 4));
    SETBIT64(out,35, GETBIT64(in, 44));
    SETBIT64(out,36, GETBIT64(in, 12));
    SETBIT64(out,37, GETBIT64(in, 52));
    SETBIT64(out,38, GETBIT64(in, 20));
    SETBIT64(out,39, GETBIT64(in, 60));
    SETBIT64(out,40, GETBIT64(in, 28));

    SETBIT64(out,41, GETBIT64(in, 35));
    SETBIT64(out,42, GETBIT64(in, 3));
    SETBIT64(out,43, GETBIT64(in, 43));
    SETBIT64(out,44, GETBIT64(in, 11));
    SETBIT64(out,45, GETBIT64(in, 51));
    SETBIT64(out,46, GETBIT64(in, 19));
    SETBIT64(out,47, GETBIT64(in, 59));
    SETBIT64(out,48, GETBIT64(in, 27));

    SETBIT64(out,49, GETBIT64(in, 34));
    SETBIT64(out,50, GETBIT64(in, 2));
    SETBIT64(out,51, GETBIT64(in, 42));
    SETBIT64(out,52, GETBIT64(in, 10));
    SETBIT64(out,53, GETBIT64(in, 50));
    SETBIT64(out,54, GETBIT64(in, 18));
    SETBIT64(out,55, GETBIT64(in, 58));
    SETBIT64(out,56, GETBIT64(in, 26));

    SETBIT64(out,57, GETBIT64(in, 33));
    SETBIT64(out,58, GETBIT64(in, 1));
    SETBIT64(out,59, GETBIT64(in, 41));
    SETBIT64(out,60, GETBIT64(in, 9));
    SETBIT64(out,61, GETBIT64(in, 49));
    SETBIT64(out,62, GETBIT64(in, 17));
    SETBIT64(out,63, GETBIT64(in, 57));
    SETBIT64(out,64, GETBIT64(in, 25));

    return out;
}

/* ---------- E-box (32 -> 48) ---------- */

uint64_t E_box(uint32_t R) {
    uint64_t out = 0ULL;

    SETBIT64(out, 1,  GETBIT32(R, 32));
    SETBIT64(out, 2,  GETBIT32(R, 1));
    SETBIT64(out, 3,  GETBIT32(R, 2));
    SETBIT64(out, 4,  GETBIT32(R, 3));
    SETBIT64(out, 5,  GETBIT32(R, 4));
    SETBIT64(out, 6,  GETBIT32(R, 5));

    SETBIT64(out, 7,  GETBIT32(R, 4));
    SETBIT64(out, 8,  GETBIT32(R, 5));
    SETBIT64(out, 9,  GETBIT32(R, 6));
    SETBIT64(out,10,  GETBIT32(R, 7));
    SETBIT64(out,11,  GETBIT32(R, 8));
    SETBIT64(out,12,  GETBIT32(R, 9));

    SETBIT64(out,13,  GETBIT32(R, 8));
    SETBIT64(out,14,  GETBIT32(R, 9));
    SETBIT64(out,15,  GETBIT32(R, 10));
    SETBIT64(out,16,  GETBIT32(R, 11));
    SETBIT64(out,17,  GETBIT32(R, 12));
    SETBIT64(out,18,  GETBIT32(R, 13));

    SETBIT64(out,19,  GETBIT32(R, 12));
    SETBIT64(out,20,  GETBIT32(R, 13));
    SETBIT64(out,21,  GETBIT32(R, 14));
    SETBIT64(out,22,  GETBIT32(R, 15));
    SETBIT64(out,23,  GETBIT32(R, 16));
    SETBIT64(out,24,  GETBIT32(R, 17));

    SETBIT64(out,25,  GETBIT32(R, 16));
    SETBIT64(out,26,  GETBIT32(R, 17));
    SETBIT64(out,27,  GETBIT32(R, 18));
    SETBIT64(out,28,  GETBIT32(R, 19));
    SETBIT64(out,29,  GETBIT32(R, 20));
    SETBIT64(out,30,  GETBIT32(R, 21));

    SETBIT64(out,31,  GETBIT32(R, 20));
    SETBIT64(out,32,  GETBIT32(R, 21));
    SETBIT64(out,33,  GETBIT32(R, 22));
    SETBIT64(out,34,  GETBIT32(R, 23));
    SETBIT64(out,35,  GETBIT32(R, 24));
    SETBIT64(out,36,  GETBIT32(R, 25));

    SETBIT64(out,37,  GETBIT32(R, 24));
    SETBIT64(out,38,  GETBIT32(R, 25));
    SETBIT64(out,39,  GETBIT32(R, 26));
    SETBIT64(out,40,  GETBIT32(R, 27));
    SETBIT64(out,41,  GETBIT32(R, 28));
    SETBIT64(out,42,  GETBIT32(R, 29));

    SETBIT64(out,43,  GETBIT32(R, 28));
    SETBIT64(out,44,  GETBIT32(R, 29));
    SETBIT64(out,45,  GETBIT32(R, 30));
    SETBIT64(out,46,  GETBIT32(R, 31));
    SETBIT64(out,47,  GETBIT32(R, 32));
    SETBIT64(out,48,  GETBIT32(R, 1));

    return out; /* left-aligned: bits occupy positions 1..48 inside the 64-bit word */
}

/* ---------- P-box (32 -> 32) ---------- */
/* input 32-bit (MSB pos1). Output 32-bit (MSB pos1). */
uint32_t P_box(uint32_t in) {
    uint32_t out = 0U;

    SETBIT32(out, 1,  GETBIT32(in, 16));
    SETBIT32(out, 2,  GETBIT32(in, 7));
    SETBIT32(out, 3,  GETBIT32(in, 20));
    SETBIT32(out, 4,  GETBIT32(in, 21));
    SETBIT32(out, 5,  GETBIT32(in, 29));
    SETBIT32(out, 6,  GETBIT32(in, 12));
    SETBIT32(out, 7,  GETBIT32(in, 28));
    SETBIT32(out, 8,  GETBIT32(in, 17));

    SETBIT32(out, 9,  GETBIT32(in, 1));
    SETBIT32(out,10,  GETBIT32(in, 15));
    SETBIT32(out,11,  GETBIT32(in, 23));
    SETBIT32(out,12,  GETBIT32(in, 26));
    SETBIT32(out,13,  GETBIT32(in, 5));
    SETBIT32(out,14,  GETBIT32(in, 18));
    SETBIT32(out,15,  GETBIT32(in, 31));
    SETBIT32(out,16,  GETBIT32(in, 10));

    SETBIT32(out,17,  GETBIT32(in, 2));
    SETBIT32(out,18,  GETBIT32(in, 8));
    SETBIT32(out,19,  GETBIT32(in, 24));
    SETBIT32(out,20,  GETBIT32(in, 14));
    SETBIT32(out,21,  GETBIT32(in, 32));
    SETBIT32(out,22,  GETBIT32(in, 27));
    SETBIT32(out,23,  GETBIT32(in, 3));
    SETBIT32(out,24,  GETBIT32(in, 9));

    SETBIT32(out,25,  GETBIT32(in, 19));
    SETBIT32(out,26,  GETBIT32(in, 13));
    SETBIT32(out,27,  GETBIT32(in, 30));
    SETBIT32(out,28,  GETBIT32(in, 6));
    SETBIT32(out,29,  GETBIT32(in, 22));
    SETBIT32(out,30,  GETBIT32(in, 11));
    SETBIT32(out,31,  GETBIT32(in, 4));
    SETBIT32(out,32,  GETBIT32(in, 25));

    return out;
}

/* ---------- PC1 (64 -> 56) ---------- */
/* returns left-aligned 56-bit (bits placed into positions 1..56) */
uint64_t PC1(uint64_t key) {
    uint64_t out = 0ULL;

    SETBIT64(out,  1, GETBIT64(key, 57));
    SETBIT64(out,  2, GETBIT64(key, 49));
    SETBIT64(out,  3, GETBIT64(key, 41));
    SETBIT64(out,  4, GETBIT64(key, 33));
    SETBIT64(out,  5, GETBIT64(key, 25));
    SETBIT64(out,  6, GETBIT64(key, 17));
    SETBIT64(out,  7, GETBIT64(key, 9));

    SETBIT64(out,  8, GETBIT64(key, 1));
    SETBIT64(out,  9, GETBIT64(key, 58));
    SETBIT64(out, 10, GETBIT64(key, 50));
    SETBIT64(out, 11, GETBIT64(key, 42));
    SETBIT64(out, 12, GETBIT64(key, 34));
    SETBIT64(out, 13, GETBIT64(key, 26));
    SETBIT64(out, 14, GETBIT64(key, 18));

    SETBIT64(out, 15, GETBIT64(key, 10));
    SETBIT64(out, 16, GETBIT64(key, 2));
    SETBIT64(out, 17, GETBIT64(key, 59));
    SETBIT64(out, 18, GETBIT64(key, 51));
    SETBIT64(out, 19, GETBIT64(key, 43));
    SETBIT64(out, 20, GETBIT64(key, 35));
    SETBIT64(out, 21, GETBIT64(key, 27));

    SETBIT64(out, 22, GETBIT64(key, 19));
    SETBIT64(out, 23, GETBIT64(key, 11));
    SETBIT64(out, 24, GETBIT64(key, 3));
    SETBIT64(out, 25, GETBIT64(key, 60));
    SETBIT64(out, 26, GETBIT64(key, 52));
    SETBIT64(out, 27, GETBIT64(key, 44));
    SETBIT64(out, 28, GETBIT64(key, 36));

    SETBIT64(out, 29, GETBIT64(key, 63));
    SETBIT64(out, 30, GETBIT64(key, 55));
    SETBIT64(out, 31, GETBIT64(key, 47));
    SETBIT64(out, 32, GETBIT64(key, 39));
    SETBIT64(out, 33, GETBIT64(key, 31));
    SETBIT64(out, 34, GETBIT64(key, 23));
    SETBIT64(out, 35, GETBIT64(key, 15));

    SETBIT64(out, 36, GETBIT64(key, 7));
    SETBIT64(out, 37, GETBIT64(key, 62));
    SETBIT64(out, 38, GETBIT64(key, 54));
    SETBIT64(out, 39, GETBIT64(key, 46));
    SETBIT64(out, 40, GETBIT64(key, 38));
    SETBIT64(out, 41, GETBIT64(key, 30));
    SETBIT64(out, 42, GETBIT64(key, 22));

    SETBIT64(out, 43, GETBIT64(key, 14));
    SETBIT64(out, 44, GETBIT64(key, 6));
    SETBIT64(out, 45, GETBIT64(key, 61));
    SETBIT64(out, 46, GETBIT64(key, 53));
    SETBIT64(out, 47, GETBIT64(key, 45));
    SETBIT64(out, 48, GETBIT64(key, 37));
    SETBIT64(out, 49, GETBIT64(key, 29));

    SETBIT64(out, 50, GETBIT64(key, 21));
    SETBIT64(out, 51, GETBIT64(key, 13));
    SETBIT64(out, 52, GETBIT64(key, 5));
    SETBIT64(out, 53, GETBIT64(key, 28));
    SETBIT64(out, 54, GETBIT64(key, 20));
    SETBIT64(out, 55, GETBIT64(key, 12));
    SETBIT64(out, 56, GETBIT64(key, 4));

    return out;
}

/* ---------- PC2 (56 -> 48) ---------- */
/* cd56: left-aligned 56-bit input (bits in positions 1..56)
   returns left-aligned 48-bit output (bits in positions 1..48) */
uint64_t PC2(uint64_t cd56) {
    uint64_t out = 0ULL;

    SETBIT64(out,  1, GETBIT64(cd56, 14));
    SETBIT64(out,  2, GETBIT64(cd56, 17));
    SETBIT64(out,  3, GETBIT64(cd56, 11));
    SETBIT64(out,  4, GETBIT64(cd56, 24));
    SETBIT64(out,  5, GETBIT64(cd56, 1));
    SETBIT64(out,  6, GETBIT64(cd56, 5));

    SETBIT64(out,  7, GETBIT64(cd56, 3));
    SETBIT64(out,  8, GETBIT64(cd56, 28));
    SETBIT64(out,  9, GETBIT64(cd56, 15));
    SETBIT64(out, 10, GETBIT64(cd56, 6));
    SETBIT64(out, 11, GETBIT64(cd56, 21));
    SETBIT64(out, 12, GETBIT64(cd56, 10));

    SETBIT64(out, 13, GETBIT64(cd56, 23));
    SETBIT64(out, 14, GETBIT64(cd56, 19));
    SETBIT64(out, 15, GETBIT64(cd56, 12));
    SETBIT64(out, 16, GETBIT64(cd56, 4));
    SETBIT64(out, 17, GETBIT64(cd56, 26));
    SETBIT64(out, 18, GETBIT64(cd56, 8));

    SETBIT64(out, 19, GETBIT64(cd56, 16));
    SETBIT64(out, 20, GETBIT64(cd56, 7));
    SETBIT64(out, 21, GETBIT64(cd56, 27));
    SETBIT64(out, 22, GETBIT64(cd56, 20));
    SETBIT64(out, 23, GETBIT64(cd56, 13));
    SETBIT64(out, 24, GETBIT64(cd56, 2));

    SETBIT64(out, 25, GETBIT64(cd56, 41));
    SETBIT64(out, 26, GETBIT64(cd56, 52));
    SETBIT64(out, 27, GETBIT64(cd56, 31));
    SETBIT64(out, 28, GETBIT64(cd56, 37));
    SETBIT64(out, 29, GETBIT64(cd56, 47));
    SETBIT64(out, 30, GETBIT64(cd56, 55));

    SETBIT64(out, 31, GETBIT64(cd56, 30));
    SETBIT64(out, 32, GETBIT64(cd56, 40));
    SETBIT64(out, 33, GETBIT64(cd56, 51));
    SETBIT64(out, 34, GETBIT64(cd56, 45));
    SETBIT64(out, 35, GETBIT64(cd56, 33));
    SETBIT64(out, 36, GETBIT64(cd56, 48));

    SETBIT64(out, 37, GETBIT64(cd56, 44));
    SETBIT64(out, 38, GETBIT64(cd56, 49));
    SETBIT64(out, 39, GETBIT64(cd56, 39));
    SETBIT64(out, 40, GETBIT64(cd56, 56));
    SETBIT64(out, 41, GETBIT64(cd56, 34));
    SETBIT64(out, 42, GETBIT64(cd56, 53));

    SETBIT64(out, 43, GETBIT64(cd56, 46));
    SETBIT64(out, 44, GETBIT64(cd56, 42));
    SETBIT64(out, 45, GETBIT64(cd56, 50));
    SETBIT64(out, 46, GETBIT64(cd56, 36));
    SETBIT64(out, 47, GETBIT64(cd56, 29));
    SETBIT64(out, 48, GETBIT64(cd56, 32));

    return out;
}

/* ---------- S-Boxes (must store these) ---------- */
static const unsigned char SBOX[64 * 8] = {
    // S1
    14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
    0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
    4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
    15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,

    // S2
    15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,

    // S3
    10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
    13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
    13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
    1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,

    // S4
    7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
    3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,

    // S5
    2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
    4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,

    // S6
    12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
    10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
    9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
    4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,

    // S7
    4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
    1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
    6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,

    // S8
    13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
    1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
    7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
    2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
};

/* ---------- S-box stage: take left-aligned 48-bit input (bits in positions 1..48) ---------- */
/* returns 32-bit value right where MSB corresponds to position1 of 32-bit word (we pack with shifts) */
uint32_t sbox_sub(uint64_t in_left48) {
    uint32_t res = 0U;

    for (int i = 0; i < 8; ++i) {
        /* For i-th S-box, bits occupy positions (1 + i*6) .. (1 + i*6 + 5) inside left-aligned 48-bit */
        int start_pos = 1 + i * 6; // 1..43
        unsigned int six = 0;
        for (int b = 0; b < 6; ++b) {
            six = (six << 1) | (unsigned int)GETBIT64(in_left48, start_pos + b);
        }
        /* bits: b1 b2 b3 b4 b5 b6  where b1 is MSB of the 6
           row = (b1 << 1) | b6
           col = b2..b5
        */
        unsigned int b1 = (six >> 5) & 0x1;
        unsigned int b6 = six & 0x1;
        unsigned int row = (b1 << 1) | b6;
        unsigned int col = (six >> 1) & 0xF;
        unsigned int sidx = (i * 64) + (row * 16) + col;
        unsigned int val = (unsigned int)SBOX[sidx] & 0xF;
        /* place 4-bit val into res: left-to-right -> highest nibble first */
        res |= (val << (28 - 4 * i));
    }
    return res;
}

/* ---------- Round key storage: each key is left-aligned 48-bit in 64-bit container ---------- */
uint64_t keys[ROUNDS];

/* ---------- Key schedule ---------- */
void generate_keys(uint64_t key) {
    // PC1 returns left-aligned 56-bit (positions 1..56). Right-align it for splitting:
    uint64_t k56_left = PC1(key);             // left-aligned (bits 1..56)
    uint64_t k56 = k56_left >> (64 - 56);     // right-aligned 56-bit (low 56 bits)

    uint32_t C = (uint32_t)((k56 >> 28) & 0x0FFFFFFF); // top 28 bits
    uint32_t D = (uint32_t)(k56 & 0x0FFFFFFF);         // low 28 bits

    for (int i = 1; i <= ROUNDS; ++i) {
        int shifts;
        if (i == 1 || i == 2 || i == 9 || i == 16) shifts = 1;
        else shifts = 2;

        // rotate left on 28-bit halves
        C = ((C << shifts) | (C >> (28 - shifts))) & 0x0FFFFFFF;
        D = ((D << shifts) | (D >> (28 - shifts))) & 0x0FFFFFFF;

        // form right-aligned 56-bit CD
        uint64_t CD_right = (((uint64_t)C) << 28) | (uint64_t)D;

        // left-align into 64-bit (positions 1..56)
        uint64_t CD_left = CD_right << (64 - 56);

        // PC2 expects left-aligned 56-bit and returns left-aligned 48-bit key
        keys[i - 1] = PC2(CD_left);
    }
}

/* ---------- single round feistel function using left-aligned keys and left-aligned E-box output ---------- */
uint32_t func(uint32_t r, uint64_t k_left48) {
    uint64_t f0 = E_box(r);         // left-aligned 48-bit
    uint64_t f1 = f0 ^ k_left48;    // left-aligned 48-bit
    uint32_t f2 = sbox_sub(f1);     // 32-bit
    return P_box(f2);               // permutation -> 32-bit
}

/* ---------- Process one 64-bit block (mode 0 encrypt, 1 decrypt) ---------- */
uint64_t processBlock(uint64_t block, int mode) {
    // IP: left-aligned 64-bit
    uint64_t permuted_block = IP(block);

    // extract left (high 32 bits) and right (low 32 bits); these 32-bit words use GETBIT32 semantics (MSB pos1)
    uint32_t left = (uint32_t)((permuted_block >> 32) & 0xFFFFFFFFU);
    uint32_t right = (uint32_t)(permuted_block & 0xFFFFFFFFU);

    for (int i = 0; i < 16; ++i) {
        uint32_t temp = right;
        int subkey_index = (mode == 0) ? i : (15 - i); // 0=encrypt use keys[0..15], 1=decrypt use reversed
        uint32_t f_result = func(right, keys[subkey_index]);
        right = f_result ^ left;
        left = temp;
    }

    // swap before final permutation (standard DES)
    uint64_t preout = (((uint64_t)right) << 32) | (uint64_t)left; // left and right placed back as 64-bit (left in high 32 bits)
    uint64_t final_block = FP(preout);
    return final_block;
}

/* ---------- test main with the canonical DES test vector ---------- */ 




int main(int argc, char **argv)
{
    if (argc != 5) {
        printf("Usage:\n");
        printf("  %s e keyfile plaintext ciphertext\n", argv[0]);
        printf("  %s d keyfile ciphertext plaintext\n", argv[0]);
        return 1;
    }

    //(0 = encrypt, 1 = decrypt)
    int mode;
    if (argv[1][0] == 'e')
        mode = 0;
    else if (argv[1][0] == 'd')
        mode = 1;
    else {
        printf("Invalid mode. Use 'e' for encryption or 'd' for decryption.\n");
        return 1;
    }

    // key
    FILE *fk = fopen(argv[2], "rb");
    if (!fk) {
        printf("Error: cannot open key file.\n");
        return 1;
    }
    uint64_t key;
    if (fread(&key, sizeof(uint64_t), 1, fk) != 1) {
        printf("Error: failed to read key file.\n");
        fclose(fk);
        return 1;
    }
    fclose(fk);

    //generate key
    generate_keys(key);

    // input/output files
    FILE *fin = fopen(argv[3], "rb");
    FILE *fout = fopen(argv[4], "wb");
    if (!fin || !fout) {
        printf("Error: cannot open input/output file.\n");
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return 1;
    }
    uint64_t block_in, block_out;
    size_t n;
    while ((n = fread(&block_in, sizeof(uint64_t), 1, fin)) == 1) {
        block_out = processBlock(block_in, mode);
        fwrite(&block_out, sizeof(uint64_t), 1, fout);
    }

    fclose(fin);
    fclose(fout);

    printf("Operation completed successfully.\n");
    return 0;
}




/*

gcc -O3 final_after_adding_main.c -o final_after_adding_main

./final_after_adding_main.exe e key plaintext ciphertext

./final_after_adding_main.exe d key ciphertext plaintext_out

*/