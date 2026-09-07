#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80024190(void) __attribute__((noreturn));
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
extern s32 D_800E1CB0;

#ifdef __mips__
static const u32 bank_words[] __asm__("func_8187A800")
    __attribute__((section(".text.func_8187A800"), aligned(4))) = {
    0x80025C5C, 0x88827382, 0x92828582, 0x40818582,
    0x81829782, 0x40819382, 0x8F828E82, 0x85824081,
    0x86828682, 0x83828582, 0x40819482, 0x8E828F82,
    0x00004081, 0x00004481, 0x800254FC, 0x80025508,
    0x80025514, 0x80025520, 0x8002552C, 0x8002554C,
    0x80025558, 0x80025570, 0x800255AC, 0x00000000,
    0x80025988, 0x800259C4, 0x80025A00, 0x80025A3C,
    0x80025A78, 0x00000020, 0x00200020, 0x00200000,
    0x0020FFE0, 0x0000FFE0, 0xFFE0FFE0, 0xFFE00000,
    0xFFE00020, 0x00000000, 0x80025D4C, 0x80025DCC,
    0x800260B4, 0x800262A8, 0x800263B0, 0x800264E0,
    0x80026618, 0x8002683C,
};
__asm__(".globl func_8187A800\n"
        ".type func_8187A800,@function\n"
        ".size func_8187A800,424\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_8187A800")))
#else
#define BODY_NAME func_8187A800
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(void *target, s32 effect_arg) BODY_ATTR;

/* Attempts to apply an effect and reports the outcome for flagged targets. */
BODY_STORAGE void BODY_NAME(void *target, s32 effect_arg)
{
    s32 message;
    s32 message_start;

    if (func_8009D218(target, 4) == 0) {
        if ((func_800A48F0(target, 0x14,
                          (s8)(func_800A6870(effect_arg & 0xFF) + 2)) << 16) != 0) {
            if (FIELD(target, s32, 0x14) & 0x4000) {
                func_80099844(target, &D_800E1CB0);
                func_80024190();
            }
        } else if (FIELD(target, s32, 0x14) & 0x4000) {
            message = func_800990FC();
            message_start = message;
            message = func_80099194(&D_80024004, message);
            message = func_80099734(target, message);
            message = func_80099194(&D_80024034, message);
            func_80099290(message);
            func_800A5720(message_start);
        }
    }
}
