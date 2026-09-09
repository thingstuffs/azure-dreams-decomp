#include "common.h"
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
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, s32, void *);

extern void func_801719C0(void *);
extern void func_80171BE0(void *, void *, void *, void *);
extern s32 func_80172330(void *, void *, void *, s32);
extern void func_801736B8(void *, void *, void *, void *);
extern void func_80173D6C(void *, void *, void *);

extern u16 D_80013714;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80171514;
extern u8 D_80173E8C[8];
extern u8 D_80173E94[];
extern u8 D_80173EC4[];
extern u8 D_80173EE4[];


typedef struct S_80171514_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80171514_0;   /* arg3 in func_80171514 */

typedef struct S_80171514_1 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80171514_1;   /* arg2 in func_80171514 */


typedef struct S_80171514_3 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80171514_3;   /* entry in func_80171514 */

/* Updates object animation, dispatches its action, and adjusts its facing. */
void func_80171514(void *obj, void *motion, void *part, void *state)
{
    static void *const dispatch_labels[] = {
        &&case_stop, &&case_callback, &&case_action, &&case_default
    };
    u32 entry_status = D_80083462;
    s32 state_flags;
    s32 query_result;
    s32 action_kind;
    s32 jump_index;
    s32 entry_index;
    u8 *entry_base;
    u8 *entry;
    u8 *target_part;
    s16 distance;
    void *callback_state;

    if (entry_status & 0x1000) {
        (*(u8 *)((u8 *)obj + (0x9A))) = 14;
        func_801719C0(obj);
        return;
    }


    if (((S_80171514_0 *)state)->unk_1C & 0x200) {
        if (((S_80171514_1 *)part)->unk_2C == D_80173EC4) {
            (*(u8 *)((u8 *)obj + (0x9A))) = 13;
            (*(u8 *)((u8 *)obj + (0x9B))) = 1;
            (*(u32 *)((u8 *)obj + (0x8C))) = 0;
            ((S_80171514_0 *)state)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(obj, motion, part, D_80173E94) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((S_80171514_0 *)state)->unk_1C & 0x100) {
            func_800AA258(obj, motion, part, state);
            return;
        }

        if ((*(u8 *)((u8 *)obj + (0x9A))) != 14) {
            (*(u8 *)((u8 *)obj + (0x9A))) = 14;
        }
        if (((S_80171514_1 *)part)->unk_2C != D_80173E8C) {
            (*(u8 * *)((u8 *)part + (0x2C))) = D_80173E8C;
            func_80047784(
                part,
                D_80173E8C[((D_80083228 + ((S_80171514_0 *)state)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_80171514_1 *)part)->unk_05 = 1;
            (*(s16 *)((u8 *)obj + (0xA2))) = 0;
            (*(s16 *)((u8 *)obj + (0x9E))) = 0;
        }

        ((S_80171514_0 *)state)->unk_1C |= 0x40000;
        (*(u16 *)((u8 *)obj + (0x98))) &= 0xFFF7;

        if (((S_80171514_0 *)state)->unk_64 != 0) {
            if (func_800AA6B4(obj, motion, part, D_80173EE4) != 0) {
                return;
            }
        }

        if (((S_80171514_0 *)state)->unk_1C & 0x80000) {
            u16 previous_amount;
            u16 pending_amount;

            func_800AA888(obj, motion, part, state);
            previous_amount = (*(u16 *)((u8 *)obj + (0x92)));
            pending_amount = (*(u16 *)((u8 *)obj + (0xA2)));
            (*(s16 *)((u8 *)obj + (0xA2))) = 0;
            (*(s16 *)((u8 *)obj + (0x9E))) = 0;
            (*(u16 *)((u8 *)obj + (0x92))) = previous_amount - pending_amount;
            func_801736B8(obj, motion, part, state);
            return;
        }

        if ((s16)func_800A1C58(state) != 0) {
            func_800AAB10(obj, motion, part, state);
        }
    }

    query_result = func_8009FB34(((S_80171514_1 *)part)->unk_24.at00.v, ((S_80171514_1 *)part)->unk_24.at01.v);
    ((S_80171514_1 *)part)->unk_26 = query_result;

    if (((S_80171514_0 *)state)->unk_6D > 0) {
        if (((S_80171514_0 *)state)->unk_1C & 0x20) {
            goto case_stop;
        }

        if (((S_80171514_1 *)part)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto case_default;
        }

        if ((((S_80171514_0 *)state)->unk_46 & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        state, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }

            if (D_80013714 & 8) {
                u8 callback_flags;

                func_80173D6C(obj, motion, part);
                callback_flags = ((S_80171514_0 *)state)->unk_71;
                callback_state = state;
                callback_flags &= 0x7F;
                ((S_80171514_0 *)state)->unk_71 = callback_flags;
                goto case_callback_tail;
            }

            if ((s16)func_80172330(obj, motion, part, 0) == 0) {
                return;
            }
            ((S_80171514_0 *)state)->unk_46 |= 0x4000;
            if ((((S_80171514_0 *)state)->unk_46 & 0x8000) == 0) {
                goto case_default;
            }
        }

        action_kind = ((S_80171514_0 *)state)->unk_46 & 0x3FFF;
        jump_index = action_kind - 1;
        if ((u32)jump_index >= 12U) {
            goto case_default;
        }
        (void)dispatch_labels;
        goto *D_80170808[jump_index];

case_stop:
        func_800A9A0C(state);
        return;

case_callback:
        callback_state = state;
        (*(void * volatile *)((u8 *)obj + (0x8C))) = &D_80171514;
case_callback_tail:
        func_800A9A0C(callback_state);
        ((S_80171514_0 *)state)->unk_46 &= 0x7FFF;
        return;

case_action:
        func_800AAF00(obj, motion, part, 0, &D_80171514);
        return;

case_default:
        func_80171BE0(obj, motion, part, state);
        return;
    }

    state_flags = ((S_80171514_0 *)state)->unk_1C;
    if ((state_flags & 0x2000) == 0) {
        entry_index = (s8)query_result;
        if (entry_index >= 0) {
            entry_base = D_800E2970;
            entry = entry_index * 20 + entry_base;
            if (((S_80171514_3 *)entry)->unk_0C & 2) {
                return;
            }
        }
        if ((state_flags & 0x430) == 0) {
            target_part = D_80082E80;
            if ((s16)func_8009FD7C(
                    ((S_80171514_1 *)part)->unk_24.at00.v, ((S_80171514_1 *)part)->unk_24.at01.v,
                    target_part[0x24], target_part[0x25]) != 0) {
                query_result = func_800A0818(
                    ((S_80171514_1 *)part)->unk_24.at00.v, ((S_80171514_1 *)part)->unk_24.at01.v,
                    target_part[0x24], target_part[0x25], &distance);
                ((S_80171514_0 *)state)->unk_2A = query_result;
            }
        }
    }
}
