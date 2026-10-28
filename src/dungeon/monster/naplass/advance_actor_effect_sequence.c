#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/system.h"
#include "engine/node/allocation.h"
#include "engine/graphics.h"

struct SpriteFrameState;
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

s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
void clear_slots_of_type(ActorRecord *owner, s8 match_type);
s32 register_node(ObjectNodeHeader *entry, void *registration_id);
s32 check_entity_relation();
s16 get_tile_chebyshev_distance();
#include "dungeon/player/object/action_state.h"
s32 generate_random_value(void);
extern void on_actor_status_updated(void *actor);
void update_actor_status_and_mp(ActorRecord *entity);
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
s32 advance_actor_pending_action(void *actor_state, void *action, void *status, void *actor);
void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_80171F94(ActorRecord *action_state, ObjectPosition *action_context, void *sprite, ActorRecord *actor);
void advance_actor_effect_sequence(Rec_func_801732A4_arg0 *state, EntityRec *position,struct SpriteFrameState *actor, void *model);
extern u8 effect_update_tag[];
extern u8 naplass_action_continuation_address[];
extern u8 naplass_frame_set[];
extern u8 naplass_frame_set_5[];
extern u8 D_801741EC[];
extern u8 D_801741F4[];
extern u8 D_801741FC[];

/* Advances the actor effect sequence, updating directional animation and its attached effect. */
/* Animates status slot 1, processes MP and turn updates while active, and releases its linked sprite
 * before restoring movement. */
