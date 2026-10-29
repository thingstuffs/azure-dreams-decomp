#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "engine/script.h"
#include "sdk/libc.h"
#include "slus.h"
#include "town/map.h"
#include "town/person.h"

#define F_S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define F_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void *D_800D210C[];
extern u8 D_800E9CD4[];
extern u8 D_800E9CFC[];
extern u8 D_800E9D0C[];
extern u8 D_800E9D34[];
extern u8 D_800E9D54[];
extern u8 D_800E9D8C[];
extern u8 D_800E9DAC[];
extern u8 D_800E9DD4[];
extern u8 D_800E9DEC[];

/* Updates random idle actions, bounded wandering, and sprite animation. */
void update_random_idle_wander(void *actor, void *motion, SpriteFrameState *sprite, s32 update_context) {
    void *anim_script;
    s16 *x_steps;
    s16 *y_steps;
    s16 *step_y;
    s16 *step_x;
    s16 *probe_x;
    s32 state;
    u16 timer;
    s32 choice;
    s32 direction_index;
    s32 step_offset;
    s32 distance;
    s32 delta_y;
    s32 walk_ticks;

    anim_script = 0;
    if (service_script_controller() != 0 &&
        check_transform_identifier_and_hook(actor) != 0) {
        if (!(F_S32(actor, 0xAC) & 1)) {
            SD_Call(0x601);
            F_S32(actor, 0xAC) |= 1;
        }
    } else {
        F_S32(actor, 0xAC) &= -2;
    }
    advance_sprite_animation_and_textures(sprite);
    timer = F_U16(actor, 0x6C) - 1;
    state = F_S16(actor, 0x68);
    F_U16(actor, 0x6C) = timer;

    switch (state) {
    case 0:
        choice = rand() & 0xF;
        if ((choice < 4) && (F_S16(actor, 0xA4) == 0x40)) {
            choice += 4;
        }
        F_U16(actor, 0x6C) = (rand() & 0x1F) + 0x28;
        if (choice < 4) {
            anim_script = D_800E9CD4;
            F_S16(actor, 0x68) = 0x40;
        }
        if (choice == 4) {
            F_S16(actor, 0xA6) = rand() & 1;
            anim_script = D_800E9D34;
            F_S16(actor, 0x68) = 0x60;
        } else if (choice < 8) {
            F_S16(actor, 0xA6) = rand() & 1;
            anim_script = D_800E9DAC;
            F_S16(actor, 0x68) = 0x80;
        } else {
            x_steps = dir_step_x;
            y_steps = dir_step_y;
            for (;;) {
                direction_index = rand() & 3;
                step_offset = direction_index * 4;
                probe_x = (s16 *)(step_offset + (long)x_steps);
                distance = F_S16(actor, 0xA2) + *probe_x;
                distance = abs(distance);
                choice = direction_index * 2;
                if (distance >= 2) {
                    continue;
                }
                delta_y = F_S16(actor, 0xA0) + *(s16 *)(step_offset + (long)y_steps);
                delta_y = abs(delta_y);
                if (delta_y < 2) {
                    break;
                }
            }
            walk_ticks = 0x40;
            step_x = (s16 *)((u8 *)dir_step_x + step_offset);
            step_y = (s16 *)((u8 *)dir_step_y + step_offset);
            F_U16(actor, 0x6C) = walk_ticks;
            F_S16(actor, 0xA2) = (u16)F_S16(actor, 0xA2) + (u16)*step_x;
            F_S16(actor, 0xA0) = (u16)F_S16(actor, 0xA0) + (u16)*step_y;
            F_S32(motion, 0xC) = *step_x << 16;
            F_S32(motion, 0x10) = *step_y << 16;
            F_S16(actor, 0x68) = 0xA0;
            if ((F_S16(actor, 0xA4) != 0xA0) ||
                ((choice >> 1) != F_S16(actor, 0xA6))) {
                F_S16(actor, 0xA6) = choice >> 1;
                anim_script = D_800D210C[choice >> 1];
            }
        }
        F_U16(actor, 0xA4) = F_U16(actor, 0x68);
        break;
    case 0x40:
        if (sprite->flags & 0x6000) {
            anim_script = D_800E9CFC;
        }
        if ((s16)timer > 0) {
            break;
        }
        anim_script = D_800E9D0C;
        F_S16(actor, 0x68) = 0;
        break;
    case 0x60:
        if ((s16)timer > 0) {
            break;
        }
        anim_script = D_800E9D54;
        F_S16(actor, 0x68) = 0x61;
        break;
    case 0x61:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        anim_script = D_800E9D8C;
        F_S16(actor, 0x68) = 0xF0;
        break;
    case 0x80:
        if (sprite->flags & 0x6000) {
            anim_script = D_800E9DD4;
        }
        if ((s16)timer > 0) {
            break;
        }
        anim_script = D_800E9DEC;
        F_S16(actor, 0x68) = 0xF0;
        break;
    case 0xA0:
        F_S32(motion, 0) += F_S32(motion, 0xC);
        F_S32(motion, 4) += F_S32(motion, 0x10);
        if (F_S16(actor, 0x6C) > 0) {
            break;
        }
        F_S16(actor, 0x68) = 0;
        break;
    case 0xF0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        F_S16(actor, 0x68) = 0;
        break;
    }

    if (F_S16(actor, 0xA6) != 0) {
        sprite->flags &= 0xFFFE;
    } else {
        sprite->flags |= 1;
    }
    if (anim_script != 0) {
        select_record_entry_and_value(sprite, anim_script, 0);
    }
}
