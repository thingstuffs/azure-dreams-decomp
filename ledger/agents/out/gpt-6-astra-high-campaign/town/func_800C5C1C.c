#include "common.h"

extern s32 func_80033D38(void *, void *);
extern void func_800C3780(void *arg0, void *arg1, void *arg2);
extern void func_800C37C4(void *arg0, void *arg1, void *arg2);

typedef void (*FuncPtr)(void *, void *, void *);

/* Update the object's flag and dispatch its current state handler. */
void func_800C337C(void *object, void *context, void *dispatch_data) {
    u8 *object_bytes = (u8 *) object;
    u8 state;

    if (func_80033D38(object, context) != 0) {
        object_bytes[0x15] = 1;
    }
    state = object_bytes[0x94];
    if (state == 0) {
        *(u16 *)(object_bytes + 0x72) = *(u16 *)(object_bytes + 0x6E);
        func_800C3780(object, context, dispatch_data);
        return;
    }
    if (state == 1) {
        func_800C37C4(object, context, dispatch_data);
        return;
    }
    (*(FuncPtr *)((((volatile u8 *) object_bytes)[0x94] * 4) + *(s32 *)(object_bytes + 0x58) - 8))(object, context, dispatch_data);
}
