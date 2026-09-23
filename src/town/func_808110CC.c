#include "common.h"


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

typedef struct S_8052BCCC_0 {
    u8 pad_00[0x48];
    void * unk_48;
    u8 pad_4C[0x1C];
    s16 unk_68;
    u8 pad_6A[0x2E];
    s8 * unk_98;
    u8 pad_9C[0x4];
    s16 unk_A0;
    u16 unk_A2;
    u16 unk_A4;
    u16 unk_A6;
    u8 pad_A8[0x4];
    void * unk_AC;
} S_8052BCCC_0;   /* obj in func_8052BCCC */

typedef struct S_8052BCCC_1 {
    volatile s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    volatile s32 unk_0C;
    volatile s32 unk_10;
    s32 unk_14;
} S_8052BCCC_1;   /* motion in func_8052BCCC */

typedef struct S_8052BCCC_2 {
    u8 pad_00[0x8];
    u16 unk_08;
    s16 unk_0A;
    u16 unk_0C;
} S_8052BCCC_2;   /* aux in func_8052BCCC */

typedef struct S_8052BCCC_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s16 unk_06;
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8052BCCC_3;   /* out in func_8052BCCC */

/* Per-frame step for the town cutscene actor: integrate its motion, then run its ten-state dispatch. */
void func_8052BCCC(void *obj, void *motion, void *incoming_out) {
    static void *const keepalive[10] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7, &&case_8, &&case_9
    };
    void *aux;
    register void *out ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 table[14];
    s32 a0;
    s32 a1;
    s32 value;
    register s32 next_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 flag;
    s32 state;
    s16 phase_u16;
    u16 mode;
    s8 *ptr;

    aux = ((S_8052BCCC_0 *)obj)->unk_AC;
    __builtin_memcpy(table, D_805266C0, 12);
    __builtin_memcpy((u8 *)table + 16, D_805266CC, 12);

    {
        s32 base0;
        s32 baseC;
        s32 base4;
        s32 base8;
        base0 = ((S_8052BCCC_1 *)motion)->unk_00;
        baseC = ((S_8052BCCC_1 *)motion)->unk_0C;
        a0 = ((S_8052BCCC_1 *)motion)->unk_10;
        a1 = ((S_8052BCCC_1 *)motion)->unk_14;
        (*(s32 *)((u8 *)(motion) + (0))) = base0 + baseC;
        base4 = ((S_8052BCCC_1 *)motion)->unk_04;
        base8 = ((S_8052BCCC_1 *)motion)->unk_08;
        ((S_8052BCCC_1 *)motion)->unk_04 = base4 + a0;
        ((S_8052BCCC_1 *)motion)->unk_08 = base8 + a1;
    }
    ((S_8052BCCC_0 *)obj)->unk_A2 = ((S_8052BCCC_0 *)obj)->unk_A2 - 1;
    ((S_8052BCCC_2 *)aux)->unk_0C |= 1;

    state = ((S_8052BCCC_0 *)obj)->unk_68;
    out = incoming_out;
    if ((u32)state >= 10)
        goto state7_finished;
    goto *D_805266DC[state];

