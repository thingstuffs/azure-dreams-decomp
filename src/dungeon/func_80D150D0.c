#include "dungeon/monster/noise/start_directional_action_and_record_tile.h"

/* Advances a timed actor effect, spawning and positioning its visual object before cleanup. */
void advance_timed_actor_visual_effect(void *effect_state, EntityRec *position, void *source_mesh, EntityRec *actor)
{
    T_801748D0_LocalFrame frame;
    void *effect_body;
    T_801748D0_S_801748D0_7 *effect_mesh;
    void *anchor_pos;
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
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        timer = ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 - 1;
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = timer;
        if (((s32)(timer << 16) <= 0) ||
            (((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
            ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = 0;
            ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B++;
            flags = ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14;
            ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 = flags & 0xF7FF;
        }
        return;
    case 1:
        if (!(((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
            play_sound_if_enabled(0x80D);
        }
        count = 0;
        do {
            object_or_height = (s32)allocate_list_node(0x112, &D_80083498);
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
            mesh_flags = effect_mesh->unk_14;
            effect_mesh->unk_1E = 0x400;
            effect_mesh->unk_1C = 0x400;
            effect_mesh->unk_0E = 0x80;
            effect_mesh->unk_0D = 0x80;
            effect_mesh->unk_0C = 0x80;
            effect_mesh->unk_10 = 0x20;
            effect_mesh->unk_12 = 0xFF80;
            mesh_flags |= 0xC;
            effect_mesh->unk_14 = mesh_flags;
            register_node((void *)object_or_height, project_sprite_chain);
            call_value = D_80174ED0[0];
            effect_mesh->unk_2C = D_80174ED0;
            select_sprite_entry(effect_mesh, call_value, 0);
            object_or_height = (s32)((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at00.v;
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_02 = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_02;
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_06 = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_06;
            anchor_z = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_0A;
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
                first_height = func_80065420(frame.pos, frame.out0, &frame.out1, &frame.out2);
                mesh_flags = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_02;
                frame.pos[0] = mesh_flags;
                mesh_flags = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_06;
                frame.pos[1] = mesh_flags;
                mesh_flags = ((T_801748D0_S_801748D0_9 *)anchor_pos)->unk_0A;
                frame.pos[2] = mesh_flags;
                anchor_height = func_80065420(frame.pos, frame.out0, &frame.out1, &frame.out2);
                lookup_value = D_800DCECC[((g_game_work.view.viewAngle + (s16)((T_801748D0_S_801748D0_3 *)effect_body)->unk_94 + 0x100)
                    >> 9) & 7];
                effect_mesh->unk_06 = first_height - anchor_height - (lookup_value << 1);
                continue;
            }
            ((T_801748D0_S_801748D0_4 *)((void *)object_or_height))->unk_08.at02.v = anchor_z - 0x1E;
            effect_mesh->unk_06 = 4;

        } while (++count < 1);
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = 0x2D;
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B++;
        return;
    case 2:
        if (((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 & 0xE000) {
            if (((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C != D_80174E88) {
                ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C = D_80174E88;
                ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 &= 0xF7FF;
                select_sprite_entry(source_mesh, ((u8 *)((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C)[((g_game_work.view.viewAngle
                    + actor->facing + 0x100) >> 9) & 7], 0);
            }
        }
        if (!(((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 & 0x8000)) {
            timer = ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 - 1;
            ((T_801748D0_S_801748D0_0 *)effect_state)->unk_96 = timer;
            if ((s32)(timer << 16) > 0) {
                return;
            }
        }
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        set_record_integer_tile_center(position, ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_24, ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_25);
        if (((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C != D_80174E88) {
            ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C = D_80174E88;
            ((T_801748D0_S_801748D0_2 *)source_mesh)->unk_14 &= 0xF7FF;
            select_sprite_entry(source_mesh, ((u8 *)((T_801748D0_S_801748D0_2 *)source_mesh)->unk_2C)[((g_game_work.view.viewAngle
                + actor->facing + 0x100) >> 9) & 7], 0);
        }
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_9B++;
        return;
    case 3:
        owner_link = actor->target;
        if (owner_link != 0) {
            check_action_six_eligibility(actor, owner_link);
        }
        reduce_actor_food_meter(actor, 0x400);
        ((T_801748D0_S_801748D0_0 *)effect_state)->unk_8C = update_actor_behavior_and_direction;
        g_dungeon_status.unk_0C = 0;
        actor->unk_46 &= 0x7FFF;

        return;
    }
}
