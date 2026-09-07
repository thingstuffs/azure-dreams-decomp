#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void D_80170CF8(void *, s32, s32, s32, s32, s32, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[16];
extern u8 D_80170838[16];
extern u8 D_801717F4[];
extern u8 D_80175988[];

void func_80173280(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 i;
    register void *tile ASM_REG("$20") = arg2;
    s32 ry;
    s32 rx;
    void *obj;
    u8 *kindp;
    s32 state;
    register s32 flag ASM_REG("$18");
    register s32 save_nudge ASM_REG("$18");
    static void *const keepalive[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };

#ifdef NON_MATCHING
    save_nudge = 0;
#endif
    ASM_KEEP_DEP_NV(save_nudge, arg3);
    ASM_USE(save_nudge);
    state = FIELD(arg0, u8, 0x9B);
    ASM_KEEP(tile);
    flag = 0;
    if (state != 1) {
        if ((s32)state < 2) {
            if (state == 0) {
                goto state_0;
            }
            return;
        }
        if (state == 2) {
            goto state_2;
        }
        if (state == 3) {
            goto state_3;
        }
        return;
    }
    goto state_1;

state_0:
    if (FIELD(arg3, s32, 0x1C) & 0x2000) {
        u32 kind = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;

        if (kind >= 7) {
            goto kind_default;
        }
        goto *(((void **)D_80170838)[kind]);

kind_5:
        flag = 1;
        goto kind_3;
kind_6:
        flag = 1;
        goto kind_2;
kind_7:
        flag = 1;
        goto kind_1;
    } else {
        u32 kind = FIELD(arg3, u16, 0x46) & 0x3FFF;

        if (kind == 2) {
            goto kind_2;
        }
        if ((s32)kind < 3) {
            if (kind == 1) {
                goto kind_1;
            }
            kindp = 0;
            goto use_kind;
        }
        if (kind == 3) {
            goto kind_3;
        }
        kindp = 0;
        goto use_kind;
    }

kind_3:
    kindp = (u8 *)arg3 + 0xE;
    goto use_kind;
kind_2:
    kindp = (u8 *)arg3 + 0xB;
    goto use_kind;
kind_1:
    kindp = (u8 *)arg3 + 8;
    goto use_kind;
kind_default:
    kindp = 0;

use_kind:
    if (*kindp != 0) {
        *(volatile u16 *)((u8 *)arg0 + 0x98) =
            FIELD(arg0, u16, 0x98) & 0xFF7F;
        ASM_MEM_BARRIER();
        {
            register s32 use_flag ASM_REG("$2") = flag;
            ASM_KEEP(use_flag);
            if (use_flag) {
                obj = D_800814A8;
                FIELD(arg3, void *, 0x60) = obj;
                goto copy_existing;
            }
        }
        {
            u8 *base;
            u8 kind;
            register u8 *entry ASM_REG("$2");

            base = (u8 *)0x80070000;
            ASM_KEEP(base);
            kind = *kindp;
            base -= 0x21DC;
            entry = (u8 *)((u32)(kind * 20) + (u32)base);
            ASM_KEEP(entry);

            if (entry[0x12] == 2) {
                obj = FIELD(arg3, void *, 0x60);

                if (obj != 0) {
copy_existing:
                    {
                        register u8 *other ASM_REG("$3") =
                            FIELD((u8 *)obj - 0x14, u8 *, 0);
                        FIELD(arg3, u8, 0x72) = other[0x24];
                        FIELD(arg3, u8, 0x73) = other[0x25];
                    }
                    goto invoke_move;
                }
                goto call_move;
            }
        }

        *(void * volatile *)((u8 *)arg3 + 0x60) =
            func_800A05A4(arg3, FIELD(tile, u8, 0x24), FIELD(tile, u8, 0x25),
                          FIELD(arg3, s16, 0x2A), 0x10);
        ASM_KEEP(flag);
        {
            s32 x = FIELD(arg3, s8, 0x72);
            s32 y = FIELD(arg3, s8, 0x73);

            if (x < 0) {
                x = -x;
            }
            if (y < 0) {
                y = -y;
            }
            FIELD(arg3, u8, 0x72) = x;
            FIELD(arg3, u8, 0x73) = y;
        }

call_move:
        (void)0;
invoke_move:
        if (func_800A94A0(arg3, kindp, flag, (u8 *)arg0 + 0x98)) {
            FIELD(arg0, u16, 0x96) = 0x18;
            FIELD(arg0, u16, 0x9E) = 4;
            FIELD(arg0, u8, 0x9B)++;
            return;
        }
        goto done;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(tile, u8, 0x24), FIELD(tile, u8, 0x25));
    {
        u8 *global = D_800814A8;
        FIELD(D_80083460, s32, 0xC) = 0;
        FIELD(global, u16, 0xA6)--;
    }
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, u8 *, 0x8C) = D_801717F4;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    return;

state_1:
    if (func_8003F270()) {
        FIELD(tile, u16, 0x14) |= 0x800;
        return;
    }
    FIELD(tile, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);

state_2:
    i = 0;
    do {
        flag = func_80069EF8() & 0xFF;
        flag |= 0x80;
        rx = (s16)((func_80069EF8() & 0x7F) - 0x40);
        ry = (s16)((func_80069EF8() & 0x7F) - 0x40);
        D_80170CF8((u8 *)arg0 - 0x20, 0, 0x00808080, flag, rx, ry,
                   (s16)((func_80069EF8() & 0x7F) - 0x40));
        i++;
    } while (i < 5);

    FIELD(arg0, u16, 0x9E)--;
    if ((s16)FIELD(arg0, u16, 0x9E) == 1) {
        FIELD(tile, u16, 0x14) |= 0x800;
    }
    if (FIELD(arg0, s16, 0x96) == 5) {
        FIELD(tile, u16, 0x14) &= 0xF7FF;
    }
    FIELD(arg0, u16, 0x96)--;
    if ((s16)FIELD(arg0, u16, 0x96) > 0 &&
        !(FIELD(tile, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg0, u16, 0x98) |= 0x80;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(tile, u16, 0x14) |= 0x800;
    FIELD(arg0, u16, 0x96) = 0x14;
    return;

state_3:
    kindp = D_80083460;
    if (FIELD(kindp, s32, 0xC) == 0) {
        FIELD(arg0, u16, 0x96) = 0;
    }
    FIELD(arg0, u16, 0x96)--;
    if ((s16)FIELD(arg0, u16, 0x96) <= 0) {
        *(volatile u16 *)((u8 *)arg0 + 0x96) = 0;
        FIELD(tile, u16, 0x14) &= 0xF7FF;
    }
    if (!(FIELD(tile, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(tile, u8, 0x24), FIELD(tile, u8, 0x25));
    if (FIELD(tile, u8 *, 0x2C) != D_80175988) {
        u8 *table = D_80175988;
        FIELD(tile, u8 *, 0x2C) = table;
        func_80047784(tile,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(tile, u16, 0x14) &= 0xF7FF;
    }
    if (FIELD(kindp, s32, 0xC) != 0) {
        goto done;
    }
    FIELD(kindp, u16, 0xA)--;
    FIELD(arg0, u8 *, 0x8C) = D_801717F4;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}
