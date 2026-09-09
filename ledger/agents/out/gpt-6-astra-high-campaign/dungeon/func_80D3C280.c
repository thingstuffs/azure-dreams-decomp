#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80171A80_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    union { u8 n; volatile u8 v; } unk_9A;   /* accessed as both */
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u8 pad_A4[0xC];
    union { volatile u8 v; u8 n; } unk_B0;   /* accessed as both */
    u8 pad_B1[0x4];
    u8 unk_B5;
} S_80171A80_0;   /* arg0 in func_80171A80 */


typedef struct S_80171A80_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171A80_2;   /* arg2 in func_80171A80 */


typedef struct S_80171A80_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171A80_4;   /* origin in func_80171A80 */

typedef struct S_80171A80_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171A80_5;   /* player in func_80171A80 */

typedef struct S_80171A80_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80171A80_6;   /* global in func_80171A80 */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

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
extern void func_800D6068(void *, void *, void *, void *);
extern void func_801708B8(void *, void *, void *);
extern void func_801717D0(void *, void *, void *, void *, void *);
extern void func_80172144(void *, void *, void *, void *);
extern void func_801723F8(void *, void *, void *, void *);
extern s32 func_80172BB0(void *, void *, void *, void *);
extern void func_80172D88(void *, void *, void *, void *);
extern s32 func_80172EA8(void *, void *, void *, s32);
extern void func_80174A68(void *, void *, void *, void *);
extern void func_801754AC(void *, void *, void *, void *);
extern void func_80175F44(void *, void *, void *, s32, s32);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800E23E0[];
extern u8 D_800E23F8[];
extern u8 D_800E2418[];
extern u8 D_800E2420[];
extern u8 D_800E2428[];
extern s8 D_800E2970[];
extern void *D_80170820[];
extern u8 D_80171A80[];
extern void *D_800E3D7C[];

