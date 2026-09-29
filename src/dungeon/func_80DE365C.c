#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80170E5C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80170E5C_0;   /* arg0 in func_80170E5C */

typedef struct S_80170E5C_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80170E5C_1;   /* arg3 in func_80170E5C */

typedef struct S_80170E5C_2 {
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
} S_80170E5C_2;   /* arg2 in func_80170E5C */


extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern s32 func_800A6D30(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171420(void *, void *, void *, void *);
extern void func_80171B68(void *, void *, void *, void *);
extern s32 func_80171E10(void *, void *, void *, void *);
extern void func_80171FD4(void *, void *, void *, void *);
extern s32 func_801720EC(void *, void *, void *, void *);
extern void func_8017236C(void *, void *, void *, void *);
extern void func_801737DC(void *, void *, void *, void *);
extern s32 func_80173E48(void *, void *, void *, s32);

extern u8 D_80174520[];
extern u8 D_80174530[];
extern u8 D_80174538[];
extern u8 D_80174548[];
extern u8 D_80174560[];

/* Update actor actions, facing, and animation according to dungeon state. */
void func_80170E5C(void *actor_in, void *context_in, void *sprite_in, void *status_in)
{
    void *status;
    u8 *anim_table;
    s32 tile_record;
    s32 direction_aux;
    u32 initial_flags = dungeonStatus.flags;

    status = status_in;

    if (initial_flags & 0x1000) {
        ((S_80170E5C_0 *)actor_in)->unk_9A = 0xE;
        func_80171B68(actor_in, context_in, sprite_in, status);
        return;
    }


    if (((S_80170E5C_1 *)status)->unk_25 == 0) {
        func_800AA79C(actor_in, context_in, sprite_in, status);
        if (((S_80170E5C_2 *)sprite_in)->unk_2C == D_80174538) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80174530;
        func_80047784(sprite_in,
            D_80174530[((gameWork.view.viewAngle + ((S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80170E5C_1 *)status)->unk_1C & 0x200) {
        if (((S_80170E5C_2 *)sprite_in)->unk_2C == D_80174538) {
            ((S_80170E5C_0 *)actor_in)->unk_9A = 0xD;
            ((S_80170E5C_0 *)actor_in)->unk_9B = 1;
            ((S_80170E5C_0 *)actor_in)->unk_8C = 0;
            ((S_80170E5C_1 *)status)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor_in, context_in, sprite_in, D_80174530)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((S_80170E5C_1 *)status)->unk_1C & 0x100) {
            func_800AA258(actor_in, context_in, sprite_in, status);
            return;
        }

        {
            s32 next_state;
            s32 actor_state;

            actor_state = ((S_80170E5C_0 *)actor_in)->unk_9A;
            next_state = 0xE;

            if (actor_state != next_state) {
                anim_table = D_80174520;
                if (((S_80170E5C_2 *)sprite_in)->unk_2C != anim_table) {
                    (*(void * *)((u8 *)sprite_in + 0x2C)) = anim_table;
                    func_80047784(sprite_in,
                        anim_table[((gameWork.view.viewAngle + ((S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80170E5C_0 *)actor_in)->unk_9A = next_state;
            }
        }

        ((S_80170E5C_0 *)actor_in)->unk_98 &= 0xFFF3;
        if (((S_80170E5C_1 *)status)->unk_64 != 0) {
            if (func_800AA6B4(actor_in, context_in, sprite_in, D_80174548)) {
                return;
            }
        }

        if (((S_80170E5C_1 *)status)->unk_1C & 0x80000) {
            func_800AA888(actor_in, context_in, sprite_in, status);
            func_801737DC(actor_in, context_in, sprite_in, status);
            return;
        }

        if ((s16)func_800A1C58(status) != 0) {
            func_800AAB10(actor_in, context_in, sprite_in, status);
        }
    }

    tile_record = func_8009FB34(((S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((S_80170E5C_2 *)sprite_in)->unk_24.at01.v);
    ((S_80170E5C_2 *)sprite_in)->unk_26 = tile_record;

    if (((S_80170E5C_1 *)status)->unk_6D > 0) {
        if (((S_80170E5C_1 *)status)->unk_1C & 0x20) {
            goto special_cleanup;
        }
        if (((S_80170E5C_2 *)sprite_in)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            goto ordinary_cleanup;
        }
        if (!(((S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(status,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80173E48(actor_in, context_in, sprite_in, 0) == 0) {
                return;
            }
            ((S_80170E5C_1 *)status)->unk_46 |= 0x4000;
            if (!(((S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

        switch (((S_80170E5C_1 *)status)->unk_46 & 0x3FFF) {
        case 8:
        case 9:
            if ((s16)func_80171E10(actor_in, context_in, sprite_in, status) == 0) {
                func_80171FD4(actor_in, context_in, sprite_in, status);
            }
            return;

        case 4:
            if (((S_80170E5C_1 *)status)->unk_1C & 0x400) {
                register s32 movement_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                movement_flags = ((S_80170E5C_1 *)status)->unk_14;

                if (movement_flags >= 0) {
                    ((S_80170E5C_1 *)status)->unk_14 = movement_flags | 0x80000000;
                    ((S_80170E5C_1 *)status)->unk_2A.u += (func_800A6D30(actor_in) & 7) << 9;
                }
            }
            if ((s16)func_801720EC(actor_in, context_in, sprite_in, status) != 0) {
                return;
            }
            func_8017236C(actor_in, context_in, sprite_in, status);
            return;

        case 5:
        case 6:
        case 7:
        {
            EntityRec *active_actor;
            s32 direction;

            direction = func_800A0818(
                ((S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((S_80170E5C_2 *)sprite_in)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &direction_aux);
            active_actor = D_800814A8;
            ((S_80170E5C_1 *)status)->unk_2A.s = direction;
            if (active_actor->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
        }

        case 12:
special_cleanup:
            func_800A9A0C(status);
            return;

        case 1:
        case 2:
        case 3:
aaf_cleanup:
            func_800AAF00(actor_in, context_in, sprite_in, D_80174560, func_80170E5C);
            return;

        case 11:
        default:
ordinary_cleanup:
            func_80171420(actor_in, context_in, sprite_in, status);
            return;
        }
    } else if (!(((S_80170E5C_1 *)status)->unk_1C & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(((S_80170E5C_1 *)status)->unk_1C & 0x430)) {

                if ((s16)func_8009FD7C(((S_80170E5C_2 *)sprite_in)->unk_24.at00.v,
                        ((S_80170E5C_2 *)sprite_in)->unk_24.at01.v, D_80082E80.tileX,
                        D_80082E80.tileY) != 0) {
                    ((S_80170E5C_1 *)status)->unk_2A.s = func_800A0818(
                        ((S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((S_80170E5C_2 *)sprite_in)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_aux);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80170E5C_2 *)sprite_in)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174520;
    if (((S_80170E5C_2 *)sprite_in)->unk_2C == anim_table) {
        return;
    }

update_table:
    (*(void * *)((u8 *)sprite_in + 0x2C)) = anim_table;
    func_80047784(sprite_in,
        *(u8 *)((u32)(((gameWork.view.viewAngle + ((S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7) +
                (u32)anim_table),
        0);
}
