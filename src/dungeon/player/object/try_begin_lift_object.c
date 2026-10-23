#include "shared/actor_status_flags.h"
#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "shared/entity.h"

typedef struct S_80048A44_Obj S_80048A44_Obj;
extern u8 resident_globals_page[];


void set_sprite_animation_frame(S_80048A44_Obj *obj, s16 frame_group, s16 frame_index, s32 slot_index);
extern void adjust_source_value_and_finalize();
extern s32 spawn_object_at_target_position();
extern void append_packed_action_record();
extern s32 play_sound_if_enabled();
extern u8 player_lift_frames[];
extern u8 D_800E0495[];


typedef struct S_8008C5C4_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8008C5C4_1;   /* arg2 in try_begin_lift_object */

typedef struct S_8008C5C4_2 {
    u8 pad_00[0x8C];
    union { void * p; u8 * p2; } unk_8C;   /* accessed as both */
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x80];
    s32 unk_11C;
    u8 pad_120[0x4];
    s32 unk_124;
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

typedef struct S_8008C5C4_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008C5C4_5;

typedef struct S_8008C5C4_6 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8008C5C4_6;   /* ((S_8008C5C4_2 *)arg0)->unk_124 in try_begin_lift_object */

/* Find a target ahead of the actor and initialize the interaction state. */
s32 try_begin_lift_object(S_8008C5C4_2 *action, void *unused, S_8008C5C4_1 *position, EntityRec *actor) {
    s32 target;
    s32 target_result;
    s32 direction_offset;
    s32 result;
    u32 tail_page;
    s32 tail_result;
    s32 mode;
    register s32 target_kind;

    direction_offset = ((u16)((u16)actor->facing) >> 8) & 0xE;
    target_result = spawn_object_at_target_position(
        actor,
        (s16)(position->unk_24 + *(u16 *)(((u8 *)dir_step_x) + direction_offset)),
        (s16)(position->unk_25 + *(u16 *)(((u8 *)dir_step_y) + direction_offset)));
    action->unk_124 = target_result;
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
                        if (((s32)g_game_work.pressed_buttons) & 0x40) {
                            play_sound_if_enabled(0x506);
                            adjust_source_value_and_finalize(action->unk_124, &D_800E0495);
                            tail_result = 0;
                        } else {
                            tail_result = 0;
                        }
                        tail_page = (u32)resident_globals_page;
                        ((S_8008C5C4_4 *)((void *)tail_page))->unk_1484 = 0;
                        action->unk_124 = 0;
                        action->unk_8C.p = (void *)((u32)handle_player_input);
                        return tail_result;
                    }
                }
                target = action->unk_124;
                ((S_8008C5C4_5 *)target)->unk_1C |= 0x80000;
                actor->flags1C |= ACTOR_CARRYING;
                ((S_8008C5C4_6 *)(action->unk_124))->unk_60 = actor;
                append_packed_action_record(actor, 0x20, 0, 0);
                play_sound_if_enabled(0x511);
            }
            action->unk_9A = 0x1B;
            action->unk_9B = 0;
            action->unk_8C.p = 0;
            position->unk_2C = player_lift_frames;
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
