/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_80DA1000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80DA1000_0;   /* temp_v0 in func_8015E874 */

typedef struct S_80DA1000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80DA1000_1;   /* var_s0 in func_8015E874 */

typedef struct S_80DA1000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80DA1000_2;   /* temp_s4 in func_8015E874 */

typedef struct S_80DA1000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80DA1000_3;   /* temp_s2 in func_8015E874 */

typedef struct S_80DA1000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80DA1000_4;   /* temp_s5 in func_8015E874 */




void *func_8003FD64();
s32 func_8004491C(); /* extern */
s16 func_800A48F0(); /* extern */
s32 func_800A6D30();
void func_800A9C18(); /* extern */
s32 func_800AA36C(); /* extern */
extern M2C_UNK D_8015EA3C;
extern M2C_UNK D_8015EE68;
extern M2C_UNK D_8016186C;

void *func_8015E874(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 type_id) ;
/* Allocates an entity and initializes its type, placement, flags, and callbacks. */
void *func_8015E874(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 type_id) {
    s32 global_byte;
    s32 unused_slot;
    s32 spawn_mode;
    s32 flags_14;
    s32 flags_1c;
    S_80DA1000_3 *placement;
    S_80DA1000_2 *type_data;
    void *object;
    S_80DA1000_4 *entity_data;
    S_80DA1000_1 *entity = NULL;
    s8 saved_x;
    s8 saved_y;
    s16 saved_type;
    void *object_arg;
    void *type_arg;

    M2C_ERROR(/* Read from unset register $t0 */) | 0x4481;
    saved_x = grid_x;
    saved_type = type_id;
    saved_y = grid_y;
    global_byte = (s32) *(s8 *)-0x56D4;
    object = func_8003FD64(0x112, ((M2C_UNK *)&D_80083498.next));
    if (object != NULL) {
        entity = object + 0x20;
        ((S_80DA1000_0 *)object)->unk_10 = &D_8015EA3C;
        entity->unk_13 = 0x1A;
        func_8004491C(object, func_80045340);
        type_data = ((S_80DA1000_0 *)object)->unk_08;
        type_data->unk_0A = saved_type;
        placement = ((S_80DA1000_0 *)object)->unk_0C;
        spawn_mode = spawn_flags & 3;
        placement->unk_25 = saved_y;
        entity_data = entity;
        placement->unk_2C = &D_8016186C;
        placement->unk_24 = saved_x;
        if (spawn_mode == 1) {
            flags_14 = entity->unk_14 | 0x6000;
            flags_1c = entity->unk_1C | 0x6000;
            entity->unk_14 = flags_14;
            entity->unk_1C = flags_1c;
        } else if (spawn_mode >= 2) {
            flags_14 = entity->unk_14 | 0x2000;
            flags_1c = entity->unk_1C | 0x2000;
            entity->unk_14 = (s32) flags_14;
            entity->unk_1C = (s32) flags_1c;
        } else {
            if (((spawn_flags & ~3) << 0x10) == 0) {
                if (!(entity->unk_14 & 0x200)) {
                    if (func_800A6D30() & 1) {
                        entity->unk_1C = (s32) (entity->unk_1C | 0x200);
                        func_800A48F0(entity, 1, (func_800A6D30() & 0x3F) | 0x20);
                    }
                }
            }
        }
        func_800A9C18(object, type_data, placement, spawn_flags);
        entity_data->unk_9A = 0xFF;
        entity_data->unk_9C = -1;
        entity_data->unk_8C = &D_8015EE68;
        func_800AA36C(entity_data, type_data, placement, entity);
    }
    return entity;
}
