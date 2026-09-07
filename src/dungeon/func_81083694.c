#include "common.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct TileEntry {
    u8 pad[12];
    u16 flags;
    u8 tail[6];
} TileEntry;

extern u16 D_80083462;
extern s16 D_80083228;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern TileEntry D_800E2970[];
extern void *D_80170808[];
extern u8 D_80175F10[];
extern u8 D_80175F20;
extern u8 D_80175F28;
extern u8 D_80175F38[];
extern u8 D_80175F50;
extern u8 D_80175F60;

extern s32 func_80042900();
extern s32 func_80047784(void *, s32, s32);
extern s32 func_8009A180();
extern s32 func_8009FB34();
extern s32 func_8009FD7C();
extern s32 func_800A0818();
extern s32 func_800A1C58();
extern s32 func_800A6D30();
extern s32 func_800A9A0C();
extern s32 func_800AA258();
extern s32 func_800AA6B4();
extern s32 func_800AA79C();
extern s32 func_800AA888();
extern s32 func_800AA924();
extern s32 func_800AAB10();
extern s32 func_800AAF00();
extern s32 func_801716B4();
extern s32 func_801718F8();
extern s32 func_80172050();
extern s32 func_80172218();
extern s32 func_80172334();
extern s32 func_801723D8();
extern s32 func_80172504();
extern s32 func_801727D8();
extern s32 func_80174698();
extern s32 func_80174EB4();
extern s32 func_80175ED4();

