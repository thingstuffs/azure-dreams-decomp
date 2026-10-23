#include "shared/actor_status_ids.h"
#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80083460.h"


extern s32 initialize_timed_motion_step();
extern s32 get_entity_effect_value();
extern s32 clear_slots_of_type();
extern s32 set_sprite_animation_frame();
extern s32 display_formatted_context_message();
extern s32 set_record_integer_tile_center();

extern Rec_D_80083460 D_80083460;
extern u8 D_800DCFF8[];
extern u8 D_800E0597;
extern u8 D_800E05C3;


typedef struct S_80092E90_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80092E90_1;   /* arg2 in update_wake_nearby_monsters */


typedef struct S_80092E90_3 {
    u8 pad_00[0x4];
    union { s16 n; u16 v; u16 n2; } unk_04;   /* accessed as both */
} S_80092E90_3;   /* countBase in update_wake_nearby_monsters */

typedef struct S_80092E90_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80092E90_4;   /* arg0 in update_wake_nearby_monsters */

typedef struct S_80092E90_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    void * unk_5C;
} S_80092E90_5;   /* savedArg3 in update_wake_nearby_monsters */

typedef struct S_80092E90_7_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80092E90_7_pre;   /* the 0x14 bytes before node in update_wake_nearby_monsters, addressed as node[-1] */

typedef struct S_80092E90_7 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_80092E90_7;   /* node in update_wake_nearby_monsters */

typedef struct S_80092E90_9 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80092E90_9;   /* ((S_80092E90_7_pre *)node)[-1].unk_00 in update_wake_nearby_monsters */

/* Move toward the target tile, process matching list entries, and advance the effect state. */
void update_wake_nearby_monsters(void *controller, ObjectPosition *motion, void *actor, void *entry)
{
    s32 found_match;
    s32 tile_origin;
    s32 target_pos;
    s16 match_result;
    s16 frames_left;
    s16 move_frames;
    u16 frame_count;
    u8 state;
    void *count_state;
    void *node;

    move_frames = g_dungeon_status.movement_frames_left;
    if (move_frames != 0) {
        target_pos = ((S_80092E90_1 *)actor)->unk_24 << 6;
        tile_origin = motion->x.w.i - 0x20;
        motion->velocity_x =
            ((target_pos - tile_origin) << 16) / move_frames;
        tile_origin = motion->y.w.i;
        tile_origin -= 0x20;
        target_pos = ((S_80092E90_1 *)actor)->unk_25 << 6;
        motion->velocity_y =
            ((target_pos - tile_origin) << 16) / g_dungeon_status.movement_frames_left;
    } else {
        motion->velocity_x = 0;
        motion->velocity_y = 0;
    }
    count_state = &D_80083460;
    frames_left = ((S_80092E90_3 *)count_state)->unk_04.n;
    frame_count = ((S_80092E90_3 *)count_state)->unk_04.v;
    if (frames_left != 0) {
        ((S_80092E90_3 *)count_state)->unk_04.n2 = frame_count - 1;
    }

    state = ((S_80092E90_4 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (!(((S_80092E90_1 *)actor)->unk_14 & 0xE000)) {
            return;
        }
        initialize_timed_motion_step(0x10, 8);
        (*(void * *)((u8 *)actor + (0x2C))) = D_800DCFF8;
        set_sprite_animation_frame(
            actor,
            D_800DCFF8[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80092E90_5 *)entry)->unk_2A + 0x100) >> 9) & 7],
            0,
            1);
        ((S_80092E90_4 *)controller)->unk_9B++;
        return;

    case 1:
        if (!(((S_80092E90_1 *)actor)->unk_14 & 0xE000)) {
            return;
        }

        found_match = 0;
        if (!((*(u16 *)0x80013714) & 8)) {
            node = (u8 *)((S_80092E90_5 *)entry)->unk_5C + 0x20;
            do {
                if ((reference_tile_object.room_index ==
                     ((S_80092E90_9 *)(((S_80092E90_7_pre *)node)[-1].unk_00))->unk_26) &&
                    ((get_entity_effect_value(node, STATUS_SLEEP) << 16) != 0)) {
                    clear_slots_of_type(node, STATUS_SLEEP);
                    found_match = 1;
                }
                node = (u8 *)((S_80092E90_7 *)node)->unk_5C + 0x20;
            } while (node != entry);

            match_result = found_match;
            {
                void *message;
                if (match_result != 0) {
                    message = &D_800E0597;
                } else {
                    message = &D_800E05C3;
                }
                display_formatted_context_message(message);
            }
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((S_80092E90_1 *)actor)->unk_24, ((S_80092E90_1 *)actor)->unk_25);
        ((S_80092E90_4 *)controller)->unk_8C = handle_player_input;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
    default:
        return;
    }
}
