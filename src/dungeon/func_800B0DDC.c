#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800B653C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B653C_0;   /* temp_s1 in func_800B653C */

typedef struct S_800B653C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800B653C_1;   /* held_arg0 in func_800B653C */

typedef struct S_800B653C_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800B653C_2;   /* temp_s0 in func_800B653C */



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
extern s32 D_800B63A8;
extern s32 D_800DEA68;

void func_800B653C(void *arg0, u32 arg1) {
    S_800B653C_1 *held_arg0;
    s16 *temp_a0_2;
    s16 *table0;
    u32 index;
    S_800B653C_2 *temp_s0;
    S_800B653C_0 *temp_s1;
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
        temp_v0->unk10 = &D_800B63A8;
        func_8004491C(temp_v0, &D_80045340);
        table0 = D_8006CCD8;
        temp_a0_2 = &D_8006CCE8[index];
        temp_s1->unk_02 =
            (s16)(held_arg0->unk_02 -
                  (table0[index] * 0x10));
        temp_s1->unk_06 =
            (s16)(held_arg0->unk_06 - (*temp_a0_2 * 0x10));
        temp_s1->unk_0A = held_arg0->unk_0A;
        temp_s1->unk_0C =
            0 - (held_arg0->unk_0C * ((rand(temp_a0_2) & 1) + 2));
        temp_s1->unk_10 =
            0 - (held_arg0->unk_10 * ((rand() & 1) + 2));
        temp_s1->unk_14 = (~rand() & 1) << 0xF;
        func_8003DB94(temp_s0, &D_800DEA68, 0);
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        temp_s0->unk_10 = 0x60;
        temp_s0->unk_14 |= 0xC;
        temp_s2->unk18 = 0x10;
        temp_s2->unk16 = 0x10;
        temp_s2->unk14 = 0x10;
        temp_s2->unkE = (rand() & 3) | 4;
        temp_s2->unk8 = 0x800;
    }
}
