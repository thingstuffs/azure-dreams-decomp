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

extern void func_801718A4() __attribute__((noreturn));
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

void func_80171514(void *arg0_, void *arg1_, void *arg2_, void *arg3_)
{
    static void *const keepalive[] = {
        &&case_stop, &&case_callback, &&case_action, &&case_default
    };
    void *obj = arg0_;
    void *motion = arg1_;
    void *part = arg2_;
    void *state = arg3_;
#define arg0 obj
#define arg1 motion
#define arg2 part
#define arg3 state
    u32 entry_status = D_80083462;
    s32 flags;
    s32 result;
    s32 kind;
    s32 jump_index;
    s32 entry_index;
    u8 *entry_base;
    u8 *entry;
    u8 *animation;
    s16 distance;

    if (entry_status & 0x1000) {
        (*(u8 *)((u8 *)arg0 + (0x9A))) = 14;
        func_801719C0(arg0);
        return;
    }
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    if (((S_80171514_0 *)arg3)->unk_1C & 0x200) {
        if (((S_80171514_1 *)arg2)->unk_2C == D_80173EC4) {
            (*(u8 *)((u8 *)arg0 + (0x9A))) = 13;
            (*(u8 *)((u8 *)arg0 + (0x9B))) = 1;
            (*(u32 *)((u8 *)arg0 + (0x8C))) = 0;
            ((S_80171514_0 *)arg3)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80173E94) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((S_80171514_0 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

           /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        if ((*(u8 *)((u8 *)arg0 + (0x9A))) != 14) {
            (*(u8 *)((u8 *)arg0 + (0x9A))) = 14;
        }
        if (((S_80171514_1 *)arg2)->unk_2C != D_80173E8C) {
            (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80173E8C;
            func_80047784(
                arg2,
                D_80173E8C[((D_80083228 + ((S_80171514_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_80171514_1 *)arg2)->unk_05 = 1;
            (*(s16 *)((u8 *)arg0 + (0xA2))) = 0;
            (*(s16 *)((u8 *)arg0 + (0x9E))) = 0;
        }

        ((S_80171514_0 *)arg3)->unk_1C |= 0x40000;
        (*(u16 *)((u8 *)arg0 + (0x98))) &= 0xFFF7;

        if (((S_80171514_0 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80173EE4) != 0) {
                return;
            }
        }

        if (((S_80171514_0 *)arg3)->unk_1C & 0x80000) {
            u16 old_value;
            u16 amount;

            func_800AA888(arg0, arg1, arg2, arg3);
            old_value = (*(u16 *)((u8 *)arg0 + (0x92)));
            amount = (*(u16 *)((u8 *)arg0 + (0xA2)));
            (*(s16 *)((u8 *)arg0 + (0xA2))) = 0;
            (*(s16 *)((u8 *)arg0 + (0x9E))) = 0;
            (*(u16 *)((u8 *)arg0 + (0x92))) = old_value - amount;
            func_801736B8(arg0, arg1, arg2, arg3);
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(((S_80171514_1 *)arg2)->unk_24.at00.v, ((S_80171514_1 *)arg2)->unk_24.at01.v);
    ((S_80171514_1 *)arg2)->unk_26 = result;

    if (((S_80171514_0 *)arg3)->unk_6D > 0) {
        if (((S_80171514_0 *)arg3)->unk_1C & 0x20) {
            goto case_stop;
        }

        if (((S_80171514_1 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto case_default;
        }

        if ((((S_80171514_0 *)arg3)->unk_46 & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        arg3, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }

            if (D_80013714 & 8) {
                void *tail_arg;
                u8 tail_flags;

                func_80173D6C(arg0, arg1, arg2);
                tail_flags = ((S_80171514_0 *)arg3)->unk_71;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                tail_arg = arg3;
                ASM_KEEP(tail_arg);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                tail_flags &= 0x7F;
                ((S_80171514_0 *)arg3)->unk_71 = tail_flags;
                func_801718A4(tail_arg);
            }

            if ((s16)func_80172330(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            ((S_80171514_0 *)arg3)->unk_46 |= 0x4000;
            if ((((S_80171514_0 *)arg3)->unk_46 & 0x8000) == 0) {
                goto case_default;
            }
        }

        kind = ((S_80171514_0 *)arg3)->unk_46 & 0x3FFF;
        jump_index = kind - 1;
        if ((u32)jump_index >= 12U) {
            goto case_default;
        }
        (void)keepalive;
        goto *D_80170808[jump_index];

case_stop:
        func_800A9A0C(arg3);
        return;

case_callback:
        (*(void * volatile *)((u8 *)arg0 + (0x8C))) = &D_80171514;
        func_800A9A0C(arg3);
        ((S_80171514_0 *)arg3)->unk_46 &= 0x7FFF;
        return;

case_action:
        func_800AAF00(arg0, arg1, arg2, 0, &D_80171514);
        return;

case_default:
        func_80171BE0(arg0, arg1, arg2, arg3);
        return;
    }

    flags = ((S_80171514_0 *)arg3)->unk_1C;
    if ((flags & 0x2000) == 0) {
        entry_index = (s8)result;
        if (entry_index >= 0) {
            entry_base = D_800E2970;
            entry = entry_index * 20 + entry_base;
            if (((S_80171514_3 *)entry)->unk_0C & 2) {
                return;
            }
        }
        if ((flags & 0x430) == 0) {
            animation = D_80082E80;
            if ((s16)func_8009FD7C(
                    ((S_80171514_1 *)arg2)->unk_24.at00.v, ((S_80171514_1 *)arg2)->unk_24.at01.v,
                    animation[0x24], animation[0x25]) != 0) {
                result = func_800A0818(
                    ((S_80171514_1 *)arg2)->unk_24.at00.v, ((S_80171514_1 *)arg2)->unk_24.at01.v,
                    animation[0x24], animation[0x25], &distance);
                ((S_80171514_0 *)arg3)->unk_2A = result;
            }
        }
    }
}
#undef arg0
#undef arg1
#undef arg2
#undef arg3

/* MECHANISM: Natural entry-status initialization plus long-lived pinned arguments yields the retail 0x38 frame/save order.
   A volatile callback-pointer lvalue preserves retail's sw; jal; nop sequence and removes the displacement cascade.
   Separate entry-base/result locals keep the table base in v0 and coalesce the indexed address into v1.
   A scoped a0 tail argument, value barrier, and scheduler fence retain the s0 delay-store base with the move in the load slot. */
