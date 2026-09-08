#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


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
extern void func_80171574(void *, void *);
extern void func_80171784(void *, void *, void *, void *);
extern s32 func_80171ECC(void *, void *, void *, void *);
extern void func_80172090(void *, void *, void *, void *);
extern s32 func_801721B4(void *, void *, void *, void *);
extern void func_80173468(void *, void *, void *, void *);
extern void func_80173AE8(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80171014[];
extern u8 D_8017420C[];
extern u8 D_8017421C[];
extern u8 D_8017424C[];
extern u8 D_80174254[];
extern u8 D_8017425C[];


typedef struct S_80171014_0 {
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
} S_80171014_0;   /* arg0 in func_80171014 */


typedef struct S_80171014_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171014_2;   /* arg2 in func_80171014 */


typedef struct S_80171014_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171014_4;   /* origin in func_80171014 */

typedef struct S_80171014_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171014_5;   /* player in func_80171014 */

/* Updates a dungeon actor's state, animation, and behavior. */
void func_80171014(void *actor, void *actor_context, void *map_object, void *creature)
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
        ((S_80171014_0 *)actor)->unk_9A = 0xE;
        func_80171574(actor, actor_context);
        return;
    }
    if (((Rec_D_800E3D7C *)creature)->unk_24.at01_u8.v == 0) {
        void *animation_table;

        func_800AA79C(actor, actor_context, map_object, creature);
        if (((S_80171014_2 *)map_object)->unk_2C == D_8017425C) {
            return;
        }
        animation_table = D_80174254;
        (*(void * *)((u8 *)map_object + (0x2C))) = animation_table;
        func_80047784(map_object,
            ((u8 *)animation_table)[((D_80083228 + ((Rec_D_800E3D7C *)creature)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x200) {
        if (((S_80171014_2 *)map_object)->unk_2C == D_8017425C) {
            ((S_80171014_0 *)actor)->unk_9A = 0xD;
            ((S_80171014_0 *)actor)->unk_9B = 1;
            ((S_80171014_0 *)actor)->unk_8C = 0;
            ((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor, actor_context, map_object, D_80174254) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x100) {
            func_800AA258(actor, actor_context, map_object, creature);
            return;
        }

        {
            u8 current_state = ((S_80171014_0 *)actor)->unk_9A;
            u32 next_state = 0xE;
            void *current_animation;
            void *animation_table;

            if (current_state != next_state) {
                ((S_80171014_0 *)actor)->unk_9A = next_state;
            }
            current_animation = ((S_80171014_2 *)map_object)->unk_2C;
            animation_table = D_8017420C;
            if (current_animation != animation_table) {
                (*(void * *)((u8 *)map_object + (0x2C))) = animation_table;
                func_80047784(map_object,
                    ((u8 *)animation_table)[((D_80083228 + ((Rec_D_800E3D7C *)creature)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                    0);
                ((S_80171014_2 *)map_object)->unk_05 = 1;
                ((S_80171014_0 *)actor)->unk_A2.s = 0;
                ((S_80171014_0 *)actor)->unk_9E = 0;
            }
        }

        ((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 |= 0x40000;
        ((S_80171014_0 *)actor)->unk_98 &= 0xFFF7;

        if (((Rec_D_800E3D7C *)creature)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(actor, actor_context, map_object, D_8017421C) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x80000) {
            s16 offset_delta;

            func_800AA888(actor, actor_context, map_object, creature);
            offset_delta = ((S_80171014_0 *)actor)->unk_92.u - ((S_80171014_0 *)actor)->unk_A2.u;
            ((S_80171014_0 *)actor)->unk_A2.s = 0;
            ((S_80171014_0 *)actor)->unk_9E = 0;
            ((S_80171014_0 *)actor)->unk_92.s = offset_delta;
            func_80173468(actor, actor_context, map_object, creature);
            return;
        }

        if ((func_800A1C58(creature) << 16) != 0) {
            if ((func_800AAB10(actor, actor_context, map_object, creature) << 16) != 0) {
                func_80173AE8(actor, actor_context, map_object, creature);
                return;
            }
        }
    }

    room_id = func_8009FB34(((S_80171014_2 *)map_object)->unk_24.at00.v, ((S_80171014_2 *)map_object)->unk_24.at01.v);
    ((S_80171014_2 *)map_object)->unk_26 = room_id;

    if (((Rec_D_800E3D7C *)creature)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }
        if (((S_80171014_2 *)map_object)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)creature)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(creature,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801721B4(actor, actor_context, map_object, 0) << 16) == 0) {
                return;
            }
            action_state = ((Rec_D_800E3D7C *)creature)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)creature)->unk_44.at02_u16.v = action_state;
            if (!(action_state & 0x8000)) {
                goto generic;
            }
        }

        action_state = ((Rec_D_800E3D7C *)creature)->unk_44.at02_u16.v & 0x3FFF;
        if ((u32)(action_state - 1) >= 12) {
            goto generic;
        }
        (void)action_labels;
        goto *D_80170808[(u32)(action_state - 1)];

jt_c8:
jt_c9:
        if ((func_80171ECC(actor, actor_context, map_object, creature) << 16) != 0) {
            return;
        }
        func_80172090(actor, actor_context, map_object, creature);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 facing_angle;

            facing_angle = func_800A0818(
                ((S_80171014_2 *)map_object)->unk_24.at00.v, ((S_80171014_2 *)map_object)->unk_24.at01.v,
                ((S_80171014_4 *)origin)->unk_24, ((S_80171014_4 *)origin)->unk_25,
                &distance);
            player = D_800814A8;
            ((Rec_D_800E3D7C *)creature)->unk_2A.as_s16 = facing_angle;
            if (((S_80171014_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }

jt_c12:
case_12:
        func_800A9A0C(creature);
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(actor, actor_context, map_object, D_8017424C, D_80171014);
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_80171784(actor, actor_context, map_object, creature);
        return;
    }

    if (!(((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(((DungeonRecord *)D_800E2970)[room_index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80171014_2 *)map_object)->unk_24.at00.v, ((S_80171014_2 *)map_object)->unk_24.at01.v,
                        ((S_80171014_4 *)origin)->unk_24, ((S_80171014_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)creature)->unk_2A.as_s16 = func_800A0818(
                        ((S_80171014_2 *)map_object)->unk_24.at00.v, ((S_80171014_2 *)map_object)->unk_24.at01.v,
                        ((S_80171014_4 *)origin)->unk_24, ((S_80171014_4 *)origin)->unk_25,
                        &distance);
                }
            }
        }
    }
}
