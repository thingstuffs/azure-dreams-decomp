#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_801732A4_arg0.h"

typedef struct S_801732A4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x4];
    u16 unk_6A;
    u8 pad_6C[0x1];
    s8 unk_6D;
} S_801732A4_2;   /* arg3 in advance_actor_effect_sequence_2 */

typedef struct S_801732A4_8 {
    u8 pad_00[0xBB];
    u8 unk_BB;
} S_801732A4_8;

typedef struct Copy24 { u32 words[6]; } Copy24;

void *allocate_list_node();
s32 get_entity_effect_value();
void clear_slots_of_type();
s32 register_node();
void select_sprite_entry();
s32 check_entity_relation();
s16 get_tile_chebyshev_distance();
s32 has_pending_actor_or_turn_action();
s32 play_sound_if_enabled();
s32 generate_random_value();
extern void on_actor_status_updated(void *actor);
void update_actor_status_and_food();
void begin_pushed_actor_move();
s32 begin_ready_actor_directional_action();
s32 advance_actor_pending_action();
void begin_actor_move_to_target_facing();
void apply_clamped_actor_value_delta();
extern void func_80171F94(void *action_state, void *action_context, void *sprite, EntityRec *actor);
void advance_actor_effect_sequence();
extern u8 D_800D7960[];
extern u8 D_80170E68[];
extern u8 D_801741DC[];
extern u8 D_801741E4[];
extern u8 D_801741EC[];
extern u8 D_801741F4[];
extern u8 D_801741FC[];

