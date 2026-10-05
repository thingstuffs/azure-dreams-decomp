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
extern s32 func_800A94A0(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void func_800BB044(void *);

extern u8 D_80170E9C[];
extern u8 D_80174EE0[];


typedef struct S_8017293C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8017293C_0;   /* arg0 in func_8017293C */

typedef struct S_8017293C_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017293C_1_pre;   /* the 0x14 bytes before active in func_8017293C, addressed as active[-1] */

typedef struct S_8017293C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017293C_2;   /* linked in func_8017293C */


typedef struct S_8017293C_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8017293C_5;   /* global in func_8017293C */

/* Runs the actor's selected item action and handles its wait and completion phases. */
void func_8017293C(void *action, EntityRec *motion, void *sprite, void *actor)
{
    s32 is_special;
    u8 *item_slot;
    void *target;
    u8 *scratch_pointer;

    is_special = 0;
    item_slot = (u8 *)(((S_8017293C_0 *)action)->unk_9B);
    switch ((u8)item_slot) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
            u32 kind_index;

            kind_index = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
            switch (kind_index) {
            case 7:
                is_special = 1;
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
                /* fall through */
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
                /* fall through */
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 item_kind;

            item_kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
            switch (item_kind) {
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }
        if (*item_slot != 0) {
            ((S_8017293C_0 *)action)->unk_98 &= 0xFF7F;
            {
                s16 use_special;

                use_special = is_special;
                if (use_special != 0) {
                    target = D_800814A8;
                    (*(void * *)((u8 *)actor + 0x60)) = target;
                    scratch_pointer = ((S_8017293C_1_pre *)target)[-1].unk_00;
                    (*(u8 *)((u8 *)actor + 0x72)) = ((S_8017293C_2 *)scratch_pointer)->unk_24;
                    (*(u8 *)((u8 *)actor + 0x73)) = ((S_8017293C_2 *)scratch_pointer)->unk_25;
                } else {
                    u8 item_id;

                    item_id = *item_slot;
                    if (D_8006DE24[item_id].kind == 2) {
                        target = (*(void * *)((u8 *)actor + 0x60));
                        if (target != 0) {
                            scratch_pointer = ((S_8017293C_1_pre *)target)[-1].unk_00;
                            (*(u8 *)((u8 *)actor + 0x72)) = ((S_8017293C_2 *)scratch_pointer)->unk_24;
                            (*(u8 *)((u8 *)actor + 0x73)) = ((S_8017293C_2 *)scratch_pointer)->unk_25;

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

            if (func_800A94A0(actor, item_slot, is_special,
                (u8 *)action + 0x98) == 0) {
                return;
            }
            func_800BB044(actor);
            ((S_8017293C_0 *)action)->unk_9B++;
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
        ((S_8017293C_0 *)action)->unk_8C = D_80170E9C;
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
        ((S_8017293C_0 *)action)->unk_9B++;

    case 2:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3 &&
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((S_8017293C_0 *)action)->unk_96 = 1;
            ((S_8017293C_0 *)action)->unk_98 |= 0x80;
        }
        {
            s16 wait_ticks;

            wait_ticks = ((S_8017293C_0 *)action)->unk_96 - 1;
            ((S_8017293C_0 *)action)->unk_96 = wait_ticks;
            if (wait_ticks <= 0) {
                ((S_8017293C_0 *)action)->unk_96 = 0;
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
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80174EE0) {
            u8 *direction_frames;
            s32 direction;

            direction_frames = D_80174EE0;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_frames;
            direction = ((gameWork.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(sprite, direction_frames[direction], 0);
        }
        {
            scratch_pointer = (u8 *)&dungeonStatus.unk_00;
            if (((S_8017293C_5 *)scratch_pointer)->unk_0C != 0) {
                return;
            }
            ((S_8017293C_5 *)scratch_pointer)->unk_0A--;
            ((S_8017293C_0 *)action)->unk_8C = D_80170E9C;
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
