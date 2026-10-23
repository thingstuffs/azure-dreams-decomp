#include "modules/town_map_props.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_trail_views.h"

typedef struct S_800BE214_3 {
    s32 * unk_00;
} S_800BE214_3;   /* (s8 *)sp10 + (arg0->state * 4) in advance_actor_animation_pose */

typedef struct S_800BE214_4 {
    s32 * unk_00;
} S_800BE214_4;   /* (s8 *)sp10 + (arg0->animation_index * 4) in advance_actor_animation_pose */

typedef union {
    s16 state;
    u16 raw;
} StateWord;

struct Dst;
struct Elem;

typedef struct {
    void *entries[9];
} AnimTable;

extern void *const D_80089684[9];
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_800F9D80[];

typedef struct S_800BE214_0 {
    u8 pad_00[0x68];
    s16 state; /* 0x68 */
    u8 pad_6A[0x2];
    s16 pose_ticks; /* 0x6C */
    u8 pad_6E[0x32];
    u16 base_height; /* 0xA0 */
    u8 pad_A2[0x2];
    s32 animation_index; /* 0xA4 */
} S_800BE214_0;   /* arg0 in advance_actor_animation_pose */

   /* Advances the actor animation state and applies a timed pose offset. */
void advance_actor_animation_pose(S_800BE214_0 *actor, TrailHeightView *pose, SpriteFrameState *animation) {
    void *animations[9];
    s16 animation_index;
    s32 state;
    u16 elapsed_frames;

    *(AnimTable *)animations = *(AnimTable *)D_80089684;
    advance_sprite_animation_and_textures(animation);
    state = actor->state;
    switch (state) {
    case 0:
        if ((service_script_controller() != 0) && (check_transform_identifier_and_hook(actor) != 0)) {
            animation_index = rand() & 7;
            actor->state = animation_index;
            actor->animation_index = (u32)animation_index;
            select_record_entry_and_value((struct Dst *)animation, (struct Elem *)((S_800BE214_3 *)((s8 *)animations
                + (actor->state * 4)))->unk_00, 0);
            actor->state = (s16)((u16)actor->state + 0x20);
        }
        break;
    case 0x20:
        if (!(animation->flags & 0x6000))
            return;
        select_record_entry_and_value((struct Dst *)animation, (struct Elem *)animations[0], 0);
        actor->pose_ticks = 0;
        actor->animation_index = 0;
        pose->unk_0A = (u16)actor->base_height;
        actor->state = 0x60;
        break;
    case 0x23:
        if (!(animation->flags & 0x6000))
            return;
        actor->pose_ticks = 6;
        actor->animation_index = 8;
        select_record_entry_and_value((struct Dst *)animation, (struct Elem *)animations[8], 0);
        actor->state = 0x40;
        break;
    case 0x24:
        if (!(animation->flags & 0x6000))
            return;
        select_record_entry_and_value((struct Dst *)animation, (struct Elem *)&D_800F9D80, 0);
        {
            StateWord next_state = { 0x20 };
            actor->state = next_state.state;
        }
        break;
    case 0x25:
        if (!(animation->flags & 0x6000))
            return;
        select_record_entry_and_value((struct Dst *)animation, (struct Elem *)D_800F9D80, 0);
        actor->state = 0x20;
        break;
    case 0x21:
    case 0x22:
    case 0x26:
    case 0x27:
        if (!(animation->flags & 0x6000))
            return;
        actor->state = 0x60;
        break;
    case 0x40:
        pose->unk_0A = (u16)(actor->base_height + (rcos((actor->pose_ticks << 0xC) / 22) >> 8));
        elapsed_frames = (u16)actor->pose_ticks;
        actor->pose_ticks = (s16)(elapsed_frames + 1);
        if ((s16)elapsed_frames >= 0xDC) {
            actor->state = 0x20;
        }
        break;
    case 0x60:
        if ((service_script_controller() == 0) || (check_transform_identifier_and_hook(actor) == 0)) {
            actor->state = 0;
        }
        break;
    }

    if (animation->flags & 0x6000) {
        select_record_entry_and_value((struct Dst *)animation, (struct Elem *)((S_800BE214_4 *)((s8 *)animations
            + (actor->animation_index * 4)))->unk_00, 0);
    }

    return;
}
