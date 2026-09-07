#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

typedef struct {
    u8 pad00[0x13];
    s8 field13;
    u8 pad14[0x78];
} D_800E3E48_Entry;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)

#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

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

s32 func_800AB778(void *arg0, void *arg1, void *arg2, void *arg3) {
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
    register void *temp_v0_2 ASM_REG("$2");
    register void *temp_v0_7 ASM_REG("$2");
    register s32 temp_v0_idx ASM_REG("$2");
    register u32 temp_v1_base ASM_REG("$3");
    register s32 initial_zero ASM_REG("$2");
    register void *call_actor16 ASM_REG("$4");
    void *page4;
    void *page16;
    void *call_event16;
    void *page_obj4;
    void *page_obj16;
    u8 *state4_tail;
    u8 *state16_tail;
    s32 *global16;
    s32 state4_owner;
    s32 call_flags;

    temp_s0 = M2C_FIELD(arg3, s32 *, 0x14);
    if (temp_s0 & 0x20000000) {
        M2C_FIELD(arg3, s32 *, 0x14) = temp_s0 | 0x400000;
        func_800ACB98();
        initial_zero = 0;
        ASM_TAILSLOT_PIN(initial_zero);
        func_800ABD9C();
        return 0;
    }

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
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
                register s32 default_low_zero ASM_REG("$2");

                default_low_zero = 0;
                ASM_KEEP(default_low_zero);
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
            register s32 default_high_zero ASM_REG("$2");

            default_high_zero = 0;
            ASM_KEEP(default_high_zero);
            func_800ABD9C();
        }
    }

state_case0: {
    u8 *state0;
    register s32 state0_value ASM_REG("$2");
    register u32 state0_page ASM_REG("$2");

    ASM_SCHED_BARRIER();
    if (M2C_FIELD(arg3, u8 *, 0x43) != 0xFD) {
        if ((func_800A2C78(arg3) << 0x10) == 0) {
            state0_page = 0x80080000;
            ASM_PAGEBASE_PIN(state0_page);
            return func_800AB840();
        }
        return 0;
    }
    do { M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s32 *, 0x110) = 0; } while (0);
    do { state0 = (u8 *)&D_80083460; } while (0);
    M2C_FIELD(state0, u16 *, 0xA)++;
    do { state0_value = 3; } while (0);
    M2C_FIELD(arg0, u8 *, 0x9B) = state0_value;
    return func_800ABD98_state0();
    }

state_case3:
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000) {
        func_80094E34();
    }
    if (M2C_FIELD(arg3, u8 *, 0x43) < 0x40U) {
        s32 table_idx;
        register s32 call_mode ASM_REG("$7");
        register void *call_actor ASM_REG("$4");

        table_idx = func_800429E4(arg3);
        call_actor = arg3;
        ASM_KEEP_NV(call_actor);
        call_mode = 2;
        ASM_KEEP_NV(call_mode);
        func_800C542C(call_actor,
            D_800DCED4[table_idx],
            (s32)call_actor == M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s32 *, 0xAC), call_mode);
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
        M2C_FIELD(arg0, u8 *, 0x9B) = 0x10;
        return func_800ABD98_state3();
    }
    if (M2C_FIELD(arg2, u16 *, 0x12) == 0) {
        M2C_FIELD(arg2, u16 *, 0x12) = 0xFF80U;
    }
    M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
    M2C_FIELD(arg2, u16 *, 0x14) |= 0xC;
    M2C_FIELD(arg0, s16 *, 0x96) = 0x10;
    M2C_FIELD(arg3, s32 *, 0x1C) |= 0x10000000;
    M2C_FIELD(arg0, u8 *, 0x9B)++;
    return func_800ABD98();

