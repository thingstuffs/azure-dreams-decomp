#include "shared/audio_commands.h"
#include "common.h"
#include "sdk/libc.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "engine/scene.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/player/object.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x1C];
    u32 field_1C;
    u8 pad_20[0xA];
    union {
        s16 s16;
        u16 u16;
    } field_2A;
    u8 pad_2C[0x1A];
    u16 field_46;
    u8 pad_48[0x18];
    void *field_60;
    u8 pad_64[0x9];
    u8 field_6D;
    u8 pad_6E[0x4];
    union {
        s8 s8;
        u8 u8;
    } field_72;
    union {
        s8 s8;
        u8 u8;
    } field_73;
} ActorFieldView_810318E4;

typedef struct {
    u8 pad_00[0xA6];
    u16 field_A6;
} ActiveFieldView_810318E4;

typedef struct Copy48 {
    u32 words[12];
} Copy48;

extern void select_sprite_entry(void *, u8, s32);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, void *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

extern u8 D_801708D4;

#include "dungeon/monster/glacier.h"
#include "dungeon/item.h"
extern u8 D_801760FC[];

typedef struct S_801730E4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801730E4_2;   /* linked in advance_selected_item_action_2 */

typedef struct S_801730E4_5 {
    u8 pad_00[0x94];
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_801730E4_5;   /* part in advance_selected_item_action_2 */

typedef struct S_801730E4_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_801730E4_7;   /* target in advance_selected_item_action_2 */

typedef struct S_801730E4_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_801730E4_8;   /* held_base in advance_selected_item_action_2 */

typedef struct S_801730E4_9 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801730E4_9;   /* source in advance_selected_item_action_2 */

/* Advances the selected item's action, visual effect, and cleanup states. */
/* Starts a targeted spell with an attached copied sprite, waits for its animation, then recenters and
 * updates status. */
void advance_selected_item_action_2(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 position_delta[3];
    s16 is_special;
    void *active;
    u32 linked;
    u8 linked_x;
    u8 linked_y;
    u8 *selection;
    u8 *owner_object;
    u8 state;

    is_special = 0;
    owner_object = (u8 *)body - 0x20;
    state = body->action_phase.u;
    switch (state) {
    case 0:
        if ((actor->flags1C) & 0x2000) {
            switch ((actor->action_flags) & 0x3FFF) {
            case 7:
                is_special = 1;
                /* fallthrough */
            case 3:
                selection = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
                /* fallthrough */
            case 2:
                selection = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
                /* fallthrough */
            case 1:
                selection = (u8 *)actor + 8;
                break;
            default:
                selection = 0;
                break;
            }
        } else {
            switch ((actor->action_flags) & 0x3FFF) {
            case 3:
                selection = (u8 *)actor + 0xE;
                break;
            case 2:
                selection = (u8 *)actor + 0xB;
                break;
            case 1:
                selection = (u8 *)actor + 8;
                break;
            default:
                selection = 0;
                break;
            }
        }

        if (*selection != 0) {
            body->action_state_flags &= 0xFF7F;
            {
                s32 use_special = is_special;

                if (use_special != 0) {
                    active = primary_actor_record;
                    (actor->target) = active;
                    linked = (u32)*(u8 * *)&((ObjectNodeHeader *)((u8 *)active - 0x20))->sprite;
                    (actor->target_tile_x) = ((S_801730E4_2 *)linked)->unk_24;
                    (actor->target_tile_y) = ((S_801730E4_2 *)linked)->unk_25;
                } else {
                    linked = item_action_definitions[*selection].kind;
                    if (linked == 2) {
                        active = (actor->target);
                        if (active != 0) {
                            linked = (u32)*(u8 * *)&((ObjectNodeHeader *)((u8 *)active - 0x20))->sprite;
                            (actor->target_tile_x) = ((S_801730E4_2 *)linked)->unk_24;
                            (actor->target_tile_y) = ((S_801730E4_2 *)linked)->unk_25;
                        }
                    } else {
                        {
                            s32 target_x;
                            s32 target_y;

                            target_x = (s32)scan_actor_along_heading(
                                actor, sprite->tile_x, sprite->tile_y,
                                (actor->facing), 0x10);
                            actor->target = (void *)target_x;
                            target_x = abs(actor->target_tile_x);
                            target_y = abs(actor->target_tile_y);
                            (actor->target_tile_x) = target_x;
                            (actor->target_tile_y) = target_y;
                        }
                    }
                }
            }

            if (create_actor_spell_effect(actor, selection, is_special, (u8 *)body + 0x98) == 0) {
                return;
            }
            body->action_timer.u = 10;
            body->action_phase.u++;
            play_sound_if_enabled(0x703);
            return;
        }
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        {
            void *inner_active_actor;

            inner_active_actor = primary_actor_record;
            g_dungeon_status.active_actor = 0;
            (((ActiveFieldView_810318E4 *)inner_active_actor)->field_A6)--;
        }
        advance_status_timers(actor);
        (actor->pending_turn_updates)--;
        body->unk_8C.address = update_actor_timed_effects;
        (actor->target_tile_y) = 0;
        (actor->target_tile_x) = 0;
        (actor->action_flags) &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        body->action_timer.u = 10;
        body->action_phase.u++;
        {
            ObjectNodeHeader *effect_object;

            effect_object = allocate_list_node(0x112, &scene_object_list_anchor.next);
            if (effect_object != 0) {
                S_801730E4_5 *effect_state;
                u8 *effect_data;
                void *owner_sprite;
                u8 animation_id;

                effect_state = (S_801730E4_5 *)(((u8 *)effect_object) + 0x20);
                effect_state->unk_96 = 0xF;
                effect_object->update_callback = &D_801708D4;
                effect_state->unk_A8 = position;
                effect_state->unk_94 = (actor->facing);
                effect_data = *(u8 * *)&effect_object->sprite;
                *(Copy48 *)effect_data = *(Copy48 *)sprite;
                ((S_801730E4_7 *)effect_data)->unk_1E = 0x1000;
                ((S_801730E4_7 *)effect_data)->unk_1C = 0x1000;
                ((S_801730E4_7 *)effect_data)->unk_0E = 0x80;
                ((S_801730E4_7 *)effect_data)->unk_0D = 0x80;
                ((S_801730E4_7 *)effect_data)->unk_0C = 0x80;
                register_node(effect_object, project_sprite_chain);
                animation_id = D_801760FC[0];
                ((S_801730E4_7 *)effect_data)->unk_2C = D_801760FC;
                select_sprite_entry(effect_data, animation_id, 0);
                ((S_801730E4_7 *)effect_data)->unk_10 = 0x20;
                ((S_801730E4_7 *)effect_data)->unk_12 = 0xFF80;
                ((S_801730E4_7 *)effect_data)->unk_14 |= 0xC;

                owner_sprite = ((S_801730E4_8 *)owner_object)->unk_0C;
                effect_data = *(u8 * *)&effect_object->position;
                if (resolve_record_orientation_or_fallback(((S_801730E4_9 *)owner_sprite)->unk_08, owner_sprite, position_delta, 0) != 0) {
                    ((S_801730E4_7 *)effect_data)->unk_02 = ((u16)position->x.w.i);
                    ((S_801730E4_7 *)effect_data)->unk_06 = ((u16)position->y.w.i);
                    ((S_801730E4_7 *)effect_data)->unk_0A = ((u16)position->z.w.i);
                    ((S_801730E4_7 *)effect_data)->unk_02 += position_delta[0];
                    ((S_801730E4_7 *)effect_data)->unk_06 += position_delta[1];
                    ((S_801730E4_7 *)effect_data)->unk_0A += position_delta[2];
                }
            }
        }

    case 2:
        {
            u16 timer;

            timer = body->action_timer.u - 1;
            body->action_timer.u = timer;
            if ((s16)timer > 0 && !(sprite->flags & 0xE000)) {
                return;
            }
        }
        body->action_state_flags |= 0x80;
        body->action_phase.u++;
        return;

    case 3:
        if ((sprite->unk_04 == 2 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            sprite->flags |= 0x800;
            body->action_timer.u = 0x14;
        }
        {
            u16 timer;

            if ((g_dungeon_status.active_actor) == 0) {
                body->action_timer.u = 0;
            }
            timer = body->action_timer.u - 1;
            body->action_timer.u = timer;
            if ((s16)timer <= 0) {
                body->action_timer.u = 0;
                sprite->flags &= 0xF7FF;
            }
            if (!(sprite->flags & 0xE000)) {
                return;
            }

            position->velocity_z = 0;
            position->velocity_y = 0;
            position->velocity_x = 0;
            set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
            if (*(u8 * *)&sprite->frameTable != glacier_direction_frames) {
                s32 direction_index;

                sprite->frameTable = glacier_direction_frames;
                direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + (actor->facing) + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, glacier_direction_frames[direction_index], 0);
                sprite->flags &= 0xF7FF;
            }
            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        body->unk_8C.address = update_actor_timed_effects;
        advance_status_timers(actor);
        (actor->target_tile_y) = 0;
        (actor->target_tile_x) = 0;
        (actor->pending_turn_updates)--;
        (actor->action_flags) &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;
    default:
        return;
    }
}
