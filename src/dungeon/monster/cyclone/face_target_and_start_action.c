#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"



typedef struct S_801722E4_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801722E4_5_pre;   /* the 0x14 bytes before ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in face_target_and_start_action, addressed as ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv[-1] */



extern void select_sprite_entry();
extern s16 get_rounded_facing_and_rounding_flag();
extern s32 try_claim_dungeon_action_slot();
extern s32 advance_status_timers();
extern s32 select_nearby_target_and_initialize_slot();
extern s32 apply_camera_offset_and_select_target();
extern u8 D_801764A0[];


typedef struct S_801722E4_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801722E4_1;   /* arg2 in face_target_and_start_action */

typedef struct S_801722E4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801722E4_2;

typedef struct S_801722E4_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_801722E4_3;   /* arg0 in face_target_and_start_action */

/* Face the target and initialize the actor action when status checks allow it. */
void face_target_and_start_action(S_801722E4_3 *action_state, s32 event_context, S_801722E4_1 *sprite, EntityRec *actor) {
    s32 distance;
    void *actor_base;
    S_801722E4_2 *target;
    u8 *direction_frames;

    actor->unk_71 =
        (u8)(actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2008)) {
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            actor_base = (s8 *)actor - 0x20;
            apply_camera_offset_and_select_target(actor_base, event_context, 8, 0x300);
            if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
                target = ((S_801722E4_5_pre *)(actor->target))[-1].unk_00;
                actor->facing = get_rounded_facing_and_rounding_flag(
                    sprite->unk_24,
                    sprite->unk_25,
                    target->unk_24,
                    target->unk_25,
                    &distance);
                direction_frames = D_801764A0;
                action_state->unk_9A = 0x17;
                action_state->unk_9B = 0;
                action_state->unk_8C = 0;
                sprite->unk_2C = direction_frames;
                select_sprite_entry(
                    sprite,
                    direction_frames[((s32)(g_game_work.view.viewAngle +
                                    actor->facing + 0x100) >> 9) &
                             7],
                    0);
                advance_status_timers(actor);
                actor->unk_6D =
                    (u8)(((u8)actor->unk_6D) - 1);
                action_state->unk_98 =
                    (u16)(action_state->unk_98 | 8);
                select_nearby_target_and_initialize_slot(actor_base, event_context, 8, 0x300);
            }
        }
    }
}
