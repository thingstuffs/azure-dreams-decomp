#include "shared/audio_commands.h"
/* Projectile movement and impact sequencing with projected textured sprite animation. */
#include "modules/dungeon_ovl_1858800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor.h"
#include "dungeon/effect/particle.h"
#include "dungeon/item.h"

#define HI16(v) (((s16 *)&(v))[1])
#define HI16U(v) (((u16 *)&(v))[1])





/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_1858800_entry)(ProjectileState *, ProjectileMotion *, ProjectileSprite *) =
    run_timed_sprite_projectile;

/* Updates a projectile effect, spawning particles and moving toward its target before impact and cleanup. */
void run_timed_sprite_projectile(ProjectileState *effect, ProjectileMotion *motion, ProjectileSprite *effect_sprite)
{
    ProjectileActor *caster;
    s32 particle_or_y;
    s32 sprite_or_x;
    ProjectileParticle *particle_data;
    s32 index_or_x;
    s32 tile_dx;
    s32 tile_dy;
    ProjectileTargetTransform target_pos;
    s16 launch_offset[3];
    ProjectileObject *caster_obj;
    ProjectileSprite *caster_sprite;
    ProjectileActor *target;
    s32 step_x;
    s32 step_y;
    s32 world_x;
    s32 range;
    s32 target_tile;
    s32 abs_dy;
    s32 world_y;
    s32 flags;
    s32 ground_z;
    s32 offset_y;
    s32 distance;
    s32 travel_frames;
    s32 state;

    u8 *direction_x = ((u8 *)dir_step_x);
    s32 direction_offset;
    caster = effect->caster;
    target = (ProjectileActor *)caster->unk_2A.u;
    caster_obj = (ProjectileObject *)((u8 *)caster - 0x20);
    caster_sprite = ((ProjectileObject *)((u8 *)caster - 0x20))->sprite;
    direction_offset = ((u32)target) >> 8;
    direction_offset &= 0xE;
    step_x = *(s16 *)(direction_x + direction_offset);
    step_y = *(s16 *)(((u8 *)dir_step_y) + direction_offset);

    if ((u32)(effect->phase.u - 1) < 3) {
        index_or_x = 9;
        do {
            particle_or_y = (s32)allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (particle_or_y != 0) {
                sprite_or_x = (s32)((ProjectileObject *)particle_or_y)->sprite;
                ((ProjectileObject *)particle_or_y)->update_callback = update_timed_sprite_effect;
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->position)->x.s =
                    motion->x.s + (((rand() & 0x3FF) - 511) << 9);
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->position)->y.s =
                    motion->y.s + (((rand() & 0x3FF) - 511) << 9);
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->position)->z.s =
                    motion->z.s + (((rand() & 0x3FF) - 511) << 9);
                if (effect->phase.s == 2) {
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->position)->velocity_x =
                        motion->velocity_x >> 2;
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->position)->velocity_y =
                        motion->velocity_y >> 2;
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->position)->x.s +=
                        (step_x << 21) -
                        (((step_x * effect->phase_ticks.s) << 20) / 12);
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->position)->y.s +=
                        (step_y << 21) -
                        (((step_y * effect->phase_ticks.s) << 20) / 12);
                    particle_data = (ProjectileParticle *)((u8 *)particle_or_y + 0x20);
                } else {
                    particle_data = (ProjectileParticle *)((u8 *)particle_or_y + 0x20);
                }
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->position)->velocity_z = -rand() << 1;
                ((ProjectileSprite *)sprite_or_x)->unk_1E = 0x1000;
                ((ProjectileSprite *)sprite_or_x)->unk_1C = 0x1000;
                ((ProjectileSprite *)sprite_or_x)->unk_14 |= 0xC;
                if (rand() & 1) {
                    ((ProjectileSprite *)sprite_or_x)->unk_14 |= 1;
                }
                *(s16 *)((u8 *)sprite_or_x + 0x10) = 96;
                *(void * *)((u8 *)sprite_or_x + 0x00) = secondary_sprite;
                ((ProjectileSprite *)sprite_or_x)->unk_08 = *(void **)(secondary_sprite + 4);
                ((ProjectileSprite *)sprite_or_x)->unk_04 = 0;
                ((ProjectileSprite *)sprite_or_x)->unk_05 = 0;
                ((ProjectileSprite *)sprite_or_x)->unk_0C.at00u.v = 0x3030C0;
                particle_data->unk_00 = effect;
                particle_data->unk_4C.u = 0;
                particle_data->unk_48 = rand() & 3;
                particle_data->unk_4A = index_or_x + 40;
                particle_data->unk_04 = (s8)caster->unk_72.u;
                particle_data->unk_06 = (s8)caster->unk_73.u;
            }
            index_or_x--;
        } while (index_or_x >= 0);
    }

    effect->travel_ticks.u = effect->travel_ticks.u - 1;
    state = effect->phase.s;
    switch (state) {
    case 0:
        if ((((AnimationFlags *)effect->launch_context)->unk_00 & 0x80) == 0) {
            return;
        }
        if (resolve_record_orientation_or_fallback(((ProjectileSprite *)caster_obj->sprite)->unk_08,
                          caster_obj->sprite, launch_offset, 0) == 0) {
            launch_offset[1] = 0;
            launch_offset[0] = 0;
            launch_offset[2] = (caster_sprite->unk_14 & 0x8000) ? -48 : 0;
        }
        motion->x.s = ((ProjectileMotion *)caster_obj->position)->x.s +
                              ((s32)launch_offset[0] << 16);
        motion->y.s = ((ProjectileMotion *)caster_obj->position)->y.s +
                              ((s32)launch_offset[1] << 16);
        motion->z.s = ((ProjectileMotion *)caster_obj->position)->z.s +
                              ((s32)launch_offset[2] << 16);
        register_node((u8 *)effect - 0x20, draw_animated_projectile_quads);
        range = (s16)get_definition_entry_byte_13(7);
        offset_y = caster_sprite->unk_24;
        target = (void *)scan_actor_along_heading(caster, offset_y,
                                       caster_sprite->unk_25,
                                       caster->unk_2A.s, range);
        caster->unk_60.p = target;
        if (target == 0) {
            distance = 0;
            tile_dy = distance;
            tile_dx = distance;
            while (distance < get_definition_entry_byte_13(7)) {
                index_or_x = (caster_sprite->unk_24 + tile_dx) * 64 + 32;
                offset_y = (caster_sprite->unk_25 + tile_dy) * 64 + 32;
                sprite_or_x = index_or_x & 0xFFFF;
                {
                    s32 probe_y;
                    direction_x = (u8 *)(sprite_or_x);
                    probe_y = offset_y & 0xFFFF;
                    ground_z = (s16)sample_terrain_surface_height((s32)direction_x, probe_y,
                                       (s16)(((ProjectileMotion *)caster_obj->position)->z.h.unk_0A - 128));
                }
                particle_or_y = offset_y & 0xFFFF;
                if ((s16)check_enabled_neighbor_height(sprite_or_x, particle_or_y, ground_z, caster->unk_2A.s,
                                  caster->unk_60.s) != 0) {
                    break;
                }
                tile_dy += step_y;
                distance++;
                tile_dx += step_x;
            }
            caster->unk_72.u = caster_sprite->unk_24 + step_x * distance;
            target_tile = caster_sprite->unk_25 + step_y * distance;
        } else {
            sprite_or_x = (s32)((ProjectileObject *)((u8 *)target - 0x20))->sprite;
            if ((((ProjectileSprite *)sprite_or_x)->unk_14 & 0x8000) && (effect_sprite->unk_14 & 0x8000)) {
                effect->phase.s = 3;
                return;
            }
            caster->unk_72.u = ((ProjectileSprite *)sprite_or_x)->unk_24;
            target_tile = ((ProjectileSprite *)sprite_or_x)->unk_25;
        }
        caster->unk_73.u = target_tile;
        target_tile = caster->unk_72.s;
        HI16(target_pos.x.v) = (target_tile << 6) + 32;
        target_tile = caster->unk_73.s;
        HI16(target_pos.y.v) = (target_tile << 6) + 32;
        HI16(target_pos.z.v) = (s16)sample_terrain_surface_height(HI16U(target_pos.x.v), HI16U(target_pos.y.v),
                                           (s16)(((ProjectileMotion *)caster_obj->position)->z.h.unk_0A - 48));
        if (HI16(target_pos.z.v) >= 512) {
            HI16(target_pos.z.v) = ((ProjectileMotion *)caster_obj->position)->z.h.unk_0A;
        }
        HI16(target_pos.z.v) -= 48;
        index_or_x = HI16(target_pos.x.v) - motion->x.h.unk_02;
        offset_y = HI16(target_pos.y.v) - motion->y.h.unk_06;
        distance = index_or_x;
        distance = abs(distance);
        abs_dy = offset_y;
        abs_dy = abs(abs_dy);
        if (distance < abs_dy) {
            distance = abs_dy;
        }
        travel_frames = distance / 8;
        travel_frames++;
        effect->travel_ticks.s = travel_frames;
        motion->velocity_x = (index_or_x << 16) / effect->travel_ticks.s;
        motion->velocity_y = (offset_y << 16) / effect->travel_ticks.s;
        motion->velocity_z = (target_pos.z.v - motion->z.s) /
                                 effect->travel_ticks.s;
        effect->phase_ticks.s = 8;
        effect->travel_ticks.u = effect->travel_ticks.u + effect->phase_ticks.u;
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        effect->phase.u = effect->phase.u + 1;
        return;

    case 1:
        effect->phase_ticks.s = effect->phase_ticks.s - 1;
        if (effect->phase_ticks.s > 0) {
            return;
        }
        effect->phase_ticks.s = 12;
        effect->phase.u = effect->phase.u + 1;
        return;

    case 2:
        effect->phase_ticks.s = effect->phase_ticks.s - 1;
        if (effect->phase_ticks.s > 0) {
            motion->velocity_x += step_x << 16;
            motion->velocity_y += step_y << 16;
        }
        motion->x.s += motion->velocity_x;
        motion->y.s += motion->velocity_y;
        motion->z.s += motion->velocity_z;
        world_x = motion->x.h.unk_02;
        if (world_x < 0) {
            world_x += 63;
        }
        if ((world_x >> 6) == (s8)caster->unk_72.u) {
            world_y = motion->y.h.unk_06;
            if (world_y < 0) {
                world_y += 63;
            }
            if ((world_y >> 6) == (s8)caster->unk_73.u) {
                effect->travel_ticks.u = 0;
            }
        }
        if (effect->travel_ticks.s > 0) {
            return;
        }
        effect->phase.u = effect->phase.u + 1;
        motion->velocity_x = step_x << 16;
        motion->velocity_y = step_y << 16;
        return;

    case 3:
        motion->x.s += motion->velocity_x;
        motion->y.s += motion->velocity_y;
        motion->z.s += motion->velocity_z;
        if (caster->unk_60.s != 0) {
            apply_attack_power_and_element_effects(caster->unk_60.p, 10, effect->spell_variant, 1,
                          caster->unk_2A.s, caster, 2);
        }
        effect->travel_ticks.s = 16;
        effect->phase.u = effect->phase.u + 1;
        return;

    case 4:
        unlink_node((u8 *)effect - 0x20);
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        effect->phase.u = effect->phase.u + 1;
        return;

    case 5:
        flags = effect->child_flags;
        if (flags & 0x8000) {
            effect->child_flags = flags & ~0x8000;
            return;
        }
        if (effect->travel_ticks.s > 0) {
            return;
        }
        g_dungeon_status.active_actor = 0;
        ((ObjectStatusPrefix *)((u8 *)effect - 0x20))->unk_1E |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
}
#include "modules/dungeon_ovl_1858800.h"
#include "common.h"
#include "shared/game_work.h"