void advance_actor_effect_sequence_2(ActorRecord *body, void *transform, SpriteFrameState *sprite, void *actor_state) {
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
    ObjectNodeHeader *effect_node;
    void *effect_transform;
    void *active_effect;
    TileObject *player_sprite;

    phase = ((Rec_func_801732A4_arg0 *)body)->unk_9B;
    switch (phase) {
    default:
        return;
    case 0:
        if (!(sprite->flags & 0xE000))
            return;
        sprite->frameTable = naplass_frame_set;
        select_sprite_entry(sprite, naplass_frame_set[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100)
            >> 9) & 7], 0);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        ((Rec_func_801732A4_arg0 *)body)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)body)->unk_9B + 1);
        return;
    case 1:
        sprite_flags = sprite->flags;
        if (!(sprite_flags & 0x8000)) {
            if (sprite_flags & 0x6000) {
                sprite->flags = (u16)(sprite_flags & 0x9FFF);
                count = ((Rec_func_801732A4_arg0 *)body)->unk_96 + 1;
                ((Rec_func_801732A4_arg0 *)body)->unk_96 = count;
                if (count & 1) {
                    play_sound_if_enabled(0x51B);
                }
            }
        }
        if (g_dungeon_status.flags & 0x1000)
            return;
        if ((get_entity_effect_value(actor_state, STATUS_SLEEP) << 0x10) == 0) {
            sprite->frameTable = naplass_frame_set_5;
            select_sprite_entry(sprite, naplass_frame_set_5[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100)
                >> 9) & 7], 0);
            if (sprite->flags & 0x8000) {
                if (((Rec_func_801732A4_arg0 *)body)->unk_98 & 0x8000) {
                    count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
                    g_dungeon_status.activity_counts.parts.pending_action_count = count;
                    ((Rec_func_801732A4_arg0 *)body)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)body)->unk_9B + 1);
                    return;
                }
                ((S_801732A4_2 *)actor_state)->unk_1C = (s32)(((S_801732A4_2 *)actor_state)->unk_1C & ~ACTOR_ASLEEP);
                body->unk_8C.address = naplass_action_continuation_address;
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
            ((Rec_func_801732A4_arg0 *)body)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)body)->unk_9B + 1);
            return;
        }
        if (((S_801732A4_2 *)actor_state)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(body, transform, sprite, 0) != 0) {
                ((Rec_func_801732A4_arg0 *)body)->unk_98 = (u16)(((Rec_func_801732A4_arg0 *)body)->unk_98 | 0x8000);
                if (((S_801732A4_2 *)actor_state)->unk_25 == 0) {
                    if (g_dungeon_status.flags & 0x2008)
                        return;
                    advance_actor_pending_action(body, transform, sprite, actor_state);
                    return;
                }
                ((Rec_func_801732A4_arg0 *)body)->unk_AA = (u16)((((S_801732A4_2 *)actor_state)->unk_6A
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
            begin_pushed_actor_move(body, transform, sprite, actor_state);
            return;
        }
        if (action_flags & 0x80000) {
            begin_actor_move_to_target_facing(body, transform, sprite, actor_state);
            advance_actor_effect_sequence(body, transform, sprite, actor_state);
            return;
        }
        if (((S_801732A4_2 *)actor_state)->unk_6D == 0)
            return;
        if ((has_pending_actor_or_turn_action(actor_state) << 0x10) != 0) {
            if ((check_entity_relation(actor_state, ((s32)primary_actor_record->previous_actor_header) + 0x20) << 0x10) != 0)
                return;
        }
        update_actor_status_and_mp(actor_state);
        on_actor_status_updated(actor_state);
        if ((get_entity_effect_value(actor_state, STATUS_SLEEP) << 0x10) != 0) {
            player_sprite = &reference_tile_object;
            region_id = *(s8 *)&sprite->room_index;
            if (region_id == player_sprite->room_index && region_id >= 0) {
                if (!(generate_random_value() & 7)) {
                    clear_slots_of_type(actor_state, STATUS_SLEEP);
                }
            } else if (get_tile_chebyshev_distance(player_sprite, sprite) < 2) {
                if (!(generate_random_value() & 7)) {
                    clear_slots_of_type(actor_state, STATUS_SLEEP);
                }
            }
            if (((Rec_func_801732A4_arg0 *)body)->unk_98 & 0x8000) {
                clear_slots_of_type(actor_state, STATUS_SLEEP);
            }
        }
        if ((get_entity_effect_value(actor_state, STATUS_SLEEP) << 0x10) != 0)
            return;
        sprite->frameTable = naplass_frame_set_5;
        select_sprite_entry(sprite, naplass_frame_set_5[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100)
            >> 9) & 7], 0);
        if (sprite->flags & 0x8000) {
            if (!(((Rec_func_801732A4_arg0 *)body)->unk_98 & 0x8000)) {
                ((S_801732A4_2 *)actor_state)->unk_1C = (s32)(((S_801732A4_2 *)actor_state)->unk_1C & ~ACTOR_ASLEEP);
                body->unk_8C.address = naplass_action_continuation_address;
                return;
            }
            {
                actor_flags = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
                g_dungeon_status.activity_counts.parts.pending_action_count = actor_flags;
            }
            ((Rec_func_801732A4_arg0 *)body)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)body)->unk_9B + 1);
            return;
        }
        {
            actor_flags = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(actor_flags + 1);
        }
        ((Rec_func_801732A4_arg0 *)body)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)body)->unk_9B + 1);
        return;
    case 2:
        if (!(sprite->flags & 0xE000))
            return;
        sprite->frameTable = D_801741EC;
        select_sprite_entry(sprite, D_801741EC[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100)
            >> 9) & 7], 0);
        ((Rec_func_801732A4_arg0 *)body)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)body)->unk_9B + 1);
        return;
    case 3:
        if (!(sprite->flags & 0xE000))
            return;
        sprite->frameTable = D_801741F4;
        select_sprite_entry(sprite, D_801741F4[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A + 0x100)
            >> 9) & 7], 0);
        ((Rec_func_801732A4_arg0 *)body)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)body)->unk_9B + 1);
        new_effect = allocate_list_node(0x112, &scene_object_list_anchor.next);
        ((Rec_func_801732A4_arg0 *)body)->unk_A0 = new_effect;
        /* BYTES: The action register is reused for the effect node after allocation. */
        body = new_effect;
        effect_node = new_effect;
        if (body == NULL)
            return;
        register_node(effect_node, project_sprite_chain);
        effect_transform = effect_node->position;
        effect_node->update_callback = effect_update_tag;
        *(Copy24 *)effect_transform = *(Copy24 *)transform;
        ((Rec_func_801732A4_arg0 *)body)->unk_BB = 0;
        effect_sprite = effect_node->sprite;
        ((Rec_func_801732A4_arg0 *)body)->unk_4A = (u16)((S_801732A4_2 *)actor_state)->unk_2A;
        sprite_data = sprite->animation_resource;
        effect_sprite->scale_y = 0x1000;
        effect_sprite->scale_x = 0x1000;
        effect_sprite->animation_resource = sprite_data;
        effect_sprite->flags = (u16)sprite->flags;
        effect_sprite->clut = (u16)sprite->clut;
        effect_sprite->color.word = (s32)sprite->color.word;
        effect_sprite->frameTable = D_801741FC;
        select_sprite_entry(effect_sprite, D_801741FC[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801732A4_2 *)actor_state)->unk_2A
            + 0x100) >> 9) & 7], 0);
        return;
    case 4:
        if (!(sprite->flags & 0xE000))
            return;
        active_effect = ((Rec_func_801732A4_arg0 *)body)->unk_A0;
        if (active_effect != NULL) {
            ((S_801732A4_8 *)active_effect)->unk_BB = 0xFF;
            ((Rec_func_801732A4_arg0 *)body)->unk_A0 = NULL;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        ((S_801732A4_2 *)actor_state)->unk_1C = (s32)(((S_801732A4_2 *)actor_state)->unk_1C & ~ACTOR_ASLEEP);
        effect_flags = ((Rec_func_801732A4_arg0 *)body)->unk_98;
        if (effect_flags & 0x8000) {
            ((Rec_func_801732A4_arg0 *)body)->unk_98 = (u16)(effect_flags & 0x7FFF);
            ((S_801732A4_2 *)actor_state)->unk_2A = (s16)((Rec_func_801732A4_arg0 *)body)->unk_AA;
            ((S_801732A4_2 *)actor_state)->unk_6D = (s8)((u8)((S_801732A4_2 *)actor_state)->unk_6D + 1);
            ((Rec_func_801732A4_arg0 *)body)->unk_9B = (u8)(((Rec_func_801732A4_arg0 *)body)->unk_9B + 1);
            return;
        }
        body->unk_8C.address = naplass_action_continuation_address;
        return;
    case 5:
        func_80171F94(body, transform, sprite, actor_state);
        return;
    }
}
