#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "engine/script.h"
#include "sdk/libc.h"
#include "slus.h"
#include "town/map.h"
#include "town/map/motion.h"
#include "shared/sprite_source.h"
#include "town/person.h"

extern SpriteSourceEntry *D_800D210C[4];
extern SpriteSourceEntry D_800E9CD4[];
extern SpriteSourceEntry D_800E9CFC[];
extern SpriteSourceEntry D_800E9D0C[];
extern SpriteSourceEntry D_800E9D34[];
extern SpriteSourceEntry D_800E9D54[];
extern SpriteSourceEntry D_800E9D8C[];
extern SpriteSourceEntry D_800E9DAC[];
extern SpriteSourceEntry D_800E9DD4[];
extern SpriteSourceEntry D_800E9DEC[];

/* Updates random idle actions, bounded wandering, and sprite animation. */
void update_random_idle_wander(TownWanderBody *actor, ObjectPosition *motion, SpriteFrameState *sprite, s32 update_context) {
    SpriteSourceEntry *anim_script;
    s16 *x_steps;
    s16 *y_steps;
    s16 *step_y;
    s16 *step_x;
    s16 *probe_x;
    s32 state;
    s16 timer;
    s32 choice;
    s32 direction_index;
    s32 distance;
    s32 delta_y;
    s32 walk_ticks;

    anim_script = 0;
    if (service_script_controller() != 0 &&
        check_town_target_and_callback(actor) != 0) {
        if (!(actor->action_flags & 1)) {
            SD_Call(0x601);
            actor->action_flags |= 1;
        }
    } else {
        actor->action_flags &= -2;
    }
    advance_sprite_animation_and_textures(sprite);
    timer = actor->ticks - 1;
    state = actor->state;
    actor->ticks = timer;

    switch (state) {
    case 0:
        choice = rand() & 0xF;
        if ((choice < 4) && (actor->previous_state == 0x40)) {
            choice += 4;
        }
        actor->ticks = (rand() & 0x1F) + 0x28;
        if (choice < 4) {
            anim_script = D_800E9CD4;
            actor->state = 0x40;
        }
        if (choice == 4) {
            actor->direction = rand() & 1;
            anim_script = D_800E9D34;
            actor->state = 0x60;
        } else if (choice < 8) {
            actor->direction = rand() & 1;
            anim_script = D_800E9DAC;
            actor->state = 0x80;
        } else {
            x_steps = dir_step_x;
            y_steps = dir_step_y;
            for (;;) {
                direction_index = rand() & 3;
                probe_x = (s16 *)(direction_index * 4 + (long)x_steps);
                distance = actor->tile_offset_x + *probe_x;
                distance = abs(distance);
                choice = direction_index * 2;
                if (distance >= 2) {
                    continue;
                }
                delta_y = actor->tile_offset_y + y_steps[direction_index * 2];
                delta_y = abs(delta_y);
                if (delta_y < 2) {
                    break;
                }
            }
            walk_ticks = 0x40;
            step_x = &dir_step_x[direction_index * 2];
            step_y = &dir_step_y[direction_index * 2];
            actor->ticks = walk_ticks;
            actor->tile_offset_x += *step_x;
            actor->tile_offset_y += *step_y;
            motion->velocity_x = *step_x << 16;
            motion->velocity_y = *step_y << 16;
            actor->state = 0xA0;
            if ((actor->previous_state != 0xA0) ||
                ((choice >> 1) != actor->direction)) {
                actor->direction = choice >> 1;
                anim_script = D_800D210C[choice >> 1];
            }
        }
        actor->previous_state = actor->state;
        break;
    case 0x40:
        if (sprite->flags & 0x6000) {
            anim_script = D_800E9CFC;
        }
        if (timer > 0) {
            break;
        }
        anim_script = D_800E9D0C;
        actor->state = 0;
        break;
    case 0x60:
        if (timer > 0) {
            break;
        }
        anim_script = D_800E9D54;
        actor->state = 0x61;
        break;
    case 0x61:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        anim_script = D_800E9D8C;
        actor->state = 0xF0;
        break;
    case 0x80:
        if (sprite->flags & 0x6000) {
            anim_script = D_800E9DD4;
        }
        if (timer > 0) {
            break;
        }
        anim_script = D_800E9DEC;
        actor->state = 0xF0;
        break;
    case 0xA0:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        if (actor->ticks > 0) {
            break;
        }
        actor->state = 0;
        break;
    case 0xF0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        actor->state = 0;
        break;
    }

    if (actor->direction != 0) {
        sprite->flags &= 0xFFFE;
    } else {
        sprite->flags |= 1;
    }
    if (anim_script != 0) {
        select_record_entry_and_value(sprite, anim_script, 0);
    }
}
