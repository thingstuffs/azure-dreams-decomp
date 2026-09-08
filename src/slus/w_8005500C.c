#include "common.h"

#include "common.h"

typedef struct S_800847D0 {
    u32 flags1;
    u32 flags2;
    u32 field8;
    u32 fieldC;
    u32 field10;
    u32 field14;
    u32 field18;
    u8 pad1C[2];
    s16 field1E;
    s16 field20;
    s16 field22;
    u8 pad24[2];
    s16 field26;
    u8 field28;
    u8 pad29[7];
    s8 field30;
    s8 field31;
    s8 field32;
    s8 field33;
} S_800847D0;

typedef struct S_800848F8 {
    void (*field0)(void);
    s32 field4;
    s16 field8;
    s16 fieldA;
    s32 fieldC;
    s16 field10;
    s16 field12;
    s16 field14;
    s16 field16;
    s16 field18;
} S_800848F8;

extern S_800847D0 D_800847D0;
extern S_800848F8 D_800848F8;
extern void func_800553D4(s32 a0);
extern void func_800550E8(void);
extern void func_80054F9C(s32 a0, S_800848F8 *a1);

/* Dispatches a packed code by its high nibble or stores it for a state update. */
void func_8005500C(s32 code)
{
    s32 packed_code = code;

    code &= 0xF000;
    if (code == 0x2000) {
        goto set_e1;
    }
    if (code >= 0x2001) {
        goto upper;
    }
    if (code == 0) {
        goto special;
    }
    if (code == 0x1000) {
        goto do_71;
        do { } while (0);
    }
    return;

upper:
    if (code == 0x8000) {
        if (1) {
            goto special;
        }
    }
    if (code > 0x8000) {
        goto high;
    }
    if (code == 0x4000) {
        goto do_f1;
    }
    return;

high:
    if (code != 0x9000) {
        return;
    }

special:
    {
        S_800847D0 *state = &D_800847D0;
        s32 low_byte = packed_code & 0xFF;

        do { } while (0);
        code = packed_code & 0xF000;
        state->field26 = (s16)low_byte;
        if (code != 0) {
            state->field26 = (s16)(low_byte | code);
        }
        if (D_800847D0.flags1 & 0x100) {
            func_80054F9C(0xB1, &D_800848F8);
            return;
            code = packed_code;
        }
    }

    func_800550E8();
    return;

set_e1:
    code = 0xE1;
    goto call;

do_71:
    code = 0x71;
    goto call;

do_f1:
    code = 0xF1;

call:
    func_800553D4(code);
}