void func_80170E94(void *in0, void *arg1, void *arg2, void *arg3) {
    void *arg0 = in0;
    s16 out;
    s32 tile;
    u32 swi;
    u32 state;
    u32 state25;
    u32 state_work;
    u8 *seq;
    u8 *seq10;
    u8 *effect_ptr;
    u8 *map;
    static void *const sw_keep[] = {
        &&case_1, &&case_1, &&case_1, &&case_default,
        &&case_5, &&case_5, &&case_5, &&case_8,
        &&case_9, &&case_default, &&case_11, &&case_12,
    };

    if ((F(arg0, u8, 0xAE) == 0) && (D_80083462 & 0x1000)) {
        F(arg0, u8, 0x9A) = 14;
        func_801716B4();
        goto done;
    }

    if (F(arg3, u8, 0x25) == 0) {
        func_80175ED4(arg0, arg3);
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (F(arg2, void *, 0x2C) == &D_80175F28) {
            goto done;
        }
        seq10 = &D_80175F20;
        goto set_seq10;
    }

    if (F(arg3, u32, 0x1C) & 0x200) {
        if (F(arg2, void *, 0x2C) == &D_80175F28) {
            F(arg0, u8, 0x9A) = 13;
            F(arg0, u8, 0x9B) = 1;
            F(arg0, u32, 0x8C) = 0;
            F(arg3, u32, 0x1C) &= ~0x40000;
            goto done;
        }
        func_80175ED4(arg0, arg3);
        if (func_800AA924(arg0, arg1, arg2, &D_80175F20)) {
            goto done;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (F(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto done;
        }

        state = F(arg0, u8, 0x9A);
        state25 = 25;
        state_work = 14;
        if (state == state25) {
            goto state_check_14;
        }
        if (F(arg0, u8, 0xAE) != 0) {
            state_work = (u32)D_80175F38;
            if (F(arg2, void *, 0x2C) != (void *)state_work) {
                func_80174EB4(arg0, arg1, arg2);
                F(arg2, void *, 0x2C) = (void *)state_work;
                func_80047784(arg2,
                    ((u8 *)state_work)[((D_80083228 + F(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
            F(arg0, u8, 0x9A) = state25;
            goto state_done;
        }
state_check_14:
        state = F(arg0, u8, 0x9A);
        state_work = 14;
        if (state != state_work) {
            if (F(arg0, u8, 0xAE) == 0) {
                seq10 = D_80175F10;
                if (F(arg2, void *, 0x2C) != seq10) {
                    F(arg2, void *, 0x2C) = seq10;
                    func_80047784(arg2,
                        seq10[((D_80083228 + F(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                }
                F(arg0, u8, 0x9A) = state_work;
            }
        }

state_done:
        F(arg0, u16, 0x98) &= 0xFFF3;
        if (F(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, &D_80175F50)) {
                goto done;
            }
        }
        if (F(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80174698(arg0, arg1, arg2, arg3);
            goto done;
        }
        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    tile = func_8009FB34(F(arg2, u8, 0x24), F(arg2, u8, 0x25));
    F(arg2, u8, 0x26) = tile;
    if (F(arg3, s8, 0x6D) <= 0) {
        goto health_zero;
    }
    if (F(arg3, u32, 0x1C) & 0x20) {
        goto kill;
    }
    if ((F(arg2, u16, 0x24) == *(u16 *)&D_80082EA4) &&
        (F(arg0, u8, 0xAE) == 0)) {
        func_80175ED4(arg0, arg3);
        func_801718F8(arg0, arg1, arg2, arg3);
        goto done;
    }

    if (!(F(arg3, u16, 0x46) & 0x8000)) {
        if (D_80083462 & 0x2000) {
            if ((s16)func_8009A180(arg3,
                    (u8 *)F(D_800814A8, void *, 0x58) + 0x20) != 0) {
                goto done;
            }
        }
        if (F(arg0, u8, 0xAE) == 0) {
            if ((s16)func_801727D8(arg0, arg1, arg2, 0) == 0) {
                goto done;
            }
        }
        F(arg3, u16, 0x46) |= 0x4000;
        if (!(F(arg3, u16, 0x46) & 0x8000)) {
            goto case_default;
        }
    }

    swi = (F(arg3, u16, 0x46) & 0x3FFF) - 1;
    if (swi >= 12) {
        goto case_default;
    }
    (void)sw_keep;
    goto *D_80170808[swi];

case_12:
    if (func_80175ED4(arg0, arg3) == 0) {
        goto kill;
    }
    seq10 = D_80175F10;
    F(arg2, void *, 0x2C) = seq10;
    func_80047784(arg2,
        seq10[((D_80083228 + F(arg3, s16, 0x2A) + 0x100) >> 9) & 7], 0);
    goto kill;

case_11:
    func_801718F8(arg0, arg1, arg2, arg3);
    goto final_cleanup;

case_8:
    func_80175ED4(arg0, arg3);
    if ((s16)func_80172050(arg0, arg1, arg2, arg3) != 0) {
        goto done;
    }
    func_80172218(arg0, arg1, arg2, arg3);
    goto done;

case_9:
    {
    register void *effect_owner;

    if (F(arg0, u8, 0xAE) != 0) {
        if ((F(arg3, u32, 0x1C) & 0x400) && (F(arg3, s32, 0x14) >= 0)) {
            F(arg3, u32, 0x14) |= 0x80000000;
            F(arg3, u16, 0x2A) += (func_800A6D30(arg0, arg1) & 7) << 9;
        }
        func_80172504(arg0, arg1, arg2, arg3);
        goto done;
    }
    func_801723D8(arg0, arg1, arg2, arg3);
    goto done;

case_5: {
        s16 next_tile;
        void *leader;

        next_tile = func_800A0818(
            F(arg2, u8, 0x24), F(arg2, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &out);
        leader = D_800814A8;
        F(arg3, s16, 0x2A) = next_tile;
        if (F(leader, u8, 0x9A) == 17) {
            goto case_1;
        }
    }

kill:
    func_800A9A0C(arg3);
    goto done;

case_1:
    func_80175ED4(arg0, arg3);
    func_800AAF00(arg0, arg1, arg2, &D_80175F60, func_80170E94);
    goto done;

case_default:
    func_801718F8(arg0, arg1, arg2, arg3);
    if (F(arg0, u8, 0xAE) == 0) {
        goto done;
    }

final_cleanup:
    func_80175ED4(arg0, arg3);
    goto done;

health_zero:
    if (F(arg0, u8, 0xAE) == 0) {
        u32 flags = F(arg3, u32, 0x1C);
        if (flags & 0x2000) {
            goto flag_2000;
        }
        if ((s8)tile >= 0) {
            if (D_800E2970[(s8)tile].flags & 2) {
                goto final_checks;
            }
        }
        if (flags & 0x430) {
            goto final_checks;
        }
        map = D_80082E80;
        if ((s16)func_8009FD7C(F(arg2, u8, 0x24), F(arg2, u8, 0x25),
                map[0x24], map[0x25]) != 0) {
            F(arg3, s16, 0x2A) = func_800A0818(
                F(arg2, u8, 0x24), F(arg2, u8, 0x25),
                map[0x24], map[0x25], &out);
        }
        goto final_checks;

flag_2000:
        if ((s16)func_80042900(arg3, 4) != 0) {
            goto final_checks;
        }
        if (F(D_800814A8, u8, 0x9A) == 23) {
            func_80172334(arg0, arg1, arg2, arg3);
        }
    }

final_checks:
    if (D_80083462 & 0x2000) {
        goto done;
    }
    if (F(arg2, u16, 0x14) & 0x40) {
        goto done;
    }
    if (F(arg0, u8, 0xAE) != 0) {
        seq = D_80175F38;
        if (F(arg2, void *, 0x2C) == seq) {
            goto done;
        }
        func_80174EB4(arg0, arg1, arg2);
        F(arg2, void *, 0x2C) = seq;
        effect_owner = arg2;
        effect_ptr = seq + (((D_80083228 + F(arg3, s16, 0x2A) + 0x100) >> 9) & 7);
    } else {
        void *current_seq;

        current_seq = F(arg2, void *, 0x2C);
        seq10 = D_80175F10;
        if (current_seq == seq10) {
            goto done;
        }

set_seq10:
        F(arg2, void *, 0x2C) = seq10;
        effect_owner = arg2;
        effect_ptr = seq10 + (((D_80083228 + F(arg3, s16, 0x2A) + 0x100) >> 9) & 7);
    }

    func_80047784(effect_owner, *effect_ptr, 0);
    }

done:
    return;
}
