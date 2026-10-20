#include "common.h"

#include "common.h"

typedef struct S_8003566C_3 {
    void * unk_00;
} S_8003566C_3;   /* arg0 in scroll_window_x */

typedef struct S_8003566C_4 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8003566C_4;   /* ((S_8003566C_3 *)arg0)->unk_00 in scroll_window_x */


typedef struct S_8003566C_0 {
    void * unk_00;
    u8 pad_04[0x49];
    s8 unk_4D;
    u8 pad_4E[0x1A];
    s32 * unk_68;
    u8 pad_6C[0x8];
    s32 unk_74;
} S_8003566C_0;   /* arg0 in scroll_window_x */

typedef struct S_8003566C_1 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8003566C_1;   /* temp_v0 in scroll_window_x */

typedef struct S_8003566C_2 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8003566C_2;   /* temp_v1 in scroll_window_x */


void create_window_overlay_object(s32 node_addr, void *display, u8 *image, s32 *state_ref, s32 option, u8 *owner);
extern u8 D_8006A86C[];
extern u8 D_80081F78[];
extern u8 D_800822F0[];
void runtime_decrease_state_by_a_0();

/* Decrease the stored value, clamp negatives to zero, and advance state below 0x100. */
void scroll_window_x(S_8003566C_0 *state) {
    S_8003566C_1 *value_data;
    S_8003566C_2 *clamp_data;

    value_data = state->unk_00;
    value_data->unk_08 = (u16) (value_data->unk_08 - 0xA0);
    clamp_data = state->unk_00;
    if ((s16) clamp_data->unk_08 < 0) {
        clamp_data->unk_08 = 0U;
    }
    if ((s16) ((S_8003566C_4 *)(((S_8003566C_3 *)state)->unk_00))->unk_08 < 0x100) {
        create_window_overlay_object(&D_800822F0, &D_80081F78, &D_8006A86C, state, 1, state->unk_74);
        state->unk_4D = 0;
        state->unk_68 = &runtime_decrease_state_by_a_0;
    }
}
