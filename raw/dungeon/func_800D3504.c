#include "common.h"

extern void func_8003DB94(void *, void *, s32);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, s32);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800D8FFC(void);
extern void func_800D9028(void);
extern void func_800D904C(void);
extern void func_800D92C0(void *, void *, void *, void *);
extern void func_800DA660(void *, void *, void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern u16 D_80083462;
extern void *D_800E262C[];
extern s8 D_800E2970[];

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

void func_800D8C64(void *arg0, void *arg1, void *arg2, void *arg3)
{
    void **table;
    s32 result;
    s32 scratch;

    if (D_80083462 & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_800D904C();
        func_800D9028();
        return;
    }

    if (FIELD(arg3, u8, 0x25) == 0) {
        void *current;
        u32 globalPage;

        func_800AA79C(arg0, arg1, arg2, arg3);
        current = FIELD(arg2, void *, 0x2C);
        table = D_800E262C;
        if (current != table) {
            globalPage = 0x80080000;
            ASM_KEEP(globalPage);
            FIELD(arg2, void *, 0x2C) = table;
            func_800D8FFC();
        }
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_800E262C) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            func_800D9028();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, 0)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_800D9028();
            return;
        }

        if (FIELD(arg0, u8, 0x9A) != 0xE) {
            u8 state = 0xE;

            table = D_800E262C;
            if (FIELD(arg2, void *, 0x2C) != table) {
                FIELD(arg2, void *, 0x2C) = table;
                func_8003DB94(arg2,
                    *(void **)((u8 *)table +
                        (((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 7) & 0x1C)),
                    0);
            }
            FIELD(arg0, u8, 0x9A) = state;
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0)) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            FIELD(arg0, s32, 0x90) = 0;
            FIELD(arg0, u16, 0x98) &= 0xFFFE;
            FIELD(arg1, s32, 0x14) = 0;
            func_800AA888(arg0, arg1, arg2, arg3);
            func_800DA660(arg0, arg1, arg2, arg3);
            func_800D9028();
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, u8, 0x26) = result;

    if (FIELD(arg3, s8, 0x6D) > 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x20) {
            func_800A9A0C(arg3);
            func_800D9028();
            return;
        }
        func_800D92C0(arg0, arg1, arg2, arg3);
        func_800D9028();
        return;
    }

    if (!(FIELD(arg3, u32, 0x1C) & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(FIELD(arg3, u32, 0x1C) & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(FIELD(arg2, u8, 0x24),
                        FIELD(arg2, u8, 0x25), FIELD(origin, u8, 0x24),
                        FIELD(origin, u8, 0x25)) != 0) {
                    FIELD(arg3, s16, 0x2A) = func_800A0818(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                        &scratch);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (FIELD(arg2, u16, 0x14) & 0x40) {
        return;
    }
    table = D_800E262C;
    if (FIELD(arg2, void *, 0x2C) == table) {
        return;
    }
    if (FIELD(arg0, u16, 0x98) & 1) {
        return;
    }
    FIELD(arg2, void *, 0x2C) = table;
    func_8003DB94(arg2,
        *(void **)((u8 *)table +
            (((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 7) & 0x1C)),
        0);
}
