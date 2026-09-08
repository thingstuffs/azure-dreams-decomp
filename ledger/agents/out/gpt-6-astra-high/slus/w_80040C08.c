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

/* Selects the next mode, clears transient state, and dispatches mode setup. */
void func_80040C08(void)
{
    State *state_ptr = &D_80082E60;
    State *reset_state;
    register s32 saved_data_addr ASM_REG("$2");   /* MATCH pin: slus-diff */
    register s32 buffer_size ASM_REG("$4");   /* MATCH pin: slus-diff */
    s32 next_mode;
    u8 current_mode;
    u8 selected_mode;
    u8 flags;

    saved_data_addr = D_8008148C.field_0;
    buffer_size = 0x38000;
    current_mode = state_ptr->field_B;

    D_80080A7C.field_0 = buffer_size;
    D_80081480.field_0 = saved_data_addr;
    if (current_mode != 0) {
        next_mode = 3;
    } else {
        D_8008148C.field_0 = (s32)D_80126804;
        func_800411FC(0);
        func_8003E1FC();
        next_mode = func_8003E240(0);
        if (next_mode != 0) {
            next_mode = 3;
        } else {
            next_mode = 1;
        }
    }
    state_ptr->field_B = next_mode;
    reset_state = &D_80082E60;
    selected_mode = reset_state->field_B;
    flags = reset_state->field_F;
    reset_state->field_D = 0;
    reset_state->field_C = 0;
    reset_state->field_18 = 0;
    reset_state->field_F = flags & 0x7E;
    func_80040CBC(selected_mode);
}
