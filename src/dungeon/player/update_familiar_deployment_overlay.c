#include "common.h"
#include "dungeon/player/familiar_deployment_overlay.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "dungeon/player.h"
#include "engine/graphics.h"
#include "dungeon/data.h"

/* cfail-repair: tf7-phase1-cache-v3 */

enum DeploymentOverlayState {
    DEPLOY_OVERLAY_GROW = 0,
    DEPLOY_OVERLAY_WAIT_SAVE = 1,
    DEPLOY_OVERLAY_SHRINK = 2,
    DEPLOY_OVERLAY_REMOVE = 3,
};

/* Updates an object's scale and brightness through its transition modes. */
void update_familiar_deployment_overlay(void *object_data, ObjectPosition *unused, SpriteFrameState *sprite_data) {
    FamiliarDeploymentOverlayBody *body = object_data;
    SpriteFrameState *sprite = sprite_data;
    s16 mode;
    u16 grow_ticks;
    u16 shrink_ticks;
    u16 grow_scale;
    u16 scale_or_ticks;
    u16 mode_next;
    u8 dimmed_brightness;
    u8 brightness;

    step_actor_animation(sprite, body->animation_index + 2);
    if (reference_tile_object.sprite_flags & 1) {
        sprite->flags |= 1;
    } else {
        sprite->flags &= 0xFFFE;
    }
    mode = (s16)body->mode;
    switch (mode) {
    case DEPLOY_OVERLAY_GROW:
        grow_scale = sprite->scale_x;
        sprite->scale_x = (u16)(grow_scale + ((s32)(0x1000 - grow_scale) / 4));
        grow_ticks = body->ticks_left - 1;
        body->ticks_left = grow_ticks;
        if ((grow_ticks << 0x10) <= 0) {
            sprite->scale_x = 0x1000;
            mode_next = body->mode;
            mode_next += 1;
            body->mode = mode_next;
        }
        return;
    case DEPLOY_OVERLAY_WAIT_SAVE:
        if (body->animation_index == 0) {
            brightness = sprite->color.c.r;
            if (brightness >= 0x81U) {
                dimmed_brightness = brightness - 8;
                sprite->color.c.r = dimmed_brightness;
                sprite->color.c.b = dimmed_brightness;
                sprite->color.c.g = dimmed_brightness;
            }
        }
        if ((s32)body->owner_sprite->frameTable != (s32)&familiar_save_frames) {
            return;
        }
        if (body->animation_index == 0) {
            scale_or_ticks = 8;
            mode_next = body->mode;
            body->ticks_left = scale_or_ticks;
            mode_next += 1;
            body->mode = mode_next;
            return;
        }
        NODE_HEADER(body)->flags |= NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return;
    case DEPLOY_OVERLAY_SHRINK:
        scale_or_ticks = sprite->scale_x;
        sprite->scale_x = (u16)(scale_or_ticks + ((s32)(0 - scale_or_ticks) / 4));
        shrink_ticks = body->ticks_left - 1;
        body->ticks_left = shrink_ticks;
        if ((shrink_ticks << 0x10) <= 0) {
            sprite->scale_x = 0;
            mode_next = body->mode;
            mode_next += 1;
            body->mode = mode_next;
        }
        return;
    case DEPLOY_OVERLAY_REMOVE:
        NODE_HEADER(body)->flags |= NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return;
    }
}
