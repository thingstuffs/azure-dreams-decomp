#include "modules/dungeon_ovl_1858800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

#define HI16(v) (((s16 *)&(v))[1])
#define HI16U(v) (((u16 *)&(v))[1])





/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_1858800_entry)(ProjectileState *, ProjectileMotion *, ProjectileSprite *) =
    func_80024020;

/* Updates a projectile effect, spawning particles and moving toward its target before impact and cleanup. */
void func_80024020(ProjectileState *effect, ProjectileMotion *motion, ProjectileSprite *effect_sprite)
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
    caster = effect->unk_00;
    target = (ProjectileActor *)caster->unk_2A.u;
    caster_obj = (ProjectileObject *)((u8 *)caster - 0x20);
    caster_sprite = ((ProjectileObject *)((u8 *)caster - 0x20))->unk_0C;
    direction_offset = ((u32)target) >> 8;
    direction_offset &= 0xE;
    step_x = *(s16 *)(direction_x + direction_offset);
    step_y = *(s16 *)(((u8 *)dir_step_y) + direction_offset);

    if ((u32)(effect->unk_0A.u - 1) < 3) {
        index_or_x = 9;
        do {
            particle_or_y = (s32)allocate_list_node(0x312, ((u8 *)(&D_80083498)));
            if (particle_or_y != 0) {
                sprite_or_x = (s32)((ProjectileObject *)particle_or_y)->unk_0C;
                ((ProjectileObject *)particle_or_y)->unk_10 = update_timed_sprite_effect;
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_00.s =
                    motion->unk_00.s + (((func_80069EF8() & 0x3FF) - 511) << 9);
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_04.s =
                    motion->unk_04.s + (((func_80069EF8() & 0x3FF) - 511) << 9);
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_08.s =
                    motion->unk_08.s + (((func_80069EF8() & 0x3FF) - 511) << 9);
                if (effect->unk_0A.s == 2) {
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_0C =
                        motion->unk_0C >> 2;
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_10 =
                        motion->unk_10 >> 2;
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_00.s +=
                        (step_x << 21) -
                        (((step_x * effect->unk_0C.s) << 20) / 12);
                    ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_04.s +=
                        (step_y << 21) -
                        (((step_y * effect->unk_0C.s) << 20) / 12);
                    particle_data = (ProjectileParticle *)((u8 *)particle_or_y + 0x20);
                } else {
                    particle_data = (ProjectileParticle *)((u8 *)particle_or_y + 0x20);
                }
                ((ProjectileMotion *)((ProjectileObject *)particle_or_y)->unk_08)->unk_14 = -func_80069EF8() << 1;
                ((ProjectileSprite *)sprite_or_x)->unk_1E = 0x1000;
                ((ProjectileSprite *)sprite_or_x)->unk_1C = 0x1000;
                ((ProjectileSprite *)sprite_or_x)->unk_14 |= 0xC;
                if (func_80069EF8() & 1) {
                    ((ProjectileSprite *)sprite_or_x)->unk_14 |= 1;
                }
                *(s16 *)((u8 *)sprite_or_x + 0x10) = 96;
                *(void * *)((u8 *)sprite_or_x + 0x00) = D_800DEA68;
                ((ProjectileSprite *)sprite_or_x)->unk_08 = *(void **)(D_800DEA68 + 4);
                ((ProjectileSprite *)sprite_or_x)->unk_04 = 0;
                ((ProjectileSprite *)sprite_or_x)->unk_05 = 0;
                ((ProjectileSprite *)sprite_or_x)->unk_0C.at00u.v = 0x3030C0;
                particle_data->unk_00 = effect;
                particle_data->unk_4C.u = 0;
                particle_data->unk_48 = func_80069EF8() & 3;
                particle_data->unk_4A = index_or_x + 40;
                particle_data->unk_04 = (s8)caster->unk_72.u;
                particle_data->unk_06 = (s8)caster->unk_73.u;
            }
            index_or_x--;
        } while (index_or_x >= 0);
    }

    effect->unk_50.u = effect->unk_50.u - 1;
    state = effect->unk_0A.s;
    switch (state) {
    case 0:
        if ((((AnimationFlags *)effect->unk_04)->unk_00 & 0x80) == 0) {
            return;
        }
        if (resolve_record_orientation_or_fallback(((ProjectileSprite *)caster_obj->unk_0C)->unk_08,
                          caster_obj->unk_0C, launch_offset, 0) == 0) {
            launch_offset[1] = 0;
            launch_offset[0] = 0;
            launch_offset[2] = (caster_sprite->unk_14 & 0x8000) ? -48 : 0;
        }
        motion->unk_00.s = ((ProjectileMotion *)caster_obj->unk_08)->unk_00.s +
                              ((s32)launch_offset[0] << 16);
        motion->unk_04.s = ((ProjectileMotion *)caster_obj->unk_08)->unk_04.s +
                              ((s32)launch_offset[1] << 16);
        motion->unk_08.s = ((ProjectileMotion *)caster_obj->unk_08)->unk_08.s +
                              ((s32)launch_offset[2] << 16);
        register_node((u8 *)effect - 0x20, func_800248F8);
        range = (s16)get_definition_entry_byte_13(7);
        offset_y = caster_sprite->unk_24;
        target = (void *)scan_monster_along_heading(caster, offset_y,
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
                                       (s16)(((ProjectileMotion *)caster_obj->unk_08)->unk_08.h.unk_0A - 128));
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
            sprite_or_x = (s32)((ProjectileObject *)((u8 *)target - 0x20))->unk_0C;
            if ((((ProjectileSprite *)sprite_or_x)->unk_14 & 0x8000) && (effect_sprite->unk_14 & 0x8000)) {
                effect->unk_0A.s = 3;
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
                                           (s16)(((ProjectileMotion *)caster_obj->unk_08)->unk_08.h.unk_0A - 48));
        if (HI16(target_pos.z.v) >= 512) {
            HI16(target_pos.z.v) = ((ProjectileMotion *)caster_obj->unk_08)->unk_08.h.unk_0A;
        }
        HI16(target_pos.z.v) -= 48;
        index_or_x = HI16(target_pos.x.v) - motion->unk_00.h.unk_02;
        offset_y = HI16(target_pos.y.v) - motion->unk_04.h.unk_06;
        distance = index_or_x;
        distance = abs(distance);
        abs_dy = offset_y;
        abs_dy = abs(abs_dy);
        if (distance < abs_dy) {
            distance = abs_dy;
        }
        travel_frames = distance / 8;
        travel_frames++;
        effect->unk_50.s = travel_frames;
        motion->unk_0C = (index_or_x << 16) / effect->unk_50.s;
        motion->unk_10 = (offset_y << 16) / effect->unk_50.s;
        motion->unk_14 = (target_pos.z.v - motion->unk_08.s) /
                                 effect->unk_50.s;
        effect->unk_0C.s = 8;
        effect->unk_50.u = effect->unk_50.u + effect->unk_0C.u;
        play_sound_if_enabled(0x300);
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 1:
        effect->unk_0C.s = effect->unk_0C.s - 1;
        if (effect->unk_0C.s > 0) {
            return;
        }
        effect->unk_0C.s = 12;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 2:
        effect->unk_0C.s = effect->unk_0C.s - 1;
        if (effect->unk_0C.s > 0) {
            motion->unk_0C += step_x << 16;
            motion->unk_10 += step_y << 16;
        }
        motion->unk_00.s += motion->unk_0C;
        motion->unk_04.s += motion->unk_10;
        motion->unk_08.s += motion->unk_14;
        world_x = motion->unk_00.h.unk_02;
        if (world_x < 0) {
            world_x += 63;
        }
        if ((world_x >> 6) == (s8)caster->unk_72.u) {
            world_y = motion->unk_04.h.unk_06;
            if (world_y < 0) {
                world_y += 63;
            }
            if ((world_y >> 6) == (s8)caster->unk_73.u) {
                effect->unk_50.u = 0;
            }
        }
        if (effect->unk_50.s > 0) {
            return;
        }
        effect->unk_0A.u = effect->unk_0A.u + 1;
        motion->unk_0C = step_x << 16;
        motion->unk_10 = step_y << 16;
        return;

    case 3:
        motion->unk_00.s += motion->unk_0C;
        motion->unk_04.s += motion->unk_10;
        motion->unk_08.s += motion->unk_14;
        if (caster->unk_60.s != 0) {
            apply_attack_power_and_element_effects(caster->unk_60.p, 10, effect->unk_09, 1,
                          caster->unk_2A.s, caster, 2);
        }
        effect->unk_50.s = 16;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 4:
        unlink_node((u8 *)effect - 0x20);
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        effect->unk_0A.u = effect->unk_0A.u + 1;
        return;

    case 5:
        flags = effect->unk_10;
        if (flags & 0x8000) {
            effect->unk_10 = flags & ~0x8000;
            return;
        }
        if (effect->unk_50.s > 0) {
            return;
        }
        g_dungeon_status.unk_0C = 0;
        ((ObjectStatusPrefix *)((u8 *)effect - 0x20))->unk_1E |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }
}
#include "modules/dungeon_ovl_1858800.h"
#include "common.h"
#include "shared/game_work.h"



