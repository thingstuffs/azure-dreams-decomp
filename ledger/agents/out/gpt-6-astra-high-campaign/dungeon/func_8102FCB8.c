#include "common.h"
#include "records/Rec_D_800814A8.h"


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_8003DB94(void *, void *, s32);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void *func_8003FC64(s32);
extern void func_80047784(void *, s32, s32);
extern void func_800478B8(void *);
extern s32 rand(void);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
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
extern void func_80170DD0(void *, void *, void *);
extern void func_80171C3C(void *, void *, void *, void *);
extern void func_80171E80(void *, void *, void *, void *);
extern s32 func_8017263C(void *, void *, void *, void *);
extern void func_80172800(void *, void *, void *, void *);
extern s32 func_80172918(void *, void *, void *, s32);
extern void func_8017412C(void *, void *, void *, void *);
extern void func_801756E0(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800DEA68[];
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170A0C[];
extern u8 D_801714B8;
extern u8 D_8017609C[];
extern u8 D_801760A4[];
extern u8 D_801760AC[];
extern u8 D_801760DC[];
extern u8 D_801760E4[];
extern u8 D_801760EC[];


typedef struct S_801714B8_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801714B8_0_pre;   /* the 0x14 bytes before arg0 in func_801714B8, addressed as arg0[-1] */

typedef struct S_801714B8_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s16 unk_A0;
} S_801714B8_0;   /* arg0 in func_801714B8 */

typedef struct S_801714B8_1 {
    u8 pad_00[0x1C];
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
} S_801714B8_1;   /* arg3 in func_801714B8 */

typedef struct S_801714B8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801714B8_2;   /* arg2 in func_801714B8 */


typedef struct S_801714B8_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801714B8_4;   /* origin in func_801714B8 */

typedef struct S_801714B8_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801714B8_5;   /* player in func_801714B8 */

typedef struct S_801714B8_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801714B8_6;   /* object in func_801714B8 */

typedef struct S_801714B8_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u8 pad_1E[0xA];
    void * unk_28;
} S_801714B8_7;   /* object_data in func_801714B8 */

typedef struct S_801714B8_8 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801714B8_8;   /* owner in func_801714B8 */

typedef struct S_801714B8_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_801714B8_9;   /* part in func_801714B8 */

