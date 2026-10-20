#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef struct
{
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
}
DungeonRecord;
typedef void (*DungeonCallback)(void *, void *, void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void *place_actor_at_directional_neighbor(void *, s32, s32, s32);
extern s32 check_global_or_linked_flag_20000(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_801715F0(void *, void *, void *, void *);
extern void func_80171848(void *, void *, void *, void *);
extern s32 func_80171FF4(void *, void *, void *, void *);
extern void func_801721B8(void *, void *, void *, void *);
extern void advance_actor_walk_animation(void *, void *, void *, void *);
extern s32 func_80172414(void *, void *, void *, s32);
extern void func_80173834(void *, void *, void *, void *);
extern u8 D_80174880[];
extern u8 D_80174890[];
extern u8 D_801748C8;
extern u8 D_801748D8[];
extern u8 D_801748E0[];
extern DungeonRecord D_800E2970[];
void update_creature_animation_action(void *, void *, void *, void *);
/* Update creature animation and dispatch its dungeon action. */
void update_creature_animation_action(void *actor, void *context, void *sprite_arg, void *creature)
{
    s32 direction_aux;
    s8 room_id;
    u16 action;
    void *sprite;
    u32 dungeon_flags = g_dungeon_status.flags;
    if (dungeon_flags & 0x1000) {
        *((u8 *) (((u8 *) actor) + 0x9A)) = 0xE;
        func_801715F0(actor, context, sprite_arg, creature);
        return;
    }
    if ((*((u8 *) (((u8 *) creature) + 0x25))) == 0) {
        void *anim_table;
        advance_actor_pending_action(actor, context, sprite_arg, creature);
        if ((*((void **) (((u8 *) sprite_arg) + 0x2C))) == D_801748E0) {
            return;
        }
        anim_table = D_801748D8;
        *((void **) (((u8 *) sprite_arg) + 0x2C)) = anim_table;
        select_sprite_entry(sprite_arg, ((u8 *) anim_table)[(((g_game_work.view.camera_rotation.parts.viewAngle + (*((s16 *) (((u8 *) creature)
            + 0x2A)))) + 0x100) >> 9) & 7], 0);
        return;
    }
    sprite = sprite_arg;
    if ((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x200) {
        if ((*((void **) (((u8 *) sprite) + 0x2C))) == D_801748E0) {
            *((u8 *) (((u8 *) actor) + 0x9A)) = 0xD;
            *((u8 *) (((u8 *) actor) + 0x9B)) = 1;
            *((s32 *) (((u8 *) actor) + 0x8C)) = 0;
            *((u32 *) (((u8 *) creature) + 0x1C)) &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_801748D8) != 0) {
            return;
        }
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if ((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, creature);
            return;
        }
        {
            register void *current_anim;
            void *anim_table;
            switch (*((u8 *) (((u8 *) actor) + 0x9A))) {
            case 0xE:
                break;

            default:
                *((u8 *) (((u8 *) actor) + 0x9A)) = 0xE;
                break;

            }

            current_anim = *((void **) (((u8 *) sprite) + 0x2C));
            anim_table = D_80174880;
            if (current_anim != anim_table) {
                *((void **) (((u8 *) sprite) + 0x2C)) = anim_table;
                select_sprite_entry(sprite, ((u8 *) anim_table)[(((g_game_work.view.camera_rotation.parts.viewAngle + (*((s16 *) (((u8 *) creature)
                    + 0x2A)))) + 0x100) >> 9) & 7], 0);
                *((u8 *) (((u8 *) sprite) + 5)) = 1;
                *((s16 *) (((u8 *) actor) + 0xA6)) = 0;
                *((s16 *) (((u8 *) actor) + 0xB2)) = 0;
            }
        }
        *((u32 *) (((u8 *) creature) + 0x1C)) |= 0x40000;
        *((u16 *) (((u8 *) actor) + 0x98)) &= 0xFFF7;
        if ((*((s16 *) (((u8 *) creature) + 0x64))) != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80174890) != 0) {
                return;
            }
        }
        if ((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x80000) {
            s16 adjusted_offset;
            begin_actor_move_to_target_facing(actor, context, sprite, creature);
            adjusted_offset = (*((u16 *) (((u8 *) actor) + 0x92))) - (*((u16 *) (((u8 *) actor) + 0xA6)));
            *((s16 *) (((u8 *) actor) + 0xA6)) = 0;
            *((s16 *) (((u8 *) actor) + 0xB2)) = 0;
            *((s16 *) (((u8 *) actor) + 0x92)) = adjusted_offset;
            func_80173834(actor, context, sprite, creature);
            return;
        }
        if ((can_entity_gain_level(creature) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, creature);
        }
    }
    room_id = find_active_rect_containing_point(*((u8 *) (((u8 *) sprite) + 0x24)), *((u8 *) (((u8 *) sprite) + 0x25)));
    *((u8 *) (((u8 *) sprite) + 0x26)) = room_id;
    if ((*((s8 *) (((u8 *) creature) + 0x6D))) > 0) {
        if ((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x20) {
            update_actor_status_and_food(creature);
            return;
        }
        if ((*((u16 *) (((u8 *) sprite) + 0x24))) == (*((u16 *) (((s8 *)&D_80082E80.tile_position.parts.tile_x))))) {
            func_80171848(actor, context, sprite, creature);
            return;
        }
        if (!((*((u16 *) (((u8 *) creature) + 0x46))) & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(creature, ((u8 *) (*((void **) (((u8 *) D_800814A8) + 0x58)))) + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172414(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action = (*((u16 *) (((u8 *) creature) + 0x46))) | 0x4000;
            *((u16 *) (((u8 *) creature) + 0x46)) = action;
            if (!(action & 0x8000)) {
                func_80171848(actor, context, sprite, creature);
                return;
            }
        }
        action = (*((u16 *) (((u8 *) creature) + 0x46))) & 0x3FFF;
        if (((u32) (action - 1)) >= 12) {
            func_80171848(actor, context, sprite, creature);
            return;
        }
        switch (action - 1) {
        case 8:
        {
            void *target = place_actor_at_directional_neighbor(creature, *((u8 *) (((u8 *) sprite) + 0x24)), *((u8 *) (((u8 *) sprite)
                + 0x25)), *((s16 *) (((u8 *) creature) + 0x2A)));
            *((void **) (((u8 *) actor) + 0xA8)) = target;
            if (target == 0) {
                func_80171848(actor, context, sprite, creature);
                return;
            }
            if (check_global_or_linked_flag_20000(target) != 0) {
                func_80171848(actor, context, sprite, creature);
                return;
            }
            if ((*((u8 *) (((u8 *) (*((void **) (((u8 *) actor) + 0xA8)))) + 0x13))) < 0x33) {
                advance_actor_walk_animation(actor, context, sprite, creature);
                return;
            }
            func_80171848(actor, context, sprite, creature);
            return;
        }
        case 7:
            if ((func_80171FF4(actor, context, sprite, creature) << 16) != 0) {
                return;
            }
            func_801721B8(actor, context, sprite, creature);
            return;
        case 4:
        case 5:
        case 6:
        {
            u8 *player_pos = ((u8 *)(&D_80082E80));
            void *player;
            s16 facing_angle;
            facing_angle = get_rounded_facing_and_rounding_flag(*((u8 *) (((u8 *) sprite) + 0x24)), *((u8 *) (((u8 *) sprite) + 0x25)),
                *((u8 *) (((u8 *) player_pos) + 0x24)), *((u8 *) (((u8 *) player_pos) + 0x25)), &direction_aux);
            player = D_800814A8;
            *((s16 *) (((u8 *) creature) + 0x2A)) = facing_angle;
            if ((*((u8 *) (((u8 *) player) + 0x9A))) == 0x11) {
                begin_actor_spell_action(actor, context, sprite, &D_801748C8, update_creature_animation_action);
                return;
            }
        }
        case 11:
            update_actor_status_and_food(creature);
            return;
        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(actor, context, sprite, &D_801748C8, update_creature_animation_action);
            return;
        case 3:
        case 9:
        case 10:
        default:
            func_80171848(actor, context, sprite, creature);
            return;
        }
    }
    if (!((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x2000)) {
        s32 room_index = room_id;
        if ((room_index < 0) || (!(D_800E2970[room_index].flags & 2))) {
            if (!((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x430)) {
                u8 *player_pos = ((u8 *)(&D_80082E80));
                if ((compare_monster_neighbor_values(*((u8 *) (((u8 *) sprite) + 0x24)), *((u8 *) (((u8 *) sprite) + 0x25)),
                    *((u8 *) (((u8 *) player_pos) + 0x24)), *((u8 *) (((u8 *) player_pos) + 0x25))) << 16) != 0) {
                    *((s16 *) (((u8 *) creature) + 0x2A)) = get_rounded_facing_and_rounding_flag(*((u8 *) (((u8 *) sprite) + 0x24)),
                        *((u8 *) (((u8 *) sprite) + 0x25)), *((u8 *) (((u8 *) player_pos) + 0x24)),
                        *((u8 *) (((u8 *) player_pos) + 0x25)), &direction_aux);
                }
            }
        }
    }
    return;

}
