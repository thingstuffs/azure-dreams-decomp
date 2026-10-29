#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/beldo_large.h"
#include "shared/tile_object.h"
#include "sdk/libc.h"

typedef struct {
    u8 bytes[8];
} Copy8 __attribute__((packed));



#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))

extern void draw_transformed_sprite_with_clip_rect(void *, void *, void *, s32, s32);
extern void create_offset_particle_effect();
extern void spawn_directional_projectile_effect();


extern Copy8 D_80164A4C;
extern u8 *beldo_actor_nodes;

/* Update a staged particle effect, ramping emission and brightness before fading out. */
/* Brightens the player sprite while ramping particle emission, then emits projectile bursts, restores
 * gray, and ends the action. */
void update_dungeon_actor_behavior(void *effect) {
    u16 blit_data[8];
    u8 *burst_context;
    u8 *render_state;
    TileObject *particle;
    s32 timer_snapshot;
    ActorRecord * actor;
    s16 state;
    u16 old_timer;
    u16 next_state;
    u8 shade;
    u8 particle_level;
    u32 render_flags;
    s32 burst_x;
    s32 burst_y;
    s32 burst_kind;
    s32 ramp_count;
    s32 ramp_x;
    s32 ramp_y;
    s32 late_count;
    s32 late_x;
    s32 late_y;
    s32 early_count;
    s32 early_x;
    s32 early_y;
    u32 flag_mask;
    s32 enabled;

    *(Copy8 *)&blit_data[4] = D_80164A4C;
    burst_context = ((u8 *)(&scene_object_list_anchor));
    state = S16_AT(effect, 0x12);
    render_state = burst_context + 0x20;
    enabled = 1;

    switch (state) {
    case 0:
        actor = dungeon_actor_ring_anchor;
        if (actor->action_id.u != 0x11) {
            return;
        }
        actor->action_timer.u += 0x3C;
        U16_AT(effect, 0x18) = 0;
        U16_AT(effect, 0x12)++;
        S8_AT(actor, 0xA8) = enabled;
        beldo_actor_nodes[0x47] = 0;
        return;
    case 1:
        U16_AT(effect, 0x18)++;
        if (S16_AT(effect, 0x18) == 6) {
            blit_data[0] = blit_data[4] + ((s16)blit_data[6] >> 1);
            blit_data[1] = blit_data[5] + 0x30;
            draw_transformed_sprite_with_clip_rect(primary_actor_record, &blit_data[4], blit_data, 1, state);
        }
        if (S16_AT(effect, 0x18) >= 7) {
            if ((U16_AT(effect, 0x18) & 3) == 3) {
                burst_kind = (rand() & 0xFF) | 0x80;
                burst_x = (s16)((rand() & 0x7F) - 0x40);
                burst_y = (s16)((rand() & 0x7F) - 0x40);
                create_timed_offset_motion_effect(burst_context, burst_kind, burst_x, burst_y,
                    (s16)((rand() & 0x7F) - 0x40));
            }
        }
        flag_mask = 0x10000000;
        particle = &reference_tile_object;
        particle_level = particle->primitive_color.parts.color_r;
        U32_AT(render_state, 0x1C) |= flag_mask;
        if (particle_level < 0xFC) {
            shade = particle->primitive_color.parts.color_b + 3;
            particle->primitive_color.parts.color_b = shade;
            particle->primitive_color.parts.color_g = shade;
            particle->primitive_color.parts.color_r = shade;
        }

        timer_snapshot = S16_AT(effect, 0x18);
        ramp_count = 0;
        if (timer_snapshot >= 10) {
            ramp_count = 1;
            if (timer_snapshot >= 20) {
                ramp_count = 2;
                if (timer_snapshot >= 30) {
                    ramp_count = 3;
                    if (timer_snapshot >= 40) {
                        ramp_count = 5;
                        if (timer_snapshot < 50) {
                            ramp_count = 4;
                        }
                    }
                }
            }
        }
        timer_snapshot = S16_AT(effect, 0x18);
        if (ramp_count > 0) {
            /* BYTES: retail evidence: the test's operands survive (the arm compiled away); reconstructed as a conditional update of a local nothing reads in the retail build - any dead local set reproduces the bytes (lane r118_fable_f4; decision 45, docs/evidence/r97_decisions.md) */
            if (timer_snapshot) {
                next_state = 0;
            }
            do {
                ramp_count--;
                ramp_x = (s16)((rand() & 0x3F) - 0x20);
                ramp_y = (s16)((rand() & 0x3F) - 0x20);
                create_offset_particle_effect(((u8 *)(&view_reference_entity)), ramp_x, ramp_y,
                    (s16)(-(rand() & 0x3F) - 0x10));
            } while (ramp_count > 0);
        }
        if (S16_AT(effect, 0x18) >= 0x3C) {
            next_state = U16_AT(effect, 0x12);
            U16_AT(effect, 0x18) = 0;
            U16_AT(effect, 0x12) = next_state + 1;
        }
        return;
    case 2:
        old_timer = U16_AT(effect, 0x18);
        U16_AT(effect, 0x18) = old_timer + 1;
        if ((u32)(old_timer - 0xE) < 9U) {
            late_count = 8;
            do {
                late_count--;
                late_x = (s16)((rand() & 0x3F) - 0x20);
                late_y = (s16)((rand() & 0x3F) - 0x20);
                spawn_directional_projectile_effect(((u8 *)(&view_reference_entity)), late_x, late_y,
                    (s16)(-(rand() & 0x1F) - 0x18));
            } while (late_count > 0);
        }
        if (S16_AT(effect, 0x18) < 0xE) {
            early_count = 5;
            do {
                early_count--;
                early_x = (s16)((rand() & 0x3F) - 0x20);
                early_y = (s16)((rand() & 0x3F) - 0x20);
                create_offset_particle_effect(((u8 *)(&view_reference_entity)), early_x, early_y,
                    (s16)(-(rand() & 0x3F) - 0x10));
            } while (early_count > 0);
        } else {
        }
        if (reference_tile_object.primitive_color.parts.color_r >= 0x81) {
            shade = reference_tile_object.primitive_color.parts.color_b - 3;
            reference_tile_object.primitive_color.parts.color_b = shade;
            reference_tile_object.primitive_color.parts.color_g = shade;
            reference_tile_object.primitive_color.parts.color_r = shade;
            return;
        }
        render_flags = U32_AT(render_state, 0x1C);
        reference_tile_object.primitive_color.parts.color_b = 0x80;
        reference_tile_object.primitive_color.parts.color_g = 0x80;
        reference_tile_object.primitive_color.parts.color_r = 0x80;
        U32_AT(render_state, 0x1C) = render_flags & 0xEFFFFFFF;

        next_state = U16_AT(effect, 0x12);
        U16_AT(effect, 0x12) = next_state + 1;
        return;
    case 3:
        g_dungeon_status.active_actor = 0;
        U16_AT(effect, -2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;

        return;
    default:
        return;
    }
}
