#include "common.h"

typedef struct S_8016C190_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016C190_0;   /* arg0 in func_8016C190 */

typedef struct S_8016C190_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
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
} S_8016C190_1;   /* arg3 in func_8016C190 */

typedef struct S_8016C190_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016C190_2_pre;   /* the 0x14 bytes before v0 in func_8016C190, addressed as v0[-1] */

typedef struct S_8016C190_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8016C190_3;   /* arg2 in func_8016C190 */

typedef struct S_8016C190_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016C190_4;   /* arg1 in func_8016C190 */

typedef struct S_8016C190_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8016C190_5;   /* control in func_8016C190 */



extern s32 func_8003F270();
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_8016A36C[];
extern u8 D_801739A0[];
extern u8 D_801739A8[];
extern u8 D_801739B0[];
extern u8 D_801739B8[];
extern void *D_80164960[];

void func_8016C190(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&select_1, &&select_2, &&select_3, &&select_none,
        &&mode_select_1, &&mode_select_2, &&mode_select_3
    };
    u8 state_id;
    u8 *choice;
    register u8 *entry ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *table;
    u8 *control;
    s32 mode;
    s32 flagged_kind;
    s32 kind;
    register s32 v0 ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 y;
    void *object;

    state_id = ((S_8016C190_0 *)arg0)->unk_9B;
    mode = 0;
    (void)jt_keep;

    switch (state_id) {
    case 0:
        if (((S_8016C190_1 *)arg3)->unk_1C & 0x2000) {
            flagged_kind = ((S_8016C190_1 *)arg3)->unk_46 & 0x3FFF;
            if ((u32)(flagged_kind - 1) < 7) {
                goto *D_80164960[(u32)(flagged_kind - 1)];
            }
            goto select_none;

mode_select_3:
            mode = 1;
            goto select_3;
mode_select_2:
            mode = 1;
            goto select_2;
mode_select_1:
            mode = 1;
            goto select_1;
        } else {
            kind = ((S_8016C190_1 *)arg3)->unk_46 & 0x3FFF;
            switch (kind) {
            case 1:
                goto select_1;
            case 2:
                goto select_2;
            case 3:
                goto select_3;
            default:
                goto select_none;
            }
        }

select_3:
        choice = (u8 *)arg3 + 0xE;
        goto selection_done;
select_2:
        choice = (u8 *)arg3 + 0xB;
        goto selection_done;
select_1:
        choice = (u8 *)arg3 + 8;
        goto selection_done;
select_none:
        choice = 0;
selection_done:
        if (*choice != 0) {
            v0 = ((S_8016C190_0 *)arg0)->unk_98 & 0xFF7F;
            ((S_8016C190_0 *)arg0)->unk_98 = v0;
            v0 = mode;
            if (v0 != 0) {
                v0 = (s32)D_800814A8;
                ((S_8016C190_1 *)arg3)->unk_60 = (void *)v0;
                goto set_from_object;
            } else {
                u8 *base = D_8006DE24;
                v0 = (s32)(base + *choice * 20);
                if (((u8 *)v0)[0x12] == 2) {
                    v0 = (s32)((S_8016C190_1 *)arg3)->unk_60;
                    if (v0 != 0) {
set_from_object:
                        entry = (u8 *)((S_8016C190_2_pre *)v0)[-1].unk_00;
                        ((S_8016C190_1 *)arg3)->unk_72.s = entry[0x24];
                        ((S_8016C190_1 *)arg3)->unk_73.s = entry[0x25];
                    }
                } else {
                    ((S_8016C190_1 *)arg3)->unk_60 = func_800A05A4(
                        arg3,
                        ((S_8016C190_3 *)arg2)->unk_24,
                        ((S_8016C190_3 *)arg2)->unk_25,
                        ((S_8016C190_1 *)arg3)->unk_2A,
                        0x10);
                    v0 = ((S_8016C190_1 *)arg3)->unk_72.u;
                    y = ((S_8016C190_1 *)arg3)->unk_73.u;
                    if (v0 < 0) {
                        v0 = -v0;
                    }
                    if (y < 0) {
                        y = -y;
                    }
                    ((S_8016C190_1 *)arg3)->unk_72.s = v0;
                    ((S_8016C190_1 *)arg3)->unk_73.s = y;
                }
            }

            if (func_800A94A0(arg3, choice, mode,
                              (u16 *)((u8 *)arg0 + 0x98)) != 0) {
                ((S_8016C190_0 *)arg0)->unk_96.s = 8;
                ((S_8016C190_0 *)arg0)->unk_9B++;
            }
            return;
        }

        ((S_8016C190_4 *)arg1)->unk_14 = 0;
        ((S_8016C190_4 *)arg1)->unk_10 = 0;
        ((S_8016C190_4 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_8016C190_3 *)arg2)->unk_24, ((S_8016C190_3 *)arg2)->unk_25);
        D_8008346C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        func_800A4ACC(arg3);
        ((S_8016C190_1 *)arg3)->unk_6D--;
        ((S_8016C190_0 *)arg0)->unk_8C = D_8016A36C;
        ((S_8016C190_1 *)arg3)->unk_73.s = 0;
        ((S_8016C190_1 *)arg3)->unk_72.s = 0;
        ((S_8016C190_1 *)arg3)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((S_8016C190_3 *)arg2)->unk_14 |= 0x800;
            return;
        }
        ((S_8016C190_3 *)arg2)->unk_14 &= 0xF7FF;
        ((S_8016C190_0 *)arg0)->unk_9B++;
        func_800A56E0(0x703);
        /* fall through */

    case 2:
        ((S_8016C190_0 *)arg0)->unk_96.u--;
        if ((s16)((S_8016C190_0 *)arg0)->unk_96.u > 0 &&
            !(((S_8016C190_3 *)arg2)->unk_14 & 0xE000)) {
            return;
        }
        ((S_8016C190_0 *)arg0)->unk_98 |= 0x80;
        ((S_8016C190_0 *)arg0)->unk_9B++;
        return;

    case 3:
        if (D_8008346C == 0) {
            ((S_8016C190_0 *)arg0)->unk_96.s = 0;
        }
        if (!(((S_8016C190_3 *)arg2)->unk_14 & 0xE000)) {
            return;
        }

        ((S_8016C190_4 *)arg1)->unk_14 = 0;
        ((S_8016C190_4 *)arg1)->unk_10 = 0;
        ((S_8016C190_4 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_8016C190_3 *)arg2)->unk_24, ((S_8016C190_3 *)arg2)->unk_25);

        switch (((S_8016C190_0 *)arg0)->unk_AC) {
        case 0:
            object = ((S_8016C190_3 *)arg2)->unk_2C;
            table = D_801739A0;
            break;
        case 1:
            object = ((S_8016C190_3 *)arg2)->unk_2C;
            table = D_801739A8;
            break;
        case 2:
            object = ((S_8016C190_3 *)arg2)->unk_2C;
            table = D_801739B0;
            break;
        case 3:
            object = ((S_8016C190_3 *)arg2)->unk_2C;
            table = D_801739B8;
            break;
        default:
            goto finish;
        }

        if ((u8 *)object != table) {
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
            func_80047784(
                arg2,
                *(u8 *)((unsigned long)(((D_80083228 +
                    ((S_8016C190_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) +
                    (unsigned long)table),
                0);
        }

finish:
        control = (u8 *)&D_80083460;
        if (((S_8016C190_5 *)control)->unk_0C != 0) {
            return;
        }
        ((S_8016C190_5 *)control)->unk_0A--;
        ((S_8016C190_0 *)arg0)->unk_8C = D_8016A36C;
        func_800A4ACC(arg3);
        ((S_8016C190_1 *)arg3)->unk_6D--;
        ((S_8016C190_1 *)arg3)->unk_73.s = 0;
        ((S_8016C190_1 *)arg3)->unk_72.s = 0;
        ((S_8016C190_1 *)arg3)->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        return;

    default:
        return;
    }
}
