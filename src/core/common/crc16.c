#include <libpull/common.h>
#include <stdint.h>

uint16_t libpull_crc16(const unsigned char* data, unsigned char length){
    // CRC-CCITT (Initialized with 0xFFFF)
    unsigned char x;
    unsigned short crc = 0xFFFF;

    while (length--){
        x = crc >> 8 ^ *data++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x <<5)) ^ ((unsigned short)x);
    }
    return crc;
}
