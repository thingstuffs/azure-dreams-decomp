#include "modules/dungeon_resource06_slot0.h"

void func_801738E0(void *entity, void *context, void *anim, void *actor)
{
    s32 state;

    state = ((R06_801738E0_S_801738E0_0 *)entity)->unk_9B;
    switch (state) {
    case 0:
    {
        s32 *scene_state;
        u8 *direction_anims;

        if (!(((R06_801738E0_S_801738E0_1 *)anim)->unk_14 & 0xE000)) {
            return;
        }

        scene_state = &g_dungeon_status.unk_00;
        ((R06_801738E0_S_801738E0_2 *)scene_state)->unk_0A--;
        direction_anims = ((u8 *)D_80175894);
        (*(void * *)((u8 *)anim + 0x2C)) = direction_anims;
        select_sprite_entry(anim,
            direction_anims[((g_game_work.view.viewAngle + ((R06_801738E0_S_801738E0_3 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((R06_801738E0_S_801738E0_0 *)entity)->unk_9B++;
        return;
    }
    case 1:
    {
        u8 *scene_state;
        u32 actor_flags;

        if (((R06_801738E0_S_801738E0_3 *)actor)->unk_25 != 0) {
            s32 *scene_state;

            (*(void * *)((u8 *)anim + 0x2C)) = ((u8 *)D_8017588C);
            select_sprite_entry(anim,
                ((u8 *)D_8017588C)[((g_game_work.view.viewAngle + ((R06_801738E0_S_801738E0_3 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((R06_801738E0_S_801738E0_3 *)actor)->unk_1C |= 0x40000;
            scene_state = &g_dungeon_status.unk_00;
            ((R06_801738E0_S_801738E0_2 *)scene_state)->unk_0A++;
            ((R06_801738E0_S_801738E0_0 *)entity)->unk_9B++;
            return;
        }

        scene_state = (u8 *)&g_dungeon_status.unk_00;
        if (((R06_801738E0_S_801738E0_4 *)scene_state)->unk_02 & 0x1000) {
            return;
        }

        if (((R06_801738E0_S_801738E0_3 *)actor)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(entity, context, anim, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            return;
        }

        actor_flags = ((R06_801738E0_S_801738E0_3 *)actor)->unk_1C;
        if (actor_flags & 0x100) {
            begin_pushed_actor_move(entity, context, anim, actor);
            return;
        }

        if (actor_flags & 0x80000) {
            u16 entity_value;
            u16 pending_delta;

            begin_actor_move_to_target_facing(entity, context, anim, actor);
            entity_value = ((R06_801738E0_S_801738E0_0 *)entity)->unk_92;
            pending_delta = ((R06_801738E0_S_801738E0_0 *)entity)->unk_B6;
            ((R06_801738E0_S_801738E0_0 *)entity)->unk_B6 = 0;
            ((R06_801738E0_S_801738E0_0 *)entity)->unk_B8 = 0;
            ((R06_801738E0_S_801738E0_0 *)entity)->unk_92 = entity_value - pending_delta;
            func_80173C34(entity, context, anim, actor);
            return;
        }

        if (((R06_801738E0_S_801738E0_3 *)actor)->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            if ((check_entity_relation(actor,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_food(actor);
        on_actor_status_updated(actor);
        if (((R06_801738E0_S_801738E0_3 *)actor)->unk_25 == 0) {
            return;
        }

        (*(void * *)((u8 *)anim + 0x2C)) = ((u8 *)D_8017588C);
        select_sprite_entry(anim,
            ((u8 *)D_8017588C)[((g_game_work.view.viewAngle + ((R06_801738E0_S_801738E0_3 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((R06_801738E0_S_801738E0_3 *)actor)->unk_1C |= 0x40000;
        ((R06_801738E0_S_801738E0_4 *)scene_state)->unk_0A++;
    }
        ((R06_801738E0_S_801738E0_0 *)entity)->unk_9B++;
        return;
    case 2:
        if (((R06_801738E0_S_801738E0_1 *)anim)->unk_14 & 0xE000) {
            s32 *scene_state;

            scene_state = &g_dungeon_status.unk_00;
            ((R06_801738E0_S_801738E0_2 *)scene_state)->unk_0A--;
            ((R06_801738E0_S_801738E0_3 *)actor)->unk_1C &= ~0x208;
            ((R06_801738E0_S_801738E0_0 *)entity)->unk_8C = ((void *)initialize_destination_state);
        }

        return;
    default:
        return;
    }
}
