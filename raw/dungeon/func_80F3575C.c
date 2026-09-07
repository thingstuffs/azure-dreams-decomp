#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u8 pad0[0x12];
    u8 kind;
    u8 pad13;
} MotionEntry;

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170E94[];
extern u8 D_80174A7C[];

void func_80172F5C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u16 pending[3];
    register u8 *sel ASM_REG("$16");
    register s32 special ASM_REG("$20");
    void *obj;
    register void *rec ASM_REG("$3");
    s32 x;
    s32 y;
    s32 counter;
    u8 *block;

    special = 0;
    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        if (FIELD(arg3, u32, 0x1C) & 0x2000) {
            static void *const sw_keep[] = {&&sw_c, &&sw_b, &&sw_a, &&sel_none};
            extern void *const D_80170878[];
            u32 swi = (u32)((FIELD(arg3, u16, 0x46) & 0x3FFF) - 1);

            if (swi >= 7) {
                goto sel_none;
            }
            (void)sw_keep;
            goto *D_80170878[swi];
        sw_c:
            special = 1;
            goto kind_c;
        sw_b:
            special = 1;
            goto kind_b;
        sw_a:
            special = 1;
            goto kind_a;
        }

        switch (FIELD(arg3, u16, 0x46) & 0x3FFF) {
        case 3:
        kind_c:
            sel = (u8 *)arg3 + 0xE;
            break;
        case 2:
        kind_b:
            sel = (u8 *)arg3 + 0xB;
            break;
        case 1:
        kind_a:
            sel = (u8 *)arg3 + 8;
            break;
        default:
        sel_none:
            sel = (u8 *)0;
            break;
        }

        if (*sel != 0) {
            FIELD(arg0, u16, 0x98) &= 0xFF7F;
            ASM_KEEP(sel);
            {
                s32 flag = special;

                ASM_KEEP(flag);
                if (flag != 0) {
                    obj = D_800814A8;
                    FIELD(arg3, void *, 0x60) = obj;
                    goto have_obj;
                }
            }
            if (((MotionEntry *)D_8006DE24)[*sel].kind == 2) {
                obj = FIELD(arg3, void *, 0x60);
                if (obj == 0) {
                    goto do_step;
                }
            have_obj:
                rec = FIELD(obj, void *, -0x14);
                FIELD(arg3, u8, 0x72) = FIELD(rec, u8, 0x24);
                FIELD(arg3, u8, 0x73) = FIELD(rec, u8, 0x25);
                goto do_step;
            }
            FIELD(arg3, void *, 0x60) =
                func_800A05A4(arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                              FIELD(arg3, s16, 0x2A), 0x10);
            ASM_KEEP(arg3);
            x = FIELD(arg3, s8, 0x72);
            y = FIELD(arg3, s8, 0x73);
            if (x < 0) {
                x = -x;
            }
            if (y < 0) {
                y = -y;
            }
            FIELD(arg3, u8, 0x72) = x;
            FIELD(arg3, u8, 0x73) = y;
        do_step:
            pending[0] = FIELD(arg1, u16, 2);
            pending[1] = FIELD(arg1, u16, 6);
            pending[2] = FIELD(arg1, u16, 0xA);
            if (func_800A94A0(arg3, sel, special, (u8 *)arg0 + 0x98) == 0) {
                return;
            }
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
            func_800A56E0(0x703);
            FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
            return;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        D_8008346C = 0;
        FIELD(D_800814A8, u16, 0xA6) = FIELD(D_800814A8, u16, 0xA6) - 1;
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x6D) = FIELD(arg3, u8, 0x6D) - 1;
        FIELD(arg0, void *, 0x8C) = D_80170E94;
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
        FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
    case 2:
        if ((FIELD(arg2, s8, 4) == 6 && (FIELD(arg2, u16, 0x14) & 0x1000)) ||
            (FIELD(arg2, u16, 0x14) & 0xE000)) {
            FIELD(arg2, u16, 0x14) |= 0x800;
            FIELD(arg0, u16, 0x98) |= 0x80;
        }
        if ((FIELD(arg2, s8, 4) == 7 && (FIELD(arg2, u16, 0x14) & 0x1000)) ||
            (FIELD(arg2, u16, 0x14) & 0x8000)) {
            FIELD(arg2, u16, 0x14) |= 0x800;
            FIELD(arg0, u16, 0x96) = 8;
        }
        counter = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = counter;
        if ((s16)counter <= 0) {
            FIELD(arg0, u16, 0x96) = 0;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
            return;
        }
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        {
            u8 *table = D_80174A7C;

            if (FIELD(arg2, u8 *, 0x2C) != table) {
                FIELD(arg2, u8 *, 0x2C) = table;
                func_80047784(arg2,
                    table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
        }
        block = (u8 *)&D_80083460;
        if (FIELD(block, s32, 0xC) != 0) {
            return;
        }
        FIELD(block, u16, 0xA) = FIELD(block, u16, 0xA) - 1;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg0, void *, 0x8C) = D_80170E94;
        func_800A4ACC(arg3);
        if (FIELD(arg3, s8, 0x6D) > 0) {
            FIELD(arg3, u8, 0x6D) = FIELD(arg3, u8, 0x6D) - 1;
        }
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}
