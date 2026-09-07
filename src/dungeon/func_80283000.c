#include "common.h"

typedef struct {
    u8 pad_00[0x19];
    s8 red;
    s8 green;
    s8 blue;
} ColorState;

extern void func_80064624(s32, s32);
extern void func_80064D20(void *);
extern void func_80064D50(void *);
extern void func_80064EC0(s32, s32, s32);
extern void func_80064EE0(s32, s32, s32);
extern void func_80064F00(s32, s32);
extern void func_80064F20(s32);

extern u8 D_80083160[];
extern u8 *D_80083478;
extern u8 D_800DDC7C;
extern ColorState D_801C9E40;
extern ColorState D_801DA714;

#ifdef __mips__
void func_80016000(void);
static const u32 split_prefix[] __asm__("func_80016000")
    __attribute__((section(".text.func_80016000"), aligned(4))) = {
        0x8001D4FC, 0x8001D508, 0x8001D540, 0x8001D5C0, 0x8001D578,
        0x8001D5B0, 0x8001D5B0, 0x8001D5B0, 0x8001D5B0,
        0x8001D5B0, 0x8001D5B0, 0x8001D5B0, 0x8001D5B0,
        0x8001E944, 0x8001E944, 0x8001E944, 0x8001E87C,
        0x8001E944, 0x8001E944, 0x8001E944, 0x8001E944,
        0x8001E944, 0x8001E944, 0x8001E944, 0x8001E944,
        0x8001E944, 0x8001E944, 0x8001E8A4, 0x8001E8E8,
        0x8001E8B8, 0x8001E910,
    };
__asm__(".globl func_80016000\n"
        ".size func_80016000, 472");
#define BODY_NAME func_8001607C
#else
#define BODY_NAME func_80016000
#endif

void BODY_NAME(void) {
    u8 *base;
    u8 *state;
    s32 scale;
    void *call_arg;
    s32 negative;
    s32 positive;

    base = D_80083160;
    state = base + 0x18;
    scale = 0x200;
    *(s32 *)(state + 0x88) = scale;
    func_80064F20(scale);
    *(s32 *)(state + 0x78) = 0;
    *(s32 *)(state + 0x7C) = 0;
    *(s32 *)(state + 0x80) = 0;
    func_80064EE0(0, 0, 0);
    *(s16 *)(state + 0x58) = scale;
    *(s16 *)(state + 0x5E) = scale;
    *(s16 *)(state + 0x64) = scale;
    *(s16 *)(state + 0x5A) = -0x100;
    *(s16 *)(state + 0x60) = -0x100;
    *(s16 *)(state + 0x66) = -0x100;
    *(s16 *)(state + 0x5C) = 0;
    *(s16 *)(state + 0x62) = 0;
    *(s16 *)(state + 0x68) = 0;
    func_80064D50(base + 0x70);

    call_arg = base + 0x50;
    ASM_KEEP_NV(call_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
    negative = -0x800;
    positive = 0x800;
    *(s16 *)(state + 0x38) = negative;
    *(s16 *)(state + 0x3C) = negative;
    ASM_KEEP_NV(positive);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    negative = 0x800;
    *(s16 *)(state + 0x3A) = positive;
    positive = -0x800;
    *(s16 *)(state + 0x3E) = negative;
    *(s16 *)(state + 0x40) = positive;
    *(s16 *)(state + 0x42) = negative;
    *(s16 *)(state + 0x44) = 0;
    *(s16 *)(state + 0x46) = 0;
    *(s16 *)(state + 0x48) = 0;
    func_80064D20(call_arg);

    *(s32 *)(state + 0x84) = 0x1000;
    func_80064624(0x1000, *(s32 *)(state + 0x88));
    func_80064EC0(0xA0, 0xA0, 0xA0);
    D_801C9E40.red = 0;
    D_801C9E40.green = 0;
    D_801C9E40.blue = 0;
    D_801DA714.red = 0;
    D_801DA714.green = 0;
    D_801DA714.blue = 0;
    func_80064F00(0xA0, 0x78);
    *(s16 *)(base + 0x18) = -0xBC;
    *(s16 *)(base + 0x1A) = -0x88;
    *(s16 *)(base + 0x1C) = 0x172;
    *(s16 *)(base + 0x1E) = 0x19A;
    D_80083478 = &D_800DDC7C;
}
