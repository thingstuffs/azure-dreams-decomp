#include "shared/dungeon_actor_callbacks.h"
#include "shared/entity.h"
#include "dungeon/player.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80092018_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(void *, void *, void *, void *);
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x84];
    void * unk_124;
} S_80092018_0;   /* arg0 in update_player_push */

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

typedef struct S_80092018_5 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_80092018_5;

   /* ((S_80092018_0 *)arg0)->unk_124 in update_player_push */

struct D83460_VIEW { s16 pad[3]; s16 divisor[1]; };

void set_sprite_animation_frame();
s32 resolve_player_input_facing(s16 direction_offset, u16 *flags, u16 *angle);
s32 has_action_input_without_modifier(); /* Unprototyped: zero or one argument; retail replaces all incoming argument registers. */
void process_unflagged_linked_entries(s32 firstEntryBase);
void process_unflagged_linked_entries_alt(s32 firstNodeBase);
void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y);
void spawn_opposite_offset_effect(void *source_data, u32 direction_bits);
extern u8 player_push_frames[];
extern u8 D_800DD020[];
extern u8 player_push_loop_frames[];

/* Updates actor movement and animation through the action states. */
void update_player_push(void *actor, void *motion, SpriteFrameState *sprite, void *model) {
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
        if (sprite->flags & 0xE000) {
            if (*(u8 * *)&sprite->frameTable != player_push_loop_frames) {
                sprite->frameTable = player_push_loop_frames;
                set_sprite_animation_frame(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)model)->facing + 0x100)
                    >> 9) & 7) + player_push_loop_frames), 0, 1);
                return;
            }
        } else {
            heading_or_coord = resolve_player_input_facing(((S_80092018_0 *)actor)->unk_9E, actor + 0xA2, model + 0x2A) << 0x10;
            if ((heading_or_coord >> 0x10) == 0xFFF) {
                return;
            }
            if ((((u16) ((ActorRecord *)model)->facing >> 9) & 7) == ((heading_or_coord >> 0x19) & 7)) {
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
            + (((u16) ((ActorRecord *)model)->facing >> 8) & 0xE))) * 8);
        ((S_80092018_3 *)motion)->unk_10.at02.v = (s16) (*((s16 *)(((u8 *)dir_step_y)
            + (((u16) ((ActorRecord *)model)->facing >> 8) & 0xE))) * 8);
        start_frames_left = ((S_80092018_0 *)actor)->unk_96.s - 1;
        ((S_80092018_0 *)actor)->unk_96.s = start_frames_left;
        if ((start_frames_left << 0x10) > 0) {
            return;
        }
        sprite->frameTable = player_push_frames;
        set_sprite_animation_frame(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)model)->facing + 0x100) >> 9) & 7)
            + player_push_frames), 0, 1);
        attachment = ((S_80092018_0 *)actor)->unk_124;
        ((ActorRecord *)attachment)->flags1C = (s32) (((ActorRecord *)attachment)->flags1C | 0x100);
        ((ActorRecord *)(((S_80092018_0 *)actor)->unk_124))->movement_facing = (u16) ((ActorRecord *)model)->facing;
        ((ActorRecord *)(((S_80092018_0 *)actor)->unk_124))->target = model;
        ((S_80092018_0 *)actor)->unk_9B = (u8) (((S_80092018_0 *)actor)->unk_9B + 1);
        return;
    case 17:
        if (sprite->flags & 0xE000) {
            sprite->frameTable = D_800DD020;
            set_sprite_animation_frame(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)model)->facing + 0x100)
                >> 9) & 7) + D_800DD020), 0, 1);
            ((S_80092018_0 *)actor)->unk_9B = (u8) (((S_80092018_0 *)actor)->unk_9B + 1);
        }
    case 18:
        move_state = &g_dungeon_status.turn_scale;
        if (((S_80092018_5 *)move_state)->unk_04 != 0) {
            heading_or_coord = ((S_80092018_3 *)motion)->unk_02;
            {
                s32 delta;
                s32 direction_offset;
                delta = sprite->tile_x << 6;
                direction_offset = *((s16 *)(((u8 *)dir_step_x) + (((u16) ((ActorRecord *)model)->facing
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
                delta = sprite->tile_y << 6;
                direction_offset = *((s16 *)(((u8 *)dir_step_y) + (((u16) ((ActorRecord *)model)->facing
                    >> 8) & 0xE))) * 0x10;
                direction_offset += 0x20;
                delta += direction_offset;
                delta -= heading_or_coord;
                ((S_80092018_3 *)motion)->unk_10.at00.v = (s32) ((delta
                    << 0x10) / ((struct D83460_VIEW *) move_state)->divisor[-1]);
            }
        }
        if (!((u16) ((S_80092018_5 *)move_state)->unk_04 & 3)) {
            spawn_opposite_offset_effect(motion, ((ActorRecord *)model)->facing);
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
        sprite->frameTable = player_push_loop_frames;
        set_sprite_animation_frame(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)model)->facing + 0x100) >> 9) & 7)
            + player_push_loop_frames), 0, 1);
        ((S_80092018_0 *)actor)->unk_96.s = 2U;
        ((S_80092018_0 *)actor)->unk_9B = 0x13U;
        return;
    case 19:
        settle_frames = (s16) ((S_80092018_0 *)actor)->unk_96.s;
        if (settle_frames != 0) {
            {
                s32 delta;
                s32 origin;
                delta = sprite->tile_x << 6;
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
                delta = sprite->tile_y << 6;
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
        anim_flags = sprite->flags;
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
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        process_unflagged_linked_entries_alt(((ActorRecord *)model)->next_actor_header);
        process_unflagged_linked_entries(((ActorRecord *)model)->next_actor_header);
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
