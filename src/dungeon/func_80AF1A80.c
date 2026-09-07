#include "common.h"

typedef struct S_80173280_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
} S_80173280_0;   /* arg0 in func_80173280 */

typedef struct S_80173280_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80173280_1;   /* arg3 in func_80173280 */

typedef struct S_80173280_2 {
    u8 * unk_00;
} S_80173280_2;   /* (u8 *)obj - 0x14 in func_80173280 */

typedef struct S_80173280_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80173280_3;   /* tile in func_80173280 */

typedef struct S_80173280_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173280_4;   /* arg1 in func_80173280 */

typedef struct S_80173280_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80173280_5;   /* D_80083460 in func_80173280 */

typedef struct S_80173280_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80173280_6;   /* global in func_80173280 */

typedef struct S_80173280_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80173280_7;   /* kindp in func_80173280 */



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
    register void *tile ASM_REG("$20") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 ry;
    s32 rx;
    void *obj;
    u8 *kindp;
    s32 state;
    s32 flag;
    register s32 save_nudge ASM_REG("$18");   /* MATCH pin: retail schedule: same instructions, different order without it */
    static void *const keepalive[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };

#ifdef NON_MATCHING
    save_nudge = 0;
#endif
    ASM_KEEP_DEP_NV(save_nudge, arg3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_USE(save_nudge);   /* MATCH pin: retail schedule: same instructions, different order without it */
    state = ((S_80173280_0 *)arg0)->unk_9B;
    ASM_KEEP(tile);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
    if (((S_80173280_1 *)arg3)->unk_1C & 0x2000) {
        u32 kind = (((S_80173280_1 *)arg3)->unk_46 & 0x3FFF) - 1;

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
        u32 kind = ((S_80173280_1 *)arg3)->unk_46 & 0x3FFF;

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
            ((S_80173280_0 *)arg0)->unk_98 & 0xFF7F;
        {
            s32 use_flag = flag;
            ASM_KEEP(use_flag);   /* MATCH pin: retail delay-slot fill depends on it */
            if (use_flag) {
                obj = D_800814A8;
                ((S_80173280_1 *)arg3)->unk_60 = obj;
                goto copy_existing;
            }
        }
        {
            u8 *base;
            u8 kind;
            u8 *entry;

            base = (u8 *)0x80070000;
            ASM_KEEP(base);   /* MATCH pin: keeps a statement from moving across a call/branch */
            kind = *kindp;
            base -= 0x21DC;
            entry = (u8 *)((u32)(kind * 20) + (u32)base);
            ASM_KEEP(entry);   /* MATCH pin: load-bearing for the whole function shape */

            if (entry[0x12] == 2) {
                obj = ((S_80173280_1 *)arg3)->unk_60;

                if (obj != 0) {
copy_existing:
                    {
                        register u8 *other ASM_REG("$3") =
                            ((S_80173280_2 *)((u8 *)obj - 0x14))->unk_00;
                        ((S_80173280_1 *)arg3)->unk_72.s = other[0x24];
                        ((S_80173280_1 *)arg3)->unk_73.s = other[0x25];
                    }
                    goto invoke_move;
                }
                goto call_move;
            }
        }

        *(void * volatile *)((u8 *)arg3 + 0x60) =
            func_800A05A4(arg3, ((S_80173280_3 *)tile)->unk_24, ((S_80173280_3 *)tile)->unk_25,
                          ((S_80173280_1 *)arg3)->unk_2A, 0x10);
        ASM_KEEP(flag);   /* MATCH pin: keeps a statement from moving across a call/branch */
        {
            s32 x = ((S_80173280_1 *)arg3)->unk_72.u;
            s32 y = ((S_80173280_1 *)arg3)->unk_73.u;

            if (x < 0) {
                x = -x;
            }
            if (y < 0) {
                y = -y;
            }
            ((S_80173280_1 *)arg3)->unk_72.s = x;
            ((S_80173280_1 *)arg3)->unk_73.s = y;
        }

call_move:
        (void)0;
invoke_move:
        if (func_800A94A0(arg3, kindp, flag, (u8 *)arg0 + 0x98)) {
            ((S_80173280_0 *)arg0)->unk_96.s = 0x18;
            ((S_80173280_0 *)arg0)->unk_9E = 4;
            ((S_80173280_0 *)arg0)->unk_9B++;
            return;
        }
        goto done;
    }

    ((S_80173280_4 *)arg1)->unk_14 = 0;
    ((S_80173280_4 *)arg1)->unk_10 = 0;
    ((S_80173280_4 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80173280_3 *)tile)->unk_24, ((S_80173280_3 *)tile)->unk_25);
    {
        u8 *global = D_800814A8;
        ((S_80173280_5 *)D_80083460)->unk_0C = 0;
        ((S_80173280_6 *)global)->unk_A6--;
    }
    func_800A4ACC(arg3);
    ((S_80173280_1 *)arg3)->unk_6D--;
    ((S_80173280_0 *)arg0)->unk_8C = D_801717F4;
    ((S_80173280_1 *)arg3)->unk_73.s = 0;
    ((S_80173280_1 *)arg3)->unk_72.s = 0;
    ((S_80173280_1 *)arg3)->unk_46 &= 0x7FFF;
    return;

