#include "common.h"

typedef struct S_800BCE78_0 {
    u8 pad_00[0x68];
    s16 unk_68;
    u8 pad_6A[0x2];
    u16 unk_6C;
    u8 pad_6E[0x32];
    s32 unk_A0;
    u8 pad_A4[0x8];
    s32 unk_AC;
} S_800BCE78_0;   /* arg0 in func_800BCE78 */

typedef struct S_800BCE78_1 {
    s32 unk_00;
    u8 pad_04[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    union { s32 s; volatile s32 u; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    s32 unk_14;
} S_800BCE78_1;   /* arg1 in func_800BCE78 */

typedef struct S_800BCE78_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800BCE78_2;   /* arg2 in func_800BCE78 */



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
    register s32 arg_31 ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 state_34 ASM_REG("$6");   /* MATCH pin: keeps a constant in a register as retail does */

    callback = 0;
    if ((func_800352FC() != 0) && (func_800C2AB4(arg0) != 0)) {
        if (!(((S_800BCE78_0 *)arg0)->unk_AC & 1)) {
            func_80053DA8(0x60B);
            ((S_800BCE78_0 *)arg0)->unk_AC |= 1;
        }
    } else {
        ((S_800BCE78_0 *)arg0)->unk_AC &= ~1;
    }

    state = ((S_800BCE78_0 *)arg0)->unk_68;
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
        s32 random;
        s32 result;
        register s32 rem;
        register s32 dx;
        s32 abs_dx;
        register s32 vx;

        ((S_800BCE78_1 *)arg1)->unk_08.at02.v = func_800C2AE8(arg1);
        if (!(((S_800BCE78_2 *)arg2)->unk_14 & 0x6000)) {
            goto tail;
        }
        result = rand();
        random = result;
        ASM_KEEP(result);   /* MATCH pin: retail register colouring depends on it */
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
            ((S_800BCE78_0 *)arg0)->unk_68 = state_10;
            ((S_800BCE78_0 *)arg0)->unk_6C = (rand() % 2) + 2;
            goto random_done;

random_case_1: {
            s32 limit;
            s32 case_vx;

            ((S_800BCE78_0 *)arg0)->unk_68 = 0x20;
            ((S_800BCE78_2 *)arg2)->unk_14 |= 0x800;
            ((S_800BCE78_0 *)arg0)->unk_6C = (rand() & 1) + 2;
            limit = 0x1FFFFF;
            ((S_800BCE78_1 *)arg1)->unk_14 = -0x30000;
            dx = ((S_800BCE78_1 *)arg1)->unk_00;
            dx -= ((S_800BCE78_0 *)arg0)->unk_A0;
            abs_dx = __builtin_abs(dx);
            limit = limit < abs_dx;
            if (!limit) {
                ((S_800BCE78_1 *)arg1)->unk_0C.s = 0x10000;
                if (!(rand() & 1)) {
                    goto case_1_after_store;
                }
                case_vx = -((S_800BCE78_1 *)arg1)->unk_0C.s;
                goto case_1_store;
            } else {
                case_vx = -0x10000;
                if (dx < 0) {
                    case_vx = 0x10000;
                }
            }
case_1_store:
            ((S_800BCE78_1 *)arg1)->unk_0C.s = case_vx;
case_1_after_store:
            if (((S_800BCE78_1 *)arg1)->unk_0C.s > 0) {
                ((S_800BCE78_2 *)arg2)->unk_14 |= 1;
            } else {
                ((S_800BCE78_2 *)arg2)->unk_14 &= 0xFFFE;
            }
            goto random_done;
        }

random_case_2: {
            s32 limit;
            s32 rng_result;
            s32 *case_callback;

            case_callback = D_800E9ECC;
            callback = case_callback;
            ((S_800BCE78_0 *)arg0)->unk_68 = 0x30;
            rng_result = rand();
            limit = 0xFFFFF;
            vx = (rng_result & 0x1FF) << 8;
            ((S_800BCE78_1 *)arg1)->unk_0C.s = vx;
            dx = ((S_800BCE78_1 *)arg1)->unk_00;
            dx -= ((S_800BCE78_0 *)arg0)->unk_A0;
            abs_dx = __builtin_abs(dx);
            limit = limit < abs_dx;
            if (!limit) {
                if (rand() & 1) {
                    ((S_800BCE78_1 *)arg1)->unk_0C.u = ((S_800BCE78_1 *)arg1)->unk_0C.s;
                } else {
                    ((S_800BCE78_1 *)arg1)->unk_0C.s = -((S_800BCE78_1 *)arg1)->unk_0C.s;
                }
            } else if (dx > 0) {
                ((S_800BCE78_1 *)arg1)->unk_0C.s = -vx;
            }
            if (((S_800BCE78_1 *)arg1)->unk_0C.s > 0) {
                ((S_800BCE78_2 *)arg2)->unk_14 |= 1;
            } else {
                ((S_800BCE78_2 *)arg2)->unk_14 &= 0xFFFE;
            }
            ((S_800BCE78_1 *)arg1)->unk_14 = -0x20000;
            goto random_done;
        }

random_case_4:
            ((S_800BCE78_0 *)arg0)->unk_68 = 0x40;
            ((S_800BCE78_0 *)arg0)->unk_6C = 0x14;
            ((S_800BCE78_2 *)arg2)->unk_14 |= 0x800;
random_done:
        goto tail;
    }

case_10: {
        register u16 timer;

        if (((S_800BCE78_2 *)arg2)->unk_14 & 0x6000) {
            timer = ((S_800BCE78_0 *)arg0)->unk_6C - 1;
            ((S_800BCE78_0 *)arg0)->unk_6C = timer;
            if ((s16)timer <= 0) {
                ((S_800BCE78_0 *)arg0)->unk_68 = 0;
            }
            callback = (s32 *)D_800E9E7C;
        }
        goto tail;
    }

case_20: {
        void *call_arg;
        register s32 x ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 vx ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
        s32 y;
        register s32 vy ASM_REG("$6");   /* MATCH pin: keeps a constant in a register as retail does */
        register s32 floor ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 compare ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        register u16 timer;

        call_arg = arg1;
        ASM_KEEP(call_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
        x = ((S_800BCE78_1 *)arg1)->unk_00;
        vx = ((S_800BCE78_1 *)arg1)->unk_0C.s;
        y = ((S_800BCE78_1 *)arg1)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)arg1)->unk_14;
        x += vx;
        y += vy;
        ((S_800BCE78_1 *)arg1)->unk_00 = x;
        {
            register s32 new_vy ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

            new_vy = vy;
            ASM_KEEP(new_vy);   /* MATCH pin: retail delay-slot fill depends on it */
            ((S_800BCE78_1 *)arg1)->unk_08.at00.v = y;
            y = 0x10000;
            new_vy += y;
            ((S_800BCE78_1 *)arg1)->unk_14 = new_vy;
        }
        floor = func_800C2AE8(call_arg);
        compare = floor < ((S_800BCE78_1 *)arg1)->unk_08.at02.v;
        if (compare) {
            ((S_800BCE78_1 *)arg1)->unk_08.at02.v = floor;
            timer = ((S_800BCE78_0 *)arg0)->unk_6C - 1;
            ((S_800BCE78_0 *)arg0)->unk_6C = timer;
            if ((s16)timer <= 0) {
                ((S_800BCE78_1 *)arg1)->unk_14 = 0;
                ((S_800BCE78_1 *)arg1)->unk_0C.s = 0;
                ((S_800BCE78_2 *)arg2)->unk_14 &= 0xF7FF;
                ((S_800BCE78_0 *)arg0)->unk_68 = 0;
            } else {
                ((S_800BCE78_1 *)arg1)->unk_14 = -0x30000;
            }
        }
        goto tail;
    }

