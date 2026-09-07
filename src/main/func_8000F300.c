#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ s8 unk1;
    /* 0x02 */ s8 pad2[2];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s8 pad8[2];
    /* 0x0A */ s8 unkA;
    /* 0x0B */ s8 unkB;
} Struct_8000F300;

void *func_80022300(s32 unused, Struct_8000F300 *arg1, s32 arg2) {
    s32 v0 = 0xA04010;
    u8 v1 = arg1->unk0;
    void *ret;

    arg1->unk1 = 0x28;
    arg1->unkA = (s8)(arg2 * 8 + 4);
    arg1->unkB = 0x13;
    ret = arg1 + 1;
    arg1->unk4 = v0;
    v1 |= 0x80;
    arg1->unk0 = v1;
    return ret;
}
