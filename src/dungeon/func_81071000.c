/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_func_80158898_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_func_80158898_0;   /* temp_v0 in func_80158898 */

typedef struct S_func_80158898_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x78];
    u16 unk_98;
} S_func_80158898_1;   /* var_s0 in func_80158898 */

typedef struct S_func_80158898_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_func_80158898_2;   /* temp_s4 in func_80158898 */

typedef struct S_func_80158898_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_func_80158898_3;   /* temp_s2 in func_80158898 */

typedef struct S_func_80158898_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0xD];
    s16 unk_AA;
} S_func_80158898_4;   /* temp_s5 in func_80158898 */

void *func_8003FD64();
s32 func_8004491C();
s16 func_800A48F0();
s32 func_800A6D30();
void func_800A9C18();
s32 func_800AA36C();
extern M2C_UNK D_80158AA4;
extern M2C_UNK D_80158F68;
extern M2C_UNK D_8015BFB8;
extern M2C_UNK D_8015C000;



/* Allocate a dungeon object and initialize its placement, flags, and behavior. */
 void *func_80158898(s16 spawn_flags, s16 x, s16 y, s16 config_value) {
    S_func_80158898_1 *object_state;
    s32 mode_or_roll;
    u16 state_flags;
    S_func_80158898_3 *placement;
    S_func_80158898_2 *config;
    S_func_80158898_4 *behavior;
    void *object;
    s8 saved_x;
    s16 saved_config_value;
    s8 saved_y;
    void *init_config;

    object_state = NULL;
    saved_x = x;
    saved_config_value = config_value;
    saved_y = y;
    object = func_8003FD64(0x112, ((M2C_UNK *)&D_80083498.next));
    if (object != NULL) {
        object_state = object + 0x20;
        ((S_func_80158898_0 *)object)->unk_10 = &D_80158AA4;
        object_state->unk_13 = 0x2B;
        func_8004491C(object, func_80045340);
        config = ((S_func_80158898_0 *)object)->unk_08;
        config->unk_0A = saved_config_value;
        placement = ((S_func_80158898_0 *)object)->unk_0C;
        mode_or_roll = spawn_flags & 3;
        placement->unk_25 = saved_y;
        behavior = object_state;
        placement->unk_2C = &D_8015BFB8;
        placement->unk_24 = saved_x;
        if (mode_or_roll == 1) {
            state_flags = object_state->unk_98;
            object_state->unk_14 = (s32) (object_state->unk_14 | 0x6000);
            object_state->unk_98 = (u16) (state_flags | 0x4000);
            object_state->unk_1C = (s32) (object_state->unk_1C | 0x6000);
        } else if (mode_or_roll >= 2) {
            state_flags = object_state->unk_98;
            object_state->unk_14 = (s32) (object_state->unk_14 | 0x2000);
            object_state->unk_98 = (u16) (state_flags | 0x4000);
            object_state->unk_1C = (s32) (object_state->unk_1C | 0x2000);
        } else if (((spawn_flags & ~3) << 0x10) == 0) {
            if (!(object_state->unk_14 & 0x200)) {
                init_config = config;
                mode_or_roll = func_800A6D30();
                if (mode_or_roll & 1) {
                    object_state->unk_1C = (s32) (object_state->unk_1C | 0x200);
                    func_800A48F0(object_state, 1, (func_800A6D30() & 0x3F) | 0x20);
                    placement->unk_2C = &D_8015C000;
                }
            }
        }
        func_800A9C18(object, config, placement, spawn_flags);
        behavior->unk_9A = 0xFF;
        behavior->unk_9C = -1;
        behavior->unk_8C = &D_80158F68;
        placement->unk_14 = (u16) (placement->unk_14 | 0xC);
        behavior->unk_AA = (s16) ((u16) object_state->unk_14 & 7);
        func_800AA36C(behavior, config, placement, object_state);
    }
    return object_state;
}
