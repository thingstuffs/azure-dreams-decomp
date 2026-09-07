#include "common.h"

#define FIELD(p, t, n) (*(t)((u8 *)(p) + (n)))

extern void func_80034A1C(void *, ...);
extern void func_8003EA54(void *);
extern void func_80050D68(void *);
extern s32 func_80058F88();
extern s32 func_80071494();
extern void func_8023FA58(void *, void *, ...);
extern void func_8023FB18(void *, ...);
extern s32 func_80252550();

extern u8 D_8028E568[];
extern u8 D_8028E56C[12];
extern u8 D_8028E590[];
extern u8 D_8028E600[];
extern s32 D_80084D5C;
extern u8 D_805266C0[];
extern u8 D_805266CC[];
extern u8 D_805266D8[];
extern u8 D_8053013C[];
extern void *D_805266DC[];

void func_8052BCCC(void *arg0, void *arg1, void *incoming_out) {
    static void *const keepalive[10] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7, &&case_8, &&case_9
    };
    void *self = arg0;
    void *motion = arg1;
    void *aux;
    register void *out ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    u16 table[14];
    s32 a0;
    s32 a1;
    s32 value;
    register s32 next_state ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
    s32 flag;
    s32 state;
    s16 phase_u16;
    u16 mode;
    s8 *ptr;

#define arg0 self
#define arg1 motion
#define arg2 out
#define s2 aux
    aux = FIELD(arg0, void **, 0xAC);
    ASM_KEEP(aux);   /* MATCH pin: keeps a constant in a register as retail does */
    __builtin_memcpy(table, D_805266C0, 12);
    __builtin_memcpy((u8 *)table + 16, D_805266CC, 12);

    {
        s32 base0;
        s32 baseC;
        s32 base4;
        s32 base8;
        base0 = FIELD(arg1, volatile s32 *, 0);
        baseC = FIELD(arg1, volatile s32 *, 0xC);
        a0 = FIELD(arg1, volatile s32 *, 0x10);
        a1 = FIELD(arg1, volatile s32 *, 0x14);
        FIELD(arg1, s32 *, 0) = base0 + baseC;
        base4 = FIELD(arg1, volatile s32 *, 4);
        base8 = FIELD(arg1, volatile s32 *, 8);
        FIELD(arg1, s32 *, 4) = base4 + a0;
        FIELD(arg1, s32 *, 8) = base8 + a1;
    }
    FIELD(arg0, u16 *, 0xA2) = FIELD(arg0, u16 *, 0xA2) - 1;
    FIELD(s2, u16 *, 0xC) |= 1;

    state = FIELD(arg0, s16 *, 0x68);
    out = incoming_out;
    if ((u32)state >= 10)
        goto state7_finished;
    goto *D_805266DC[state];

case_0: {
            s32 state0_flag;
            a1 = func_80071494() & 0xF;
            if (FIELD(s2, s16 *, 0xA) >= 25) {
                a1 = func_80071494() & 7;
                goto state0_finish;
            }
            if (FIELD(s2, s16 *, 0xA) >= 19) {
                state0_flag = a1 < 3;
                if (state0_flag)
                    goto state0_small;
                state0_flag = a1 < 5;
                goto state0_random;
            }
            if (FIELD(s2, s16 *, 0xA) >= 7) {
                state0_flag = a1 < 4;
                if (state0_flag)
                    goto state0_small;
                state0_flag = a1 < 8;
                goto state0_random;
            }
            state0_flag = a1 < 6;
            if (state0_flag) {
state0_small:
                a1 = (0 - func_80071494()) & 3;
                goto state0_finish;
            }
            state0_flag = a1 < 7;
state0_random:
            a0 = a1 + 14;
            if (state0_flag) {
                a1 = (func_80071494(a0, a1) % 23) + 44;
state0_finish:
                a0 = a1 + 14;
            }
            FIELD(arg0, u16 *, 0xA2) = a0;
            FIELD(arg0, s16 *, 0xA6) = a0;
            FIELD(arg1, s32 *, 0x10) = (s32)0xFFC00000 / FIELD(arg0, s16 *, 0xA2);
            if (FIELD(arg0, s16 *, 0xA0) < 2)
                FIELD(arg2, u16 *, 0x14) |= 1;
            if (FIELD(arg0, u16 *, 0xA0) & 1) {
                FIELD(arg2, s16 *, 6) = -256;
                FIELD(arg1, s32 *, 0x10) = 0 - FIELD(arg1, s32 *, 0x10);
            } else {
                FIELD(arg2, s16 *, 6) = -64;
                func_80034A1C(arg2, D_8028E600, 0);
            }
            next_state = 1;
            goto set_state;
}

