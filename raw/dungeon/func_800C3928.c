#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

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
    register u8 *ptr_s1 ASM_REG("$17") = arg0;
    register u8 *ptr_s0 ASM_REG("$16") = arg1;
    register u8 *object ASM_REG("$21") = arg2;
    register u8 *scratch ASM_REG("$18");
    register u8 *indices ASM_REG("$22");
    register u8 *table ASM_REG("$20");
    register u8 *vertices ASM_REG("$23");
    register u8 *packet ASM_REG("$19");
    u8 *arg2_tail;
    u8 *state;
    u8 *descriptor;
    register u8 *call_a0 ASM_REG("$4");
    register u8 *call_a1 ASM_REG("$5");
    register u8 *call_a2 ASM_REG("$6");
    register u8 *call_a3 ASM_REG("$7");
    register s32 table_word ASM_REG("$3");
    register u32 next_index ASM_REG("$2");
    register u32 final_index ASM_REG("$3");
    register s32 word2 ASM_REG("$2");
    register s32 word3 ASM_REG("$3");
    register u32 half_index ASM_REG("$2");
    register u16 half_value ASM_REG("$2");
    register u16 final_half ASM_REG("$3");
    register u8 *word2_ptr ASM_REG("$2");
    register u8 *word3_ptr ASM_REG("$3");
    register u8 *packet_arg0 ASM_REG("$2");
    s32 projected;
    s32 visible;
    s32 flags;
    u16 object_x;
    MATRIX_LOCAL local;
    static void *const keepalive[] = { &&after_switch };

    ASM_KEEP(ptr_s1);
    ASM_KEEP(ptr_s0);
    ASM_KEEP(object);

    local.saved_arg3 = arg3;
    func_800649A0();

    object_x = FIELD(object, u16, 0x1C);
    scratch = (u8 *)0x1F800000;
    FIELD(scratch, s32, 0x30) = object_x;
    FIELD(scratch, s32, 0x34) = FIELD(object, u16, 0x1E);
    FIELD(scratch, s32, 0x38) = FIELD(object, u16, 0x20);
    FIELD(scratch, s32, 0x40) = FIELD(ptr_s0, s16, 2);
    FIELD(scratch, s32, 0x44) = FIELD(ptr_s0, s16, 6);
    FIELD(scratch, s32, 0x48) = FIELD(ptr_s0, s16, 0xA);

    func_80064AE0(&local.matrix);

    FIELD(scratch, s16, 0x60) = 0x1000;
    FIELD(scratch, s16, 0x58) = 0x1000;
    FIELD(scratch, s16, 0x50) = 0x1000;
    FIELD(scratch, s16, 0x5E) = 0;
    FIELD(scratch, s16, 0x5C) = 0;
    FIELD(scratch, s16, 0x5A) = 0;
    FIELD(scratch, s16, 0x56) = 0;
    FIELD(scratch, s16, 0x54) = 0;
    FIELD(scratch, s16, 0x52) = 0;

    func_80065AB0(FIELD(object, u16, 0x16), scratch + 0x50);
    func_80065DF0(FIELD(object, u16, 0x1A), scratch + 0x50);
    func_80065C50(FIELD(object, u16, 0x18), scratch + 0x50);

    ptr_s0 = (u8 *)0x80080000;
    if (FIELD(object, u16, 0x14) & 1) {
        FIELD(scratch, s32, 0x30) = -FIELD(scratch, s32, 0x30);
    }
    if (FIELD(object, u16, 0x14) & 2) {
        FIELD(scratch, s32, 0x34) = -FIELD(scratch, s32, 0x34);
    }

    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064B90(scratch + 0x50, scratch + 0x40);
    func_80064840(scratch + 0x50, ptr_s1, scratch + 0xD0);
    func_80064840(&local.matrix, scratch + 0xD0, scratch + 0x50);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    state = FIELD(ptr_s0, u8 *, 0x3160);
    arg2_tail = object + 0xC;
    FIELD(scratch, u8 *, 0x20) = state + 0xB0;
    packet = FIELD(state, u8 *, 0x8D0);
    ptr_s0 = packet + 7;
    FIELD(object, u16, 0x14) |= 0x8000;

    descriptor = FIELD(object, u8 *, 8);
    indices = FIELD(descriptor, u8 *, 0);
    table = FIELD(descriptor, u8 *, 4);
    vertices = FIELD(descriptor, u8 *, 8);
    ptr_s1 = indices + 0x1F;

    ASM_KEEP(scratch);

    table_word = FIELD(table + FIELD(indices, u16, 0) * 8, s32, 0);
    ASM_KEEP(table_word);
    next_index = FIELD(ptr_s1, u16, -0x1D);
    ASM_KEEP(next_index);
    FIELD(scratch, s32, 0x70) = table_word;
    table_word = FIELD(table + next_index * 8, s32, 0);
    ASM_KEEP(table_word);
    next_index = FIELD(ptr_s1, u16, -0x1B);
    ASM_KEEP(next_index);
    word2_ptr = (u8 *)(next_index * 8 + (u32)table);
    ASM_KEEP(word2_ptr);
    FIELD(scratch, s32, 0x78) = table_word;
    final_index = FIELD(ptr_s1, u16, -0x19);
    ASM_KEEP(final_index);
    word2 = FIELD(word2_ptr, s32, 0);
    ASM_KEEP(word2);
    word3_ptr = (u8 *)(final_index * 8 + (u32)table);
    ASM_KEEP(word3_ptr);
    FIELD(scratch, s32, 0x80) = word2;
    half_index = FIELD(indices, u16, 0);
    ASM_KEEP(half_index);
    word3 = FIELD(word3_ptr, s32, 0);
    ASM_KEEP(word3);

    half_value = FIELD(table + half_index * 8, u16, 4);
    ASM_KEEP(half_value);
    FIELD(scratch, u16, 0x74) = half_value;

    half_value = FIELD(table + FIELD(ptr_s1, u16, -0x1D) * 8, u16, 4);
    ASM_KEEP(half_value);
    call_a0 = scratch + 0x70;
    ASM_KEEP(call_a0);
    FIELD(scratch, u16, 0x7C) = half_value;

    half_index = FIELD(ptr_s1, u16, -0x1B);
    ASM_KEEP(half_index);
    call_a1 = scratch + 0x78;
    ASM_KEEP(call_a1);
    half_value = FIELD(table + half_index * 8, u16, 4);
    ASM_KEEP(half_value);
    call_a2 = scratch + 0x80;
    ASM_KEEP(call_a2);
    FIELD(scratch, u16, 0x84) = half_value;

    half_index = FIELD(ptr_s1, u16, -0x19);
    ASM_KEEP(half_index);
    call_a3 = scratch + 0x88;
    ASM_KEEP(call_a3);
    FIELD(scratch, s32, 0x88) = word3;
    ASM_SCHED_BARRIER();
    final_half = FIELD(table + half_index * 8, u16, 4);
    ASM_KEEP(final_half);

    packet_arg0 = packet + 8;
    ASM_KEEP(packet_arg0);
    FIELD(scratch, u16, 0x8C) = final_half;
    ASM_JALDELAY_PIN(final_half);
    projected = func_80065590(call_a0, call_a1,
                              call_a2, call_a3,
                              packet_arg0, packet + 0x14,
                              packet + 0x20, packet + 0x2C,
                              scratch + 0x90, scratch + 0x94);
    FIELD(scratch, s32, 0xC0) = projected;

    flags = FIELD(object, u16, 0x14) & 3;
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
    func_800C93E0(FIELD(ptr_s0, s32, 1),
                  FIELD(ptr_s0, s32, 0xD),
                  FIELD(ptr_s0, s32, 0x19));
