#include "common.h"
#include "shared/vector.h"
#include "shared/audio_commands.h"
#include "shared/object_links.h"
#include "shared/sprite_source.h"
#include "shared/object_node.h"
#include "records/Rec_func_800249DC_arg0.h"
#include "dungeon/effect/particle.h"

/* Callback body of the directional projectile; child callbacks mark activity
 * at +0x10 while the controller waits to retire. */
typedef struct DirectionalEffectWork {
    struct ActorRecord *owner;
    u16 *animation_flags;
    u8 pad_08[2];
    union { s16 s; u16 u; } state;
    u8 pad_0C[4];
    s32 child_flags;
    u8 pad_14[0x3C];
    union { s16 s; u16 u; } ticks_left;
    union { s16 s; u16 u; } frame;
} DirectionalEffectWork;
/* Directional particle travel, target impact geometry, and timed status effects. */
#include "shared/entity.h"
#include "shared/object_node.h"
#include "modules/dungeon_ovl_190681c.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/effect.h"
#include "dungeon/effect/motion.h"
#include "dungeon/effect/screen.h"

/* Two child callbacks share the parent word and phase offset. The moving
 * child reuses its callback's existing target/velocity record. */
typedef union DirectionalChildWork {
    DirectionalEffectWork *owner;
    struct {
        Rec_func_800249DC_arg0 motion;
        s16 state;
    } trail;
    UpdateDirectionalActorEffectBody impact;
} DirectionalChildWork;

typedef struct DirectionalChildNode {
    ObjectNodeHeader header;
    DirectionalChildWork work;
} DirectionalChildNode;

/* Moves a particle effect to a directional target, animates its impact, and attempts the target status
   effect. */