case_1: {
            s32 case1_value;
            if (FIELD(arg0, s16 *, 0xA2) <= 0) {
                FIELD(arg1, s32 *, 0x10) = 0;
                phase_u16 = FIELD(arg0, s16 *, 0xA6);
                case1_value = (s32)0x800000 / (s16)(phase_u16 * 2);
                FIELD(arg0, u16 *, 0xA2) = phase_u16 * 2;
                FIELD(arg1, s32 *, 0xC) = case1_value;
                if (FIELD(arg0, s16 *, 0xA0) < 2)
                    FIELD(arg1, s32 *, 0xC) = 0 - case1_value;
                func_80034A1C(arg2, D_8028E590, 0);
                next_state = 2;
                goto set_state;
            }
            goto state7_finished;
}

case_2: {
            register u16 phase ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
            if (FIELD(arg0, s16 *, 0xA2) <= 0) {
                phase = FIELD(arg0, u16 *, 0xA6);
                mode = FIELD(arg0, u16 *, 0xA0);
                value = (s32)0xFFC00000 / (s16)phase;
                FIELD(arg0, u16 *, 0xA2) = phase;
                if (mode & 1) {
                    if ((s16)mode == 1)
                        a0 = value;
                    else
                        a0 = 0 - value;
                    FIELD(arg1, s32 *, 0xC) = a0;
                    FIELD(arg1, s32 *, 0x10) = 0;
                } else {
                    FIELD(arg1, s32 *, 0xC) = 0;
                    FIELD(arg1, s32 *, 0x10) = value;
                }
                next_state = 3;
                goto set_state;
            }
            goto state7_finished;
}

case_3:
            if (FIELD(arg0, s16 *, 0xA2) <= 0) {
                FIELD(arg1, s32 *, 0x10) = 0;
                FIELD(arg1, s32 *, 0xC) = 0;
                FIELD(arg1, s32 *, 4) += (s32)0xFFFC0000;
                FIELD(arg2, s32 *, 0) = D_8028E568;
                FIELD(arg2, s32 *, 8) = *(s32 *)D_8028E56C;
                FIELD(arg2, s8 *, 4) = 0;
                FIELD(arg2, s8 *, 5) = 0;
                if (func_80071494() & 7) {
                    u16 phase3;
                    phase3 = FIELD(arg0, u16 *, 0xA6);
                    FIELD(arg0, volatile u16 *, 0xA2) = 16;
                    FIELD(arg0, u16 *, 0xA2) = phase3;
                    next_state = (s32)0xFF900000 - FIELD(arg1, s32 *, 8);
                    next_state /= (s16)phase3;
                    FIELD(arg1, s32 *, 0x14) = next_state;
                    next_state = 4;
                } else {
                    s32 pos;
                    FIELD(arg0, u16 *, 0xA2) = 12;
                    next_state = (func_80071494() & 0xFF) << 12;
                    pos = FIELD(arg1, s32 *, 8);
                    a0 = 0x580000;
                    pos += a0;
                    a0 = FIELD(arg0, s16 *, 0xA2);
                    next_state -= pos;
                    next_state /= a0;
                    FIELD(arg1, s32 *, 0x14) = next_state;
                    next_state = 5;
                }
                goto set_state;
            }
            goto state7_finished;

case_4:
            if (FIELD(arg1, s32 *, 8) <= (s32)0xFFA80000 &&
                !(FIELD(arg0, u16 *, 0xA4) & 2)) {
                FIELD(arg2, s16 *, 6) = 0;
                FIELD(arg0, void **, 0x48) = D_805266D8;
                FIELD(arg0, u16 *, 0xA4) |= 2;
                func_8023FA58(arg0, arg1, D_8053013C);
                FIELD(s2, u16 *, 8) += 1;
            }
            if (FIELD(arg0, s16 *, 0xA2) == 3) {
                FIELD(arg2, s32 *, 0) = D_8028E568;
                FIELD(arg2, s32 *, 8) = *(s32 *)D_8028E56C;
                FIELD(arg2, s8 *, 4) = 0;
                FIELD(arg2, s8 *, 5) = 0;
            }
            if (FIELD(arg0, s16 *, 0xA2) <= 0) {
                FIELD(arg1, s32 *, 0x14) = 0;
                FIELD(arg0, s16 *, 0x68) = 7;
                FIELD(arg0, u16 *, 0xA2) = FIELD(arg0, s16 *, 0xA6) * 2 + 20;
            }
            goto state7_finished;

