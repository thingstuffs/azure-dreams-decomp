#include "common.h"

typedef struct {
    u8 pad00[0x14];
    u16 unk14;
} SubEnt;

typedef struct {
    SubEnt *unk00;
    u8 unk04;
} Arg0Ent;

typedef struct {
    u8 pad00[0xC];
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
    u8 pad0F[0x14 - 0xF];
    u16 unk14;
    u8 pad16[0x1C - 0x16];
    u16 unk1C;
    u16 unk1E;
} Arg2Ent;

typedef struct {
    s32 value;
    s32 pad[2];
} LargeS32;

extern LargeS32 D_800814A0;
extern s32 D_800DEDB0[3];

extern void func_800478B8(void *a0);
extern void func_8003DB94(void *a0, void *a1, s16 a2);
extern void func_80024244(void) __attribute__((noreturn));

void func_8186298C(Arg0Ent *arg0, void *arg1, Arg2Ent *arg2)
{
    u16 val;
    u8 b;

    arg0->unk00->unk14++;
    val = arg2->unk1E + 0x400;
    b = arg2->unk0E - 4;
    arg2->unk1E = val;
    arg2->unk1C = val;
    arg2->unk0E = b;
    arg2->unk0D = b;
    arg2->unk0C = b;
    func_800478B8(arg2);

    if (arg2->unk14 & 0x6000) {
        if (arg0->unk04 != 0) {
            *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
            D_800814A0.value |= 0x8000;
            func_80024244();
            return;
        } else {
            __asm__ __volatile__("");
            func_8003DB94(arg2, D_800DEDB0, 4);
            arg0->unk04 = 1;
        }
    }
}
