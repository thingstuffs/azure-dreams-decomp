#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_801714EC(void) __attribute__((noreturn));
extern void func_80171510(void);
extern void func_80171768(void *, void *, void *, void *);
extern s32 func_80171F24(void *, void *, void *, void *);
extern void func_80172110(void *, void *, void *, void *);
extern s32 func_80172228(void *, void *, void *, s32);
extern void func_80173900(void *, void *, void *, void *);
extern void func_80173AD4(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern s32 D_80170F68;
extern u8 D_80173FB8[];
extern u8 D_80173FC0[];
extern u8 D_80173FF0[];
extern u8 D_80173FF8[];
extern u8 D_80174000[];

void func_80170F68(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *p0 ASM_REG("$17");
    register void *p1 ASM_REG("$19");
    register void *p2 ASM_REG("$16");
    register void *p3 ASM_REG("$18");
    u8 *table;
    s32 result;
    s32 scratch;
    u32 initial_flags = D_80083462;

    p0 = arg0;
    p1 = arg1;
    p2 = arg2;
    p3 = arg3;
#define arg0 p0
#define arg1 p1
#define arg2 p2
#define arg3 p3

    if (initial_flags & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_80171510();
        func_801714EC();
        return;
    }

    ASM_KEEP(p0);
    ASM_KEEP(p1);
    ASM_KEEP(p2);
    ASM_KEEP(p3);

    if (FIELD(arg3, u8, 0x25) == 0) {
        register u8 *zero_table ASM_REG("$5");

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) != D_80174000) {
            zero_table = D_80173FF8;
            FIELD(arg2, void *, 0x2C) = zero_table;
            func_80047784(arg2,
                zero_table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }
        FIELD(arg0, s16, 0xAE) = 0;
        func_80042B68(arg3, 0x1A);
        func_801714EC();
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80174000) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            func_801714EC();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80173FF8)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_801714EC();
            return;
        }

        ASM_KEEP(arg0);
        if (FIELD(arg0, u8, 0x9A) != 0xE) {
            u8 state = 0xE;

            table = D_80173FB8;
            if (FIELD(arg2, void *, 0x2C) != table) {
                FIELD(arg2, void *, 0x2C) = table;
                func_80047784(arg2,
                    table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
            FIELD(arg0, u8, 0x9A) = state;
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80173FC0)) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173900(arg0, arg1, arg2, arg3);
            func_801714EC();
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
            goto special_cleanup;
        }
        if (FIELD(arg2, u16, 0x24) == *(u16 *)&D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(arg3,
                        (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172228(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            FIELD(arg3, u16, 0x46) |= 0x4000;
            if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

#ifdef __mips__
        {
            static void *volatile dispatch_labels[] = {
                &&aaf_cleanup, &&aaf_cleanup, &&aaf_cleanup,
                &&extra_cleanup,
                &&coords_case, &&coords_case, &&coords_case,
                &&handler_case, &&handler_case,
                &&ordinary_cleanup, &&ordinary_cleanup,
                &&special_cleanup,
            };
            s32 dispatch_index;

            dispatch_index = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
            if ((u32)dispatch_index >= 12) {
                goto ordinary_cleanup;
            }
            goto *D_80170808[dispatch_index];
        }
handler_case:
#else
        switch (FIELD(arg3, u16, 0x46) & 0x3FFF) {
        case 8:
        case 9:
#endif
            if ((s16)func_80171F24(arg0, arg1, arg2, arg3) == 0) {
                func_80172110(arg0, arg1, arg2, arg3);
                func_801714EC();
            }
            return;

#ifdef __mips__
extra_cleanup:
#else
        case 4:
#endif
            func_80173AD4(arg0, arg1, arg2, arg3);
            func_801714EC();
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
            void *global;
            s32 direction;

            direction = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                &scratch);
            global = D_800814A8;
            FIELD(arg3, s16, 0x2A) = direction;
            if (FIELD(global, u8, 0x9A) == 0x11) {
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

        case 10:
        case 11:
        default:
            goto ordinary_cleanup;
        }
#endif

special_cleanup:
        func_800A9A0C(arg3);
        func_801714EC();
        return;

aaf_cleanup:
        func_800AAF00(arg0, arg1, arg2, D_80173FF0, &D_80170F68);
        func_801714EC();
        return;

ordinary_cleanup:
        func_80171768(arg0, arg1, arg2, arg3);
        func_801714EC();
        return;
    } else if (!(FIELD(arg3, u32, 0x1C) & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) || !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
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
    table = D_80173FB8;
    if (FIELD(arg2, void *, 0x2C) == table) {
        return;
    }
    FIELD(arg2, void *, 0x2C) = table;
    func_80047784(arg2,
        ((((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7) + table)[0],
        0);
}