case_5:
            if (FIELD(arg0, s16 *, 0xA2) <= 0) {
                FIELD(arg0, u16 *, 0xA2) = 6;
                FIELD(arg1, s32 *, 0x14) = ((s32)0xFFD80000 - FIELD(arg1, s32 *, 8)) /
                    FIELD(arg0, s16 *, 0xA2);
                FIELD(arg0, s16 *, 0x68) = 6;
            }
            goto state7_finished;

case_6:
            if (FIELD(arg0, s16 *, 0xA2) <= 0) {
	                FIELD(arg0, u16 *, 0xA2) = 8;
	                next_state = (s32)0xFF900000 - FIELD(arg1, s32 *, 8);
	                FIELD(arg1, s32 *, 0x14) = next_state / FIELD(arg0, s16 *, 0xA2);
	                ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
	                next_state = 4;
                goto set_state;
            }
            goto state7_finished;

case_7: {
            void *call_out;
            if (FIELD(arg0, s16 *, 0xA2) <= 0) {
                call_out = arg2;
                if (FIELD(arg0, s16 *, 0xA0) & 1) {
                    value = (s32)D_8028E590;
                } else {
                    FIELD(arg2, s16 *, 6) = 64;
                    value = (s32)D_8028E600;
                }
                func_80034A1C(call_out, (void *)value, 0);
                FIELD(arg0, u16 *, 0xA4) &= 0xFFFD;
                FIELD(s2, u16 *, 0xC) &= 0xFFFB;
                flag = FIELD(arg0, u16 *, 0xA0);
                FIELD(arg0, u16 *, 0xA2) = 8;
                a1 = -0x80000;
                if (flag & 1) {
                    a0 = a1;
                    if ((s16)flag != 1)
                        a0 = 0x80000;
	                    FIELD(arg1, s32 *, 0xC) = a0;
	                    FIELD(arg1, s32 *, 0x10) = 0;
	                    goto set_state_8;
	                } else {
	                    FIELD(arg1, s32 *, 0xC) = 0;
	                    FIELD(arg1, s32 *, 0x10) = a1;
	                    goto set_state_8;
	                }
	            }
            goto state7_finished;
}

case_8:
            if (FIELD(arg0, s16 *, 0xA2) <= 0) {
                func_8023FB18(arg0);
                ptr = FIELD(arg0, s8 **, 0x98);
                if (ptr != 0)
                    *ptr = 0;
                func_80050D68(arg0);
                FIELD(arg0, u16 *, -2) |= 0x8000;
                D_80084D5C |= 0x8000;
            }
            goto state7_finished;

case_9: {
            s32 phase;
            phase = FIELD(arg0, s16 *, 0xA2);
            if (phase == 1) {
                func_80058F88(0x512);
                phase = FIELD(arg0, s16 *, 0xA2);
            }
            if (phase < 6) {
                FIELD(arg2, u16 *, 0x1C) = FIELD(table, u16 *, phase * 2);
                FIELD(arg2, u16 *, 0x1E) = FIELD(
                    table, u16 *, FIELD(arg0, s16 *, 0xA2) * 2 + 16);
            }
	            if (FIELD(arg0, s16 *, 0xA2) > 0)
	                goto state7_finished;
	set_state_8:
	            next_state = 8;
	            goto set_state;
}

set_state:
    FIELD(arg0, s16 *, 0x68) = next_state;
state7_finished:
    func_8003EA54(arg2);
    if ((FIELD(arg0, u16 *, 0xA4) & 2) && func_80252550(D_8053013C, arg1) != 0) {
        FIELD(arg1, s32 *, 0x14) = 0;
        FIELD(arg1, s32 *, 0x10) = 0;
        FIELD(arg1, s32 *, 0xC) = 0;
        {
            void *tail_aux = FIELD(arg0, void **, 0xAC);
            FIELD(tail_aux, u16 *, 6) += 1;
        }
        FIELD(arg0, u16 *, 0xA4) &= 0xFFFD;
        FIELD(arg2, s32 *, 0) = D_8028E568;
        FIELD(arg2, s32 *, 8) = *(s32 *)D_8028E56C;
        FIELD(arg2, s8 *, 4) = 0;
        FIELD(arg2, s8 *, 5) = 0;
        FIELD(arg0, u16 *, 0xA2) = 14;
        FIELD(arg0, s16 *, 0x68) = 9;
    }
    return;
#undef arg0
#undef arg1
#undef arg2
}