state_1:
    if (func_8003F270()) {
        ((S_80173280_3 *)tile)->unk_14 |= 0x800;
        return;
    }
    ((S_80173280_3 *)tile)->unk_14 &= 0xF7FF;
    ((S_80173280_0 *)arg0)->unk_9B++;
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

    ((S_80173280_0 *)arg0)->unk_9E--;
    if ((s16)((S_80173280_0 *)arg0)->unk_9E == 1) {
        ((S_80173280_3 *)tile)->unk_14 |= 0x800;
    }
    if (((S_80173280_0 *)arg0)->unk_96.u == 5) {
        ((S_80173280_3 *)tile)->unk_14 &= 0xF7FF;
    }
    ((S_80173280_0 *)arg0)->unk_96.s--;
    if ((s16)((S_80173280_0 *)arg0)->unk_96.s > 0 &&
        !(((S_80173280_3 *)tile)->unk_14 & 0xE000)) {
        goto done;
    }
    ((S_80173280_0 *)arg0)->unk_98 |= 0x80;
    ((S_80173280_0 *)arg0)->unk_9B++;
    ((S_80173280_3 *)tile)->unk_14 |= 0x800;
    ((S_80173280_0 *)arg0)->unk_96.s = 0x14;
    return;

state_3:
    kindp = D_80083460;
    if (((S_80173280_7 *)kindp)->unk_0C == 0) {
        ((S_80173280_0 *)arg0)->unk_96.s = 0;
    }
    ((S_80173280_0 *)arg0)->unk_96.s--;
    if ((s16)((S_80173280_0 *)arg0)->unk_96.s <= 0) {
        *(volatile u16 *)((u8 *)arg0 + 0x96) = 0;
        ((S_80173280_3 *)tile)->unk_14 &= 0xF7FF;
    }
    if (!(((S_80173280_3 *)tile)->unk_14 & 0xE000)) {
        goto done;
    }
    ((S_80173280_4 *)arg1)->unk_14 = 0;
    ((S_80173280_4 *)arg1)->unk_10 = 0;
    ((S_80173280_4 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80173280_3 *)tile)->unk_24, ((S_80173280_3 *)tile)->unk_25);
    if (((S_80173280_3 *)tile)->unk_2C != D_80175988) {
        u8 *table = D_80175988;
        (*(u8 * *)((u8 *)tile + 0x2C)) = table;
        func_80047784(tile,
            table[((D_80083228 + ((S_80173280_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80173280_3 *)tile)->unk_14 &= 0xF7FF;
    }
    if (((S_80173280_7 *)kindp)->unk_0C != 0) {
        goto done;
    }
    ((S_80173280_7 *)kindp)->unk_0A--;
    ((S_80173280_0 *)arg0)->unk_8C = D_801717F4;
    func_800A4ACC(arg3);
    ((S_80173280_1 *)arg3)->unk_73.s = 0;
    ((S_80173280_1 *)arg3)->unk_72.s = 0;
    ((S_80173280_1 *)arg3)->unk_6D--;
    ((S_80173280_1 *)arg3)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}