/* Advance the animation and enqueue a textured quad at the projected position. */
s32 draw_animated_projectile_quads(RenderRecord *render_record, EntityRec *position)
{
    SVECTOR world_point;
    s16 screen[4];
    GameWork *render_state = &g_game_work;
    s16 *screen_base = screen;
    s32 half_width;
    s32 *projection_out = &half_width;
    RenderRecord *frame_record;
    u32 depth;
    s32 endpoint;
    s32 height;
    POLY_FT4 *poly;

next_record:
    world_point.x = (u16)position->x.w.i;
    frame_record = render_record;
    world_point.y = (u16)position->y.w.i;
    world_point.z = (u16)position->z.w.i - 14;

    for (endpoint = 0; endpoint < 2; endpoint++) {
        depth = RotTransPers(&world_point, &screen_base[endpoint * 2], projection_out, projection_out) - 8;
        world_point.z += 28;
    }

    height = screen[1] - screen[3];
    if (++frame_record->frame >= 12) {
        frame_record->frame = 8;
    }

    if (depth < 480) {
        u8 tex_u;
        s32 tex_v;
        s32 ot_offset;

        poly = (POLY_FT4 *)((RenderContext *)render_state->draw_buffer)->next_prim;
        ((RenderContext *)render_state->draw_buffer)->next_prim = (u8 *)poly + sizeof(POLY_FT4);
        *(u32 *)&poly->r0 = 0x00808080;
        SetPolyFT4(poly);
        SetSemiTrans(poly, 1);
        poly->tpage = GetTPage(0, 1, 0x2C0, 0x100);
        poly->clut = GetClut(0, 0x1F8);

        half_width = height >> 1;
        poly->x0 = poly->x1 = screen[0] + (u16)half_width;
        poly->x2 = poly->x3 = screen[0] - (u16)half_width;
        poly->y0 = poly->y2 = screen[1];
        poly->y1 = poly->y3 = screen[3];

        tex_u = frame_record->frame;
        ot_offset = depth << 2;
        tex_u = (tex_u & 3) << 5;
        poly->u0 = poly->u1 = tex_u;
        poly->u2 = poly->u3 = tex_u + 31;
        tex_v = ((s16)frame_record->frame >> 2) * 32;
        poly->v0 = poly->v2 = tex_v - 128;
        poly->v1 = poly->v3 = tex_v - 97;

        poly->tag = (poly->tag & 0xFF000000) |
                    (*(u32 *)((u8 *)((RenderContext *)render_state->draw_buffer) + 0xB0 + ot_offset) &
                     0x00FFFFFF);
        *(u32 *)((u8 *)((RenderContext *)render_state->draw_buffer) + 0xB0 + ot_offset) =
            (*(u32 *)((u8 *)((RenderContext *)render_state->draw_buffer) + 0xB0 + ot_offset) & 0xFF000000) |
            ((u32)poly & 0x00FFFFFF);
    }

    position = *(void **)((u8 *)render_record - 8);
    if (position != 0) {
        render_record = (RenderRecord *)((u8 *)position + 0x20);
        position = *(void **)((u8 *)position + 8);
        goto next_record;
    }
    return 0;
}

