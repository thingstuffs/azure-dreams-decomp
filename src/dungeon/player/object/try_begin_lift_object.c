#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "dungeon/item.h"

extern u8 resident_globals_page[];

void set_sprite_animation_frame(struct SpriteFrameState *obj, s16 frame_group, s16 frame_index, s32 slot_index);
extern s32 spawn_object_at_target_position(); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern s32 play_sound_if_enabled(s32 query_value);
extern u8 player_lift_frames[];
extern u8 D_800E0495[];

typedef struct S_8008C5C4_2 {
    u8 pad_00[0x8C];
    union { void * p; u8 * p2; } unk_8C;   /* accessed as both */
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x80];
    s32 unk_11C;
    u8 pad_120[0x4];
    ActorRecord *unk_124;
} S_8008C5C4_2;   /* arg0 in try_begin_lift_object */

typedef struct S_8008C5C4_3 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
} S_8008C5C4_3;

typedef struct S_8008C5C4_4 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_8008C5C4_4;   /* (void *)tail_page in try_begin_lift_object */

   /* ((S_8008C5C4_2 *)arg0)->unk_124 in try_begin_lift_object */

/* Find a target ahead of the actor and initialize the interaction state. */
s32 try_begin_lift_object(S_8008C5C4_2 *action, void *unused, SpriteAnimationTableView *position, EntityRec *actor) {
    ActorRecord *target;
    s32 target_result;
    s32 direction_offset;
    s32 result;
    u8 * tail_page;
    s32 tail_result;
    s32 mode;
    register s32 target_kind;

    direction_offset = ((u16)((u16)actor->facing) >> 8) & 0xE;
    target_result = spawn_object_at_target_position(
        actor,
        (s16)(position->tile_x + *(u16 *)(((u8 *)dir_step_x) + direction_offset)),
        (s16)(position->tile_y + *(u16 *)(((u8 *)dir_step_y) + direction_offset)));
    action->unk_124 = (ActorRecord *)target_result;
    if (target_result != 0) {
        result = -1;
        if (target_result <= 0) {
            if (!(((S_8008C5C4_3 *)target_result)->unk_14 & 0x80000)) {
                action->unk_11C = target_result;
                action->unk_124 = 0;
            } else {
                mode = *(s32 *)0x80012090;
                if (mode == 1) {
                    target_kind = ((S_8008C5C4_3 *)target_result)->unk_13;
                    if ((target_kind == 0x39) || (target_kind == 2)) {
                        if ((g_game_work.pressed_buttons) & 0x40) {
                            play_sound_if_enabled(0x506);
                            adjust_source_value_and_finalize(action->unk_124, &D_800E0495);
                            tail_result = 0;
                        } else {
                            tail_result = 0;
                        }
                        tail_page = resident_globals_page;
                        ((S_8008C5C4_4 *)((void *)tail_page))->unk_1484 = 0;
                        action->unk_124 = 0;
                        action->unk_8C.p = (void *)((u32)handle_player_input);
                        return tail_result;
                    }
                }
                target = action->unk_124;
                target->flags1C |= 0x80000;
                actor->flags1C |= ACTOR_CARRYING;
                action->unk_124->target = actor;
                append_packed_action_record(actor, 0x20, 0, 0);
                play_sound_if_enabled(0x511);
            }
            action->unk_9A = 0x1B;
            action->unk_9B = 0;
            action->unk_8C.p = 0;
            position->frame_table = player_lift_frames;
            set_sprite_animation_frame(
                position,
                player_lift_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle +
                                  (s16)((u16)actor->facing) + 0x100) >> 9) & 7],
                0, 1);
            tail_result = 1;
            return tail_result;
        }
        return result;
    }
    action->unk_8C.p2 =handle_player_input;
    result = 0;
    return result;
}
