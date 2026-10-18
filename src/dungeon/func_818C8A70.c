#include "shared/object_node.h"
#include "modules/dungeon_ovl_18e8800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

   /* the 0x2 bytes before arg0 in update_a_moving_effect_spawns_particles_advances_timed_phases, addressed as arg0[-1] */

   /* arg0 in update_a_moving_effect_spawns_particles_advances_timed_phases */







   /* arg1 in update_a_moving_effect_spawns_particles_advances_timed_phases */





   /* the 0x18 bytes before ((B31_818C8A70_S_818C8A70_0 *)arg0)->unk_30 in update_a_moving_effect_spawns_particles_advances_timed_phases, addressed as ((B31_818C8A70_S_818C8A70_0 *)arg0)->unk_30[-1] */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_800DE870[9];
extern u8 D_800DEC00[];
extern u8 D_800E3D68;

/* Updates a moving effect, spawns particles, and advances its timed phases. */
void update_a_moving_effect_spawns_particles_advances_timed_phases(void *effect, B31_818C8A70_S_818C8A70_4 *position) {
    M2C_UNK effect_mode;
    s16 coord;
    s16 coord_2;
    s16 phase;
    s32 effect_value;
    u8 random_value;
    u16 remaining_ticks;
    u16 burst_ticks;
    u16 fade_ticks;
    B31_818C8A70_S_818C8A70_3 *sprite;
    B31_818C8A70_S_818C8A70_5 *particle_pos;
    B31_818C8A70_S_818C8A70_1 *particle_state;   /* retained from the base: holds the repeated particle-state role */
    B31_818C8A70_S_818C8A70_6 *source;
    void *particle;

    D_80024D04 = 1;
    source = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_2C;
    if (((B31_818C8A70_S_818C8A70_0 *)effect)->unk_00 == 0) {
        particle = func_8003FC64(0x212);
        particle_state = particle + 0x20;
        if (particle != NULL) {
            particle_state->unk_02 = 0x1A;
            ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_10 = func_80024124;
            func_8004491C(particle, func_80045340);
            sprite = ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_0C;
            sprite->unk_10 = 0x60;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
            particle_pos = ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_08;
            random_value = func_80069EF8();
            coord = position->unk_00.at02.v;
            coord -= 8;
            coord += random_value & 0xF;
            particle_pos->unk_02 = coord;
            random_value = func_80069EF8();
            coord = position->unk_04.at02.v;
            coord -= 8;
            coord += random_value & 0xF;
            particle_pos->unk_06 = coord;
            random_value = func_80069EF8();
            coord = position->unk_08.at02.v;
            coord -= 4;
            coord += random_value & 7;
            particle_pos->unk_0A = coord;
            particle_state->unk_60 = (s32) (func_80069EF8() + 0xFFFE0000);
            sprite = ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_0C;
            sprite->unk_1C = 0x1000;
            sprite->unk_1E = 0x1000;
            sprite->unk_0E = 0x80;
            sprite->unk_0D = 0x80;
            sprite->unk_0C = 0x80;
            sprite->unk_12 = 0x7DCF;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
            func_8003DB94(sprite, D_800DE870, 0);
        }
        remaining_ticks = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 - 1;
        ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 = remaining_ticks;
        if ((remaining_ticks << 0x10) <= 0) {
            if (((B31_818C8A70_S_818C8A70_0 *)effect)->unk_08 != 0) {
                ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_00 = 1;
                ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 = 0U;
                play_sound_if_enabled(0x300);
            } else {
                ((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 = (u16) (((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 | 0x8000);
                object_flag_block.flags = object_flag_block.flags | 0x8000;
            }
        }
        if ((check_adjacent_tile_height_clearance(position->unk_00.at02.v, position->unk_04.at02.v, (s16) position->unk_08.at02.v, ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_30) << 0x10) == 0) {
            position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_58);
            position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_5C);
            position->unk_08.at00.v = (s32) (position->unk_08.at00.v + ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_60);
        } else {
            ((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 = (u16) (((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 | 0x8000);
            object_flag_block.flags = object_flag_block.flags | 0x8000;
            return;
        }
    }
    phase = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_00;
    if (phase == 1) {
        burst_ticks = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 + 1;
        ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 = burst_ticks;
        if ((burst_ticks & 3) == phase) {
            particle = func_8003FC64(0x212);
            particle_state = particle + 0x20;
            if (particle != NULL) {
                u32 particle_z;
                u16 particle_z_base;
                particle_state->unk_02 = 0x1A;
                ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_10 = func_80024124;
                func_8004491C(particle, func_80045340);
                sprite = ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_0C;
                sprite->unk_10 = 0x60;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
                particle_pos = ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_08;
                sprite = ((B31_818C8A70_S_818C8A70_7_pre *)(((B31_818C8A70_S_818C8A70_0 *)effect)->unk_30))[-1].unk_00;
                random_value = func_80069EF8();
                coord = sprite->unk_02;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->unk_02 = coord;
                random_value = func_80069EF8();
                coord = sprite->unk_06;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->unk_06 = coord;
                random_value = func_80069EF8();
                random_value &= 0x1F;
                particle_z_base = sprite->unk_0A;
                random_value += 0x10;
                particle_z = (u32)particle_z_base - random_value;
                particle_pos->unk_0A = particle_z;
                particle_state->unk_58 = (s32) (func_80069EF8() - 0x8000);
                particle_state->unk_5C = (s32) (func_80069EF8() - 0x8000);
                particle_state->unk_60 = (s32) ((func_80069EF8() + 0xFFFC0000) * 2);
                sprite = ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_0C;
                sprite->unk_1C = 0x1000;
                sprite->unk_1E = 0x1000;
                sprite->unk_0E = 0x80;
                sprite->unk_0D = 0x80;
                sprite->unk_0C = 0x80;
                sprite->unk_12 = 0x7DCF;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
                func_8003DB94(sprite, D_800DE870, 0);
            }
        }
        if ((((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 & 3) == 2) {
            particle = func_8003FC64(0x212);
            particle_state = particle + 0x20;
            if (particle != NULL) {
                s16 particle_z;
                particle_state->unk_02 = 0x14;
                ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_10 = interpolate_view_parameters;
                func_8004491C(particle, func_80045340);
                sprite = ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_0C;
                sprite->unk_10 = 0;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
                particle_pos = ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_08;
                sprite = ((B31_818C8A70_S_818C8A70_7_pre *)(((B31_818C8A70_S_818C8A70_0 *)effect)->unk_30))[-1].unk_00;
                random_value = func_80069EF8();
                coord = sprite->unk_02;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->unk_02 = coord;
                random_value = func_80069EF8();
                coord = sprite->unk_06;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->unk_06 = coord;
                random_value = func_80069EF8();
                random_value &= 0x3F;
                coord_2 = sprite->unk_0A;
                random_value += 0x20;
                particle_z = coord_2 - random_value;
                particle_pos->unk_0A = particle_z;
                sprite = ((B31_818C8A70_S_818C8A70_2 *)particle)->unk_0C;
                sprite->unk_1C = 0x800;
                sprite->unk_1E = 0x800;
                particle_state->unk_60 = (s32) (func_80069EF8() + 0xFFFE0000);
                sprite->unk_0E = 0x80;
                sprite->unk_0D = 0x80;
                sprite->unk_0C = 0x80;
                sprite->unk_12 = 0x7DC0;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
                func_8003DB94(sprite, D_800DEC00, 0);
            }
        }
        if ((s16) ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 >= 0x29) {
            ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_00 = 2;
            ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 = 0U;
            if (try_trigger_target_record_effect(source->unk_60, 1, source) == 0) {
                s16 random_bonus;
                u32 effect_scale;
                random_bonus = generate_random_value();
                random_bonus &= 3;
                effect_scale = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_15;
                random_bonus += 2;
                effect_scale >>= 2;
                effect_value = effect_scale + random_bonus;
                effect_mode = 0x10;
                if (D_800E3D68 == 0xFF) {
                    effect_mode = 0xFF;
                }
                try_apply_confusion_status(((B31_818C8A70_S_818C8A70_0 *)effect)->unk_30, effect_mode, effect_value);
            }
        }
    }
    if (((B31_818C8A70_S_818C8A70_0 *)effect)->unk_00 == 2) {
        fade_ticks = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 + 1;
        ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 = fade_ticks;
        if ((s16) fade_ticks >= 0x15) {
            ((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 = (u16) (((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 | 0x8000);
            object_flag_block.flags = object_flag_block.flags | 0x8000;
        }
    }
}
