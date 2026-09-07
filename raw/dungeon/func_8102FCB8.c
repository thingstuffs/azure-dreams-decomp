#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
extern void func_80171C18(void) __attribute__((noreturn));
extern void func_80171C3C(void);
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

void func_801714B8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *p0 ASM_REG("$19");
    register void *p1 ASM_REG("$20");
    register void *p2 ASM_REG("$17");
    register void *p3 ASM_REG("$18");
    s32 result;
    s32 scratch;
    u16 offsets[3];
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
        func_80171C3C();
        func_80171C18();
        return;
    }

    ASM_KEEP(p0);
    ASM_KEEP(p1);
    ASM_KEEP(p2);
    ASM_KEEP(p3);

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) != D_801760EC) {
            u8 *state_table = D_801760E4;

            FIELD(arg2, void *, 0x2C) = state_table;
            func_80047784(arg2,
                state_table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            func_80171C18();
        }
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_801760EC) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            func_80171C18();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_801760E4)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_80171C18();
            return;
        }

        ASM_KEEP(arg0);
        if (FIELD(arg0, u8, 0x9A) != 0xE) {
            u8 state = 0xE;
            u8 *state_table = D_8017609C;

            if (FIELD(arg2, void *, 0x2C) != state_table) {
                FIELD(arg2, void *, 0x2C) = state_table;
                func_80047784(arg2,
                    state_table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
            FIELD(arg0, s16, 0x9E) = 0;
            FIELD(arg0, s16, 0xA0) = (rand() & 0x1F) + 0xF;
            FIELD(arg0, u8, 0x9A) = state;
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_801760AC)) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_8017412C(arg0, arg1, arg2, arg3);
            func_80171C18();
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
            if ((s16)func_80172918(arg0, arg1, arg2, 0) == 0) {
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
                &&ordinary_cleanup,
                &&coords_case, &&coords_case, &&coords_case,
                &&handler_case, &&handler2_case,
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
#endif
            if ((s16)func_8017263C(arg0, arg1, arg2, arg3) == 0) {
                func_80172800(arg0, arg1, arg2, arg3);
                func_80171C18();
            }
            return;

#ifdef __mips__
handler2_case:
#else
        case 9:
#endif
            func_801756E0(arg0, arg1, arg2, arg3);
            func_80171C18();
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
            s16 coordinate;

            coordinate = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                &scratch);
            player = D_800814A8;
            FIELD(arg3, s16, 0x2A) = coordinate;
            if (FIELD(player, u8, 0x9A) == 0x11) {
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
        func_800A9A0C(arg3);
        func_80171C18();
        return;

aaf_cleanup:
        func_800AAF00(arg0, arg1, arg2, D_801760DC, &D_801714B8);
        func_80171C18();
        return;

ordinary_cleanup:
        func_80171E80(arg0, arg1, arg2, arg3);
        func_80171C18();
        return;
    } else if (!(FIELD(arg3, u32, 0x1C) & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) || !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(FIELD(arg3, u32, 0x1C) & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25)) != 0) {
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
    if (FIELD(arg3, u32, 0x1C) & 0x20) {
        return;
    }

    {
    u8 *main_table = D_8017609C;

    if (FIELD(arg2, void *, 0x2C) != main_table) {
        if (FIELD(arg2, void *, 0x2C) != D_801760A4) {
            FIELD(arg2, void *, 0x2C) = main_table;
            func_80047784(arg2,
                main_table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg0, s16, 0x9E) = 0;
            FIELD(arg0, s16, 0xA0) = (rand() & 0x1F) + 0xF;
        }
        if (FIELD(arg2, void *, 0x2C) != main_table) {
            goto final_state_check;
        }
    }

    {
        s16 timer = FIELD(arg0, u16, 0x9E);

        FIELD(arg0, u16, 0x9E) = timer + 1;
        if (timer >= FIELD(arg0, s16, 0xA0)) {
            void *object;
            u8 *object_data;

            u8 *alt_table = D_801760A4;

            FIELD(arg2, void *, 0x2C) = alt_table;
            func_80047784(arg2,
                alt_table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            func_800478B8(arg2);

            object = func_8003FC64(0x212);
            if (object != 0) {
                func_80170DD0(object, arg0, arg1);
                FIELD(object, void *, 0x10) = D_80170A0C;
                object_data = (u8 *)object + 0x20;
                FIELD(object_data, void *, 0x28) = arg1;
                FIELD(object_data, u16, 0x1C) = FIELD(arg3, u16, 0x2A);

                {
                    void *owner = FIELD(arg0, void *, -0x14);

                if (func_8003DE58(
                        FIELD(owner, void *, 8), owner, offsets, 0xF)) {
                    void *part = FIELD(object, void *, 8);

                    FIELD(part, u16, 2) += offsets[0];
                    FIELD(part, u16, 6) += offsets[1];
                    FIELD(part, u16, 0xA) += offsets[2];
                }
                }
                {
                    void *part = FIELD(object, void *, 0xC);
                    FIELD(part, u16, 0x14) |= 0x80;
                    func_8003DB94(part, &D_800DEA68, 0);
                }
            }
        }
    }
    }

final_state_check:
    if (FIELD(arg2, void *, 0x2C) == D_801760A4 &&
            (FIELD(arg2, u16, 0x14) & 0x6000)) {
        u8 *state_table = D_8017609C;

        FIELD(arg2, void *, 0x2C) = state_table;
        func_80047784(arg2,
            state_table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, s16, 0x9E) = 0;
        FIELD(arg0, s16, 0xA0) = (rand() & 0x1F) + 0xF;
    }
}
