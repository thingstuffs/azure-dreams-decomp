#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_80170A44(void *, void *, void *, void *);
extern void func_801731F4(void) __attribute__((noreturn));
extern void func_80173268(void) __attribute__((noreturn));

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern void *D_801708B0[];
extern s32 D_801714D4[];
extern u8 D_801740E0[];
extern u8 D_80174110[];
extern u8 D_80174118[];

void func_80172A48(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *held_arg0 ASM_REG("$16") = arg0;
    register void *held_arg1 ASM_REG("$20") = arg1;
    register void *held_arg2 ASM_REG("$19") = arg2;
    register void *held_arg3 ASM_REG("$18") = arg3;
    static void *volatile state_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3,
        &&state_4, &&state_5, &&state_6, &&state_7,
        &&state_8, &&end, &&end, &&end,
        &&end, &&end, &&end, &&end,
        &&state_16, &&state_17, &&state_18, &&state_19,
        &&state_20, &&state_21, &&state_22, &&state_23
    };
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    register u8 *selection ASM_REG("$17");
    s32 special;
    s32 call_special;
    register s32 next_state ASM_REG("$2");
    u8 state;
    void *active;

#define arg0 held_arg0
#define arg1 held_arg1
#define arg2 held_arg2
#define arg3 held_arg3

    ASM_KEEP(held_arg0);
    ASM_KEEP(held_arg1);
    ASM_KEEP(held_arg2);
    ASM_KEEP(held_arg3);

    special = 0;
    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 24) {
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
        goto *D_801708B0[dispatch];

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
    call_special = special;
    ASM_KEEP_NV(call_special);
    if (func_800A94A0(arg3, selection, call_special, (u8 *)arg0 + 0x98) == 0) {
        goto end;
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    if ((u32)(*selection - 0x2E) >= 3) {
        goto end;
    }
    if (call_special == 1) {
        goto end;
    }
    FIELD(arg0, u8, 0x9B) = 0x10;
    return;

empty_selection:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = D_801714D4;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    return;

state_1:
    if (func_8003F270()) {
        goto set_actor_flag;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state_2:
    {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer + 1;
        if ((s16)timer < 8) {
            ASM_SCHED_BARRIER();
            if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
                goto end;
            }
        }
    }
    ASM_SCHED_BARRIER();
    next_state = FIELD(arg0, u8, 0x9B) + 1;
    FIELD(arg0, u16, 0x96) = 0;
    ASM_SCHED_BARRIER();
    ASM_TAILSLOT_PIN(next_state);
    func_80173268();

state_3:
    if (FIELD(arg0, s16, 0xA2) != 0) {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer + 1;
        if ((s16)timer < 15) {
            ASM_SCHED_BARRIER();
            if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
                goto end;
            }
        }
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);
    ASM_SCHED_BARRIER();
    {
        register void *model_base ASM_REG("$5") = D_80174110;
        ASM_SCHED_BARRIER();
        ASM_TAILSLOT_PIN(model_base);
        func_801731F4();
    }

state_4:
    func_80170A44(arg0, arg1, arg2, arg3);
    {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer + 1;
        if ((s16)timer < 3) {
            ASM_SCHED_BARRIER();
            if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
                goto end;
            }
        }
    }
    FIELD(arg2, u16, 0x14) |= 0x800;
    next_state = FIELD(arg0, u8, 0x9B) + 1;
    ASM_SCHED_BARRIER();
    ASM_TAILSLOT_PIN(next_state);
    func_80173268();

state_5:
    FIELD(arg2, u16, 0x14) |= 0x800;
    {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer + 1;
        if ((s16)timer < 10) {
            ASM_SCHED_BARRIER();
            if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
                goto end;
            }
        }
    }
    ASM_SCHED_BARRIER();
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    return;

state_6:
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u16, 0x98) |= 0x80;
    FIELD(arg0, u8, 0x9B)++;
    return;

state_7:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg0, u8, 0x9B)++;
    if (FIELD(arg2, u8 *, 0x2C) == D_801740E0) {
        goto end;
    }
    {
        u8 *model = D_801740E0;

        FIELD(arg2, void *, 0x2C) = model;
        func_80047784(arg2,
            model[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    FIELD(arg0, u16, 0x9E) = 0;
    FIELD(arg0, s16, 0x92) = -0x20;
    return;

state_8:
    {
        u8 *global;

        global = (u8 *)&D_80083460;
        if (FIELD(global, s32, 0x0C) != 0) {
            goto end;
        }
        FIELD(global, u16, 0x0A)--;
        FIELD(arg0, void *, 0x8C) = D_801714D4;
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
    }
    return;

state_16:
    if (func_8003F270()) {
set_actor_flag:
        FIELD(arg2, u16, 0x14) |= 0x800;
        return;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state_17:
    {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer + 1;
        if ((s16)timer < 8 &&
            !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            goto end;
        }
    }
    next_state = FIELD(arg0, u8, 0x9B) + 1;
    FIELD(arg0, u16, 0x96) = 0;
    ASM_TAILSLOT_PIN(next_state);
    func_80173268();

state_18:
    if (FIELD(arg0, s16, 0xA2) != 0) {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer + 1;
        if ((s16)timer < 15 &&
            !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            goto end;
        }
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);
    {
        register void *model_base ASM_REG("$5") = D_80174110;
        ASM_TAILSLOT_PIN(model_base);
        func_801731F4();
    }

state_19:
    func_80170A44(arg0, arg1, arg2, arg3);
    {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer + 1;
        if ((s16)timer < 2 &&
            !(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto end;
        }
    }
    FIELD(arg2, u16, 0x14) |= 0x800;
    next_state = FIELD(arg0, u8, 0x9B) + 1;
    ASM_TAILSLOT_PIN(next_state);
    func_80173268();

state_20:
    FIELD(arg2, u16, 0x14) |= 0x800;
    if (FIELD(arg0, s16, 0x96) < 5) {
        func_80170A44(arg0, arg1, arg2, arg3);
    }
    {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer + 1;
        if ((s16)timer < 10 &&
            !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            goto end;
        }
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u16, 0x98) |= 0x80;
    return;

state_21:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    {
        register u8 *model_base ASM_REG("$5") = D_80174118;

        FIELD(arg2, void *, 0x2C) = model_base;
        func_80047784(arg2,
            model_base[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    return;

state_22:
    {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = timer + 1;
        if ((s16)timer < 5) {
            goto end;
        }
    }
    next_state = FIELD(arg0, u8, 0x9B) + 1;
    FIELD(arg0, u16, 0x96) = 0;
    ASM_TAILSLOT_PIN(next_state);
    func_80173268();

state_23:
    next_state = 6;
    FIELD(arg0, u16, 0x96) = 0;

store_next_state:
    FIELD(arg0, u8, 0x9B) = next_state;

end:
    return;
}
