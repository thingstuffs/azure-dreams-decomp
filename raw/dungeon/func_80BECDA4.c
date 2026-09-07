#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800BB044(void *);

extern void func_801726B0(void) __attribute__((noreturn));
extern void func_801726B8(void) __attribute__((noreturn));
extern void func_801726C0(void) __attribute__((noreturn));
extern void func_801726CC(void) __attribute__((noreturn));

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170838[28];
extern u8 D_80171014[];
extern u8 D_8017420C[];

void func_801725A4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&L_tail_b0, &&L_tail_b8, &&L_tail_c0, &&L_after_jt
    };
    register void *owner ASM_REG("$21") = arg0;
    register void *motion ASM_REG("$19") = arg1;
    register void *actor ASM_REG("$18") = arg2;
    register void *object ASM_REG("$16") = arg3;
    register s32 special;
    register u8 *selected ASM_REG("$17");
    register s32 x ASM_REG("$2");
    register s32 y ASM_REG("$3");
    s32 kind;
    u32 index;
    void *spawn;
    u8 *entry;
    register u8 *record ASM_REG("$3");
    u8 *record_base;
    register u32 record_id ASM_REG("$4");
    void **dispatch;
    s32 state;
    state = FIELD(owner, u8, 0x9B);
    ASM_KEEP_NV(motion);
    ASM_KEEP_NV(actor);
    ASM_KEEP_NV(object);
    special = 0;
    if (state == 1) {
        goto L_state1;
    }
    if (state < 2) {
        if (state == 0) {
            goto L_state0;
        }
        return;
    }
    ASM_KEEP(state);
    if (state == 2) {
        goto L_state2;
    }
    return;

L_state0:
        if (FIELD(object, s32, 0x1C) & 0x2000) {
            index = (FIELD(object, u16, 0x46) & 0x3FFF) - 1;
            if (index >= 7U) {
                goto L_after_jt;
            }
            dispatch = (void **)D_80170838;
            (void)jt_keep;
            goto *dispatch[index];

L_tail_b0:
            special = 1;
            ASM_TAILSLOT_PIN(special);
            func_801726B0();
L_tail_b8:
            special = 1;
            ASM_TAILSLOT_PIN(special);
            func_801726B8();
L_tail_c0:
            special = 1;
            ASM_TAILSLOT_PIN(special);
            func_801726C0();
        }

        kind = FIELD(object, u16, 0x46) & 0x3FFF;
        if (kind == 2) {
            goto L_kind2;
        }
        if (kind < 3) {
            if (kind == 1) {
                goto L_kind1;
            }
            selected = 0;
            ASM_KEEP(selected);
            goto L_selected;
        }
        if (kind == 3) {
            selected = (u8 *)object + 0xE;
            ASM_TAILSLOT_PIN(selected);
            func_801726CC();
        }
        selected = 0;
        goto L_selected;
L_kind2:
        selected = (u8 *)object + 0xB;
        ASM_TAILSLOT_PIN(selected);
        func_801726CC();
L_kind1:
        ASM_KEEP(state);
        selected = (u8 *)object + 8;
        ASM_TAILSLOT_PIN(selected);
        func_801726CC();

L_after_jt:
        selected = 0;
L_selected:
        if (*selected != 0) {
            FIELD(owner, u16, 0x98) &= 0xFF7F;
            ASM_KEEP(owner);
            x = special;
            ASM_KEEP(x);
            if (x) {
                spawn = D_800814A8;
                FIELD(object, void *, 0x60) = spawn;
                goto L_record;
            }

            record_base = D_8006DE24;
            record_id = *selected;
            entry = record_base + (record_id * 20);
            if (entry[0x12] == 2) {
                spawn = FIELD(object, void *, 0x60);
                if (spawn == 0) {
                    goto L_spawn_ready;
                }
L_record:
                record = *(u8 **)((u8 *)spawn - 0x14);
                FIELD(object, u8, 0x72) = record[0x24];
                FIELD(object, u8, 0x73) = record[0x25];
                goto L_spawn_ready;
            }

            spawn = func_800A05A4(
                object,
                FIELD(actor, u8, 0x24),
                FIELD(actor, u8, 0x25),
                FIELD(object, s16, 0x2A),
                0x10);
            FIELD(object, void *, 0x60) = spawn;

            x = FIELD(object, s8, 0x72);
            y = FIELD(object, s8, 0x73);
            if (x < 0) {
                x = -x;
            }
            if (y < 0) {
                y = -y;
            }
            FIELD(object, u8, 0x72) = x;
            FIELD(object, u8, 0x73) = y;

L_spawn_ready:
            if (func_800A94A0(object, selected, special,
                              (u16 *)((u8 *)owner + 0x98)) == 0) {
                return;
            }
            func_800BB044(object);
            FIELD(owner, u8, 0x9B)++;
            return;
        }

        FIELD(motion, s32, 0x14) = 0;
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0x0C) = 0;
        func_800A2B04(motion, FIELD(actor, u8, 0x24), FIELD(actor, u8, 0x25));
        D_8008346C = 0;
        FIELD(D_800814A8, u16, 0xA6)--;
        func_800A4ACC(object);
        FIELD(object, u8, 0x6D)--;
        FIELD(owner, void *, 0x8C) = D_80171014;
        FIELD(object, u8, 0x73) = 0;
        FIELD(object, u8, 0x72) = 0;
        FIELD(object, u16, 0x46) &= 0x7FFF;
        return;

