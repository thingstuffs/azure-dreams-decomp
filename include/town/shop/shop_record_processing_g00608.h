#ifndef TOWN_SHOP_SHOP_RECORD_PROCESSING_G00608_H
#define TOWN_SHOP_SHOP_RECORD_PROCESSING_G00608_H
/* Shop record processing declarations (G00608). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B3110. */

#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B0870_0 {
    u8 unk_00;
    union { s8 s; u8 u; } unk_01;   /* accessed as both */
    u8 unk_02;
    u8 unk_03;
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u8 unk_0A;
    u8 unk_0B;
} S_800B0870_0;

/* arg0 in initialize_shop_display_records */
typedef struct S_800B0870_1 {
    u8 unk_00;
    u8 pad_01[0x1];
    u8 unk_02;
    u8 pad_03[0x1];
    u8 unk_04;
    u8 pad_05[0x1];
    u8 unk_06;
} S_800B0870_1;

extern s32 texture_build_a_hex_48_byte_two_color_swapped_pattern_blocks_returns_base(s32, s32*); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern s32 D_800D15C4;

/* Functions defined in this translation unit. */
void initialize_shop_display_records(void *destination, S_800B0870_1 *source);
void process_shop_record_and_subrecord(s32 record_address);

#endif
