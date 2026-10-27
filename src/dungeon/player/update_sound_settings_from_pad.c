#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "dungeon/menu.h"
#include "dungeon/player/input.h"
#include "engine/runtime.h"

extern u16 dungeon_camera_targets[];
extern u16 camera_pitch_index[5];
extern s16 camera_pitch_presets[];
extern s16 camera_depth_target[5];
extern u8 animation_tick_scale[16];



#include "dungeon/player/object/action_state.h"
extern u16 camera_depth_index[5];
extern s16 camera_depth_presets[];
s32 queue_view_slot(s32 enable);
s32 set_camera_targets(s32 channel, void *settings, s32 apply);
/* Config-screen input step: apply the pad's sound-setting changes and report whether input is still accepted. */
s32 update_sound_settings_from_pad(void *actor, void *unused_motion,
    void *unused_sprite, void *unused_stats)
{
    GameWork *base;
    short stopped;
    short result;
    s32 changed;
    u16 value;
    u16 input_flags;
    stopped = 0;
    result = 0;
    changed = 0;
    base = &g_game_work;
    if (dungeon_floor_flags & 0x40000) {
        stopped = 1;
    }
    else {
        input_flags = *(u16 *) 0x80013714;
        if (((input_flags & 0xC) || (input_flags & 1)) || (((u8 *) actor)[0x9A] == 0x19)) {
            stopped = 1;
        }
        else
            if ((has_pending_dungeon_activity(0) << 16) == 0) {
                result = 1;
            }
        else {
            stopped = 1;
        }
    }
    if (stopped == 0) {
        if (g_game_work.view.slot[2].callback == 0) {
            if (((base->buttons) & 0x10) == 0) {
                if ((base->buttons) & 8) {
                    changed = 1;
                    dungeon_camera_targets[2] = dungeon_camera_targets[2] - 0x200;
                }
                else
                    if ((base->buttons) & 4) {
                        changed = 1;
                        dungeon_camera_targets[2] = dungeon_camera_targets[2] + 0x200;
                    }
            }
            if ((base->buttons) & 0x10) {
                if ((base->pressed_buttons) & 1) {
                    changed = 1;
                    value = (u16) ((camera_pitch_index[0] + 1) & 3);
                    camera_pitch_index[0] = value;
                    dungeon_camera_targets[0] = (u16) camera_pitch_presets[(u16) value];
                }
            }
            if (changed != 0) {
                g_game_work.view.slot[2].callback = 0;
                queue_view_slot(1);
                set_camera_targets(0, dungeon_camera_targets, 1);
            }
        }
        if ((base->buttons) & 0x10) {
            if ((base->pressed_buttons) & 4) {
                value = (s16) ((camera_depth_index[0] + 1) & 3);
                camera_depth_index[0] = value;
                dungeon_floor_flags |= 0x40;
                camera_depth_target[0] = camera_depth_presets[(u16) value];
            }
        }
        if ((base->buttons) & 0x10) {
            if ((base->pressed_buttons) & 2) {
                advance_wrapped_cycle_index();
            }
        }
        if (test_resident_bit(0xA2) != 0) {
            if ((base->pressed_buttons) & 0xC0000) {
                animation_tick_scale[0] = 1;
            }
            else
                if ((base->buttons) & 0x30000) {
                    animation_tick_scale[0] = 2;
                }
        }
    }
    return result;
}
