#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CA1E0_0 {
    u8 pad_00[0x24];
    union { u8 s; volatile u8 u; } unk_24;   /* accessed as both */
    union { u8 s; volatile u8 u; } unk_25;   /* accessed as both */
    s8 unk_26;
} S_800CA1E0_0;   /* temp_s2 in func_800CA1E0 */

typedef struct S_800CA1E0_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
} S_800CA1E0_1;   /* temp_table in func_800CA1E0 */

typedef struct S_800CA1E0_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} S_800CA1E0_2;   /* temp_arg2 in func_800CA1E0 */

typedef struct S_800CA1E0_3 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_800CA1E0_3;   /* (void *)temp_e_index in func_800CA1E0 */


extern u16 D_8006CCD8[];
extern u8 D_8008333C[32];
extern u16 D_8006CCE8[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
extern s8 D_800E2970[];
M2C_UNK func_8009A350();
s16 func_8009FB34();
s16 func_800BCB04();

/* Checks whether a directional step is in bounds and clear of obstacles. */
s32 func_800CA1E0(u32 action_flags, void *position, void *volatile object, u16 height_offset) {
    u16 tile_flags;
    u16 saved_height_offset;
    s32 lookup_arg;
    s32 direction;
    register s32 target_coord ASM_REG("$16");
    s32 target_x;
    register s32 center_y ASM_REG("$20");
    s32 direction_offset;
    s32 coord_value;
    register s32 coord_offset ASM_REG("$2");
    s32 query_arg;
    s32 direction_arg;
    void *tile_flags_out;
    register u16 entry_height_offset ASM_REG("$7");
    s32 entity_addr;
    register u16 *lookup_base ASM_REG("$2");
    register u16 *step_x;
    u16 *step_y;
    u16 *offset_x;
    u16 *offset_y;
    u16 height;
    register u32 bounds_page ASM_REG("$2");
    s32 early_result;
    u32 scaled_y;
    register u32 scaled_x ASM_REG("$3");
    register s32 result ASM_REG("$2");
    register s32 call_height_offset ASM_REG("$8");
    register S_800CA1E0_0 *coords ASM_REG("$18");
    register S_800CA1E0_2 *object_data ASM_REG("$8");
    register u8 *bounds ASM_REG("$6");
    s32 clearance;
    void *position_copy;

    position_copy = position;
    coords = position_copy;
    ASM_KEEP_NV(coords);
    entry_height_offset = height_offset;
    ASM_KEEP_NV(entry_height_offset);
    lookup_arg = (action_flags >> 9) & 7;
    direction = lookup_arg;
    ASM_KEEP_NV(direction);
    lookup_base = D_8006CCD8;
    direction_offset = direction << 1;
    ASM_KEEP_NV(direction_offset);
    step_x = (u16 *)((u32)direction_offset + (u32)lookup_base);
    coord_value = coords->unk_24.s;
    coord_offset = *step_x;
    ASM_KEEP_NV(direction);
    ASM_CLOBBER("$4");
    lookup_arg = direction;
    ASM_KEEP_NV(lookup_arg);
    saved_height_offset = entry_height_offset;
    target_x = coord_value + coord_offset;
    bounds_page = 0x80080000;
    ASM_KEEP_DEP_NV(bounds_page, target_x);
    coord_value = target_x & 0xFFFF;
    bounds = (u8 *)(bounds_page + 0x333C);
    if (coord_value == 0) {
        goto out_of_bounds;
    }
    ASM_KEEP_NV(bounds);
    position_copy = (void *)1;
    if (((1 << ((S_800CA1E0_1 *)bounds)->unk_14) - 1) < coord_value) {
        return -1;
    }
    lookup_base = D_8006CCE8;
    step_y = (u16 *)((u32)direction_offset + (u32)lookup_base);
    coord_value = coords->unk_25.s;
    coord_offset = *step_y;
    target_coord = coord_value + coord_offset;
    coord_value = target_coord & 0xFFFF;
    if (coord_value == 0) {
        return -1;
    }
    if (!(((1 << ((S_800CA1E0_1 *)bounds)->unk_16) - 1) < coord_value)) {
        goto check_step;
    }
out_of_bounds:
    early_result = -1;
    return early_result;
check_step:
    scaled_x = coords->unk_24.u;
    scaled_y = coords->unk_25.u;
    object_data = object;
    scaled_x <<= 6;
    ASM_KEEP_NV(scaled_x);
    query_arg = scaled_x >> 6;
    ASM_KEEP_NV(query_arg);
    scaled_y <<= 6;
    ASM_KEEP_NV(scaled_y);
    direction_arg = scaled_y >> 6;
    ASM_KEEP_NV(direction_arg);
    target_coord = scaled_x + 0x20;
    height = object_data->unk_88;
    center_y = scaled_y + 0x20;
    if ((func_8009A540(lookup_arg, query_arg, direction_arg, (s16) (height - entry_height_offset)) << 0x10) == 0) {
        goto blocked;
    }
    direction_arg = direction;
    ASM_KEEP_NV(direction_arg);
    tile_flags_out = &tile_flags;
    ASM_KEEP_NV(tile_flags_out);
    offset_x = D_800DCEAC;
    offset_x = (u16 *)((u32)direction_offset + (u32)offset_x);
    ASM_KEEP_NV(offset_x);
    offset_y = D_800DCEBC;
    offset_y = (u16 *)((u32)direction_offset + (u32)offset_y);
    ASM_KEEP_NV(offset_y);
    lookup_arg = coords->unk_24.s;
    ASM_KEEP_NV(lookup_arg);
    query_arg = coords->unk_25.s;
    ASM_KEEP_NV(query_arg);
    coord_value = *offset_x;
    coord_offset = *offset_y;
    target_x = coord_value + target_coord;
    target_coord = coord_offset + center_y;
    func_8009A350(lookup_arg, query_arg, direction_arg, tile_flags_out);
    if ((tile_flags & 0x8002) != 0) {
        goto blocked;
    }
    goto check_entity;
blocked:
    early_result = 0;
    return early_result;
check_entity:
    if (coords->unk_26 < 0) {
        lookup_arg = func_8009FB34((coords->unk_24.s + *step_x) & 0xFFFF, (coords->unk_25.s + *step_y) & 0xFFFF);
        if (lookup_arg >= 0) {
            entity_addr = lookup_arg << 2;
            lookup_base = (u16 *)D_800E2970;
            entity_addr = (entity_addr + lookup_arg) << 2;
            entity_addr = entity_addr + (u32)lookup_base;
            ASM_KEEP_NV(entity_addr);
            lookup_arg = target_x & 0xFFFF;
            if (!(((S_800CA1E0_3 *)((void *)entity_addr))->unk_0C & 2)) {
                goto check_clearance;
            }
            object_data = object;
            if (!(object_data->unk_1C & 0x2000)) {
                goto blocked;
            }
        }
    }
    lookup_arg = target_x & 0xFFFF;
check_clearance:
    call_height_offset = saved_height_offset;
    clearance = (s16)func_800BCB04(lookup_arg, target_coord & 0xFFFF, (s16) (height - call_height_offset));
    result = -1;
    if (clearance < 0x201) {
        result = 1;
    }
    return result;
}
