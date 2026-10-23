#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor/callback.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
#include "shared/object_node.h"


typedef s32 M2C_UNK;

extern void select_sprite_entry(void *, s32, s32);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_actor_linked_effect(void *);
extern void create_offset_actor_object(void *, void *, void *);

extern void D_80170E94(void *, void *, void *, void *);
extern u8 golem_direction_frames[8];

typedef struct S_801738B4_0 {
    u8 pad_00[0x8C];
    ActorCallback action_callback; /* 0x8C */
    u8 pad_90[0x6];
    u16 wait_ticks; /* 0x96 */
    u16 action_flags; /* 0x98 */
    u8 pad_9A[0x1];
    u8 phase; /* 0x9B */
} S_801738B4_0;   /* arg0 in advance_actor_item_use_sequence */

   /* entity in advance_actor_item_use_sequence */

typedef struct S_801738B4_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801738B4_4;   /* global in advance_actor_item_use_sequence */

/* Advances an actor's item-use sequence and resets its state when the action ends. */
void advance_actor_item_use_sequence(void *action_ctx, ObjectPosition *scene_object, SpriteFrameState *entity, void *actor)
{
    u8 *item;
    s32 special_mode;
    s32 action_state;
    s32 item_selector;
    u16 remaining_ticks;
    s32 target_x;
    s32 target_y;
    void *active_object;
    void *copy_object;
    u8 *action_status;
    s32 use_shared_object;

    special_mode = 0;
    action_state = ((S_801738B4_0 *)action_ctx)->phase;
    switch (action_state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & ACTOR_PLAYER_SIDE) {
            item_selector = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
            switch (item_selector) {
            case 6:
                special_mode = 1;
                /* fall through */
            case 2:
                item = (u8 *)actor + 0x0E;
                break;
            case 5:
                special_mode = 1;
                /* fall through */
            case 1:
                item = (u8 *)actor + 0x0B;
                break;
            case 4:
                special_mode = 1;
                /* fall through */
            case 0:
                item = (u8 *)actor;
                item += 8;
                break;
            default:
                item = 0;
                break;
            }
        } else {
            item_selector = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
            switch (item_selector) {
            case 3:
                item = (u8 *)actor + 0x0E;
                break;
            case 2:
                item = (u8 *)actor + 0x0B;
                break;
            case 1:
                item = (u8 *)actor + 8;
                break;
            default:
                item = 0;
                break;
            }
        }

        if (*item != 0) {

            ((S_801738B4_0 *)action_ctx)->action_flags &= 0xFF7F;
            use_shared_object = (special_mode == 1);
            if (use_shared_object) {
                copy_object = primary_actor_record;
                (*(void **)((u8 *)actor + 0x60)) = copy_object;
                action_status = *(u8 * *)&((ObjectNodeHeader *)((u8 *)copy_object - 0x20))->sprite;
                (*(u8 *)((u8 *)actor + 0x72)) = action_status[0x24];
                (*(u8 *)((u8 *)actor + 0x73)) = action_status[0x25];
            } else if (item_action_definitions[*item].kind == 2) {
                copy_object = (*(void **)((u8 *)actor + 0x60));
                if (copy_object != 0) {
                    action_status = *(u8 * *)&((ObjectNodeHeader *)((u8 *)copy_object - 0x20))->sprite;
                    (*(u8 *)((u8 *)actor + 0x72)) = action_status[0x24];
                    (*(u8 *)((u8 *)actor + 0x73)) = action_status[0x25];
                }
            } else {
                target_x = (s32)scan_actor_along_heading(actor,
                    entity->unk_24,
                    entity->unk_25,
                    (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                (*(void **)((u8 *)actor + 0x60)) = (void *)target_x;
                target_x = __builtin_abs(*(s8 *)((u8 *)actor + 0x72));
                target_y = __builtin_abs(*(s8 *)((u8 *)actor + 0x73));
                (*(s8 *)((u8 *)actor + 0x72)) = target_x;
                (*(s8 *)((u8 *)actor + 0x73)) = target_y;
            }
            if (create_actor_spell_effect(actor, item, special_mode, &((S_801738B4_0 *)action_ctx)->action_flags)) {
                create_actor_linked_effect(actor);
                ((S_801738B4_0 *)action_ctx)->phase++;
            }
            break;
        } else {
            scene_object->velocity_z = 0;
            scene_object->velocity_y = 0;
            scene_object->velocity_x = 0;
            set_record_integer_tile_center(scene_object, entity->unk_24, entity->unk_25);
            active_object = primary_actor_record;
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)active_object + 0xA6))--;
            advance_status_timers(actor);
            (*(u8 *)((u8 *)actor + 0x6D))--;
            ((S_801738B4_0 *)action_ctx)->action_callback = &D_80170E94;
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            break;
        }

    case 1:
        if (get_cd_command_queue_depth()) {
            entity->flags |= 0x0800;
            break;
        }
        entity->flags &= 0xF7FF;
        ((S_801738B4_0 *)action_ctx)->phase++;

    case 2:
        if ((entity->unk_04 == 3 &&
             (entity->flags & 0x1000)) ||
            (entity->flags & 0xE000)) {
            create_offset_actor_object(action_ctx, scene_object, entity);
            ((S_801738B4_0 *)action_ctx)->phase++;
        }

    case 3:
        if ((entity->unk_04 == 4 &&
             (entity->flags & 0x1000)) ||
            (entity->flags & 0xE000)) {
            entity->flags |= 0x0800;
            ((S_801738B4_0 *)action_ctx)->wait_ticks = 1;
            ((S_801738B4_0 *)action_ctx)->action_flags |= 0x0080;
        }

        remaining_ticks = ((S_801738B4_0 *)action_ctx)->wait_ticks - 1;
        ((S_801738B4_0 *)action_ctx)->wait_ticks = remaining_ticks;
        if ((s16)remaining_ticks <= 0) {
            ((S_801738B4_0 *)action_ctx)->wait_ticks = 0;
            entity->flags &= 0xF7FF;
        }
        if (!(entity->flags & 0xE000)) {
            break;
        }

        scene_object->velocity_z = 0;
        scene_object->velocity_y = 0;
        scene_object->velocity_x = 0;
        set_record_integer_tile_center(scene_object, entity->unk_24, entity->unk_25);
        if (*(unsigned char **)&entity->frameTable != golem_direction_frames) {
            (entity->frameTable) = golem_direction_frames;
            select_sprite_entry(entity,
                golem_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7],
                0);
        }

        action_status = (u8 *)&g_dungeon_status.turn_scale;
        if (*(s32 *)&((ObjectNodeHeader *)action_status)->sprite != 0) {
            break;
        }
        ((S_801738B4_4 *)action_status)->unk_0A--;
        ((S_801738B4_0 *)action_ctx)->action_callback = &D_80170E94;
        advance_status_timers(actor);
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u8 *)((u8 *)actor + 0x6D))--;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);

    }

    return;
}
