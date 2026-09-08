#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_800AB778_19 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_19;   /* page4 in func_800AB778 */

typedef struct S_800AB778_20 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_20;   /* page16 in func_800AB778 */

typedef struct S_800AB778_21 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x60];
    s32 unk_110;
} S_800AB778_21;   /* ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v in func_800AB778 */

typedef struct S_800AB778_22 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_22;   /* ((S_800AB778_19 *)page4)->unk_3D7C in func_800AB778 */

typedef struct S_800AB778_23 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_23;   /* ((S_800AB778_20 *)page16)->unk_3D7C in func_800AB778 */

typedef struct S_800AB778_24 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800AB778_24;   /* ((S_800AB778_22 *)(((S_800AB778_19 *)page4)->unk_3D7C))->unk_110 in func_800AB778 */

typedef struct S_800AB778_25 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800AB778_25;   /* ((S_800AB778_23 *)(((S_800AB778_20 *)page16)->unk_3D7C))->unk_110 in func_800AB778 */


typedef struct S_800AB778_0_pre {
    u16 unk_00;
} S_800AB778_0_pre;   /* the 0x2 bytes before arg3 in func_800AB778, addressed as arg3[-1] */


typedef struct S_800AB778_1 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800AB778_1;   /* arg0 in func_800AB778 */

typedef struct S_800AB778_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AB778_2;   /* state0 in func_800AB778 */

typedef struct S_800AB778_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_800AB778_3;   /* arg2 in func_800AB778 */

typedef struct S_800AB778_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AB778_4;   /* state4_head in func_800AB778 */


typedef struct S_800AB778_6 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    s32 unk_D0;
} S_800AB778_6;   /* temp_v0_7 in func_800AB778 */

typedef struct S_800AB778_7 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_800AB778_7;   /* *temp_a1_4 in func_800AB778 */

typedef struct S_800AB778_8 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_8;   /* page4 in func_800AB778 */

typedef struct S_800AB778_9 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_9;   /* page_obj4 in func_800AB778 */

typedef struct S_800AB778_10 {
    s32 unk_00;
} S_800AB778_10;   /* &D_800814A0 in func_800AB778 */

typedef struct S_800AB778_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_800AB778_11;   /* state4_tail in func_800AB778 */

typedef struct S_800AB778_12 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    s32 unk_D0;
} S_800AB778_12;   /* temp_v0_2 in func_800AB778 */

typedef struct S_800AB778_13 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_800AB778_13;   /* *temp_a1 in func_800AB778 */

typedef struct S_800AB778_14 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_14;   /* page16 in func_800AB778 */

typedef struct S_800AB778_15 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_15;   /* page_obj16 in func_800AB778 */

typedef struct S_800AB778_16 {
    s32 unk_00;
} S_800AB778_16;   /* global16 in func_800AB778 */

typedef struct S_800AB778_17 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AB778_17;   /* state16_tail in func_800AB778 */


typedef struct {
    u8 pad00[0x13];
    s8 field13;
    u8 pad14[0x78];
} D_800E3E48_Entry;

M2C_UNK func_800422DC();
s32 func_80042900();
s32 func_800429E4();
M2C_UNK func_80094E34();
M2C_UNK func_80098B38();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_8009929C();
s32 func_80099734();
M2C_UNK func_80099844();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A18E8();
s16 func_800A1BD0();
s32 func_800A2C78();
M2C_UNK func_800A31D0();
M2C_UNK func_800A5720();
s32 func_800AB840();
s32 func_800ABA58();
s32 func_800ABA98();
s32 func_800ABB70();
s32 func_800ABD98();
s32 func_800ABD98_state0() __asm__("func_800ABD98");
s32 func_800ABD98_state3() __asm__("func_800ABD98");
void func_800ABD9C(void) __attribute__((noreturn));
M2C_UNK func_800ACB98();
M2C_UNK func_800C542C();
extern u8 D_80010A80[];
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800DCE68;
extern s16 D_800DCED4[];
extern M2C_UNK D_800E0C34;
extern M2C_UNK D_800E0C58;
extern M2C_UNK D_800E0C67;
extern M2C_UNK D_800E3D7C;
extern void *D_800E3DF0[];
extern D_800E3E48_Entry D_800E3E48[];

