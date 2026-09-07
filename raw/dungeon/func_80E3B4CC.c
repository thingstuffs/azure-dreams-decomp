#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0;
extern s16 D_80083228;
extern s32 D_80083460;
extern s8 D_800E2968;
extern u8 D_80176668[];

extern s32 func_8003FA44(s32);
extern void func_80042640(void *, s32);
extern void func_80047784(void *, s32, s32);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A152C(s32, s32);
extern s32 func_800A1618(s32, s32);
extern void *func_801708B4(s32, s16, s16, s16);
extern void func_80174FBC(void) __attribute__((noreturn));

void func_80174CCC(void *arg0, void *arg1, void *arg2)
{
    s32 state;
    s32 trig;
    void *created;
    void *source;
    void *owner;
    void *parent;
    register void *tail_arg ASM_REG("$4");
    u8 *global_base;
    s32 kind;
    s32 target_coord;
    s32 target_coord_x;
    s32 current_coord_x;
    s32 delta_x;
    s32 target_coord_y;
    s32 current_coord_y;
    s32 delta_y;
    s32 source_byte;
    u32 created_flags14;
    u32 created_flags1C;
    u32 first_created_flags;
    register u32 used_page ASM_REG("$4");
    register u32 state_page ASM_REG("$2");
    register u16 flags ASM_REG("$3");
    u16 marked;
    u16 timer;

    state = FIELD(arg0, s16, 0x1E);
    if (state != 0) {
        if (state == 1) {
            goto state_one;
        }
        goto cleanup;
    }

    target_coord_x = FIELD(arg0, s16, 0x32) << 6;
    current_coord_x = FIELD(arg1, s16, 2) - 0x20;
    delta_x = target_coord_x - current_coord_x;
    FIELD(arg1, s32, 0) +=
        (delta_x << 16) / FIELD(arg0, s16, 0x20);

    target_coord_y = FIELD(arg0, s16, 0x34) << 6;
    current_coord_y = FIELD(arg1, s16, 6) - 0x20;
    delta_y = target_coord_y - current_coord_y;
    FIELD(arg1, s32, 4) +=
        (delta_y << 16) / FIELD(arg0, s16, 0x20);

    trig = func_800644B8(FIELD(arg0, s16, 0x20) << 6) >> 4;
    FIELD(arg1, s32, 8) +=
        (((FIELD(arg0, s16, 0x36) - trig) -
          FIELD(arg1, s16, 0xA)) << 16) /
        FIELD(arg0, s16, 0x20);

    if (FIELD(arg0, s16, 0x20) == 6) {
        func_80047784(arg2, 0x42, 0);
    }

    timer = FIELD(arg0, u16, 0x20) - 1;
    FIELD(arg0, u16, 0x20) = timer;
    if ((s16)timer > 0) {
        goto cleanup;
    }

    target_coord = FIELD(arg0, s16, 0x32);
    target_coord = (target_coord << 6) + 0x20;
    FIELD(arg1, s16, 2) = target_coord;
    target_coord = FIELD(arg0, s16, 0x34);
    target_coord = (target_coord << 6) + 0x20;
    FIELD(arg1, s16, 6) = target_coord;
    FIELD(arg1, u16, 0xA) = FIELD(arg0, u16, 0x36);
    func_80047784(arg2, 0x43, 0);
    FIELD(arg0, u16, 0x1E)++;
    goto cleanup;

state_one:
    if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
        goto cleanup;
    }
    if (func_800A1618(0x1E, 1) == 0) {
        if (func_800A1618(0x1E, 3) == 0) {
            goto done;
        }
    }
    if (func_8003FA44(3) == 0) {
        goto done;
    }

    global_base = (u8 *)&D_80083460;
    ASM_KEEP(global_base);
    kind = 4;
    FIELD(global_base, u16, 0xA)--;
    used_page = 0x80080000;
    ASM_KEEP(used_page);
    marked = FIELD(arg0, volatile u16, -2);
    flags = FIELD(arg0, volatile u16, 0x38);
    ASM_KEEP_NV(flags);
    marked |= 0x8000;
    FIELD(arg0, u16, -2) = marked;
    ASM_SCHED_BARRIER();
    state_page = 0x800E0000;
    ASM_KEEP(state_page);
    FIELD((void *)state_page, s8, 0x2968) = state;
    FIELD((void *)used_page, s32, 0x14A0) |= 0x8000;
    if (flags & 0x2000) {
        kind = 7;
    }

    created = func_801708B4(kind,
        FIELD(arg0, s16, 0x32),
        FIELD(arg0, s16, 0x34),
        FIELD(arg0, s16, 0x36));
    if (created == 0) {
        goto cleanup;
    }

    func_80042640(created, 0x1E);
    FIELD(created, u32, 0x14) &= ~7;
    created_flags14 = FIELD(created, u32, 0x14);
    first_created_flags = FIELD(arg0, u16, 0x38);
    FIELD(created, u32, 0x1C) &= ~7;
    created_flags1C = FIELD(created, u32, 0x1C);
    created_flags14 |= first_created_flags;
    FIELD(created, u32, 0x14) = created_flags14;
    created_flags1C |= FIELD(arg0, u16, 0x38);
    FIELD(created, u32, 0x1C) = created_flags1C;

    FIELD(created, u8, 5) =
        (FIELD(FIELD(arg0, void *, 0x10), u8, 5) + 1) >> 1;
    FIELD(created, u8, 0x29) =
        (FIELD(FIELD(arg0, void *, 0x10), u8, 0x29) + 1) >> 1;
    source_byte = FIELD(FIELD(arg0, void *, 0x10), u8, 0x28);
    FIELD(created, u8, 0x43) = 0xFD;
    FIELD(created, u8, 0x28) = (source_byte + 1) >> 1;

    source = FIELD(arg0, void *, 0x10);
    if (FIELD(source, u32, 0x14) & 0x4000) {
        tail_arg = created;
        ASM_KEEP(tail_arg);
        FIELD(created, void *, 0xA4) = FIELD(arg0, void *, 0xC);
        func_80174FBC();
    }
    tail_arg = created;
    ASM_KEEP_NV(tail_arg);
    if (FIELD(source, void *, 0xA4) != 0) {
        FIELD(created, void *, 0xA4) = FIELD(source, void *, 0xA4);
    }

    parent = FIELD(tail_arg, void *, 0xA4);
    if (parent != 0) {
        FIELD(parent, u16, 0xCA)++;
    }

    owner = FIELD(created, void *, -0x14);
    FIELD(owner, void *, 0x2C) = D_80176668;
    FIELD(owner, u16, 0x14) |= 0x4000;
    FIELD(owner, u16, 0x12) = FIELD(arg0, u16, 0x3A);
    func_80047784(owner,
        FIELD(owner, u8 *, 0x2C)
            [((D_80083228 + FIELD(created, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_800A152C(0x1E, 1);

cleanup:
    func_800478B8(arg2);
done:
    return;
}
