#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s32 func_800A0818(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_80171388(void *);
extern void func_801715CC(void *, void *, void *, void *);
extern s32 func_80171D80(void *, void *, void *, void *);
extern void func_80171F90(void *, void *, void *, void *);
extern s32 func_801720E0(void *, void *, void *, s32);
extern void func_80173478(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170E68[];
extern u8 D_8017386C[];
extern u8 D_80173874[];
extern u8 D_8017389C[];

typedef struct S_80170E68_3 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E68_3;   /* player in func_80170E68 */

typedef struct S_80170E68_4 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80170E68_4;   /* entry in func_80170E68 */

/* Dispatch actor behavior and update its facing animation from dungeon state. */
void func_80170E68(Rec_func_800A9E70_arg0 *actor, void *context, void *sprite, Rec_D_800E3D7C *state)
{
    static void *const case_labels[] = {
        &&case_9, &&case_8, &&case_5_7, &&case_1_3,
        &&case_12, &&case_default
    };
    volatile u16 *dungeon_status;
    s32 initial_flags;
    s32 flags;
    s32 result;
    s32 action_kind;
    s32 action_index;
    s32 entry_index;
    u8 *entry_base;
    u8 *entry;
    u8 *player_sprite;
    S_80170E68_3 *player;
    volatile s16 distance;
    u16 status_flags;

    dungeon_status = (volatile u16 *)&D_80083460;
    if (dungeon_status[1] & 0x1000) {
        actor->unk_9A.as_u8 = 14;
        func_80171388(actor);
        return;
    }

    if (state->unk_24.at01_u8.v == 0) {
        result = -0x201;
        func_800AA79C(actor, context, sprite, state);
        (void)result;
        goto tail_animation;
    }

    initial_flags = state->unk_1C.as_u32;
    state->unk_1C.as_u32 = initial_flags & -0x201;

    status_flags = dungeon_status[1];

    if ((status_flags & 0x2000) == 0) {
        if (initial_flags & 0x100) {
            func_800AA258(actor, context, sprite, state);
            return;
        }

        if (actor->unk_9A.as_u8 != 14) {
            if (*(u8 **)((u8 *)sprite + 0x2C) != D_8017386C) {
                *(u8 **)((u8 *)sprite + 0x2C) = D_8017386C;
                func_80047784(
                    sprite,
                    D_8017386C[((D_80083228 + state->unk_2A.as_s16 + 0x100) >> 9) & 7],
                    0);
            }
            actor->unk_9A.as_u8 = 14;
        }

        actor->unk_98 &= 0xFFF3;

        if (state->unk_64.as_s16 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80173874) != 0) {
                return;
            }
        }

        if (state->unk_1C.as_u32 & 0x80000) {
            func_800AA888(actor, context, sprite, state);
            func_80173478(actor, context, sprite, state);
            return;
        }

        if ((s16)func_800A1C58(state) != 0) {
            func_800AAB10(actor, context, sprite, state);
        }
    }

    result = func_8009FB34(*(u8 *)((u8 *)sprite + 0x24), *(u8 *)((u8 *)sprite + 0x25));
    *(u8 *)((u8 *)sprite + 0x26) = result;

    if (state->unk_6D.as_s8 > 0) {
        if (state->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }

        if (*(u16 *)((u8 *)sprite + 0x24) == *(u16 *)&D_80082EA4) {
            goto case_default;
        }

        if ((state->unk_44.at02_u16.v & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(state, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }

            if ((s16)func_801720E0(actor, context, sprite, 0) == 0) {
                return;
            }
            state->unk_44.at02_u16.v |= 0x4000;
            if ((state->unk_44.at02_u16.v & 0x8000) == 0) {
                goto case_default;
            }
        }

        action_kind = state->unk_44.at02_u16.v & 0x3FFF;
        action_index = action_kind - 1;
        if ((u32)action_index >= 12U) {
            goto case_default;
        }
        (void)case_labels;
        goto *D_80170808[action_index];

case_9:
        actor->unk_98 |= 0x8000;

case_8:
        if ((state->unk_1C.as_u32 & 0x2000) &&
            ((state->unk_44.at02_u16.v & 0x3FFF) == 8)) {
            actor->unk_98 &= 0x7FFF;
        }
        if ((s16)func_80171D80(actor, context, sprite, state) != 0) {
            return;
        }
        func_80171F90(actor, context, sprite, state);
        return;

case_5_7:
        result = func_800A0818(
            *(u8 *)((u8 *)sprite + 0x24), *(u8 *)((u8 *)sprite + 0x25),
            D_80082E80[0x24], D_80082E80[0x25], (s16 *)&distance);
        player = D_800814A8;
        state->unk_2A.as_s16 = result;
        if (player->unk_9A == 0x11) {
            goto case_1_3_common;
        }

case_12:
        func_800A9A0C(state);
        return;

case_1_3:
case_1_3_common:
        func_800AAF00(actor, context, sprite, D_8017389C, D_80170E68);
        return;

case_default:
        func_801715CC(actor, context, sprite, state);
        return;
    }

    flags = state->unk_1C.as_u32;
    if ((flags & 0x2000) == 0) {
        entry_index = (s8)result;
        if (entry_index >= 0) {
            entry_base = (u8 *)D_800E2970;
            entry = entry_base + entry_index * 20;
            if (((S_80170E68_4 *)entry)->unk_0C & 2) {
                goto tail_checks;
            }
        }
        if ((flags & 0x430) == 0) {
            player_sprite = D_80082E80;
            if ((s16)func_8009FD7C(
                    *(u8 *)((u8 *)sprite + 0x24), *(u8 *)((u8 *)sprite + 0x25),
                    player_sprite[0x24], player_sprite[0x25]) != 0) {
                result = func_800A0818(
                    *(u8 *)((u8 *)sprite + 0x24), *(u8 *)((u8 *)sprite + 0x25),
                    player_sprite[0x24], player_sprite[0x25], (s16 *)&distance);
                state->unk_2A.as_s16 = result;
            }
        }
    }

tail_checks:
    if (D_80083462 & 0x2000) {
        return;
    }
    if (*(u16 *)((u8 *)sprite + 0x14) & 0x40) {
        return;
    }
tail_animation:
    if (*(u8 * volatile *)((u8 *)sprite + 0x2C) != D_8017386C) {
        *(u8 **)((u8 *)sprite + 0x2C) = D_8017386C;
        func_80047784(
            sprite,
            D_8017386C[((D_80083228 + state->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
    }
}

