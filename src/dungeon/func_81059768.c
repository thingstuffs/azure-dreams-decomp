#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"


extern void func_80042B68(void *, s32);
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
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171510(void *, void *, void *, void *);
extern void func_80171768(void *, void *, void *, void *);
extern s32 func_80171F24(void *, void *, void *, void *);
extern void func_80172110(void *, void *, void *, void *);
extern s32 func_80172228(void *, void *, void *, s32);
extern void func_80173900(void *, void *, void *, void *);
extern void func_80173AD4(void *, void *, void *, void *);

extern s32 D_80170F68;
extern u8 D_80173FB8[];
extern u8 D_80173FC0[];
extern u8 D_80173FF0[];
extern u8 D_80173FF8[];
extern u8 D_80174000[];


typedef struct S_80170F68_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80170F68_1;   /* arg3 in func_80170F68 */

typedef struct S_80170F68_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170F68_2;   /* arg2 in func_80170F68 */


/* Updates a dungeon actor's behavior, facing, and animation from its current state. */
void func_80170F68(void *actor_arg, void *context_arg, void *map_object_arg, void *actor_state_arg)
{
    u8 *anim_table;
    s32 tile_id;
    s32 distance;
    u32 initial_flags = dungeonStatus.flags;


    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xE;
        func_80171510(actor_arg, context_arg, map_object_arg, actor_state_arg);
        return;
    }


    if (((S_80170F68_1 *)actor_state_arg)->unk_25 == 0) {
        u8 *inactive_anims;

        func_800AA79C(actor_arg, context_arg, map_object_arg, actor_state_arg);
        if (((S_80170F68_2 *)map_object_arg)->unk_2C != D_80174000) {
            inactive_anims = D_80173FF8;
            (*(void * *)((u8 *)map_object_arg + (0x2C))) = inactive_anims;
            func_80047784(map_object_arg,
                inactive_anims[((gameWork.view.viewAngle + ((S_80170F68_1 *)actor_state_arg)->unk_2A + 0x100)
                    >> 9) & 7],
                0);
        }
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_AE = 0;
        func_80042B68(actor_state_arg, 0x1A);
        return;
    }

    if (((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x200) {
        if (((S_80170F68_2 *)map_object_arg)->unk_2C == D_80174000) {
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_8C = 0;
            ((S_80170F68_1 *)actor_state_arg)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor_arg, context_arg, map_object_arg, D_80173FF8)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x100) {
            func_800AA258(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 != 0xE) {
            u8 next_state = 0xE;

            anim_table = D_80173FB8;
            if (((S_80170F68_2 *)map_object_arg)->unk_2C != anim_table) {
                (*(void * *)((u8 *)map_object_arg + (0x2C))) = anim_table;
                func_80047784(map_object_arg,
                    anim_table[((gameWork.view.viewAngle + ((S_80170F68_1 *)actor_state_arg)->unk_2A + 0x100)
                        >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = next_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_98 &= 0xFFF3;
        if (((S_80170F68_1 *)actor_state_arg)->unk_64 != 0) {
            if (func_800AA6B4(actor_arg, context_arg, map_object_arg, D_80173FC0)) {
                return;
            }
        }

        if (((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x80000) {
            func_800AA888(actor_arg, context_arg, map_object_arg, actor_state_arg);
            func_80173900(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }

        if ((s16)func_800A1C58(actor_state_arg) != 0) {
            func_800AAB10(actor_arg, context_arg, map_object_arg, actor_state_arg);
        }
    }

    tile_id = func_8009FB34(((S_80170F68_2 *)map_object_arg)->unk_24.at00.v,
        ((S_80170F68_2 *)map_object_arg)->unk_24.at01.v);
    ((S_80170F68_2 *)map_object_arg)->unk_26 = tile_id;

    if (((S_80170F68_1 *)actor_state_arg)->unk_6D > 0) {
        if (((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x20) {
            func_800A9A0C(actor_state_arg);
            return;
        }
        if (((S_80170F68_2 *)map_object_arg)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_80171768(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }
        if (!(((S_80170F68_1 *)actor_state_arg)->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(actor_state_arg,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172228(actor_arg, context_arg, map_object_arg, 0) == 0) {
                return;
            }
            ((S_80170F68_1 *)actor_state_arg)->unk_46 |= 0x4000;
            if (!(((S_80170F68_1 *)actor_state_arg)->unk_46 & 0x8000)) {
                func_80171768(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
            }
        }

        switch (((S_80170F68_1 *)actor_state_arg)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_80171F24(actor_arg, context_arg, map_object_arg, actor_state_arg) == 0) {
                func_80172110(actor_arg, context_arg, map_object_arg, actor_state_arg);
                return;
            }
            return;
        case 9:
            func_80173AD4(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        case 5:
        case 6:
        case 7:
            {
                EntityRec *player;
                s32 direction;

                direction = func_800A0818(
                    ((S_80170F68_2 *)map_object_arg)->unk_24.at00.v, ((S_80170F68_2 *)map_object_arg)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &distance);
                player = D_800814A8;
                ((S_80170F68_1 *)actor_state_arg)->unk_2A = direction;
                if (player->unk_9A == 0x11) {
                    func_800AAF00(actor_arg, context_arg, map_object_arg, D_80173FF0, &D_80170F68);
                    return;
                }
            }
            /* fallthrough */
        case 12:
            func_800A9A0C(actor_state_arg);
            return;
        case 1:
        case 2:
        case 3:
            func_800AAF00(actor_arg, context_arg, map_object_arg, D_80173FF0, &D_80170F68);
            return;
        default:
            func_80171768(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }
    } else if (!(((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x2000)) {
        s32 record_index = (s8)tile_id;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x430)) {

                if ((s16)func_8009FD7C(((S_80170F68_2 *)map_object_arg)->unk_24.at00.v,
                        ((S_80170F68_2 *)map_object_arg)->unk_24.at01.v, D_80082E80.tileX,
                        D_80082E80.tileY) != 0) {
                    ((S_80170F68_1 *)actor_state_arg)->unk_2A = func_800A0818(
                        ((S_80170F68_2 *)map_object_arg)->unk_24.at00.v,
                            ((S_80170F68_2 *)map_object_arg)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80170F68_2 *)map_object_arg)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80173FB8;
    if (((S_80170F68_2 *)map_object_arg)->unk_2C == anim_table) {
        return;
    }
    (*(void * *)((u8 *)map_object_arg + (0x2C))) = anim_table;
    func_80047784(map_object_arg,
        ((((gameWork.view.viewAngle + ((S_80170F68_1 *)actor_state_arg)->unk_2A + 0x100) >> 9) & 7) + anim_table)[0],
        0);
}
