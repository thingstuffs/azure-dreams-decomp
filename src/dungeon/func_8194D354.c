#include "modules/dungeon_ovl_7e6b7800.h"

void update_three_way_target_effect(void *effect_arg, void *position) {
    s32 fallback_pos[6];
    Row_8194D1E4_Packed8 direction;
    Row_8194D1E4_FourWords transform[2];
    s16 offset[3];
    s32 *target_pos;
    TileObject *tile_or_y_steps;
    s32 *effect_pool;
    EntityRec *origin;

    s16 phase;
    s32 state_or_heading;
    s32 rounded_phase;
    s32 phase_random;
    s32 step_count;
    u16 *input_page;
    s32 position_valid;
    s32 origin_x, shifted_height, view_heading;
    s32 clear_tint_mask;
    s32 neutral_color;
    u16 start_delay;
    u16 ground_height;
    u16 near_height;
    u16 tint_delay;
    u16 next_state_c1;
    u16 next_state_c2;
    u16 next_state_c3;
    s32 forward_dx;
    s32 forward_dy;
    s32 backtrack_dx;
    s32 backtrack_dy;
    u8 tile_y;
    void *actor_or_frame;
    void *effect_data;
    s32 offset_mode;
    void *target;
    EntityRec *actor_value;
    void *actor_value_2;


    state_or_heading = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.s;
    ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_10 = (u16)(((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_10 + 1);
    switch ((u32)state_or_heading) {
    case 0:
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_10 = 0U;
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.s++;
        D_800814A8->unk_F4 = 0;
        allocate_effect_and_initialize_sprite(((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_00 - 0x20, ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_04, &D_800DE5DC);
    case 1:
        if (*((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_04 & 0x80) {
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 = 0xAU;
            ((Row_8194D354_S_80024B54_1 *)D_800814A8)->unk_A6--;
            D_800814A8->unk_A8 = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_08;
            next_state_c1 = ((u16)D_800814A8->facing);
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.s++;
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0E = next_state_c1;
            if (func_80053EF0(4) != 2) {
                play_sound_if_enabled(0x300);
                ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_1A = 0;
                return;
            }
            play_sound_if_enabled(0x4300);
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_1A = 0;
            return;
        }
        break;
    case 2:
        start_delay = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 - 1;
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 = start_delay;
        if ((start_delay << 0x10) > 0) {
            break;
        }
        phase_random = func_80069EF8();
        rounded_phase = phase_random;
        if ((phase_random) < 0) {
            rounded_phase = (phase_random) + 0xFFF;
        }
        origin = &D_80083780;
        origin_x = (s32)D_80083780.x.v;
        (*(s32 *)((u8 *)position + 0)) = origin_x;
        phase = phase_random - ((rounded_phase >> 12) << 12);
        (*(s32 *)((u8 *)position + 4)) = origin->y.v;
        actor_value = D_800814A8;
        tile_or_y_steps = &D_80082E80;
        shifted_height = ((actor_value->unk_88) - 0x50) << 0x10;
        effect_data = offset;
        (*(s32 *)((u8 *)position + 8)) = shifted_height;
        view_heading = g_game_work.view.viewAngle;
        state_or_heading = actor_value->facing;
        offset_mode = 0;
        view_heading += state_or_heading;
        view_heading += 0x100;
        view_heading >>= 7;
        view_heading &= 0x1C;
        state_or_heading = (*(s32 *)D_800E3D18);
        actor_or_frame = (void *)(s32)*(s32 *)(view_heading + state_or_heading);
        if (resolve_record_orientation_or_fallback(actor_or_frame, tile_or_y_steps, effect_data, offset_mode) != 0) {
            (*(s32 *)((u8 *)position + 0)) = (s32)((*(s32 *)((u8 *)position + 0)) + (offset[0] << 0x10));
            (*(s32 *)((u8 *)position + 4)) = (s32)((*(s32 *)((u8 *)position + 4)) + (offset[1] << 0x10));
            (*(s32 *)((u8 *)position + 8)) = (s32)((*(s32 *)((u8 *)position + 8)) + (offset[2] << 0x10));
        }
        actor_or_frame = D_800814A8;
        target = scan_monster_along_heading(actor_or_frame, tile_or_y_steps->tileX,
            tile_or_y_steps->tileY, (s16)((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_2A, 8);
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14 = target;
        if (target != NULL) {
            target_pos = ((Row_8194D354_S_80024B54_6_pre *)target)[-1].unk_00;
        } else {
            target_pos = fallback_pos;
            step_count = 0;
            ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u = (u16)((tile_or_y_steps->tileX << 6) + 0x20);
            tile_y = tile_or_y_steps->tileY;
            ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u = (u16)((tile_y << 6) + 0x20);
            do {
                actor_or_frame = D_800814A8;
                forward_dx = dir_step_x[(((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u = (u16)(((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u + (forward_dx << 6));
                forward_dy = dir_step_y[(((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u = (u16)(((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u + (forward_dy << 6));
                ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u = (u16)((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_88;
                ground_height = get_surface_height_at_record(target_pos);
                ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u = ground_height;
                if ((s16)ground_height > 0x200) {
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u =
                        (u16)((u16)D_800814A8->unk_88);
                }
                position_valid = check_left_tile_and_center_height(((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u,
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u, (s16)((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u);
                if ((position_valid << 0x10) != 0) {
                    actor_or_frame = D_800814A8;
                    backtrack_dx = dir_step_x[(((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u = (u16)(((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.u - (backtrack_dx
                        << 5));
                    backtrack_dy = dir_step_y[(((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u = (u16)(((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.u - (backtrack_dy
                        << 5));
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u = (u16)((Row_8194D354_S_80024B54_5 *)actor_or_frame)->unk_88;
                    near_height = get_surface_height_at_record(target_pos);
                    ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u = near_height;
                    if ((s16)near_height > 0x200) {
                        ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.u =
                            (u16)((u16)D_800814A8->unk_88);
                    }
                    break;
                }
                step_count += 1;
            } while (step_count < 8);
        }
        update_directional_actor_effect(((Row_8194D354_S_80024B54_8 *)position)->unk_02, ((Row_8194D354_S_80024B54_8 *)position)->unk_06,
            ((Row_8194D354_S_80024B54_8 *)position)->unk_0A, ((Row_8194D354_S_80024B54_7 *)target_pos)->unk_02.s,
            (s32)((Row_8194D354_S_80024B54_7 *)target_pos)->unk_06.s, (s32)((Row_8194D354_S_80024B54_7 *)target_pos)->unk_0A.s, &direction);
        func_80065820(&direction, transform);
        allocate_effect_with_endpoints((s32)effect_arg, position, target_pos, phase, transform[0], transform[1], direction);
        allocate_effect_with_endpoints((s32)effect_arg, position, target_pos, (s16)(phase + 0x555), transform[0], transform[1], direction);
        allocate_effect_with_endpoints((s32)effect_arg, position, target_pos, (s16)(phase + 0xAAA), transform[0], transform[1], direction);
        next_state_c2 = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.u;
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 = 0x18U;
        ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.s = (s16)(next_state_c2 + 1);
        break;
    case 3:
        actor_or_frame = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14;
        if (actor_or_frame != NULL) {
            (*(s32 *)((u8 *)actor_or_frame + 0x1C)) = (s32)((*(s32 *)((u8 *)actor_or_frame + 0x1C)) | 0x10000000);
            effect_data = ((Row_8194D354_S_80024B54_13_pre *)(((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14))[-1].unk_00;
            if ((s16)((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 >= 0xC) {
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C + 8);
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D - 8);
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E - 8);
                if ((u8)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C >= 0xE1U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C = 0xE0U;
                }
                if ((u8)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D < 0x20U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D = 0x20U;
                }
                if ((u8)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E < 0x20U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E = 0x20U;
                }
                input_page = (u16 *)0x80080000;
            } else {
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C - 8);
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D + 8);
                ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E = (u8)(((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E + 8);
                if ((u8)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C < 0x80U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0C = 0x80U;
                }
                if ((u8)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D >= 0x81U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0D = 0x80U;
                }
                input_page = (u16 *)(u32)((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E;
                if ((u32)input_page >= 0x81U) {
                    ((Row_8194D354_S_80024B54_9 *)effect_data)->unk_0E = 0x80U;
                }
                input_page = (u16 *)0x80080000;
            }
        } else {
            input_page = (u16 *)0x80080000;
        }
        if (!(((Row_8194D354_S_80024B54_10 *)input_page)->unk_2E94 & 0x8000)) {
            tint_delay = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 - 1;
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_18 = tint_delay;
            if ((s16)tint_delay >= 0) {
                break;
            }
        }
        if (((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14 != NULL) {
            apply_attack_power_and_element_effects(((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14, 0xA, ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_09, 9,
                (s32)(s16)((((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0E << 9) + 0x800), ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_00, 1);
            clear_tint_mask = 0xEFFFFFFF;
            neutral_color = 0x00808080;
            actor_value_2 = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_14;
            ((Row_8194D354_S_80024B54_1 *)actor_value_2)->unk_1C = (s32)(((Row_8194D354_S_80024B54_1 *)actor_value_2)->unk_1C & clear_tint_mask);
            effect_data = ((Row_8194D354_S_80024B54_1_pre *)actor_value_2)[-1].unk_00;
            (*(s32 *)((u8 *)effect_data + 0xC)) = neutral_color;
        }
        effect_pool = (s32 *)0x80080000;
        if (((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_1A != 0) {
            next_state_c3 = ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.u;
            ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_0A.s = (s16)(next_state_c3 + 1);
            break;
        }
    case 4:
        effect_pool = (s32 *)0x80080000;
        if (((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_1A != 0) {
            break;
        }
        effect_pool = (s32 *)((u8 *)effect_pool + 0x3460);
        (*(s32 *)((u8 *)effect_pool + 0xC)) = 0;
        ((Row_8194D354_S_80024B54_11 *)effect_pool)->unk_0A = (u16)(((Row_8194D354_S_80024B54_11 *)effect_pool)->unk_0A - 1);
        (*(u16 *)((u8 *)effect_arg + -2)) = (u16)(((Row_8194D354_S_80024B54_0_pre *)effect_arg)[-1].unk_00 | 0x8000);
        (*(s32 *)&object_flag_block.flags) = (s32)((*(s32 *)((u8 *)(&object_flag_block.flags) + 0)) | 0x8000);
        return;
    default:
        break;
    }
    ((Row_8194D354_S_80024B54_0 *)effect_arg)->unk_1A = 0;
    return;
}
