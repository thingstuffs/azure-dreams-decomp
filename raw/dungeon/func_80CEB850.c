#include "common.h"

typedef s32 M2C_UNK;
#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

s32 func_80042900();
M2C_UNK func_80042B68();
M2C_UNK func_80047784();
s32 func_8009A180();
s16 func_8009FD40();
s32 func_800A2C34();
s32 func_800A6D30();
M2C_UNK func_800A9A04();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
M2C_UNK func_80171BEC();
#ifndef NON_MATCHING
__asm__(".set func_80171BEC_returning, func_80171BEC");
extern M2C_UNK func_80171BEC_returning();
#else
#define func_80171BEC_returning func_80171BEC
#endif
M2C_UNK func_801759A0();

extern u8 *D_800814A8[];
extern u8 D_80082E80[];
extern s16 D_80083228[];
extern u8 D_80083460[];
extern u8 D_801724BC[];
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];
extern u8 D_80175E6C[];
extern u8 D_80175E74[];
extern u8 D_80175E7C[];

void func_80175050(M2C_UNK *arg0, M2C_UNK arg1, void *arg2_in, M2C_UNK *arg3_in) {
    register u8 *temp_a1 ASM_REG("$5");
    u8 *state1_callback;
    register u8 *old_callback ASM_REG("$3");
    register M2C_UNK *state0_arg0 ASM_REG("$4");
    register M2C_UNK *var_v0 ASM_REG("$2");
    M2C_UNK *state1_base;
    M2C_UNK *arg3;
    register void *arg2 ASM_REG("$17");
    s32 flags;
    s32 state;
    s32 kind;
    s8 floor;

    arg3 = arg3_in;
    arg2 = arg2_in;
    ASM_KEEP_NV(arg2);
    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto done;
        }
        kind = FIELD(arg3, u8, 0x48);
        if (kind == 14) {
            goto state0_kind_14;
        }
        if (kind < 15) {
            if (kind == 13) {
                goto state0_kind_13;
            }
            goto state0_default_low;
        }
        if (kind == 15) {
            goto state0_kind_15;
        }
        goto state0_default_high;
state0_kind_13:
        temp_a1 = D_80175E54;
        goto state0_notify;
state0_kind_14:
        temp_a1 = D_80175E5C;
        goto state0_notify;
state0_kind_15:
        temp_a1 = D_80175E64;
