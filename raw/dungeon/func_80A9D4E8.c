#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[16];
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern u8 D_80170E7C;
extern u8 D_80174C3C[8];
extern u8 D_80174C7C[8];

extern s32 func_8003F270();
extern void func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_800DA840();

void func_80172CE8(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[7] = {
        &&item_8, &&item_b, &&item_e, &&item_none,
        &&item_8, &&item_b, &&item_e
    };
    u16 pos[3];
    s32 special;
    u8 *item;
    void *node;
    u8 state;

    special = 0;
    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
        if (FIELD(arg3, u32, 0x1C) & 0x2000) {
            u32 kind = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
            if (kind >= 7) {
                goto item_none;
            }
            (void)jt_keep;
            goto *(((void **)D_80170838)[kind]);
item_e:
            special = 1;
            goto item_e_value;
item_b:
            special = 1;
            goto item_b_value;
item_8:
            special = 1;
            goto item_8_value;
        }

        {
            s32 kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
            if (kind == 2) {
                goto item_b_value;
            }
            if (kind < 3) {
                item = 0;
                if (kind == 1) {
                    goto item_8_value;
                }
                goto item_ready;
            }
            item = 0;
            if (kind != 3) {
                goto item_ready;
            }
item_e_value:
            item = (u8 *)arg3 + 0xE;
            goto item_ready;
item_b_value:
            item = (u8 *)arg3 + 0xB;
            goto item_ready;
item_8_value:
            item = (u8 *)arg3 + 8;
            goto item_ready;
item_none:
            item = 0;
        }

item_ready:
        if (*item == 0) {
            goto no_item;
        }

        FIELD(arg0, u16, 0x98) &= 0xFF7F;
        ASM_SCHED_BARRIER();
        {
            register s32 special_test ASM_REG("$2");

            special_test = special;
            ASM_KEEP(special_test);
            if (special_test) {
                node = D_800814A8;
                FIELD(arg3, void *, 0x60) = node;
                goto copy_existing;
            }
        }

        {
            u8 *entry_base = D_8006DE24;
            u8 id = *item;
            u8 *entry = entry_base + id * 20;
            if (entry[0x12] == 2) {
                node = FIELD(arg3, void *, 0x60);
                if (node != 0) {
copy_existing:
                    {
                        register u8 *owner ASM_REG("$3");

                        owner = FIELD(node, u8 *, -0x14);
                        ASM_KEEP(owner);
                        FIELD(arg3, u8, 0x72) = FIELD(owner, u8, 0x24);
                        FIELD(arg3, u8, 0x73) = FIELD(owner, u8, 0x25);
                    }
                    goto object_ready;
                }
            } else {
                s32 x;
                s32 y;

                node = func_800A05A4(
                    arg3,
                    FIELD(arg2, u8, 0x24),
                    FIELD(arg2, u8, 0x25),
                    FIELD(arg3, s16, 0x2A),
                    0x10);
                FIELD(arg3, void * volatile, 0x60) = node;
                ASM_KEEP(node);
                x = FIELD(arg3, s8, 0x72);
                y = FIELD(arg3, s8, 0x73);
                if (x < 0) {
                    x = -x;
                }
                if (y < 0) {
                    y = -y;
                }
                FIELD(arg3, s8, 0x72) = x;
                FIELD(arg3, s8, 0x73) = y;
            }
        }

object_ready:
        pos[0] = FIELD(arg1, u16, 2);
        pos[1] = FIELD(arg1, u16, 6);
        pos[2] = FIELD(arg1, u16, 0xA);
        if (func_800A94A0(arg3, item, special, (u8 *)arg0 + 0x98)) {
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DA840(pos, (s16)((*item - 1) % 3));
            goto increment_state;
        }
        goto end;

no_item:
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        D_8008346C = 0;
        {
            u8 *global_obj = (u8 *)D_800814A8;
            FIELD(global_obj, u16, 0xA6)--;
        }
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg0, void *, 0x8C) = &D_80170E7C;
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        goto end;

    case 1:
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto end;
        }
        FIELD(arg2, void *, 0x2C) = D_80174C7C;
        func_80047784(
            arg2,
            D_80174C7C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
increment_state:
        FIELD(arg0, u8, 0x9B)++;
        goto end;

    case 2:
        if (func_8003F270()) {
            FIELD(arg2, u16, 0x14) |= 0x800;
            goto end;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg0, u8, 0x9B)++;
        /* fall through */

    case 3:
        if ((FIELD(arg2, s8, 4) == 5 &&
             (FIELD(arg2, u16, 0x14) & 0x1000)) ||
            (FIELD(arg2, u16, 0x14) & 0xE000)) {
            FIELD(arg2, u16, 0x14) |= 0x800;
            FIELD(arg0, u16, 0x96) = 0x10;
            FIELD(arg0, u16, 0x98) |= 0x80;
        }

        {
            u16 timer = FIELD(arg0, u16, 0x96) - 1;
            FIELD(arg0, u16, 0x96) = timer;
            if ((s16)timer <= 0) {
                FIELD(arg0, u16, 0x96) = 0;
                FIELD(arg2, u16, 0x14) &= 0xF7FF;
            }
        }

        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto end;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

        if (FIELD(arg2, void *, 0x2C) != D_80174C3C) {
            FIELD(arg2, void *, 0x2C) = D_80174C3C;
            func_80047784(
                arg2,
                D_80174C3C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }

        {
            u8 *global_state = D_80083460;
            if (FIELD(global_state, s32, 0xC) != 0) {
                goto end;
            }
            FIELD(global_state, u16, 0xA)--;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg0, void *, 0x8C) = &D_80170E7C;
        func_800A4ACC(arg3);
        if (FIELD(arg3, s8, 0x6D) > 0) {
            FIELD(arg3, u8, 0x6D)--;
        }
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
        break;

    default:
        break;
    }

end:
    return;
}
