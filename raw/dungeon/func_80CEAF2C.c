#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003F270();
extern void func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_80171790();
extern void func_80171928();
extern void func_80174840() __attribute__((noreturn));
extern void func_80174848() __attribute__((noreturn));
extern void func_80174850() __attribute__((noreturn));
extern void func_8017485C() __attribute__((noreturn));
extern void func_801748CC() __attribute__((noreturn));
extern void func_80174930() __attribute__((noreturn));
extern void func_80174B84() __attribute__((noreturn));
extern void func_80174BC4() __attribute__((noreturn));

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern u8 D_801724BC[];
extern u8 D_80175E24[];
extern u8 D_80175E2C[];
extern u8 D_80175E34[];

void func_8017472C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_none,
        &&special_1, &&special_2, &&special_3
    };
    s32 state;
    register s32 special ASM_REG("$21");
    s32 kind;
    register u8 *choice ASM_REG("$16");
    void *object;
    register void *record ASM_REG("$3");
    s32 x;
    s32 y;
    u16 timer;
    register s32 i ASM_REG("$16");
    register u8 *table ASM_REG("$5");
    register void *state3_object ASM_REG("$3");
    register u32 state3_page ASM_REG("$2");
    register s32 slot_carrier ASM_REG("$4");
    u8 *control;

    state = FIELD(arg0, u8, 0x9B);
    special = 0;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    ASM_SCHED_BARRIER();
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    return;

state_0:
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        kind = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
        if ((u32)kind >= 7U) {
            goto kind_none;
        }
        (void)keepalive;
        goto *D_80170850[kind];

special_3:
        special = 1;
        ASM_TAILSLOT_PIN(special);
        func_80174840();
        return;
special_2:
        special = 1;
        ASM_TAILSLOT_PIN(special);
        func_80174848();
        return;
special_1:
        special = 1;
        ASM_TAILSLOT_PIN(special);
        func_80174850();
        return;
    }

    kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
    if (kind == 2) {
        goto kind_2;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto kind_1;
        }
        choice = 0;
        ASM_KEEP(choice);
        func_8017485C();
        return;
    }
    if (kind != 3) {
        goto kind_none;
    }

kind_3:
    choice = (u8 *)arg3 + 0xE;
    ASM_TAILSLOT_PIN(choice);
    func_8017485C();
    return;
kind_2:
    choice = (u8 *)arg3 + 0xB;
    ASM_TAILSLOT_PIN(choice);
    func_8017485C();
    return;
kind_1:
    ASM_SCHED_BARRIER();
    choice = (u8 *)arg3 + 8;
    ASM_TAILSLOT_PIN(choice);
    func_8017485C();
    return;

kind_none:
    choice = 0;

    if (*choice != 0) {
        FIELD(arg0, u16, 0x98) &= 0xFF7F;
        if (special != 0) {
            FIELD(arg3, void *, 0x60) = D_800814A8;
            func_801748CC();
            return;
        }

        if (D_8006DE24[*choice * 20 + 0x12] == 2) {
            object = FIELD(arg3, void *, 0x60);
            if (object == 0) {
                goto move_setup;
            }
            record = FIELD(object, void *, -0x14);
            ASM_KEEP(record);
            FIELD(arg3, u8, 0x72) = FIELD(record, u8, 0x24);
            FIELD(arg3, u8, 0x73) = FIELD(record, u8, 0x25);
            func_80174930();
            return;
        }

        object = func_800A05A4(
            arg3,
            FIELD(arg2, u8, 0x24),
            FIELD(arg2, u8, 0x25),
            FIELD(arg3, s16, 0x2A),
            0x10);
        FIELD(arg3, void *, 0x60) = object;
        ASM_SCHED_BARRIER();
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

move_setup:
        if (func_800A94A0(arg3, choice, special,
                          (u8 *)arg0 + 0x98) == 0) {
            return;
        }
        FIELD(arg0, u16, 0x96) = 0x16;
        FIELD(arg0, s16, 0xAE) = 0xE;
        FIELD(arg0, u8, 0x9B)++;
        return;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = D_801724BC;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    return;

state_1:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        return;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);

state_2:
    ASM_SET(slot_carrier);
    i = 0;
    if (!(FIELD(arg0, u16, 0x96) & 1) &&
        FIELD(arg0, s16, 0xAE) != 0) {
        FIELD(arg0, u16, 0xAE)--;
        ASM_SET(i);
        i = 0;
        ASM_USE(slot_carrier);
    }
    do {
        func_80171790(arg0, arg1, arg2, arg3);
        i++;
    } while (i < 10);

    if (FIELD(arg0, s16, 0x96) == 0x16) {
        func_80171928(arg0, arg1, arg2);
    }
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((s32)(timer << 16) > 0 &&
        !(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    FIELD(arg0, u16, 0x98) |= 0x80;
    FIELD(arg0, u8, 0x9B)++;
    return;

state_3:
    if (D_8008346C == 0) {
        FIELD(arg0, u16, 0x96) = 0;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    kind = FIELD(arg3, u8, 0x48);
    if (kind == 0xE) {
        goto state3_kind_e;
    }
    if (kind < 0xF) {
        if (kind == 0xD) {
            goto state3_kind_d;
        }
        {
            state3_page = 0x80080000;
            ASM_KEEP(state3_page);
            state3_object = (u8 *)state3_page + 0x3460;
            ASM_TAILSLOT_PIN(state3_object);
            func_80174BC4();
            return;
        }
    }
    if (kind == 0xF) {
        goto state3_kind_f;
    }
    {
        state3_page = 0x80080000;
        ASM_KEEP(state3_page);
        state3_object = (u8 *)state3_page + 0x3460;
        ASM_TAILSLOT_PIN(state3_object);
        func_80174BC4();
        return;
    }

state3_kind_d:
        ASM_SCHED_BARRIER();
        state3_object = FIELD(arg2, void *, 0x2C);
        state3_page = 0x80170000;
        ASM_KEEP(state3_page);
        table = (u8 *)state3_page + 0x5E24;
        ASM_KEEP(state3_object);
        ASM_TAILSLOT_PIN(table);
        func_80174B84();
        return;
state3_kind_e:
        state3_object = FIELD(arg2, void *, 0x2C);
        state3_page = 0x80170000;
        ASM_KEEP(state3_page);
        table = (u8 *)state3_page + 0x5E2C;
        ASM_KEEP(state3_object);
        ASM_TAILSLOT_PIN(table);
        func_80174B84();
        return;
state3_kind_f:
        ASM_SCHED_BARRIER();
        state3_object = FIELD(arg2, void *, 0x2C);
        state3_page = 0x80170000;
        ASM_KEEP(state3_page);
        table = (u8 *)state3_page + 0x5E34;

    if (state3_object != table) {
        FIELD(arg2, u8 *, 0x2C) = table;
        func_80047784(
            arg2,
            *(u8 *)((((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7) + (u32)table),
            0);
    }

    control = (u8 *)&D_80083460;
    if (FIELD(control, s32, 0xC) != 0) {
        return;
    }
    FIELD(control, u16, 0xA)--;
    FIELD(arg0, void *, 0x8C) = D_801724BC;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);
}