/* MECHANISM: Separate stack screen/pointer bases force the retail 0x50 frame and s7/s4 roles.
   A 40-byte FT4 plus uncached OT re-addressing restores the body length and reloads.
   The record walk is a loop whose top is the first statement after the prologue (retail
   word 15, the `j 0x80024934` back edge at word 137); the projection loop must index through
   `screen_base`, not through `screen` directly, or gcc materialises the array address again
   (`addiu $s0,$sp,0x18`) where retail copies the base register (`move $s0,$s7`). */
#include "modules/dungeon_ovl_1858800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"



/* Updates effect motion and advances its timed sprite animation. */
void update_timed_sprite_effect(void *effect, void *motion, void *sprite) {
    s32 state;
    s32 rounded_x;
    s32 rounded_y;
    s32 vel_y;
    s32 vel_z;
    s32 pos_x;
    s32 vel_x;
    s32 sprite_word;
    s32 timer_shift;
    u8 red_level;
    s32 timer;
    u16 sprite_scale;
    u8 green_blue;
    ProjectileOwnerFlags *owner;

    pos_x = ((ProjectileMotion *)motion)->x.s;
    vel_x = ((ProjectileMotion *)motion)->velocity_x;
    vel_y = ((ProjectileMotion *)motion)->velocity_y;
    vel_z = ((ProjectileMotion *)motion)->velocity_z;
    ((ProjectileMotion *)motion)->x.s = pos_x + vel_x;
    ((ProjectileMotion *)motion)->y.s = (s32) (((ProjectileMotion *)motion)->y.s + vel_y);
    ((ProjectileMotion *)motion)->z.s = (s32) (((ProjectileMotion *)motion)->z.s + vel_z);
    owner = ((ProjectileParticle *)effect)->unk_00;
    owner->unk_10 = (s32) (owner->unk_10 | 0x8000);
    rounded_x = ((ProjectileMotion *)motion)->x.h.unk_02;
    if ((rounded_x / 64) == ((ProjectileParticle *)effect)->unk_04) {
        rounded_y = ((ProjectileMotion *)motion)->y.h.unk_06;
        if ((rounded_y / 64) == ((ProjectileParticle *)effect)->unk_06) {
            ((ProjectileMotion *)motion)->velocity_z = 0;
            ((ProjectileMotion *)motion)->velocity_y = 0;
            ((ProjectileMotion *)motion)->velocity_x = 0;
        }
    }
    state = ((ProjectileParticle *)effect)->unk_4C.s;
    timer = ((ProjectileParticle *)effect)->unk_48 - 1;
    ((ProjectileParticle *)effect)->unk_48 = timer;
    switch (state) {
    case 0:
        timer_shift = timer << 0x10;
        if (timer_shift > 0) {
            return;
        }
        register_node(effect - 0x20, project_sprite_chain);
        ((ProjectileParticle *)effect)->unk_4C.u = ((ProjectileParticle *)effect)->unk_4C.u + 1;
        return;
    case 1:
        advance_sprite_animation_and_textures(sprite);
        if (((ProjectileSprite *)sprite)->unk_14 & 0x6000) {
            ((ProjectileSprite *)sprite)->unk_04 = 0;
            ((ProjectileSprite *)sprite)->unk_05 = 0;
        }
        if (((ProjectileSprite *)sprite)->unk_0C.at00.v <= ((ProjectileParticle *)effect)->unk_4A) {
            ((ProjectileMotion *)motion)->velocity_x = (s32) (((ProjectileMotion *)motion)->velocity_x * 5);
            ((ProjectileMotion *)motion)->velocity_y = (s32) (((ProjectileMotion *)motion)->velocity_y * 5);
            ((ProjectileMotion *)motion)->velocity_z = (s32) (((ProjectileMotion *)motion)->velocity_z * 8);
            ((ProjectileSprite *)sprite)->unk_1E = 0xC00U;
            ((ProjectileSprite *)sprite)->unk_1C = 0xC00U;
            ((ProjectileSprite *)sprite)->unk_0C.at00u.v = ((ProjectileSprite *)sprite)->unk_0C.at00u.v * 4;
            if (((ProjectileParticle *)effect)->unk_48 & 1) {
                ((ProjectileSprite *)sprite)->unk_00 = shared_sprite_entries;
                sprite_word = ((SpriteSourceEntry *)shared_sprite_entries)->source;
            } else {
                ((ProjectileSprite *)sprite)->unk_00 = &timed_projectile_sprite_entries;
                sprite_word = timed_projectile_sprite_entries.source;
            }
            ((ProjectileSprite *)sprite)->unk_04 = 0;
            ((ProjectileSprite *)sprite)->unk_05 = 0;
            ((ProjectileSprite *)sprite)->unk_08 = sprite_word;
            ((ProjectileParticle *)effect)->unk_4C.u = ((ProjectileParticle *)effect)->unk_4C.u + 1;
        } else {
            sprite_scale = ((ProjectileSprite *)sprite)->unk_1E - 0x200;
            ((ProjectileSprite *)sprite)->unk_1E = sprite_scale;
            ((ProjectileSprite *)sprite)->unk_1C = sprite_scale;
            ((ProjectileSprite *)sprite)->unk_0C.at00.v = (u8) (((ProjectileSprite *)sprite)->unk_0C.at00.v
                - (u8) ((ProjectileParticle *)effect)->unk_4A);
            green_blue = ((ProjectileSprite *)sprite)->unk_0C.at02.v - ((s32) ((u16) ((ProjectileParticle *)effect)->unk_4A
                << 0x10) >> 0x12);
            ((ProjectileSprite *)sprite)->unk_0C.at02.v = green_blue;
            ((ProjectileSprite *)sprite)->unk_0C.at01.v = green_blue;
        }
                        /* fall through */
    case 2:
        advance_sprite_animation_and_textures(sprite);
        if (((ProjectileSprite *)sprite)->unk_14 & 0x6000) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((EffectStatusPrefix *)effect)[-1].unk_00 | NODE_REMOVE);
            object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        }
        break;
    default:
        return;
    }
}
/* Historic per-row note: The natural 0x20 frame follows from three held arguments and explicit state CFG labels.
   Zero-arg noreturn dispatchers plus a guarded $v0 tail-slot pointer reproduce all five retail tails.
   Volatile ordered initial loads, direct scalar RMWs, and a comparison-local memory fence close scheduling. */
