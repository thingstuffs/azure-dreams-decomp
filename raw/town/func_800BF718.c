#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_800352FC(void);
extern s32 func_800C2AB4(void *);
extern void func_80053DA8(s32);
extern s32 rand(void);
extern s16 func_800C2AE8(void *);
extern void func_8008F134(void *, s32, s32);
extern void func_80033D08(void *);
extern void func_800478B8(void *);
extern void func_8003DB94(void *, void *, s32);

extern s32 D_800814A0;
extern s32 D_800E9E14[];
extern s32 D_800E9E34[];
extern s32 D_800E9E54[];
extern u8 D_800E9E7C[];
extern s32 D_800E9ECC[];

void func_800BCE78(void *arg0, void *arg1, void *arg2)
{
    register s32 *callback;
    register s32 state;
    register s32 state_10;
    register s32 arg_31 ASM_REG("$5");
    register s32 state_34 ASM_REG("$6");

    callback = 0;
    if ((func_800352FC() != 0) && (func_800C2AB4(arg0) != 0)) {
        if (!(FIELD(arg0, s32, 0xAC) & 1)) {
            func_80053DA8(0x60B);
            FIELD(arg0, s32, 0xAC) |= 1;
        }
    } else {
        FIELD(arg0, s32, 0xAC) &= ~1;
    }

    state = FIELD(arg0, s16, 0x68);
    arg_31 = 0x31;
    if (state == arg_31) {
        goto case_31;
    }
    if (state >= 0x32) {
        goto dispatch_high;
    }
    state_10 = 0x10;
    if (state == state_10) {
        goto case_10;
    }
    if (state < 0x11) {
        if (state == 0) {
            goto case_0;
        }
        goto tail;
    }
    if (state == 0x20) {
        goto case_20;
    }
    if (state == 0x30) {
        goto case_30;
    }
    goto tail;

dispatch_high:
    state_34 = 0x34;
    if (state == state_34) {
        goto case_34;
    }
    if (state < 0x35) {
        if (state == 0x32) {
            goto case_32;
        }
        if (state == 0x33) {
            goto case_33;
        }
        goto tail;
    }
    if (state == 0x40) {
        goto case_40;
    }
    if (state == 0xFF) {
        goto case_FF;
    }
    goto tail;

case_0: {
        register s32 random ASM_REG("$3");
        register s32 result ASM_REG("$2");
        register s32 rem;
        register s32 dx;
        register s32 abs_dx ASM_REG("$2");
        register s32 vx;

        FIELD(arg1, s16, 0xA) = func_800C2AE8(arg1);
        if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
            goto tail;
        }
        result = rand();
        random = result;
        ASM_KEEP(result);
        rem = result >> 2;
        if (random < 0) {
            rem = (random + 3) >> 2;
        }
        random = random - (rem * 4);
        if (random == 1) {
            goto random_case_1;
        }
        if (random >= 2) {
            goto random_high;
        }
        if (random == 0) {
            goto random_case_0;
        }
        goto random_done;

random_high:
        if (random == 2) {
            goto random_case_2;
        }
        if (random == 4) {
            goto random_case_4;
        }
        goto random_done;

random_case_0:
            callback = (s32 *)D_800E9E7C;
            FIELD(arg0, s16, 0x68) = state_10;
            FIELD(arg0, u16, 0x6C) = (rand() % 2) + 2;
            goto random_done;

random_case_1: {
            register s32 limit ASM_REG("$3");
            register s32 case_vx ASM_REG("$2");

            FIELD(arg0, s16, 0x68) = 0x20;
            FIELD(arg2, u16, 0x14) |= 0x800;
            FIELD(arg0, u16, 0x6C) = (rand() & 1) + 2;
            limit = 0x1FFFFF;
            FIELD(arg1, s32, 0x14) = -0x30000;
            dx = FIELD(arg1, s32, 0);
            dx -= FIELD(arg0, s32, 0xA0);
            abs_dx = __builtin_abs(dx);
            limit = limit < abs_dx;
            if (!limit) {
                FIELD(arg1, s32, 0xC) = 0x10000;
                if (!(rand() & 1)) {
                    goto case_1_after_store;
                }
                case_vx = -FIELD(arg1, s32, 0xC);
                goto case_1_store;
            } else {
                case_vx = -0x10000;
                if (dx < 0) {
                    case_vx = 0x10000;
                }
            }
case_1_store:
            FIELD(arg1, s32, 0xC) = case_vx;
case_1_after_store:
            if (FIELD(arg1, s32, 0xC) > 0) {
                FIELD(arg2, u16, 0x14) |= 1;
            } else {
                FIELD(arg2, u16, 0x14) &= 0xFFFE;
            }
            goto random_done;
        }

random_case_2: {
            register s32 limit ASM_REG("$3");
            register s32 rng_result ASM_REG("$2");
            register s32 *case_callback ASM_REG("$2");

            case_callback = D_800E9ECC;
            callback = case_callback;
            FIELD(arg0, s16, 0x68) = 0x30;
            rng_result = rand();
            limit = 0xFFFFF;
            vx = (rng_result & 0x1FF) << 8;
            FIELD(arg1, s32, 0xC) = vx;
            dx = FIELD(arg1, s32, 0);
            dx -= FIELD(arg0, s32, 0xA0);
            abs_dx = __builtin_abs(dx);
            limit = limit < abs_dx;
            if (!limit) {
                if (rand() & 1) {
                    FIELD(arg1, volatile s32, 0xC) = FIELD(arg1, s32, 0xC);
                } else {
                    FIELD(arg1, s32, 0xC) = -FIELD(arg1, s32, 0xC);
                }
            } else if (dx > 0) {
                FIELD(arg1, s32, 0xC) = -vx;
            }
            if (FIELD(arg1, s32, 0xC) > 0) {
                FIELD(arg2, u16, 0x14) |= 1;
            } else {
                FIELD(arg2, u16, 0x14) &= 0xFFFE;
            }
            FIELD(arg1, s32, 0x14) = -0x20000;
            goto random_done;
        }

random_case_4:
            FIELD(arg0, s16, 0x68) = 0x40;
            FIELD(arg0, u16, 0x6C) = 0x14;
            FIELD(arg2, u16, 0x14) |= 0x800;
random_done:
        goto tail;
    }