state0_notify:
        ASM_KEEP_NV(temp_a1);
        FIELD(arg2, u8 *, 0x2C) = temp_a1;
        var_v0 = (M2C_UNK *)((((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7) + (unsigned long)temp_a1);
        ASM_KEEP_NV(var_v0);
        func_80047784(arg2, FIELD(var_v0, u8, 0), 0);
        state0_arg0 = arg0;
        var_v0 = (M2C_UNK *)D_80083460;
        goto state0_decrement;
state0_default_low:
        state0_arg0 = arg0;
        var_v0 = (M2C_UNK *)D_80083460;
        goto state0_decrement;
state0_default_high:
        state0_arg0 = arg0;
        var_v0 = (M2C_UNK *)D_80083460;
state0_decrement:
        ASM_KEEP_NV(state0_arg0);
        ASM_KEEP_NV(var_v0);
        FIELD(var_v0, u16, 0xA)--;
        FIELD(state0_arg0, u8, 0x9B)++;
        func_80171BEC_returning(state0_arg0, arg1, arg2);
        ASM_MEM_BARRIER();
        goto done;

    case 1:
        kind = FIELD(arg3, u8, 0x48);
        switch (kind) {
        case 13:
            old_callback = FIELD(arg2, u8 *, 0x2C);
            state1_callback = D_80175E54;
            goto state1_maybe_update;
        case 14:
            old_callback = FIELD(arg2, u8 *, 0x2C);
            state1_callback = D_80175E5C;
            goto state1_maybe_update;
        case 15:
            old_callback = FIELD(arg2, u8 *, 0x2C);
            state1_callback = D_80175E64;
            break;
        default:
            goto state1_check;
        }
state1_maybe_update:
        ASM_KEEP_NV(old_callback);
        if (old_callback != state1_callback) {
            FIELD(arg2, u8 *, 0x2C) = state1_callback;
            var_v0 = (M2C_UNK *)((((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7) + (unsigned long)state1_callback);
            ASM_KEEP_NV(var_v0);
            func_80047784(arg2, FIELD(var_v0, u8, 0), 0);
        }

state1_check:

    if ((func_80042900(arg3, 1) << 16) == 0) {
        kind = FIELD(arg3, u8, 0x48);
        ASM_SCHED_BARRIER();
        if (kind != 14) {
            if (kind < 15) {
                if (kind != 13) {
                    goto suffix;
                }
                temp_a1 = D_80175E6C;
                goto state1_notify;
            }
            goto kind_ge_15;
        } else {
            ASM_SCHED_BARRIER();
            temp_a1 = D_80175E6C + 8;
            goto state1_notify;
        }
    }

    state1_base = (M2C_UNK *)D_80083460;
    if (FIELD(state1_base, u16, 2) & 0x1000) {
        goto done;
    }
    if (FIELD(arg3, s16, 0x64) != 0 && func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
        goto done;
    }
    if (FIELD(arg3, u8, 0x25) == 0) {
        if (FIELD(state1_base, u16, 2) & 0x2008) {
            goto done;
        }
        func_800AA79C(arg0, arg1, arg2, arg3);
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        goto done;
    }
    flags = FIELD(arg3, s32, 0x1C);
    if (flags & 0x100) {
        func_800AA258(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(arg0, arg1, arg2, arg3);
        func_801759A0(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (FIELD(arg3, s8, 0x6D) == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        if ((func_8009A180(arg3, *(u8 **)(D_800814A8[0] + 0x58) + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 16) != 0) {
        register unsigned long var_a0_page ASM_REG("$2");
        register M2C_UNK *var_a0 ASM_REG("$4");
        var_a0_page = 0x80080000;
        ASM_KEEP_NV(var_a0_page);
        var_a0 = (M2C_UNK *)(var_a0_page + 0x2E80);
        ASM_KEEP_NV(var_a0);
        floor = FIELD(arg2, s8, 0x26);
        if (!((floor == FIELD(var_a0, s8, 0x26) && floor >= 0) || func_8009FD40(var_a0, arg2) < 2)) {
            goto second_check;
        }
        if (func_800A6D30(var_a0) & 7) {
            goto second_check;
        }
        func_80042B68(arg3, 1);
    }

second_check:
    if ((func_80042900(arg3, 1) << 16) != 0) {
        goto done;
    }
    kind = FIELD(arg3, u8, 0x48);
    if (kind != 14) {
        if (kind < 15) {
            if (kind == 13) {
                goto kind_13;
            }
            goto suffix;
        }
        goto kind_ge_15;
    } else {
        goto kind_14;
    }
kind_ge_15:
    if (kind == 15) {
        goto kind_15;
    }
    goto suffix;
kind_13:
    temp_a1 = D_80175E6C;
    goto state1_notify;
kind_14:
    temp_a1 = D_80175E74;
    goto state1_notify;
kind_15:
    temp_a1 = D_80175E7C;
state1_notify:
    ASM_KEEP_NV(temp_a1);
    FIELD(arg2, u8 *, 0x2C) = temp_a1;
    var_v0 = (M2C_UNK *)((((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7) + (unsigned long)temp_a1);
    ASM_KEEP_NV(var_v0);
    func_80047784(arg2, FIELD(var_v0, u8, 0), 0);

suffix:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8 *, 0x8C) = D_801724BC;
        goto done;
    }
    var_v0 = (M2C_UNK *)D_80083460;
    ASM_KEEP_NV(var_v0);
    FIELD(var_v0, u16, 0xA)++;
    FIELD(arg0, u8, 0x9B)++;

    goto done;

    case 2:
        if (FIELD(arg2, u16, 0x14) & 0xE000) {
            var_v0 = (M2C_UNK *)D_80083460;
            ASM_KEEP_NV(var_v0);
            FIELD(var_v0, u16, 0xA)--;
            FIELD(arg0, u8 *, 0x8C) = D_801724BC;
        }
        goto done;

    default:
        goto done;
    }

done:
    return;
}
