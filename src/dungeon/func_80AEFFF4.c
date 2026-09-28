#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"



extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171D7C(void *, void *, void *, void *);
extern void func_80171FE8(void *, void *, void *, void *);
extern s32 func_801727B8(void *, void *, void *, void *);
extern void func_8017297C(void *, void *, void *, void *);
extern s32 func_80172A94(void *, void *, void *, s32);
extern void func_80174258(void *, void *, void *, void *);
extern void func_80174798(void *, void *, void *, void *);
extern void func_801751C0(void *, void *, void *, void *);

extern void *D_80170808[];
extern u8 D_801717F4;
extern u8 D_80175988[];
extern u8 D_80175998[];
extern u8 D_801759D0[];
extern u8 D_801759E0[];
extern u8 D_801759E8[];




typedef struct S_801717F4_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801717F4_2;   /* arg2 in func_801717F4 */


typedef struct S_801717F4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801717F4_4;   /* origin in func_801717F4 */

typedef struct S_801717F4_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801717F4_5;   /* player in func_801717F4 */

/* Updates actor animation and dispatches dungeon actions from entity state. */
void func_801717F4(void *actor_arg, void *context_arg, void *sprite_arg, void *entity_arg)
{
    static void *const action_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    s32 direction_aux;
    s32 tile_record;
    u16 action_state;
    u32 initial_flags = dungeonStatus.flags;


    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xE;
        func_80171D7C(actor_arg, context_arg, sprite_arg, entity_arg);
        do {
            return;
        } while (0);
    }


    if (((EntityRec *)entity_arg)->tileY == 0) {
        u8 *animations;

        func_800AA79C(actor_arg, context_arg, sprite_arg, entity_arg);
        if (((S_801717F4_2 *)sprite_arg)->unk_2C == D_801759E8) {
            return;
        }
        animations = D_801759E0;
        (*(void * *)((u8 *)sprite_arg + (0x2C))) = animations;
        func_80047784(sprite_arg,
            animations[((gameWork.viewAngle + ((EntityRec *)entity_arg)->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)((EntityRec *)entity_arg)->flags1C) & 0x200) {
        if (((S_801717F4_2 *)sprite_arg)->unk_2C == D_801759E8) {
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_8C = 0;
            ((EntityRec *)entity_arg)->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor_arg, context_arg, sprite_arg, D_801759E0) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)((EntityRec *)entity_arg)->flags1C) & 0x100) {
            func_800AA258(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8;
            u32 next_state;

            next_state = 0xE;
            if (current_state != next_state) {
                u8 *animations = D_80175988;

                if (((S_801717F4_2 *)sprite_arg)->unk_2C != animations) {
                    (*(void * *)((u8 *)sprite_arg + (0x2C))) = animations;
                    func_80047784(sprite_arg,
                        animations[((gameWork.viewAngle + ((EntityRec *)entity_arg)->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_A0.at00_s16.v = 0x14;
                ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = next_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_98 &= 0xFFF3;

        if (((EntityRec *)entity_arg)->unk_64 != 0) {
            if (func_800AA6B4(actor_arg, context_arg, sprite_arg, D_80175998) != 0) {
                return;
            }
        }

        if (((u32)((EntityRec *)entity_arg)->flags1C) & 0x80000) {
            func_800AA888(actor_arg, context_arg, sprite_arg, entity_arg);
            func_80174258(actor_arg, context_arg, sprite_arg, entity_arg);
            (*(void * *)((u8 *)sprite_arg + (0x2C))) = D_80175988;
            func_80047784(sprite_arg,
                D_80175988[((gameWork.viewAngle + ((EntityRec *)entity_arg)->facing + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((s16)func_800A1C58(entity_arg) != 0) {
            if ((s16)func_800AAB10(actor_arg, context_arg, sprite_arg, entity_arg) != 0) {
                func_801751C0(actor_arg, context_arg, sprite_arg, entity_arg);
            }
        }
    }

    tile_record = func_8009FB34(((S_801717F4_2 *)sprite_arg)->unk_24.at00.v, ((S_801717F4_2 *)sprite_arg)->unk_24.at01.v);
    ((S_801717F4_2 *)sprite_arg)->unk_26 = tile_record;

    if (((EntityRec *)entity_arg)->unk_6D > 0) {
        if (((u32)((EntityRec *)entity_arg)->flags1C) & 0x20) {
            goto special_cleanup;
        }
        if (((S_801717F4_2 *)sprite_arg)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            goto ordinary_cleanup;
        }
        if (!(((EntityRec *)entity_arg)->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(entity_arg,
                        (u8 *)((EntityRec *)D_800814A8)->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172A94(actor_arg, context_arg, sprite_arg, 0) == 0) {
                return;
            }
            action_state = ((EntityRec *)entity_arg)->unk_46 | 0x4000;
            ((EntityRec *)entity_arg)->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

        action_state = ((EntityRec *)entity_arg)->unk_46 & 0x3FFF;
        if ((u32)(action_state - 1) >= 12) {
            goto ordinary_cleanup;
        }
        (void)action_labels;
        goto *D_80170808[(u32)(action_state - 1)];

jt_c8:
jt_c9:
        if ((s16)func_801727B8(actor_arg, context_arg, sprite_arg, entity_arg) != 0) {
            return;
        }
        func_8017297C(actor_arg, context_arg, sprite_arg, entity_arg);
        return;

jt_c10:
        func_80174798(actor_arg, context_arg, sprite_arg, entity_arg);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            void *player;
            s16 direction;

            direction = func_800A0818(
                ((S_801717F4_2 *)sprite_arg)->unk_24.at00.v, ((S_801717F4_2 *)sprite_arg)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &direction_aux);
            player = D_800814A8;
            ((EntityRec *)entity_arg)->facing = direction;
            if (((S_801717F4_5 *)player)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
            goto special_cleanup;
        }

jt_c12:
special_cleanup:
        func_800A9A0C(entity_arg);
        return;

jt_c1:
jt_c2:
jt_c3:
aaf_cleanup:
        func_800AAF00(actor_arg, context_arg, sprite_arg, D_801759D0, &D_801717F4);
        return;

jt_c4:
jt_c11:
ordinary_cleanup:
        func_80171FE8(actor_arg, context_arg, sprite_arg, entity_arg);
        return;
    }

    if (!(((u32)((EntityRec *)entity_arg)->flags1C) & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) ||
            !(D_800E2970[record_index].flags & 2)) {
            if (!(((u32)((EntityRec *)entity_arg)->flags1C) & 0x430)) {

                if ((s16)func_8009FD7C(
                        ((S_801717F4_2 *)sprite_arg)->unk_24.at00.v, ((S_801717F4_2 *)sprite_arg)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) != 0) {
                    ((EntityRec *)entity_arg)->facing = func_800A0818(
                        ((S_801717F4_2 *)sprite_arg)->unk_24.at00.v, ((S_801717F4_2 *)sprite_arg)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_aux);
                }
            }
        }
    }
}