case_10: {
        register u16 timer;

        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            timer = FIELD(arg0, u16, 0x6C) - 1;
            FIELD(arg0, u16, 0x6C) = timer;
            if ((s16)timer <= 0) {
                FIELD(arg0, s16, 0x68) = 0;
            }
            callback = (s32 *)D_800E9E7C;
        }
        goto tail;
    }

case_20: {
        register void *call_arg ASM_REG("$4");
        register s32 x ASM_REG("$2");
        register s32 vx ASM_REG("$5");
        register s32 y ASM_REG("$3");
        register s32 vy ASM_REG("$6");
        register s32 floor ASM_REG("$4");
        register s32 compare ASM_REG("$3");
        register u16 timer;

        call_arg = arg1;
        ASM_KEEP(call_arg);
        x = FIELD(arg1, s32, 0);
        vx = FIELD(arg1, s32, 0xC);
        y = FIELD(arg1, s32, 8);
        vy = FIELD(arg1, s32, 0x14);
        x += vx;
        y += vy;
        FIELD(arg1, s32, 0) = x;
        {
            register s32 new_vy ASM_REG("$2");

            new_vy = vy;
            ASM_KEEP(new_vy);
            FIELD(arg1, s32, 8) = y;
            y = 0x10000;
            new_vy += y;
            FIELD(arg1, s32, 0x14) = new_vy;
        }
        floor = func_800C2AE8(call_arg);
        compare = floor < FIELD(arg1, s16, 0xA);
        if (compare) {
            FIELD(arg1, s16, 0xA) = floor;
            timer = FIELD(arg0, u16, 0x6C) - 1;
            FIELD(arg0, u16, 0x6C) = timer;
            if ((s16)timer <= 0) {
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(arg1, s32, 0xC) = 0;
                FIELD(arg2, u16, 0x14) &= 0xF7FF;
                FIELD(arg0, s16, 0x68) = 0;
            } else {
                FIELD(arg1, s32, 0x14) = -0x30000;
            }
        }
        goto tail;
    }

case_30: {
        register s32 vy ASM_REG("$4");
        register s32 new_vy ASM_REG("$3");

        {
            register s32 x ASM_REG("$2");
            register s32 vx ASM_REG("$3");

            x = FIELD(arg1, s32, 0);
            vx = FIELD(arg1, s32, 0xC);
            vy = FIELD(arg1, s32, 0x14);
            x += vx;
            new_vy = vy;
            ASM_KEEP(new_vy);
            FIELD(arg1, s32, 0) = x;
        }
        {
            register s32 y ASM_REG("$2");

            y = FIELD(arg1, s32, 8);
            new_vy -= 0x4000;
            FIELD(arg1, s32, 0x14) = new_vy;
            y += vy;
            FIELD(arg1, s32, 8) = y;
        }
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            callback = D_800E9E34;
            FIELD(arg0, s16, 0x68) = arg_31;
            FIELD(arg0, u16, 0x6C) = 3;
        }
        goto tail;
    }