/* Advance the animation and enqueue a textured quad at the projected position. */
s32 func_800248F8(RenderRecord *render_record, EntityRec *position)
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
        depth = func_80065420(&world_point, &screen_base[endpoint * 2], projection_out, projection_out) - 8;
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

        poly = (POLY_FT4 *)((RenderContext *)render_state->unk_000)->next_prim;
        ((RenderContext *)render_state->unk_000)->next_prim = (u8 *)poly + sizeof(POLY_FT4);
        *(u32 *)&poly->r0 = 0x00808080;
        func_800666F4(poly);
        func_80066640(poly, 1);
        poly->tpage = func_80066460(0, 1, 0x2C0, 0x100);
        poly->clut = func_8006649C(0, 0x1F8);

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
                    (*(u32 *)((u8 *)((RenderContext *)render_state->unk_000) + 0xB0 + ot_offset) &
                     0x00FFFFFF);
        *(u32 *)((u8 *)((RenderContext *)render_state->unk_000) + 0xB0 + ot_offset) =
            (*(u32 *)((u8 *)((RenderContext *)render_state->unk_000) + 0xB0 + ot_offset) & 0xFF000000) |
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
    void *owner;

    pos_x = ((ProjectileMotion *)motion)->unk_00.s;
    vel_x = ((ProjectileMotion *)motion)->unk_0C;
    vel_y = ((ProjectileMotion *)motion)->unk_10;
    vel_z = ((ProjectileMotion *)motion)->unk_14;
    ((ProjectileMotion *)motion)->unk_00.s = pos_x + vel_x;
    ((ProjectileMotion *)motion)->unk_04.s = (s32) (((ProjectileMotion *)motion)->unk_04.s + vel_y);
    ((ProjectileMotion *)motion)->unk_08.s = (s32) (((ProjectileMotion *)motion)->unk_08.s + vel_z);
    owner = ((ProjectileParticle *)effect)->unk_00;
    ((ProjectileOwnerFlags *)owner)->unk_10 = (s32) (((ProjectileOwnerFlags *)owner)->unk_10 | 0x8000);
    rounded_x = ((ProjectileMotion *)motion)->unk_00.h.unk_02;
    if ((rounded_x / 64) == ((ProjectileParticle *)effect)->unk_04) {
        rounded_y = ((ProjectileMotion *)motion)->unk_04.h.unk_06;
        if ((rounded_y / 64) == ((ProjectileParticle *)effect)->unk_06) {
            ((ProjectileMotion *)motion)->unk_14 = 0;
            ((ProjectileMotion *)motion)->unk_10 = 0;
            ((ProjectileMotion *)motion)->unk_0C = 0;
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
        func_800478B8(sprite);
        if (((ProjectileSprite *)sprite)->unk_14 & 0x6000) {
            ((ProjectileSprite *)sprite)->unk_04 = 0;
            ((ProjectileSprite *)sprite)->unk_05 = 0;
        }
        if (((ProjectileSprite *)sprite)->unk_0C.at00.v <= ((ProjectileParticle *)effect)->unk_4A) {
            ((ProjectileMotion *)motion)->unk_0C = (s32) (((ProjectileMotion *)motion)->unk_0C * 5);
            ((ProjectileMotion *)motion)->unk_10 = (s32) (((ProjectileMotion *)motion)->unk_10 * 5);
            ((ProjectileMotion *)motion)->unk_14 = (s32) (((ProjectileMotion *)motion)->unk_14 * 8);
            ((ProjectileSprite *)sprite)->unk_1E = 0xC00U;
            ((ProjectileSprite *)sprite)->unk_1C = 0xC00U;
            ((ProjectileSprite *)sprite)->unk_0C.at00u.v = ((ProjectileSprite *)sprite)->unk_0C.at00u.v * 4;
            if (((ProjectileParticle *)effect)->unk_48 & 1) {
                ((ProjectileSprite *)sprite)->unk_00 = D_800DEC70;
                sprite_word = ((SpriteSourceEntry *)D_800DEC70)->unk_04;
            } else {
                ((ProjectileSprite *)sprite)->unk_00 = &D_800DED28;
                sprite_word = ((SpriteSourceEntry *)(&D_800DED28))->unk_04;
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
        func_800478B8(sprite);
        if (((ProjectileSprite *)sprite)->unk_14 & 0x6000) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((EffectStatusPrefix *)effect)[-1].unk_00 | 0x8000);
            object_flag_block.flags = object_flag_block.flags | 0x8000;
        }
        break;
    default:
        return;
    }
}
/* Historic per-row note: The natural 0x20 frame follows from three held arguments and explicit state CFG labels.
   Zero-arg noreturn dispatchers plus a guarded $v0 tail-slot pointer reproduce all five retail tails.
   Volatile ordered initial loads, direct scalar RMWs, and a comparison-local memory fence close scheduling. */
