#include "common.h"

#include "common.h"

typedef struct {
    unsigned char pad[0x1e];
    u16 value;
} Func8003C450State;

extern void func_8003C488(void);

// Increase the state value by 0x400, clamping at 0x1000 and advancing the callback when reached.
void func_8003C450(void **callbackSlot, s32 unused, Func8003C450State *state) {
    u32 incrementedValue;

    incrementedValue = state->value;
    incrementedValue += 0x400;
    state->value = incrementedValue;
    if ((incrementedValue & 0xffff) < 0x1000) {
        return;
    }
    state->value = 0x1000;
    *callbackSlot = (void *)func_8003C488;
}
