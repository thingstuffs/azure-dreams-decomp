#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_8015FFA4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u8 pad_A4[0x12];
    s16 unk_B6;
} S_8015FFA4_0;   /* arg0 in func_8015FFA4 */


typedef struct S_8015FFA4_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_8015FFA4_2;   /* arg2 in func_8015FFA4 */


typedef struct S_8015FFA4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8015FFA4_4;   /* origin in func_8015FFA4 */

typedef struct S_8015FFA4_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_8015FFA4_5;   /* player in func_8015FFA4 */




extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80160510(void *, void *, void *, void *);
extern void func_801606C8(void *, void *, void *, void *);
extern s32 func_80160E10(void *, void *, void *, void *);
extern void func_801610A8(void *, void *, void *, void *);
extern s32 func_801611CC(void *, void *, void *, void *);
extern void func_80163078(void *, void *, void *, void *);

extern void *D_8015E818[];
extern u8 D_8015FFA4[];
extern u8 D_80163C30[];
extern u8 D_80163C38[];
extern u8 D_80163C88[];
extern u8 D_80163C90[];
extern u8 D_80163CA0[];
extern u8 D_80163CA8[];

/* Updates actor animation, dispatches its action state, and adjusts facing toward the player. */
void func_8015FFA4(void *actor, void *actor_aux, void *sprite, void *entity)
{
    static void *const state_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    s32 direction_aux;
    s8 room_id;
    u16 action_state;

    if (dungeonStatus.flags & 0x1000) {
        ((S_8015FFA4_0 *)actor)->unk_9A = 0xE;
        func_80160510(actor, actor_aux, sprite, entity);
        return;
    }
    if (((EntityRec *)entity)->tileY == 0) {
        void *anim_table;

        func_800AA79C(actor, actor_aux, sprite, entity);
        if (((S_8015FFA4_2 *)sprite)->unk_2C == D_80163C90) {
            return;
        }
        anim_table = D_80163CA0;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            ((u8 *)anim_table)[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)((EntityRec *)entity)->flags1C) & 0x200) {
        if (((S_8015FFA4_2 *)sprite)->unk_2C == D_80163C90) {
            ((S_8015FFA4_0 *)actor)->unk_9A = 0xD;
            ((S_8015FFA4_0 *)actor)->unk_9B = 1;
            ((S_8015FFA4_0 *)actor)->unk_8C = 0;
            ((EntityRec *)entity)->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor, actor_aux, sprite, D_80163CA0) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)((EntityRec *)entity)->flags1C) & 0x100) {
            func_800AA258(actor, actor_aux, sprite, entity);
            return;
        }

        {
            u8 current_state = ((S_8015FFA4_0 *)actor)->unk_9A;
            u32 next_state = 0xE;
            void *current_anim;

            if (current_state != next_state) {
                ((S_8015FFA4_0 *)actor)->unk_9A = next_state;
                ((S_8015FFA4_0 *)actor)->unk_B6 = 0;
            }
            current_anim = ((S_8015FFA4_2 *)sprite)->unk_2C;
            if (current_anim == D_80163CA8) {
                if (!(((S_8015FFA4_2 *)sprite)->unk_14 & 0xE000)) {
                    goto table_done;
                }
                (*(void * *)((u8 *)sprite + 0x2C)) = D_80163C30;
                func_80047784(sprite,
                    D_80163C30[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                    0);
            } else {
                void *idle_anim = D_80163C30;
                if (current_anim == idle_anim) {
                    goto table_done;
                }
                (*(void * *)((u8 *)sprite + 0x2C)) = idle_anim;
                func_80047784(sprite,
                    *(u8 *)((u32)(((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7) + (u32)idle_anim),
                    0);
            }
            ((S_8015FFA4_2 *)sprite)->unk_05 = 1;
            ((S_8015FFA4_0 *)actor)->unk_A2.s = 0;
            ((S_8015FFA4_0 *)actor)->unk_9E = 0;
        }
table_done:

        (*(u32 *)&((EntityRec *)entity)->flags1C) |= 0x40000;
        ((S_8015FFA4_0 *)actor)->unk_98 &= 0xFFF7;

        if (((EntityRec *)entity)->unk_64 != 0) {
            if (func_800AA6B4(actor, actor_aux, sprite, D_80163C38) != 0) {
                return;
            }
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x80000) {
            s16 base_height;

            func_800AA888(actor, actor_aux, sprite, entity);
            base_height = ((S_8015FFA4_0 *)actor)->unk_92.u - ((S_8015FFA4_0 *)actor)->unk_A2.u;
            ((S_8015FFA4_0 *)actor)->unk_A2.s = 0;
            ((S_8015FFA4_0 *)actor)->unk_9E = 0;
            ((S_8015FFA4_0 *)actor)->unk_92.s = base_height;
            func_80163078(actor, actor_aux, sprite, entity);
            return;
        }

        if ((func_800A1C58(entity) << 16) != 0) {
            func_800AAB10(actor, actor_aux, sprite, entity);
        }
    }

    room_id = func_8009FB34(((S_8015FFA4_2 *)sprite)->unk_24.at00.v, ((S_8015FFA4_2 *)sprite)->unk_24.at01.v);
    ((S_8015FFA4_2 *)sprite)->unk_26 = room_id;

    if (((EntityRec *)entity)->unk_6D > 0) {
        if (((u32)((EntityRec *)entity)->flags1C) & 0x20) {
            goto case_12;
        }
        if (((S_8015FFA4_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            goto generic;
        }
        if (!(((EntityRec *)entity)->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(entity,
                        (u8 *)((EntityRec *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801611CC(actor, actor_aux, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = ((EntityRec *)entity)->unk_46 | 0x4000;
            ((EntityRec *)entity)->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                goto generic;
            }
        }

        action_state = ((EntityRec *)entity)->unk_46 & 0x3FFF;
        if ((u32)(action_state - 1) >= 12) {
            goto generic;
        }
        (void)state_labels;
        goto *D_8015E818[(u32)(action_state - 1)];

jt_c8:
jt_c9:
        if ((func_80160E10(actor, actor_aux, sprite, entity) << 16) != 0) {
            return;
        }
        func_801610A8(actor, actor_aux, sprite, entity);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            void *player;
            s16 facing;

            facing = func_800A0818(
                ((S_8015FFA4_2 *)sprite)->unk_24.at00.v, ((S_8015FFA4_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &direction_aux);
            player = D_800814A8;
            ((EntityRec *)entity)->facing = facing;
            if (((S_8015FFA4_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }

jt_c12:
case_12:
        func_800A9A0C(entity);
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(actor, actor_aux, sprite, D_80163C88, D_8015FFA4);
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_801606C8(actor, actor_aux, sprite, entity);
        return;
    }

    if (!(((u32)((EntityRec *)entity)->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)((EntityRec *)entity)->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                        ((S_8015FFA4_2 *)sprite)->unk_24.at00.v, ((S_8015FFA4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    ((EntityRec *)entity)->facing = func_800A0818(
                        ((S_8015FFA4_2 *)sprite)->unk_24.at00.v, ((S_8015FFA4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_aux);
                }
            }
        }
    }
}
