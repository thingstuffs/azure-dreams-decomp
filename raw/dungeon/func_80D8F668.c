#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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

extern void func_80171320(void) __attribute__((noreturn));
extern void func_80171364(void) __attribute__((noreturn));
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

void func_80170E68(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&case_9, &&case_8, &&case_5_7, &&case_1_3,
        &&case_12, &&case_default
    };
    volatile u16 *status;
    s32 initial_flags;
    s32 flags;
    s32 result;
    s32 kind;
    s32 switch_index;
    s32 tail_index;
    u8 *entry_base;
    u8 *entry;
    u8 *animation;
    void *player;
    volatile s16 distance;
    u16 status_flags;

    status = (volatile u16 *)&D_80083460;
    if (status[1] & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 14;
        func_80171388(arg0);
        func_80171364();
    }

    if (FIELD(arg3, u8, 0x25) == 0) {
        result = -0x201;
        func_800AA79C(arg0, arg1, arg2, arg3);
        (void)result;
        func_80171320();
    }

    initial_flags = FIELD(arg3, u32, 0x1C);
    FIELD(arg3, u32, 0x1C) = initial_flags & -0x201;

    status_flags = status[1];
    
    if ((status_flags & 0x2000) == 0) {
        if (initial_flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_80171364();
        }

        
        ASM_SCHED_BARRIER();
        if (FIELD(arg0, u8, 0x9A) != 14) {
            if (FIELD(arg2, u8 *, 0x2C) != D_8017386C) {
                FIELD(arg2, u8 *, 0x2C) = D_8017386C;
                func_80047784(
                    arg2,
                    D_8017386C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
            FIELD(arg0, u8, 0x9A) = 14;
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80173874) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173478(arg0, arg1, arg2, arg3);
            func_80171364();
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, u8, 0x26) = result;

    if (FIELD(arg3, s8, 0x6D) > 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x20) {
            goto case_12;
        }

        if (FIELD(arg2, u16, 0x24) == *(u16 *)&D_80082EA4) {
            goto case_default;
        }

        if ((FIELD(arg3, u16, 0x46) & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(arg3, (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) != 0) {
                    return;
                }
            }

            if ((s16)func_801720E0(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            FIELD(arg3, u16, 0x46) |= 0x4000;
            if ((FIELD(arg3, u16, 0x46) & 0x8000) == 0) {
                goto case_default;
            }
        }

        kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
        switch_index = kind - 1;
        if ((u32)switch_index >= 12U) {
            goto case_default;
        }
        (void)keepalive;
        goto *D_80170808[switch_index];

case_9:
        FIELD(arg0, u16, 0x98) |= 0x8000;

case_8:
        if ((FIELD(arg3, u32, 0x1C) & 0x2000) &&
            ((FIELD(arg3, u16, 0x46) & 0x3FFF) == 8)) {
            FIELD(arg0, u16, 0x98) &= 0x7FFF;
        }
        if ((s16)func_80171D80(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_80171F90(arg0, arg1, arg2, arg3);
        func_80171364();

case_5_7:
        result = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], (s16 *)&distance);
        player = D_800814A8;
        FIELD(arg3, s16, 0x2A) = result;
        if (FIELD(player, u8, 0x9A) == 0x11) {
            goto case_1_3_common;
        }

case_12:
        func_800A9A0C(arg3);
        func_80171364();

case_1_3:
case_1_3_common:
        func_800AAF00(arg0, arg1, arg2, D_8017389C, D_80170E68);
        func_80171364();

case_default:
        func_801715CC(arg0, arg1, arg2, arg3);
        return;
    }

    flags = FIELD(arg3, u32, 0x1C);
    if ((flags & 0x2000) == 0) {
        tail_index = (s8)result;
        if (tail_index >= 0) {
            entry_base = (u8 *)D_800E2970;
            entry = entry_base + tail_index * 20;
            if (FIELD(entry, u16, 0xC) & 2) {
                goto tail_checks;
            }
        }
        if ((flags & 0x430) == 0) {
            animation = D_80082E80;
            if ((s16)func_8009FD7C(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    animation[0x24], animation[0x25]) != 0) {
                result = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    animation[0x24], animation[0x25], (s16 *)&distance);
                FIELD(arg3, s16, 0x2A) = result;
            }
        }
    }

tail_checks:
    if (D_80083462 & 0x2000) {
        return;
    }
    if (FIELD(arg2, u16, 0x14) & 0x40) {
        return;
    }
    if (FIELD(arg2, u8 * volatile, 0x2C) != D_8017386C) {
        FIELD(arg2, u8 *, 0x2C) = D_8017386C;
        func_80047784(
            arg2,
            D_8017386C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
}

/* MECHANISM: Returning func_801715CC plus explicit return restored the missing local-exit edge.
   A post-flags schedule barrier moved s4=14 from the branch slot into retail's load-delay slot.
   Split switch/tail indices and base/result pointers fixed the tail register roles.
   Pinning only initial_flags to v1 made the overlapping status base naturally use a0 via v0. */