void update_directional_actor_effect(DirectionalEffectWork *effect, ObjectPosition *motion, void *context_arg) {
    ActorRecord *actor;
    SpriteFrameState *actor_data;
    ObjectNodeHeader *actor_header;
    DirectionalChildNode *particle;
    SpriteFrameState *render_data;
    DirectionalChildWork *particle_data;
    s32 count;
    s32 state;
    s32 tile_x;
    s32 tile_y;
    s32 distance;
    GteShortVector offset;
    s32 original_count;
    s32 delta_y;
    s32 frames;
    s32 velocity_y;
    u8 *spawn_callback = D_800249DC;
    u8 *template_data = fading_sprite_entries;

    {
        actor = effect->owner;
        original_count = effect->ticks_left.u;
        state = effect->state.s;
        count = original_count - 1;
    }
    actor_data = ((ObjectNodeHeader *)actor)[-1].sprite;
    actor_header = (ObjectNodeHeader *)actor - 1;

    effect->ticks_left.u = (u16)count;
    if (state > 0) {
        actor = effect->owner;
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
            particle = allocate_list_node(786, &scene_object_list_anchor.next);
            if (particle != 0) {
                register_node(particle, project_sprite_chain);
                render_data = particle->header.sprite;
                particle->header.update_callback = spawn_callback;
                particle->header.position->x.w.i = (u16)((u16)motion->x.w.i +
                                                 (rand() & 0x1ff) - 256);
                particle->header.position->y.w.i = (u16)((u16)motion->y.w.i +
                                                 (rand() & 0x1ff) - 256);
                particle_data = &particle->work;
                particle->header.position->z.w.i = (u16)((u16)motion->z.w.i +
                                                  (rand() & 0xf) - 8);
                particle_data->trail.motion.unk_1C = motion->x.v;
                particle_data->trail.motion.unk_20 = motion->y.v;
                particle_data->trail.motion.unk_24 = motion->z.v;
                particle_data->trail.motion.unk_34 = motion->velocity_x;
                particle_data->trail.motion.unk_38 = motion->velocity_y;
                particle_data->trail.motion.unk_3C = motion->velocity_z;
                particle_data->trail.motion.unk_48 = effect->ticks_left.u;

                {
                    s16 flags;
                    SpriteSourceEntry *tpl;
                    render_data->scale_y = 4096;
                    render_data->scale_x = 4096;
                    render_data->tpage_abr = 32;
                    flags = render_data->flags;
                    render_data->color.word = 0x101010;
                    render_data->unk_00 = template_data;
                    render_data->flags = flags | 0xc;
                    tpl = render_data->unk_00;
                    render_data->source = tpl->source;
                    render_data->unk_04 = 0;
                    render_data->frame_ticks = 0;
                }
                particle->work.owner = effect;
                particle_data->trail.state = 0;
            }
            distance--;
        }
    }

    {
        s32 mode = effect->state.s;
        switch (mode) {
        case 0:
        {
            void *target;
            s32 delta_x;
            s32 abs_y;
            if ((*effect->animation_flags & 0x80) != 0) {
                if (resolve_record_orientation_or_fallback(actor_header->sprite->source, actor_header->sprite, &offset, 0) == 0) {
                    offset.vy = 0;
                    offset.vx = 0;
                    offset.vz = (actor_data->flags & 0x8000) ? -48 : 0;
                }
                target = scan_actor_along_heading(actor, actor_data->tile_x, actor_data->tile_y, actor->facing,
                                       (s16)get_definition_entry_byte_13(36));
                actor->target = target;
                if (target == 0) {
                    actor->target_tile_x = actor_data->tile_x;
                    actor->target_tile_y = actor_data->tile_y;
                } else {
                    render_data = ((ObjectNodeHeader *)target)[-1].sprite;
                    if ((render_data->flags & 0x8000) != 0) {
                        if ((((SpriteFrameState *)context_arg)->flags & 0x8000) != 0) {
                            effect->state.u = 240;
                            return;
                        }
                    }
                    actor->target_tile_x = render_data->tile_x;
                    actor->target_tile_y = render_data->tile_y;
                }
                {
                    u8 *effect_header = (u8 *)effect - 32;
                    u8 *callback = project_linked_vertical_point_quads;
                    motion->x.v = actor_header->position->x.v + ((s32)offset.vx << 16);
                    motion->y.v = actor_header->position->y.v + ((s32)offset.vy << 16);
                    motion->z.v = actor_header->position->z.v + ((s32)offset.vz << 16);
                    register_node(effect_header, callback);
                }
                delta_x = actor->target_tile_x;
                delta_y = actor_data->tile_x;
                abs_y = actor_data->tile_y;
                delta_x -= delta_y;
                delta_y = actor->target_tile_y;
                distance = abs(delta_x);
                delta_y -= abs_y;
                abs_y = abs(delta_y);
                if (distance < abs_y)
                    distance = abs_y;
                if (distance < 4)
                    distance = 4;
                frames = distance << 2;
                effect->ticks_left.u = (u16)frames;
                abs_y = actor->target_tile_x;
                delta_x = motion->x.w.i;
                abs_y <<= 6;
                distance = abs_y + 32;
                frames = (s16)frames;
                delta_x = distance - delta_x;
                delta_x /= frames;
                velocity_y = actor->target_tile_y;
                velocity_y <<= 6;
                abs_y = velocity_y + 32;
                velocity_y = motion->y.w.i;
                state = delta_x << 16;
                motion->velocity_x = state;
                delta_x = effect->ticks_left.s;
                velocity_y = abs_y - velocity_y;
                velocity_y /= delta_x;
                motion->velocity_y = velocity_y << 16;
                tile_x = (actor->target_tile_x << 6) & 0xffc0;
                tile_y = (actor->target_tile_y << 6) & 0xffc0;
                distance = (s16)sample_terrain_surface_height(tile_x, tile_y, (u16)actor_header->position->z.w.i - 48) - 192;
                {
                    s32 velocity_z;
                    s32 travel_frames;
                    velocity_z = motion->z.w.i;
                    travel_frames = effect->ticks_left.s;
                    velocity_z = (distance - velocity_z) / travel_frames;
                    motion->velocity_z = velocity_z << 16;
                }
                effect->frame.u = 0;
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                effect->state.u = (u16)(effect->state.u + 1);
                return;
            }
            break;
        }

        case 1:
        {
            s16 frame_counter;
            if (effect->ticks_left.s >= 0) {
                motion->x.v += motion->velocity_x;
                motion->y.v += motion->velocity_y;
                motion->z.v += motion->velocity_z;
            }
            frame_counter = (u16)effect->frame.u + 1;
            effect->frame.u = (u16)frame_counter;
            if (frame_counter >= 8) {
                effect->frame.u = 4;
            }
            if (effect->ticks_left.s <= 0 && effect->frame.s == 7) {
                effect->ticks_left.u = 8;
                effect->state.u = (u16)(effect->state.u + 1);
                return;
            }
            break;
        }

        case 2:
        {
            u16 frame_counter = (u16)effect->frame.u + 1;
            effect->frame.u = frame_counter;
            if (effect->ticks_left.s == mode) {
                if (actor->target != 0) {
                    particle = allocate_list_node(770, &scene_object_list_anchor.next);
                    if (particle != 0) {
                        register_node(particle, directional_particle_node_callback);
                        particle->header.update_callback = directional_particle_callback;
                        {
                            s32 coordinate = actor->target_tile_x;
                            particle_data = &particle->work;
                            particle_data->impact.x.s = coordinate << 6;
                            coordinate = actor->target_tile_y;
                            particle_data->impact.y.s = coordinate << 6;
                            particle_data->impact.z.s = (u16)motion->z.w.i;
                        }
                        particle->work.owner = effect;
                        particle_data->impact.state.s = 0;
                    }
                }
            }
            if (effect->ticks_left.s <= 0) {
                if (actor->target != 0) {
                    effect->state.u = 240;
                    return;
                }
                unlink_node((u8 *)effect - 32);
                effect->state.u = 255;
                return;
            }
            break;
        }

        case 240:
            unlink_node((u8 *)effect - 32);
            effect->ticks_left.u = 10;
            initialize_timed_motion_step(8, 16);
            effect->state.u = (u16)(effect->state.u + 1);
            return;

        case 241:
            copy_selected_table_pair(actor->target, effect->ticks_left.s);
            if (effect->ticks_left.s == 6 && try_trigger_target_record_effect(actor->target, 4, actor) == 0 &&
                actor->target != 0) {
                try_apply_effect_four_by_chance(actor->target, current_spell_effect_variant[0] == 255 ? 255 : 16, 4);
            }
            if (effect->ticks_left.s > 0)
                break;
            unlink_node((u8 *)effect - 32);
            effect->state.u = 255;
            return;

        case 255:
        {
            s32 effect_flags;
            effect_flags = effect->child_flags;
            if ((effect_flags & 0x8000) != 0) {
                effect->child_flags = effect_flags & ~0x8000;
                return;
            } else {
                effect->ticks_left.u = 10;
                effect->state.u = (u16)(effect->state.u + 1);
                return;
            }
        }

        case 256:
            if (effect->ticks_left.s < 0) {
                g_dungeon_status.active_actor = 0;
                ((ObjectStatusPrefix16 *)effect)[-1].flags = (u16)(((ObjectStatusPrefix16 *)effect)[-1].flags | 0x8000);
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
            break;
        default:
            return;
        }
    }
}
