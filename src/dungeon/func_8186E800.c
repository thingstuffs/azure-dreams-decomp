#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80024154(void) __attribute__((noreturn));
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern void func_80099844(void *, void *);
extern s32 func_8009D218(void *, s32);
extern s32 func_800A48F0(void *, s32, s8);
extern void func_800A5720(s32);
extern s32 func_800A6870(s32);

extern s32 D_80024004;
extern s32 D_80024034;
extern s32 D_800E1C64;

#ifdef __mips__
static const u32 bank_words[] __asm__("func_8186E800")
    __attribute__((section(".text.func_8186E800"), aligned(4))) = {
    0x800248C4, 0x88827382, 0x92828582, 0x40818582,
    0x81829782, 0x40819382, 0x8F828E82, 0x85824081,
    0x86828682, 0x83828582, 0x40819482, 0x8E828F82,
    0x00004081, 0x00004481, 0x00000020, 0x00200020,
    0x00200000, 0x0020FFE0, 0x0000FFE0, 0xFFE0FFE0,
    0xFFE00000, 0xFFE00020, 0x800249B0, 0x80024A30,
    0x80024CD8, 0x80024ED4, 0x80025074, 0x800252D4,
    0x800252D4, 0x800252D4, 0x80025270,
};
__asm__(".globl func_8186E800\n"
        ".type func_8186E800,@function\n"
        ".size func_8186E800,364\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_8186E800")))
#else
#define BODY_NAME func_8186E800
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(void *arg0, s32 arg1) BODY_ATTR;

BODY_STORAGE void BODY_NAME(void *arg0, s32 arg1)
{
    s32 value;
    s32 temp_v0;

    if (func_8009D218(arg0, 1) == 0) {
        if ((func_800A48F0(arg0, 0x12,
                          (s8)(func_800A6870(arg1 & 0xFF) + 2)) << 16) != 0) {
            if (FIELD(arg0, s32, 0x14) & 0x4000) {
                func_80099844(arg0, &D_800E1C64);
                func_80024154();
            }
        } else if (FIELD(arg0, s32, 0x14) & 0x4000) {
            value = func_800990FC();
            temp_v0 = value;
            value = func_80099194(&D_80024004, value);
            value = func_80099734(arg0, value);
            value = func_80099194(&D_80024034, value);
            func_80099290(value);
            func_800A5720(temp_v0);
        }
    }
}
