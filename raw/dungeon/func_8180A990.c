#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void *(*SpawnFunc)(s32, s32, s32, s16);

extern void *func_80025170(void *);
extern void *func_8003FC64(s32);
extern void func_8003F320(void);
extern void func_80042640(void *, s16);
extern void func_80042710(void *, void *);
extern s32 func_800429E4(void *);
extern void func_8004397C(void *);
extern void func_80044A50(void *);
extern void func_8004E130(s32);
extern void *func_800A0B94(s32, s32, s32);
extern s32 func_800A1618(s32, s32);
extern void func_8009A028(void *, s32);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800BC318(void *);

extern s32 D_80012090[];
extern s32 D_8002520C[];
extern s32 D_80025A14[];
extern s32 D_80025C94[];
extern s32 D_8002663C[];
extern s16 D_8002715A;
extern s16 D_8002715C;
extern s32 D_800814A0;
extern s8 D_80083160[];
extern u8 *D_800E3D7C;

void func_80026190(void *arg0)
{
    s32 state;
    register s32 state_two ASM_REG("$4");
    s32 i;
    s32 role_s1;
    s32 signed_kind;
    register s32 shifted_kind ASM_REG("$2");
    s32 copied;
    register s32 loaded_fail_flags ASM_REG("$2");
    register s32 fail_flags ASM_REG("$3");
    s32 entity_flags;
    register s32 source_check_flags ASM_REG("$3");
    register s32 source_check_mask ASM_REG("$2");
    s32 loop_count;
    register s32 clear_mask ASM_REG("$5");
    u16 spawn_bits;
    u16 owner_bits;
    u16 child_bits;
    u16 alloc_bits;
    s32 cleanup_flags;
    s32 alloc_flags;
    register s32 amount100 ASM_REG("$2");
    register void *call_work ASM_REG("$4");
    register void *owner ASM_REG("$22");
    register u8 *status_page ASM_REG("$2");
    register u8 *mode_page ASM_REG("$3");
    s32 mode;
    u8 *flag_page;
    u8 *cleanup_page;
    u8 *status;
    volatile u8 *clear;
    void *container;
    void *source;
    void *parent;
    void *early0;
    void *early1;
    void *alloc2;
    void *alloc_fail;
    void *owner_fail;
    void *child_fail;
    void *spawn_fail0;
    void *spawn_fail1;
    void *spawn_fail2;
    register void *spawn_fail3 ASM_REG("$4");
    void *work;

    owner = arg0;
    status_page = (u8 *)0x80080000;
    ASM_KEEP(owner);
    ASM_KEEP_NV(status_page);
    state = FIELD(owner, s16, 0x1C);
    ASM_KEEP(state);
    state_two = 2;
    ASM_KEEP_NV(state_two);
    if (state == state_two) {
        if (D_8002715C == 0) {
            FIELD(owner, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        D_8002715C = 0;
        goto done;
    }

    status = status_page + 0x3160;
    ASM_KEEP_NV(status);
    if (FIELD(status, s32, 8) & 0x20) {
        early0 = FIELD(owner, void *, 0);
        if (early0 != NULL) {
            FIELD(early0, s16, 0x1C) = 3;
        }
        early1 = FIELD(owner, void *, 4);
        if (early1 != NULL) {
            FIELD(early1, s16, 0xE) = 3;
        }
        D_8002715A = 1;
        FIELD(owner, s16, 0x1C) = state_two;
        D_8002715C = 0;
        func_8004E130(state_two);
        goto done;
    }

    if (state != 0) {
        goto done;
    }

    role_s1 = (s32)func_8003FC64(0x12);
    if (role_s1 == 0) {
        goto done;
    }
    FIELD((void *)role_s1, void *, 0x10) = D_8002520C;
    container = (u8 *)role_s1 + 0x20;
    FIELD(owner, void *, 0) = container;
    FIELD(container, u16, 0x26) = FIELD(owner, u16, 0x26);

    alloc2 = func_8003FC64(0x112);
    FIELD(container, void *, 8) = alloc2;
    if (alloc2 == NULL) {
        alloc_fail = FIELD(owner, void *, 0);
        alloc_bits = FIELD(alloc_fail, u16, -2);
        FIELD(alloc_fail, u16, -2) = alloc_bits | 0x8000;
        alloc_flags = D_800814A0;
        FIELD(owner, void *, 0) = NULL;
        alloc_flags |= 0x8000;
        D_800814A0 = alloc_flags;
        goto done;
    }

    role_s1 = (s32)alloc2;
    FIELD((void *)role_s1, void *, 0x10) = D_80025A14;
    FIELD((void *)role_s1, void *, 0x78) = FIELD(owner, void *, 0);
    if ((FIELD(container, void *, 0x14) = func_80025170(container)) == NULL) {
        owner_fail = FIELD(owner, void *, 0);
        owner_bits = FIELD(owner_fail, u16, -2);
        cleanup_page = (u8 *)0x80080000;
        FIELD(owner_fail, u16, -2) = owner_bits | 0x8000;
        FIELD(owner, void *, 0) = NULL;
        child_fail = FIELD(container, void *, 8);
        cleanup_flags = FIELD(cleanup_page, s32, 0x14A0);
        child_bits = FIELD(child_fail, u16, 0x1E);
        cleanup_flags |= 0x8000;
        FIELD(cleanup_page, s32, 0x14A0) = cleanup_flags;
        FIELD(child_fail, u16, 0x1E) = child_bits | 0x8000;
        FIELD(container, void *, 8) = NULL;
        goto done;
    }

    i = 0;
    flag_page = (u8 *)0x80080000;
loop:
    source = *(void **)(D_800E3D7C + (i * 4) + 0xAC);
    if (source == NULL) {
        goto next;
    }

    role_s1 = 0x1E;
    if (!(FIELD(source, s32, 0x14) & 0x20000000)) {
        role_s1 = FIELD(source, u8, 0x13);
    }
    if (FIELD(source, u8, 0x13) == 0x2E) {
        role_s1 = FIELD(source, u16, 0xA8);
    }
    func_8004397C(source);

    mode_page = (u8 *)0x80010000;
    ASM_KEEP_NV(mode_page);
    mode = FIELD(mode_page, s32, 0x2090);
    if (mode == 1) {
        if ((s16)role_s1 == 2) {
            role_s1 = 0x39;
        }
    }
    shifted_kind = role_s1 << 16;
    signed_kind = shifted_kind >> 16;
    ASM_KEEP(shifted_kind);

    work = func_800A0B94(signed_kind, func_800A1618(signed_kind, 3), 1);
    func_8003F320();
    work = ((SpawnFunc)work)(1, 0, 0, FIELD(source, s16, 0x88));

    mode_page = (u8 *)0x80010000;
    ASM_KEEP_NV(mode_page);
    mode = FIELD(mode_page, s32, 0x2090);
    if ((mode == 1) && (signed_kind == 0x39)) {
        role_s1 = 2;
    }

    if (work == NULL) {
        spawn_fail0 = FIELD(owner, void *, 0);
        FIELD(spawn_fail0, u16, -2) |= 0x8000;
        FIELD(owner, void *, 0) = NULL;

        spawn_fail1 = FIELD(container, void *, 8);
        FIELD(spawn_fail1, u16, 0x1E) |= 0x8000;
        FIELD(container, void *, 8) = NULL;

        spawn_fail2 = FIELD(container, void *, 0x14);
        FIELD(spawn_fail2, u16, 0x1E) |= 0x8000;

        loaded_fail_flags = FIELD(flag_page, volatile s32, 0x14A0);
        ASM_KEEP_NV(loaded_fail_flags);
        spawn_fail3 = FIELD(container, void *, 0xC);
        ASM_KEEP(spawn_fail3);
        FIELD(container, void *, 0x14) = NULL;
        ASM_KEEP(spawn_fail3);
        fail_flags = loaded_fail_flags | 0x8000;
        ASM_KEEP_NV(fail_flags);
        FIELD(flag_page, s32, 0x14A0) = fail_flags;
        if (spawn_fail3 != NULL) {
            spawn_bits = FIELD(spawn_fail3, u16, 0x1E);
            FIELD(flag_page, volatile s32, 0x14A0) = fail_flags;
            FIELD(spawn_fail3, u16, 0x1E) = spawn_bits | 0x8000;
            FIELD(container, void *, 0xC) = NULL;
        }
        goto done;
    }

    func_80042640(work, (s16)role_s1);
    FIELD(work, s32, 0x14) = 0;
    FIELD(work, s32, 0x1C) = 0;
    func_80042710(work, source);

    loop_count = 3;
    clear = (u8 *)work + 6;
    FIELD(work, u8, 0x13) = role_s1;
    do {
        clear[0x2C] = 0;
        clear[0x2D] = 0;
        ASM_KEEP(clear);
        loop_count--;
        clear -= 2;
    } while (loop_count >= 0);

    clear_mask = 0xBFFFFFFF;
    ASM_KEEP(clear_mask);
    call_work = work;
    ASM_KEEP_NV(call_work);
    amount100 = 0x64;
    ASM_KEEP_NV(amount100);
    FIELD(work, s8, 0x25) = amount100;
    ASM_KEEP(amount100);
    FIELD(work, s16, 0x88) = 0;
    entity_flags = FIELD(work, s32, 0x1C);
    entity_flags &= ~0x1EF8;
    entity_flags &= clear_mask;
    entity_flags |= 0x40000;
    FIELD(work, s32, 0x1C) = entity_flags;
    func_8009A028(call_work, clear_mask);

    source_check_mask = 0x20000000;
    ASM_KEEP_NV(source_check_mask);
    source_check_flags = FIELD(source, s32, 0x14);
    parent = FIELD(work, void *, -0x14);
    source_check_flags &= source_check_mask;
    ASM_KEEP_NV(source_check_flags);
    if (source_check_flags) {
        copied = func_800429E4(source) << 2;
    } else {
        copied = FIELD(FIELD(source, void *, -0x14), u16, 0x12);
    }
    FIELD(parent, u16, 0x12) = copied;
    ASM_KEEP(work);

    role_s1 = (s32)work - 0x20;
    *(s32 *)((u8 *)container + (i * 4) + 0xC) = role_s1;
    FIELD(work, s32, 0x5C) = FIELD((void *)role_s1, s32, 0x10) | 0x80000000;
    FIELD(work, void *, 0x58) = FIELD(owner, void *, 0);
    FIELD(work, s16, 0x6A) = i;
    func_80044A50((void *)role_s1);
    func_800BC318((void *)role_s1);
    func_8009A3D0(FIELD(parent, u8, 0x24), FIELD(parent, u8, 0x25), 0x300);
    FIELD(work, u8, 0x87) = 0xFF;
    FIELD((void *)role_s1, void *, 0x10) = D_80025C94;

next:
    i++;
    if (i < 2) {
        goto loop;
    }

    role_s1 = (s32)func_8003FC64(0x212);
    if (role_s1 != 0) {
        FIELD((void *)role_s1, void *, 0x10) = D_8002663C;
        FIELD(owner, void *, 4) = (u8 *)role_s1 + 0x20;
    }
    FIELD(owner, u16, 0x1C)++;

done:
    return;
}
