/* Relinked copy of dungeon/func_80A47C0C (func_80A47C0C.c); retail differs only at relocation sites. */
#include "modules/dungeon_resource06_slot0.h"

/* r121_nodonor relink of dungeon/func_80A47C0C: symbols this copy binds at other addresses. */
void func_80159964();
void func_80159964();
extern u8 D_8015D894[];
extern u8 D_8015D88C[];
extern u8 D_8015D86C[];
extern u8 D_8015D874[];
void func_8015BC34(R06_80173C34_Actor *actor, s32 action, R06_80173C34_Entity *entity, R06_80173C34_MapObject *map_object);
void func_8015D068(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
s32 func_8015A550(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
s32 func_8015A264(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor);
void func_8015A428(void *action_state, void *context, void *sprite, EntityRec *actor);
void func_8015A428(void *action_state, void *context, void *sprite, EntityRec *actor);
extern u8 D_8015D884[];
void func_80159B1C(void *move_data, void *context, void *position_data, void *actor_data);

void choose_flame_action_slot_c(void *actor, void *actor_context, void *sprite, void *creature)
{
    s32 distance;
    s8 room_id;
    u16 behavior_flags;

    if (g_dungeon_status.flags & 0x1000) {
        ((R06_8017140C_S_8017140C_0 *)actor)->unk_9A = 0xE;
        func_80159964(actor, actor_context);
        return;
    }

    if (((R06_8017140C_S_8017140C_1 *)creature)->unk_25 == 0) {
        u8 *animation_table;

        advance_actor_pending_action(actor, actor_context, sprite, creature);
        if (((R06_8017140C_S_8017140C_2 *)sprite)->unk_2C == ((u8 *)D_8015D894)) {
            return;
        }
        animation_table = ((u8 *)D_8015D88C);
        (*(void * *)((u8 *)sprite + 0x2C)) = animation_table;
        select_sprite_entry(sprite,
            animation_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((R06_8017140C_S_8017140C_1 *)creature)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x200) {
        if (((R06_8017140C_S_8017140C_2 *)sprite)->unk_2C == ((u8 *)D_8015D894)) {
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_9A = 0xD;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_9B = 1;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_8C = 0;
            ((R06_8017140C_S_8017140C_1 *)creature)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, actor_context, sprite, ((u8 *)D_8015D88C)) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        void *current_animation;
        u8 *animation_table;

        if (((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor, actor_context, sprite, creature);
            return;
        }

        if (((R06_8017140C_S_8017140C_0 *)actor)->unk_9A != 0xE) {
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_9A = 0xE;
        }

        current_animation = ((R06_8017140C_S_8017140C_2 *)sprite)->unk_2C;
        animation_table = ((u8 *)D_8015D86C);
        if (current_animation != animation_table) {
            (*(void * *)((u8 *)sprite + 0x2C)) = animation_table;
            select_sprite_entry(sprite,
                animation_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((R06_8017140C_S_8017140C_1 *)creature)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((R06_8017140C_S_8017140C_2 *)sprite)->unk_05 = 1;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_B6.s = 0;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_B8 = 0;
        }

        ((R06_8017140C_S_8017140C_1 *)creature)->unk_1C |= 0x40000;
        ((R06_8017140C_S_8017140C_0 *)actor)->unk_98 &= 0xFFF7;

        if (((R06_8017140C_S_8017140C_1 *)creature)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, actor_context, sprite, ((u8 *)D_8015D874)) != 0) {
                return;
            }
        }

        if (((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x80000) {
            s16 adjusted_offset;

            begin_actor_move_to_target_facing(actor, actor_context, sprite, creature);
            adjusted_offset = ((R06_8017140C_S_8017140C_0 *)actor)->unk_92.u - ((R06_8017140C_S_8017140C_0 *)actor)->unk_B6.u;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_B6.s = 0;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_B8 = 0;
            ((R06_8017140C_S_8017140C_0 *)actor)->unk_92.s = adjusted_offset;
            func_8015BC34(actor, actor_context, sprite, creature);
            return;
        }

        if ((can_entity_gain_level(creature) << 16) != 0) {
            if ((process_selected_actor_record(actor, actor_context, sprite, creature) << 16) != 0) {
                func_8015D068(actor, actor_context, sprite, creature);
            }
        }
    }

    room_id = ((s8)find_active_rect_containing_point(((R06_8017140C_S_8017140C_2 *)sprite)->unk_24.at00.v, ((R06_8017140C_S_8017140C_2 *)sprite)->unk_24.at01.v));
    ((R06_8017140C_S_8017140C_2 *)sprite)->unk_26 = room_id;

    if (((R06_8017140C_S_8017140C_1 *)creature)->unk_6D > 0) {
        if (((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x20) {
            update_actor_status_and_food(creature);
            return;
        }
        if (((R06_8017140C_S_8017140C_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            func_80159B1C(actor, actor_context, sprite, creature);
            return;
        }
        if (!(((R06_8017140C_S_8017140C_1 *)creature)->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(creature,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8015A550(actor, actor_context, sprite, 0) << 16) == 0) {
                return;
            }
            behavior_flags = ((R06_8017140C_S_8017140C_1 *)creature)->unk_46 | 0x4000;
            ((R06_8017140C_S_8017140C_1 *)creature)->unk_46 = behavior_flags;
            if (!(behavior_flags & 0x8000)) {
                func_80159B1C(actor, actor_context, sprite, creature);
                return;
            }
        }

        {
            u32 behavior_index = (u32)((((R06_8017140C_S_8017140C_1 *)creature)->unk_46 & 0x3FFF) - 1);

            switch (behavior_index) {
            case 7:
            case 8:
                if ((func_8015A264(actor, actor_context, sprite, creature) << 16) != 0) {
                    return;
                }
                func_8015A428(actor, actor_context, sprite, creature);
                return;

            case 4:
            case 5:
            case 6:
            {
                EntityRec *player;
                s16 facing_angle;

                facing_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R06_8017140C_S_8017140C_2 *)sprite)->unk_24.at00.v),(s16)(((R06_8017140C_S_8017140C_2 *)sprite)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                    &distance));
                player = D_800814A8;
                ((R06_8017140C_S_8017140C_1 *)creature)->unk_2A = facing_angle;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(actor, actor_context, sprite, ((u8 *)D_8015D884), choose_flame_action_slot_c);
                    return;
                }
            }

            case 11:
                update_actor_status_and_food(creature);
                return;

            case 0:
            case 1:
            case 2:
                begin_actor_spell_action(actor, actor_context, sprite, ((u8 *)D_8015D884), choose_flame_action_slot_c);
                return;

            default:
                func_80159B1C(actor, actor_context, sprite, creature);
                return;
            }
        }
    }

    if (!(((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((R06_8017140C_S_8017140C_1 *)creature)->unk_1C & 0x430)) {

                if ((compare_monster_neighbor_values(
                        ((R06_8017140C_S_8017140C_2 *)sprite)->unk_24.at00.v, ((R06_8017140C_S_8017140C_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y) << 16) != 0) {
                    ((R06_8017140C_S_8017140C_1 *)creature)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R06_8017140C_S_8017140C_2 *)sprite)->unk_24.at00.v),(s16)(((R06_8017140C_S_8017140C_2 *)sprite)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                        &distance));
                }
            }
        }
    }
}