/* Updates dungeon actor animation, status, and action dispatch. */
void func_80171A80(void *entity, void *context, void *sprite, void *actor)
{
    static void *const action_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    s32 distance;
    s8 room_id;
    u16 action_state;

    if (D_80083462 & 0x1000) {
        ((S_80171A80_0 *)entity)->unk_9A.n = 0xE;
        func_80172144(entity, context, sprite, actor);
        return;
    }

    if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v == 0) {
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            void *anim_table;

            func_800AA79C(entity, context, sprite, actor);
            if (((S_80171A80_2 *)sprite)->unk_2C == D_800E2428) {
                return;
            }
            anim_table = D_800E2420;
            (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
            func_80047784(sprite,
                ((u8 *)anim_table)[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            return;
        } else {
            func_80175F44(entity, context, sprite, 0, 0);
            return;
        }
    }

    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x200) {
        if (((S_80171A80_2 *)sprite)->unk_2C == D_800E2428) {
            ((S_80171A80_0 *)entity)->unk_9A.n = 0xD;
            ((S_80171A80_0 *)entity)->unk_9B = 1;
            ((S_80171A80_0 *)entity)->unk_8C = 0;
            ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(entity, context, sprite, D_800E2420) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x100) {
            func_800AA258(entity, context, sprite, actor);
            return;
        }

        if (((S_80171A80_0 *)entity)->unk_9A.v != 0xE) {
            ((S_80171A80_0 *)entity)->unk_9A.v = 0xE;
        }
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            void *anim_table = D_800E23E0;
            u8 is_active;

            if (((S_80171A80_2 *)sprite)->unk_2C != anim_table) {
                (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                func_80047784(sprite,
                    ((u8 *)anim_table)[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                    0);
                ((S_80171A80_2 *)sprite)->unk_05 = 1;
                is_active = ((S_80171A80_0 *)entity)->unk_B0.v;
                ((S_80171A80_0 *)entity)->unk_9E = 0;
                ((S_80171A80_0 *)entity)->unk_A2.s = 0;
            } else {
                is_active = ((S_80171A80_0 *)entity)->unk_B0.n;
            }
            if (is_active == 0) {
                func_801708B8(entity, context, sprite);
            }
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 |= 0x40000;
                ((S_80171A80_0 *)entity)->unk_98 &= 0xFFF7;
            }
        }

        if (((Rec_D_800E3D7C *)actor)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(entity, context, sprite, D_800E23F8) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x80000) {
            s16 height_delta;

            func_800AA888(entity, context, sprite, actor);
            height_delta = ((S_80171A80_0 *)entity)->unk_92.u - ((S_80171A80_0 *)entity)->unk_A2.u;
            ((S_80171A80_0 *)entity)->unk_A2.s = 0;
            ((S_80171A80_0 *)entity)->unk_9E = 0;
            ((S_80171A80_0 *)entity)->unk_92.s = height_delta;
            func_80174A68(entity, context, sprite, actor);
            return;
        }

        if ((func_800A1C58(actor) << 16) != 0) {
            func_800AAB10(entity, context, sprite, actor);
        }
    }

    room_id = func_8009FB34(((S_80171A80_2 *)sprite)->unk_24.at00.v, ((S_80171A80_2 *)sprite)->unk_24.at01.v);
    ((S_80171A80_2 *)sprite)->unk_26 = room_id;

    if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x20) {
            goto jt_c12;
        }
        if (((S_80171A80_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(actor,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172EA8(entity, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v = action_state;
            if (!(action_state & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

        action_state = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x3FFF;
        if ((u32)(action_state - 1) >= 12) {
            goto ordinary_cleanup;
        }
        (void)action_labels;
        goto *D_80170820[(u32)(action_state - 1)];

jt_c8:
jt_c9:
        if ((func_80172BB0(entity, context, sprite, actor) << 16) != 0) {
            return;
        }
        func_80172D88(entity, context, sprite, actor);
        return;

jt_c1:
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            func_801754AC(entity, context, sprite, actor);
            return;
        }
        func_80175F44(entity, context, sprite, 1, 0);
        return;

jt_c2:
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            func_800D6068(entity, context, sprite, actor);
            return;
        }
        func_80175F44(entity, context, sprite, 1, 0);
        return;

jt_c5:
jt_c6:
jt_c7:
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            u8 *origin = D_80082E80;
            void *player;
            s16 facing;

            facing = func_800A0818(
                ((S_80171A80_2 *)sprite)->unk_24.at00.v, ((S_80171A80_2 *)sprite)->unk_24.at01.v,
                ((S_80171A80_4 *)origin)->unk_24, ((S_80171A80_4 *)origin)->unk_25,
                &distance);
            player = D_800814A8;
            ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = facing;
            if (((S_80171A80_5 *)player)->unk_9A == 0x11) {
                goto coords_continue;
            }
        } else {
            goto global_continue;
        }

jt_c12:
        func_800A9A0C(actor);
        return;

coords_continue:
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            func_801717D0(entity, context, sprite, D_800E2418, D_80171A80);
            return;
        }
global_continue:
        {
            void *leader = D_800E3D7C[0];

            if (((S_80171A80_6 *)leader)->unk_A6 != 0) {
                goto ordinary_cleanup;
            }
            ((S_80171A80_6 *)leader)->unk_A6 = 2;
            func_80175F44(entity, context, sprite, 1, 2);
            return;
        }

jt_c3:
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            func_800AAF00(entity, context, sprite, D_800E2418, D_80171A80);
            return;
        } else {
            s32 action_mode = 1;

            func_80175F44(entity, context, sprite,
                1, action_mode);
            return;
        }

jt_c4:
jt_c10:
jt_c11:
ordinary_cleanup:
        func_801723F8(entity, context, sprite, actor);
        return;
    }

    if (!(((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(((DungeonRecord *)D_800E2970)[room_index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80171A80_2 *)sprite)->unk_24.at00.v, ((S_80171A80_2 *)sprite)->unk_24.at01.v,
                        ((S_80171A80_4 *)origin)->unk_24, ((S_80171A80_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(
                        ((S_80171A80_2 *)sprite)->unk_24.at00.v, ((S_80171A80_2 *)sprite)->unk_24.at01.v,
                        ((S_80171A80_4 *)origin)->unk_24, ((S_80171A80_4 *)origin)->unk_25,
                        &distance);
                }
            }
        }
    }
}
