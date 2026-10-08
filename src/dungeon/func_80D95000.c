/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_80D95000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80D95000_0;   /* temp_v0 in func_8016A874 */

typedef struct S_80D95000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80D95000_1;   /* var_s0 in func_8016A874 */

typedef struct S_80D95000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80D95000_2;   /* temp_s4 in func_8016A874 */

typedef struct S_80D95000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80D95000_3;   /* temp_s2 in func_8016A874 */

typedef struct S_80D95000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80D95000_4;   /* temp_s5 in func_8016A874 */




void *func_8003FD64();
s32 func_8004491C();
s16 func_800A48F0();
s32 func_800A6D30();
void func_800A9C18();
s32 func_800AA36C();
extern u8 D_8016AA3C[];
extern s32 D_8016AE68;
extern s32 D_8016D86C;

void *func_8016A874(s16 init_flags, s16 x, s16 y, s16 initial_value) ;
/* Allocates an object and initializes its state, placement, and mode. */
void *func_8016A874(s16 init_flags, s16 x, s16 y, s16 initial_value) {
    s32 global_byte;
    s32 unused_slot;
    s32 mode;
    S_80D95000_3 *placement;
    S_80D95000_2 *object_data;
    void *object;
    S_80D95000_4 *extended_state;
    S_80D95000_1 *state = NULL;
    s8 saved_x;
    s8 saved_y;
    s16 saved_value;
    s32 state_flags;
    s32 pending_flags;

    M2C_ERROR(/* Read from unset register $t0 */) | 0x4481;
    saved_x = x;
    saved_value = initial_value;
    saved_y = y;
    global_byte = (s32) *(s8 *)-0x56D4;
    object = func_8003FD64(0x112, ((M2C_UNK *)&D_80083498.next));
    if (object != NULL) {
        state = object + 0x20;
        ((S_80D95000_0 *)object)->unk_10 = &D_8016AA3C;
        state->unk_13 = 0x1A;
        func_8004491C(object, func_80045340);
        object_data = ((S_80D95000_0 *)object)->unk_08;
        object_data->unk_0A = saved_value;
        placement = ((S_80D95000_0 *)object)->unk_0C;
        mode = init_flags & 3;
        placement->unk_25 = saved_y;
        extended_state = state;
        placement->unk_2C = &D_8016D86C;
        placement->unk_24 = saved_x;
        if (mode == 1) {
            state_flags = state->unk_14 | 0x6000;
            pending_flags = state->unk_1C | 0x6000;
            state->unk_14 = state_flags;
            state->unk_1C = pending_flags;
        } else if (mode >= 2) {
            state_flags = state->unk_14 | 0x2000;
            pending_flags = state->unk_1C | 0x2000;
            state->unk_14 = state_flags;
            state->unk_1C = pending_flags;
        } else {
            if (((init_flags & ~3) << 0x10) == 0) {
                if (!(state->unk_14 & 0x200)) {
                    if (func_800A6D30() & 1) {
                        state->unk_1C = (s32) (state->unk_1C | 0x200);
                        func_800A48F0(state, 1, (func_800A6D30() & 0x3F) | 0x20);
                    }
                }
            }
        }
        func_800A9C18(object, object_data, placement, init_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &D_8016AE68;
        func_800AA36C(extended_state, object_data, placement, state);
    }
    return state;
}
