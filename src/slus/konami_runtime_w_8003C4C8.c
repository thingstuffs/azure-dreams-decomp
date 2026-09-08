#include "common.h"

#include "common.h"

typedef struct Func8003C4C8State {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    s16 unk_1E;
} Func8003C4C8State;

extern void func_8003C0C0(void *arg0, Func8003C4C8State *arg1);

/* Fades the state to black and clears its active flag when the timer expires. */
void func_8003C4C8(
    s32 *active_flag,
    Func8003C4C8State *unused_state,
    Func8003C4C8State *fade_state
) {
    s32 intensity;
    u16 timer;

    intensity = fade_state->unk_0E - 0x10;
    timer = fade_state->unk_1C - 0x200;
    fade_state->unk_1C = timer;

    if (intensity < 0) {
        intensity = 0;
    }

    fade_state->unk_0E = intensity;
    fade_state->unk_0D = intensity;
    fade_state->unk_0C = intensity;

    if ((s16)fade_state->unk_1C <= 0) {
        fade_state->unk_1E = 0;
        *active_flag = 0;
        func_8003C0C0(active_flag, fade_state);
    }
}
