#include "modules/dungeon_ovl_18b8824.h"

void dungeonAdvanceLaunchedEffect(ovl_18b8824_81898EBC_EffectState *state, ovl_18b8824_81898EBC_Motion *motion, ovl_18b8824_81898EBC_ColorPart *part)
{
    void *owner;
    void *owner_data;
    void *owner_node;
    void *source_pos;
    register u8 *origin;
    ovl_18b8824_81898EBC_Scratch scratch;
    u8 *global_page;
    s32 state_id;
    u32 source_z;
    s32 axis;
    u8 *delta_ptr;
    s16 *target_pos;
    s32 target_z;

    state->timer++;
    state_id = state->state;
    owner = state->owner;

    switch (state_id) {
    case 0:

        origin = ((u8 *)&D_80082E80);
        {
            void *node = ovl_18b8824_81898EBC_PTR_AT((u8 *)owner - 0x20, 0xC);
            s32 dir = (ovl_18b8824_81898EBC_U16_AT(D_800814A8, 0x2A) >> 9) & 7;
            ovl_18b8824_81898EBC_U16_AT(owner, 0x2A) = dungeonGetRoundedFacingAndRoundingFlag(ovl_18b8824_81898EBC_U8_AT(node, 0x24), ovl_18b8824_81898EBC_U8_AT(node, 0x25),
                origin[0x24] + dirStepX[dir], origin[0x25] + dirStepY[dir], &ovl_18b8824_81898EBC_result);
        }
        state->timer = 0;
        state->state++;
        state->direction = (ovl_18b8824_81898EBC_U16_AT(owner, 0x2A) >> 9) & 7;
        state->status = 0;
        part->color = 0x00808080;

    case 1:
        owner_data = (u8 *)owner - 0x20;
        owner_node = ovl_18b8824_81898EBC_PTR_AT(owner_data, 0xC);
        if (resolveRecordOrientationOrFallback(ovl_18b8824_81898EBC_PTR_AT(owner_node, 8), owner_node, ovl_18b8824_81898EBC_probe, 0) == 0) {
            if (!(ovl_18b8824_81898EBC_U16_AT(ovl_18b8824_81898EBC_PTR_AT(owner_data, 0xC), 0x14) & 0x8000)) {
                break;
            }
        }

        source_pos = ovl_18b8824_81898EBC_PTR_AT(owner_data, 8);
        ovl_18b8824_81898EBC_U16_AT(motion, 2) = ovl_18b8824_81898EBC_U16_AT(source_pos, 2);
        ovl_18b8824_81898EBC_U16_AT(motion, 6) = ovl_18b8824_81898EBC_U16_AT(source_pos, 6);
        source_z = ovl_18b8824_81898EBC_U16_AT(source_pos, 0xA);
        ovl_18b8824_81898EBC_U16_AT(motion, 0xA) = source_z;
        if (!(ovl_18b8824_81898EBC_U16_AT(ovl_18b8824_81898EBC_PTR_AT(owner_data, 0xC), 0x14) & 0x8000)) {
            ovl_18b8824_81898EBC_U16_AT(motion, 2) += ovl_18b8824_81898EBC_probe[0];
            ovl_18b8824_81898EBC_U16_AT(motion, 6) += ovl_18b8824_81898EBC_probe[1];
            ovl_18b8824_81898EBC_U16_AT(motion, 0xA) += ovl_18b8824_81898EBC_probe[2];
        } else {
            ovl_18b8824_81898EBC_U16_AT(motion, 0xA) = source_z - 0x40;
        }
        if (!(ovl_18b8824_81898EBC_U16_AT(state->image, 0) & 0x80)) {
            break;
        }

        target_pos = scratch.work;
        if ((ovl_18b8824_81898EBC_U16_AT(owner_data, 0x1E) | 0x2000) != 0) {
            void *direction_node = D_800814A8;

            state->x = D_80082E80.tileX + dirStepX[(ovl_18b8824_81898EBC_U16_AT(direction_node, 0x2A) >> 9) & 7];
            state->y = D_80082E80.tileY + dirStepY[(ovl_18b8824_81898EBC_U16_AT(direction_node, 0x2A) >> 9) & 7];
        } else {
            state->x = D_80082E80.tileX + dirStepX[state->direction];
            state->y = D_80082E80.tileY + dirStepY[state->direction];
        }

        {
            {
                void *height_node;
                s32 tile_coord;

                tile_coord = state->x;
                global_page = (u8 *)0x80080000;
                ovl_18b8824_81898EBC_S16_AT(target_pos, 2) = tile_coord * 64 + 0x20;
                tile_coord = state->y;
                height_node = ovl_18b8824_81898EBC_PTR_AT(global_page, 0x14A8);
                ovl_18b8824_81898EBC_S16_AT(target_pos, 6) = tile_coord * 64 + 0x20;
                ovl_18b8824_81898EBC_S16_AT(target_pos, 0xA) = ((s16 *)height_node)[0x44] - 0x20;
            }
            ovl_18b8824_81898EBC_S16_AT(target_pos, 0xA) = dungeonGetSurfaceHeightAtRecord(target_pos);
            state->z = ovl_18b8824_81898EBC_S16_AT(target_pos, 0xA);
            getOffsetMapCellValueAndFlags(state->x - 1, state->y, 0, &ovl_18b8824_81898EBC_map_flags);
            if (ovl_18b8824_81898EBC_map_flags & 0x3300) {
                s32 fallback_value;

                fallback_value =
                    ((s16 *)ovl_18b8824_81898EBC_PTR_AT(global_page, 0x14A8))[0x44] << 16;
                ovl_18b8824_81898EBC_S32_AT((u8 *)target_pos, 8) = fallback_value;
                state->state = 6;
            } else {
                target_z = ovl_18b8824_81898EBC_S16_AT(target_pos, 0xA);

                if (target_z >= 0x201) {
                    s32 fallback_value;

                    fallback_value =
                        ((s16 *)ovl_18b8824_81898EBC_PTR_AT(global_page, 0x14A8))[0x44] << 16;
                    ovl_18b8824_81898EBC_S32_AT((u8 *)target_pos, 8) = fallback_value;
                    state->state = 6;
                } else if ((dungeonCheckLeftTileAndCenterHeight(ovl_18b8824_81898EBC_U16_AT(target_pos, 2), ovl_18b8824_81898EBC_U16_AT(target_pos, 6), target_z) << 16) != 0) {
                    s32 fallback_value;

                    fallback_value =
                        ((s16 *)ovl_18b8824_81898EBC_PTR_AT(global_page, 0x14A8))[0x44] << 16;
                    ovl_18b8824_81898EBC_S32_AT((u8 *)target_pos, 8) = fallback_value;
                    state->state = 6;
                } else if ((func_800A5690() << 16) == 0) {
                    s32 fallback_value;

                    fallback_value =
                        ((s16 *)ovl_18b8824_81898EBC_PTR_AT(global_page, 0x14A8))[0x44] << 16;
                    ovl_18b8824_81898EBC_S32_AT((u8 *)target_pos, 8) = fallback_value;
                    state->state = 6;
                } else {
                    if ((ovl_18b8824_81898EBC_U16_AT(owner_data, 0x1E) | 0x2000) != 0) {
                        state->status = 1;
                    } else {
                        state->status = 2;
                    }
                    state->state++;
                }
            }

            {
                s32 delta_x;
                s32 raised_z;
                s32 delta_y;
                s32 delta_z;

                axis = 1;
                delta_ptr = (u8 *)&scratch + 2;
                delta_x = ovl_18b8824_81898EBC_S16_AT(target_pos, 2) - ovl_18b8824_81898EBC_S16_AT(motion, 2);
                delta_x = abs(delta_x);
                ovl_18b8824_81898EBC_probe[0] = delta_x;
                delta_y = ovl_18b8824_81898EBC_S16_AT(target_pos, 6) - ovl_18b8824_81898EBC_S16_AT(motion, 6);
                delta_y = abs(delta_y);
                ovl_18b8824_81898EBC_probe[1] = delta_y;
                raised_z = ovl_18b8824_81898EBC_S16_AT(motion, 0xA) + 160;
                delta_z = ovl_18b8824_81898EBC_S16_AT(target_pos, 0xA) - raised_z;
                delta_z = abs(delta_z);
                ovl_18b8824_81898EBC_probe[2] = delta_z;
                state->duration = delta_x;
            }
            do {
                s32 axis_delta;

                axis_delta = ovl_18b8824_81898EBC_S16_AT(delta_ptr, 24);
                if (state->duration < axis_delta) {
                    state->duration = ovl_18b8824_81898EBC_U16_AT(delta_ptr, 24);
                }
                axis++;
                delta_ptr += 2;
            } while (axis < 3);
            state->duration =
                (state->duration >> 4) + (state->duration >> 5);
            if (state->duration == 0) {
                state->duration = 1;
            }
            ovl_18b8824_81898EBC_S32_AT(motion, 0xC) =
                (ovl_18b8824_81898EBC_S32_AT(target_pos, 0) - ovl_18b8824_81898EBC_S32_AT(motion, 0)) / state->duration;
            {
                s32 current_y;
                s32 y_step;
                s32 move_frames;

                current_y = ovl_18b8824_81898EBC_S32_AT(motion, 4);
                y_step = ovl_18b8824_81898EBC_S32_AT(target_pos, 4) - current_y;
                move_frames = state->duration;
                y_step /= move_frames;
                ovl_18b8824_81898EBC_S32_AT(motion, 0x10) = y_step;
            }
            {
                s32 raised_z;
                s32 z_offset;

                z_offset = 0x00A00000;
                raised_z = ovl_18b8824_81898EBC_S32_AT(motion, 8) + z_offset;
                ovl_18b8824_81898EBC_S32_AT(motion, 0x14) =
                    (ovl_18b8824_81898EBC_S32_AT(target_pos, 8) - raised_z) / state->duration;
            }
            dungeonCreateASpriteRandomRotationCopiesInitialData(state, motion, state->duration);
            dungeonCreateASpriteRandomRotationCopiesInitialData(state, motion, state->duration);
            dungeonCreateASpriteRandomRotationCopiesInitialData(state, motion, state->duration);
            state->timer = 0;
            break;
        }

    case 2:
        ovl_18b8824_81898EBC_S32_AT(motion, 0) += ovl_18b8824_81898EBC_S32_AT(motion, 0xC);
        ovl_18b8824_81898EBC_S32_AT(motion, 4) += ovl_18b8824_81898EBC_S32_AT(motion, 0x10);
        ovl_18b8824_81898EBC_S32_AT(motion, 8) += ovl_18b8824_81898EBC_S32_AT(motion, 0x14);
        if (state->timer < state->duration) {
            break;
        }
        func_8002441C(state, motion);
        func_800A56E0(0x300);
        state->timer = 0;
        state->state++;
        break;

    case 3:
        if (state->timer < 0x10) {
            break;
        }
        func_800245CC(state, motion);
        state->timer = 0;
        state->state++;
        break;

    case 4:
        if (state->timer < 0x11) {
            break;
        }
        if (state->status != 0) {
            void *effect = dungeonCreateActorSpriteAtTile(state->status, state->x, state->y,
                                         state->z);
            s32 intensity;
            s16 clamped_intensity;
            u32 effect_id;
            s32 random_bits;

            func_80042640(effect, 52);
            random_bits = func_800A6D30();
            effect_id = ovl_18b8824_81898EBC_U8_AT(state, 9);
            intensity = effect_id >> 1;
            intensity += effect_id << 1;
            intensity += random_bits & 3;
            intensity += 16;
            clamped_intensity = intensity;
            if (intensity >= 256) {
                clamped_intensity = 255;
            }
            ovl_18b8824_81898EBC_U8_AT(effect, 0x28) = clamped_intensity;
            ovl_18b8824_81898EBC_U8_AT(effect, 0x29) = clamped_intensity;
        }
        state->timer = 0;
        state->state++;
        break;

    case 5:
        if (state->field_14 != 0) {
            break;
        }
        dungeonStatus.unk_0C = 0;
        ovl_18b8824_81898EBC_U16_AT(state, -2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        break;

    case 6:
        ovl_18b8824_81898EBC_S32_AT(motion, 0) += ovl_18b8824_81898EBC_S32_AT(motion, 0xC);
        ovl_18b8824_81898EBC_S32_AT(motion, 4) += ovl_18b8824_81898EBC_S32_AT(motion, 0x10);
        if (state->timer >= state->duration) {
            state->state = 5;
            state->timer = 0;
        }

    }

    state->field_14 = 0;
}
