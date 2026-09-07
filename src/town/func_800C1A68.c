/* func_800BF1C8 (TOWN row func_800C1A68) -- byte-exact production source.
 * Stock config: 2.7.2-cdk-G0  (toolchain/compilers/gcc-2.7.2-cdk, -S -O2 -G0).
 *
 * Three deltas from the W52/W65/W72 frontier best_clean_defined.c, each with a
 * named compiler mechanism:
 *   1. `const Counter *counter_p = &D_80012D5C;` hoisted above the flag test, so
 *      expand emits high(D_80012D5C) BEFORE the flag branch (cse folds the
 *      lo_sum into the else-arm load, so no extra word).
 *   2. `do { ... } while (0)` around the state-0 arm.  Its NOTE_INSN_LOOP_BEG/END
 *      survive to local-alloc, where they make flow.c's loop-depth-weighted
 *      reg_n_refs != 2 and update_equiv_regs' move path depth != 0 -- which is
 *      what stops local-alloc sinking that high back down to its use.
 *   3. `abs()` (gcc BUILT_IN_ABS) instead of the hand-expanded unsigned negate.
 *      It selects mips.md's `abssi2`, a single type="multi" INSN, so reorg sees
 *      no JUMP_INSN there and cannot steal the threshold `ori` into a delay slot.
 *
 * No pins, ASM_KEEP, inline asm, volatile, barriers, fake callees or fake
 * externs.  `keepalive` holds the addresses of the five REAL retail jump-table
 * targets (D_800898D4 @ file offset 0xC174 = BF268,BF318,BF354,BF2B0,BF3A8,
 * BF354); it is required only to stop gcc deleting arms it cannot see reached.
 */
#include "common.h"


typedef struct Obj {
    char pad0[0x68];
    s16 state;
    char pad6A[2];
    u16 counter;
} Obj;

typedef struct Arg1 {
    s32 x;
    s32 y;
} Arg1;

typedef struct Arg2 {
    char pad0[0x1A];
    u16 cursor;
} Arg2;

typedef struct Entry {
    u8 bytes[8];
} Entry;

typedef struct EntryPair {
    Entry entries[2];
} EntryPair;

typedef struct Counter {
    u32 value;
    u32 pad[2];
} Counter;

extern EntryPair D_800898C4;
extern void *D_800898D4[];
extern u8 D_80011F81[];
extern Counter D_80012D5C;
extern s32 D_80083780[];

extern int abs(int);

extern s32 func_800352FC(void);
extern void func_80053DA8(s32);
extern void func_800673A0(void *, s32, s32);
extern s32 func_800C2AB4(Obj *);
void func_800BF1C8(Obj *self, Arg1 *arg1, Arg2 *arg2) {
    EntryPair local;
    s32 state;
    register s32 work;
    register s32 operand;
    register s32 value;
    static void *const keepalive[5] = {&&state0, &&state3, &&state1, &&state2or5, &&state4};

    local = D_800898C4;
    self->counter = self->counter - 1;
    state = self->state;
    if ((u32)state >= 6) {
        return;
    }
    goto *D_800898D4[state];

state0:
    do {
        const Counter *counter_p = &D_80012D5C;
        operand = 0;
        if (D_80011F81[0] != 0) {
            operand = 1;
        } else {
            value = counter_p->value;
            if ((u32)value >= 0x1388U) {
                operand = 1;
            }
        }
        func_800673A0(&local.entries[operand], 0x188, 0x180);
    } while (0);
state3:
    {
        work = 0x3FFFFF;
        value = D_80083780[0];
        operand = arg1->x;
        {
            s32 magnitude = abs((s32)((u32)value - (u32)operand));
            work = work < magnitude;
        }
        if (work != 0) {
            return;
        }
    }
    if (func_800352FC() == 0) {
        return;
    }
    if (func_800C2AB4(self) == 0) {
        return;
    }
    func_80053DA8(0x50B);
    self->counter = 0x20;
    self->state = (u16)self->state + 1;
    return;

state1:
    if (D_80083780[1] < arg1->y + 0x800000) {
        D_80083780[1] += 0x40000;
    }
    {
        register s32 value = arg2->cursor;
        value -= 0x20;
        arg2->cursor = value;
        goto wait_for_counter;
    }

state2or5:
    if (func_800352FC() != 0 && func_800C2AB4(self) != 0) {
        return;
    }
    {
        s32 next_state = self->state;
        next_state += 1;
        next_state %= 6;
        self->state = (s16)next_state;
        return;
    }

state4:
    arg2->cursor += 0x20;
wait_for_counter:
    if ((s16)self->counter > 0) {
        return;
    }
    self->state = (u16)self->state + 1;
}
