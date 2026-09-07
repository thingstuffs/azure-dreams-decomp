#include "common.h"

typedef struct {
    s8 pad00[0x98];
    u8 *field_98;
    u8 *field_9C;
} Obj;

typedef struct {
    u8 pad00[0x1A];
    volatile u16 field_1A;
} State;

extern s32 D_800814A0[3];
extern void func_80033D08(void *arg0);
extern void func_800B9F60(void);

void func_800B9EDC(Obj *arg0, void *arg1, State *arg2)
{
    if (*arg0->field_98 == 0) {
        func_80033D08(arg0);
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    arg2->field_1A += *(s8 *)(arg0->field_9C + 0x97);
    arg2->field_1A &= 0xFFF;
}
