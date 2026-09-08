#include "common.h"

/* D_80082E60: global state struct. field_8 is read as a byte (arg to
 * func_80040CBC / copied into field_B), then cleared as a halfword;
 * field_E is cleared as a byte. */
struct S_80082E60 {
    char pad0[8];
    union {
        u8 b;
        u16 h;
    } field_8;
    s8 pad_A;
    s8 field_B;
    s8 field_C;
    s8 field_D;
    s8 field_E;
    char pad_F[0xA];
    s8 field_18;
};

extern struct S_80082E60 D_80082E60;

/* D_80083160: shared state table; four u32 fields at these offsets are
 * cleared here (declared >8 bytes to force %hi/%lo addressing). */
struct S_80083160 {
    char pad0[0xCC];
    u32 field_CC;
    char pad_D0[0x110 - 0xD0];
    u32 field_110;
    char pad_114[0x154 - 0x114];
    u32 field_154;
    char pad_158[0x198 - 0x158];
    u32 field_198;
};

extern struct S_80083160 D_80083160;

extern void func_80040CBC(s16 a0);

/* Saves and processes the state byte, then clears pending state and four shared table fields. */
void func_80040BB4(void)
{
    u8 state_byte = D_80082E60.field_8.b;

    D_80082E60.field_B = state_byte;
    func_80040CBC(state_byte);

    D_80082E60.field_E = 0;
    D_80082E60.field_8.h = 0;

    D_80083160.field_154 = 0;
    D_80083160.field_198 = 0;
    D_80083160.field_CC = 0;
    D_80083160.field_110 = 0;
}
