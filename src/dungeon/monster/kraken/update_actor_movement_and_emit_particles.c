#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/kraken.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/actor_action.h"
#include "shared/dungeon_projectile_views.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/player/object.h"
#include "dungeon/actor.h"
#include "sdk/libc.h"
#include "dungeon/monster/kraken_frames.h"

   /* arg0 in update_actor_movement_and_emit_particles */

   /* obj in update_actor_movement_and_emit_particles */

typedef struct S_80172D1C_3 {
    u8 pad_00[0x48];
    s16 unk_48;
} S_80172D1C_3;   /* (u8 *)calc_other in update_actor_movement_and_emit_particles */

extern u8 kraken_action_resume_address[];
extern u8 D_8017406C[];

/* Updates actor movement, emits particles, and settles the actor onto its tile. */
/* Applies Kraken's pending HP change, emits seven particles while recoiling, then returns it to its tile
 * and idle frames. */
void update_actor_movement_and_emit_particles(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *sprite, void *entity_arg) {
    EntityRec *entity = entity_arg;
    ObjectNodeHeader *particle;
    SpriteFrameState *particle_sprite;
    void *particle_update;
    u8 *unused_particle_state;
    s32 particle_or_dir_index;
    s32 state;
    s32 unused_value;
    s32 unused_value2;
    s32 sprite_flags;
    s32 timer;
    s32 next_timer;
    s16 state_timer;
    s32 velocity_x;
    s32 velocity_y;
    s32 speed_work;
    s32 component_work;
    s32 component_work_2;
    u8 *particle_work;

    if (actor->action_phase == 1) {
        particle_or_dir_index = 6;
        particle_update = D_8017406C;
        do {
            particle = allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (particle != 0) {
                particle_work = NODE_BODY(particle);
                register_node(particle, project_sprite_chain);
                particle_sprite = particle->sprite;
                particle->update_callback = particle_update;

                particle->position->x.w.i =
                    ((u16) motion->x.w.i) + (rand() & 0xF) - 8;
                particle->position->y.w.i =
                    ((u16) motion->y.w.i) + (rand() & 0xF) - 8;
                particle->position->z.w.i =
                    ((u16) motion->z.w.i) + (rand() & 0xF) - 8;

                particle->position->velocity_x =
                    ((rand() & 0xFF) - 0x80) << 10;
                particle->position->velocity_y =
                    ((rand() & 0xFF) - 0x80) << 10;
                particle->position->velocity_z = (-4 - (rand() & 3)) << 16;

                ((S_80172D1C_3 *)particle_work)->unk_48 = 10;
                sprite_flags = sprite->animation_resource;
                component_work = particle_sprite->flags | 0xC;
                particle_sprite->scale_y = 0x1800;
                particle_sprite->scale_x = 0x1800;
                particle_sprite->animation_resource = sprite_flags;
                particle_sprite->flags = component_work;
                component_work_2 = sprite->clut;
                particle_sprite->tpage_abr = 0x20;
                particle_sprite->clut = component_work_2 - 0x80;
                select_sprite_entry(particle_sprite, 0x2D, 0);
                particle_sprite->color.word = 0x808080;
            }
            particle_or_dir_index--;
        } while (particle_or_dir_index >= 0);
    }

    particle_or_dir_index = (entity->unk_6A >> 9) & 7;
    state = actor->action_phase;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        if (entity->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(actor, motion, sprite, kraken_frame_set);
            break;
        }
        if (sprite->flags & 0x8000) {
            actor->action_timer = 0;
            actor->action_phase = 2;
            break;
        }

        motion->velocity_x = dir_step_x[particle_or_dir_index] << 18;
        motion->velocity_y = dir_step_y[particle_or_dir_index] << 18;
        actor->action_phase++;
        state_timer = -1;
        if (entity->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            state_timer = 8;
        }
        actor->action_timer = state_timer;
        velocity_x = motion->velocity_x;
        motion->velocity_x = velocity_x - velocity_x / 4;
        velocity_y = motion->velocity_y;
        motion->velocity_y = velocity_y - velocity_y / 4;
        break;

    case 1:
        motion->velocity_x -= dir_step_x[particle_or_dir_index] << 14;
        motion->velocity_y -= dir_step_y[particle_or_dir_index] << 14;
        timer = (s16)actor->action_timer;
        if (timer > 0) {
            actor->action_timer = actor->action_timer - 1;
        } else {
            if (sprite->flags & 0x6000) {
                actor->action_timer = 0;
            }
        }
        if ((s16)actor->action_timer != 0) {
            break;
        }
        if (entity->unk_28 == 0) {
            actor->action_phase = 0;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(actor, motion, sprite, kraken_frame_set);
            break;
        }
        actor->action_timer = 8;
        actor->action_phase++;
        break;

    case 2:
        if ((s16)actor->action_timer != 0) {
            speed_work = sprite->tile_x;
            component_work = motion->x.w.i;
            speed_work <<= 6;
            component_work -= 0x20;
            speed_work -= component_work;
            speed_work <<= 15;
            speed_work >>= 1;
            motion->velocity_x = speed_work;

            speed_work = sprite->tile_y;
            component_work = motion->y.w.i;
            speed_work <<= 6;
            component_work -= 0x20;
            speed_work -= component_work;
            speed_work <<= 15;
            component_work = motion->velocity_x;
            speed_work >>= 1;
            motion->velocity_y = speed_work;
            velocity_y = component_work >> 1;
            component_work = component_work + velocity_y;
            motion->velocity_x = component_work;
            component_work = speed_work >> 1;
            speed_work += component_work;
            motion->velocity_y = speed_work;
        }
        next_timer = actor->action_timer - 1;
        actor->action_timer = next_timer;
        if ((next_timer << 16) <= 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = kraken_frame_set_1;
            select_sprite_entry(sprite,
                          kraken_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                          0);
            if ((g_dungeon_status.pending_display_owner) == (u8 *)entity - 0x20) {
                *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
            }
            actor->unk_8C.address = kraken_action_resume_address;
        }
    }
}
