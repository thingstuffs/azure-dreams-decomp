#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80024064(void);
extern void func_800240C8(void);
extern void func_80024160(void);
extern void func_800243C8(void);
extern void func_80024640(void);
extern void func_8002467C(void);
extern void func_800247C8(void) __attribute__((noreturn));
extern void func_800246F0(void);
extern void func_80024790(void);
extern void func_8002485C(void);
extern void func_80024884(void);
extern void func_80024924(void);
extern void func_800249F4(void);
extern void func_80024AA8(void);

extern void func_800B835C(void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern void func_80024DE8(void *, void *);
extern s32 func_8009FCF0(s32, s32, s32, s32);
extern void func_800A56E0(s32);
extern s32 func_800A45D8(s32, s32, s32);
extern void func_80065F90(s32, s32);
extern void *func_80024C80(void *, void *, s32);
extern void func_800262B8(void *, s32, void *);
extern void func_800241E8(void) __attribute__((noreturn));
extern void func_80024380(void) __attribute__((noreturn));
extern void func_8002477C(void) __attribute__((noreturn));

extern void *D_80024008[];
extern u8 D_80026324[];
extern u8 D_80026326[];
extern u8 D_80026328[];
extern u8 D_8002632A[];
extern u8 D_8002632C[];
extern u8 D_80045340[];
extern u8 D_80026344[];
extern u8 D_80026470[];
extern u8 D_80026474[];
extern u8 D_80026878[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];
extern u8 D_800814A0[];
extern u8 D_8008346C[];

#ifdef __mips__
static void (*const func_81886800_table[])(void) __asm__("func_81886800")
    __attribute__((section(".text.func_81886800"), aligned(4))) = {
    func_80024064,
    0,
    func_800240C8,
    func_80024160,
    func_800243C8,
    func_80024640,
    func_8002467C,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800246F0,
    func_80024790,
    func_8002485C,
    func_80024884,
    func_80024924,
    func_800249F4,
    func_80024AA8,
};
#define BODY_NAME func_81886864
#else
#define BODY_NAME func_81886864
#endif

void BODY_NAME(void *arg0_in, void *arg1_in, void *arg2_in)
    __attribute__((section(".text.func_81886800")));
void BODY_NAME(void *arg0_in, void *arg1_in, void *arg2_in)
{
#ifdef __mips__
    register void *arg0 ASM_REG("$16") = arg0_in;
    register void *arg1 ASM_REG("$17") = arg1_in;
    register void *arg2 ASM_REG("$19") = arg2_in;
    register void *state_object ASM_REG("$18");
    register void *base ASM_REG("$20");
    register void *copy ASM_REG("$21");
#else
    void *arg0 = arg0_in;
    void *arg1 = arg1_in;
    void *arg2 = arg2_in;
    void *state_object;
    void *base;
    void *copy;
#endif
    s32 state;
    u32 state_valid;
#ifdef __mips__
    register u16 state_bits ASM_REG("$2");
#else
    u16 state_bits;
#endif
    s16 result[3];
    s32 rect[2];
    static void *const switch_keep[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7, &&case_8, &&case_9,
        &&case_10, &&case_11, &&case_12, &&case_13, &&case_14,
        &&case_15, &&case_16, &&case_17,
    };

    state_object = FIELD(arg0, void *, 0);
    state = FIELD(arg0, s16, 0xA);
    base = (u8 *)state_object - 0x20;
    state_valid = (u32)state < 18u;
    copy = FIELD(base, void *, 8);
    if (!state_valid) {
        goto end;
    }
    (void)switch_keep;
    goto *D_80024008[state];

case_0:
    rect[0] = 0x01000340;
    rect[1] = 0x00200020;
    func_800B835C(D_8002632C, rect, 1, 0);

    FIELD(arg2, u32, 0xC) = 0x00808080;
    FIELD(arg2, u16, 0x1E) = 0x555;
    FIELD(arg2, u16, 0x1C) = 0x555;
    FIELD(arg2, void *, 8) = D_80026344;
    FIELD(D_80026324, u16, 0) = 0;
    FIELD(D_80026328, u16, 0) = 0;
    FIELD(D_8002632A, u16, 0) = 0;
    FIELD(D_80026470, s32, 0) = 0;
    state_bits = FIELD(state_object, u16, 0x2A);
    FIELD(D_80026474, s32, 0) = 0;
    FIELD(arg0, u16, 0x16) = (state_bits >> 9) & 7;
    FIELD(arg0, u16, 0xA)++;

    if (func_8003DF74(
            FIELD(FIELD(base, void *, 0xC), void *, 8),
            FIELD(base, void *, 0xC), result, 0) == 0) {
        if ((FIELD(FIELD(base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
            goto end;
        }
    }

    FIELD(arg1, u16, 2) = FIELD(copy, u16, 2);
    FIELD(arg1, u16, 6) = FIELD(copy, u16, 6);
    if (FIELD(FIELD(base, void *, 0xC), u16, 0x14) & 0x8000) {
        {
#ifdef __mips__
            register s32 tail_value ASM_REG("$2");
#else
            s32 tail_value;
#endif
            tail_value = FIELD(copy, u16, 0xA) - 64;
            ASM_TAILSLOT_PIN(tail_value);
            func_800241E8();
        }
    }
    FIELD(arg1, u16, 0xA) = FIELD(copy, u16, 0xA) + result[2];
    FIELD(arg0, u16, 0x2E) = FIELD(arg1, u16, 0xA);
    ASM_SCHED_BARRIER();

    {
        void *holder = FIELD(arg0, void *, 4);
        if ((FIELD(holder, u16, 0) & 0x80) == 0) {
            goto end;
        }
        if ((FIELD(arg0, u8, 0x12) & 4) == 0) {
            func_8004491C((u8 *)arg0 - 0x20, D_80045340);
            FIELD(arg2, u16, 0x10) = 0x20;
            FIELD(arg2, u8, 0xE) = 0x80;
            FIELD(arg2, u8, 0xD) = 0x80;
            FIELD(arg2, u8, 0xC) = 0x80;
            FIELD(arg2, u16, 0x14) |= 0xC;
            FIELD(arg0, u8, 0x12) |= 4;
        }
    }

    {
        if (FIELD(state_object, void *, 0x60) == 0) {
            goto case_0_no_object;
        }
        {
#ifdef __mips__
            register void *entry_copy ASM_REG("$4");
#else
            void *entry_copy;
#endif
            entry_copy =
                FIELD(FIELD(state_object, void *, 0x60), void *, -0x18);
            FIELD(arg0, u16, 0xC) = FIELD(entry_copy, u16, 2);
            FIELD(arg0, u16, 0xE) = FIELD(entry_copy, u16, 6);
            {
                #ifdef __mips__
                register u8 index ASM_REG("$3");
                register u8 *table ASM_REG("$2");
                #else
                u8 index;
                u8 *table;
                #endif
                table = D_800DDC40;
                index = FIELD(FIELD(state_object, void *, 0x60), u8, 0x13);
                FIELD(arg0, u16, 0x10) =
                    FIELD(entry_copy, u16, 0xA) - table[index];
            }
            {
                s16 index;
                u8 value;
                index = FIELD(arg0, s16, 0x16);
                entry_copy = FIELD(state_object, void *, -0x14);
                value = FIELD(entry_copy, u8, 0x24) +
                        D_8006CCD8[(s32)index * 2];
                FIELD(arg0, u8, 0x1E) = value;
                FIELD(arg0, u8, 0x20) = value;
            }
            {
                s16 index;
                u8 value;
                index = FIELD(arg0, s16, 0x16);
                value = FIELD(entry_copy, u8, 0x25) +
                        D_8006CCE8[(s32)index * 2];
                FIELD(arg0, u8, 0x1F) = value;
                FIELD(arg0, u8, 0x21) = value;
            }
            {
#ifdef __mips__
                register s32 left ASM_REG("$2");
                register s32 right ASM_REG("$3");
#else
                s32 left;
                s32 right;
#endif
                s32 delta;
                left = FIELD(state_object, s8, 0x72);
                right = FIELD(entry_copy, u8, 0x24);
                if (left == right) {
                    left = FIELD(state_object, s8, 0x73);
                    right = FIELD(entry_copy, u8, 0x25);
                    delta = left - right;
                } else {
                    delta = left - right;
                }
                if (delta < 0) {
                    delta = -delta;
                }
                FIELD(arg0, u16, 0x14) = delta + 1;
            }
        }
    }
    func_80024380();

case_0_no_object:
    FIELD(arg0, u16, 0x14) = 8;
    FIELD(arg0, u16, 0xC) = FIELD(arg1, u16, 2);
    FIELD(arg0, u16, 0xE) = FIELD(arg1, u16, 6);
    FIELD(arg0, u16, 0x10) = FIELD(state_object, u16, 0x88) - 80;
    ASM_SCHED_BARRIER();
    {
        u8 *table0 = D_8006CCD8;
        s16 index = FIELD(arg0, s16, 0x16);
        FIELD(arg1, u16, 0xE) =
            FIELD(table0 + (s32)index * 2, s16, 0) * 8;
        {
        u8 *table1 = D_8006CCE8;
            s16 index2 = FIELD(arg0, s16, 0x16);
            FIELD(arg1, u16, 0x12) =
                FIELD(table1 + (s32)index2 * 2, s16, 0) * 8;
        }
    }
    func_8002477C();

case_1:
    {
        #ifdef __mips__
        register s32 delta ASM_REG("$3");
        register s32 value ASM_REG("$4");
        #else
        s32 delta;
        s32 value;
        #endif
        delta = FIELD(arg1, s32, 0xC);
        value = delta;
        FIELD(arg1, s32, 0) += delta;
        ASM_KEEP(delta);
        value += value >> 4;
        FIELD(arg1, s32, 0xC) = value;
        if ((value < 0 ? -value : value) > 0x200000) {
            value = value > 0 ? 0x200000 : -0x200000;
            FIELD(arg1, s32, 0xC) = value;
        }
    }
    {
        #ifdef __mips__
        register s32 delta ASM_REG("$3");
        register s32 value ASM_REG("$4");
        #else
        s32 delta;
        s32 value;
        #endif
        delta = FIELD(arg1, s32, 0x10);
        value = delta;
        FIELD(arg1, s32, 4) += delta;
        ASM_KEEP(delta);
        value += value >> 4;
        FIELD(arg1, s32, 0x10) = value;
        if ((value < 0 ? -value : value) > 0x200000) {
            value = value > 0 ? 0x200000 : -0x200000;
            FIELD(arg1, s32, 0x10) = value;
        }
    }
    {
        s32 value = FIELD(arg0, s32, 0x2C);
        value += (((s32)FIELD(arg0, s16, 0x10) << 16) - value) >> 4;
        FIELD(arg0, s32, 0x2C) = value;
        value = FIELD(arg1, s32, 8);
        value += (((s32)FIELD(arg0, s16, 0x10) << 16) - value) >> 4;
        FIELD(arg1, s32, 8) = value;
    }
    {
        s32 value = func_800644B8((s32)FIELD(arg0, s16, 0x18) << 7);
        FIELD(arg1, s32, 8) += value << 6;
    }
    func_80024DE8(arg1, arg2);
    {
        s32 value = FIELD(arg1, s16, 2);
        if (value < 0) {
            value += 63;
        }
        FIELD(arg0, u8, 0x1E) = value >> 6;
        value = FIELD(arg1, s16, 6);
        if (value < 0) {
            value += 63;
        }
        FIELD(arg0, u8, 0x1F) = value >> 6;
    }
    if (FIELD(arg0, s16, 0x20) == FIELD(arg0, s16, 0x1E)) {
        goto end;
    }
    if (FIELD(state_object, void *, 0x60) != 0) {
        if (FIELD(arg0, s16, 0x58) == 0) {
            s32 value = func_8009FCF0(
                FIELD(arg0, volatile u8, 0x1E),
                FIELD(arg0, volatile u8, 0x1F),
                FIELD(state_object, volatile u8, 0x72),
                FIELD(state_object, volatile u8, 0x73));
            value = (s16)value;
            if (value < 5) {
                FIELD(arg0, s16, 0x58) = 1;
                func_800A56E0(0x300);
            }
        }
    }
    if (FIELD(state_object, void *, 0x60) != 0) {
        if ((FIELD(state_object, volatile u32, 0x70) & 0xFFFF0000) ==
            (FIELD(arg0, volatile u32, 0x1C) & 0xFFFF0000)) {
#ifdef __mips__
            register void *identity_work ASM_REG("$4");
#else
            void *identity_work;
#endif
            identity_work = arg1;
            {
                s32 coordinate = FIELD(state_object, s8, 0x72);
                FIELD(arg1, s16, 2) = (coordinate << 6) + 0x20;
            }
            {
                s32 coordinate = FIELD(state_object, s8, 0x73);
                FIELD(arg1, s16, 6) = (coordinate << 6) + 0x20;
            }
            FIELD(arg1, u16, 0xA) = FIELD(arg0, u16, 0x10);
            func_80024DE8(identity_work, arg2);
            {
                u16 counter = FIELD(arg0, u16, 0xA);
                u16 global_value =
                    FIELD(FIELD(state_object, void *, 0x60), u16, 0x88);
                counter++;
                FIELD(arg0, u16, 0xA) = counter;
                FIELD(D_80026878, u16, 0) = global_value;
            }
            func_800247C8();
        }
    }

case_1_continue:
    {
        u8 x = FIELD(arg0, u8, 0x1E);
        u8 y = FIELD(arg0, u8, 0x1F);
        s32 timer = FIELD(arg0, u16, 0x14) - 1;
        s32 collision;
        FIELD(arg0, u16, 0x14) = timer;
        FIELD(arg0, u8, 0x20) = x;
        FIELD(arg0, u8, 0x21) = y;
        if ((timer << 16) != 0) {
            s32 ax = (((s32)FIELD(arg0, s8, 0x1E) << 6) + 0x20) & 0xFFE0;
            s32 ay = (((s32)FIELD(arg0, s8, 0x1F) << 6) + 0x20) & 0xFFE0;
            collision = func_800A45D8(ax, ay, FIELD(arg0, s16, 0x2E));
            if ((collision << 16) == 0) {
                goto end;
            }
        }
        FIELD(arg0, u16, 0xA) = 16;
        func_800247C8();
    }

case_2:
    func_80065F90(FIELD(arg1, s16, 0xE), FIELD(arg1, s16, 0x12));
    {
#ifdef __mips__
    register void *map_pointer ASM_REG("$7");
#else
    void *map_pointer;
#endif
    FIELD(arg0, void *, 0x28) = func_80024C80(
        arg0, arg1, (map_pointer = FIELD(state_object, void *, 0x60),
                    FIELD(map_pointer, s16, 0x88)));
    if (FIELD(arg0, void *, 0x28) == 0) {
        goto end;
    }
    FIELD(arg0, u16, 0xA)++;
    FIELD(arg2, u8, 0xC) -= FIELD(arg2, u8, 0xC) >> 2;
    FIELD(arg2, u8, 0xD) -= FIELD(arg2, u8, 0xD) >> 2;
    FIELD(arg2, u8, 0xE) -= FIELD(arg2, u8, 0xE) >> 2;
    if ((FIELD(FIELD(arg0, void *, 0x28), u16, 0x1E) & 0x8000) == 0) {
        goto end;
    }
    if (FIELD(state_object, void *, 0x60) != 0) {
        func_800262B8(FIELD(state_object, void *, 0x60),
                      FIELD(arg0, u8, 9), state_object);
    }
    FIELD(arg0, u16, 0xA) = 17;
    func_800247C8();
    }

case_3:
    {
#ifdef __mips__
    register void *work ASM_REG("$4");
#else
    void *work;
#endif
    work = arg1;
    FIELD(work, s32, 0) += FIELD(work, s32, 0xC);
    FIELD(work, s32, 4) += FIELD(work, s32, 0x10);
    {
        s32 target = (s32)FIELD(arg0, s16, 0x10) << 16;
        s32 value = FIELD(work, s32, 8);
        value += (target - value) >> 4;
        FIELD(work, s32, 8) = value;
    }
    FIELD(arg2, u8, 0xC) -= FIELD(arg2, u8, 0xC) >> 1;
    FIELD(arg2, u8, 0xD) -= FIELD(arg2, u8, 0xD) >> 1;
    FIELD(arg2, u8, 0xE) -= FIELD(arg2, u8, 0xE) >> 1;
    func_80024DE8(work, arg2);
    if (FIELD(arg2, u8, 0xC) < 2) {
        FIELD(arg0, u16, 0xA)++;
        func_800247C8();
    } else {
        goto end;
    }
    }

case_4:
    if (FIELD(D_80026326, s16, 0) != 0) {
        goto end;
    }
    FIELD(D_8008346C, s32, 0) = 0;
    FIELD((u8 *)arg0 - 2, u16, 0) |= 0x8000;
    FIELD(D_800814A0, s32, 0) |= 0x8000;

case_5:
case_6:
case_7:
case_8:
case_9:
case_10:
case_11:
case_12:
case_13:
case_14:
case_15:
case_16:
case_17:
end:
    {
        u16 end_count = FIELD(arg0, u16, 0x18);
        FIELD(D_80026326, u16, 0) = 0;
        FIELD(arg0, u16, 0x18) = end_count + 1;
    }
}

#ifdef __mips__
__asm__(
    ".globl func_81886800\n"
    ".type func_81886800,@function\n"
    ".size func_81886800,2052\n");
#endif
