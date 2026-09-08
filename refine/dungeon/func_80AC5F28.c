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
extern void func_80171CD4(void *, void *, void *, void *);
extern void func_80171F40(void *, void *, void *, void *);
extern s32 func_80172710(void *, void *, void *, void *);
extern void func_801728D4(void *, void *, void *, void *);
extern s32 func_801729EC(void *, void *, void *, s32);
extern void func_801743E8(void *, void *, void *, void *);
extern void func_80174928(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern s32 D_80171728;
extern u8 D_80174DEC[];
extern u8 D_80174DFC[];
extern u8 D_80174E2C[];
extern u8 D_80174E44[];
extern u8 D_80174E4C[];




typedef struct S_80171728_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171728_2;   /* arg2 in func_80171728 */


typedef struct S_80171728_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171728_4;   /* origin in func_80171728 */

typedef struct S_80171728_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171728_5;   /* player in func_80171728 */

/* Updates creature behavior, facing, and animation from dungeon and action state. */
void func_80171728(void *actor_in, void *context_in, void *sprite_in, void *creature_in)
{
    static void *const action_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    void *actor;
    void *context;
    void *sprite;
    register void *creature ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *anim_table;
    s32 distance;
    s8 room_id;
    u16 action_flags;
    u32 initial_flags = D_80083462;

    actor = actor_in;
    context = context_in;
    sprite = sprite_in;
    creature = creature_in;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_80171CD4(actor, context, sprite, creature);
        return;
    }

    ASM_KEEP(actor);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(context);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(sprite);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(creature);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    if (((Rec_D_800E3D7C *)creature)->unk_24.at01_u8.v == 0) {
        func_800AA79C(actor, context, sprite, creature);
        if (((S_80171728_2 *)sprite)->unk_2C == D_80174E4C) {
            return;
        }
        {
            register u8 *anim_page ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */

            anim_page = (u8 *)0x80170000;
            ASM_KEEP(anim_page);   /* MATCH pin: load-bearing for the whole function shape */
            anim_table = anim_page + 0x4E44;
        }
        goto set_table;
    }

    if (((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x200) {
        if (((S_80171728_2 *)sprite)->unk_2C == D_80174E4C) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            ((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_80174E44) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x100) {
            func_800AA258(actor, context, sprite, creature);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8;
            u32 next_state;

            next_state = 0xE;
            if (current_state != next_state) {
                anim_table = D_80174DEC;
                if (((S_80171728_2 *)sprite)->unk_2C != anim_table) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                    func_80047784(sprite,
                        anim_table[((D_80083228 + ((Rec_D_800E3D7C *)creature)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = 0x14;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = next_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
        if (((Rec_D_800E3D7C *)creature)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80174DFC) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(actor, context, sprite, creature);
            func_801743E8(actor, context, sprite, creature);
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174DEC;
            func_80047784(sprite,
                D_80174DEC[((D_80083228 + ((Rec_D_800E3D7C *)creature)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((func_800A1C58(creature) << 16) != 0) {
            func_800AAB10(actor, context, sprite, creature);
        }
    }

    room_id = func_8009FB34(((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v);
    ((S_80171728_2 *)sprite)->unk_26 = room_id;

    if (((Rec_D_800E3D7C *)creature)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x20) {
            goto jt_c12;
        }
        if (((S_80171728_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)creature)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(creature,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801729EC(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = ((Rec_D_800E3D7C *)creature)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)creature)->unk_44.at02_u16.v = action_flags;
            if (!(action_flags & 0x8000)) {
                goto generic;
            }
        }

        action_flags = ((Rec_D_800E3D7C *)creature)->unk_44.at02_u16.v & 0x3FFF;
        if ((u32)(action_flags - 1) >= 12) {
            goto generic;
        }
        (void)action_labels;
        goto *D_80170808[(u32)(action_flags - 1)];

jt_c8:
jt_c9:
        if ((func_80172710(actor, context, sprite, creature) << 16) != 0) {
            return;
        }
        func_801728D4(actor, context, sprite, creature);
        return;

jt_c10:
        func_80174928(actor, context, sprite, creature);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 heading;

            heading = func_800A0818(
                ((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v,
                ((S_80171728_4 *)origin)->unk_24, ((S_80171728_4 *)origin)->unk_25,
                &distance);
            player = D_800814A8;
            ((Rec_D_800E3D7C *)creature)->unk_2A.as_s16 = heading;
            if (((S_80171728_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }

jt_c12:
        func_800A9A0C(creature);
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(actor, context, sprite, D_80174E2C, &D_80171728);
        return;

jt_c4:
jt_c11:
generic:
        func_80171F40(actor, context, sprite, creature);
        return;
    }

    if (!(((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(((DungeonRecord *)D_800E2970)[room_index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)creature)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v,
                        ((S_80171728_4 *)origin)->unk_24, ((S_80171728_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)creature)->unk_2A.as_s16 = func_800A0818(
                        ((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v,
                        ((S_80171728_4 *)origin)->unk_24, ((S_80171728_4 *)origin)->unk_25,
                        &distance);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80171728_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174DEC;
    if (((S_80171728_2 *)sprite)->unk_2C == anim_table) {
        return;
    }
set_table:
    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
    func_80047784(sprite,
        *(u8 *)(((((D_80083228 + ((Rec_D_800E3D7C *)creature)->unk_2A.as_s16 + 0x100) >> 9) & 7)) + (u32)anim_table),
        0);
}
