#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

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
    register u8 *entry ASM_REG("$3");
    u8 *table;
    u8 *control;
    s32 mode;
    s32 flagged_kind;
    s32 kind;
    register s32 v0 ASM_REG("$2");
    s32 y;
    void *object;

    state_id = FIELD(arg0, u8, 0x9B);
    mode = 0;
    (void)jt_keep;

    switch (state_id) {
    case 0:
        if (FIELD(arg3, u32, 0x1C) & 0x2000) {
            flagged_kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
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
            kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
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
            v0 = FIELD(arg0, u16, 0x98) & 0xFF7F;
            FIELD(arg0, u16, 0x98) = v0;
            v0 = mode;
            ASM_KEEP(v0);
            if (v0 != 0) {
                v0 = (s32)D_800814A8;
                FIELD(arg3, void *, 0x60) = (void *)v0;
                goto set_from_object;
            } else {
                register u8 *base ASM_REG("$3") = D_8006DE24;
                v0 = (s32)(base + *choice * 20);
                if (((u8 *)v0)[0x12] == 2) {
                    v0 = (s32)FIELD(arg3, void *, 0x60);
                    if (v0 != 0) {
set_from_object:
                        entry = (u8 *)FIELD(v0, void *, -0x14);
                        FIELD(arg3, u8, 0x72) = entry[0x24];
                        FIELD(arg3, u8, 0x73) = entry[0x25];
                    }
                } else {
                    FIELD(arg3, void *, 0x60) = func_800A05A4(
                        arg3,
                        FIELD(arg2, u8, 0x24),
                        FIELD(arg2, u8, 0x25),
                        FIELD(arg3, s16, 0x2A),
                        0x10);
                    v0 = FIELD(arg3, s8, 0x72);
                    y = FIELD(arg3, s8, 0x73);
                    if (v0 < 0) {
                        v0 = -v0;
                    }
                    if (y < 0) {
                        y = -y;
                    }
                    FIELD(arg3, u8, 0x72) = v0;
                    FIELD(arg3, u8, 0x73) = y;
                }
            }

            if (func_800A94A0(arg3, choice, mode,
                              (u16 *)((u8 *)arg0 + 0x98)) != 0) {
                FIELD(arg0, s16, 0x96) = 8;
                FIELD(arg0, u8, 0x9B)++;
            }
            return;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        D_8008346C = 0;
        FIELD(D_800814A8, u16, 0xA6)--;
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg0, u8 *, 0x8C) = D_8016A36C;
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            FIELD(arg2, u16, 0x14) |= 0x800;
            return;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg0, u8, 0x9B)++;
        func_800A56E0(0x703);
        /* fall through */

    case 2:
        FIELD(arg0, u16, 0x96)--;
        if ((s16)FIELD(arg0, u16, 0x96) > 0 &&
            !(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }
        FIELD(arg0, u16, 0x98) |= 0x80;
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 3:
        if (D_8008346C == 0) {
            FIELD(arg0, s16, 0x96) = 0;
        }
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

        switch (FIELD(arg0, u8, 0xAC)) {
        case 0:
            object = FIELD(arg2, void *, 0x2C);
            table = D_801739A0;
            break;
        case 1:
            object = FIELD(arg2, void *, 0x2C);
            table = D_801739A8;
            break;
        case 2:
            object = FIELD(arg2, void *, 0x2C);
            table = D_801739B0;
            break;
        case 3:
            object = FIELD(arg2, void *, 0x2C);
            table = D_801739B8;
            break;
        default:
            goto finish;
        }

        if ((u8 *)object != table) {
            FIELD(arg2, u8 *, 0x2C) = table;
            func_80047784(
                arg2,
                *(u8 *)((unsigned long)(((D_80083228 +
                    FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7) +
                    (unsigned long)table),
                0);
        }

finish:
        control = (u8 *)&D_80083460;
        if (FIELD(control, s32, 0x0C) != 0) {
            return;
        }
        FIELD(control, u16, 0x0A)--;
        FIELD(arg0, u8 *, 0x8C) = D_8016A36C;
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
        return;

    default:
        return;
    }
}
