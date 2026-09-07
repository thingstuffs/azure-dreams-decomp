#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
extern void func_80171964(void);
extern void func_80171B1C(void *, void *, void *, void *);
extern s32 func_80172264(void *, void *, void *, void *);
extern void func_80172428(void *, void *, void *, void *);
extern s32 func_80172550(void *, void *, void *, s32);
extern void func_80173C34(void *, void *, void *, void *);
extern void func_80175068(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern u8 D_8017586C[];
extern u8 D_80175874[];
extern u8 D_80175884[];
extern u8 D_8017588C[];
extern u8 D_80175894[];

void func_8017140C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch;
    s8 result;
    u16 state;

    if (D_80083462 & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_80171964();
        return;
    }

    if (FIELD(arg3, u8, 0x25) == 0) {
        u8 *table;

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) == D_80175894) {
            return;
        }
        table = D_8017588C;
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80175894) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_8017588C) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        void *current;
        u8 *table;

        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (FIELD(arg0, u8, 0x9A) != 0xE) {
            FIELD(arg0, u8, 0x9A) = 0xE;
        }
        ASM_SCHED_BARRIER();

        current = FIELD(arg2, void *, 0x2C);
        table = D_8017586C;
        if (current != table) {
            FIELD(arg2, void *, 0x2C) = table;
            func_80047784(arg2,
                table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg2, u8, 5) = 1;
            FIELD(arg0, s16, 0xB6) = 0;
            FIELD(arg0, s16, 0xB8) = 0;
        }

        FIELD(arg3, u32, 0x1C) |= 0x40000;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80175874) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            s16 delta;

            func_800AA888(arg0, arg1, arg2, arg3);
            delta = FIELD(arg0, u16, 0x92) - FIELD(arg0, u16, 0xB6);
            FIELD(arg0, s16, 0xB6) = 0;
            FIELD(arg0, s16, 0xB8) = 0;
            FIELD(arg0, s16, 0x92) = delta;
            func_80173C34(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            if ((func_800AAB10(arg0, arg1, arg2, arg3) << 16) != 0) {
                func_80175068(arg0, arg1, arg2, arg3);
            }
        }
    }

    result = func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, u8, 0x26) = result;

    if (FIELD(arg3, s8, 0x6D) > 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x20) {
            goto case_12;
        }
        if (FIELD(arg2, u16, 0x24) == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172550(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = FIELD(arg3, u16, 0x46) | 0x4000;
            FIELD(arg3, u16, 0x46) = state;
            if (!(state & 0x8000)) {
                goto generic;
            }
        }

        {
            static void *const sw_keep[] = {
                &&case_123, &&generic, &&sw_case89, &&sw_case567, &&case_12
            };
            extern void *const D_80170808[];
            u32 swi = (u32)((FIELD(arg3, u16, 0x46) & 0x3FFF) - 1);

            if (swi >= 12) {
                goto generic;
            }
            (void)sw_keep;
            goto *D_80170808[swi];
        }
sw_case89:
        if ((func_80172264(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172428(arg0, arg1, arg2, arg3);
        return;

sw_case567:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 coordinate;

            coordinate = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                &scratch);
            player = D_800814A8;
#ifndef __mips__
            
#endif
            FIELD(arg3, s16, 0x2A) = coordinate;
            if (FIELD(player, u8, 0x9A) == 0x11) {
                goto case_123;
            }
        }

case_12:
        func_800A9A0C(arg3);
        return;

case_123:
        func_800AAF00(arg0, arg1, arg2, D_80175884, func_8017140C);
        return;

generic:
        func_80171B1C(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(FIELD(arg3, u32, 0x1C) & 0x2000)) {
        s32 index = result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(FIELD(arg3, u32, 0x1C) & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25)) << 16) != 0) {
                    FIELD(arg3, s16, 0x2A) = func_800A0818(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                        &scratch);
                }
            }
        }
    }
}
