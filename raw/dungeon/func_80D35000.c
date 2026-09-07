#include "common.h"

typedef long long s64;

#define FIELD(p, type, off) (*(type *)((s8 *)(p) + (off)))

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
static const u32 bank_words[] __asm__("func_80D35000")
    __attribute__((section(".text.func_80D35000"), aligned(4))) = {
    0x8014D190, 0x8014D358, 0x8014DB58, 0x8014DB58,
    0x8014DB58, 0x8014DB84, 0x8014DB04, 0x8014DB04,
    0x8014DB04, 0x8014DAB0, 0x8014DAE8, 0x8014DB84,
    0x8014DB84, 0x8014DB48, 0x00000001, 0x00010001,
    0x00010000, 0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFF0000, 0xFFFF0001, 0x8014F76C, 0x8014F764,
    0x8014F75C, 0x8014F774, 0x8014F71C, 0x8014F714,
    0x8014F70C,
};
__asm__(".globl func_80D35000\n"
        ".size func_80D35000, 720");
#define BODY_NAME func_80D35074
#else
#define BODY_NAME func_80D35000
#endif

void BODY_NAME(void *arg0, void *arg1, void *arg2)
{
    StackWork work;
    s16 count;
    s16 level;
    s32 first;
    s32 value;
    void *other;

    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    FIELD(arg1, s32, 0xC) = FIELD(arg1, s32, 0xC) * 9 / 10;
    FIELD(arg1, s32, 0x10) = FIELD(arg1, s32, 0x10) * 9 / 10;
    FIELD(arg1, s32, 0x14) = FIELD(arg1, s32, 0x14) * 8 / 10;

    if (FIELD(arg2, u16, 0x1C) == 0) {
        FIELD(arg2, u16, 0x1E) = 0x400;
        FIELD(arg2, u16, 0x1C) = 0x400;
    }

    value = FIELD(arg2, u16, 0x1E) + 0x32;
    FIELD(arg2, u16, 0x1E) = value;
    FIELD(arg2, u16, 0x1C) = value;

    work.xyz[0] = FIELD(arg1, u16, 2);
    work.xyz[1] = FIELD(arg1, u16, 6);
    work.xyz[2] = FIELD(arg1, u16, 0xA);
    first = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);

    other = FIELD(arg0, void *, 0xA8);
    work.xyz[0] = FIELD(other, u16, 2);
    work.xyz[1] = FIELD(other, u16, 6);
    work.xyz[2] = FIELD(other, u16, 0xA);
    FIELD(arg2, s16, 6) = first -
        func_80065420(work.xyz, &work.out18, &work.out20, &work.out24) -
        D_800DCECC[((D_80083228 + FIELD(arg0, s16, 0x94) + 0x100) >> 9) & 7] * 2;

    level = FIELD(arg0, s16, 0x96);
    if (level < 10) {
        FIELD(arg2, s16, 0x10) = 0x20;
        FIELD(arg2, u16, 0x12) = 0xFF80;
        FIELD(arg2, u16, 0x14) |= 0xC;
        value = (level << 7) / 10;
        FIELD(arg2, s8, 0xE) = value;
        FIELD(arg2, s8, 0xD) = value;
        FIELD(arg2, s8, 0xC) = value;
    }

    func_800478B8(arg2);
    count = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = count;
    if ((count << 16) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
