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
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171684(void *, void *);
extern void func_801718DC(void *, void *, void *, void *);
extern s32 func_80172088(void *, void *, void *, void *);
extern void func_8017224C(void *, void *, void *, void *);
extern s32 func_80172364(void *, void *, void *, s32);
extern void func_80174060(void *, void *, void *, void *);
extern void func_80174234(void *, void *, void *, void *);
extern void func_80174B14(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800DCF5B;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80174F00[];
extern u8 D_80174F08[];
extern u8 D_80174F38;
extern u8 D_80174F40;
extern u8 D_80174F48;




typedef struct S_801710F4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801710F4_2;   /* arg2 in func_801710F4 */


typedef struct S_801710F4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801710F4_4;   /* origin in func_801710F4 */

typedef struct S_801710F4_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801710F4_5;   /* player in func_801710F4 */

/* Updates dungeon actor behavior, facing, and animation from its current state. */
void func_801710F4(void *actor_input, void *context_input, void *sprite_input, void *entity_input)
{
    static void *const action_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    void *actor;
    void *context;
    void *sprite;
    register void *entity ASM_REG("$18");
    u8 *anim_table;
    s32 distance;
    s8 room_id;
    u16 action_state;
    u16 initial_flags = D_80083462;

    actor = actor_input;
    context = context_input;
    sprite = sprite_input;
    entity = entity_input;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_80171684(actor, context);
        do {
            return;
        } while (0);
    }


    if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v == 0) {
        func_800AA79C(actor, context, sprite, entity);
        if (((S_801710F4_2 *)sprite)->unk_2C != &D_80174F48) {
            u8 *next_anim_table = &D_80174F40;

            (*(void * *)((u8 *)sprite + 0x2C)) = next_anim_table;
            func_80047784(sprite,
                *(u8 *)((u32)(((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) +
                    (u32)next_anim_table),
                0);
        }
        return;
    }

    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x200) {
        if (((S_801710F4_2 *)sprite)->unk_2C == &D_80174F48) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor, context, sprite, &D_80174F40) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            u8 actor_state = 0xE;

            anim_table = D_80174F00;
            if (((S_801710F4_2 *)sprite)->unk_2C != anim_table) {
                (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                func_80047784(sprite,
                    anim_table[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = actor_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
        if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80174F08) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(actor, context, sprite, entity);
            func_80174060(actor, context, sprite, entity);
            return;
        }

        if ((func_800A1C58(entity) << 16) != 0) {
            func_800AAB10(actor, context, sprite, entity);
        }
    }

    room_id = func_8009FB34(((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v);
    ((S_801710F4_2 *)sprite)->unk_26 = room_id;

    if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x20) {
            goto special_cleanup;
        }
        if (((S_801710F4_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(entity,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172364(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = action_state;
            if (!(action_state & 0x8000)) {
                goto generic;
            }
        }

        action_state = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x3FFF;
        if ((u32)(action_state - 1) >= 12) {
            goto generic;
        }
        (void)action_labels;
        goto *D_80170808[(u32)(action_state - 1)];

jt_c8:
jt_c9:
        if ((func_80172088(actor, context, sprite, entity) << 16) == 0) {
            func_8017224C(actor, context, sprite, entity);
        }
        return;

jt_c4:
        func_80174B14(actor, context, sprite, entity);
        return;

jt_c10:
jt_c11:
        if (D_800DCF5B != 0) {
            goto generic;
        }
        func_80174234(actor, context, sprite, entity);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 facing_angle;

            facing_angle = func_800A0818(
                ((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v,
                ((S_801710F4_4 *)origin)->unk_24, ((S_801710F4_4 *)origin)->unk_25,
                &distance);
            player = D_800814A8;
            ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = facing_angle;
            if (((S_801710F4_5 *)player)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
        }

jt_c12:
special_cleanup:
        func_800A9A0C(entity);
        return;

jt_c1:
jt_c2:
jt_c3:
aaf_cleanup:
        func_800AAF00(actor, context, sprite, &D_80174F38, func_801710F4);
        return;

generic:
        func_801718DC(actor, context, sprite, entity);
        return;
    }

    if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(((DungeonRecord *)D_800E2970)[room_index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v,
                        ((S_801710F4_4 *)origin)->unk_24, ((S_801710F4_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = func_800A0818(
                        ((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v,
                        ((S_801710F4_4 *)origin)->unk_24, ((S_801710F4_4 *)origin)->unk_25,
                        &distance);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_801710F4_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174F00;
    if (((S_801710F4_2 *)sprite)->unk_2C == anim_table) {
        return;
    }

    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
    func_80047784(sprite,
        *(u8 *)((u32)(((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) +
            (u32)anim_table),
        0);
}
