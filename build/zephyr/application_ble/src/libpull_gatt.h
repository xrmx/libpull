#ifndef LIBPULL_GATT_H_
#define LIBPULL_GATT_H_

#ifdef __cplusplus
extern "C" {
#endif

enum libpull_state_t {
    STATE_IDLE = 0,
    STATE_DOWNLOADING = 1,
    STATE_DOWNLOADED = 2,
    STATE_UPDATING = 3
};

enum update_result {
    RESULT_INIT = 0,
    RESULT_SUCCESS = 1,
    RESULT_IMAGE_TOO_BIG = 2,
    RESULT_OUT_OF_RAM = 3,
    RESULT_CONNECTION_LOST = 4,
    RESULT_INTEGRITY_CHECK = 5,
    RESULT_UNSUPPORTED_PACKAGE = 6,
    RESULT_INVALID_URI = 7,
    RESULT_UPDATE_FAILED = 8,
    RESULT_UNSUPPORTED_PROTOCOL = 9
};

enum libpull_cmd_t {
    CMD_YIELD,
    CMD_INIT,
};

typedef uint8_t libpull_state_t;
typedef uint8_t libpull_cmd_t;

#define LIBPULL_SERVICE_UUID \
    0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12, \
    0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12

#define LIBPULL_VERSION_UUID \
    0xf1, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x13, \
    0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x13

#define LIBPULL_STATE_UUID \
    0xf2, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x13, \
    0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x13

#define LIBPULL_PACKETS_UUID \
    0xfA, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x13, \
    0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x13

#define LIBPULL_CMD_UUID \
    0xf3, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x13, \
    0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x13

#define LIBPULL_FIRMWARE_UUID \
    0xf4, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x13, \
    0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x13

    void libpull_gatt_init();

#ifdef __cplusplus
}
#endif

#endif /* LIBPULL_GATT_H_ */