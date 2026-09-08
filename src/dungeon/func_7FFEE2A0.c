#include "common.h"

typedef struct Struct_7FFEE2A0 {
    char pad0[0x64];
    s16 unk64;
    void (*unk68)(void);
    void (*unk6C)(void);
} Struct_7FFEE2A0;

/* Decrements the countdown and activates the next callback when it expires. */
void func_8008BA00(Struct_7FFEE2A0 *state) {
    state->unk64--;
    if (state->unk64 < 0) {
        void (*next_callback)(void) = state->unk6C;
        state->unk68 = next_callback;
        next_callback();
    }
}
