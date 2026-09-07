#include "common.h"

typedef long long s64;

typedef struct S_80D17000_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80D17000_0;   /* arg1 in BODY_NAME */

typedef struct S_80D17000_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80D17000_1;   /* arg2 in BODY_NAME */

typedef struct S_80D17000_2 {
    u8 pad_00[0x94];
    s16 unk_94;
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x10];
    void * unk_A8;
} S_80D17000_2;   /* arg0 in BODY_NAME */

typedef struct S_80D17000_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D17000_3;   /* other in BODY_NAME */



extern void func_800478B8(void *);
extern s32 func_80065420(void *, void *, void *, void *);

extern s32 D_800814A0;
extern s16 D_80083228;
extern s8 D_800DCECC[8];

typedef struct StackWork {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

#ifdef __mips__
static const u32 split_prefix[] __asm__("func_80D17000")
    __attribute__((section(".text.func_80D17000"), aligned(4))) = {
    0x8016B190, 0x8016B358,
    0x8016BB58, 0x8016BB58, 0x8016BB58, 0x8016BB84,
    0x8016BB04, 0x8016BB04, 0x8016BB04,
    0x8016BAB0, 0x8016BAE8,
    0x8016BB84, 0x8016BB84, 0x8016BB48,
    0x00000001, 0x00010001, 0x00010000,
    0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFF0000, 0xFFFF0001,
    0x8016D76C, 0x8016D764, 0x8016D75C, 0x8016D774,
    0x8016D71C, 0x8016D714, 0x8016D70C,
};
__asm__(".globl func_80D17000\n"
        ".size func_80D17000, 720");
#define BODY_NAME func_80D17074
#else
#define BODY_NAME func_80D17000
#endif

void BODY_NAME(void *arg0, void *arg1, void *arg2)
{
    StackWork work;
    s16 count;
    s16 level;
    s32 first;
    s32 value;
    void *other;

    ((S_80D17000_0 *)arg1)->unk_00.at00.v += ((S_80D17000_0 *)arg1)->unk_0C;
    ((S_80D17000_0 *)arg1)->unk_04.at00.v += ((S_80D17000_0 *)arg1)->unk_10;
    ((S_80D17000_0 *)arg1)->unk_08.at00.v += ((S_80D17000_0 *)arg1)->unk_14;
    ((S_80D17000_0 *)arg1)->unk_0C = ((S_80D17000_0 *)arg1)->unk_0C * 9 / 10;
    ((S_80D17000_0 *)arg1)->unk_10 = ((S_80D17000_0 *)arg1)->unk_10 * 9 / 10;
    ((S_80D17000_0 *)arg1)->unk_14 = ((S_80D17000_0 *)arg1)->unk_14 * 8 / 10;

    if (((S_80D17000_1 *)arg2)->unk_1C == 0) {
        ((S_80D17000_1 *)arg2)->unk_1E = 0x400;
        ((S_80D17000_1 *)arg2)->unk_1C = 0x400;
    }

    value = ((S_80D17000_1 *)arg2)->unk_1E + 0x32;
    ((S_80D17000_1 *)arg2)->unk_1E = value;
    ((S_80D17000_1 *)arg2)->unk_1C = value;

    work.xyz[0] = ((S_80D17000_0 *)arg1)->unk_00.at02.v;
    work.xyz[1] = ((S_80D17000_0 *)arg1)->unk_04.at02.v;
    work.xyz[2] = ((S_80D17000_0 *)arg1)->unk_08.at02.v;
    first = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);

    other = ((S_80D17000_2 *)arg0)->unk_A8;
    work.xyz[0] = ((S_80D17000_3 *)other)->unk_02;
    work.xyz[1] = ((S_80D17000_3 *)other)->unk_06;
    work.xyz[2] = ((S_80D17000_3 *)other)->unk_0A;
    ((S_80D17000_1 *)arg2)->unk_06 = first -
        func_80065420(work.xyz, &work.out18, &work.out20, &work.out24) -
        D_800DCECC[((D_80083228 + ((S_80D17000_2 *)arg0)->unk_94 + 0x100) >> 9) & 7] * 2;

    level = ((S_80D17000_2 *)arg0)->unk_96.s;
    if (level < 10) {
        ((S_80D17000_1 *)arg2)->unk_10 = 0x20;
        ((S_80D17000_1 *)arg2)->unk_12 = 0xFF80;
        ((S_80D17000_1 *)arg2)->unk_14 |= 0xC;
        value = (level << 7) / 10;
        ((S_80D17000_1 *)arg2)->unk_0E = value;
        ((S_80D17000_1 *)arg2)->unk_0D = value;
        ((S_80D17000_1 *)arg2)->unk_0C = value;
    }

    func_800478B8(arg2);
    count = ((S_80D17000_2 *)arg0)->unk_96.u - 1;
    ((S_80D17000_2 *)arg0)->unk_96.u = count;
    if ((count << 16) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
