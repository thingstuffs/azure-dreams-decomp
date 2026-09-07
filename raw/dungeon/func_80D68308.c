#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_801711DC(void *, s32, s32);
extern void func_8017145C(void *, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_800E2348[];
extern u8 D_800E2388[8];
extern u8 D_800E2398[8];
extern void *D_80170850[];
extern u8 D_80170870[20];
extern s32 D_80171F1C;

void func_80173B08(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const state_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3,
        &&state_4, &&state_5, &&state_6, &&state_7
    };
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *selection;
    register u8 *table ASM_REG("$5");
    register u32 page_entry ASM_REG("$2");
    register s32 special ASM_REG("$18");
    s16 counter;
    u8 state;
    void *active;

    special = 0;
    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 8) {
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
        goto *(((void **)D_80170870)[dispatch]);

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
    ASM_KEEP(special);
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

    {
        u8 item;

        item = *selection;
        if (D_8006DE24[item * 20 + 0x12] == 2) {
            active = FIELD(arg3, void *, 0x60);
            if (active != 0) {
                register void *linked ASM_REG("$3");

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
    if (func_800A94A0(arg3, selection, special,
                      (u8 *)arg0 + 0x98) == 0) {
        goto end;
    }
    FIELD(arg0, u8, 0x9B)++;
    goto end;

empty_selection:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = &D_80171F1C;
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
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, u32, 0x1C) &= 0xFFFBFFFF;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg2, s16, 0x10) = 0x20;
    FIELD(arg2, u16, 0x14) |= 0xC;

state_3:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 7;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        FIELD(arg0, u16, 0x98) |= 0x80;
        goto end;
    }
    {
        s16 floor;

        floor = func_800BCB04(FIELD(arg1, u16, 2),
                              FIELD(arg1, u16, 6),
                              (s16)(FIELD(arg3, u16, 0x88) - 0x20));
        if ((FIELD(arg0, s16, 0x92) -
             (s16)(floor - FIELD(arg3, u16, 0x88))) != 0) {
            goto end;
        }
    }
    table = D_800E2398;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    ASM_SCHED_BARRIER();
    page_entry = 0x80080000;
    goto update_table;

state_4:
    {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer + 1;
        if (timer < 12 && !(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto end;
        }
    }
    FIELD(arg0, u16, 0x98) |= 0x80;
    FIELD(arg2, u16, 0x14) |= 0x800;
    FIELD(arg0, u16, 0x96) = 0x12;
    FIELD(arg0, u8, 0x9B)++;
    counter = 0;
    do {
        func_801711DC((u8 *)arg0 - 0x20,
                      FIELD(arg3, s16, 0x2A), 0xE0E0E0);
        counter++;
    } while ((s16)counter < 3);
    goto end;

state_5:
    if (D_8008346C == 0) {
        FIELD(arg0, u16, 0x96) = 0;
    }
    if (FIELD(arg0, s16, 0x96) >= 10) {
        counter = 0;
        do {
            func_801711DC((u8 *)arg0 - 0x20,
                          FIELD(arg3, s16, 0x2A), 0xE0E0E0);
            counter++;
        } while ((s16)counter < 3);
    }
    if ((u32)(FIELD(arg0, u16, 0x96) - 10) < 7) {
        register s32 next ASM_REG("$2");

        special = 0;
        do {
            s16 shifted;

            shifted = special;
            next = shifted;
            if (next != FIELD(arg3, s16, 0x2A)) {
                counter = 0;
                do {
                    func_8017145C((u8 *)arg0 - 0x20, shifted);
                    counter++;
                } while ((s16)counter <= 0);
                next = special + 0x200;
            } else {
                next = special + 0x200;
            }
            special = next;
            ASM_KEEP(next);
        } while ((s16)next < 0x1000);
    }
    {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer > 0 && !(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto end;
        }
    }
    table = D_800E2388;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    {
        u16 flags;

        flags = FIELD(arg0, u16, 0x98);
        flags |= 8;
        FIELD(arg0, u8, 0x9B)++;
        ASM_SCHED_BARRIER();
        page_entry = 0x80080000;
        FIELD(arg0, u16, 0x98) = flags;
    }
    goto update_table;

update_table:
    {
        FIELD(arg2, u8 *, 0x2C) = table;
        page_entry = (u32)(((FIELD((void *)page_entry, s16, 0x3228) +
                              FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7) +
                     (u32)table;
        ASM_KEEP_NV(page_entry);
        func_80047784(arg2, *(u8 *)page_entry, 0);
    }
    goto end;

state_6:
    if (FIELD(arg0, s16, 0x92) >= -0x1F) {
        FIELD(arg0, u16, 0x92) -= 4;
        goto end;
    }
    FIELD(arg0, u8, 0x9B)++;

state_7:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    if (FIELD(arg2, u8 *, 0x2C) != D_800E2348) {
        FIELD(arg2, u8 *, 0x2C) = D_800E2348;
        func_80047784(
            arg2,
            D_800E2348[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u16, 0x9E) = 0;
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg3, u32, 0x1C) |= 0x40000;
        FIELD(arg0, s16, 0x92) = -0x20;
        FIELD(arg2, u16, 0x14) &= 0xFFF3;
    }
    {
        u8 *global;

        global = (u8 *)&D_80083460;
        if (FIELD(global, s32, 0x0C) != 0) {
            goto end;
        }
        FIELD(global, u16, 0x0A)--;
        FIELD(arg0, void *, 0x8C) = &D_80171F1C;
        func_800A4ACC(arg3);
    }
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);

end:
    return;
}
