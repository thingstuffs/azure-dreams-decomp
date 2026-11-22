#ifndef FRONTEND_CARD_SAVE_IMAGE_H
#define FRONTEND_CARD_SAVE_IMAGE_H
#include "common.h"
typedef struct CardSaveHeaderPrefix {
    u8 bytes[4];
} CardSaveHeaderPrefix;

typedef struct CardSaveIconPalette {
    u8 bytes[0x20];
} CardSaveIconPalette;

/* 0xC0 file units of 128 bytes. The checksum covers 6014 words after
 * +0x208; the load path also clears the signed halfword at that offset. */
typedef struct CardSaveImage {
    CardSaveHeaderPrefix prefix;
    char title_and_reserved[0x5C]; /* description starts at +4; palette starts at +0x60 */
    CardSaveIconPalette icon_clut;
    u8 icon_frames[3][0x80];
    u8 pad_200[4];
    s32 checksum;
    union {
        s32 words[6014];
        struct { s16 load_marker; u8 remaining[0x5DF6]; } fields;
    } data;
} CardSaveImage;
/* The developer checksum reads four more words than the shipping card file. */
typedef struct CardDevSaveWork {
    struct {
        u8 prefix[4];
        char title_and_reserved[0x1FC];
    } header;
    u8 pad_200[4];
    s32 checksum;
    s32 words[6018];
} CardDevSaveWork;
#endif
