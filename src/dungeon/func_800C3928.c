#include "common.h"

typedef struct S_800C9088_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x4];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800C9088_0;   /* object in func_800C9088 */

typedef struct S_800C9088_1 {
    u8 pad_00[0x20];
    union { u8 * s; void * u; } unk_20;   /* accessed as both */
    u8 pad_24[0xC];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x4];
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    u8 pad_62[0xE];
    s32 unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    s32 unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    s32 unk_80;
    u16 unk_84;
    u8 pad_86[0x2];
    s32 unk_88;
    u16 unk_8C;
    u8 pad_8E[0x32];
    s32 unk_C0;
    u8 pad_C4[0x50];
    volatile s32 unk_114;
} S_800C9088_1;   /* scratch in func_800C9088 */

typedef struct S_800C9088_2 {
    u8 unk_00;
    u8 pad_01[0x1];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x3154];
    u8 * unk_3160;
} S_800C9088_2;   /* ptr_s0 in func_800C9088 */

typedef struct S_800C9088_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800C9088_3;   /* state in func_800C9088 */

typedef struct S_800C9088_4 {
    u8 * unk_00;
    u8 * unk_04;
    u8 * unk_08;
} S_800C9088_4;   /* descriptor in func_800C9088 */

typedef struct S_800C9088_5 {
    u16 unk_00;
} S_800C9088_5;   /* indices in func_800C9088 */

typedef struct S_800C9088_6 {
    s32 unk_00;
} S_800C9088_6;   /* table + next_index * 8 in func_800C9088 */

typedef struct S_800C9088_7 {
    s32 unk_00;
} S_800C9088_7;   /* word2_ptr in func_800C9088 */

typedef struct S_800C9088_8 {
    s32 unk_00;
} S_800C9088_8;   /* word3_ptr in func_800C9088 */

typedef struct S_800C9088_9 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800C9088_9;   /* table + half_index * 8 in func_800C9088 */

typedef struct S_800C9088_10_pre {
    u8 unk_00;
} S_800C9088_10_pre;   /* the 0x1 bytes before ptr_s1 in func_800C9088, addressed as ptr_s1[-1] */

typedef struct S_800C9088_10 {
    s8 unk_00;
} S_800C9088_10;   /* ptr_s1 in func_800C9088 */

typedef struct S_800C9088_11 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800C9088_11;   /* *(u8 **)state_base in func_800C9088 */

typedef struct S_800C9088_12 {
    s32 unk_00;
} S_800C9088_12;   /* table + ((S_800C9088_5 *)indices)->unk_00 * 8 in func_800C9088 */

typedef struct S_800C9088_13 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800C9088_13;   /* table + (*(u16 *)((u8 *)ptr_s1 + -0x1D)) * 8 in func_800C9088 */



typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct {
    MATRIX matrix;
    u16 saved_arg3;
    u16 pad;
    u32 reserved;
} MATRIX_LOCAL;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064B90(void *, void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065034(void *, void *, void *);
extern s32 func_80065480(s32, s32, s32);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065AB0(u16, void *);
extern void func_80065C50(u16, void *);
extern void func_80065DF0(u16, void *);
extern void func_8006658C(void *, void *);
extern void func_8006671C(void *);
extern void func_800C925C(void);
extern void func_800C93D4(void) __attribute__((noreturn));
extern void func_800C93E0() __attribute__((noreturn));
extern u8 D_80083160[];

void func_800C9088(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    u8 *ptr_s1 = arg0;   /* MATCH pin: retail schedule: same instructions, different order without it */
    u8 *ptr_s0 = arg1;
    u8 *object = arg2;
    register u8 *scratch ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *indices;
    register u8 *table ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *vertices;
    register u8 *packet ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *arg2_tail;
    u8 *state;
    u8 *descriptor;
    u8 *call_a0;
    u8 *call_a1;
    u8 *call_a2;
    u8 *call_a3;
    s32 table_word;
    u32 next_index;
    u32 final_index;
    s32 word2;
    s32 word3;
    u32 half_index;
    u16 half_value;
    u16 final_half;
    u8 *word2_ptr;
    u8 *word3_ptr;
    register u8 *packet_arg0 ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 projected;
    s32 visible;
    s32 flags;
    u16 object_x;
    MATRIX_LOCAL local;
    static void *const keepalive[] = { &&after_switch };


    local.saved_arg3 = arg3;
    func_800649A0();

    object_x = ((S_800C9088_0 *)object)->unk_1C;
    scratch = (u8 *)0x1F800000;
    ((S_800C9088_1 *)scratch)->unk_30 = object_x;
    ((S_800C9088_1 *)scratch)->unk_34 = ((S_800C9088_0 *)object)->unk_1E;
    ((S_800C9088_1 *)scratch)->unk_38 = ((S_800C9088_0 *)object)->unk_20;
    ((S_800C9088_1 *)scratch)->unk_40 = ((S_800C9088_2 *)ptr_s0)->unk_02;
    ((S_800C9088_1 *)scratch)->unk_44 = ((S_800C9088_2 *)ptr_s0)->unk_06;
    ((S_800C9088_1 *)scratch)->unk_48 = ((S_800C9088_2 *)ptr_s0)->unk_0A;

    func_80064AE0(&local.matrix);

    ((S_800C9088_1 *)scratch)->unk_60 = 0x1000;
    ((S_800C9088_1 *)scratch)->unk_58 = 0x1000;
    ((S_800C9088_1 *)scratch)->unk_50 = 0x1000;
    ((S_800C9088_1 *)scratch)->unk_5E = 0;
    ((S_800C9088_1 *)scratch)->unk_5C = 0;
    ((S_800C9088_1 *)scratch)->unk_5A = 0;
    ((S_800C9088_1 *)scratch)->unk_56 = 0;
    ((S_800C9088_1 *)scratch)->unk_54 = 0;
    ((S_800C9088_1 *)scratch)->unk_52 = 0;

    func_80065AB0(((S_800C9088_0 *)object)->unk_16, scratch + 0x50);
    func_80065DF0(((S_800C9088_0 *)object)->unk_1A, scratch + 0x50);
    func_80065C50(((S_800C9088_0 *)object)->unk_18, scratch + 0x50);

    ptr_s0 = (u8 *)0x80080000;
    if (((S_800C9088_0 *)object)->unk_14 & 1) {
        ((S_800C9088_1 *)scratch)->unk_30 = -((S_800C9088_1 *)scratch)->unk_30;
    }
    if (((S_800C9088_0 *)object)->unk_14 & 2) {
        ((S_800C9088_1 *)scratch)->unk_34 = -((S_800C9088_1 *)scratch)->unk_34;
    }

    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064B90(scratch + 0x50, scratch + 0x40);
    func_80064840(scratch + 0x50, ptr_s1, scratch + 0xD0);
    func_80064840(&local.matrix, scratch + 0xD0, scratch + 0x50);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    state = ((S_800C9088_2 *)ptr_s0)->unk_3160;
    arg2_tail = object + 0xC;
    ((S_800C9088_1 *)scratch)->unk_20.s = state + 0xB0;
    packet = ((S_800C9088_3 *)state)->unk_8D0;
    ptr_s0 = packet + 7;
    ((S_800C9088_0 *)object)->unk_14 |= 0x8000;

    descriptor = ((S_800C9088_0 *)object)->unk_08;
    indices = ((S_800C9088_4 *)descriptor)->unk_00;
    table = ((S_800C9088_4 *)descriptor)->unk_04;
    vertices = ((S_800C9088_4 *)descriptor)->unk_08;
    ptr_s1 = indices + 0x1F;

    ASM_KEEP(scratch);   /* MATCH pin: retail immediate-load split depends on it */

    table_word = ((S_800C9088_12 *)(table + ((S_800C9088_5 *)indices)->unk_00 * 8))->unk_00;
    ASM_KEEP(table_word);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    next_index = (*(u16 *)((u8 *)ptr_s1 + -0x1D));
    ASM_KEEP(next_index);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_800C9088_1 *)scratch)->unk_70 = table_word;
    table_word = ((S_800C9088_6 *)(table + next_index * 8))->unk_00;
    next_index = (*(u16 *)((u8 *)ptr_s1 + -0x1B));
    ASM_KEEP(next_index);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    word2_ptr = (u8 *)(next_index * 8 + (u32)table);
    ((S_800C9088_1 *)scratch)->unk_78 = table_word;
    final_index = (*(u16 *)((u8 *)ptr_s1 + -0x19));
    word2 = ((S_800C9088_7 *)word2_ptr)->unk_00;
    word3_ptr = (u8 *)(final_index * 8 + (u32)table);
    ((S_800C9088_1 *)scratch)->unk_80 = word2;
    half_index = ((S_800C9088_5 *)indices)->unk_00;
    word3 = ((S_800C9088_8 *)word3_ptr)->unk_00;

    half_value = ((S_800C9088_9 *)(table + half_index * 8))->unk_04;
    ((S_800C9088_1 *)scratch)->unk_74 = half_value;

    half_value = ((S_800C9088_13 *)(table + (*(u16 *)((u8 *)ptr_s1 + -0x1D)) * 8))->unk_04;
    call_a0 = scratch + 0x70;
    ((S_800C9088_1 *)scratch)->unk_7C = half_value;

    half_index = (*(u16 *)((u8 *)ptr_s1 + -0x1B));
    ASM_KEEP(half_index);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_a1 = scratch + 0x78;
    half_value = ((S_800C9088_9 *)(table + half_index * 8))->unk_04;
    ASM_KEEP(half_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_a2 = scratch + 0x80;
    ((S_800C9088_1 *)scratch)->unk_84 = half_value;

    half_index = (*(u16 *)((u8 *)ptr_s1 + -0x19));
    call_a3 = scratch + 0x88;
    ((S_800C9088_1 *)scratch)->unk_88 = word3;
    final_half = ((S_800C9088_9 *)(table + half_index * 8))->unk_04;

    packet_arg0 = packet + 8;
    ((S_800C9088_1 *)scratch)->unk_8C = final_half;
    ASM_JALDELAY_PIN(final_half);   /* MATCH pin: load-bearing for the whole function shape */
    projected = func_80065590(call_a0, call_a1,
                              call_a2, call_a3,
                              packet_arg0, packet + 0x14,
                              packet + 0x20, packet + 0x2C,
                              scratch + 0x90, scratch + 0x94);
    ((S_800C9088_1 *)scratch)->unk_C0 = projected;

    flags = ((S_800C9088_0 *)object)->unk_14 & 3;
    if (flags == 1) {
        goto flag_one;
    }
    if (flags < 2) {
        if (flags == 0) {
            goto flag_zero;
        }
        func_800C93D4();
    }
    if (flags == 2) {
        goto flag_two;
    }
    func_800C93D4();

flag_zero:
    func_800C93E0((*(s32 *)((u8 *)ptr_s0 + 1)),
                  (*(s32 *)((u8 *)ptr_s0 + 0xD)),
                  (*(s32 *)((u8 *)ptr_s0 + 0x19)));
flag_one:
    func_800C93E0((*(s32 *)((u8 *)ptr_s0 + 0xD)),
                  (*(s32 *)((u8 *)ptr_s0 + 1)),
                  (*(s32 *)((u8 *)ptr_s0 + 0x19)));
flag_two:
    func_800C93E0((*(s32 *)((u8 *)ptr_s0 + 0x19)),
                  (*(s32 *)((u8 *)ptr_s0 + 0xD)),
                  (*(s32 *)((u8 *)ptr_s0 + 1)));

after_switch:
    visible = func_80065480((*(s32 *)((u8 *)ptr_s0 + 0x19)),
                            (*(s32 *)((u8 *)ptr_s0 + 1)),
                            (*(s32 *)((u8 *)ptr_s0 + 0xD)));
    ((S_800C9088_1 *)scratch)->unk_114 = visible;
    if (((S_800C9088_1 *)scratch)->unk_114 > 0) {
        register u16 raw_arg3 ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 signed_arg3 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

        raw_arg3 = local.saved_arg3;
        ASM_KEEP(raw_arg3);   /* MATCH pin: retail basic-block layout depends on it */
        signed_arg3 = (s16)raw_arg3;
        ((S_800C9088_1 *)scratch)->unk_C0 -= signed_arg3;
        if ((u32)((S_800C9088_1 *)scratch)->unk_C0 < 0x1E0) {
            func_80065034(vertices + (*(u16 *)((u8 *)ptr_s1 + -0xF)) * 8,
                          arg2_tail, packet + 4);
            func_80065034(vertices + (*(u16 *)((u8 *)ptr_s1 + -0xD)) * 8,
                          arg2_tail, packet + 0x10);
            func_80065034(vertices + (*(u16 *)((u8 *)ptr_s1 + -0xB)) * 8,
                          arg2_tail, packet + 0x1C);
            func_80065034(vertices + (*(u16 *)((u8 *)ptr_s1 + -9)) * 8,
                          arg2_tail, packet + 0x28);

            (*(s32 *)((u8 *)ptr_s0 + 5)) = (*(s32 *)((u8 *)ptr_s1 + -0x17));
            (*(u16 *)((u8 *)ptr_s0 + 7)) += ((S_800C9088_0 *)object)->unk_12;
            (*(s32 *)((u8 *)ptr_s0 + 0x11)) = (*(s32 *)((u8 *)ptr_s1 + -0x13));
            if (((S_800C9088_0 *)object)->unk_10 != 0) {
                (*(u16 *)((u8 *)ptr_s0 + 0x13)) =
                    ((*(u16 *)((u8 *)ptr_s0 + 0x13)) & 0xFF9F) +
                    ((S_800C9088_0 *)object)->unk_10;
            }
            (*(u16 *)((u8 *)ptr_s0 + 0x1D)) = (*(u16 *)((u8 *)ptr_s1 + -5));
            (*(u16 *)((u8 *)ptr_s0 + 0x29)) = (*(u16 *)((u8 *)ptr_s1 + -3));

            func_8006671C(packet);
            flags = ((S_800C9088_0 *)object)->unk_14;
            if (flags & 8) {
                if (flags & 4) {
                    ((S_800C9088_2 *)ptr_s0)->unk_00 |= 2;
                }
            }

            call_a1 = packet;
            ASM_KEEP_DEP_NV(call_a1, ptr_s0);   /* MATCH pin: keeps a statement from moving across a call/branch */
            ptr_s0 += 0x34;
            func_8006658C((u8 *)((S_800C9088_1 *)scratch)->unk_20.u +
                              ((S_800C9088_1 *)scratch)->unk_C0 * 4,
                          call_a1);
            ASM_USE_NV(ptr_s0);   /* MATCH pin: retail basic-block layout depends on it */
            packet += 0x34;
            ((S_800C9088_0 *)object)->unk_14 &= 0x7FFF;
        }
    }

    if (((S_800C9088_10_pre *)ptr_s1)[-1].unk_00 != 1 || ((S_800C9088_10 *)ptr_s1)->unk_00 >= 0) {
        ptr_s1 += 0x20;
        indices += 0x20;
        ASM_KEEP(ptr_s1);   /* MATCH pin: retail basic-block layout depends on it */
        ASM_TAILSLOT_PIN(indices);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        func_800C925C();
        return;
    }

    func_80064A40();
    {
        register u8 *state_base ASM_REG("$8") = D_80083160;   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(state_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ((S_800C9088_11 *)(*(u8 **)state_base))->unk_8D0 = packet;
    }
    ASM_KEEP(table);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg2_tail);   /* MATCH pin: retail register colouring depends on it */
}
