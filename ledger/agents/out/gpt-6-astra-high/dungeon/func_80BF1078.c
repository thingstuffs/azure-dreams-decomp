#include "common.h"


extern u8 D_80083498[];
extern u8 D_8016AA58[];
extern u8 D_80045340[];
extern s32 D_8016B014;
extern s32 D_8016E20C;
extern s32 D_8016E25C;

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();


typedef struct S_8016A878_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 * unk_10;
} S_8016A878_0;   /* temp_v0 in func_8016A878 */

typedef struct S_8016A878_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A878_1;   /* var_s0 in func_8016A878 */

typedef struct S_8016A878_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A878_2;   /* temp_s4 in func_8016A878 */

typedef struct S_8016A878_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    s32 * unk_2C;
} S_8016A878_3;   /* temp_s2 in func_8016A878 */

typedef struct S_8016A878_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A878_4;   /* temp_s5 in func_8016A878 */

/* Allocate and initialize an object with its placement, flags, and runtime state. */
void *func_8016A878(s16 init_flags, s8 tile_x, s8 tile_y, s16 object_id)
{
    s32 mode;
    s32 flags_14;
    s32 flags_1c;
    S_8016A878_3 *placement;
    S_8016A878_2 *object_data;
    void *object;
    S_8016A878_4 *runtime;
    S_8016A878_1 *state;
    register s8 saved_x ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s16 saved_id;
    register s8 saved_y ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */

    state = 0;
    saved_x = tile_x;
    saved_id = object_id;
    saved_y = tile_y;
    object = func_8003FD64(0x112, D_80083498);
    if (object == 0) {
        goto done;
    }
    state = object + 0x20;
    ((S_8016A878_0 *)object)->unk_10 = D_8016AA58;
    state->unk_13 = 0x10;
    func_8004491C(object, D_80045340);
    object_data = ((S_8016A878_0 *)object)->unk_08;
    object_data->unk_0A = saved_id;
    placement = ((S_8016A878_0 *)object)->unk_0C;
    mode = init_flags & 3;
    placement->unk_25 = saved_y;
    runtime = state;
    placement->unk_2C = &D_8016E20C;
    placement->unk_24 = saved_x;
    if (mode == 1) {
        flags_14 = state->unk_14 | 0x6000;
        flags_1c = state->unk_1C | 0x6000;
        state->unk_14 = flags_14;
        state->unk_1C = flags_1c;
    } else if (mode >= 2) {
        flags_14 = state->unk_14 | 0x2000;
        flags_1c = state->unk_1C | 0x2000;
        state->unk_14 = flags_14;
        state->unk_1C = flags_1c;
    } else if (((init_flags & ~3) << 0x10) == 0) {
        register void *query_object ASM_REG("$4") = object;   /* MATCH pin: retail delay-slot contents depend on it */
        if (!(state->unk_14 & 0x200)) {
            if (func_800A6D30(query_object) & 1) {
                func_800A48F0(state, 1, (func_800A6D30(query_object) & 0x3F) | 0x20);
                placement->unk_2C = &D_8016E25C;
            }
        }
    }
    func_800A9C18(object, object_data, placement, init_flags);
    runtime->unk_9A = 0xFF;
    runtime->unk_9C = -1;
    runtime->unk_8C = &D_8016B014;
    state->unk_1C = (s32)(state->unk_1C | 0x40000);
    runtime->unk_92 = -0x20;
    func_800AA36C(runtime, object_data, placement, state);
done:
    return state;
}
