#include "common.h"

#include "common.h"

typedef struct Func80035AF8State {
    u8 pad00[0x14];
    s16 x;
    s16 y;
    u8 pad18[0x4C];
    u16 counter;
    u8 pad66[2];
    void (*callback)(void *, void *);
    u8 pad6C[8];
    u8 *read_ptr;
    u8 sound_id;
    s8 sound_arg;
} Func80035AF8State;

extern void func_80035BE0(void *arg0);
extern void func_80035C44(void *arg0, void *arg1);
extern s32 func_80035DBC(s32 arg0);
extern void func_8003AC1C(s16 x, s16 y, s32 arg2, s32 arg3);
extern void func_8003AE60(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);
extern void func_8003C2B8(void);
extern s32 func_8003C890(s32 arg0, s32 arg1);
extern u32 *func_8003C8E4(s32 arg0);

/* Display the requested sound and select its next state callback. */
void func_80035AF8(Func80035AF8State *state) {
    u8 sound_id;
    s32 display_value;
    u32 *sound_entry;

    sound_id = state->read_ptr[1];
    if (sound_id == 0) {
        return;
    }
    state->sound_id = sound_id;
    func_8003AE60(state->x, state->y, 0x30, 0x10, 0, 0, 0);
    display_value = (s32)func_80035DBC(state->sound_id);
    func_8003AC1C(state->x, state->y, 1, display_value);
    sound_entry = func_8003C8E4(state->sound_id);
    if (sound_entry != 0) {
        state->sound_arg = ((u8 *)sound_entry)[2];
        if (func_8003C890(state->sound_id, state->sound_arg) != 0) {
            ((u8 *)sound_entry)[2] = ((u8 *)sound_entry)[3];
            func_8003C2B8();
            state->counter = 1;
            state->callback = func_80035BE0;
            return;
        }
    }
    state->callback = func_80035C44;
}
