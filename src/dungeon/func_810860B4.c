#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"


typedef s32 M2C_UNK;

extern s32 get_cd_command_queue_depth(void);
extern void func_80047784(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_actor_linked_effect(void *);
extern void create_offset_actor_object(void *, void *, void *);

extern M2C_UNK D_80170E94;
extern u8 D_80175F10[8];


typedef struct S_801738B4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801738B4_0;   /* arg0 in advance_actor_item_use_sequence */

typedef struct S_801738B4_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_801738B4_1_pre;   /* the 0x14 bytes before copy_object in advance_actor_item_use_sequence, addressed as copy_object[-1] */

   /* entity in advance_actor_item_use_sequence */


typedef struct S_801738B4_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801738B4_4;   /* global in advance_actor_item_use_sequence */

/* Advances an actor's item-use sequence and resets its state when the action ends. */
void advance_actor_item_use_sequence(void *action_ctx, EntityRec *scene_object, void *entity, void *actor)
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
    action_state = ((S_801738B4_0 *)action_ctx)->unk_9B;
    switch (action_state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
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

            ((S_801738B4_0 *)action_ctx)->unk_98 &= 0xFF7F;
            use_shared_object = (special_mode == 1);
            if (use_shared_object) {
                copy_object = D_800814A8;
                (*(void * *)((u8 *)actor + 0x60)) = copy_object;
                action_status = ((S_801738B4_1_pre *)copy_object)[-1].unk_00;
                (*(u8 *)((u8 *)actor + 0x72)) = action_status[0x24];
                (*(u8 *)((u8 *)actor + 0x73)) = action_status[0x25];
            } else if (D_8006DE24[*item].kind == 2) {
                copy_object = (*(void * *)((u8 *)actor + 0x60));
                if (copy_object != 0) {
                    action_status = ((S_801738B4_1_pre *)copy_object)[-1].unk_00;
                    (*(u8 *)((u8 *)actor + 0x72)) = action_status[0x24];
                    (*(u8 *)((u8 *)actor + 0x73)) = action_status[0x25];
                }
            } else {
                target_x = (s32)scan_monster_along_heading(actor,
                    ((SpriteAnimationTableView *)entity)->unk_24,
                    ((SpriteAnimationTableView *)entity)->unk_25,
                    (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                (*(void * *)((u8 *)actor + 0x60)) = (void *)target_x;
                target_x = __builtin_abs(*(s8 *)((u8 *)actor + 0x72));
                target_y = __builtin_abs(*(s8 *)((u8 *)actor + 0x73));
                (*(s8 *)((u8 *)actor + 0x72)) = target_x;
                (*(s8 *)((u8 *)actor + 0x73)) = target_y;
            }
            if (create_actor_spell_effect(actor, item, special_mode, &((S_801738B4_0 *)action_ctx)->unk_98)) {
                create_actor_linked_effect(actor);
                ((S_801738B4_0 *)action_ctx)->unk_9B++;
            }
            break;
        } else {
            scene_object->flags14 = 0;
            scene_object->unk_10 = 0;
            scene_object->unk_0C = 0;
            set_record_integer_tile_center(scene_object, ((SpriteAnimationTableView *)entity)->unk_24, ((SpriteAnimationTableView *)entity)->unk_25);
            active_object = D_800814A8;
            g_dungeon_status.unk_0C = 0;
            (*(u16 *)((u8 *)active_object + 0xA6))--;
            advance_status_timers(actor);
            (*(u8 *)((u8 *)actor + 0x6D))--;
            ((S_801738B4_0 *)action_ctx)->unk_8C = &D_80170E94;
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            break;
        }

    case 1:
        if (get_cd_command_queue_depth()) {
            ((SpriteAnimationTableView *)entity)->unk_14 |= 0x0800;
            break;
        }
        ((SpriteAnimationTableView *)entity)->unk_14 &= 0xF7FF;
        ((S_801738B4_0 *)action_ctx)->unk_9B++;

    case 2:
        if ((((SpriteAnimationTableView *)entity)->unk_04 == 3 &&
             (((SpriteAnimationTableView *)entity)->unk_14 & 0x1000)) ||
            (((SpriteAnimationTableView *)entity)->unk_14 & 0xE000)) {
            create_offset_actor_object(action_ctx, scene_object, entity);
            ((S_801738B4_0 *)action_ctx)->unk_9B++;
        }

    case 3:
        if ((((SpriteAnimationTableView *)entity)->unk_04 == 4 &&
             (((SpriteAnimationTableView *)entity)->unk_14 & 0x1000)) ||
            (((SpriteAnimationTableView *)entity)->unk_14 & 0xE000)) {
            ((SpriteAnimationTableView *)entity)->unk_14 |= 0x0800;
            ((S_801738B4_0 *)action_ctx)->unk_96 = 1;
            ((S_801738B4_0 *)action_ctx)->unk_98 |= 0x0080;
        }

        remaining_ticks = ((S_801738B4_0 *)action_ctx)->unk_96 - 1;
        ((S_801738B4_0 *)action_ctx)->unk_96 = remaining_ticks;
        if ((s16)remaining_ticks <= 0) {
            ((S_801738B4_0 *)action_ctx)->unk_96 = 0;
            ((SpriteAnimationTableView *)entity)->unk_14 &= 0xF7FF;
        }
        if (!(((SpriteAnimationTableView *)entity)->unk_14 & 0xE000)) {
            break;
        }

        scene_object->flags14 = 0;
        scene_object->unk_10 = 0;
        scene_object->unk_0C = 0;
        set_record_integer_tile_center(scene_object, ((SpriteAnimationTableView *)entity)->unk_24, ((SpriteAnimationTableView *)entity)->unk_25);
        if (((SpriteAnimationTableView *)entity)->unk_2C != D_80175F10) {
            (*(u8 * *)((u8 *)entity + 0x2C)) = D_80175F10;
            func_80047784(entity,
                D_80175F10[((g_game_work.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7],
                0);
        }

        action_status = (u8 *)&g_dungeon_status.unk_00;
        if (((S_801738B4_4 *)action_status)->unk_0C != 0) {
            break;
        }
        ((S_801738B4_4 *)action_status)->unk_0A--;
        ((S_801738B4_0 *)action_ctx)->unk_8C = &D_80170E94;
        advance_status_timers(actor);
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u8 *)((u8 *)actor + 0x6D))--;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        play_sound_if_enabled(0xB4);

    }

    return;
}
