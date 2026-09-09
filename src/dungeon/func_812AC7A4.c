#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8016BFA4_0 {
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
} S_8016BFA4_0;   /* arg0 in func_8016BFA4 */


typedef struct S_8016BFA4_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_8016BFA4_2;   /* arg2 in func_8016BFA4 */


typedef struct S_8016BFA4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016BFA4_4;   /* origin in func_8016BFA4 */

typedef struct S_8016BFA4_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_8016BFA4_5;   /* player in func_8016BFA4 */



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
extern void func_8016C510(void *, void *, void *, void *);
extern void func_8016C6C8(void *, void *, void *, void *);
extern s32 func_8016CE10(void *, void *, void *, void *);
extern void func_8016D0A8(void *, void *, void *, void *);
extern s32 func_8016D1CC(void *, void *, void *, void *);
extern void func_8016F078(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_8016A818[];
extern u8 D_8016BFA4[];
extern u8 D_8016FC30[];
extern u8 D_8016FC38[];
extern u8 D_8016FC88[];
extern u8 D_8016FC90[];
extern u8 D_8016FCA0[];
extern u8 D_8016FCA8[];

/* Updates actor animation, facing, and action handling from dungeon state. */
void func_8016BFA4(void *actor, void *context, void *sprite, void *entity)
{
    static void *const action_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    s32 direction_flags;
    s8 area_id;
    u16 action;

    if (D_80083462 & 0x1000) {
        ((S_8016BFA4_0 *)actor)->unk_9A = 0xE;
        func_8016C510(actor, context, sprite, entity);
        return;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v == 0) {
        void *anim_table;

        func_800AA79C(actor, context, sprite, entity);
        if (((S_8016BFA4_2 *)sprite)->unk_2C == D_8016FC90) {
            return;
        }
        anim_table = D_8016FCA0;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            ((u8 *)anim_table)[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x200) {
        if (((S_8016BFA4_2 *)sprite)->unk_2C == D_8016FC90) {
            ((S_8016BFA4_0 *)actor)->unk_9A = 0xD;
            ((S_8016BFA4_0 *)actor)->unk_9B = 1;
            ((S_8016BFA4_0 *)actor)->unk_8C = 0;
            ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_8016FCA0) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }

        {
            u8 current_state = ((S_8016BFA4_0 *)actor)->unk_9A;
            u32 next_state = 0xE;
            void *current_anim;
            void *anim_table;

            if (current_state != next_state) {
                ((S_8016BFA4_0 *)actor)->unk_9A = next_state;
                ((S_8016BFA4_0 *)actor)->unk_B6 = 0;
            }
            current_anim = ((S_8016BFA4_2 *)sprite)->unk_2C;
            if (current_anim == D_8016FCA8) {
                if (((S_8016BFA4_2 *)sprite)->unk_14 & 0xE000) {
                    void *idle_anim; /* MATCH: form the jump arm anim_table address in a1. */
                    idle_anim = D_8016FC30;
                    (*(void * *)((u8 *)sprite + 0x2C)) = idle_anim;
                    func_80047784(sprite,
                        ((u8 *)idle_anim)[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                    ((S_8016BFA4_2 *)sprite)->unk_05 = 1;
                    ((S_8016BFA4_0 *)actor)->unk_A2.s = 0;
                    ((S_8016BFA4_0 *)actor)->unk_9E = 0;
                }
            } else {
                anim_table = D_8016FC30;
                if (current_anim != anim_table) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                    func_80047784(sprite,
                        ((u8 *)anim_table)[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                    ((S_8016BFA4_2 *)sprite)->unk_05 = 1;
                    ((S_8016BFA4_0 *)actor)->unk_A2.s = 0;
                    ((S_8016BFA4_0 *)actor)->unk_9E = 0;
                }
            }
        }

        ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 |= 0x40000;
        ((S_8016BFA4_0 *)actor)->unk_98 &= 0xFFF7;

        if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_8016FC38) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x80000) {
            s16 base_height;

            func_800AA888(actor, context, sprite, entity);
            base_height = ((S_8016BFA4_0 *)actor)->unk_92.u - ((S_8016BFA4_0 *)actor)->unk_A2.u;
            ((S_8016BFA4_0 *)actor)->unk_A2.s = 0;
            ((S_8016BFA4_0 *)actor)->unk_9E = 0;
            ((S_8016BFA4_0 *)actor)->unk_92.s = base_height;
            func_8016F078(actor, context, sprite, entity);
            return;
        }

        if ((func_800A1C58(entity) << 16) != 0) {
            func_800AAB10(actor, context, sprite, entity);
        }
    }

    area_id = func_8009FB34(((S_8016BFA4_2 *)sprite)->unk_24.at00.v, ((S_8016BFA4_2 *)sprite)->unk_24.at01.v);
    ((S_8016BFA4_2 *)sprite)->unk_26 = area_id;

    if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }
        if (((S_8016BFA4_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(entity,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8016D1CC(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = action;
            if (!(action & 0x8000)) {
                goto generic;
            }
        }

        action = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x3FFF;
        if ((u32)(action - 1) >= 12) {
            goto generic;
        }
        (void)action_labels;
        goto *D_8016A818[(u32)(action - 1)];

jt_c8:
jt_c9:
        if ((func_8016CE10(actor, context, sprite, entity) << 16) != 0) {
            return;
        }
        func_8016D0A8(actor, context, sprite, entity);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *reference_pos = D_80082E80;
            void *player;
            s16 facing;

            facing = func_800A0818(
                ((S_8016BFA4_2 *)sprite)->unk_24.at00.v, ((S_8016BFA4_2 *)sprite)->unk_24.at01.v,
                ((S_8016BFA4_4 *)reference_pos)->unk_24, ((S_8016BFA4_4 *)reference_pos)->unk_25,
                &direction_flags);
            player = D_800814A8;
            ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = facing;
            if (((S_8016BFA4_5 *)player)->unk_9A == 0x11) {
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
        func_800AAF00(actor, context, sprite, D_8016FC88, D_8016BFA4);
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_8016C6C8(actor, context, sprite, entity);
        return;
    }

    if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x2000)) {
        s32 area_index = area_id;

        if ((area_index < 0) ||
            !(((DungeonRecord *)D_800E2970)[area_index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x430)) {
                u8 *reference_pos = D_80082E80;

                if ((func_8009FD7C(
                        ((S_8016BFA4_2 *)sprite)->unk_24.at00.v, ((S_8016BFA4_2 *)sprite)->unk_24.at01.v,
                        ((S_8016BFA4_4 *)reference_pos)->unk_24, ((S_8016BFA4_4 *)reference_pos)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = func_800A0818(
                        ((S_8016BFA4_2 *)sprite)->unk_24.at00.v, ((S_8016BFA4_2 *)sprite)->unk_24.at01.v,
                        ((S_8016BFA4_4 *)reference_pos)->unk_24, ((S_8016BFA4_4 *)reference_pos)->unk_25,
                        &direction_flags);
                }
            }
        }
    }
}
