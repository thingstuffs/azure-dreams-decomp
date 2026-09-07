#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef s32 M2C_UNK;

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800BB044(void *);
extern void func_80174BC8(void *, void *, void *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170868[];
extern M2C_UNK D_80170E94;
extern u8 D_80175F10[8];

void func_801738B4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *entity ASM_REG("$18") = arg2;
    register void *actor ASM_REG("$17") = arg3;
    static void *const keep_cases[] = {
        &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7
    };
    u8 *item;
    s32 special;
    s32 state;
    s32 kind;
    u16 value;
    s32 x;
    s32 y;
    void *object;
    register void *copy_object ASM_REG("$2");
    register u8 *record ASM_REG("$3");
    u8 *global;

    special = 0;
    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    if (FIELD(actor, u32, 0x1C) & 0x2000) {
        kind = (FIELD(actor, u16, 0x46) & 0x3FFF) - 1;
        if ((u32)kind >= 7) {
            goto no_item;
        }
        (void)keep_cases;
        goto *D_80170868[kind];

case_7:
        special = 1;
        goto item_3;
case_6:
        special = 1;
        goto item_2;
case_5:
        special = 1;
        goto item_1;
    } else {
        kind = FIELD(actor, u16, 0x46) & 0x3FFF;
        if (kind == 2) {
            goto item_2;
        }
        if (kind < 3) {
            if (kind == 1) {
                goto item_1;
            }
            goto no_item;
        }
        if (kind == 3) {
            goto item_3;
        }
        goto no_item;
    }

case_3:
item_3:
    item = (u8 *)actor + 0x0E;
    goto have_item;
case_2:
item_2:
    item = (u8 *)actor + 0x0B;
    goto have_item;
case_1:
item_1:
    item = (u8 *)actor + 8;
    goto have_item;
case_4:
no_item:
    item = 0;

have_item:
    if (*item == 0) {
        goto empty_item;
    }

    FIELD(arg0, u16, 0x98) &= 0xFF7F;
    {
        s32 special_test = (special == 1);
        if (special_test) {
            copy_object = D_800814A8;
            FIELD(actor, void *, 0x60) = copy_object;
            goto copy_position_object;
        }
    }
    {
        u8 item_id;

        item_id = *item;
        if (D_8006DE24[item_id * 20 + 0x12] != 2) {
            goto spawn_object;
        }
    }
    copy_object = FIELD(actor, void *, 0x60);
    if (copy_object == 0) {
        goto apply_item;
    }

copy_position_object:
    ASM_USE(copy_object);
    record = FIELD(copy_object, u8 *, -0x14);
    FIELD(actor, u8, 0x72) = record[0x24];
    FIELD(actor, u8, 0x73) = record[0x25];
    goto call_item;

spawn_object:
    copy_object = func_800A05A4(actor,
        FIELD(entity, u8, 0x24),
        FIELD(entity, u8, 0x25),
        FIELD(actor, s16, 0x2A), 0x10);
    FIELD(actor, void * volatile, 0x60) = copy_object;
    ASM_USE(copy_object);
    x = FIELD(actor, s8, 0x72);
    y = FIELD(actor, s8, 0x73);
    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }
    FIELD(actor, s8, 0x72) = x;
    FIELD(actor, s8, 0x73) = y;

call_item:
apply_item:
    if (!func_800A94A0(actor, item, special, &FIELD(arg0, u16, 0x98))) {
        goto epilogue;
    }
    func_800BB044(actor);
    FIELD(arg0, u8, 0x9B)++;
    goto done;

empty_item:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(entity, u8, 0x24), FIELD(entity, u8, 0x25));
    object = D_800814A8;
    D_8008346C = 0;
    FIELD(object, u16, 0xA6)--;
    func_800A4ACC(actor);
    FIELD(actor, u8, 0x6D)--;
    FIELD(arg0, M2C_UNK *, 0x8C) = &D_80170E94;
    FIELD(actor, u8, 0x73) = 0;
    FIELD(actor, u8, 0x72) = 0;
    FIELD(actor, u16, 0x46) &= 0x7FFF;
    goto done;

state_1:
    if (func_8003F270()) {
        FIELD(entity, u16, 0x14) |= 0x0800;
        goto done;
    }
    FIELD(entity, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state_2:
    if ((FIELD(entity, s8, 4) == 3 &&
         (FIELD(entity, u16, 0x14) & 0x1000)) ||
        (FIELD(entity, u16, 0x14) & 0xE000)) {
        func_80174BC8(arg0, arg1, entity);
        FIELD(arg0, u8, 0x9B)++;
    }

state_3:
    if ((FIELD(entity, s8, 4) == 4 &&
         (FIELD(entity, u16, 0x14) & 0x1000)) ||
        (FIELD(entity, u16, 0x14) & 0xE000)) {
        FIELD(entity, u16, 0x14) |= 0x0800;
        FIELD(arg0, u16, 0x96) = 1;
        FIELD(arg0, u16, 0x98) |= 0x0080;
    }

    value = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = value;
    if ((s16)value <= 0) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(entity, u16, 0x14) &= 0xF7FF;
    }
    if (!(FIELD(entity, u16, 0x14) & 0xE000)) {
        goto epilogue;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(entity, u8, 0x24), FIELD(entity, u8, 0x25));
    if (FIELD(entity, u8 *, 0x2C) != D_80175F10) {
        FIELD(entity, u8 *, 0x2C) = D_80175F10;
        func_80047784(entity,
            D_80175F10[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    global = (u8 *)&D_80083460;
    if (FIELD(global, s32, 0x0C) != 0) {
        goto epilogue;
    }
    FIELD(global, u16, 0x0A)--;
    FIELD(arg0, M2C_UNK *, 0x8C) = &D_80170E94;
    func_800A4ACC(actor);
    FIELD(actor, u8, 0x73) = 0;
    FIELD(actor, u8, 0x72) = 0;
    FIELD(actor, u8, 0x6D)--;
    FIELD(actor, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);

done:
epilogue:
    ASM_KEEP(actor);
    ASM_KEEP(entity);
    return;
}
