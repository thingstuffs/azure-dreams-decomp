#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
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
extern void func_80171CD8(void *, void *, void *, void *);
extern void func_80171F1C(void *, void *, void *, void *);
extern s32 func_801726D0(void *, void *, void *, void *);
extern void func_80172894(void *, void *, void *, void *);
extern s32 func_801729AC(void *, void *, void *, s32);
extern void func_80174598(void *, void *, void *, void *);
extern void func_8017476C(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80171760[];
extern u8 D_80174E88[];
extern u8 D_8017555C[];
extern u8 D_80174E98[];
extern u8 D_80174EE0[];
extern u8 D_80174EE8[];
extern u8 D_80174EF0[];




typedef struct S_80171760_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171760_2;   /* arg2 in func_80171760 */


typedef struct S_80171760_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171760_4;   /* origin in func_80171760 */

typedef struct S_80171760_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171760_5;   /* player in func_80171760 */

/* Update the actor's dungeon behavior, facing, and directional animation. */
void func_80171760(void *motion, void *render_ctx, void *map_entity, void *actor)
{
    static void *const action_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    u8 *anim_table;
    s32 room_id;
    s32 direction_flags;
    u32 initial_flags = D_80083462;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)motion)->unk_9A.as_u8 = 0xE;
        func_80171CD8(motion, render_ctx, map_entity, actor);
        return;
    }

    if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v == 0) {
        func_800AA79C(motion, render_ctx, map_entity, actor);
        if (((S_80171760_2 *)map_entity)->unk_2C != D_80174EF0) {
            (*(void * *)((u8 *)map_entity + (0x2C))) = D_80174EE8;
            func_80047784(map_entity,
                *(u8 *)((((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32)D_80174EE8),
                0);
            return;
        }
        return;
    }

    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x200) {
        if (((S_80171760_2 *)map_entity)->unk_2C == D_80174EF0) {
            ((Rec_func_800A9E70_arg0 *)motion)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)motion)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)motion)->unk_8C = 0;
            ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 &= ~0x40000;
            return;
        }
        if (func_800AA924(motion, render_ctx, map_entity, D_80174EE8)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x100) {
            func_800AA258(motion, render_ctx, map_entity, actor);
            return;
        }

        {
            u8 current_state;
            u8 idle_state;

            current_state = *(volatile u8 *)((u8 *)motion + 0x9A);
            idle_state = 0xE;
            if (current_state != idle_state) {
                anim_table = D_80174E88;
                if (((S_80171760_2 *)map_entity)->unk_2C != anim_table) {
                    (*(void * *)((u8 *)map_entity + (0x2C))) = anim_table;
                    func_80047784(map_entity,
                        anim_table[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)motion)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)motion)->unk_A0.at00_s16.v = (rand() & 0x1F) + 0xF;
                ((Rec_func_800A9E70_arg0 *)motion)->unk_9A.as_u8 = idle_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)motion)->unk_98 &= 0xFFF3;
        if (((Rec_D_800E3D7C *)actor)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(motion, render_ctx, map_entity, D_80174E98)) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(motion, render_ctx, map_entity, actor);
            func_80174598(motion, render_ctx, map_entity, actor);
            return;
        }

        if ((func_800A1C58(actor) << 16) != 0) {
            func_800AAB10(motion, render_ctx, map_entity, actor);
        }
    }

    room_id = func_8009FB34(((S_80171760_2 *)map_entity)->unk_24.at00.v, ((S_80171760_2 *)map_entity)->unk_24.at01.v);
    ((S_80171760_2 *)map_entity)->unk_26 = room_id;

    if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 > 0) {
        u16 action_state;

        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }
        if (((S_80171760_2 *)map_entity)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(actor,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801729AC(motion, render_ctx, map_entity, 0) << 16) == 0) {
                return;
            }
            action_state = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v = action_state;
            if (!(action_state & 0x8000)) {
                goto generic;
            }
        }

        action_state = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x3FFF;
        if ((u32)(action_state - 1) >= 12) {
            goto generic;
        }
        (void)action_labels;
        goto *D_80170808[(u32)(action_state - 1)];

jt_c8:
        if ((func_801726D0(motion, render_ctx, map_entity, actor) << 16) != 0) {
            return;
        }
        func_80172894(motion, render_ctx, map_entity, actor);
        return;

jt_c9:
        func_8017476C(motion, render_ctx, map_entity, actor);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 facing_angle;

            facing_angle = func_800A0818(
                ((S_80171760_2 *)map_entity)->unk_24.at00.v, ((S_80171760_2 *)map_entity)->unk_24.at01.v,
                ((S_80171760_4 *)origin)->unk_24, ((S_80171760_4 *)origin)->unk_25,
                &direction_flags);
            player = D_800814A8;
            ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = facing_angle;
            if (((S_80171760_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }

jt_c12:
case_12:
        func_800A9A0C(actor);
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(motion, render_ctx, map_entity, D_80174EE0, D_80171760);
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_80171F1C(motion, render_ctx, map_entity, actor);
        return;
    } else if (!(((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(((DungeonRecord *)D_800E2970)[room_index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80171760_2 *)map_entity)->unk_24.at00.v, ((S_80171760_2 *)map_entity)->unk_24.at01.v,
                        ((S_80171760_4 *)origin)->unk_24, ((S_80171760_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(
                        ((S_80171760_2 *)map_entity)->unk_24.at00.v, ((S_80171760_2 *)map_entity)->unk_24.at01.v,
                        ((S_80171760_4 *)origin)->unk_24, ((S_80171760_4 *)origin)->unk_25,
                        &direction_flags);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80171760_2 *)map_entity)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174E88;
    if (((S_80171760_2 *)map_entity)->unk_2C == anim_table) {
        return;
    }
update_common:
    (*(void * *)((u8 *)map_entity + (0x2C))) = anim_table;
    func_80047784(map_entity,
        *(u8 *)((((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32)anim_table),
        0);
}
