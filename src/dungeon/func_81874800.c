#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK D_80024004;
extern M2C_UNK D_80024034;
extern M2C_UNK D_800E1C8A;

extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern void func_80099844(void *, void *);
extern s32 func_8009D218(void *, s32);
extern s32 func_800A48F0(void *, s32, s32);
extern void func_800A5720(s32);
extern s32 func_800A6870(s32);
extern void func_80024170(void) __attribute__((noreturn));

#ifdef __mips__
static const u32 prefix_words[] __asm__("func_81874800")
    __attribute__((section(".text.func_81874800"), aligned(4))) = {
    0x800259D8, 0x88827382, 0x92828582, 0x40818582,
    0x81829782, 0x40819382, 0x8F828E82, 0x85824081,
    0x86828682, 0x83828582, 0x40819482, 0x8E828F82,
    0x00004081, 0x00004481, 0x800254CC, 0x80025528,
    0x8002559C, 0x800255FC, 0x8002564C, 0x80025730,
    0x8002575C, 0x800257B4, 0x00000008, 0x00080008,
    0x00080000, 0x0008FFF8, 0x0000FFF8, 0xFFF8FFF8,
    0xFFF80000, 0xFFF80008, 0x80025AD0, 0x80025B50,
    0x80026018, 0x800261D8, 0x8002634C, 0x80026498,
    0x800264B4, 0x8002659C,
};
__asm__(".globl func_81874800\n"
        ".type func_81874800,@function\n"
        ".size func_81874800,392\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_81874800")))
#else
#define BODY_NAME func_81874800
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(void *arg0, s32 arg1) BODY_ATTR;
BODY_STORAGE void BODY_NAME(void *arg0, s32 arg1)
{
    s32 saved;
    s32 value;

    if (func_8009D218(arg0, 2) == 0) {
        if (func_800A48F0(
                arg0, 0x13,
                ((func_800A6870(arg1 & 0xFF) + 4) << 24) >> 24) << 16) {
            if (*(s32 *)((u8 *)arg0 + 0x14) & 0x4000) {
                func_80099844(arg0, &D_800E1C8A);
                func_80024170();
            }
        } else if (*(s32 *)((u8 *)arg0 + 0x14) & 0x4000) {
            value = func_800990FC();
            saved = value;
            value = func_80099194(&D_80024004, value);
            value = func_80099734(arg0, value);
            value = func_80099194(&D_80024034, value);
            func_80099290(value);
            func_800A5720(saved);
        }
    }
}

/* MECHANISM: Preserve the row's byte-backed identity/data bank, then express
 * the executable suffix with the retail call nesting and live-range order. */
