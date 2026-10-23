/* Noise directional action setup and timed actor visual effects. */
#include "shared/entity.h"
#include "dungeon/monster/noise/start_directional_action_and_record_tile.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/manoeva.h"

/* Start the actor's directional action and record the adjacent tile result. */
void start_directional_action_and_record_tile(void *action_state, void *action_context, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 direction;

    actor->movement_queue_state = (u8)(actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_96.as_s16 = 0xF;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            (sprite->frameTable) = &D_80174EC8;
            select_sprite_entry(
                sprite,
                *(&D_80174EC8 + (((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
                0);
            sprite->flags = (u16)(sprite->flags | 0x800);
            advance_status_timers(actor);
            actor->pending_turn_updates = (u8)(((u8)actor->pending_turn_updates) - 1);
            direction = ((u16)actor->facing >> 9) & 7;
            actor->target = find_eligible_actor_at_tile_and_height(
                actor,
                (sprite->tile_x + ((u16 *)dir_step_x)[direction]) & 0xFFFF,
                (sprite->tile_y + ((u16 *)dir_step_y)[direction]) & 0xFFFF,
                actor->ground_height);
        }
    }
}

/* Advances a timed actor effect, spawning and positioning its visual object before cleanup. */
/* Creates a timed Noise sprite at its target or source, waits 45 ticks, checks the target action, then
 * spends MP. */
void advance_timed_actor_visual_effect(void *effect_state, ObjectPosition *position, SpriteFrameState *source_mesh, ActorRecord *actor)
{
    T_801748D0_LocalFrame frame;
    void *effect_body;
    SpriteFrameState *effect_mesh;
    ObjectPosition *anchor_pos;
    T_801748D0_S_801748D0_11 *owner_link;
    void *linked_owner;
    void *linked_body;
    void *owner;
    s16 count;
    s32 object_or_height;
    s32 anchor_height;
    s32 first_height;
    u16 timer;
    u16 anchor_z;
    u16 flags;
    s32 call_value;
    s32 mesh_flags;
    s32 lookup_value;
    s32 phase;

    owner = (u8 *)effect_state - 0x20;
    phase = ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B;
    switch (phase) {
    case 0:
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        timer = ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 - 1;
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = timer;
        if (((s32)(timer << 16) <= 0) ||
            (source_mesh->flags & 0x8000)) {
            ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = 0;
            ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B++;
            flags = source_mesh->flags;
            source_mesh->flags = flags & 0xF7FF;
        }
        return;
    case 1:
        if (!(source_mesh->flags & 0x8000)) {
            play_sound_if_enabled(0x80D);
        }
        count = 0;
        do {
            object_or_height = (s32)allocate_list_node(0x112, &scene_object_list_anchor);
            effect_body = (u8 *)((void *)object_or_height);
            effect_body += 0x20;
            if (((void *)object_or_height) == 0) {
                continue;
            }
            ((T_801748D0_S_801748D0_3 *)effect_body)->unk_96 = 0x2D;
            ((T_801748D0_S_801748D0_3 *)effect_body)->unk_9E = 0x2D;
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_10 = update_effect_visuals_and_lifetime;
            linked_body = actor->target;
            if (linked_body == 0) {
                ((T_801748D0_S_801748D0_3 *)effect_body)->unk_A8 = position;
                ((T_801748D0_S_801748D0_3 *)effect_body)->unk_A2 = 0;
            } else {
                linked_owner = ((T_801748D0_S_801748D0_6_pre *)linked_body)[-1].unk_00;
                ((T_801748D0_S_801748D0_3 *)effect_body)->unk_A2 = 1;
                ((T_801748D0_S_801748D0_3 *)effect_body)->unk_A8 = linked_owner;
            }
            ((T_801748D0_S_801748D0_3 *)effect_body)->unk_94 = actor->facing;
            effect_mesh = ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_0C;
            anchor_pos = ((T_801748D0_S_801748D0_3 *)effect_body)->unk_A8;
            *(T_801748D0_MeshCopy *)effect_mesh = *(T_801748D0_MeshCopy *)source_mesh;
            mesh_flags = effect_mesh->flags;
            effect_mesh->scale_y = 0x400;
            effect_mesh->scale_x = 0x400;
            effect_mesh->color.c.b = 0x80;
            effect_mesh->color.c.g = 0x80;
            effect_mesh->color.c.r = 0x80;
            effect_mesh->tpage_abr = 0x20;
            effect_mesh->clut = 0xFF80;
            mesh_flags |= 0xC;
            effect_mesh->flags = mesh_flags;
            register_node((void *)object_or_height, project_sprite_chain);
            call_value = noise_frame_set_2[0];
            effect_mesh->frameTable = noise_frame_set_2;
            select_sprite_entry(effect_mesh, call_value, 0);
            object_or_height = (s32)((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at00.v;
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_02 = *(u16 *)&anchor_pos->x.w.i;
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_06 = *(u16 *)&anchor_pos->y.w.i;
            anchor_z = *(u16 *)&anchor_pos->z.w.i;
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v = anchor_z;
            if (actor->target == 0) {
                owner_link = ((T_801748D0_S_801748D0_10 *)owner)->unk_0C;
                if (resolve_record_orientation_or_fallback(owner_link->unk_08, owner_link, frame.delta, 0) != 0) {
                    ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_02 += frame.delta[0];
                    ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_06 += frame.delta[1];
                    ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v += frame.delta[2];
                }
                frame.pos[0] = ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_02;
                frame.pos[1] = ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_06;
                frame.pos[2] = ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v;
                first_height = RotTransPers(frame.pos, frame.out0, &frame.out1, &frame.out2);
                mesh_flags = *(u16 *)&anchor_pos->x.w.i;
                frame.pos[0] = mesh_flags;
                mesh_flags = *(u16 *)&anchor_pos->y.w.i;
                frame.pos[1] = mesh_flags;
                mesh_flags = *(u16 *)&anchor_pos->z.w.i;
                frame.pos[2] = mesh_flags;
                anchor_height = RotTransPers(frame.pos, frame.out0, &frame.out1, &frame.out2);
                lookup_value = view_direction_depth_biases[((g_game_work.view.camera_rotation.parts.viewAngle + (s16)((T_801748D0_S_801748D0_3 *)effect_body)->unk_94 + 0x100)
                    >> 9) & 7];
                effect_mesh->depth_bias = first_height - anchor_height - (lookup_value << 1);
                continue;
            }
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v = anchor_z - 0x1E;
            effect_mesh->depth_bias = 4;

        } while (++count < 1);
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = 0x2D;
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B++;
        return;
    case 2:
        if (source_mesh->flags & 0xE000) {
            if (source_mesh->frameTable != noise_direction_frames) {
                source_mesh->frameTable = noise_direction_frames;
                source_mesh->flags &= 0xF7FF;
                select_sprite_entry(source_mesh, ((u8 *)source_mesh->frameTable)[((g_game_work.view.camera_rotation.parts.viewAngle
                    + actor->facing + 0x100) >> 9) & 7], 0);
            }
        }
        if (!(source_mesh->flags & 0x8000)) {
            timer = ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 - 1;
            ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = timer;
            if ((s32)(timer << 16) > 0) {
                return;
            }
        }
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, source_mesh->tile_x, source_mesh->tile_y);
        if (source_mesh->frameTable != noise_direction_frames) {
            source_mesh->frameTable = noise_direction_frames;
            source_mesh->flags &= 0xF7FF;
            select_sprite_entry(source_mesh, ((u8 *)source_mesh->frameTable)[((g_game_work.view.camera_rotation.parts.viewAngle
                + actor->facing + 0x100) >> 9) & 7], 0);
        }
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B++;
        return;
    case 3:
        owner_link = actor->target;
        if (owner_link != 0) {
            check_action_six_eligibility(actor, owner_link);
        }
        spend_actor_mp(actor, 0x400);
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_8C = update_actor_behavior_and_direction;
        g_dungeon_status.active_actor = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;

        return;
    }
}