/* Updates actor behavior, facing, and timed animation effects in the dungeon. */
void func_801714B8(void *actor_arg, void *context_arg, void *sprite_arg, void *stats_arg)
{
    register void *actor ASM_REG("$19");
    void *context;
    register void *sprite ASM_REG("$17");
    register void *stats ASM_REG("$18");
    s32 room_id;
    s32 distance;
    u16 spawn_offset[3];
    u32 initial_flags = D_80083462;

    actor = actor_arg;
    context = context_arg;
    sprite = sprite_arg;
    stats = stats_arg;

    if (initial_flags & 0x1000) {
        ((S_801714B8_0 *)actor)->unk_9A = 0xE;
        func_80171C3C(actor, context, sprite, stats);
        return;
    }

    ASM_KEEP(actor);
    ASM_KEEP(context);
    ASM_KEEP(sprite);
    ASM_KEEP(stats);

    if (((S_801714B8_1 *)stats)->unk_25 == 0) {
        func_800AA79C(actor, context, sprite, stats);
        if (((S_801714B8_2 *)sprite)->unk_2C != D_801760EC) {
            u8 *state_table = D_801760E4;

            (*(void * *)((u8 *)sprite + (0x2C))) = state_table;
            func_80047784(sprite,
                state_table[((D_80083228 + ((S_801714B8_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((S_801714B8_1 *)stats)->unk_1C & 0x200) {
        if (((S_801714B8_2 *)sprite)->unk_2C == D_801760EC) {
            ((S_801714B8_0 *)actor)->unk_9A = 0xD;
            ((S_801714B8_0 *)actor)->unk_9B = 1;
            ((S_801714B8_0 *)actor)->unk_8C = 0;
            ((S_801714B8_1 *)stats)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_801760E4)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_801714B8_1 *)stats)->unk_1C & 0x100) {
            func_800AA258(actor, context, sprite, stats);
            return;
        }

        
        if (((S_801714B8_0 *)actor)->unk_9A != 0xE) {
            u8 state = 0xE;
            u8 *state_table = D_8017609C;

            if (((S_801714B8_2 *)sprite)->unk_2C != state_table) {
                (*(void * *)((u8 *)sprite + (0x2C))) = state_table;
                func_80047784(sprite,
                    state_table[((D_80083228 + ((S_801714B8_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                    0);
            }
            ((S_801714B8_0 *)actor)->unk_9E.s = 0;
            ((S_801714B8_0 *)actor)->unk_A0 = (rand() & 0x1F) + 0xF;
            ((S_801714B8_0 *)actor)->unk_9A = state;
        }

        ((S_801714B8_0 *)actor)->unk_98 &= 0xFFF3;
        if (((S_801714B8_1 *)stats)->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_801760AC)) {
                return;
            }
        }

        if (((S_801714B8_1 *)stats)->unk_1C & 0x80000) {
            func_800AA888(actor, context, sprite, stats);
            func_8017412C(actor, context, sprite, stats);
            return;
        }

        if ((s16)func_800A1C58(stats) != 0) {
            func_800AAB10(actor, context, sprite, stats);
        }
    }

    room_id = func_8009FB34(((S_801714B8_2 *)sprite)->unk_24.at00.v, ((S_801714B8_2 *)sprite)->unk_24.at01.v);
    ((S_801714B8_2 *)sprite)->unk_26 = room_id;

    if (((S_801714B8_1 *)stats)->unk_6D > 0) {
        if (((S_801714B8_1 *)stats)->unk_1C & 0x20) {
            goto special_cleanup;
        }
        if (((S_801714B8_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(((S_801714B8_1 *)stats)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(stats,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172918(actor, context, sprite, 0) == 0) {
                return;
            }
            ((S_801714B8_1 *)stats)->unk_46 |= 0x4000;
            if (!(((S_801714B8_1 *)stats)->unk_46 & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

#ifdef __mips__
        {
            static void *volatile dispatch_labels[] = {
                &&aaf_cleanup, &&aaf_cleanup, &&aaf_cleanup,
                &&ordinary_cleanup,
                &&coords_case, &&coords_case, &&coords_case,
                &&handler_case, &&handler2_case,
                &&ordinary_cleanup, &&ordinary_cleanup,
                &&special_cleanup,
            };
            s32 dispatch_index;

            dispatch_index = (((S_801714B8_1 *)stats)->unk_46 & 0x3FFF) - 1;
            if ((u32)dispatch_index >= 12) {
                goto ordinary_cleanup;
            }
            goto *D_80170808[dispatch_index];
        }
handler_case:
#else
        switch (((S_801714B8_1 *)stats)->unk_46 & 0x3FFF) {
        case 8:
#endif
            if ((s16)func_8017263C(actor, context, sprite, stats) == 0) {
                func_80172800(actor, context, sprite, stats);
                return;
            }
            return;

#ifdef __mips__
handler2_case:
#else
        case 9:
#endif
            func_801756E0(actor, context, sprite, stats);
            return;

#ifdef __mips__
coords_case:
#else
        case 5:
        case 6:
        case 7:
#endif
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 heading;

            heading = func_800A0818(
                ((S_801714B8_2 *)sprite)->unk_24.at00.v, ((S_801714B8_2 *)sprite)->unk_24.at01.v,
                ((S_801714B8_4 *)origin)->unk_24, ((S_801714B8_4 *)origin)->unk_25,
                &distance);
            player = D_800814A8;
            ((S_801714B8_1 *)stats)->unk_2A.s = heading;
            if (((S_801714B8_5 *)player)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
            goto special_cleanup;
        }
#ifndef __mips__
        case 1:
        case 2:
        case 3:
            goto aaf_cleanup;
        case 12:
            goto special_cleanup;
        default:
            goto ordinary_cleanup;
        }
#endif

special_cleanup:
        func_800A9A0C(stats);
        return;

aaf_cleanup:
        func_800AAF00(actor, context, sprite, D_801760DC, &D_801714B8);
        return;

ordinary_cleanup:
        func_80171E80(actor, context, sprite, stats);
        return;
    } else if (!(((S_801714B8_1 *)stats)->unk_1C & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) || !(((DungeonRecord *)D_800E2970)[room_index].flags & 2)) {
            if (!(((S_801714B8_1 *)stats)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(
                        ((S_801714B8_2 *)sprite)->unk_24.at00.v, ((S_801714B8_2 *)sprite)->unk_24.at01.v,
                        ((S_801714B8_4 *)origin)->unk_24, ((S_801714B8_4 *)origin)->unk_25) != 0) {
                    ((S_801714B8_1 *)stats)->unk_2A.s = func_800A0818(
                        ((S_801714B8_2 *)sprite)->unk_24.at00.v, ((S_801714B8_2 *)sprite)->unk_24.at01.v,
                        ((S_801714B8_4 *)origin)->unk_24, ((S_801714B8_4 *)origin)->unk_25,
                        &distance);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_801714B8_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    if (((S_801714B8_1 *)stats)->unk_1C & 0x20) {
        return;
    }

    {
        u8 *main_table = D_8017609C;

        if (((S_801714B8_2 *)sprite)->unk_2C != main_table) {
            if (((S_801714B8_2 *)sprite)->unk_2C != D_801760A4) {
                (*(void * *)((u8 *)sprite + (0x2C))) = main_table;
                func_80047784(sprite,
                    main_table[((D_80083228 + ((S_801714B8_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                    0);
                ((S_801714B8_0 *)actor)->unk_9E.s = 0;
                ((S_801714B8_0 *)actor)->unk_A0 = (rand() & 0x1F) + 0xF;
            }
            if (((S_801714B8_2 *)sprite)->unk_2C != main_table) {
                goto final_state_check;
            }
        }

        {
            s16 idle_timer = ((S_801714B8_0 *)actor)->unk_9E.u;

            ((S_801714B8_0 *)actor)->unk_9E.u = idle_timer + 1;
            if (idle_timer >= ((S_801714B8_0 *)actor)->unk_A0) {
                void *object;
                u8 *object_data;

                u8 *alt_table = D_801760A4;

                (*(void * *)((u8 *)sprite + (0x2C))) = alt_table;
                func_80047784(sprite,
                    alt_table[((D_80083228 + ((S_801714B8_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                    0);
                func_800478B8(sprite);

                object = func_8003FC64(0x212);
                if (object != 0) {
                    func_80170DD0(object, actor, context);
                    ((S_801714B8_6 *)object)->unk_10 = D_80170A0C;
                    object_data = (u8 *)object + 0x20;
                    ((S_801714B8_7 *)object_data)->unk_28 = context;
                    ((S_801714B8_7 *)object_data)->unk_1C = ((S_801714B8_1 *)stats)->unk_2A.u;

                    {
                        void *owner = ((S_801714B8_0_pre *)actor)[-1].unk_00;

                        if (func_8003DE58(
                                ((S_801714B8_8 *)owner)->unk_08, owner, spawn_offset, 0xF)) {
                            void *part = ((S_801714B8_6 *)object)->unk_08;

                            ((S_801714B8_9 *)part)->unk_02 += spawn_offset[0];
                            ((S_801714B8_9 *)part)->unk_06 += spawn_offset[1];
                            ((S_801714B8_9 *)part)->unk_0A += spawn_offset[2];
                        }
                    }
                    {
                        void *part = ((S_801714B8_6 *)object)->unk_0C;
                        ((S_801714B8_9 *)part)->unk_14 |= 0x80;
                        func_8003DB94(part, &D_800DEA68, 0);
                    }
                }
            }
        }
    }

final_state_check:
    if (((S_801714B8_2 *)sprite)->unk_2C == D_801760A4 &&
            (((S_801714B8_2 *)sprite)->unk_14 & 0x6000)) {
        u8 *state_table = D_8017609C;

        (*(void * *)((u8 *)sprite + (0x2C))) = state_table;
        func_80047784(sprite,
            state_table[((D_80083228 + ((S_801714B8_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        ((S_801714B8_0 *)actor)->unk_9E.s = 0;
        ((S_801714B8_0 *)actor)->unk_A0 = (rand() & 0x1F) + 0xF;
    }
}
