#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_80174218(void *, void *, void *, void *);

extern u8 D_80171400[];
extern u8 D_80175180[];
extern u8 D_80175188[];

typedef struct S_80173ED8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_80173ED8_0;   /* arg0 in advance_entity_animation_actions */

typedef struct S_80173ED8_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173ED8_2;   /* counter in advance_entity_animation_actions */

typedef struct S_80173ED8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173ED8_4;   /* global in advance_entity_animation_actions */

typedef struct S_80173ED8_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80173ED8_5;   /* owner in advance_entity_animation_actions */

/* Advances entity animation states and handles pending actions. */
void advance_entity_animation_actions(void *action, void *context, void *sprite, void *entity)
{
    void *saved_context;
    register void *dungeon_state;
    void *saved_entity;
    u8 state;
    s32 direction;

    saved_context = context;
#define action action
#define context saved_context
#define sprite sprite

    state = ((S_80173ED8_0 *)action)->unk_9B;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        u8 *counter_state;

        if ((((SpriteFrameState *)sprite)->flags & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&g_dungeon_status.unk_00;
        ((S_80173ED8_2 *)counter_state)->unk_0A--;
        ((SpriteFrameState *)sprite)->frameTable = D_80175188;
        direction = (g_game_work.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite, D_80175188[direction & 7], 0);
        ((S_80173ED8_0 *)action)->unk_9B++;
        return;
    }

    case 1:
        if (((EntityRec *)entity)->tileY != 0) {
            register u8 *counter_state;

            ((SpriteFrameState *)sprite)->frameTable = D_80175180;
            direction = (g_game_work.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
            select_sprite_entry(sprite, D_80175180[direction & 7], 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            counter_state = (u8 *)&g_dungeon_status.unk_00;
            ((S_80173ED8_2 *)counter_state)->unk_0A++;
            ((S_80173ED8_0 *)action)->unk_9B++;
            return;
        }

        dungeon_state = &g_dungeon_status.unk_00;
        if (((S_80173ED8_4 *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if ((((EntityRec *)entity)->unk_64 != 0) &&
            begin_ready_actor_directional_action(action, context, sprite, 0)) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x100) {
            begin_pushed_actor_move(action, context, sprite, entity);
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(action, context, sprite, entity);
            ((S_80173ED8_0 *)action)->unk_A8 = 0;
            func_80174218(action, context, sprite, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            void *owner = D_800814A8;

            if ((check_entity_relation(entity,
                    (u8 *)((S_80173ED8_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_food(entity);
        on_actor_status_updated(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        ((SpriteFrameState *)sprite)->frameTable = D_80175180;
        direction = (g_game_work.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite, D_80175180[direction & 7], 0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        ((S_80173ED8_4 *)dungeon_state)->unk_0A++;

        ((S_80173ED8_0 *)action)->unk_9B++;
        return;

    case 2:
    {
        u8 *counter_state;

        if ((((SpriteFrameState *)sprite)->flags & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&g_dungeon_status.unk_00;
        ((S_80173ED8_2 *)counter_state)->unk_0A--;
        ((EntityRec *)entity)->flags1C &= ~0x208;
        ((S_80173ED8_0 *)action)->unk_8C = D_80171400;
        return;
    }

    default:
        return;
    }
}
