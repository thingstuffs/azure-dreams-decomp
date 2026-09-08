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

/* Mark inactive objects or advance their wrapped 12-bit state value. */
void func_800B9EDC(Obj *obj, void *unused, State *state)
{
    if (*obj->field_98 == 0) {
        func_80033D08(obj);
        *(u16 *)((u8 *)obj - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    state->field_1A += *(s8 *)(obj->field_9C + 0x97);
    state->field_1A &= 0xFFF;
}
