#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8014D0EC_0 {
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
    u8 pad_A4[0xE];
    s16 unk_B2;
} S_8014D0EC_0;   /* arg0 in func_8014D0EC */


typedef struct S_8014D0EC_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_8014D0EC_2;   /* arg2 in func_8014D0EC */


typedef struct S_8014D0EC_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8014D0EC_4;   /* origin in func_8014D0EC */

typedef struct S_8014D0EC_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_8014D0EC_5;   /* player in func_8014D0EC */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 func_80042900(void *, s32);
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
extern void func_8014D69C(void *, void *, void *, void *);
extern void func_8014D854(void *, void *, void *, void *);
extern s32 func_8014DF9C(void *, void *, void *, void *);
extern void func_8014E234(void *, void *, void *, void *);
extern void func_8014E358(void *, void *, void *, void *);
extern s32 func_8014E66C(void *, void *, void *, s32);
extern void func_80150574(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern u8 D_80151E40[];
extern u8 D_80151E48[];
extern u8 D_80151E98[];
extern u8 D_80151EA0[];
extern u8 D_80151EB0[];
extern u8 D_80151EB8[];

/* Updates actor animation, facing, and behavior from dungeon and entity state. */
void func_8014D0EC(void *actor, void *context, void *sprite, void *entity)
{
    s32 direction_scratch;
    s8 room_id;
    u16 behavior_flags;

    if (D_80083462 & 0x1000) {
        ((S_8014D0EC_0 *)actor)->unk_9A = 0xE;
        func_8014D69C(actor, context, sprite, entity);
        return;
    }

    if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v == 0) {
        u8 *anim_table;

        func_800AA79C(actor, context, sprite, entity);
        if (((S_8014D0EC_2 *)sprite)->unk_2C == D_80151EA0) {
            return;
        }
        anim_table = D_80151EB0;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            anim_table[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x200) {
        if (((S_8014D0EC_2 *)sprite)->unk_2C == D_80151EA0) {
            ((S_8014D0EC_0 *)actor)->unk_9A = 0xD;
            ((S_8014D0EC_0 *)actor)->unk_9B = 1;
            ((S_8014D0EC_0 *)actor)->unk_8C = 0;
            ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_80151EB0) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }

        {
            void *current_anim;
            u8 *anim_table;

            if (((S_8014D0EC_0 *)actor)->unk_9A != 0xE) {
                ((S_8014D0EC_0 *)actor)->unk_9A = 0xE;
                ((S_8014D0EC_0 *)actor)->unk_B2 = 0;
            }

            current_anim = ((S_8014D0EC_2 *)sprite)->unk_2C;
            if (current_anim == D_80151EB8) {
                if (((S_8014D0EC_2 *)sprite)->unk_14 & 0xE000) {
                    u8 *reset_anim_table = D_80151E40;

                    (*(void * *)((u8 *)sprite + 0x2C)) = reset_anim_table;
                    func_80047784(sprite,
                        reset_anim_table[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                    ((S_8014D0EC_2 *)sprite)->unk_05 = 1;
                    ((S_8014D0EC_0 *)actor)->unk_A2.s = 0;
                    ((S_8014D0EC_0 *)actor)->unk_9E = 0;
                }
            } else {
                anim_table = D_80151E40;
                if (current_anim != anim_table) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                    func_80047784(sprite,
                        anim_table[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                    ((S_8014D0EC_2 *)sprite)->unk_05 = 1;
                    ((S_8014D0EC_0 *)actor)->unk_A2.s = 0;
                    ((S_8014D0EC_0 *)actor)->unk_9E = 0;
                }
            }
        }

        ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 |= 0x40000;
        ((S_8014D0EC_0 *)actor)->unk_98 &= 0xFFF7;

        if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80151E48) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x80000) {
            s16 position_delta;

            func_800AA888(actor, context, sprite, entity);
            position_delta = ((S_8014D0EC_0 *)actor)->unk_92.u - ((S_8014D0EC_0 *)actor)->unk_A2.u;
            ((S_8014D0EC_0 *)actor)->unk_A2.s = 0;
            ((S_8014D0EC_0 *)actor)->unk_9E = 0;
            ((S_8014D0EC_0 *)actor)->unk_92.s = position_delta;
            func_80150574(actor, context, sprite, entity);
            return;
        }

        if ((func_800A1C58(entity) << 16) != 0) {
            func_800AAB10(actor, context, sprite, entity);
        }
    }

    room_id = func_8009FB34(((S_8014D0EC_2 *)sprite)->unk_24.at00.v, ((S_8014D0EC_2 *)sprite)->unk_24.at01.v);
    ((S_8014D0EC_2 *)sprite)->unk_26 = room_id;

    if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }
        if (((S_8014D0EC_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(entity,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8014E66C(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            behavior_flags = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = behavior_flags;
            if (!(behavior_flags & 0x8000)) {
                goto generic;
            }
        }

        {
            static void *const dispatch_labels[] = {
                &&case_123, &&generic, &&sw_case89, &&sw_case567, &&case_12
            };
            extern void *const D_8014C808[];
            u32 behavior_index = (u32)((((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x3FFF) - 1);

            if (behavior_index >= 12) {
                goto generic;
            }
            (void)dispatch_labels;
            goto *D_8014C808[behavior_index];
        }
sw_case89:
            if ((func_8014DF9C(actor, context, sprite, entity) << 16) != 0) {
                return;
            }
            func_8014E234(actor, context, sprite, entity);
            return;

sw_case567:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 facing_angle;

            facing_angle = func_800A0818(
                ((S_8014D0EC_2 *)sprite)->unk_24.at00.v, ((S_8014D0EC_2 *)sprite)->unk_24.at01.v,
                ((S_8014D0EC_4 *)origin)->unk_24, ((S_8014D0EC_4 *)origin)->unk_25,
                &direction_scratch);
            player = D_800814A8;
            ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = facing_angle;
            if (((S_8014D0EC_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }
            /* fallthrough */

case_12:
            func_800A9A0C(entity);
            return;

case_123:
            func_800AAF00(actor, context, sprite, D_80151E98, func_8014D0EC);
            return;

generic:
            func_8014D854(actor, context, sprite, entity);
            return;
    }

    if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(((DungeonRecord *)D_800E2970)[room_index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_8014D0EC_2 *)sprite)->unk_24.at00.v, ((S_8014D0EC_2 *)sprite)->unk_24.at01.v,
                        ((S_8014D0EC_4 *)origin)->unk_24, ((S_8014D0EC_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = func_800A0818(
                        ((S_8014D0EC_2 *)sprite)->unk_24.at00.v, ((S_8014D0EC_2 *)sprite)->unk_24.at01.v,
                        ((S_8014D0EC_4 *)origin)->unk_24, ((S_8014D0EC_4 *)origin)->unk_25,
                        &direction_scratch);
                    return;
                }
            }
        }
    } else if ((func_80042900(entity, 4) << 16) == 0) {
        if (((Rec_D_800814A8 *)D_800814A8)->unk_9A == 0x17) {
            func_8014E358(actor, context, sprite, entity);
        }
    }
}