flag_one:
    func_800C93E0(FIELD(ptr_s0, s32, 0xD),
                  FIELD(ptr_s0, s32, 1),
                  FIELD(ptr_s0, s32, 0x19));
flag_two:
    func_800C93E0(FIELD(ptr_s0, s32, 0x19),
                  FIELD(ptr_s0, s32, 0xD),
                  FIELD(ptr_s0, s32, 1));

after_switch:
    visible = func_80065480(FIELD(ptr_s0, s32, 0x19),
                            FIELD(ptr_s0, s32, 1),
                            FIELD(ptr_s0, s32, 0xD));
    FIELD(scratch, volatile s32, 0x114) = visible;
    if (FIELD(scratch, volatile s32, 0x114) > 0) {
        register u16 raw_arg3 ASM_REG("$8");
        register s32 signed_arg3 ASM_REG("$3");

        raw_arg3 = local.saved_arg3;
        ASM_KEEP(raw_arg3);
        signed_arg3 = (s16)raw_arg3;
        FIELD(scratch, s32, 0xC0) -= signed_arg3;
        if ((u32)FIELD(scratch, s32, 0xC0) < 0x1E0) {
            func_80065034(vertices + FIELD(ptr_s1, u16, -0xF) * 8,
                          arg2_tail, packet + 4);
            func_80065034(vertices + FIELD(ptr_s1, u16, -0xD) * 8,
                          arg2_tail, packet + 0x10);
            func_80065034(vertices + FIELD(ptr_s1, u16, -0xB) * 8,
                          arg2_tail, packet + 0x1C);
            func_80065034(vertices + FIELD(ptr_s1, u16, -9) * 8,
                          arg2_tail, packet + 0x28);

            FIELD(ptr_s0, s32, 5) = FIELD(ptr_s1, s32, -0x17);
            FIELD(ptr_s0, u16, 7) += FIELD(object, u16, 0x12);
            FIELD(ptr_s0, s32, 0x11) = FIELD(ptr_s1, s32, -0x13);
            if (FIELD(object, u16, 0x10) != 0) {
                FIELD(ptr_s0, u16, 0x13) =
                    (FIELD(ptr_s0, u16, 0x13) & 0xFF9F) +
                    FIELD(object, u16, 0x10);
            }
            FIELD(ptr_s0, u16, 0x1D) = FIELD(ptr_s1, u16, -5);
            FIELD(ptr_s0, u16, 0x29) = FIELD(ptr_s1, u16, -3);

            func_8006671C(packet);
            flags = FIELD(object, u16, 0x14);
            if (flags & 8) {
                if (flags & 4) {
                    FIELD(ptr_s0, u8, 0) |= 2;
                }
            }

            call_a1 = packet;
            ASM_KEEP_DEP_NV(call_a1, ptr_s0);
            ptr_s0 += 0x34;
            func_8006658C((u8 *)FIELD(scratch, void *, 0x20) +
                              FIELD(scratch, s32, 0xC0) * 4,
                          call_a1);
            ASM_USE_NV(ptr_s0);
            packet += 0x34;
            FIELD(object, u16, 0x14) &= 0x7FFF;
        }
    }

    if (FIELD(ptr_s1, u8, -1) != 1 || FIELD(ptr_s1, s8, 0) >= 0) {
        ptr_s1 += 0x20;
        indices += 0x20;
        ASM_KEEP(ptr_s1);
        ASM_TAILSLOT_PIN(indices);
        func_800C925C();
        return;
    }

    func_80064A40();
    {
        register u8 *state_base ASM_REG("$8") = D_80083160;
        ASM_KEEP(state_base);
        FIELD(*(u8 **)state_base, u8 *, 0x8D0) = packet;
    }
    ASM_KEEP(scratch);
    ASM_KEEP(table);
    ASM_KEEP(vertices);
    ASM_KEEP(arg2_tail);
    ASM_KEEP(object);
}
