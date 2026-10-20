#include "modules/dungeon_ovl_190681c.h"
#include "modules/dungeon_ovl_190681c.h"

void update_directional_actor_effect(u8 *effect, u8 *motion, void *context_arg) {
    u8 *actor;
    u8 *actor_data;
    u8 *actor_header;
    u8 *particle;
    u8 *render_data;
    u8 *particle_data;
    s32 count;
    s32 state;
    s32 tile_x;
    s32 tile_y;
    s32 distance;
    s16 offset[3];
    s32 original_count;
    s32 delta_y;
    s32 frames;
    s32 velocity_y;
    u8 *spawn_callback = D_800249DC;
    u8 *template_data = D_800DECF8;

    {
        actor = (u8 *)S32(effect, 0);
        original_count = U16(effect, 80);
        state = S16(effect, 10);
        count = original_count - 1;
    }
    actor_data = (u8 *)S32(actor, -20);
    actor_header = actor;
    actor_header -= 32;

    U16(effect, 80) = (u16)count;
    if (state > 0) {
        actor = (u8 *)S32(effect, 0);
        switch (state) {
        case 1:
            original_count = (s16)count;
            state = 20;
            count = state - original_count;
            break;
        case 2:
            count = 8;
            break;
        case 240:
        case 241:
            count = 8;
            break;
        default:
            count = -1;
            break;
        }
        distance = count;
        while (distance >= 0) {
            particle = (u8 *)allocate_list_node(786, ((u8 *)(&D_80083498)));
            if (particle != 0) {
                register_node(particle, project_sprite_chain);
                render_data = (u8 *)S32(particle, 12);
                S32(particle, 16) = (s32)spawn_callback;
                U16(S32(particle, 8), 2) = (u16)(U16(motion, 2) +
                                                 (func_80069EF8() & 0x1ff) - 256);
                U16(S32(particle, 8), 6) = (u16)(U16(motion, 6) +
                                                 (func_80069EF8() & 0x1ff) - 256);
                particle_data = particle + 32;
                U16(S32(particle, 8), 10) = (u16)(U16(motion, 10) +
                                                  (func_80069EF8() & 0xf) - 8);
                S32(particle_data, 28) = S32(motion, 0);
                S32(particle_data, 32) = S32(motion, 4);
                S32(particle_data, 36) = S32(motion, 8);
                S32(particle_data, 52) = S32(motion, 12);
                S32(particle_data, 56) = S32(motion, 16);
                S32(particle_data, 60) = S32(motion, 20);
                U16(particle_data, 72) = U16(effect, 80);

                {
                    s16 flags;
                    u8 *tpl;
                    S16(render_data, 30) = 4096;
                    S16(render_data, 28) = 4096;
                    S16(render_data, 16) = 32;
                    flags = U16(render_data, 20);
                    S32(render_data, 12) = 0x101010;
                    S32(render_data, 0) = (s32)template_data;
                    S16(render_data, 20) = flags | 0xc;
                    tpl = (u8 *)S32(render_data, 0);
                    S32(render_data, 8) = S32(tpl, 4);
                    U8(render_data, 4) = 0;
                    U8(render_data, 5) = 0;
                }
                S32(particle, 32) = (s32)effect;
                S16(particle_data, 76) = 0;
            }
            distance--;
        }
    }


    {
        s32 mode = S16(effect, 10);
        switch (mode) {
        case 0:
        {
            s32 target;
            s32 delta_x;
            s32 abs_y;
            if ((U16(S32(effect, 4), 0) & 0x80) != 0) {
                if (resolve_record_orientation_or_fallback(S32(S32(actor_header, 12), 8), S32(actor_header, 12), offset, 0) == 0) {
                    offset[1] = 0;
                    offset[0] = 0;
                    offset[2] = (U16(actor_data, 20) & 0x8000) ? -48 : 0;
                }
                target = scan_monster_along_heading(actor, U8(actor_data, 36), U8(actor_data, 37), S16(actor, 42),
                                       (s16)get_definition_entry_byte_13(36));
                S32(actor, 96) = target;
                if (target == 0) {
                    U8(actor, 114) = U8(actor_data, 36);
                    U8(actor, 115) = U8(actor_data, 37);
                } else {
                    render_data = (u8 *)S32(target, -20);
                    if ((U16(render_data, 20) & 0x8000) != 0) {
                        if ((U16(context_arg, 20) & 0x8000) != 0) {
                            U16(effect, 10) = 240;
                            return;
                        }
                    }
                    U8(actor, 114) = U8(render_data, 36);
                    U8(actor, 115) = U8(render_data, 37);
                }
                {
                    u8 *effect_header = effect - 32;
                    u8 *callback = handle_spawn_initialize_randomized_offset_parent;
                    S32(motion, 0) = S32(S32(actor_header, 8), 0) + ((s32)offset[0] << 16);
                    S32(motion, 4) = S32(S32(actor_header, 8), 4) + ((s32)offset[1] << 16);
                    S32(motion, 8) = S32(S32(actor_header, 8), 8) + ((s32)offset[2] << 16);
                    register_node(effect_header, callback);
                }
                delta_x = S8(actor, 114);
                delta_y = U8(actor_data, 36);
                abs_y = U8(actor_data, 37);
                delta_x -= delta_y;
                delta_y = S8(actor, 115);
                distance = abs(delta_x);
                delta_y -= abs_y;
                abs_y = abs(delta_y);
                if (distance < abs_y)
                    distance = abs_y;
                if (distance < 4)
                    distance = 4;
                frames = distance << 2;
                U16(effect, 80) = (u16)frames;
                abs_y = S8(actor, 114);
                delta_x = S16(motion, 2);
                abs_y <<= 6;
                distance = abs_y + 32;
                frames = (s16)frames;
                delta_x = distance - delta_x;
                delta_x /= frames;
                velocity_y = S8(actor, 115);
                velocity_y <<= 6;
                abs_y = velocity_y + 32;
                velocity_y = S16(motion, 6);
                state = delta_x << 16;
                S32(motion, 12) = state;
                delta_x = S16(effect, 80);
                velocity_y = abs_y - velocity_y;
                velocity_y /= delta_x;
                S32(motion, 16) = velocity_y << 16;
                tile_x = (S8(actor, 114) << 6) & 0xffc0;
                tile_y = (S8(actor, 115) << 6) & 0xffc0;
                distance = (s16)sample_terrain_surface_height(tile_x, tile_y, U16(S32(actor_header, 8), 10) - 48) - 192;
                {
                    s32 velocity_z;
                    s32 travel_frames;
                    velocity_z = S16(motion, 10);
                    travel_frames = S16(effect, 80);
                    velocity_z = (distance - velocity_z) / travel_frames;
                    S32(motion, 20) = velocity_z << 16;
                }
                U16(effect, 82) = 0;
                play_sound_if_enabled(768);
                U16(effect, 10) = (u16)(U16(effect, 10) + 1);
                return;
            }
            break;
        }

        case 1:
        {
            s16 frame_counter;
            if (S16(effect, 80) >= 0) {
                S32(motion, 0) += S32(motion, 12);
                S32(motion, 4) += S32(motion, 16);
                S32(motion, 8) += S32(motion, 20);
            }
            frame_counter = (u16)U16(effect, 82) + 1;
            U16(effect, 82) = (u16)frame_counter;
            if (frame_counter >= 8) {
                U16(effect, 82) = 4;
            }
            if (S16(effect, 80) <= 0 && S16(effect, 82) == 7) {
                U16(effect, 80) = 8;
                U16(effect, 10) = (u16)(U16(effect, 10) + 1);
                return;
            }
            break;
        }

        case 2:
        {
            u16 frame_counter = (u16)U16(effect, 82) + 1;
            U16(effect, 82) = frame_counter;
            if (S16(effect, 80) == mode) {
                if (S32(actor, 96) != 0) {
                    particle = (u8 *)allocate_list_node(770, ((u8 *)(&D_80083498)));
                    if (particle != 0) {
                        register_node(particle, D_80024C7C);
                        S32(particle, 16) = (s32)D_80024B60;
                        {
                            s32 coordinate = S8(actor, 114);
                            particle_data = particle + 32;
                            S16(particle_data, 12) = coordinate << 6;
                            coordinate = S8(actor, 115);
                            S16(particle_data, 14) = coordinate << 6;
                            S16(particle_data, 16) = U16(motion, 10);
                        }
                        S32(particle, 32) = (s32)effect;
                        S16(particle_data, 76) = 0;
                    }
                }
            }
            if (S16(effect, 80) <= 0) {
                if (S32(actor, 96) != 0) {
                    U16(effect, 10) = 240;
                    return;
                }
                unlink_node(effect - 32);
                U16(effect, 10) = 255;
                return;
            }
            break;
        }

        case 240:
            unlink_node(effect - 32);
            U16(effect, 80) = 10;
            func_800419EC(8, 16);
            U16(effect, 10) = (u16)(U16(effect, 10) + 1);
            return;

        case 241:
            copy_selected_table_pair(S32(actor, 96), S16(effect, 80));
            if (S16(effect, 80) == 6 && try_trigger_target_record_effect(S32(actor, 96), 4, actor) == 0 &&
                S32(actor, 96) != 0) {
                try_apply_effect_four_by_chance(S32(actor, 96), U8(D_800E3D68, 0) == 255 ? 255 : 16, 4);
            }
            if (S16(effect, 80) > 0)
                break;
            unlink_node(effect - 32);
            U16(effect, 10) = 255;
            return;

        case 255:
        {
            s32 effect_flags;
            effect_flags = S32(effect, 16);
            if ((effect_flags & 0x8000) != 0) {
                S32(effect, 16) = effect_flags & ~0x8000;
                return;
            } else {
                U16(effect, 80) = 10;
                U16(effect, 10) = (u16)(U16(effect, 10) + 1);
                return;
            }
        }

        case 256:
            if (S16(effect, 80) < 0) {
                g_dungeon_status.unk_0C = 0;
                U16(effect, -2) = (u16)(U16(effect, -2) | 0x8000);
                object_flag_block.flags |= 0x8000;
            }
            break;
        default:
            return;
        }
    }
}
