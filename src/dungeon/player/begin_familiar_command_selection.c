#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "records/Rec_func_8008D024_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/menu.h"
#include "dungeon/player.h"

typedef struct {
    s8 pad_00[0x2A];
    s16 field_2A;
} Arg0;

extern u8 player_carry_frames[8];
extern u8 player_wait_frames[8];

extern void create_panel_effect_object(void *);
extern void set_sprite_animation_frame(void *, u8, s32, s32);

typedef struct S_8008D024_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8008D024_0;

typedef struct S_8008D024_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008D024_1;

/* Selects an eligible linked target and initializes the actor's action and directional display. */
s32 begin_familiar_command_selection(Rec_func_8008D024_arg0 *actor, s32 context, SpriteFrameState *display, s32 target_index,
    s32 action_mode) {
    s32 target_flags;
    s32 slot_offset;
    S_8008D024_1 *target;
    Arg0 *actor_heading;
    s8 *slot_base;
    u8 *direction_frames;
    s16 saved_mode;

    slot_offset = (s32)(target_index << 0x10) >> 0xE;
    slot_base = (s8 *)((s32)slot_offset + (s32)actor);
    actor_heading = actor;
    target = ((S_8008D024_0 *)slot_base)->unk_AC;
    saved_mode = action_mode;
    if (target != 0) {
        target_flags = target->unk_1C;
        if (target_flags & 0x20000) {
            if (!(target_flags & 0x80000)) {
                actor->unk_104 = target;
                actor->unk_9A = 0x27;
                actor->unk_9B.as_s8 = 0;
                actor->unk_8C = 0;
                create_panel_effect_object(target);
                if ((action_mode << 0x10) == 0) {
                    build_floating_number_widget(0x21, 0xE0, 0x84, 0, 0, 0);
                    build_floating_number_widget(0x22, 0xF2, 0x98, 1, 0, 2);
                    build_floating_number_widget(0x24, 0xCE, 0x98, 2, 1, 4);
                    build_floating_number_widget(0x23, 0xE0, 0xAC, 3, 1, 6);
                    dungeon_floor_flags |= 0x2000;
                }
                if (actor->unk_1C & 0x100000) {
                    direction_frames = player_carry_frames;
                } else {
                    direction_frames = player_wait_frames;
                }
                display->frameTable = direction_frames;
                set_sprite_animation_frame(display, direction_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle
                    + ((Arg0 *)actor_heading)->field_2A + 0x100) >> 9) & 7], 0, 1);
                actor->unk_120 = saved_mode;
                return 1;
            }
        }
    }
    return 0;
}
