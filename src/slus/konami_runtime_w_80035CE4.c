#include "common.h"

#include "common.h"

typedef struct {
    u8 pad00[0x44];
    u8 *data;
    u8 pad48[2];
    s16 offset;
    u8 pad4c[0x1c];
    void (*callback)(void);
} FuncState;

typedef struct {
    u16 pad00;
    u16 value;
} FuncValue;

extern void func_80035D38(void);

/* Decreases value by 0x20, clamps it to 2, and updates the callback and data flag at the lower limit. */
void func_80035CE4(FuncState *state, FuncValue *value_state) {
    u16 value;

    value = value_state->value - 0x20;
    value_state->value = value;
    if ((s16)value < 2) {
        u8 *data;
        s16 offset;

        value_state->value = 2;
        state->callback = func_80035D38;
        data = state->data;
        offset = state->offset;
        *(data + offset + 0x50) = 1;
    }
}