case_31: {
        register s32 x;
        register s32 vx;
        register s32 y;
        register s32 vy;
        register u16 timer;

        x = FIELD(arg1, s32, 0);
        vx = FIELD(arg1, s32, 0xC);
        y = FIELD(arg1, s32, 8);
        vy = FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0) = x + vx;
        FIELD(arg1, s32, 8) = y + vy;
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            timer = FIELD(arg0, u16, 0x6C) - 1;
            FIELD(arg0, u16, 0x6C) = timer;
            if ((s16)timer <= 0) {
                callback = D_800E9E34;
                FIELD(arg1, s32, 0x14) = -0x10000;
                FIELD(arg1, s32, 0xC) >>= 1;
                FIELD(arg0, s16, 0x68) = 0x32;
                FIELD(arg0, u16, 0x6C) = (rand() & 3) + 3;
            }
        }
        goto tail;
    }

case_32: {
        register s32 x;
        register s32 vx;
        register s32 y;
        register s32 vy;
        register s32 new_vx;
        register s32 height ASM_REG("$3");
        register s32 floor_scaled ASM_REG("$2");
        register s16 floor;
        register u16 timer;

        x = FIELD(arg1, s32, 0);
        vx = FIELD(arg1, s32, 0xC);
        y = FIELD(arg1, s32, 8);
        vy = FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0) = x + vx;
        FIELD(arg1, s32, 8) = y + vy;
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            timer = FIELD(arg0, u16, 0x6C) - 1;
            FIELD(arg0, u16, 0x6C) = timer;
            if ((s16)timer <= 0) {
                FIELD(arg0, u16, 0x6C) = 8;
                new_vx = -FIELD(arg1, s32, 0xC);
                FIELD(arg1, s32, 0xC) = new_vx;
                if (new_vx > 0) {
                    FIELD(arg2, u16, 0x14) |= 1;
                } else {
                    FIELD(arg2, u16, 0x14) &= 0xFFFE;
                }
                floor = func_800C2AE8(arg1);
                floor_scaled = (s32)floor << 16;
                ASM_KEEP(floor_scaled);
                height = FIELD(arg1, s32, 8);
                ASM_KEEP(height);
                height = height + 0x100000;
                FIELD(arg1, s32, 0x14) =
                    (floor_scaled - height) /
                    (s16)FIELD(arg0, u16, 0x6C);
                callback = D_800E9E14;
                FIELD(arg0, s16, 0x68) = 0x33;
            }
        }
        goto tail;
    }

case_33: {
        register s32 x;
        register s32 vx;
        register s32 y;
        register s32 vy;
        register u16 timer;

        x = FIELD(arg1, s32, 0);
        vx = FIELD(arg1, s32, 0xC);
        y = FIELD(arg1, s32, 8);
        vy = FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0) = x + vx;
        FIELD(arg1, s32, 8) = y + vy;
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            callback = D_800E9E14;
        }
        timer = FIELD(arg0, u16, 0x6C) - 1;
        FIELD(arg0, u16, 0x6C) = timer;
        if ((s16)timer <= 0) {
            callback = D_800E9E54;
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0xC) = 0;
            FIELD(arg0, s16, 0x68) = state_34;
        }
        goto tail;
    }

case_34: {
        register s16 floor;

        FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
        floor = func_800C2AE8(arg1);
        FIELD(arg1, s16, 0xA) =
            (u16)FIELD(arg1, s16, 0xA) + ((floor - FIELD(arg1, s16, 0xA)) >> 1);
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            callback = (s32 *)D_800E9E7C;
            FIELD(arg0, s16, 0x68) = 0;
        }
        goto tail;
    }

case_40: {
        register u16 timer;

        timer = FIELD(arg0, u16, 0x6C) - 1;
        FIELD(arg0, u16, 0x6C) = timer;
        if ((s16)timer <= 0) {
            FIELD(arg0, s16, 0x68) = 0;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        goto tail;
    }

case_FF:
        func_8008F134(arg0, arg_31, state_34);
        func_80033D08(arg0);
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto tail;

tail:
    func_800478B8(arg2);
    if (callback != 0) {
        func_8003DB94(arg2, callback, 0);
    }
}
