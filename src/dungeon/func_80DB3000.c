/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_80DB3000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80DB3000_0;   /* temp_v0 in func_8014C874 */

typedef struct S_80DB3000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80DB3000_1;   /* var_s0 in func_8014C874 */

typedef struct S_80DB3000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80DB3000_2;   /* temp_s4 in func_8014C874 */

typedef struct S_80DB3000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80DB3000_3;   /* temp_s2 in func_8014C874 */

typedef struct S_80DB3000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80DB3000_4;   /* temp_s5 in func_8014C874 */




void *func_8003FD64();
s32 func_8004491C(); /* extern */
s16 func_800A48F0(); /* extern */
s32 func_800A6D30();
void func_800A9C18(); /* extern */
s32 func_800AA36C(); /* extern */
extern M2C_UNK D_8014CA3C;
extern u8 D_8014CE68;
extern M2C_UNK D_8014F86C;

void *func_8014C874(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 property_value) ;
/* Allocates and initializes a dungeon object with the supplied flags and placement. */
void *func_8014C874(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 property_value) {
    s32 global_byte;
    s32 unused_slot;
    s32 spawn_mode;
    s32 flags_14;
    s32 flags_1c;
    S_80DB3000_3 *placement;
    S_80DB3000_2 *properties;
    void *object;
    S_80DB3000_4 *extended_state;
    S_80DB3000_1 *state = NULL;
    s8 saved_x;
    s8 saved_y;
    s16 saved_property;
    void *call_object;
    void *call_properties;

    M2C_ERROR(/* Read from unset register $t0 */) | 0x4481;
    saved_x = grid_x;
    saved_property = property_value;
    saved_y = grid_y;
    global_byte = (s32) *(s8 *)-0x56D4;
    object = func_8003FD64(0x112, ((M2C_UNK *)&D_80083498.next));
    if (object != NULL) {
        state = object + 0x20;
        ((S_80DB3000_0 *)object)->unk_10 = &D_8014CA3C;
        state->unk_13 = 0x1A;
        func_8004491C(object, func_80045340);
        properties = ((S_80DB3000_0 *)object)->unk_08;
        properties->unk_0A = saved_property;
        placement = ((S_80DB3000_0 *)object)->unk_0C;
        spawn_mode = spawn_flags & 3;
        placement->unk_25 = saved_y;
        extended_state = state;
        placement->unk_2C = &D_8014F86C;
        placement->unk_24 = saved_x;
        if (spawn_mode == 1) {
            flags_14 = state->unk_14 | 0x6000;
            flags_1c = state->unk_1C | 0x6000;
            state->unk_14 = flags_14;
            state->unk_1C = flags_1c;
        } else if (spawn_mode >= 2) {
            flags_14 = state->unk_14 | 0x2000;
            flags_1c = state->unk_1C | 0x2000;
            state->unk_14 = (s32) flags_14;
            state->unk_1C = (s32) flags_1c;
        } else {
            if (((spawn_flags & ~3) << 0x10) == 0) {
                if (!(state->unk_14 & 0x200)) {
                    if (func_800A6D30() & 1) {
                        state->unk_1C = (s32) (state->unk_1C | 0x200);
                        func_800A48F0(state, 1, (func_800A6D30() & 0x3F) | 0x20);
                    }
                }
            }
        }
        func_800A9C18(object, properties, placement, spawn_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &D_8014CE68;
        func_800AA36C(extended_state, properties, placement, state);
    }
    return state;
}
