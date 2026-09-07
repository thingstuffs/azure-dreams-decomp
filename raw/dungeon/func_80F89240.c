#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s16);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800DAE44(void *, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern u8 D_80171138[];
extern u8 D_80174AD4[];

void func_80172A40(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&slot_one, &&slot_two, &&slot_three, &&slot_none,
        &&special_one, &&special_two, &&special_three
    };
    register void *owner ASM_REG("$19") = arg0;
    register void *motion ASM_REG("$21") = arg1;
    register void *actor ASM_REG("$18") = arg2;
    register void *object ASM_REG("$17") = arg3;
    register s32 special ASM_REG("$20");
    register u8 *selector ASM_REG("$16");
    s32 state;
    s32 kind;
    s32 special_copy;
    u8 *entry;
    register u8 *entry_base ASM_REG("$3");
    register void *target ASM_REG("$2");
    void *record;
    s32 x;
    s32 y;
    s32 index;
    s32 item_id;
    u8 *status;

    ASM_KEEP_NV(owner);
    ASM_KEEP_NV(motion);
    ASM_KEEP_NV(actor);
    ASM_KEEP_NV(object);

#define arg0 owner
#define arg1 motion
#define arg2 actor
#define arg3 object

    state = FIELD(arg0, u8, 0x9B);
    special = 0;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        index = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
        if ((u32)index >= 7U) {
            goto slot_none;
        }
        (void)keepalive;
        goto *(((void **)D_80170838)[index]);

special_one:
        special = 1;
        goto slot_three;
special_two:
        special = 1;
        goto slot_two;
special_three:
        special = 1;
        goto slot_one;
    }

    kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
    if (kind == 2) {
        goto slot_two;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto slot_one;
        }
        selector = 0;
        goto selected;
    }
    if (kind == 3) {
        goto slot_three;
    }
    selector = 0;
    goto selected;

slot_three:
    selector = (u8 *)arg3 + 0xE;
    goto selected;
slot_two:
    selector = (u8 *)arg3 + 0xB;
    goto selected;
slot_one:
    selector = (u8 *)arg3 + 8;
    goto selected;
slot_none:
    selector = 0;

selected:
    if (*selector != 0) {
        FIELD(arg0, u16, 0x98) &= 0xFF7F;

        special_copy = special;
        ASM_KEEP(special_copy);
        if (special_copy) {
            target = D_800814A8;
            FIELD(arg3, void *, 0x60) = target;
            goto copy_record;
        }

        entry_base = D_8006DE24;
        item_id = *selector;
        entry = entry_base + item_id * 20;
        ASM_KEEP(entry_base);
        if (entry[0x12] == 2) {
            target = FIELD(arg3, void *, 0x60);
            if (target == 0) {
                goto move_setup;
            }
copy_record:
            record = FIELD(target, void *, -0x14);
            ASM_KEEP(target);
            FIELD(arg3, u8, 0x72) = FIELD(record, u8, 0x24);
            FIELD(arg3, u8, 0x73) = FIELD(record, u8, 0x25);
            goto move_setup;
        }

        FIELD(arg3, void *, 0x60) = func_800A05A4(
            arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            FIELD(arg3, s16, 0x2A), 0x10);
        ASM_KEEP(object);

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
        if (func_800A94A0(arg3, selector, special,
                          (u16 *)((u8 *)arg0 + 0x98)) == 0) {
            return;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        func_800DAE44(arg1, 4);
        func_800A56E0(0x703);
        FIELD(arg0, u16, 0x96) = 4;
        FIELD(arg0, u8, 0x9B)++;
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
        FIELD(arg3, u32, 0x1C) &= 0xFFFBFFFF;
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
    FIELD(arg0, void *, 0x8C) = D_80171138;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    return;

state_one:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        return;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state_two:
    FIELD(arg0, s16, 0x92) +=
        (-0x30 - FIELD(arg0, s16, 0x92)) >> 3;
    FIELD(arg0, u16, 0x96)--;
    if (FIELD(arg0, s16, 0x96) > 0) {
        if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
            return;
        }
    }
    FIELD(arg0, u16, 0x98) |= 0x80;
    if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
        return;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, u32, 0x1C) |= 0x08000000;
    FIELD(arg3, u32, 0x1C) |= 0x00040000;

    if (FIELD(arg2, u8 *, 0x2C) != D_80174AD4) {
        FIELD(arg2, u8 *, 0x2C) = D_80174AD4;
        func_80047784(arg2,
                      D_80174AD4[((D_80083228 +
                                   FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                      FIELD(arg0, s16, 0xA0));
    }

    status = (u8 *)&D_80083460;
    if (FIELD(status, s32, 0xC) != 0) {
        return;
    }
    FIELD(status, u16, 0xA)--;
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, void *, 0x8C) = D_80171138;
    func_800A4ACC(arg3);
    if (FIELD(arg3, s8, 0x6D) > 0) {
        FIELD(arg3, u8, 0x6D)--;
    }
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);

#undef arg0
#undef arg1
#undef arg2
#undef arg3
}
