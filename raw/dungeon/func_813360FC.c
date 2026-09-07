#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_8016D4B8(void *, s32, void *, void *);

extern u8 *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[];
extern u16 D_80083462;
extern u8 D_8016A36C[];
extern u8 D_80173AC8[];
extern u8 D_80173AD0[];

void func_8016D0FC(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    register void *object ASM_REG("$16") = arg2;
    register u8 *counter_base ASM_REG("$2");
    register u16 count ASM_REG("$3");
    register u8 *table_direct ASM_REG("$5");
    void *actor = arg3;
    u8 *table_compare;
    u8 *current;
    s32 state;
    s32 kind;
    s32 flags;
    s32 index;

    ASM_KEEP_NV(object);
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
    goto done;

state_0:
    if (!(FIELD(object, u16, 0x14) & 0xE000)) {
        goto done;
    }
    counter_base = D_80083460;
    count = FIELD(counter_base, u16, 0xA);
    count--;
    FIELD(counter_base, u16, 0xA) = count;
    kind = FIELD(arg0, u8, 0xAC);
    if (kind == 0xE) {
        goto set_ac8_pre;
    }
    if (kind < 0xF) {
        if (kind == 0xD) {
            goto set_ac8;
        }
        goto increment_state;
    }
    if (kind != 0xF) {
        goto increment_state;
    }
set_ac8_pre:
set_ac8:
    table_direct = D_80173AC8;
    FIELD(object, u8 *, 0x2C) = table_direct;
    index = (D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9;
    func_80047784(object, table_direct[index & 7], 0);
    goto increment_state;

state_1:
    kind = FIELD(arg0, u8, 0xAC);
    if (kind == 0xE) {
        goto maybe_set_ac8;
    }
    if (kind < 0xF) {
        if (kind == 0xD) {
            goto maybe_set_ac8;
        }
        goto after_ac8;
    }
    if (kind != 0xF) {
        goto after_ac8;
    }
maybe_set_ac8:
    current = FIELD(object, u8 *, 0x2C);
    table_compare = D_80173AC8;
    if (current != table_compare) {
        FIELD(object, u8 *, 0x2C) = table_compare;
        index = (D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9;
        func_80047784(object, table_compare[index & 7], 0);
    }
after_ac8:
    if (FIELD(actor, u8, 0x25) != 0) {
        kind = FIELD(arg0, u8, 0xAC);
        if (kind == 0xE) {
            goto set_ad0;
        }
        if (kind < 0xF) {
            goto kind_lt_15;
        }
        goto kind_ge_15;
    }
    if (D_80083462 & 0x1000) {
        goto done;
    }
    if (FIELD(actor, s16, 0x64) != 0) {
        if (func_800AA6B4(arg0, arg1, object, 0) != 0) {
            goto done;
        }
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        goto done;
    }
    flags = FIELD(actor, s32, 0x1C);
    if (flags & 0x100) {
        func_800AA258(arg0, arg1, object, actor);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(arg0, arg1, object, actor);
        func_8016D4B8(arg0, arg1, object, actor);
        goto done;
    }
    if (FIELD(actor, s8, 0x6D) == 0) {
        goto done;
    }
    if ((func_800A2C34(actor) << 16) != 0) {
        if ((func_8009A180(actor, FIELD(D_800814A8, u8 *, 0x58) + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(actor);
    func_800A9A04(actor);
    if (FIELD(actor, u8, 0x25) == 0) {
        goto done;
    }
    kind = FIELD(arg0, u8, 0xAC);
    if (kind == 0xE) {
        goto set_ad0;
    }
    if (kind < 0xF) {
kind_lt_15:
        if (kind == 0xD) {
            goto set_ad0;
        }
        counter_base = D_80083460;
        goto increment_counter;
    }
kind_ge_15:
    counter_base = D_80083460;
    if (kind != 0xF) {
        goto increment_counter_pre;
    }
set_ad0:
    table_direct = D_80173AD0;
    FIELD(object, u8 *, 0x2C) = table_direct;
    index = (D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9;
    func_80047784(object, table_direct[index & 7], 0);
increment_counter_pre:
    counter_base = D_80083460;
increment_counter:
    count = FIELD(counter_base, u16, 0xA);
    count++;
    FIELD(counter_base, u16, 0xA) = count;
increment_state:
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_2:
    if (FIELD(object, u16, 0x14) & 0xE000) {
        counter_base = D_80083460;
        count = FIELD(counter_base, u16, 0xA);
        count--;
        FIELD(counter_base, u16, 0xA) = count;
        FIELD(arg0, u8 *, 0x8C) = D_8016A36C;
    }
done:
    return;
}
