#include "common.h"

typedef struct S_800B1390_0 {
    s32 *unk_m10;
    u8 pad_m0C[0xC];
} S_800B1390_0;

typedef struct S_800B1390_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 unk_20;
    s32 unk_24;
} S_800B1390_1;

extern s32 D_800B0824[];

void func_800B1390(void *record_data, s32 value_20, s32 value_08, s32 value_0c, s32 value_10,
                   s32 value_14, s32 value_24, s32 value_18) {
    S_800B1390_1 *r = record_data;
    r->unk_04 = 1;
    r->unk_08 = value_08;
    r->unk_0C = value_0c;
    r->unk_20 = value_20;
    ((S_800B1390_0 *)r)[-1].unk_m10 = D_800B0824;
    r->unk_10 = value_10;
    r->unk_14 = value_14;
    r->unk_24 = value_24;
    r->unk_18 = value_18;
}
