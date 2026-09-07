#include "common.h"

#ifdef __mips__
/* Proven 31-word literal/pointer prefix; this is row data, not C code. */
static const u32 bank_words[] __asm__("func_8196A800")
    __attribute__((section(".text.func_8196A800"), aligned(4))) = {
    0x80025D68, 0x00000001, 0x00010001, 0x00010000,
    0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
    0xFFFF0001, 0x01400340, 0x00400040, 0x01800340,
    0x00400040, 0x01C00340, 0x00400040, 0x01000380,
    0x00400040, 0x01400380, 0x00400040, 0x01800380,
    0x00400040, 0x01C00380, 0x00400040, 0x01000340,
    0x00400040, 0x00000000, 0x80025E58, 0x80025E90,
    0x80025F18, 0x800262CC, 0x800268F4,
};
__asm__(".globl func_8196A800\n"
        ".type func_8196A800,@function\n"
        ".size func_8196A800,292\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_8196A800")))
#else
#define BODY_NAME func_8196A800
#define BODY_STORAGE
#define BODY_ATTR
#endif

extern s16 D_800269B4;
extern s32 D_800814A0;

BODY_STORAGE void BODY_NAME(void *arg0, void *arg1, void *arg2) BODY_ATTR;

BODY_STORAGE void BODY_NAME(void *arg0, void *arg1, void *arg2) {
    s32 quotient;
    u16 count;

    count = *(u16 *)((u8 *)arg0 + 0x2C) - 1;
    quotient = (s32)((s32)(count << 16) >> 9) /
               (s16)*(u16 *)((u8 *)arg0 + 0x2E);
    D_800269B4 = 1;
    *(u16 *)((u8 *)arg0 + 0x2C) = count;
    *(u8 *)((u8 *)arg2 + 0x0E) += 4;
    *(s8 *)((u8 *)arg2 + 0x0D) = (s8)quotient;
    *(s8 *)((u8 *)arg2 + 0x0C) = (s8)quotient;
    if (*(s16 *)((u8 *)arg2 + 6) >= -6) {
        *(s16 *)((u8 *)arg2 + 6) -= 2;
    }
    if (*(s16 *)((u8 *)arg0 + 0x2C) <= 0) {
        s16 *slot;
        s32 index;
        s32 base;

        index = *(s16 *)((u8 *)arg0 + 0x50) * 2;
        base = *(s32 *)((u8 *)arg0 + 0x7C);
        slot = (s16 *)(index + base + 0x64);
        *slot = 0;
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 = D_800814A0 | 0x8000;
    }
}