/* Advances the actor effect sequence, updating directional animation and its attached effect. */
void advance_actor_effect_sequence_2(void *actor, void *transform, void *sprite, void *actor_state) {
    s32 actor_flags;
    s32 action_flags;
    s32 sprite_data;
    s8 region_id;
    u16 count;
    u16 sprite_flags;
    u16 effect_flags;
    u8 phase;
    SpriteFrameState *effect_sprite;
    void *new_effect;
    void *effect_transform;
    void *active_effect;
    TileObject *player_sprite;

    phase = ((Rec_func_801732A4_arg0 *)actor)->unk_9B;
    switch (phase) {
    default:
        return;
    case 0:
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000))
            return;
        ((SpriteFrameState *)sprite)->frameTable = D_801741DC;
        select_sprite_entry(sprite, D_801741DC[((g_game_work.view.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100)
            >> 9) & 7], 0);
        g_dungeon_status.unk_0A = (u16)(((u16)g_dungeon_status.unk_0A) - 1);
        ((Rec_func_801732A4_arg0 *)actor)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)actor)->unk_9B + 1);
        return;
    case 1:
        sprite_flags = ((SpriteFrameState *)sprite)->flags;
        if (!(sprite_flags & 0x8000)) {
            if (sprite_flags & 0x6000) {
                ((SpriteFrameState *)sprite)->flags = (u16)(sprite_flags & 0x9FFF);
                count = ((Rec_func_801732A4_arg0 *)actor)->unk_96 + 1;
                ((Rec_func_801732A4_arg0 *)actor)->unk_96 = count;
                if (count & 1) {
                    play_sound_if_enabled(0x51B);
                }
            }
        }
        if (g_dungeon_status.flags & 0x1000)
            return;
        if ((get_entity_effect_value(actor_state, 1) << 0x10) == 0) {
            ((SpriteFrameState *)sprite)->frameTable = D_801741E4;
            select_sprite_entry(sprite, D_801741E4[((g_game_work.view.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100)
                >> 9) & 7], 0);
            if (((SpriteFrameState *)sprite)->flags & 0x8000) {
                if (((Rec_func_801732A4_arg0 *)actor)->unk_98 & 0x8000) {
                    count = ((u16)g_dungeon_status.unk_0A) + 1;
                    g_dungeon_status.unk_0A = count;
                    ((Rec_func_801732A4_arg0 *)actor)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)actor)->unk_9B + 1);
                    return;
                }
                ((S_801732A4_2 *)actor_state)->unk_1C = (s32)(((S_801732A4_2 *)actor_state)->unk_1C & ~0x200);
                ((Rec_func_801732A4_arg0 *)actor)->unk_8C = D_80170E68;
                return;
            }
            g_dungeon_status.unk_0A = (u16)(((u16)g_dungeon_status.unk_0A) + 1);
            ((Rec_func_801732A4_arg0 *)actor)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)actor)->unk_9B + 1);
            return;
        }
        if (((S_801732A4_2 *)actor_state)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, transform, sprite, 0) != 0) {
                ((Rec_func_801732A4_arg0 *)actor)->unk_98 = (u16)(((Rec_func_801732A4_arg0 *)actor)->unk_98 | 0x8000);
                if (((S_801732A4_2 *)actor_state)->unk_25 == 0) {
                    if (g_dungeon_status.flags & 0x2008)
                        return;
                    advance_actor_pending_action(actor, transform, sprite, actor_state);
                    return;
                }
                ((Rec_func_801732A4_arg0 *)actor)->unk_AA = (u16)((((S_801732A4_2 *)actor_state)->unk_6A
                    + 0x800) & 0xFFF);
                return;
            }
        }
        actor_flags = ((S_801732A4_2 *)actor_state)->unk_14;
        if (!(actor_flags & 0x8000)) {
            ((S_801732A4_2 *)actor_state)->unk_14 = (s32)(actor_flags | 0x8000);
            ((S_801732A4_2 *)actor_state)->unk_64 = (s16)((u16)((S_801732A4_2 *)actor_state)->unk_64 + 1);
            apply_clamped_actor_value_delta(actor_state);
        }
        if ((has_pending_actor_or_turn_action(actor_state) << 0x10) != 0)
            return;
        action_flags = ((S_801732A4_2 *)actor_state)->unk_1C;
        if (action_flags & 0x100) {
            begin_pushed_actor_move(actor, transform, sprite, actor_state);
            return;
        }
        if (action_flags & 0x80000) {
            begin_actor_move_to_target_facing(actor, transform, sprite, actor_state);
            advance_actor_effect_sequence(actor, transform, sprite, actor_state);
            return;
        }
        if (((S_801732A4_2 *)actor_state)->unk_6D == 0)
            return;
        if ((has_pending_actor_or_turn_action(actor_state) << 0x10) != 0) {
            if ((check_entity_relation(actor_state, ((s32)D_800814A8->unk_58) + 0x20) << 0x10) != 0)
                return;
        }
        update_actor_status_and_food(actor_state);
        on_actor_status_updated(actor_state);
        if ((get_entity_effect_value(actor_state, 1) << 0x10) != 0) {
            player_sprite = &D_80082E80;
            region_id = *(s8 *)&((SpriteFrameState *)sprite)->unk_26;
            if (region_id == player_sprite->unk_026 && region_id >= 0) {
                if (!(generate_random_value() & 7)) {
                    clear_slots_of_type(actor_state, 1);
                }
            } else if (get_tile_chebyshev_distance(player_sprite, sprite) < 2) {
                if (!(generate_random_value() & 7)) {
                    clear_slots_of_type(actor_state, 1);
                }
            }
            if (((Rec_func_801732A4_arg0 *)actor)->unk_98 & 0x8000) {
                clear_slots_of_type(actor_state, 1);
            }
        }
        if ((get_entity_effect_value(actor_state, 1) << 0x10) != 0)
            return;
        ((SpriteFrameState *)sprite)->frameTable = D_801741E4;
        select_sprite_entry(sprite, D_801741E4[((g_game_work.view.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100)
            >> 9) & 7], 0);
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            if (!(((Rec_func_801732A4_arg0 *)actor)->unk_98 & 0x8000)) {
                ((S_801732A4_2 *)actor_state)->unk_1C = (s32)(((S_801732A4_2 *)actor_state)->unk_1C & ~0x200);
                ((Rec_func_801732A4_arg0 *)actor)->unk_8C = D_80170E68;
                return;
            }
            {
                actor_flags = ((u16)g_dungeon_status.unk_0A) + 1;
                g_dungeon_status.unk_0A = actor_flags;
            }
            ((Rec_func_801732A4_arg0 *)actor)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)actor)->unk_9B + 1);
            return;
        }
        {
            actor_flags = ((u16)g_dungeon_status.unk_0A);
            g_dungeon_status.unk_0A = (u16)(actor_flags + 1);
        }
        ((Rec_func_801732A4_arg0 *)actor)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)actor)->unk_9B + 1);
        return;
    case 2:
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000))
            return;
        ((SpriteFrameState *)sprite)->frameTable = D_801741EC;
        select_sprite_entry(sprite, D_801741EC[((g_game_work.view.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100)
            >> 9) & 7], 0);
        ((Rec_func_801732A4_arg0 *)actor)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)actor)->unk_9B + 1);
        return;
    case 3:
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000))
            return;
        ((SpriteFrameState *)sprite)->frameTable = D_801741F4;
        select_sprite_entry(sprite, D_801741F4[((g_game_work.view.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100)
            >> 9) & 7], 0);
        ((Rec_func_801732A4_arg0 *)actor)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)actor)->unk_9B + 1);
        new_effect = allocate_list_node(0x112, ((void *)&D_80083498.next));
        ((Rec_func_801732A4_arg0 *)actor)->unk_A0 = new_effect;
        actor = new_effect;
        if (actor == NULL)
            return;
        register_node(actor, project_sprite_chain);
        effect_transform = ((Rec_func_801732A4_arg0 *)actor)->unk_08;
        ((Rec_func_801732A4_arg0 *)actor)->unk_10 = D_800D7960;
        *(Copy24 *)effect_transform = *(Copy24 *)transform;
        ((Rec_func_801732A4_arg0 *)actor)->unk_BB = 0;
        effect_sprite = ((Rec_func_801732A4_arg0 *)actor)->unk_0C;
        ((Rec_func_801732A4_arg0 *)actor)->unk_4A = (u16)((S_801732A4_2 *)actor_state)->unk_2A;
        sprite_data = ((SpriteFrameState *)sprite)->unk_28;
        effect_sprite->scale_y = 0x1000;
        effect_sprite->scale_x = 0x1000;
        effect_sprite->unk_28 = sprite_data;
        effect_sprite->flags = (u16)((SpriteFrameState *)sprite)->flags;
        effect_sprite->clut = (u16)((SpriteFrameState *)sprite)->clut;
        effect_sprite->color.word = (s32)((SpriteFrameState *)sprite)->color.word;
        effect_sprite->frameTable = D_801741FC;
        select_sprite_entry(effect_sprite, D_801741FC[((g_game_work.view.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A
            + 0x100) >> 9) & 7], 0);
        return;
    case 4:
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000))
            return;
        active_effect = ((Rec_func_801732A4_arg0 *)actor)->unk_A0;
        if (active_effect != NULL) {
            ((S_801732A4_8 *)active_effect)->unk_BB = 0xFF;
            ((Rec_func_801732A4_arg0 *)actor)->unk_A0 = NULL;
        }
        g_dungeon_status.unk_0A = (u16)(((u16)g_dungeon_status.unk_0A) - 1);
        ((S_801732A4_2 *)actor_state)->unk_1C = (s32)(((S_801732A4_2 *)actor_state)->unk_1C & ~0x200);
        effect_flags = ((Rec_func_801732A4_arg0 *)actor)->unk_98;
        if (effect_flags & 0x8000) {
            ((Rec_func_801732A4_arg0 *)actor)->unk_98 = (u16)(effect_flags & 0x7FFF);
            ((S_801732A4_2 *)actor_state)->unk_2A = (s16)((Rec_func_801732A4_arg0 *)actor)->unk_AA;
            ((S_801732A4_2 *)actor_state)->unk_6D = (s8)((u8)((S_801732A4_2 *)actor_state)->unk_6D + 1);
            ((Rec_func_801732A4_arg0 *)actor)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)actor)->unk_9B + 1);
            return;
        }
        ((Rec_func_801732A4_arg0 *)actor)->unk_8C = D_80170E68;
        return;
    case 5:
        func_80171F94(actor, transform, sprite, actor_state);
        return;
    }
}
