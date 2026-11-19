#ifndef FRONTEND_CARD_SAVE_SLOT_H
#define FRONTEND_CARD_SAVE_SLOT_H
#include "common.h"
/* Cached save headers use a 128-byte stride. Retail reads words and the
 * halfword at +8; the complete table allocation bound is unestablished. */
typedef union CardSaveSlot {
    s32 words[32];
    s16 halfwords[64];
    u8 bytes[128];
    struct {
        s32 marker; /* zero for a vacant slot; set after copying a cached header */
        u8 pad_04[4];
        s32 unk_08;
        u8 pad_0C[0x10];
        u32 play_frames;
        u8 pad_20[4];
        s32 unk_24;
        u8 pad_28[4];
        s32 unk_2C;
        s32 icon_flags;
        s32 unk_34;
    } fields;
} CardSaveSlot;

/* The devkit card server clears 0x280 bytes and scans five 0x80-byte headers. */
extern CardSaveSlot card_slot_header_cache[5];

extern CardSaveSlot card_save_slot_metadata[];

/* Slot title and detail view at header-cache +12, with the same 128-byte
 * stride. The numeric detail is word 8; the full table bound is unknown. */
extern CardSaveSlot card_slot_detail_records[];

#endif
