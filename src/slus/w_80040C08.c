#include "common.h"

typedef struct LargeWord
{
    s32 field_0;
    s8 pad[8];
} LargeWord;

typedef struct State
{
    s32 field_0;
    s32 field_4;
    union {
        u8 b;
        u16 h;
    } field_8;
    s8 field_A;
    u8 field_B;
    s8 field_C;
    s8 field_D;
    s8 field_E;
    u8 field_F;
    u8 pad10[8];
    s8 field_18;
} State;

extern LargeWord D_80080A7C;
extern LargeWord D_8008148C;
extern LargeWord D_80081480;
extern State D_80082E60;
extern u8 D_80126804[];

extern void func_800411FC(u16);
extern void func_8003E1FC(void);
extern s32 func_8003E240(s32);
extern void func_80040CBC(s16);

void func_80040C08(void)
{
    State *p = &D_80082E60;
    State *q;
    register s32 old_value ASM_REG("$2");   /* MATCH pin: slus-diff */
    register s32 magic ASM_REG("$4");   /* MATCH pin: slus-diff */
    s32 next;
    u8 state;
    u8 arg;
    u8 flags;

    old_value = D_8008148C.field_0;
    magic = 0x38000;
    state = p->field_B;

    D_80080A7C.field_0 = magic;
    D_80081480.field_0 = old_value;
    if (state != 0) {
        next = 3;
    } else {
        D_8008148C.field_0 = (s32)D_80126804;
        func_800411FC(0);
        func_8003E1FC();
        next = func_8003E240(0);
        if (next != 0) {
            next = 3;
        } else {
            next = 1;
        }
    }
    p->field_B = next;
    q = &D_80082E60;
    arg = q->field_B;
    flags = q->field_F;
    q->field_D = 0;
    q->field_C = 0;
    q->field_18 = 0;
    q->field_F = flags & 0x7E;
    func_80040CBC(arg);
}
