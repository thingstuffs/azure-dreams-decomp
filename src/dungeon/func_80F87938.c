#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80171138_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_80171138_0;   /* arg0 in func_80171138 */

typedef struct S_80171138_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80171138_1;   /* arg3 in func_80171138 */

typedef struct S_80171138_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171138_2;   /* arg2 in func_80171138 */


typedef struct S_80171138_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171138_4;   /* coord_origin in func_80171138 */

typedef struct S_80171138_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171138_5;   /* player in func_80171138 */

typedef struct S_80171138_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171138_6;   /* origin in func_80171138 */



typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(u8, u8, u8, u8, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171670(void *, void *);
extern void func_8017182C(void *, void *, void *, void *);
extern s32 func_80171F74(void *, void *, void *, void *);
extern void func_80172138(void *, void *, void *, void *);
extern s32 func_80172258(void *, void *, void *, s32);
extern void func_80173D38(void *, void *, void *, void *);
extern void func_801740F4(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *const D_80170808[];
extern u8 D_80171138[];
extern u8 D_80174AD4[];
extern u8 D_80174ADC[];
extern u8 D_80174AEC[];
extern u8 D_80174AF4[];
extern u8 D_80174AFC[];

/* Updates actor behavior, animation, and facing from its status and dungeon state. */
void func_80171138(void *actor_in, void *context_in, void *sprite_in, void *stats_in)
{
    static void *const action_labels[] = {
        &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7, &&case_8,
        &&case_9, &&case_10, &&case_11, &&case_12,
    };
    void *actor;
    void *context;
    void *sprite;
    void *stats;
    s32 angle_aux;
    s32 status_flags;
    s8 tile_index;
    u16 action_state;
    u32 dungeon_flags = D_80083462;

    actor = actor_in;
    context = context_in;
    sprite = sprite_in;
    stats = stats_in;

    if (dungeon_flags & 0x1000) {
        ((S_80171138_0 *)actor)->unk_9A = 0xE;
        func_80171670(actor_in, context_in);
        return;
    }

    if (((S_80171138_1 *)stats)->unk_25 == 0) {
        func_800AA79C(actor, context, sprite, stats);
        if (((S_80171138_2 *)sprite)->unk_2C == D_80174AFC) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AF4;
        func_80047784(sprite,
            D_80174AF4[((D_80083228 + ((S_80171138_1 *)stats)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80171138_1 *)stats)->unk_1C & 0x200) {
        if (((S_80171138_2 *)sprite)->unk_2C == D_80174AFC) {
            ((S_80171138_0 *)actor)->unk_9A = 0xD;
            ((S_80171138_0 *)actor)->unk_9B = 1;
            ((S_80171138_0 *)actor)->unk_8C = 0;
            ((S_80171138_1 *)stats)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_80174AF4) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_80171138_1 *)stats)->unk_1C & 0x100) {
            func_800AA258(actor, context, sprite, stats);
            return;
        }

        if (((S_80171138_0 *)actor)->unk_9A != 0xE) {
            ((S_80171138_0 *)actor)->unk_9A = 0xE;
        }

        if (((S_80171138_2 *)sprite)->unk_2C != D_80174AD4) {
            ((S_80171138_0 *)actor)->unk_A0 = 0;
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AD4;
            func_80047784(sprite,
                D_80174AD4[((D_80083228 + ((S_80171138_1 *)stats)->unk_2A + 0x100) >> 9) & 7],
                ((S_80171138_0 *)actor)->unk_A0);
        }

        ((S_80171138_1 *)stats)->unk_1C |= 0x40000;
        ((S_80171138_0 *)actor)->unk_98 &= 0xFFF7;

        if (((S_80171138_1 *)stats)->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80174ADC) != 0) {
                return;
            }
        }

        if (((S_80171138_1 *)stats)->unk_1C & 0x80000) {
            func_800AA888(actor, context, sprite, stats);
            ((S_80171138_0 *)actor)->unk_A0 = 0;
            func_80173D38(actor, context, sprite, stats);
            return;
        }

        if ((func_800A1C58(stats) << 16) != 0) {
            func_800AAB10(actor, context, sprite, stats);
        }
    }

    tile_index = func_8009FB34(((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v);
    ((S_80171138_2 *)sprite)->unk_26 = tile_index;

    if (((S_80171138_1 *)stats)->unk_6D > 0) {
        if (((S_80171138_1 *)stats)->unk_1C & 0x20) {
            goto case_12;
        }
        if (((S_80171138_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto default_case;
        }
        action_state = ((S_80171138_1 *)stats)->unk_46;
        if (!(action_state & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(stats,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172258(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = ((S_80171138_1 *)stats)->unk_46 | 0x4000;
            ((S_80171138_1 *)stats)->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                goto default_case;
            }
        }

        {
            u32 action_index = (((S_80171138_1 *)stats)->unk_46 & 0x3FFF) - 1;

            if (action_index >= 12) {
                goto default_case;
            }
            (void)action_labels;
            goto *D_80170808[action_index];
        }

case_8:
        func_801740F4(actor, context, sprite, stats);
        return;

case_9:
        if ((func_80171F74(actor, context, sprite, stats) << 16) != 0) {
            return;
        }
        func_80172138(actor, context, sprite, stats);
        return;

case_5:
case_6:
case_7:
        {
            u8 *target_pos = D_80082E80;
            void *player;
            s16 facing_angle;

            facing_angle = func_800A0818(
                ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                ((S_80171138_4 *)target_pos)->unk_24, ((S_80171138_4 *)target_pos)->unk_25,
                &angle_aux);
            player = D_800814A8;
            ((S_80171138_1 *)stats)->unk_2A = facing_angle;
            if (((S_80171138_5 *)player)->unk_9A == 0x11) {
                goto call_aaf;
            }
        }

case_12:
        func_800A9A0C(stats);
        return;

case_1:
case_2:
case_3:
call_aaf:
        func_800AAF00(actor, context, sprite, D_80174AEC, D_80171138);
        return;

case_4:
case_10:
case_11:
default_case:
        func_8017182C(actor, context, sprite, stats);
        return;
    }

    status_flags = ((S_80171138_1 *)stats)->unk_1C;
    if (status_flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (((DungeonRecord *)D_800E2970)[tile_index].flags & 2) {
            return;
        }
    }
    if (status_flags & 0x430) {
        return;
    }

    {
        u8 *target_pos = D_80082E80;

        if ((func_8009FD7C(
                ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                ((S_80171138_6 *)target_pos)->unk_24, ((S_80171138_6 *)target_pos)->unk_25) << 16) != 0) {
            ((S_80171138_1 *)stats)->unk_2A = func_800A0818(
                ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                ((S_80171138_6 *)target_pos)->unk_24, ((S_80171138_6 *)target_pos)->unk_25, &angle_aux);
        }
    }
    return;
}
