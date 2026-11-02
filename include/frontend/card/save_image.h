#ifndef FRONTEND_CARD_SAVE_IMAGE_H
#define FRONTEND_CARD_SAVE_IMAGE_H
#include "common.h"
/* 0xC0 file units of 128 bytes. The checksum covers 6014 words after
 * +0x208; the load path also clears the signed halfword at that offset. */
typedef struct CardSaveImage {
    u8 pad_000[0x204];
    s32 checksum;
    union {
        s32 words[6014];
        struct { s16 load_marker; u8 remaining[0x5DF6]; } fields;
    } data;
} CardSaveImage;
#endif
