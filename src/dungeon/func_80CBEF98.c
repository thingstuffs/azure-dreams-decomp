#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800BB044(void *);

extern u8 D_80170F20[];
extern u8 D_801762C0[];


typedef struct S_80172798_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172798_0;   /* arg0 in func_80172798 */

typedef struct S_80172798_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172798_1_pre;   /* the 0x14 bytes before active in func_80172798, addressed as active[-1] */

typedef struct S_80172798_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172798_2;   /* linked in func_80172798 */


typedef struct S_80172798_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172798_5;   /* global in func_80172798 */

/* Advances the selected item action and resets movement when it ends. */
void func_80172798(void *action, EntityRec *motion, void *sprite, void *actor)
{
    s32 special;
    u8 *selection;
    void *active;
    u8 *scratch_pointer;

    special = 0;
    selection = (u8 *)(((S_80172798_0 *)action)->unk_9B);
    switch ((u8)selection) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
            switch (((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF)) {
            case 7:
                special = 1;
                /* fallthrough */
            case 3:
                selection = (u8 *)actor + 0xE;
                break;
            case 6:
                special = 1;
                /* fallthrough */
            case 2:
                selection = (u8 *)actor + 0xB;
                break;
            case 5:
                special = 1;
                /* fallthrough */
            case 1:
                selection = (u8 *)actor + 8;
                break;
            default:
                selection = 0;
                break;
            }
        } else {
            switch ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) {
            case 3:
                selection = (u8 *)actor + 0xE;
                break;
            case 2:
                selection = (u8 *)actor + 0xB;
                break;
            case 1:
                selection = (u8 *)actor + 8;
                break;
            default:
                selection = 0;
                break;
            }
        }

        if (*selection != 0) {
            ((S_80172798_0 *)action)->unk_98 &= 0xFF7F;
            {
                s16 special_test;

                special_test = special;
                if (special_test != 0) {
                    active = D_800814A8;
                    (*(void * *)((u8 *)actor + 0x60)) = active;
                    scratch_pointer = ((S_80172798_1_pre *)active)[-1].unk_00;
                    (*(u8 *)((u8 *)actor + 0x72)) = ((S_80172798_2 *)scratch_pointer)->unk_24;
                    (*(u8 *)((u8 *)actor + 0x73)) = ((S_80172798_2 *)scratch_pointer)->unk_25;
                } else {
                    u8 item_id;

                    item_id = *selection;
                    if (D_8006DE24[item_id].kind == 2) {
                        active = (*(void * *)((u8 *)actor + 0x60));
                        if (active != 0) {
                            scratch_pointer = ((S_80172798_1_pre *)active)[-1].unk_00;
                            (*(u8 *)((u8 *)actor + 0x72)) = ((S_80172798_2 *)scratch_pointer)->unk_24;
                            (*(u8 *)((u8 *)actor + 0x73)) = ((S_80172798_2 *)scratch_pointer)->unk_25;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        dx = (s32)func_800A05A4(
                            actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                            (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                        (*(void * volatile *)((u8 *)actor + 0x60)) = (void *)dx;
                        dx = (*(s8 *)((u8 *)actor + 0x72));
                        dy = (*(s8 *)((u8 *)actor + 0x73));
                        if (dx < 0) {
                            dx = -dx;
                        }
                        if (dy < 0) {
                            dy = -dy;
                        }
                        (*(u8 *)((u8 *)actor + 0x72)) = dx;
                        (*(u8 *)((u8 *)actor + 0x73)) = dy;
                    }
                }
            }

            if (func_800A94A0(actor, selection, special,
                              (u8 *)action + 0x98) == 0) {
                return;
            }
            func_800BB044(actor);
            ((S_80172798_0 *)action)->unk_9B++;
            return;
        }
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
            func_800A4ACC(actor);
            (*(u8 *)((u8 *)actor + 0x6D))--;
            ((S_80172798_0 *)action)->unk_8C = D_80170F20;
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            return;

    case 1:
        if (func_8003F270()) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172798_0 *)action)->unk_9B++;

    case 2:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 7 &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((S_80172798_0 *)action)->unk_96 = 1;
            ((S_80172798_0 *)action)->unk_98 |= 0x80;
        }
        {
            s16 timer;

            timer = ((S_80172798_0 *)action)->unk_96 - 1;
            ((S_80172798_0 *)action)->unk_96 = timer;
            if (timer <= 0) {
                ((S_80172798_0 *)action)->unk_96 = 0;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_801762C0) {
            u8 *anim_table;
            s32 direction;

            anim_table = D_801762C0;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
            direction = ((gameWork.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(sprite, anim_table[direction], 0);
        }
        {
            scratch_pointer = (u8 *)&dungeonStatus.unk_00;
            if (((S_80172798_5 *)scratch_pointer)->unk_0C != 0) {
                return;
            }
            ((S_80172798_5 *)scratch_pointer)->unk_0A--;
            ((S_80172798_0 *)action)->unk_8C = D_80170F20;
            func_800A4ACC(actor);
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u8 *)((u8 *)actor + 0x6D))--;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            func_800A56E0(0xB4);
        }

        return;
    default:
        return;
    }
}
