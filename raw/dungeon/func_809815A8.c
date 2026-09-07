#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738(void *, u8, s8);
extern void func_80047784(void *, u8, s32);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s16 func_800BCB04(u16, u16, s16);

extern void func_80164F3C(void) __attribute__((noreturn));
extern void func_80164FE4(void) __attribute__((noreturn));
extern void func_80165050(void) __attribute__((noreturn));
extern void func_80165408(void) __attribute__((noreturn));

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern void D_801654D4(void);
extern u8 D_801680E0[];
extern u8 D_801680E8[];
extern Callback D_80168168[];

void func_80164DA8(void *arg0_, void *arg1_, void *arg2_)
{
    register void *arg0 ASM_REG("$17") = arg0_;
    register void *arg1 ASM_REG("$21") = arg1_;
    register void *arg2 ASM_REG("$20") = arg2_;
    register void *state ASM_REG("$19") = arg0;
    register u8 *tail_value ASM_REG("$2");
    register s32 tail_index ASM_REG("$2");
    register s32 tail_state ASM_REG("$3");
    register void *tail_arg ASM_REG("$4");
    register u8 *tail_base ASM_REG("$5");
    s16 old_state;
    s16 direction;
    s16 direction_copy;
    register s32 height ASM_REG("$4");
    s32 angle;
    register s32 call_arg ASM_REG("$4");
    register s32 raw_height ASM_REG("$3");
    s16 ground;
    s16 delta;
    u16 part_flags;
    register u16 count ASM_REG("$3");
    u32 flags;
    s32 saved_offset;
    Callback callback;
    Callback callback2;

    if (D_80083462 & 0x2000) {
        callback = FIELD(arg0, Callback, 0x8C);
        if (callback == (Callback)D_801654D4) {
            ASM_KEEP(arg0_);
            callback(arg0_, arg1_, arg2_, arg0_);
            return;
        }
        FIELD(arg0, u8, 0x71) &= 0x7F;
        return;
    }

    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    ASM_KEEP(state);

    old_state = (s8)FIELD(arg0, u8, 0x6D);
    if (func_800A9E70(arg0, arg1, arg2, arg0) != 0) {
        return;
    }

    callback2 = FIELD(arg0, Callback, 0x8C);
    if (callback2 != 0) {
        callback2(arg0, arg1, arg2, arg0);
    }
    D_80168168[FIELD(arg0, u8, 0x9A)](arg0, arg1, arg2, arg0);
    if ((s16)old_state != FIELD(arg0, s8, 0x6D)) {
        func_800AA36C(arg0, arg1, arg2, arg0);
    }

    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);

    if (!(FIELD(arg0, u32, 0x1C) & 0x40000) &&
        !(FIELD(arg0, u16, 0x98) & 8)) {
        FIELD(arg1, s32, 0x14) += FIELD(arg0, s8, 0x9D) * 0x14000;
        FIELD(arg0, u8, 0x9D)++;
        func_80164F3C();
    }

    FIELD(arg0, u8, 0x9D) = 0;
    ASM_SCHED_BARRIER();
    FIELD(arg0, s32, 0x90) += FIELD(arg1, s32, 0x14);
    part_flags = FIELD(arg2, u16, 0x14);

    if (!(part_flags & 0x8000)) {
        direction = ((D_80083228 + FIELD(state, s16, 0x2A) + 0x100) >> 9) & 7;
        direction_copy = direction;
        if (FIELD(arg0, s16, 0x94) != direction_copy) {
            func_80047738(arg2,
                FIELD(FIELD(arg2, u8 *, 0x2C), u8, direction_copy),
                FIELD(arg2, s8, 4));
            FIELD(arg0, s16, 0x94) = direction;
        }
        if (D_8006CCF8[direction_copy] != 0) {
            register u32 scratch ASM_REG("$2");
            scratch = FIELD(arg2, u16, 0x14) | 1;
            ASM_TAILSLOT_PIN(scratch);
            func_80164FE4();
        }
        FIELD(arg2, u16, 0x14) &= 0xFFFE;
        func_800A020C(FIELD(state, s32, 0x1C), (u8 *)arg2 + 0xC);
        if (!(FIELD(state, u32, 0x1C) & 0x20)) {
            if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
                func_800478B8(arg2);
                tail_value = (u8 *)0xF7FF0000;
                ASM_PAGEBASE_PIN(tail_value);
                func_80165050();
            }
        } else {
            FIELD(arg2, u16, 0x14) |= 0x7000;
            FIELD(state, u32, 0x1C) &= 0xFFFBFFFF;
        }

        {
            register u32 masked_flags ASM_REG("$3");
            masked_flags = FIELD(state, u32, 0x1C) & 0xF7FFFFFF;
            FIELD(state, u32, 0x1C) = masked_flags;
            masked_flags &= 0x40000;
            ASM_KEEP(masked_flags);
            if (!masked_flags) {
                goto reset_offset;
            }
        }

        if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
            if (FIELD(arg2, u8 *, 0x2C) == D_801680E0) {
                if (FIELD(arg2, u16, 4) == 0x100) {
                    FIELD(arg0, u16, 0x9E) = 0;
                }
                count = FIELD(arg0, u16, 0x9E);
                ASM_KEEP(count);
                angle = (s32)((u32)count << 16) >> 16;
                call_arg = angle * 0xE3;
                ASM_KEEP(call_arg);
                count++;
                FIELD(arg0, u16, 0x9E) = count;
                FIELD(arg0, s32, 0xA0) = func_800644B8(call_arg) << 7;
                if (FIELD(arg2, u16, 4) == 0x103) {
                    tail_base = D_801680E8;
                    FIELD(arg2, u8 *, 0x2C) = tail_base;
                    tail_index = D_80083228;
                    tail_state = FIELD(state, s16, 0x2A);
                    ASM_KEEP(tail_state);
                    tail_arg = arg2;
                    ASM_KEEP(tail_arg);
                    tail_index = ((tail_index + tail_state + 0x100) >> 9) & 7;
                    tail_value = &tail_base[tail_index];
                    goto play_tail_value_1;
                }
            } else if (FIELD(arg2, u8 *, 0x2C) == D_801680E8) {
                count = FIELD(arg0, u16, 0x9E);
                ASM_KEEP(count);
                angle = (s32)((u32)count << 16) >> 16;
                call_arg = angle * 0xE3;
                ASM_KEEP(call_arg);
                count++;
                FIELD(arg0, u16, 0x9E) = count;
                FIELD(arg0, s32, 0xA0) = func_800644B8(call_arg) << 7;
                if (FIELD(arg2, u16, 4) == 0x103) {
                    FIELD(arg2, u8 *, 0x2C) = D_801680E0;
                    tail_index = D_80083228;
                    tail_state = FIELD(state, s16, 0x2A);
                    ASM_KEEP(tail_state);
                    tail_arg = arg2;
                    ASM_KEEP(tail_arg);
                    tail_index = ((tail_index + tail_state + 0x100) >> 9) & 7;
                    tail_value = &D_801680E0[tail_index];
play_tail_value_1:
                    func_80047784(tail_arg, *tail_value, 0);
                }
            }
        }

        if (!(FIELD(arg0, u16, 0x98) & 8)) {
            register s32 height_work ASM_REG("$2") = -0x20;
            height = FIELD(arg0, s16, 0x92);
            raw_height = FIELD(arg0, u16, 0x92);
            if (height_work < height) {
                height_work = raw_height - 8;
                FIELD(arg0, s16, 0x92) = height_work;
                func_80165408();
            }
            goto low_height_adjustment;
        }
        goto final_adjustment;
    }

    FIELD(arg2, u16, 0x14) = (part_flags & 0x800)
        ? (part_flags & 0x8FFF)
        : (part_flags | 0x7000);
    FIELD(state, u32, 0x1C) &= 0xF7FFFFFF;
    if (!(FIELD(state, u32, 0x1C) & 0x40000)) {
reset_offset:
        saved_offset = FIELD(arg0, s32, 0xA0);
        FIELD(arg0, u16, 0x9E) = 0;
        FIELD(arg0, s32, 0xA0) = 0;
        FIELD(arg0, s32, 0x90) -= saved_offset;
        if (!(FIELD(arg0, u16, 0x98) & 8)) {
            ground = func_800BCB04(FIELD(arg1, u16, 2),
                FIELD(arg1, u16, 6),
                (s16)(FIELD(state, u16, 0x88) - 0x20));
            delta = ground - FIELD(state, u16, 0x88);
            if (delta < FIELD(arg0, s16, 0x92)) {
                FIELD(arg0, s16, 0x92) = delta;
                FIELD(arg0, u8, 0x9D) = 0;
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(state, u32, 0x1C) |= 0x08000000;
                func_80165408();
            }
        }
        goto final_adjustment;
    }

    if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
        if (FIELD(arg2, u8 *, 0x2C) == D_801680E0) {
            if (FIELD(arg2, u16, 4) == 0x100) {
                FIELD(arg0, u16, 0x9E) = 0;
            }
            count = FIELD(arg0, u16, 0x9E);
            ASM_KEEP(count);
            angle = (s32)((u32)count << 16) >> 16;
            call_arg = angle * 0xE3;
            ASM_KEEP(call_arg);
            count++;
            FIELD(arg0, u16, 0x9E) = count;
            FIELD(arg0, s32, 0xA0) = func_800644B8(call_arg) << 7;
            if (FIELD(arg2, u16, 4) == 0x103) {
                tail_base = D_801680E8;
                FIELD(arg2, u8 *, 0x2C) = tail_base;
                tail_index = D_80083228;
                tail_state = FIELD(state, s16, 0x2A);
                ASM_KEEP(tail_state);
                tail_arg = arg2;
                ASM_KEEP(tail_arg);
                tail_index = ((tail_index + tail_state + 0x100) >> 9) & 7;
                tail_value = &tail_base[tail_index];
                goto play_tail_value_2;
            }
        } else if (FIELD(arg2, u8 *, 0x2C) == D_801680E8) {
            count = FIELD(arg0, u16, 0x9E);
            ASM_KEEP(count);
            angle = (s32)((u32)count << 16) >> 16;
            call_arg = angle * 0xE3;
            ASM_KEEP(call_arg);
            count++;
            FIELD(arg0, u16, 0x9E) = count;
            FIELD(arg0, s32, 0xA0) = func_800644B8(call_arg) << 7;
            if (FIELD(arg2, u16, 4) == 0x103) {
                FIELD(arg2, u8 *, 0x2C) = D_801680E0;
                tail_index = D_80083228;
                tail_state = FIELD(state, s16, 0x2A);
                ASM_KEEP(tail_state);
                tail_arg = arg2;
                ASM_KEEP(tail_arg);
                tail_index = ((tail_index + tail_state + 0x100) >> 9) & 7;
                tail_value = &D_801680E0[tail_index];
play_tail_value_2:
                func_80047784(tail_arg, *tail_value, 0);
            }
        }
    }

    if (!(FIELD(arg0, u16, 0x98) & 8)) {
        register s32 height_work ASM_REG("$2") = -0x20;
        height = FIELD(arg0, s16, 0x92);
        raw_height = FIELD(arg0, u16, 0x92);
        if (height_work < height) {
            height_work = raw_height - 8;
            FIELD(arg0, s16, 0x92) = height_work;
        } else {
low_height_adjustment:
            ASM_KEEP(height);
            height_work = height < -0x28;
            if (height_work) {
                height_work = raw_height + 8;
                FIELD(arg0, s16, 0x92) = height_work;
            }
        }
    }

final_adjustment:
    flags = FIELD(state, u32, 0x1C);
    if (flags & 0x40000000) {
        FIELD(state, u32, 0x1C) = flags & 0xBFFFFFFF;
        ground = func_800BCB04(
            (FIELD(arg2, u8, 0x24) << 6) | 0x20,
            (FIELD(arg2, u8, 0x25) << 6) | 0x20,
            (s16)(FIELD(state, u16, 0x88) - 0x20));
        if (ground < 0x200) {
            FIELD(arg0, s16, 0x92) =
                (FIELD(state, u16, 0x88) - ground) +
                FIELD(arg0, u16, 0x92);
            FIELD(state, u16, 0x88) = ground;
        }
    }

    FIELD(arg1, s16, 0xA) = FIELD(state, u16, 0x88) +
        FIELD(arg0, u16, 0x92) - FIELD(arg0, u16, 0xA2);
    FIELD(arg2, u16, 0x14) |= 0x40;
}
