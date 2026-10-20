#include "dungeon/monster/troll/troll_flash_effects.h"

/* Creates an effect and sets its movement toward a tracked target or grid position. */
void create_targeted_motion_effect(void *source_handle, Rec_func_8017121C_arg1 *origin, s32 unused, EntityRec *target)
{
    T_8017121C_Vec3u16 offset;
    void *effect;
    void *init_effect;
    void *init_data;
    T_8017121C_S_8017121C_3 *coords;
    u8 *effect_state;
    T_8017121C_S_8017121C_6 *source;
    T_8017121C_S_8017121C_2 *part;
    T_8017121C_S_8017121C_9 *target_coords;
    s16 *direction_table;
    void *tracked_target;
    s32 delta_x;
    s32 delta_z;
    s32 fallback_x;
    s32 fallback_y;
    u32 untracked_mask;
    u32 target_flags;
    s32 effect_x;
    s16 *x_entry;
    s32 x_offset;
    s32 target_x;
    u32 y_table_addr;
    s16 *y_entry;
    s32 y_offset;
    s32 z_delta;
    s32 effect_z;
    s32 grid_x_bits;
    s32 grid_axis;
    s32 grid_y;
    s32 scaled_x;
    s32 scaled_y;
    s32 centered_coord;

    effect = func_8003FC64(0x212);
    if (effect == NULL) {
        return;
    }

    init_effect = effect;
    init_data = ((u8 *)update_rotating_actor_aura);
    effect_state = (u8 *)effect + 0x20;
    ((T_8017121C_S_8017121C_0 *)effect_state)->unk_18 = 2;
    ((T_8017121C_S_8017121C_0 *)effect_state)->unk_1A = 2;
    ((T_8017121C_S_8017121C_1 *)effect)->unk_10 = update_stepped_rgb_flash;
    register_node(init_effect, init_data);

    part = ((T_8017121C_S_8017121C_1 *)effect)->unk_0C;
    part->unk_14 &= 0xFFF3;

    coords = ((T_8017121C_S_8017121C_1 *)effect)->unk_08;
    coords->unk_02.s = origin->unk_02;
    coords->unk_06.s = origin->unk_06;
    coords->unk_0A.s = origin->unk_0A;

    source = ((T_8017121C_S_8017121C_5_pre *)source_handle)[-1].unk_00;
    if (resolve_record_orientation_or_fallback(source->unk_08, source, &offset, 0) != 0) {
        coords->unk_02.s += offset.raw_y;
        coords->unk_06.s += offset.y;
        coords->unk_0A.s += offset.z;
        part = ((T_8017121C_S_8017121C_1 *)effect)->unk_0C;
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
    } else {
        coords->unk_0A.s -= 0x14;
        part = ((T_8017121C_S_8017121C_1 *)effect)->unk_0C;
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
    }
    part->unk_0E = 0xA0;
    part->unk_0D = 0xA0;
    part->unk_0C = 0xA0;
    ((T_8017121C_S_8017121C_0 *)effect_state)->unk_00 = 0xA0;
    ((T_8017121C_S_8017121C_0 *)effect_state)->unk_01 = part->unk_0D;

    ((T_8017121C_S_8017121C_0 *)effect_state)->unk_02 = part->unk_0E;

    if (target->target == NULL) {
        ((T_8017121C_S_8017121C_0 *)effect_state)->unk_60 = 0;
        ((T_8017121C_S_8017121C_0 *)effect_state)->unk_5C = 0;
        ((T_8017121C_S_8017121C_0 *)effect_state)->unk_58 = 0;
        grid_axis = ((u8)target->unk_73);
    } else {
        target_flags = ((u32)target->flags14);
        untracked_mask = 0x04000000;
        if ((target_flags & untracked_mask) == 0) {
            direction_table = ((s16 *)D_80175EBC);
            ((T_8017121C_S_8017121C_0 *)effect_state)->unk_60 = 0;
            ((T_8017121C_S_8017121C_0 *)effect_state)->unk_5C = 0;
            ((T_8017121C_S_8017121C_0 *)effect_state)->unk_58 = 0;

            grid_axis = ((u16)target->facing);
            tracked_target = target->target;
            effect_x = coords->unk_02.u;
            grid_axis = (u32)grid_axis >> 7;
            grid_axis &= 0x1C;
            grid_axis += (u32)direction_table;
            x_entry = (s16 *)grid_axis;
            target_coords = ((T_8017121C_S_8017121C_8_pre *)tracked_target)[-1].unk_00;
            x_offset = *x_entry;
            target_x = target_coords->unk_02;
            x_offset <<= 4;
            delta_x = target_x - effect_x;
            delta_x -= x_offset;
            ((T_8017121C_S_8017121C_0 *)effect_state)->unk_5A = delta_x / 2;

            y_table_addr = ((u16)target->facing);
            centered_coord = target_coords->unk_06;
            effect_z = coords->unk_06.u;
            y_table_addr = (y_table_addr >> 7) & 0x1C;
            y_table_addr += (u32)direction_table;
            y_entry = (s16 *)y_table_addr;
            y_offset = y_entry[1];
            centered_coord = centered_coord - effect_z;
            y_offset <<= 4;
            centered_coord -= y_offset;
            centered_coord += (u32)centered_coord >> 31;
            centered_coord >>= 1;
            ((T_8017121C_S_8017121C_0 *)effect_state)->unk_5E = centered_coord;

            effect_z = coords->unk_0A.u;
            z_delta = target_coords->unk_0A - effect_z;
            delta_z = z_delta;
            delta_z -= D_800DDC40[((T_8017121C_S_8017121C_10 *)(target->target))->unk_13] >> 1;
            ((T_8017121C_S_8017121C_0 *)effect_state)->unk_62 = delta_z / 2;
            return;
        }

        ((T_8017121C_S_8017121C_0 *)effect_state)->unk_60 = 0;
        ((T_8017121C_S_8017121C_0 *)effect_state)->unk_5C = 0;
        ((T_8017121C_S_8017121C_0 *)effect_state)->unk_58 = 0;

        grid_axis = ((u8)target->unk_73);
    }
    ;
    grid_x_bits = ((u8)target->unk_72);
    grid_axis <<= 24;
    grid_y = grid_axis >> 24;
    grid_x_bits <<= 24;
    grid_axis = grid_x_bits >> 24;
    if (grid_x_bits < 0) {
        grid_axis = -grid_axis;
    }
    if ((s16)grid_y < 0) {
        grid_y = -grid_y;
    }
    scaled_x = grid_axis << 16;
    centered_coord = coords->unk_02.u;
    scaled_x >>= 10;
    centered_coord -= 0x20;

    fallback_x = scaled_x - centered_coord;
    ((T_8017121C_S_8017121C_0 *)effect_state)->unk_5A = fallback_x / 2;
    centered_coord = coords->unk_06.u;
    scaled_y = (grid_y << 16) >> 10;
    ((T_8017121C_S_8017121C_0 *)effect_state)->unk_62 = 0;
    centered_coord -= 0x20;
    fallback_y = scaled_y - centered_coord;
    ((T_8017121C_S_8017121C_0 *)effect_state)->unk_5E = fallback_y / 2;
}

/* MECHANISM: Raw u8 shift/sign-extension idioms reproduce the fallback branches without widening
   artifacts. Mutating scaled_x with >>= 10 lets its sra fill an lh delay; scaled_y is shifted in one
   expression (single-set pseudos are scheduled as births), which keeps the second half in source order
   around the zero store. */
