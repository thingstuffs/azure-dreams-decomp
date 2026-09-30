#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern int abs(int);

typedef struct S_80172AF8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172AF8_0;   /* arg0 in func_80172AF8 */

typedef struct S_80172AF8_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172AF8_2_pre;   /* the 0x14 bytes before obj in func_80172AF8, addressed as obj[-1] */

typedef struct S_80172AF8_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172AF8_3;   /* rec in func_80172AF8 */

typedef struct S_80172AF8_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172AF8_4;   /* arg2 in func_80172AF8 */


typedef struct S_80172AF8_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172AF8_7;   /* block in func_80172AF8 */


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800DA840(void *, s16);

extern u8 D_80170E70[];
extern u8 D_80175A54[];

/* Advances actor motion and handles its wait and completion states. */
void func_80172AF8(void *action, void *transform, void *sprite, EntityRec *actor)
{
    u16 saved_pos[4];
    u8 *motion;
    s16 special_motion;
    void *target;
    s32 wait_ticks;
    u8 *action_state;

    special_motion = 0;
    switch (((S_80172AF8_0 *)action)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            static void * const motion_labels[] = { && special_third, && special_second, && special_first,
                && no_motion };
            extern void *const D_80170838[];
            u32 motion_index = (u32)((actor->unk_46 & 0x3FFF) - 1);

            if (motion_index >= 7) {
                goto no_motion;
            }
            (void)motion_labels;
            goto *D_80170838[motion_index];
special_third:
            special_motion = 1;
            goto third_motion;
special_second:
            special_motion = 1;
            goto second_motion;
special_first:
            special_motion = 1;
            goto first_motion;
        }

        switch (actor->unk_46 & 0x3FFF) {
        case 3:
third_motion:
            motion = (u8 *)actor + 0xE;
            break;
        case 2:
second_motion:
            motion = (u8 *)actor + 0xB;
            break;
        case 1:
first_motion:
            motion = (u8 *)actor + 8;
            break;
        default:
no_motion:
            motion = (u8 *)0;
            break;
        }

        if (*motion != 0) {
            ((S_80172AF8_0 *)action)->unk_98 &= 0xFF7F;
            {
                s16 use_special = special_motion;

                if (use_special != 0) {
                    target = D_800814A8;
                    actor->target = target;
                    goto have_target;
                }
            }
            if (D_8006DE24[*motion].kind == 2) {
                target = actor->target;
                if (target == 0) {
                    goto step_motion;
                }
have_target:
                action_state = ((S_80172AF8_2_pre *)target)[-1].unk_00;
                actor->unk_72 = ((S_80172AF8_3 *)action_state)->unk_24;
                actor->unk_73 = ((S_80172AF8_3 *)action_state)->unk_25;
                goto step_motion;
            }
            actor->target =
                func_800A05A4(actor, ((S_80172AF8_4 *)sprite)->unk_24, ((S_80172AF8_4 *)sprite)->unk_25,
                              actor->facing, 0x10);
            actor->unk_72 = abs(actor->unk_72);
            actor->unk_73 = abs(actor->unk_73);
step_motion:
            saved_pos[0] = ((u16)((EntityRec *)transform)->x.w.i);
            saved_pos[1] = ((u16)((EntityRec *)transform)->y.w.i);
            saved_pos[2] = ((u16)((EntityRec *)transform)->z.w.i);
            transform = (void *)func_800A94A0(actor, motion, special_motion, (u8 *)action + 0x98);
            if (transform == 0) {
                return;
            }
            ((S_80172AF8_4 *)sprite)->unk_14 &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DA840(saved_pos, (*motion - 1) % 3);
            ((S_80172AF8_0 *)action)->unk_9B = ((S_80172AF8_0 *)action)->unk_9B + 1;
            return;
        }

        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        func_800A2B04(transform, ((S_80172AF8_4 *)sprite)->unk_24, ((S_80172AF8_4 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        func_800A4ACC(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        ((S_80172AF8_0 *)action)->unk_8C = D_80170E70;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((S_80172AF8_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_80172AF8_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172AF8_0 *)action)->unk_9B = ((S_80172AF8_0 *)action)->unk_9B + 1;
                                /* fallthrough */
    case 2:
        if ((((S_80172AF8_4 *)sprite)->unk_04 == 4 && (((S_80172AF8_4 *)sprite)->unk_14 & 0x1000)) ||
            (((S_80172AF8_4 *)sprite)->unk_14 & 0xE000)) {
            ((S_80172AF8_4 *)sprite)->unk_14 |= 0x800;
            ((S_80172AF8_0 *)action)->unk_96 = 0x20;
            ((S_80172AF8_0 *)action)->unk_98 |= 0x80;
        }
        wait_ticks = ((S_80172AF8_0 *)action)->unk_96 - 1;
        ((S_80172AF8_0 *)action)->unk_96 = wait_ticks;
        if ((s16)wait_ticks <= 0) {
            ((S_80172AF8_0 *)action)->unk_96 = 0;
            ((S_80172AF8_4 *)sprite)->unk_14 &= 0xF7FF;
        }
        if ((((S_80172AF8_4 *)sprite)->unk_14 & 0xE000) == 0) {
            return;
        }
        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        func_800A2B04(transform, ((S_80172AF8_4 *)sprite)->unk_24, ((S_80172AF8_4 *)sprite)->unk_25);
        {
            u8 *idle_frames = D_80175A54;

            if (((S_80172AF8_4 *)sprite)->unk_2C != idle_frames) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = idle_frames;
                func_80047784(sprite,
                    idle_frames[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_state = (u8 *)&dungeonStatus.unk_00;
        if (((S_80172AF8_7 *)action_state)->unk_0C != 0) {
            return;
        }
        ((S_80172AF8_7 *)action_state)->unk_0A = ((S_80172AF8_7 *)action_state)->unk_0A - 1;
        ((S_80172AF8_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172AF8_0 *)action)->unk_8C = D_80170E70;
        func_800A4ACC(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}