case_0: {
            s32 state0_flag;
            a1 = func_80071494() & 0xF;
            if (((S_8052BCCC_2 *)aux)->unk_0A >= 25) {
                a1 = func_80071494() & 7;
                goto state0_finish;
            }
            if (((S_8052BCCC_2 *)aux)->unk_0A >= 19) {
                state0_flag = a1 < 3;
                if (state0_flag)
                    goto state0_small;
                state0_flag = a1 < 5;
                goto state0_random;
            }
            if (((S_8052BCCC_2 *)aux)->unk_0A >= 7) {
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
            ((S_8052BCCC_0 *)obj)->unk_A2 = a0;
            ((S_8052BCCC_0 *)obj)->unk_A6 = a0;
            (*(s32 *)((u8 *)(motion) + (0x10))) = (s32)0xFFC00000 / (*(s16 *)((u8 *)(obj) + (0xA2)));
            if (((S_8052BCCC_0 *)obj)->unk_A0 < 2)
                ((S_8052BCCC_3 *)out)->unk_14 |= 1;
            if ((*(u16 *)((u8 *)(obj) + (0xA0))) & 1) {
                ((S_8052BCCC_3 *)out)->unk_06 = -256;
                (*(s32 *)((u8 *)(motion) + (0x10))) = 0 - (*(s32 *)((u8 *)(motion) + (0x10)));
            } else {
                ((S_8052BCCC_3 *)out)->unk_06 = -64;
                func_80034A1C(out, D_8028E600, 0);
            }
            next_state = 1;
            goto set_state;
}

case_1: {
            s32 case1_value;
            if ((*(s16 *)((u8 *)(obj) + (0xA2))) <= 0) {
                (*(s32 *)((u8 *)(motion) + (0x10))) = 0;
                phase_u16 = ((S_8052BCCC_0 *)obj)->unk_A6;
                case1_value = (s32)0x800000 / (s16)(phase_u16 * 2);
                ((S_8052BCCC_0 *)obj)->unk_A2 = phase_u16 * 2;
                (*(s32 *)((u8 *)(motion) + (0xC))) = case1_value;
                if (((S_8052BCCC_0 *)obj)->unk_A0 < 2)
                    (*(s32 *)((u8 *)(motion) + (0xC))) = 0 - case1_value;
                func_80034A1C(out, D_8028E590, 0);
                next_state = 2;
                goto set_state;
            }
            goto state7_finished;
}

case_2: {
            u16 phase;
            if ((*(s16 *)((u8 *)(obj) + (0xA2))) <= 0) {
                phase = ((S_8052BCCC_0 *)obj)->unk_A6;
                ((S_8052BCCC_0 *)obj)->unk_A2 = phase;
                mode = (*(u16 *)((u8 *)(obj) + (0xA0)));
                value = (s32)0xFFC00000 / (s16)phase;
                if (mode & 1) {
                    if ((s16)mode == 1)
                        a0 = value;
                    else
                        a0 = 0 - value;
                    (*(s32 *)((u8 *)(motion) + (0xC))) = a0;
                    (*(s32 *)((u8 *)(motion) + (0x10))) = 0;
                } else {
                    (*(s32 *)((u8 *)(motion) + (0xC))) = 0;
                    (*(s32 *)((u8 *)(motion) + (0x10))) = value;
                }
                next_state = 3;
                goto set_state;
            }
            goto state7_finished;
}

case_3:
            if ((*(s16 *)((u8 *)(obj) + (0xA2))) <= 0) {
                (*(s32 *)((u8 *)(motion) + (0x10))) = 0;
                (*(s32 *)((u8 *)(motion) + (0xC))) = 0;
                ((S_8052BCCC_1 *)motion)->unk_04 += (s32)0xFFFC0000;
                (*(s32 *)((u8 *)(out) + (0))) = D_8028E568;
                ((S_8052BCCC_3 *)out)->unk_08 = *(s32 *)D_8028E56C;
                ((S_8052BCCC_3 *)out)->unk_04 = 0;
                ((S_8052BCCC_3 *)out)->unk_05 = 0;
                if (func_80071494() & 7) {
                    u16 phase3;
                    phase3 = ((S_8052BCCC_0 *)obj)->unk_A6;
                    (*(volatile u16 *)((u8 *)(obj) + (0xA2))) = 16;
                    ((S_8052BCCC_0 *)obj)->unk_A2 = phase3;
                    next_state = (s32)0xFF900000 - ((S_8052BCCC_1 *)motion)->unk_08;
                    next_state /= (s16)phase3;
                    ((S_8052BCCC_1 *)motion)->unk_14 = next_state;
                    next_state = 4;
                } else {
                    s32 pos;
                    ((S_8052BCCC_0 *)obj)->unk_A2 = 12;
                    next_state = (func_80071494() & 0xFF) << 12;
                    pos = ((S_8052BCCC_1 *)motion)->unk_08;
                    a0 = 0x580000;
                    pos += a0;
                    a0 = (*(s16 *)((u8 *)(obj) + (0xA2)));
                    next_state -= pos;
                    next_state /= a0;
                    ((S_8052BCCC_1 *)motion)->unk_14 = next_state;
                    next_state = 5;
                }
                goto set_state;
            }
            goto state7_finished;

case_4:
            if (((S_8052BCCC_1 *)motion)->unk_08 <= (s32)0xFFA80000 &&
                !(((S_8052BCCC_0 *)obj)->unk_A4 & 2)) {
                ((S_8052BCCC_3 *)out)->unk_06 = 0;
                ((S_8052BCCC_0 *)obj)->unk_48 = D_805266D8;
                ((S_8052BCCC_0 *)obj)->unk_A4 |= 2;
                func_8023FA58(obj, motion, D_8053013C);
                ((S_8052BCCC_2 *)aux)->unk_08 += 1;
            }
            if ((*(s16 *)((u8 *)(obj) + (0xA2))) == 3) {
                (*(s32 *)((u8 *)(out) + (0))) = D_8028E568;
                ((S_8052BCCC_3 *)out)->unk_08 = *(s32 *)D_8028E56C;
                ((S_8052BCCC_3 *)out)->unk_04 = 0;
                ((S_8052BCCC_3 *)out)->unk_05 = 0;
            }
            if ((*(s16 *)((u8 *)(obj) + (0xA2))) <= 0) {
                ((S_8052BCCC_1 *)motion)->unk_14 = 0;
                ((S_8052BCCC_0 *)obj)->unk_68 = 7;
                ((S_8052BCCC_0 *)obj)->unk_A2 = (*(s16 *)((u8 *)(obj) + (0xA6))) * 2 + 20;
            }
            goto state7_finished;

case_5:
            if ((*(s16 *)((u8 *)(obj) + (0xA2))) <= 0) {
                ((S_8052BCCC_0 *)obj)->unk_A2 = 6;
                ((S_8052BCCC_1 *)motion)->unk_14 = ((s32)0xFFD80000 - ((S_8052BCCC_1 *)motion)->unk_08) /
                    ((S_8052BCCC_0 *)obj)->unk_A2;
                ((S_8052BCCC_0 *)obj)->unk_68 = 6;
            }
            goto state7_finished;

case_6:
            if ((*(s16 *)((u8 *)(obj) + (0xA2))) <= 0) {
	                ((S_8052BCCC_0 *)obj)->unk_A2 = 8;
	                next_state = (s32)0xFF900000 - ((S_8052BCCC_1 *)motion)->unk_08;
	                next_state /= ((S_8052BCCC_0 *)obj)->unk_A2;
                    ((S_8052BCCC_1 *)motion)->unk_14 = next_state;
	                ((S_8052BCCC_0 *)obj)->unk_68 = 4;
                goto state7_finished;
            }
            goto state7_finished;

case_7: {
            void *call_out;
            if ((*(s16 *)((u8 *)(obj) + (0xA2))) <= 0) {
                call_out = out;
                if (((S_8052BCCC_0 *)obj)->unk_A0 & 1) {
                    value = (s32)D_8028E590;
                } else {
                    ((S_8052BCCC_3 *)out)->unk_06 = 64;
                    value = (s32)D_8028E600;
                }
                func_80034A1C(call_out, (void *)value, 0);
                ((S_8052BCCC_0 *)obj)->unk_A4 &= 0xFFFD;
                ((S_8052BCCC_2 *)aux)->unk_0C &= 0xFFFB;
                flag = (*(u16 *)((u8 *)(obj) + (0xA0)));
                ((S_8052BCCC_0 *)obj)->unk_A2 = 8;
                a1 = -0x80000;
                if (flag & 1) {
                    a0 = a1;
                    if ((s16)flag != 1)
                        a0 = 0x80000;
	                    (*(s32 *)((u8 *)(motion) + (0xC))) = a0;
	                    (*(s32 *)((u8 *)(motion) + (0x10))) = 0;
	                    goto set_state_8;
	                } else {
	                    (*(s32 *)((u8 *)(motion) + (0xC))) = 0;
	                    (*(s32 *)((u8 *)(motion) + (0x10))) = a1;
	                    goto set_state_8;
	                }
	            }
            goto state7_finished;
}

case_8:
            if ((*(s16 *)((u8 *)(obj) + (0xA2))) <= 0) {
                func_8023FB18(obj);
                ptr = ((S_8052BCCC_0 *)obj)->unk_98;
                if (ptr != 0)
                    *ptr = 0;
                func_80050D68(obj);
                (*(u16 *)((u8 *)(obj) + (-2))) |= 0x8000;
                D_80084D5C |= 0x8000;
            }
            goto state7_finished;

case_9: {
            s32 phase;
            phase = (*(s16 *)((u8 *)(obj) + (0xA2)));
            if (phase == 1) {
                func_80058F88(0x512);
                phase = (*(s16 *)((u8 *)(obj) + (0xA2)));
            }
            if (phase < 6) {
                ((S_8052BCCC_3 *)out)->unk_1C = (*(u16 *)((u8 *)(table) + (phase * 2)));
                ((S_8052BCCC_3 *)out)->unk_1E = (*(u16 *)((u8 *)(table) + ((*(s16 *)((u8 *)(obj) + (0xA2))) * 2 + 16)));
            }
	            if ((*(s16 *)((u8 *)(obj) + (0xA2))) > 0)
	                goto state7_finished;
	set_state_8:
	            next_state = 8;
	            goto set_state;
}

set_state:
    ((S_8052BCCC_0 *)obj)->unk_68 = next_state;
state7_finished:
    func_8003EA54(out);
    if ((((S_8052BCCC_0 *)obj)->unk_A4 & 2) && func_80252550(D_8053013C, motion) != 0) {
        ((S_8052BCCC_1 *)motion)->unk_14 = 0;
        (*(s32 *)((u8 *)(motion) + (0x10))) = 0;
        (*(s32 *)((u8 *)(motion) + (0xC))) = 0;
        {
            void *tail_aux = (*(void **)((u8 *)(obj) + (0xAC)));
            (*(u16 *)((u8 *)(tail_aux) + (6))) += 1;
        }
        (*(u16 *)((u8 *)(obj) + (0xA4))) &= 0xFFFD;
        (*(s32 *)((u8 *)(out) + (0))) = D_8028E568;
        (*(s32 *)((u8 *)(out) + (8))) = *(s32 *)D_8028E56C;
        (*(s8 *)((u8 *)(out) + (4))) = 0;
        (*(s8 *)((u8 *)(out) + (5))) = 0;
        (*(u16 *)((u8 *)(obj) + (0xA2))) = 14;
        (*(s16 *)((u8 *)(obj) + (0x68))) = 9;
    }
    return;
#undef obj
#undef motion
#undef out
}
