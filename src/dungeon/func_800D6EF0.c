#include "common.h"

typedef void (*Func)(void *, s32);
typedef struct {
    u8 pad[0xC];
    s32 value;
} GlobalState;

extern Func D_800E2934[];
extern GlobalState *D_800E5910;

extern void func_800DC628(void *, s32);
extern s32 func_800DCA1C(void *, s32);

/* Moves the current value toward its selected target and updates the object state. */
void func_800DC650(u8 *object_data) {
    u8 *state;
    u32 flags;
    s32 current;
    s32 target;
    s32 delta;
    register u32 mode ASM_REG("$5");
    void *handle;
    s32 result;

    state = object_data + 0x3C;
    flags = *(u32 *)(object_data + 0x50);
    current = *(s16 *)(*(u8 **)(state + 8) + 0xE);
    target = *(s16 *)((u8 *)D_800E2934 + (flags & 2));
    delta = target - current;

    if (delta < 0) {
        current -= 0x80;
        if (delta >= -0x80) {
            goto set_target;
        }
        goto compare;
    } else {
        current += 0x80;
        if (delta >= 0x81) {
            goto compare;
        }
    }

set_target:
    current = target;
compare:
    if (current != target) {
        *(s32 *)(object_data + 0x58) = 1;
        handle = *(void **)(object_data + 0x3C);
        mode = 0;
    } else {
        mode = *(u32 *)(object_data + 0x50);
        handle = *(void **)(object_data + 0x3C);
        mode = ((mode >> 1) ^ 1) % 2;
    }
    result = func_800DCA1C(handle, mode);
    do {
        D_800E5910->value = result;
    } while (0);
    func_800DC628(state, current);
}
