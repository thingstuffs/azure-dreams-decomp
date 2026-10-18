#include "modules/town_map_props.h"
#include "m2c_compat.h"
#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_800BE214_3 {
    s32 * unk_00;
} S_800BE214_3;   /* (s8 *)sp10 + (arg0->unk_68 * 4) in advance_actor_animation_pose */

typedef struct S_800BE214_4 {
    s32 * unk_00;
} S_800BE214_4;   /* (s8 *)sp10 + (arg0->unk_A4 * 4) in advance_actor_animation_pose */


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
extern M2C_UNK D_800F9D80[3];

typedef struct S_800BE214_0 {
    u8 pad_00[0x68];
    s16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    u8 pad_6E[0x32];
    u16 unk_A0;
    u8 pad_A2[0x2];
    s32 unk_A4;
} S_800BE214_0;   /* arg0 in advance_actor_animation_pose */


typedef struct S_800BE214_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BE214_2;   /* arg1 in advance_actor_animation_pose */

/* Advances the actor animation state and applies a timed pose offset. */
void advance_actor_animation_pose(S_800BE214_0 *actor, S_800BE214_2 *pose, Rec_D_80082E80 *animation) {
    void *animations[9];
    s16 animation_index;
    s32 state;
    u16 elapsed_frames;

    *(AnimTable *)animations = *(AnimTable *)D_80089684;
    func_800478B8(animation);
    state = actor->unk_68;
    switch (state) {
    case 0:
        if ((func_800352FC() != 0) && (check_transform_identifier_and_hook(actor) != 0)) {
            animation_index = rand() & 7;
            actor->unk_68 = animation_index;
            actor->unk_A4 = (u32)animation_index;
            func_8003DB94((struct Dst *)animation, (struct Elem *)((S_800BE214_3 *)((s8 *)animations
                + (actor->unk_68 * 4)))->unk_00, 0);
            actor->unk_68 = (s16)((u16)actor->unk_68 + 0x20);
        }
        break;
    case 0x20:
        if (!(animation->unk_14.at00_u16.v & 0x6000))
            return;
        func_8003DB94((struct Dst *)animation, (struct Elem *)animations[0], 0);
        actor->unk_6C = 0;
        actor->unk_A4 = 0;
        pose->unk_0A = (u16)actor->unk_A0;
        actor->unk_68 = 0x60;
        break;
    case 0x23:
        if (!(animation->unk_14.at00_u16.v & 0x6000))
            return;
        actor->unk_6C = 6;
        actor->unk_A4 = 8;
        func_8003DB94((struct Dst *)animation, (struct Elem *)animations[8], 0);
        actor->unk_68 = 0x40;
        break;
    case 0x24:
        if (!(animation->unk_14.at00_u16.v & 0x6000))
            return;
        func_8003DB94((struct Dst *)animation, (struct Elem *)&D_800F9D80, 0);
        {
            StateWord next_state = { 0x20 };
            actor->unk_68 = next_state.state;
        }
        break;
    case 0x25:
        if (!(animation->unk_14.at00_u16.v & 0x6000))
            return;
        func_8003DB94((struct Dst *)animation, (struct Elem *)D_800F9D80, 0);
        actor->unk_68 = 0x20;
        break;
    case 0x21:
    case 0x22:
    case 0x26:
    case 0x27:
        if (!(animation->unk_14.at00_u16.v & 0x6000))
            return;
        actor->unk_68 = 0x60;
        break;
    case 0x40:
        pose->unk_0A = (u16)(actor->unk_A0 + (func_80064584((actor->unk_6C << 0xC) / 22) >> 8));
        elapsed_frames = (u16)actor->unk_6C;
        actor->unk_6C = (s16)(elapsed_frames + 1);
        if ((s16)elapsed_frames >= 0xDC) {
            actor->unk_68 = 0x20;
        }
        break;
    case 0x60:
        if ((func_800352FC() == 0) || (check_transform_identifier_and_hook(actor) == 0)) {
            actor->unk_68 = 0;
        }
        break;
    }

    if (animation->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94((struct Dst *)animation, (struct Elem *)((S_800BE214_4 *)((s8 *)animations
            + (actor->unk_A4 * 4)))->unk_00, 0);
    }

    return;
}
