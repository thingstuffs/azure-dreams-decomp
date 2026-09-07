#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_80170D28(void *, s32, s32, s32, s32, s32, s32);
extern void func_80170F2C(void *, s32, s32, s32, s32, s32, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern void *D_80170868[];
extern u8 D_80171650[];
extern u8 D_801742C8[];

void func_80173078(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const state_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4
    };
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *selection;
    s32 special;
    s32 next_state;
    u8 state;
    void *active;

    special = 0;
    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 5) {
        goto end;
    }
    (void)state_keep;
    goto *D_80170850[state];

state_0:
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        u32 dispatch;

        dispatch = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
        if (dispatch >= 7) {
            goto kind_default;
        }
        (void)kind_keep;
        goto *D_80170868[dispatch];

kind_5:
        special = 1;
        goto kind_3;
kind_6:
        special = 1;
        goto kind_2;
kind_7:
        special = 1;
        goto kind_1;
    }

    {
        s32 type;

        type = FIELD(arg3, u16, 0x46) & 0x3FFF;
        if (type == 2) {
            goto kind_2;
        }
        if (type < 3) {
            selection = 0;
            if (type == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (type != 3) {
            selection = 0;
            goto selection_ready;
        }
    }

kind_3:
    selection = (u8 *)arg3 + 0xE;
    goto selection_ready;
kind_2:
    selection = (u8 *)arg3 + 0xB;
    goto selection_ready;
normal_kind_1:
    ASM_KEEP(selection);
kind_1:
    selection = (u8 *)arg3 + 8;
    goto selection_ready;
kind_default:
    selection = 0;

selection_ready:
    if (*selection == 0) {
        goto empty_selection;
    }
    FIELD(arg0, u16, 0x98) &= 0xFF7F;
    ASM_KEEP(selection);
    {
        register s32 special_test ASM_REG("$2");

        special_test = special;
        ASM_KEEP(special_test);
        if (special_test != 0) {
            active = D_800814A8;
            FIELD(arg3, void *, 0x60) = active;
            goto copy_active_coords;
        }
    }
    ASM_KEEP(selection);

    {
        u8 item;

        item = *selection;
        if (D_8006DE24[item * 20 + 0x12] == 2) {
            active = FIELD(arg3, void *, 0x60);
            if (active != 0) {
                register u8 *linked ASM_REG("$3");

copy_active_coords:
                linked = FIELD(active, void *, -0x14);
                ASM_KEEP(linked);
                FIELD(arg3, u8, 0x72) = FIELD(linked, u8, 0x24);
                FIELD(arg3, u8, 0x73) = FIELD(linked, u8, 0x25);
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(arg3, s16, 0x2A), 0x10);
            FIELD(arg3, void * volatile, 0x60) = active;
            ASM_KEEP(active);
            dx = FIELD(arg3, s8, 0x72);
            dy = FIELD(arg3, s8, 0x73);
            if (dx < 0) {
                dx = -dx;
            }
            if (dy < 0) {
                dy = -dy;
            }
            FIELD(arg3, u8, 0x72) = dx;
            FIELD(arg3, u8, 0x73) = dy;
        }
    }

invoke_item:
    if (func_800A94A0(arg3, selection, special, (u8 *)arg0 + 0x98) == 0) {
        goto end;
    }
    next_state = FIELD(arg0, u8, 0x9B) + 1;
    goto store_next_state;

empty_selection:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = D_80171650;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        goto end;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);

state_2:
    {
        u16 flags;
        s16 timer;

        flags = FIELD(arg2, u16, 0x14);
        if (flags & 0x8000) {
            next_state = FIELD(arg0, u8, 0x9B) + 1;
            FIELD(arg0, u16, 0x96) = 0;
store_next_state:
            FIELD(arg0, u8, 0x9B) = next_state;
            goto end;
        }
        if (FIELD(arg2, s8, 4) == 2 && (flags & 0x1000)) {
            FIELD(arg2, u16, 0x14) = flags | 0x800;
            FIELD(arg0, u16, 0x96) = 0x16;
        }
        if (FIELD(arg2, s8, 4) < 2) {
            goto end;
        }
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer <= 0) {
            FIELD(arg0, u16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B)++;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        if (FIELD(arg0, s16, 0x96) < 7) {
            goto end;
        }
    }

    special = 0;
state_4:
    {
        s32 color;
        register s32 x ASM_REG("$17");
        register s32 y ASM_REG("$16");
        s16 z;

        special++;
        color = (rand() & 0xFF) | 0x80;
        x = rand();
        x &= 0x7F;
        x -= 0x40;
        x = (s16)x;
        y = rand();
        y &= 0x7F;
        y -= 0x40;
        y = (s16)y;
        z = (rand() & 0x7F) - 0x40;
        func_80170D28((u8 *)arg0 - 0x20, 0, 0x00C0C0C0,
                      color, x, y, z);
        if ((u16)special < 5) {
            goto state_4;
        }
    }
    goto end;

state_3:
    if ((FIELD(arg2, s8, 4) == 4 &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        FIELD(arg0, u16, 0x96) = 0x20;
        FIELD(arg0, u16, 0x98) |= 0x80;
        FIELD(arg0, u8, 0x9B)++;
        special = 0;
        do {
            s32 color;

            special++;
            color = (rand() & 0xFF) | 0x80;
            func_80170F2C((u8 *)arg0 - 0x20, 0, 0x00C0C0C0,
                          color, 0, 0, 0);
        } while ((u16)special < 20);
        ASM_KEEP(special);
    }
    {
        u8 *global;
        s16 timer;

        global = (u8 *)&D_80083460;
        if (FIELD(global, s32, 0x0C) == 0) {
            FIELD(arg0, u16, 0x96) = 0;
        }
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer <= 0) {
            FIELD(arg0, u16, 0x96) = 0;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto end;
        }
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        if (FIELD(arg2, u8 *, 0x2C) != D_801742C8) {
            u8 *table;
            s32 index;

            table = D_801742C8;
            FIELD(arg2, u8 *, 0x2C) = table;
            index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            func_80047784(arg2, table[index], 0);
        }
        if (FIELD(global, s32, 0x0C) != 0) {
            goto end;
        }
        FIELD(global, u16, 0x0A)--;
        FIELD(arg0, void *, 0x8C) = D_80171650;
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

end:
    return;
}
