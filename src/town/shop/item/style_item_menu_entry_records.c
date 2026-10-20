#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AE734_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x14];
    void * unk_20;
    u8 pad_24[0x14];
    void * unk_38;
    u8 pad_3C[0x14];
    void * unk_50;
} S_800AE734_1;

typedef struct S_800AE734_2 {
    u8 pad_00[0x4];
    union { void * s; s8 * u; } unk_04;   /* accessed as both */
} S_800AE734_2;

typedef struct S_800AE734_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AE734_3;

typedef struct S_800AE734_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AE734_4;

typedef struct S_800AE734_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AE734_5;

typedef struct S_800AE734_6 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x5];
    s16 unk_08;
} S_800AE734_6;

typedef struct S_800AE734_7 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AE734_7;

typedef struct S_800AE734_8 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AE734_8;

typedef struct S_800AE734_9 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AE734_9;


typedef struct S_800AE734_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0xAC];
    s32 unk_D8;
} S_800AE734_0;   /* arg0 in style_item_menu_entry_records */

/* Sets fixed values and color bytes on each item's linked records. */
void style_item_menu_entry_records(S_800AE734_0 *collection) {
    s32 entry_offset;
    s32 entry_index;

    entry_index = 0;
    if (collection->unk_28 > 0) {
        do {
            entry_offset = entry_index * 4;
            ((S_800AE734_6 *)(((S_800AE734_2 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_38))->unk_04.s))->unk_08 = 0x20;
            *((S_800AE734_2 *)(((S_800AE734_1 *)((entry_offset + collection->unk_D8)))->unk_38))->unk_04.u = 0x68;
            ((S_800AE734_6 *)(((S_800AE734_2 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_38))->unk_04.s))->unk_01 = 0x68;
            ((S_800AE734_6 *)(((S_800AE734_2 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_38))->unk_04.s))->unk_02 = 0x60;
            ((S_800AE734_7 *)(((S_800AE734_3 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_08))->unk_04))->unk_08 = 9;
            ((S_800AE734_8 *)(((S_800AE734_4 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_20))->unk_04))->unk_08 = 0x39;
            ((S_800AE734_9 *)(((S_800AE734_5 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_50))->unk_04))->unk_08 = 0x8F;
            entry_index += 1;
        } while (entry_index < collection->unk_28);
    }
}
