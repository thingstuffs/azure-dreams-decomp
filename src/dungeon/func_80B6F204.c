#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern int abs(int);

typedef struct S_80172A04_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172A04_0;   /* arg0 in func_80172A04 */

typedef struct S_80172A04_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A04_2_pre;   /* the 0x14 bytes before obj in func_80172A04, addressed as obj[-1] */

typedef struct S_80172A04_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A04_3;   /* rec in func_80172A04 */

typedef struct S_80172A04_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172A04_4;   /* arg2 in func_80172A04 */


typedef struct S_80172A04_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172A04_7;   /* block in func_80172A04 */


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800DA840(void *, s16);

extern u8 D_80170E5C[];
extern u8 D_80173D0C[];

/* Advances an actor motion through setup, playback, and completion. */
void func_80172A04(void *state, void *position, void *sprite, EntityRec *actor)
{
    u16 effect_pos[4];
    u8 *motion;
    s16 special_motion;
    void *target;
    s32 ticks_left;
    u8 *action_state;

    special_motion = 0;
    switch (((S_80172A04_0 *)state)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            static void * const dispatch_labels[] = { && special_third, && special_second, && special_first,
                && no_motion };
            extern void *const D_80170838[];
            u32 motion_index = (u32)((actor->unk_46 & 0x3FFF) - 1);

            if (motion_index >= 7) {
                goto no_motion;
            }
            (void)dispatch_labels;
            goto *D_80170838[motion_index];
special_third:
            special_motion = 1;
            goto select_third;
special_second:
            special_motion = 1;
            goto select_second;
special_first:
            special_motion = 1;
            goto select_first;
        }

        switch (actor->unk_46 & 0x3FFF) {
        case 3:
select_third:
            motion = (u8 *)actor + 0xE;
            break;
        case 2:
select_second:
            motion = (u8 *)actor + 0xB;
            break;
        case 1:
select_first:
            motion = (u8 *)actor + 8;
            break;
        default:
no_motion:
            motion = (u8 *)0;
            break;
        }

        if (*motion != 0) {
            ((S_80172A04_0 *)state)->unk_98 &= 0xFF7F;
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
                    goto run_motion;
                }
have_target:
                action_state = ((S_80172A04_2_pre *)target)[-1].unk_00;
                actor->unk_72 = ((S_80172A04_3 *)action_state)->unk_24;
                actor->unk_73 = ((S_80172A04_3 *)action_state)->unk_25;
                goto run_motion;
            }
            actor->target =
                func_800A05A4(actor, ((S_80172A04_4 *)sprite)->unk_24, ((S_80172A04_4 *)sprite)->unk_25,
                              actor->facing, 0x10);
            actor->unk_72 = abs(actor->unk_72);
            actor->unk_73 = abs(actor->unk_73);
run_motion:
            effect_pos[0] = ((u16)((EntityRec *)position)->x.w.i);
            effect_pos[1] = ((u16)((EntityRec *)position)->y.w.i);
            effect_pos[2] = ((u16)((EntityRec *)position)->z.w.i);
            position = (void *)func_800A94A0(actor, motion, special_motion, (u8 *)state + 0x98);
            if (position == 0) {
                return;
            }
            ((S_80172A04_4 *)sprite)->unk_14 &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DA840(effect_pos, (*motion - 1) % 3);
            ((S_80172A04_0 *)state)->unk_9B = ((S_80172A04_0 *)state)->unk_9B + 1;
            return;
        }

        ((EntityRec *)position)->flags14 = 0;
        ((EntityRec *)position)->unk_10 = 0;
        ((EntityRec *)position)->unk_0C = 0;
        func_800A2B04(position, ((S_80172A04_4 *)sprite)->unk_24, ((S_80172A04_4 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1;
        func_800A4ACC(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        ((S_80172A04_0 *)state)->unk_8C = D_80170E5C;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((S_80172A04_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_80172A04_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172A04_0 *)state)->unk_9B = ((S_80172A04_0 *)state)->unk_9B + 1;
                                /* fallthrough */
    case 2:
        if ((((S_80172A04_4 *)sprite)->unk_04 == 4 && (((S_80172A04_4 *)sprite)->unk_14 & 0x1000)) ||
            (((S_80172A04_4 *)sprite)->unk_14 & 0xE000)) {
            ((S_80172A04_4 *)sprite)->unk_14 |= 0x800;
            ((S_80172A04_0 *)state)->unk_96 = 0x6;
            ((S_80172A04_0 *)state)->unk_98 |= 0x80;
        }
        ticks_left = ((S_80172A04_0 *)state)->unk_96 - 1;
        ((S_80172A04_0 *)state)->unk_96 = ticks_left;
        if ((s16)ticks_left <= 0) {
            ((S_80172A04_0 *)state)->unk_96 = 0;
            ((S_80172A04_4 *)sprite)->unk_14 &= 0xF7FF;
        }
        if ((((S_80172A04_4 *)sprite)->unk_14 & 0xE000) == 0) {
            return;
        }
        ((EntityRec *)position)->flags14 = 0;
        ((EntityRec *)position)->unk_10 = 0;
        ((EntityRec *)position)->unk_0C = 0;
        func_800A2B04(position, ((S_80172A04_4 *)sprite)->unk_24, ((S_80172A04_4 *)sprite)->unk_25);
        {
            u8 *direction_table = D_80173D0C;

            if (((S_80172A04_4 *)sprite)->unk_2C != direction_table) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
                func_80047784(sprite,
                    direction_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_state = (u8 *)&dungeonStatus.unk_00;
        if (((S_80172A04_7 *)action_state)->unk_0C != 0) {
            return;
        }
        ((S_80172A04_7 *)action_state)->unk_0A = ((S_80172A04_7 *)action_state)->unk_0A - 1;
        ((S_80172A04_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172A04_0 *)state)->unk_8C = D_80170E5C;
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
