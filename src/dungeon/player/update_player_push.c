#include "shared/dungeon_actor_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80092018_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x84];
    void * unk_124;
} S_80092018_0;   /* arg0 in update_player_push */

typedef struct S_80092018_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
} S_80092018_2;   /* arg3 in update_player_push */

typedef struct S_80092018_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    s32 unk_14;
} S_80092018_3;   /* arg1 in update_player_push */

typedef struct S_80092018_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80092018_4;

typedef struct S_80092018_5 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_80092018_5;

typedef struct S_80092018_7 {
    u8 pad_00[0x60];
    void * unk_60;
    u8 pad_64[0x6];
    u16 unk_6A;
} S_80092018_7;   /* ((S_80092018_0 *)arg0)->unk_124 in update_player_push */

struct D83460_VIEW { s16 pad[3]; s16 divisor[1]; };

void set_sprite_animation_frame();
s32 resolve_player_input_facing();
s32 has_action_input_without_modifier();
void process_unflagged_linked_entries();
void process_unflagged_linked_entries_alt();
void set_record_integer_tile_center();
void spawn_opposite_offset_effect();
extern u8 D_800DD018[];
extern u8 D_800DD020[];
extern u8 D_800DD028[];

/* Updates actor movement and animation through the action states. */
void update_player_push(void *actor, void *motion, void *sprite, void *model) {
    s16 settle_frames;
    s16 move_frames_left;
    s32 heading_or_coord;
    u16 start_frames_left;
    u16 settle_frames_left;
    u16 anim_flags;
    u8 action_state;
    void *attachment;
    s32 *move_state;

    action_state = ((S_80092018_0 *)actor)->unk_9B;
    switch (action_state) {
    case 0:
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != D_800DD028) {
                ((SpriteFrameState *)sprite)->frameTable = D_800DD028;
                set_sprite_animation_frame(sprite, *((((s32) (g_game_work.view.viewAngle + ((S_80092018_2 *)model)->unk_2A + 0x100)
                    >> 9) & 7) + D_800DD028), 0, 1);
                return;
            }
        } else {
            heading_or_coord = resolve_player_input_facing(((S_80092018_0 *)actor)->unk_9E, actor + 0xA2, model + 0x2A) << 0x10;
            if ((heading_or_coord >> 0x10) == 0xFFF) {
                return;
            }
            if ((((u16) ((S_80092018_2 *)model)->unk_2A >> 9) & 7) == ((heading_or_coord >> 0x19) & 7)) {
                return;
            }
            if ((has_action_input_without_modifier(heading_or_coord) << 0x10) == 0) {
                return;
            }
        }
        ((S_80092018_0 *)actor)->unk_8C = handle_player_input;
        return;
    case 16:
        ((S_80092018_3 *)motion)->unk_0C.at02.v = (s16) (*((s16 *)(((u8 *)dir_step_x)
            + (((u16) ((S_80092018_2 *)model)->unk_2A >> 8) & 0xE))) * 8);
        ((S_80092018_3 *)motion)->unk_10.at02.v = (s16) (*((s16 *)(((u8 *)dir_step_y)
            + (((u16) ((S_80092018_2 *)model)->unk_2A >> 8) & 0xE))) * 8);
        start_frames_left = ((S_80092018_0 *)actor)->unk_96.s - 1;
        ((S_80092018_0 *)actor)->unk_96.s = start_frames_left;
        if ((start_frames_left << 0x10) > 0) {
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = D_800DD018;
        set_sprite_animation_frame(sprite, *((((s32) (g_game_work.view.viewAngle + ((S_80092018_2 *)model)->unk_2A + 0x100) >> 9) & 7)
            + D_800DD018), 0, 1);
        attachment = ((S_80092018_0 *)actor)->unk_124;
        ((S_80092018_4 *)attachment)->unk_1C = (s32) (((S_80092018_4 *)attachment)->unk_1C | 0x100);
        ((S_80092018_7 *)(((S_80092018_0 *)actor)->unk_124))->unk_6A = (u16) ((S_80092018_2 *)model)->unk_2A;
        ((S_80092018_7 *)(((S_80092018_0 *)actor)->unk_124))->unk_60 = model;
        ((S_80092018_0 *)actor)->unk_9B = (u8) (((S_80092018_0 *)actor)->unk_9B + 1);
        return;
    case 17:
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            ((SpriteFrameState *)sprite)->frameTable = D_800DD020;
            set_sprite_animation_frame(sprite, *((((s32) (g_game_work.view.viewAngle + ((S_80092018_2 *)model)->unk_2A + 0x100)
                >> 9) & 7) + D_800DD020), 0, 1);
            ((S_80092018_0 *)actor)->unk_9B = (u8) (((S_80092018_0 *)actor)->unk_9B + 1);
        }
    case 18:
        move_state = &g_dungeon_status.unk_00;
        if (((S_80092018_5 *)move_state)->unk_04 != 0) {
            heading_or_coord = ((S_80092018_3 *)motion)->unk_02;
            {
                s32 delta;
                s32 direction_offset;
                delta = ((SpriteFrameState *)sprite)->unk_24 << 6;
                direction_offset = *((s16 *)(((u8 *)dir_step_x) + (((u16) ((S_80092018_2 *)model)->unk_2A
                    >> 8) & 0xE))) * 0x10;
                direction_offset += 0x20;
                delta += direction_offset;
                delta -= heading_or_coord;
                ((S_80092018_3 *)motion)->unk_0C.at00.v = (s32) ((delta
                    << 0x10) / (s16) ((S_80092018_5 *)move_state)->unk_04);
            }
            heading_or_coord = ((S_80092018_3 *)motion)->unk_06;
            {
                s32 delta;
                s32 direction_offset;
                delta = ((SpriteFrameState *)sprite)->unk_25 << 6;
                direction_offset = *((s16 *)(((u8 *)dir_step_y) + (((u16) ((S_80092018_2 *)model)->unk_2A
                    >> 8) & 0xE))) * 0x10;
                direction_offset += 0x20;
                delta += direction_offset;
                delta -= heading_or_coord;
                ((S_80092018_3 *)motion)->unk_10.at00.v = (s32) ((delta
                    << 0x10) / ((struct D83460_VIEW *) move_state)->divisor[-1]);
            }
        }
        if (!((u16) ((S_80092018_5 *)move_state)->unk_04 & 3)) {
            spawn_opposite_offset_effect(motion, ((S_80092018_2 *)model)->unk_2A);
        }
        move_frames_left = (u16) ((S_80092018_5 *)move_state)->unk_04 - 1;
        ((S_80092018_5 *)move_state)->unk_04 = move_frames_left;
        if ((move_frames_left << 0x10) > 0) {
            return;
        }
        ((S_80092018_5 *)move_state)->unk_04 = 0;
        ((S_80092018_3 *)motion)->unk_14 = 0;
        ((S_80092018_3 *)motion)->unk_10.at00.v = 0;
        ((S_80092018_3 *)motion)->unk_0C.at00.v = 0;
        ((SpriteFrameState *)sprite)->frameTable = D_800DD028;
        set_sprite_animation_frame(sprite, *((((s32) (g_game_work.view.viewAngle + ((S_80092018_2 *)model)->unk_2A + 0x100) >> 9) & 7)
            + D_800DD028), 0, 1);
        ((S_80092018_0 *)actor)->unk_96.s = 2U;
        ((S_80092018_0 *)actor)->unk_9B = 0x13U;
        return;
    case 19:
        settle_frames = (s16) ((S_80092018_0 *)actor)->unk_96.s;
        if (settle_frames != 0) {
            {
                s32 delta;
                s32 origin;
                delta = ((SpriteFrameState *)sprite)->unk_24 << 6;
                origin = ((S_80092018_3 *)motion)->unk_02;
                origin -= 0x20;
                delta -= origin;
                ((S_80092018_3 *)motion)->unk_0C.at00.v = (s32) ((delta << 0x10) / settle_frames);
            }
            {
                s32 delta;
                s32 origin;
                origin = ((S_80092018_3 *)motion)->unk_06;
                origin -= 0x20;
                delta = ((SpriteFrameState *)sprite)->unk_25 << 6;
                delta -= origin;
                ((S_80092018_3 *)motion)->unk_10.at00.v = (s32) ((delta
                    << 0x10) / (s16) ((S_80092018_0 *)actor)->unk_96.s);
            }
            if (((S_80092018_0 *)actor)->unk_96.u != 0) {
                settle_frames_left = ((S_80092018_0 *)actor)->unk_96.s - 1;
                ((S_80092018_0 *)actor)->unk_96.s = settle_frames_left;
                if ((settle_frames_left << 0x10) == 0) {
                    ((S_80092018_3 *)motion)->unk_10.at00.v = 0;
                    ((S_80092018_3 *)motion)->unk_0C.at00.v = 0;
                }
            }
        }
        anim_flags = ((SpriteFrameState *)sprite)->flags;
        if (!(anim_flags & 0x8000)) {
            if (!(anim_flags & 0x6000)) {
                return;
            }
            if (((S_80092018_0 *)actor)->unk_96.u != 0) {
                return;
            }
        }
        ((S_80092018_3 *)motion)->unk_14 = 0;
        ((S_80092018_3 *)motion)->unk_10.at00.v = 0;
        ((S_80092018_3 *)motion)->unk_0C.at00.v = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        process_unflagged_linked_entries_alt(((S_80092018_2 *)model)->unk_5C);
        process_unflagged_linked_entries(((S_80092018_2 *)model)->unk_5C);
        {
            DungeonGlobalStatus *action_status = &g_dungeon_status;
            u16 action_flags;
            action_flags = action_status->flags;
            action_flags = (u16) (action_flags | 0x812);
            action_status->flags = action_flags;
        }
        ((S_80092018_0 *)actor)->unk_8C = handle_player_input;
        return;
    default:
        return;
    }
}
