#include "common.h"
#include "records/Rec_D_800814A8.h"

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
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170E5C_2;   /* arg2 in func_80170E5C */


typedef struct S_80170E5C_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170E5C_4;   /* origin in func_80170E5C */

typedef struct S_80170E5C_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E5C_5;   /* global in func_80170E5C */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

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

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern void *const D_80170808[];
extern u8 D_80174520[];
extern u8 D_80174530[];
extern u8 D_80174538[];
extern u8 D_80174548[];
extern u8 D_80174560[];

/* Update actor actions, facing, and animation according to dungeon state. */
void func_80170E5C(void *actor_in, void *context_in, void *sprite_in, void *status_in)
{
    void *actor;
    void *context;
    register void *sprite ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *status;
    u8 *anim_table;
    s32 tile_record;
    s32 direction_aux;
    u32 initial_flags = D_80083462;

    actor = actor_in;
    context = context_in;
    sprite = sprite_in;
    status = status_in;

    if (initial_flags & 0x1000) {
        ((S_80170E5C_0 *)actor)->unk_9A = 0xE;
        func_80171B68(actor, context, sprite, status);
        return;
    }

    ASM_KEEP(actor);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(context);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(sprite);   /* MATCH pin: retail basic-block layout depends on it */

    if (((S_80170E5C_1 *)status)->unk_25 == 0) {
        func_800AA79C(actor, context, sprite, status);
        if (((S_80170E5C_2 *)sprite)->unk_2C == D_80174538) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174530;
        func_80047784(sprite,
            D_80174530[((D_80083228 + ((S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80170E5C_1 *)status)->unk_1C & 0x200) {
        if (((S_80170E5C_2 *)sprite)->unk_2C == D_80174538) {
            ((S_80170E5C_0 *)actor)->unk_9A = 0xD;
            ((S_80170E5C_0 *)actor)->unk_9B = 1;
            ((S_80170E5C_0 *)actor)->unk_8C = 0;
            ((S_80170E5C_1 *)status)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_80174530)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_80170E5C_1 *)status)->unk_1C & 0x100) {
            func_800AA258(actor, context, sprite, status);
            return;
        }

        {
            s32 next_state;
            s32 actor_state;

            actor_state = ((S_80170E5C_0 *)actor)->unk_9A;
            next_state = 0xE;

            if (actor_state != next_state) {
                anim_table = D_80174520;
                if (((S_80170E5C_2 *)sprite)->unk_2C != anim_table) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                    func_80047784(sprite,
                        anim_table[((D_80083228 + ((S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80170E5C_0 *)actor)->unk_9A = next_state;
            }
        }

        ((S_80170E5C_0 *)actor)->unk_98 &= 0xFFF3;
        if (((S_80170E5C_1 *)status)->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80174548)) {
                return;
            }
        }

        if (((S_80170E5C_1 *)status)->unk_1C & 0x80000) {
            func_800AA888(actor, context, sprite, status);
            func_801737DC(actor, context, sprite, status);
            return;
        }

        if ((s16)func_800A1C58(status) != 0) {
            func_800AAB10(actor, context, sprite, status);
        }
    }

    tile_record = func_8009FB34(((S_80170E5C_2 *)sprite)->unk_24.at00.v, ((S_80170E5C_2 *)sprite)->unk_24.at01.v);
    ((S_80170E5C_2 *)sprite)->unk_26 = tile_record;

    if (((S_80170E5C_1 *)status)->unk_6D > 0) {
        if (((S_80170E5C_1 *)status)->unk_1C & 0x20) {
            goto special_cleanup;
        }
        if (((S_80170E5C_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(((S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(status,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80173E48(actor, context, sprite, 0) == 0) {
                return;
            }
            ((S_80170E5C_1 *)status)->unk_46 |= 0x4000;
            if (!(((S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

        {
            static void *const action_labels[] = {
                &&aaf_cleanup, &&aaf_cleanup, &&aaf_cleanup,
                &&movement_case,
                &&coords_case, &&coords_case, &&coords_case,
                &&handler_case, &&handler_case,
                &&ordinary_cleanup, &&ordinary_cleanup,
                &&special_cleanup,
            };
            u32 action_index = (((S_80170E5C_1 *)status)->unk_46 & 0x3FFF) - 1;

            if (action_index >= 12) {
                goto ordinary_cleanup;
            }
            (void)action_labels;
            goto *D_80170808[action_index];
        }

handler_case:
        if ((s16)func_80171E10(actor, context, sprite, status) == 0) {
            func_80171FD4(actor, context, sprite, status);
        }
        return;

movement_case:
        if (((S_80170E5C_1 *)status)->unk_1C & 0x400) {
            register s32 movement_flags ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

            movement_flags = ((S_80170E5C_1 *)status)->unk_14;

            if (movement_flags >= 0) {
                ((S_80170E5C_1 *)status)->unk_14 = movement_flags | 0x80000000;
                ((S_80170E5C_1 *)status)->unk_2A.u += (func_800A6D30(actor) & 7) << 9;
            }
        }
        if ((s16)func_801720EC(actor, context, sprite, status) != 0) {
            return;
        }
        func_8017236C(actor, context, sprite, status);
        return;

coords_case:
        {
            u8 *origin = D_80082E80;
            void *active_actor;
            s32 direction;

            direction = func_800A0818(
                ((S_80170E5C_2 *)sprite)->unk_24.at00.v, ((S_80170E5C_2 *)sprite)->unk_24.at01.v,
                ((S_80170E5C_4 *)origin)->unk_24, ((S_80170E5C_4 *)origin)->unk_25,
                &direction_aux);
            active_actor = D_800814A8;
            ((S_80170E5C_1 *)status)->unk_2A.s = direction;
            if (((S_80170E5C_5 *)active_actor)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
        }

special_cleanup:
        func_800A9A0C(status);
        return;

aaf_cleanup:
        func_800AAF00(actor, context, sprite, D_80174560, func_80170E5C);
        return;

ordinary_cleanup:
        func_80171420(actor, context, sprite, status);
        return;
    } else if (!(((S_80170E5C_1 *)status)->unk_1C & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(((S_80170E5C_1 *)status)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(((S_80170E5C_2 *)sprite)->unk_24.at00.v,
                        ((S_80170E5C_2 *)sprite)->unk_24.at01.v, ((S_80170E5C_4 *)origin)->unk_24,
                        ((S_80170E5C_4 *)origin)->unk_25) != 0) {
                    ((S_80170E5C_1 *)status)->unk_2A.s = func_800A0818(
                        ((S_80170E5C_2 *)sprite)->unk_24.at00.v, ((S_80170E5C_2 *)sprite)->unk_24.at01.v,
                        ((S_80170E5C_4 *)origin)->unk_24, ((S_80170E5C_4 *)origin)->unk_25,
                        &direction_aux);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80170E5C_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174520;
    if (((S_80170E5C_2 *)sprite)->unk_2C == anim_table) {
        return;
    }

update_table:
    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
    func_80047784(sprite,
        *(u8 *)((u32)(((D_80083228 + ((S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7) +
            (u32)anim_table),
        0);
}