L_state1:
        if (func_8003F270() != 0) {
            FIELD(actor, u16, 0x14) |= 0x0800;
            return;
        }
        FIELD(actor, u16, 0x14) &= 0xF7FF;
        FIELD(owner, u8, 0x9B)++;

L_state2:
        if (FIELD(actor, s8, 4) == 4) {
            if (FIELD(actor, u16, 0x14) & 0x1000) {
                goto L_state2_ready;
            }
        }
        if ((FIELD(actor, u16, 0x14) & 0xE000) == 0) {
            return;
        }

L_state2_ready:
        FIELD(owner, u16, 0x98) |= 0x80;
        if ((FIELD(actor, u16, 0x14) & 0xE000) == 0) {
            return;
        }

        FIELD(motion, s32, 0x14) = 0;
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0x0C) = 0;
        func_800A2B04(motion, FIELD(actor, u8, 0x24), FIELD(actor, u8, 0x25));

        {
            u8 *direction_table = D_8017420C;
            if (FIELD(actor, u8 *, 0x2C) != direction_table) {
                FIELD(actor, u8 *, 0x2C) = direction_table;
                func_80047784(
                    actor,
                    direction_table[((D_80083228 + FIELD(object, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
        }

        {
            u8 *status = (u8 *)&D_80083460;
            if (FIELD(status, s32, 0xC) != 0) {
                return;
            }
            FIELD(status, u16, 0xA)--;
        }
        FIELD(owner, void *, 0x8C) = D_80171014;
        func_800A4ACC(object);
        FIELD(object, u8, 0x73) = 0;
        FIELD(object, u8, 0x72) = 0;
        FIELD(object, u8, 0x6D)--;
        FIELD(object, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
}

/* MECHANISM: 0x38 frame, owner/motion/actor/object pinned to s5/s3/s2/s0, `special`
   in s4 (UNPINNED -- the $20 pin was what pushed the constant-1 CSE off $a0 and the
   0x2000 test temp off $v0), `selected` in s1 and `record` in $v1 (the -0x14 chain
   reuses $v0 for both byte temps only when record owns $v1).  The `if (special)` arm
   is a real `goto L_record` -- as a noreturn fake-call gcc predicted it unlikely and
   filled the branch delay from the TARGET block (%hi(D_8006DE24)) instead of retail's
   fall-through %hi(D_800814A8).  The ASM_KEEP(owner) inside L_selected is a pure
   scheduling fence: without it gcc hoists the 0x98 RMW out of place (+25 words).
   PROLOGUE STORE ORDER: retail emits `sw $s4,0x28($sp)` BEFORE `sw $ra,0x30($sp)`, and
   a VOLATILE empty asm (ASM_KEEP, and every output-less ASM_USE_* and ASM_SET spelling) is a
   full sched2 barrier -- it depends on every register and calls flush_pending_lists --
   so all seven post-reload `sw sN/ra` collapse to one INSN_PRIORITY and fall back to
   save_restore_insns emission order ($ra first).  The three ASM_KEEP_NV(motion/actor/
   object) placed BEFORE `special = 0` are the fix: _NV has an output operand, so it is
   NOT implicitly volatile and NOT a barrier -- it only adds a data dependence, lifting
   each `move $sN,$aM` to priority 2 (its store to 3) while `sw $s4` stays 2 and
   `sw $ra`/`sw $s1` stay 1, which is retail's order; and because the keeps sit after
   the lbu and before `special = 0`, `move $20,$0` stays at the bottom of the entry
   block and the beq takes it as its delay slot.  EXACT, 269/269 words.
   RATCHET: the four mid-row shared tails are declared `noreturn` -- the REGISTERED
   tail-jump shape (docs/fidelity_ratchet.md SS2, config/noreturn_syms.dungeon.txt).
   The declaration is load-bearing, not decoration: spelling those tails `goto` costs
   the match (273/269 words, aligned 22, measured). */
