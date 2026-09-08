#include "common.h"

#ifndef NULL
#define NULL 0
#endif


typedef void *(*SpawnFunc)(s32, s32, s32, s16);

typedef struct S_80026190_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x14];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x8];
    u16 unk_26;
} S_80026190_0;   /* owner in func_80026190 */

typedef struct S_80026190_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80026190_1;   /* status in func_80026190 */

typedef struct S_80026190_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
} S_80026190_2;   /* early0 in func_80026190 */

typedef struct S_80026190_3 {
    u8 pad_00[0xE];
    s16 unk_0E;
} S_80026190_3;   /* early1 in func_80026190 */

typedef struct S_80026190_4 {
    u8 pad_00[0x10];
    union { void * s; s32 u; } unk_10;   /* accessed as both */
    u8 pad_14[0x64];
    void * unk_78;
} S_80026190_4;   /* (void *)role_s1 in func_80026190 */

typedef struct S_80026190_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    void * unk_14;
    u8 pad_18[0xE];
    u16 unk_26;
} S_80026190_5;   /* container in func_80026190 */

typedef struct S_80026190_6_pre {
    u16 unk_00;
} S_80026190_6_pre;   /* the 0x2 bytes before alloc_fail in func_80026190, addressed as alloc_fail[-1] */

typedef struct S_80026190_7_pre {
    u16 unk_00;
} S_80026190_7_pre;   /* the 0x2 bytes before owner_fail in func_80026190, addressed as owner_fail[-1] */

typedef struct S_80026190_8 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80026190_8;   /* cleanup_page in func_80026190 */

typedef struct S_80026190_9 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80026190_9;   /* child_fail in func_80026190 */

typedef struct S_80026190_10_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80026190_10_pre;   /* the 0x14 bytes before source in func_80026190, addressed as source[-1] */

typedef struct S_80026190_10 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x70];
    s16 unk_88;
    u8 pad_8A[0x1E];
    u16 unk_A8;
} S_80026190_10;   /* source in func_80026190 */

typedef struct S_80026190_11 {
    u8 pad_00[0x2090];
    s32 unk_2090;
} S_80026190_11;   /* mode_page in func_80026190 */

typedef struct S_80026190_12_pre {
    u16 unk_00;
} S_80026190_12_pre;   /* the 0x2 bytes before spawn_fail0 in func_80026190, addressed as spawn_fail0[-1] */

typedef struct S_80026190_13 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80026190_13;   /* spawn_fail1 in func_80026190 */

typedef struct S_80026190_14 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80026190_14;   /* spawn_fail2 in func_80026190 */

typedef struct S_80026190_15 {
    u8 pad_00[0x14A0];
    union { volatile s32 s; s32 u; } unk_14A0;   /* accessed as both */
} S_80026190_15;   /* flag_page in func_80026190 */

typedef struct S_80026190_16 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80026190_16;   /* spawn_fail3 in func_80026190 */

typedef struct S_80026190_17_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80026190_17_pre;   /* the 0x14 bytes before work in func_80026190, addressed as work[-1] */

typedef struct S_80026190_17 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x5];
    s8 unk_25;
    u8 pad_26[0x32];
    void * unk_58;
    s32 unk_5C;
    u8 pad_60[0xA];
    s16 unk_6A;
    u8 pad_6C[0x1B];
    u8 unk_87;
    s16 unk_88;
} S_80026190_17;   /* work in func_80026190 */

typedef struct S_80026190_18 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
} S_80026190_18;   /* parent in func_80026190 */

