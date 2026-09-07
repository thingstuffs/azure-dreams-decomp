#include "common.h"


extern u8 D_80083498[];
extern u8 D_80045340[];
extern s32 D_80158A58;
extern s32 D_80159014;
extern s32 D_8015C20C;
extern s32 D_8015C25C;

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();


typedef struct S_80158878_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_80158878_0;   /* temp_v0 in func_80158878 */

typedef struct S_80158878_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80158878_1;   /* var_s0 in func_80158878 */

typedef struct S_80158878_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80158878_2;   /* temp_s4 in func_80158878 */

typedef struct S_80158878_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    s32 * unk_2C;
} S_80158878_3;   /* temp_s2 in func_80158878 */

typedef struct S_80158878_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80158878_4;   /* temp_s5 in func_80158878 */

/* Allocates an object and initializes its state and attached data. */
void *func_80158878(s16 init_flags, s8 pos_x, s8 pos_y, s16 init_value)
{
    s32 init_mode;
    s32 state_flags;
    s32 update_flags;
    S_80158878_3 *placement_data;
    S_80158878_2 *config_data;
    void *object;
    S_80158878_4 *extended_state;
    S_80158878_1 *state;
    register s8 saved_x ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s16 saved_value;
    register s8 saved_y ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */

    state = 0;
    saved_x = pos_x;
    saved_value = init_value;
    saved_y = pos_y;
    object = func_8003FD64(0x112, D_80083498);
    if (object == 0) {
        goto done;
    }
    state = object + 0x20;
    ((S_80158878_0 *)object)->unk_10 = &D_80158A58;
    state->unk_13 = 0x10;
    func_8004491C(object, D_80045340);
    config_data = ((S_80158878_0 *)object)->unk_08;
    config_data->unk_0A = saved_value;
    placement_data = ((S_80158878_0 *)object)->unk_0C;
    init_mode = init_flags & 3;
    placement_data->unk_25 = saved_y;
    extended_state = state;
    placement_data->unk_2C = &D_8015C20C;
    placement_data->unk_24 = saved_x;
    if (init_mode == 1) {
        state_flags = state->unk_14 | 0x6000;
        update_flags = state->unk_1C | 0x6000;
        state->unk_14 = state_flags;
        state->unk_1C = update_flags;
    } else if (init_mode >= 2) {
        state_flags = state->unk_14 | 0x2000;
        update_flags = state->unk_1C | 0x2000;
        state->unk_14 = state_flags;
        state->unk_1C = update_flags;
    } else if (((init_flags & ~3) << 0x10) == 0) {
        register void *query_object ASM_REG("$4") = object;   /* MATCH pin: retail delay-slot contents depend on it */
        if (!(state->unk_14 & 0x200)) {
            if (func_800A6D30(query_object) & 1) {
                func_800A48F0(state, 1, (func_800A6D30(query_object) & 0x3F) | 0x20);
                placement_data->unk_2C = &D_8015C25C;
            }
        }
    }
    func_800A9C18(object, config_data, placement_data, init_flags);
    extended_state->unk_9A = 0xFF;
    extended_state->unk_9C = -1;
    extended_state->unk_8C = &D_80159014;
    state->unk_1C = (s32)(state->unk_1C | 0x40000);
    extended_state->unk_92 = -0x20;
    func_800AA36C(extended_state, config_data, placement_data, state);
done:
    return state;
}
