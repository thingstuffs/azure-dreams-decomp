#include "modules/dungeon_ovl_1936800.h"

void build_inverted(Row_81917C08_ActionState *action, Row_81917C08_EffectMotion *motion, Row_81917C08_EffectVisual *visual)
{
    EntityRec *actor;
    EntityRec *target;
    ObjectNodeHeader *node;
    Row_81917C08_EffectMotion *target_motion;
    Row_81917C08_EffectMotion *actor_motion;
    Row_81917C08_ActorVisual *actor_visual;
    Row_81917C08_ActorVisual *scan_visual;
    Row_81917C08_EffectMotion destination;
    s16 offset[3];
    s16 dest_tile_y;
    u16 tile_x, tile_y;
    s32 steps;
    s32 height;
    s16 dest_tile_x;

    action->ticks++;
    actor = action->actor;
    switch (action->phase) {
    case 0:
        action->ticks = 0;
        action->completed_a = 0;
        action->completed_b = 0;
        action->phase++;
        action->direction = ((u16)actor->facing >> 9) & 7;
        visual->color = 0x808080;
        begin_view_parameter_transition((ObjectNodeHeader *)actor - 1, motion, 8, 0x300);
        /* The initial movement work is shared with phase 1. */
    case 1:
        node = (ObjectNodeHeader *)actor - 1;
        actor_visual = node->unk_0C;
        if (!resolve_record_orientation_or_fallback(actor_visual->resource, actor_visual, offset, 0)) {
            if (!( ((Row_81917C08_ActorVisual *)node->unk_0C)->flags & 0x8000))
                break;
        }
        actor_motion = node->unk_08;
        motion->x.w.i = actor_motion->x.w.i;
        motion->y.w.i = actor_motion->y.w.i;
        motion->z.w.i = actor_motion->z.w.i;
        if (!(((Row_81917C08_ActorVisual *)node->unk_0C)->flags & 0x8000)) {
            motion->x.w.i += offset[0];
            motion->y.w.i += offset[1];
            motion->z.w.i += offset[2];
        } else {
            motion->z.w.i -= 0x40;
        }
        if (!(*action->flags & 0x80))
            break;
        steps = 0;
        target = actor->target;
        if (target) {
            target_motion = ((ObjectNodeHeader *)target - 1)->unk_08;
            motion->next_x = target_motion->x.v;
            motion->next_y = target_motion->y.v;
            motion->next_z = target_motion->z.v - (D_800DDC40[((u8 *)actor->target)[0x13]] << 15);
        } else {
            scan_visual = node->unk_0C;
            tile_x = scan_visual->tile_x;
            tile_y = scan_visual->tile_y;
            dest_tile_x = tile_x;
            dest_tile_y = tile_y;
            do {
                if (check_layer_offset_height((s16)tile_x * 0x40, (s16)tile_y * 0x40,
                                 actor->unk_88, action->direction << 9))
                    break;
                height = sample_terrain_surface_height(((s16)tile_x + dir_step_x[action->direction]) * 0x40 + 0x20,
                                     ((s16)tile_y + dir_step_y[action->direction]) * 0x40 + 0x20,
                                     actor->unk_88 - 0x20);
                if ((s16)height > 0x200 || (s16)(height - actor->unk_88) < -0x3F)
                    break;
                steps++;
                tile_x += (u16)dir_step_x[action->direction];
                tile_y += (u16)dir_step_y[action->direction];
                dest_tile_y = tile_y;
                dest_tile_x = tile_x;
            } while (steps < 8);
            target_motion = &destination;
            target_motion->x.w.i = (dest_tile_x * 64) + ((dir_step_x[action->direction] + 1) * 32);
            target_motion->y.w.i = (dest_tile_y * 64) + ((dir_step_y[action->direction] + 1) * 32);
            target_motion->z.w.i = motion->z.w.i;
            motion->next_x = target_motion->x.v;
            motion->next_y = target_motion->y.v;
            motion->next_z = motion->z.v - 0x200000;
        }
        create_an_initializes_visual_state_copies_initial_data(action, motion, actor);
        action->ticks = 0;
        action->phase++;
        break;
    case 2:
        motion->x.v += ((func_80064584(actor->facing) >> 4) * (8 - action->ticks)) << 8;
        motion->y.v += ((func_800644B8(actor->facing) >> 4) * (8 - action->ticks)) << 8;
        motion->z.v -= 0x20000;
        if (action->ticks == 5) {
            play_sound_if_enabled(0x300);
            for (steps = 0; steps < 8; steps++)
                create_an_attached_effect_copied_transform_data_randomized_angle(action, motion, (s16)steps);
        }
        if (action->ticks >= 9) {
            action->ticks = 0;
            action->phase++;
            break;
        }
        action->pending = 0;
        return;
    case 3:
        if (action->ticks < 0xD)
            motion->z.v -= 0x20000;
        if (action->ticks < 0x3C)
            break;
        create_a_type_hex_212_initializes_handler_mode(action);
        target = actor->target;
        if (target) {
            target_motion = ((ObjectNodeHeader *)target - 1)->unk_08;
            motion->next_x = (target_motion->x.v - motion->x.v) / 32;
            motion->next_y = (target_motion->y.v - motion->y.v) / 32;
            motion->next_z = (target_motion->z.v -
                (D_800DDC40[((u8 *)actor->target)[0x13]] << 15) - motion->z.v) / 32;
        } else {
            motion->next_x = (motion->next_x - motion->x.v) / 32;
            motion->next_y = (motion->next_y - motion->y.v) / 32;
            motion->next_z = (motion->next_z - motion->z.v) / 32;
        }
        action->ticks = 0;
        action->phase++;
        break;
    case 4:
        motion->x.v += motion->next_x;
        motion->y.v += motion->next_y;
        motion->z.v += motion->next_z;
        if (action->ticks >= 0x20) {
            action->ticks = 0;
            action->phase++;
            break;
        }
        action->pending = 0;
        return;
    case 5:
        if (action->completed_a < 8 || action->completed_b < 8)
            break;
        if (actor->target)
            apply_attack_power_and_element_effects(actor->target, 0x18, action->event_id, 2,
                         action->direction << 9, actor, 1);
        action->ticks = 0;
        action->phase++;
        break;
    case 6:
        if (!action->pending) {
            D_8008346C.value = 0;
            ((ObjectNodeHeader *)action)[-1].flags |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
        break;
    }
    action->pending = 0;
}