typedef struct S_80026190_19 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80026190_19;   /* ((S_80026190_10_pre *)source)[-1].unk_00 in func_80026190 */


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
    s32 state_two;
    s32 i;
    s32 role_s1;
    s32 signed_kind;
    s32 shifted_kind;
    s32 copied;
    register s32 loaded_fail_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 fail_flags;
    s32 entity_flags;
    s32 source_check_flags;
    s32 source_check_mask;
    s32 loop_count;
    s32 clear_mask;
    u16 spawn_bits;
    u16 owner_bits;
    u16 child_bits;
    u16 alloc_bits;
    s32 cleanup_flags;
    s32 alloc_flags;
    s32 amount100;
    register void *call_work ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *owner ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *status_page;
    u8 *mode_page;
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
    register void *spawn_fail3 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *work;

    owner = arg0;
    status_page = (u8 *)0x80080000;
    ASM_KEEP(owner);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(status_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    state = ((S_80026190_0 *)owner)->unk_1C.s;
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    state_two = 2;
    ASM_KEEP_NV(state_two);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state == state_two) {
        if (D_8002715C == 0) {
            (*(u16 *)((u8 *)owner + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        D_8002715C = 0;
        goto done;
    }

    status = status_page + 0x3160;
    ASM_KEEP_NV(status);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (((S_80026190_1 *)status)->unk_08 & 0x20) {
        early0 = ((S_80026190_0 *)owner)->unk_00;
        if (early0 != NULL) {
            ((S_80026190_2 *)early0)->unk_1C = 3;
        }
        early1 = ((S_80026190_0 *)owner)->unk_04;
        if (early1 != NULL) {
            ((S_80026190_3 *)early1)->unk_0E = 3;
        }
        D_8002715A = 1;
        ((S_80026190_0 *)owner)->unk_1C.s = state_two;
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
    ((S_80026190_4 *)((void *)role_s1))->unk_10.s = D_8002520C;
    container = (u8 *)role_s1 + 0x20;
    ((S_80026190_0 *)owner)->unk_00 = container;
    ((S_80026190_5 *)container)->unk_26 = ((S_80026190_0 *)owner)->unk_26;

    alloc2 = func_8003FC64(0x112);
    ((S_80026190_5 *)container)->unk_08 = alloc2;
    if (alloc2 == NULL) {
        alloc_fail = ((S_80026190_0 *)owner)->unk_00;
        alloc_bits = ((S_80026190_6_pre *)alloc_fail)[-1].unk_00;
        (*(u16 *)((u8 *)alloc_fail + -2)) = alloc_bits | 0x8000;
        alloc_flags = D_800814A0;
        ((S_80026190_0 *)owner)->unk_00 = NULL;
        alloc_flags |= 0x8000;
        D_800814A0 = alloc_flags;
        goto done;
    }

    role_s1 = (s32)alloc2;
    ((S_80026190_4 *)((void *)role_s1))->unk_10.s = D_80025A14;
    ((S_80026190_4 *)((void *)role_s1))->unk_78 = ((S_80026190_0 *)owner)->unk_00;
    if ((((S_80026190_5 *)container)->unk_14 = func_80025170(container)) == NULL) {
        owner_fail = ((S_80026190_0 *)owner)->unk_00;
        owner_bits = ((S_80026190_7_pre *)owner_fail)[-1].unk_00;
        cleanup_page = (u8 *)0x80080000;
        ((S_80026190_7_pre *)owner_fail)[-1].unk_00 = owner_bits | 0x8000;
        ((S_80026190_0 *)owner)->unk_00 = NULL;
        child_fail = ((S_80026190_5 *)container)->unk_08;
        cleanup_flags = ((S_80026190_8 *)cleanup_page)->unk_14A0;
        child_bits = ((S_80026190_9 *)child_fail)->unk_1E;
        cleanup_flags |= 0x8000;
        ((S_80026190_8 *)cleanup_page)->unk_14A0 = cleanup_flags;
        ((S_80026190_9 *)child_fail)->unk_1E = child_bits | 0x8000;
        ((S_80026190_5 *)container)->unk_08 = NULL;
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
    if (!(((S_80026190_10 *)source)->unk_14 & 0x20000000)) {
        role_s1 = ((S_80026190_10 *)source)->unk_13;
    }
    if (((S_80026190_10 *)source)->unk_13 == 0x2E) {
        role_s1 = ((S_80026190_10 *)source)->unk_A8;
    }
    func_8004397C(source);

    mode_page = (u8 *)0x80010000;
    mode = ((S_80026190_11 *)mode_page)->unk_2090;
    if (mode == 1) {
        if ((s16)role_s1 == 2) {
            role_s1 = 0x39;
        }
    }
    shifted_kind = role_s1 << 16;
    signed_kind = shifted_kind >> 16;

    work = func_800A0B94(signed_kind, func_800A1618(signed_kind, 3), 1);
    func_8003F320();
    work = ((SpawnFunc)work)(1, 0, 0, ((S_80026190_10 *)source)->unk_88);

    mode_page = (u8 *)0x80010000;
    mode = ((S_80026190_11 *)mode_page)->unk_2090;
    if ((mode == 1) && (signed_kind == 0x39)) {
        role_s1 = 2;
    }

    if (work == NULL) {
        spawn_fail0 = ((S_80026190_0 *)owner)->unk_00;
        ((S_80026190_12_pre *)spawn_fail0)[-1].unk_00 |= 0x8000;
        ((S_80026190_0 *)owner)->unk_00 = NULL;

        spawn_fail1 = ((S_80026190_5 *)container)->unk_08;
        ((S_80026190_13 *)spawn_fail1)->unk_1E |= 0x8000;
        ((S_80026190_5 *)container)->unk_08 = NULL;

        spawn_fail2 = ((S_80026190_5 *)container)->unk_14;
        ((S_80026190_14 *)spawn_fail2)->unk_1E |= 0x8000;

        loaded_fail_flags = ((S_80026190_15 *)flag_page)->unk_14A0.s;
        spawn_fail3 = ((S_80026190_5 *)container)->unk_0C;
        ((S_80026190_5 *)container)->unk_14 = NULL;
        fail_flags = loaded_fail_flags | 0x8000;
        ((S_80026190_15 *)flag_page)->unk_14A0.u = fail_flags;
        if (spawn_fail3 != NULL) {
            spawn_bits = ((S_80026190_16 *)spawn_fail3)->unk_1E;
            ((S_80026190_15 *)flag_page)->unk_14A0.s = fail_flags;
            ((S_80026190_16 *)spawn_fail3)->unk_1E = spawn_bits | 0x8000;
            ((S_80026190_5 *)container)->unk_0C = NULL;
        }
        goto done;
    }

    func_80042640(work, (s16)role_s1);
    ((S_80026190_17 *)work)->unk_14 = 0;
    ((S_80026190_17 *)work)->unk_1C = 0;
    func_80042710(work, source);

    loop_count = 3;
    clear = (u8 *)work + 6;
    ((S_80026190_17 *)work)->unk_13 = role_s1;
    do {
        clear[0x2C] = 0;
        clear[0x2D] = 0;
        ASM_KEEP(clear);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        loop_count--;
        clear -= 2;
    } while (loop_count >= 0);

    clear_mask = 0xBFFFFFFF;
    ASM_KEEP(clear_mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    call_work = work;
    amount100 = 0x64;
    ((S_80026190_17 *)work)->unk_25 = amount100;
    ASM_KEEP(amount100);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ((S_80026190_17 *)work)->unk_88 = 0;
    entity_flags = ((S_80026190_17 *)work)->unk_1C;
    entity_flags &= ~0x1EF8;
    entity_flags &= clear_mask;
    entity_flags |= 0x40000;
    ((S_80026190_17 *)work)->unk_1C = entity_flags;
    func_8009A028(call_work, clear_mask);

    source_check_mask = 0x20000000;
    ASM_KEEP_NV(source_check_mask);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    source_check_flags = ((S_80026190_10 *)source)->unk_14;
    parent = ((S_80026190_17_pre *)work)[-1].unk_00;
    source_check_flags &= source_check_mask;
    if (source_check_flags) {
        copied = func_800429E4(source) << 2;
    } else {
        copied = ((S_80026190_19 *)(((S_80026190_10_pre *)source)[-1].unk_00))->unk_12;
    }
    ((S_80026190_18 *)parent)->unk_12 = copied;
    ASM_KEEP(work);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    role_s1 = (s32)work - 0x20;
    *(s32 *)((u8 *)container + (i * 4) + 0xC) = role_s1;
    ((S_80026190_17 *)work)->unk_5C = ((S_80026190_4 *)((void *)role_s1))->unk_10.u | 0x80000000;
    ((S_80026190_17 *)work)->unk_58 = ((S_80026190_0 *)owner)->unk_00;
    ((S_80026190_17 *)work)->unk_6A = i;
    func_80044A50((void *)role_s1);
    func_800BC318((void *)role_s1);
    func_8009A3D0(((S_80026190_18 *)parent)->unk_24, ((S_80026190_18 *)parent)->unk_25, 0x300);
    ((S_80026190_17 *)work)->unk_87 = 0xFF;
    ((S_80026190_4 *)((void *)role_s1))->unk_10.s = D_80025C94;

next:
    i++;
    if (i < 2) {
        goto loop;
    }

    role_s1 = (s32)func_8003FC64(0x212);
    if (role_s1 != 0) {
        ((S_80026190_4 *)((void *)role_s1))->unk_10.s = D_8002663C;
        ((S_80026190_0 *)owner)->unk_04 = (u8 *)role_s1 + 0x20;
    }
    ((S_80026190_0 *)owner)->unk_1C.u++;

done:
    return;
}
