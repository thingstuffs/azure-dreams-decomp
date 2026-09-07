#include "common.h"

typedef struct {
    u8 pad0[8];
    u8 *data;
    u8 padC[0x44];
    s32 *handle;
} Func800B40ACArg;

extern s32 D_80012D5C;
extern u8 D_800D160C[];

#if defined(__mips__) && !defined(NON_MATCHING)
#define READ_D_80012D5C() (*(s32 *)0x80012D5C)
#else
#define READ_D_80012D5C() D_80012D5C
#endif

extern void func_8004E5A0(s32 value, s32 width, u8 *dst);
extern u8 *func_8004E69C(u8 *text);
extern u8 *strcat(u8 *dst, const u8 *src);
extern void func_8004E99C(s32 value);
extern s32 func_8004E298(u8 *data, u8 *text, s32 arg2);

/* Refreshes the display with the formatted global value and its suffix. */
void func_800B180C(Func800B40ACArg *display) {
    u8 text[32];
    func_8004E5A0(READ_D_80012D5C(), 10, text);
    func_8004E69C(text);
    strcat(text, D_800D160C);
    func_8004E99C(*display->handle);
    *display->handle = func_8004E298(display->data + 0x48, text, 0);
}
