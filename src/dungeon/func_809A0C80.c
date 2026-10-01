#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


extern void func_80047784();
extern u8 D_801710EC[];
extern u8 D_80175EB8[];
extern u8 D_80175EC8[];
extern u8 D_80175ED0[];

typedef struct S_80172480_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x14];
    u16 unk_B0;
    s16 unk_B2;
} S_80172480_0;   /* arg0 in func_80172480 */

typedef struct S_80172480_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
} S_80172480_1;   /* arg3 in func_80172480 */

typedef struct S_80172480_2 {
    u8 pad_00[0x8];
    u16 unk_08;
    u8 pad_0A[0xBE];
    u16 unk_C8;
} S_80172480_2;   /* base_83160 in func_80172480 */


typedef struct S_80172480_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80172480_4;   /* D_800E3D7C[0] in func_80172480 */

/* Advances an actor's turn-and-animation sequence and restores its saved heading. */
void func_80172480(S_80172480_0 *actor, s32 unused, Rec_D_80082E80 *animation, S_80172480_1 *transform_in) {
    S_80172480_1 *transform = transform_in;
    s32 heading;
    u8 phase;
    GameWork *scene_state = &gameWork;

    phase = actor->unk_9B;
    switch (phase) {
    case 0:
        heading = transform->unk_2A & 0xFFF;
        transform->unk_2A = heading;
        if (((0x400 - ((((u16)scene_state->view.viewAngle) + 0x100) & 0xE00)) & 0xE00) != heading) {
            transform->unk_2A = heading + 0x200;
            return;
        }
        goto advance;
    case 1:
        if (actor->unk_92 == 0) {
            {
                u8 *animation_table = D_80175EC8;
                animation->unk_2C.as_pm = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (gameWork.view.viewAngle
                        + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    func_80047784(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->unk_9B + 1;
            actor->unk_9B = phase;
            return;
        }
        if ((animation->unk_14.at00_u16.v & 0x8000) == 0) {
            return;
        }
        {
            u8 *animation_table = D_80175EC8;
            animation->unk_2C.as_pm = animation_table;
            {
                unsigned long animation_entry = (unsigned long)(((s32) (gameWork.view.viewAngle
                    + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                animation_entry += (unsigned long)animation_table;
                func_80047784(animation, *(u8 *)animation_entry, 0);
            }
        }
        phase = actor->unk_9B + 1;
        actor->unk_9B = phase;
        return;
    case 2:
        if (animation->unk_14.at00_u16.v & 0xE000) {
            {
                u8 *animation_table;
                animation_table = (u8 *)D_80175ED0;
                animation->unk_2C.as_pm = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (gameWork.view.viewAngle
                        + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    func_80047784(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->unk_9B + 1;
            actor->unk_9B = phase;
            return;
        }
        return;
    case 3:
    {
        u16 scene_status = ((u16)scene_state->buttons);
        if (scene_status != 0) {
            {
                u8 *animation_table = D_80175EC8;
                animation->unk_2C.as_pm = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (gameWork.view.viewAngle
                        + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    func_80047784(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->unk_9B + 1;
            actor->unk_9B = phase;
            return;
        }
        if (((S_80172480_4 *)(((u8 *)D_800E3D7C)))->unk_9A != 0x17) {
            {
                u8 *animation_table = D_80175EC8;
                animation->unk_2C.as_pm = animation_table;
                {
                    unsigned long animation_entry = (unsigned long)(((s32) (gameWork.view.viewAngle
                        + (s16) transform->unk_2A + 0x100) >> 9) & 7);
                    animation_entry += (unsigned long)animation_table;
                    func_80047784(animation, *(u8 *)animation_entry, 0);
                }
            }
            phase = actor->unk_9B + 1;
            actor->unk_9B = phase;
            return;
        }
        return;
    }
advance:
        phase = actor->unk_9B + 1;
        actor->unk_9B = phase;
        return;
    case 4:
        if (animation->unk_14.at00_u16.v & 0xE000) {
            transform->unk_1C = (s32) (transform->unk_1C | 0x40000);
            {
                u8 *animation_table = D_80175EB8;
                animation->unk_2C.as_pm = animation_table;
                func_80047784(animation, animation_table[((s32) (gameWork.view.viewAngle + (s16) transform->unk_2A
                    + 0x100) >> 9) & 7], 0);
            }
            actor->unk_8C = D_801710EC;
            transform->unk_2A = (u16) actor->unk_B0;
            actor->unk_B2 = 0;
            dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
        }
        return;
    default:
        return;
    }
}
