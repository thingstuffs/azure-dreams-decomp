#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

typedef struct {
    u8 pad0[8];
    s32 unk8;
    u8 padC[2];
    s16 unkE;
    u8 pad10[4];
    s16 unk14;
    s16 unk16;
    s16 unk18;
    u8 pad1A[6];
} SubObject;

typedef struct {
    u8 pad0[8];
    void *unk8;
    void *unkC;
    void *unk10;
    u8 pad14[12];
    SubObject sub20;
} Object;

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 func_8003DB94();

extern s32 D_80045340;
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern s32 D_800ABB20;
extern s32 D_800D1464;

void func_800ABC00(void *arg0, u32 arg1)
{
    void *held_arg0;
    s16 *temp_a0_2;
    s16 *table0;
    u32 index;
    void *temp_s0;
    void *temp_s1;
    SubObject *temp_s2;
    Object *temp_v0;

    held_arg0 = arg0;
    arg1 >>= 9;
    index = arg1 & 7;
    temp_v0 = func_8003FC64(0x212, arg1);
    if (temp_v0 != NULL) {
        temp_s1 = temp_v0->unk8;
        temp_s0 = temp_v0->unkC;
        temp_s2 = &temp_v0->sub20;
        temp_v0->unk10 = &D_800ABB20;
        func_8004491C(temp_v0, &D_80045340);
        table0 = D_8006CCD8;
        ASM_USE(table0);
        temp_a0_2 = &D_8006CCE8[index];
        FIELD(temp_s1, s16, 2) =
            (s16)(FIELD(held_arg0, u16, 2) -
                  (table0[index] * 0x10));
        FIELD(temp_s1, s16, 6) =
            (s16)(FIELD(held_arg0, u16, 6) - (*temp_a0_2 * 0x10));
        FIELD(temp_s1, u16, 0xA) = FIELD(held_arg0, u16, 0xA);
        FIELD(temp_s1, s32, 0xC) =
            0 - (FIELD(held_arg0, s32, 0xC) *
                 ((rand(temp_a0_2) & 1) + 2));
        FIELD(temp_s1, s32, 0x10) =
            0 - (FIELD(held_arg0, s32, 0x10) *
                 ((rand() & 1) + 2));
        FIELD(temp_s1, s32, 0x14) = (~rand() & 1) << 0xF;
        func_8003DB94(temp_s0, &D_800D1464, 0);
        ASM_USE(index);
        FIELD(temp_s0, u8, 0xE) = 0x80;
        FIELD(temp_s0, u8, 0xD) = 0x80;
        FIELD(temp_s0, u8, 0xC) = 0x80;
        FIELD(temp_s0, s16, 0x1E) = 0x1000;
        FIELD(temp_s0, s16, 0x1C) = 0x1000;
        FIELD(temp_s0, s16, 0x10) = 0x60;
        FIELD(temp_s0, u16, 0x14) |= 0xC;
        FIELD(temp_s2, s16, 2) = (rand() & 3) | 4;
    }
}