case_30: {
        s32 vy;
        s32 new_vy;

        {
            register s32 x ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            s32 vx;

            x = ((S_800BCE78_1 *)arg1)->unk_00;
            vx = ((S_800BCE78_1 *)arg1)->unk_0C.s;
            vy = ((S_800BCE78_1 *)arg1)->unk_14;
            x += vx;
            new_vy = vy;
            ASM_KEEP(new_vy);   /* MATCH pin: retail delay-slot fill depends on it */
            ((S_800BCE78_1 *)arg1)->unk_00 = x;
        }
        {
            register s32 y ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

            y = ((S_800BCE78_1 *)arg1)->unk_08.at00.v;
            new_vy -= 0x4000;
            ((S_800BCE78_1 *)arg1)->unk_14 = new_vy;
            y += vy;
            ((S_800BCE78_1 *)arg1)->unk_08.at00.v = y;
        }
        if (((S_800BCE78_2 *)arg2)->unk_14 & 0x6000) {
            callback = D_800E9E34;
            ((S_800BCE78_0 *)arg0)->unk_68 = arg_31;
            ((S_800BCE78_0 *)arg0)->unk_6C = 3;
        }
        goto tail;
    }

case_31: {
        register s32 x;
        register s32 vx;
        register s32 y;
        register s32 vy;
        register u16 timer;

        x = ((S_800BCE78_1 *)arg1)->unk_00;
        vx = ((S_800BCE78_1 *)arg1)->unk_0C.s;
        y = ((S_800BCE78_1 *)arg1)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)arg1)->unk_14;
        ((S_800BCE78_1 *)arg1)->unk_00 = x + vx;
        ((S_800BCE78_1 *)arg1)->unk_08.at00.v = y + vy;
        if (((S_800BCE78_2 *)arg2)->unk_14 & 0x6000) {
            timer = ((S_800BCE78_0 *)arg0)->unk_6C - 1;
            ((S_800BCE78_0 *)arg0)->unk_6C = timer;
            if ((s16)timer <= 0) {
                callback = D_800E9E34;
                ((S_800BCE78_1 *)arg1)->unk_14 = -0x10000;
                ((S_800BCE78_1 *)arg1)->unk_0C.s >>= 1;
                ((S_800BCE78_0 *)arg0)->unk_68 = 0x32;
                ((S_800BCE78_0 *)arg0)->unk_6C = (rand() & 3) + 3;
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
        s32 height;
        s32 floor_scaled;
        register s16 floor;
        register u16 timer;

        x = ((S_800BCE78_1 *)arg1)->unk_00;
        vx = ((S_800BCE78_1 *)arg1)->unk_0C.s;
        y = ((S_800BCE78_1 *)arg1)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)arg1)->unk_14;
        ((S_800BCE78_1 *)arg1)->unk_00 = x + vx;
        ((S_800BCE78_1 *)arg1)->unk_08.at00.v = y + vy;
        if (((S_800BCE78_2 *)arg2)->unk_14 & 0x6000) {
            timer = ((S_800BCE78_0 *)arg0)->unk_6C - 1;
            ((S_800BCE78_0 *)arg0)->unk_6C = timer;
            if ((s16)timer <= 0) {
                ((S_800BCE78_0 *)arg0)->unk_6C = 8;
                new_vx = -((S_800BCE78_1 *)arg1)->unk_0C.s;
                ((S_800BCE78_1 *)arg1)->unk_0C.s = new_vx;
                if (new_vx > 0) {
                    ((S_800BCE78_2 *)arg2)->unk_14 |= 1;
                } else {
                    ((S_800BCE78_2 *)arg2)->unk_14 &= 0xFFFE;
                }
                floor = func_800C2AE8(arg1);
                floor_scaled = (s32)floor << 16;
                height = ((S_800BCE78_1 *)arg1)->unk_08.at00.v;
                ASM_KEEP(height);   /* MATCH pin: keeps a statement from moving across a call/branch */
                height = height + 0x100000;
                ((S_800BCE78_1 *)arg1)->unk_14 =
                    (floor_scaled - height) /
                    (s16)((S_800BCE78_0 *)arg0)->unk_6C;
                callback = D_800E9E14;
                ((S_800BCE78_0 *)arg0)->unk_68 = 0x33;
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

        x = ((S_800BCE78_1 *)arg1)->unk_00;
        vx = ((S_800BCE78_1 *)arg1)->unk_0C.s;
        y = ((S_800BCE78_1 *)arg1)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)arg1)->unk_14;
        ((S_800BCE78_1 *)arg1)->unk_00 = x + vx;
        ((S_800BCE78_1 *)arg1)->unk_08.at00.v = y + vy;
        if (((S_800BCE78_2 *)arg2)->unk_14 & 0x6000) {
            callback = D_800E9E14;
        }
        timer = ((S_800BCE78_0 *)arg0)->unk_6C - 1;
        ((S_800BCE78_0 *)arg0)->unk_6C = timer;
        if ((s16)timer <= 0) {
            callback = D_800E9E54;
            ((S_800BCE78_1 *)arg1)->unk_14 = 0;
            ((S_800BCE78_1 *)arg1)->unk_0C.s = 0;
            ((S_800BCE78_0 *)arg0)->unk_68 = state_34;
        }
        goto tail;
    }