s32 func_800AB778(S_800AB778_1 *arg0, void *arg1, S_800AB778_3 *arg2, void *arg3) {
    M2C_UNK var_a2;
    s16 temp_v0;
    s16 temp_v0_4;
    s32 temp_v0_6;
    s32 temp_a0;
    s32 temp_a0_4;
    s32 temp_a1_3;
    s32 temp_s0;
    s32 temp_v0_5;
    u16 temp_a0_2;
    u16 temp_v0_3;
    u16 state4_count;
    u16 state16_count;
    s32 temp_s0_2;
    u8 temp_v1;
    u8 call_arg0;
    u8 call_arg1;
    void **temp_a1;
    void **temp_a1_4;
    S_800AB778_12 *temp_v0_2;
    S_800AB778_6 *temp_v0_7;
    register s32 temp_v0_idx ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    register u32 temp_v1_base ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 initial_zero;
    void *call_actor16;
    S_800AB778_8 *page4;
    S_800AB778_14 *page16;
    void *call_event16;
    S_800AB778_9 *page_obj4;
    S_800AB778_15 *page_obj16;
    u8 *state4_tail;
    u8 *state16_tail;
    s32 *global16;
    s32 state4_owner;
    s32 call_flags;

    temp_s0 = ((Rec_D_80082E80 *)arg3)->unk_14.at00_s32.v;
    if (temp_s0 & 0x20000000) {
        ((Rec_D_80082E80 *)arg3)->unk_14.at00_s32.v = temp_s0 | 0x400000;
        func_800ACB98();
        initial_zero = 0;
        ASM_TAILSLOT_PIN(initial_zero);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800ABD9C();
        return 0;
    }

    temp_v1 = arg0->unk_9B;
    {
        s32 dispatch_state;

        dispatch_state = temp_v1;
        if (dispatch_state == 3) {
            goto state_case3;
        }
        if (dispatch_state < 4) {
            if (dispatch_state == 0) {
                goto state_case0;
            }
            {
                register s32 default_low_zero ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */

                default_low_zero = 0;
                ASM_KEEP(default_low_zero);   /* MATCH pin: retail delay-slot contents depend on it */
                func_800ABD9C();
            }
        }
        if (dispatch_state == 4) {
            goto state_case4;
        }
        if (dispatch_state == 16) {
            goto state_case16;
        }
        {
            register s32 default_high_zero ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */

            default_high_zero = 0;
            ASM_KEEP(default_high_zero);   /* MATCH pin: retail delay-slot contents depend on it */
            func_800ABD9C();
        }
    }

state_case0: {
    u8 *state0;
    register s32 state0_value ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    u32 state0_page;

    if (((Rec_D_80082E80 *)arg3)->unk_43 != 0xFD) {
        if ((func_800A2C78(arg3) << 0x10) == 0) {
            state0_page = 0x80080000;
            ASM_PAGEBASE_PIN(state0_page);   /* MATCH pin: retail delay-slot contents depend on it */
            return func_800AB840();
        }
        return 0;
    }
    do { ((S_800AB778_21 *)(((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v))->unk_110 = 0; } while (0);
    do { state0 = (u8 *)&D_80083460; } while (0);
    ((S_800AB778_2 *)state0)->unk_0A++;
    do { state0_value = 3; } while (0);
    arg0->unk_9B = state0_value;
    return func_800ABD98_state0();
    }

state_case3:
    if (((Rec_D_80082E80 *)arg3)->unk_1C.at00_s32.v & 0x80000) {
        func_80094E34();
    }
    if (((Rec_D_80082E80 *)arg3)->unk_43 < 0x40U) {
        s32 table_idx;
        register s32 call_mode ASM_REG("$7");   /* MATCH pin: retail basic-block layout depends on it */
        register void *call_actor ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */

        table_idx = func_800429E4(arg3);
        call_actor = arg3;
        call_mode = 2;
        ASM_KEEP_NV(call_mode);   /* MATCH pin: retail schedule: same instructions, different order without it */
        func_800C542C(call_actor,
            D_800DCED4[table_idx],
            (s32)call_actor == ((S_800AB778_21 *)(((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v))->unk_AC, call_mode);
        arg0->unk_96.s = 0;
        arg0->unk_9B = 0x10;
        return func_800ABD98_state3();
    }
    if (arg2->unk_12 == 0) {
        arg2->unk_12 = 0xFF80U;
    }
    arg2->unk_10 = 0x20;
    arg2->unk_14 |= 0xC;
    arg0->unk_96.s = 0x10;
    ((Rec_D_80082E80 *)arg3)->unk_1C.at00_s32.v |= 0x10000000;
    arg0->unk_9B++;
    return func_800ABD98();

state_case4:
    arg2->unk_0C -=
        (s32)arg2->unk_0C / arg0->unk_96.s;
    arg2->unk_0D -=
        (s32)arg2->unk_0D / arg0->unk_96.s;
    arg2->unk_0E -=
        (s32)arg2->unk_0E / arg0->unk_96.s;
    temp_a0_2 = arg2->unk_1C;
    arg2->unk_1C = temp_a0_2 +
        ((s32)(0x400 - temp_a0_2) / arg0->unk_96.s);
    temp_v0_3 = arg2->unk_1E;
    arg2->unk_1E = temp_v0_3 +
        ((s32)(0x400 - temp_v0_3) / arg0->unk_96.s);
    temp_v0_4 = arg0->unk_96.u - 1;
    arg0->unk_96.s = temp_v0_4;
    if (((temp_v0_4 << 0x10) > 0) &&
        !(arg2->unk_14 & 0x8000)) {
        return 0;
    }
    temp_v0_5 = func_800990FC();
    temp_a1_3 = func_8009929C(8, temp_v0_5);
    temp_v1 = ((Rec_D_80082E80 *)arg3)->unk_43;
    if (temp_v1 == 0xFF) {
        func_80099734(arg3, temp_a1_3);
        return func_800ABA58(&D_800E0C58);
    }
    if (temp_v1 == 0xFE) {
        func_80099290(func_80099194(&D_800E0C67,
            func_80099734(arg3, temp_a1_3)));
        func_800A5720(temp_v0_5);
        return func_800ABA98();
    }
    {
        u8 *state4_head;
        u16 *state4_global;

        state4_global = (u16 *)&D_800DCE68;
        state4_head = (u8 *)&D_80083460;
        (*state4_global)--;
        ((S_800AB778_4 *)state4_head)->unk_0A--;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a constant in a register as retail does */
    func_800A31D0(arg3);
    temp_v0_6 = func_800A1BD0(arg3);
    if (temp_v0_6 >= 0) {
        void *actor_base4;

        actor_base4 = ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v;
        temp_v0_7 = (void *)((temp_v0_6 * 4) + (s32)actor_base4);
        temp_v0_7->unk_AC = 0;
        temp_v0_7->unk_D0 = 0;
    }
    page4 = (void *)0x800E0000;
    if (((S_800AB778_22 *)(((S_800AB778_19 *)page4)->unk_3D7C))->unk_110 != NULL) {
        func_800A18E8(((Rec_D_80082E80 *)arg3)->unk_12.at01_u8.v, 3);
        temp_a0_4 = ((S_800AB778_24 *)(((S_800AB778_22 *)(((S_800AB778_19 *)page4)->unk_3D7C))->unk_110))->unk_03 & 0x1F;
        temp_a1_4 = &D_800E3DF0[temp_a0_4];
        ((S_800AB778_7 *)(*temp_a1_4))->unk_13 = 0;
        D_800E3E48[temp_a0_4].field13 = 0;
        page_obj4 = page4->unk_3D7C;
        *temp_a1_4 = NULL;
        func_80098B38(page_obj4->unk_110);
        return func_800ABB70(arg3);
    }
    func_800A18E8(((Rec_D_80082E80 *)arg3)->unk_12.at01_u8.v, 2);
    if ((func_80042900(arg3, 0x1B) << 0x10) == 0) {
        call_flags = ((Rec_D_80082E80 *)arg3)->unk_1C.at00_s32.v;
        call_arg0 = arg2->unk_24;
        call_arg1 = arg2->unk_25;
        var_a2 = 0x3000;
        if (call_flags & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(call_arg0, call_arg1, var_a2);
    }
    func_8009A028(arg3);
    ((S_800AB778_0_pre *)arg3)[-1].unk_00 |= 0x8000;
    ((S_800AB778_10 *)(&D_800814A0))->unk_00 |= 0x8000;
    state4_tail = (u8 *)&D_80083460;
    state4_count = ((S_800AB778_11 *)state4_tail)->unk_0A;
    state4_owner = ((S_800AB778_11 *)state4_tail)->unk_0C;
    state4_count--;
    ((S_800AB778_11 *)state4_tail)->unk_0A = state4_count;
    if (state4_owner == (s32)arg3) {
        ((S_800AB778_11 *)state4_tail)->unk_0C = 0;
        return func_800ABD98();
    }
    goto return_zero;

state_case16:
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a constant in a register as retail does */
    ((Rec_D_80082E80 *)arg3)->unk_14.at00_s32.v = temp_s0 | 0x4000;
    call_actor16 = arg3;
    ASM_KEEP(call_actor16);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_event16 = &D_800E0C34;
    ASM_KEEP(call_event16);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s0 &= 0x4000;
    func_80099844(call_actor16, call_event16);
    if (temp_s0 == 0) {
        ((Rec_D_80082E80 *)arg3)->unk_14.at00_s32.v &= ~0x4000;
    }
    func_800A31D0(arg3);
    temp_s0_2 = ((Rec_D_80082E80 *)arg3)->unk_43;
    ((Rec_D_80082E80 *)arg3)->unk_44 = 0;
    if ((func_80042900(arg3, 0xA) << 0x10) != 0) {
        ((Rec_D_80082E80 *)arg3)->unk_12.at01_u8.v = ((Rec_D_80082E80 *)arg3)->unk_A8;
    }
    temp_v1_base = 0x80010A80;
    temp_v0_idx = temp_s0_2;
    func_800422DC(&((u8 *)temp_v1_base)[temp_v0_idx * 0x54], arg3);
    func_800A18E8(((Rec_D_80082E80 *)arg3)->unk_12.at01_u8.v, 3);
    temp_v0 = func_800A1BD0(arg3);
    if (temp_v0 >= 0) {
        void *actor_base16;

        actor_base16 = ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v;
        temp_v0_2 = (void *)((temp_v0 * 4) + (s32)actor_base16);
        temp_v0_2->unk_AC = 0;
        temp_v0_2->unk_D0 = 0;
    }
    page16 = (void *)0x800E0000;
    temp_a0 = ((S_800AB778_25 *)(((S_800AB778_23 *)(((S_800AB778_20 *)page16)->unk_3D7C))->unk_110))->unk_03 & 0x1F;
    temp_a1 = &D_800E3DF0[temp_a0];
    ((S_800AB778_13 *)(*temp_a1))->unk_13 = 0;
    D_800E3E48[temp_a0].field13 = 0;
    page_obj16 = page16->unk_3D7C;
    *temp_a1 = NULL;
    func_80098B38(page_obj16->unk_110);
    if ((func_80042900(arg3, 0x1B) << 0x10) == 0) {
        call_flags = ((Rec_D_80082E80 *)arg3)->unk_1C.at00_s32.v;
        call_arg0 = arg2->unk_24;
        call_arg1 = arg2->unk_25;
        var_a2 = 0x3000;
        if (call_flags & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(call_arg0, call_arg1, var_a2);
    }
    func_8009A028(arg3);
    global16 = (s32 *)&D_800814A0;
    state16_tail = (u8 *)&D_80083460;
    ((S_800AB778_0_pre *)arg3)[-1].unk_00 |= 0x8000;
    ((S_800AB778_16 *)global16)->unk_00 |= 0x8000;
    state16_count = ((S_800AB778_17 *)state16_tail)->unk_0A;
    state16_count--;
    ((S_800AB778_17 *)state16_tail)->unk_0A = state16_count;
return_zero:
    return 0;
}
