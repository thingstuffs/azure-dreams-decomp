#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} Actor;
typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} Entity;
typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} MapObject;


typedef struct S_801711A4_2 {
    u8 pad_00[0x5];
    s8 unk_05;
    u8 pad_06[0x1E];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801711A4_2;   /* arg2 in update_actor_animation_and_dispatch */

typedef struct S_801711A4_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    s8 unk_9B;
} S_801711A4_3;   /* saved0 in update_actor_animation_and_dispatch */


typedef struct EmptyArg {
} EmptyArg;

void select_sprite_entry();
s32 check_entity_relation();
s8 find_active_rect_containing_point();
s32 compare_monster_neighbor_values();
s16 get_rounded_facing_and_rounding_flag();
s32 can_entity_gain_level();
void update_actor_status_and_food();
void begin_pushed_actor_move();
s32 begin_ready_actor_directional_action();
s32 advance_actor_pending_action();
void begin_actor_move_to_target_facing();
s32 reset_actor_action_state();
s32 process_selected_actor_record();
void begin_actor_spell_action();
extern void func_801716CC(void *motion, s32 unused, void *actor, void *path_state);
extern void func_80171884(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, EntityRec *actor_data);
s32 func_80171FCC();
extern void func_80172190(void *action_state, void *context, void *sprite, EntityRec *actor);
s32 func_801722B8();
extern void func_80173D10(Actor *actor, s32 action, Entity *entity, MapObject *map_object);
extern void update_actor_animation_and_dispatch(void *actor, s32 context, void *sprite, EntityRec *status);
extern M2C_UNK D_8017418C;
extern M2C_UNK D_80174194;
extern M2C_UNK D_801741AC;
extern M2C_UNK D_801741C4;
extern M2C_UNK D_801741CC;

/* Updates the actor animation and dispatches dungeon actions based on status and position. */
void update_actor_animation_and_dispatch(void *actor, s32 context, void *sprite, EntityRec *status) {
    s32 direction_aux;
    void *next_handler;
    s32 status_flags;
    s32 action_id;
    s8 room_id;
    s16 angle;
    u16 action_flags;
    EntityRec *active_actor;
    s32 *direction_aux_ptr;
    EmptyArg empty_arg;

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
        func_801716CC(actor, context, sprite, status);
        return;
    }
    if (status->tileY == 0) {
        advance_actor_pending_action(actor, context, sprite, status);
        if (((S_801711A4_2 *)sprite)->unk_2C == &D_801741CC) {
            return;
        }
        (*(void **)((u8 *)sprite + 0x2C)) = &D_801741C4;
        select_sprite_entry(sprite, *(((u8 *)&D_801741C4) + (((s32) (g_game_work.view.viewAngle + status->facing + 0x100)
            >> 9) & 7)), 0);
        return;
    }
    if (status->flags1C & 0x200) {
        {
            void *action_actor = actor;
            if (((S_801711A4_2 *)sprite)->unk_2C == &D_801741CC) {
                {
                    void *reset_actor = actor;
                    EntityRec *reset_status = status;
                    s32 clear_mask = (s32)0xFFFB0000;
                    s32 flags;
                    ((S_801711A4_3 *)reset_actor)->unk_9A = 0xDU;
                    ((S_801711A4_3 *)reset_actor)->unk_9B = 1;
                    ((S_801711A4_3 *)reset_actor)->unk_8C = 0;
                    flags = reset_status->flags1C;
                    clear_mask |= 0xFFFF;
                    flags &= clear_mask;
                    reset_status->flags1C = flags;
                    return;
                }
            }
            if (reset_actor_action_state(action_actor, context, sprite, &D_801741C4) != 0) {
                return;
            }
        }
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if (status->flags1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, status);
            return;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
        }
        if (((S_801711A4_2 *)sprite)->unk_2C != &D_8017418C) {
            (*(void **)((u8 *)sprite + 0x2C)) = &D_8017418C;
            select_sprite_entry(sprite, *(((u8 *)&D_8017418C) + (((s32) (g_game_work.view.viewAngle + status->facing + 0x100)
                >> 9) & 7)), 0);
            ((S_801711A4_2 *)sprite)->unk_05 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_AE = 0;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
        }
        status->flags1C = (s32) (status->flags1C | 0x40000);
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF7);
        if (status->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, &D_80174194) != 0) {
                return;
            }
        }
        if (status->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, status);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
            func_80173D10(actor, context, sprite, status);
            return;
        }
        if ((can_entity_gain_level(status) << 0x10) != 0) {
            process_selected_actor_record(actor, context, sprite, status);
        }
    }
    room_id = find_active_rect_containing_point(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v);
    ((S_801711A4_2 *)sprite)->unk_26 = room_id;
    if (status->unk_6D > 0) {
        if (status->flags1C & 0x20) {
            update_actor_status_and_food(status);
            return;
        }
        if (((S_801711A4_2 *)sprite)->unk_24.at00u.v != *(u16 *)(&D_80082E80.tileX)) {
            if (!(status->unk_46 & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(status, ((s32)D_800814A8->unk_58) + 0x20) << 0x10) != 0) {
                        return;
                    }
                }
                if ((func_801722B8(actor, context, sprite, 0) << 0x10) == 0) {
                    return;
                }
                action_flags = status->unk_46 | 0x4000;
                status->unk_46 = action_flags;
            }
            if (status->unk_46 & 0x8000) {
                action_id = status->unk_46 & 0x3FFF;
                switch (action_id) {
                case 8:
                case 9:
                    if ((func_80171FCC(actor, context, sprite, status) << 0x10) != 0) {
                        return;
                    }
                    func_80172190(actor, context, sprite, status);
                    return;
                case 5:
                case 6:
                case 7:
                    angle = get_rounded_facing_and_rounding_flag(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY, &direction_aux);
                    active_actor = D_800814A8;
                    status->facing = angle;
                    if (active_actor->unk_9A == 0x11) {
                        next_handler = &update_actor_animation_and_dispatch;
                        begin_actor_spell_action(actor, context, sprite, &D_801741AC, next_handler);
                        return;
                    }
                case 12:
                    update_actor_status_and_food(status);
                    return;
                case 1:
                case 2:
                case 3:
                    next_handler = &update_actor_animation_and_dispatch;
                    begin_actor_spell_action(actor, context, sprite, &D_801741AC, next_handler);
                    return;
                case 4:
                case 10:
                case 11:
                default:
                    break;
                }
            }
        }
        func_80171884(actor, context, sprite, status);
        return;
    }
    status_flags = status->flags1C;
    if (status_flags & 0x2000) {
        return;
    }
    if (room_id >= 0) {
        if (D_800E2970[room_id].flags & 2) {
            return;
        }
    }
    if (status_flags & 0x430) {
        return;
    }
    if ((compare_monster_neighbor_values(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v,
        D_80082E80.tileX, D_80082E80.tileY) << 0x10) == 0) {
        return;
    }
    direction_aux_ptr = &direction_aux;
    angle = get_rounded_facing_and_rounding_flag(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v,
        D_80082E80.tileX, D_80082E80.tileY, direction_aux_ptr, ({  empty_arg; }));
    status->facing = angle;
    return;
}