case_34: {
        register s16 floor;

        ((S_800BCE78_1 *)arg1)->unk_00 += ((S_800BCE78_1 *)arg1)->unk_0C.s;
        floor = func_800C2AE8(arg1);
        ((S_800BCE78_1 *)arg1)->unk_08.at02.v =
            (u16)((S_800BCE78_1 *)arg1)->unk_08.at02.v + ((floor - ((S_800BCE78_1 *)arg1)->unk_08.at02.v) >> 1);
        if (((S_800BCE78_2 *)arg2)->unk_14 & 0x6000) {
            callback = (s32 *)D_800E9E7C;
            ((S_800BCE78_0 *)arg0)->unk_68 = 0;
        }
        goto tail;
    }

case_40: {
        register u16 timer;

        timer = ((S_800BCE78_0 *)arg0)->unk_6C - 1;
        ((S_800BCE78_0 *)arg0)->unk_6C = timer;
        if ((s16)timer <= 0) {
            ((S_800BCE78_0 *)arg0)->unk_68 = 0;
            ((S_800BCE78_2 *)arg2)->unk_14 &= 0xF7FF;
        }
        goto tail;
    }

case_FF:
        func_8008F134(arg0, arg_31, state_34);
        func_80033D08(arg0);
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto tail;

tail:
    func_800478B8(arg2);
    if (callback != 0) {
        func_8003DB94(arg2, callback, 0);
    }
}