state_case4:
    M2C_FIELD(arg2, u8 *, 0xC) -=
        (s32)M2C_FIELD(arg2, u8 *, 0xC) / M2C_FIELD(arg0, s16 *, 0x96);
    M2C_FIELD(arg2, u8 *, 0xD) -=
        (s32)M2C_FIELD(arg2, u8 *, 0xD) / M2C_FIELD(arg0, s16 *, 0x96);
    M2C_FIELD(arg2, u8 *, 0xE) -=
        (s32)M2C_FIELD(arg2, u8 *, 0xE) / M2C_FIELD(arg0, s16 *, 0x96);
    temp_a0_2 = M2C_FIELD(arg2, u16 *, 0x1C);
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_a0_2 +
        ((s32)(0x400 - temp_a0_2) / M2C_FIELD(arg0, s16 *, 0x96));
    temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x1E);
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_3 +
        ((s32)(0x400 - temp_v0_3) / M2C_FIELD(arg0, s16 *, 0x96));
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_4;
    if (((temp_v0_4 << 0x10) > 0) &&
        !(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        return 0;
    }
    temp_v0_5 = func_800990FC();
    temp_a1_3 = func_8009929C(8, temp_v0_5);
    temp_v1 = M2C_FIELD(arg3, u8 *, 0x43);
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
        M2C_FIELD(state4_head, u16 *, 0xA)--;
    }
    ASM_SCHED_BARRIER();
    func_800A31D0(arg3);
    temp_v0_6 = func_800A1BD0(arg3);
    if (temp_v0_6 >= 0) {
        register void *actor_base4 ASM_REG("$3");

        actor_base4 = M2C_FIELD(&D_800E3D7C, void **, 0);
        temp_v0_7 = (void *)((temp_v0_6 * 4) + (s32)actor_base4);
        M2C_FIELD(temp_v0_7, s32 *, 0xAC) = 0;
        M2C_FIELD(temp_v0_7, s32 *, 0xD0) = 0;
    }
    page4 = (void *)0x800E0000;
    if (M2C_FIELD(M2C_FIELD(page4, void **, 0x3D7C), void **, 0x110) != NULL) {
        func_800A18E8(M2C_FIELD(arg3, u8 *, 0x13), 3);
        temp_a0_4 = M2C_FIELD(M2C_FIELD(M2C_FIELD(page4, void **, 0x3D7C), void **, 0x110), u8 *, 3) & 0x1F;
        temp_a1_4 = &D_800E3DF0[temp_a0_4];
        M2C_FIELD(*temp_a1_4, s8 *, 0x13) = 0;
        D_800E3E48[temp_a0_4].field13 = 0;
        page_obj4 = M2C_FIELD(page4, void **, 0x3D7C);
        *temp_a1_4 = NULL;
        func_80098B38(M2C_FIELD(page_obj4, void **, 0x110));
        return func_800ABB70(arg3);
    }
    func_800A18E8(M2C_FIELD(arg3, u8 *, 0x13), 2);
    if ((func_80042900(arg3, 0x1B) << 0x10) == 0) {
        call_flags = M2C_FIELD(arg3, s32 *, 0x1C);
        call_arg0 = M2C_FIELD(arg2, u8 *, 0x24);
        call_arg1 = M2C_FIELD(arg2, u8 *, 0x25);
        var_a2 = 0x3000;
        if (call_flags & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(call_arg0, call_arg1, var_a2);
    }
    func_8009A028(arg3);
    M2C_FIELD(arg3, u16 *, -2) |= 0x8000;
    M2C_FIELD(&D_800814A0, s32 *, 0) |= 0x8000;
    state4_tail = (u8 *)&D_80083460;
    state4_count = M2C_FIELD(state4_tail, u16 *, 0xA);
    state4_owner = M2C_FIELD(state4_tail, s32 *, 0xC);
    state4_count--;
    M2C_FIELD(state4_tail, u16 *, 0xA) = state4_count;
    if (state4_owner == (s32)arg3) {
        M2C_FIELD(state4_tail, s32 *, 0xC) = 0;
        return func_800ABD98();
    }
    goto return_zero;

state_case16:
    ASM_SCHED_BARRIER();
    M2C_FIELD(arg3, s32 *, 0x14) = temp_s0 | 0x4000;
    call_actor16 = arg3;
    ASM_KEEP(call_actor16);
    call_event16 = &D_800E0C34;
    ASM_KEEP(call_event16);
    temp_s0 &= 0x4000;
    func_80099844(call_actor16, call_event16);
    if (temp_s0 == 0) {
        M2C_FIELD(arg3, s32 *, 0x14) &= ~0x4000;
    }
    func_800A31D0(arg3);
    temp_s0_2 = M2C_FIELD(arg3, u8 *, 0x43);
    M2C_FIELD(arg3, s8 *, 0x44) = 0;
    if ((func_80042900(arg3, 0xA) << 0x10) != 0) {
        M2C_FIELD(arg3, u8 *, 0x13) = M2C_FIELD(arg3, u8 *, 0xA8);
    }
    temp_v1_base = 0x80010A80;
    temp_v0_idx = temp_s0_2;
    ASM_USE2_NV(temp_v0_idx, temp_v1_base);
    func_800422DC(&((u8 *)temp_v1_base)[temp_v0_idx * 0x54], arg3);
    func_800A18E8(M2C_FIELD(arg3, u8 *, 0x13), 3);
    temp_v0 = func_800A1BD0(arg3);
    if (temp_v0 >= 0) {
        register void *actor_base16 ASM_REG("$3");

        actor_base16 = M2C_FIELD(&D_800E3D7C, void **, 0);
        temp_v0_2 = (void *)((temp_v0 * 4) + (s32)actor_base16);
        M2C_FIELD(temp_v0_2, s32 *, 0xAC) = 0;
        M2C_FIELD(temp_v0_2, s32 *, 0xD0) = 0;
    }
    page16 = (void *)0x800E0000;
    temp_a0 = M2C_FIELD(M2C_FIELD(M2C_FIELD(page16, void **, 0x3D7C), void **, 0x110), u8 *, 3) & 0x1F;
    temp_a1 = &D_800E3DF0[temp_a0];
    M2C_FIELD(*temp_a1, s8 *, 0x13) = 0;
    D_800E3E48[temp_a0].field13 = 0;
    page_obj16 = M2C_FIELD(page16, void **, 0x3D7C);
    *temp_a1 = NULL;
    func_80098B38(M2C_FIELD(page_obj16, void **, 0x110));
    if ((func_80042900(arg3, 0x1B) << 0x10) == 0) {
        call_flags = M2C_FIELD(arg3, s32 *, 0x1C);
        call_arg0 = M2C_FIELD(arg2, u8 *, 0x24);
        call_arg1 = M2C_FIELD(arg2, u8 *, 0x25);
        var_a2 = 0x3000;
        if (call_flags & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(call_arg0, call_arg1, var_a2);
    }
    func_8009A028(arg3);
    global16 = (s32 *)&D_800814A0;
    state16_tail = (u8 *)&D_80083460;
    M2C_FIELD(arg3, u16 *, -2) |= 0x8000;
    M2C_FIELD(global16, s32 *, 0) |= 0x8000;
    state16_count = M2C_FIELD(state16_tail, u16 *, 0xA);
    state16_count--;
    M2C_FIELD(state16_tail, u16 *, 0xA) = state16_count;
return_zero:
    return 0;
}
