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

/* Initializes child objects and copies source entities, or requests their shutdown. */
void func_80026190(void *owner_arg)
{
    s32 state;
    s32 stop_state;
    s32 source_slot;
    s32 object_or_kind;
    s32 signed_kind;
    s32 shifted_kind;
    s32 parent_value;
    register s32 loaded_fail_flags ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 fail_flags;
    s32 entity_flags;
    s32 source_check_flags;
    s32 source_check_mask;
    s32 clear_pairs_left;
    s32 clear_mask;
    u16 spawn_bits;
    u16 owner_bits;
    u16 child_bits;
    u16 alloc_bits;
    s32 cleanup_flags;
    s32 alloc_flags;
    s32 default_amount;
    register void *entity_arg ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *owner ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u8 *status_page;
    u8 *mode_page;
    s32 mode;
    u8 *flag_page;
    u8 *cleanup_page;
    u8 *status;
    volatile u8 *clear_cursor;
    void *container;
    void *source;
    void *parent;
    void *main_child;
    void *aux_child;
    void *child_object;
    void *alloc_container;
    void *setup_container;
    void *setup_child;
    void *spawn_container;
    void *spawn_child;
    void *spawn_resource;
    register void *prior_entity ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *entity;

    owner = owner_arg;
    status_page = (u8 *)0x80080000;
    ASM_KEEP(owner);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP_NV(status_page);   /* MATCH pin: retail immediate-load split depends on it */
    state = ((S_80026190_0 *)owner)->unk_1C.s;
    ASM_KEEP(state);   /* MATCH pin: retail schedule: same instructions, different order without it */
    stop_state = 2;
    ASM_KEEP_NV(stop_state);   /* MATCH pin: retail delay-slot fill depends on it */
    if (state == stop_state) {
        if (D_8002715C == 0) {
            (*(u16 *)((u8 *)owner + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        D_8002715C = 0;
        goto done;
    }

    status = status_page + 0x3160;
    ASM_KEEP_NV(status);   /* MATCH pin: load-bearing for the whole function shape */
    if (((S_80026190_1 *)status)->unk_08 & 0x20) {
        main_child = ((S_80026190_0 *)owner)->unk_00;
        if (main_child != NULL) {
            ((S_80026190_2 *)main_child)->unk_1C = 3;
        }
        aux_child = ((S_80026190_0 *)owner)->unk_04;
        if (aux_child != NULL) {
            ((S_80026190_3 *)aux_child)->unk_0E = 3;
        }
        D_8002715A = 1;
        ((S_80026190_0 *)owner)->unk_1C.s = stop_state;
        D_8002715C = 0;
        func_8004E130(stop_state);
        goto done;
    }

    if (state != 0) {
        goto done;
    }

    object_or_kind = (s32)func_8003FC64(0x12);
    if (object_or_kind == 0) {
        goto done;
    }
    ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = D_8002520C;
    container = (u8 *)object_or_kind + 0x20;
    ((S_80026190_0 *)owner)->unk_00 = container;
    ((S_80026190_5 *)container)->unk_26 = ((S_80026190_0 *)owner)->unk_26;

    child_object = func_8003FC64(0x112);
    ((S_80026190_5 *)container)->unk_08 = child_object;
    if (child_object == NULL) {
        alloc_container = ((S_80026190_0 *)owner)->unk_00;
        alloc_bits = ((S_80026190_6_pre *)alloc_container)[-1].unk_00;
        (*(u16 *)((u8 *)alloc_container + -2)) = alloc_bits | 0x8000;
        alloc_flags = D_800814A0;
        ((S_80026190_0 *)owner)->unk_00 = NULL;
        alloc_flags |= 0x8000;
        D_800814A0 = alloc_flags;
        goto done;
    }

    object_or_kind = (s32)child_object;
    ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = D_80025A14;
    ((S_80026190_4 *)((void *)object_or_kind))->unk_78 = ((S_80026190_0 *)owner)->unk_00;
    if ((((S_80026190_5 *)container)->unk_14 = func_80025170(container)) == NULL) {
        setup_container = ((S_80026190_0 *)owner)->unk_00;
        owner_bits = ((S_80026190_7_pre *)setup_container)[-1].unk_00;
        cleanup_page = (u8 *)0x80080000;
        ((S_80026190_7_pre *)setup_container)[-1].unk_00 = owner_bits | 0x8000;
        ((S_80026190_0 *)owner)->unk_00 = NULL;
        setup_child = ((S_80026190_5 *)container)->unk_08;
        cleanup_flags = ((S_80026190_8 *)cleanup_page)->unk_14A0;
        child_bits = ((S_80026190_9 *)setup_child)->unk_1E;
        cleanup_flags |= 0x8000;
        ((S_80026190_8 *)cleanup_page)->unk_14A0 = cleanup_flags;
        ((S_80026190_9 *)setup_child)->unk_1E = child_bits | 0x8000;
        ((S_80026190_5 *)container)->unk_08 = NULL;
        goto done;
    }

    source_slot = 0;
    flag_page = (u8 *)0x80080000;
loop:
    source = *(void **)(D_800E3D7C + (source_slot * 4) + 0xAC);
    if (source == NULL) {
        goto next;
    }

    object_or_kind = 0x1E;
    if (!(((S_80026190_10 *)source)->unk_14 & 0x20000000)) {
        object_or_kind = ((S_80026190_10 *)source)->unk_13;
    }
    if (((S_80026190_10 *)source)->unk_13 == 0x2E) {
        object_or_kind = ((S_80026190_10 *)source)->unk_A8;
    }
    func_8004397C(source);

    mode_page = (u8 *)0x80010000;
    mode = ((S_80026190_11 *)mode_page)->unk_2090;
    if (mode == 1) {
        if ((s16)object_or_kind == 2) {
            object_or_kind = 0x39;
        }
    }
    shifted_kind = object_or_kind << 16;
    signed_kind = shifted_kind >> 16;

    entity = func_800A0B94(signed_kind, func_800A1618(signed_kind, 3), 1);
    func_8003F320();
    entity = ((SpawnFunc)entity)(1, 0, 0, ((S_80026190_10 *)source)->unk_88);

    mode_page = (u8 *)0x80010000;
    mode = ((S_80026190_11 *)mode_page)->unk_2090;
    if ((mode == 1) && (signed_kind == 0x39)) {
        object_or_kind = 2;
    }

    if (entity == NULL) {
        spawn_container = ((S_80026190_0 *)owner)->unk_00;
        ((S_80026190_12_pre *)spawn_container)[-1].unk_00 |= 0x8000;
        ((S_80026190_0 *)owner)->unk_00 = NULL;

        spawn_child = ((S_80026190_5 *)container)->unk_08;
        ((S_80026190_13 *)spawn_child)->unk_1E |= 0x8000;
        ((S_80026190_5 *)container)->unk_08 = NULL;

        spawn_resource = ((S_80026190_5 *)container)->unk_14;
        ((S_80026190_14 *)spawn_resource)->unk_1E |= 0x8000;

        loaded_fail_flags = ((S_80026190_15 *)flag_page)->unk_14A0.s;
        prior_entity = ((S_80026190_5 *)container)->unk_0C;
        ((S_80026190_5 *)container)->unk_14 = NULL;
        fail_flags = loaded_fail_flags | 0x8000;
        ((S_80026190_15 *)flag_page)->unk_14A0.u = fail_flags;
        if (prior_entity != NULL) {
            spawn_bits = ((S_80026190_16 *)prior_entity)->unk_1E;
            ((S_80026190_15 *)flag_page)->unk_14A0.s = fail_flags;
            ((S_80026190_16 *)prior_entity)->unk_1E = spawn_bits | 0x8000;
            ((S_80026190_5 *)container)->unk_0C = NULL;
        }
        goto done;
    }

    func_80042640(entity, (s16)object_or_kind);
    ((S_80026190_17 *)entity)->unk_14 = 0;
    ((S_80026190_17 *)entity)->unk_1C = 0;
    func_80042710(entity, source);

    clear_pairs_left = 3;
    clear_cursor = (u8 *)entity + 6;
    ((S_80026190_17 *)entity)->unk_13 = object_or_kind;
    do {
        clear_cursor[0x2C] = 0;
        clear_cursor[0x2D] = 0;
        ASM_KEEP(clear_cursor);   /* MATCH pin: retail schedule: same instructions, different order without it */
        clear_pairs_left--;
        clear_cursor -= 2;
    } while (clear_pairs_left >= 0);

    clear_mask = 0xBFFFFFFF;
    ASM_KEEP(clear_mask);   /* MATCH pin: retail schedule: same instructions, different order without it */
    entity_arg = entity;
    default_amount = 0x64;
    ((S_80026190_17 *)entity)->unk_25 = default_amount;
    ASM_KEEP(default_amount);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ((S_80026190_17 *)entity)->unk_88 = 0;
    entity_flags = ((S_80026190_17 *)entity)->unk_1C;
    entity_flags &= ~0x1EF8;
    entity_flags &= clear_mask;
    entity_flags |= 0x40000;
    ((S_80026190_17 *)entity)->unk_1C = entity_flags;
    func_8009A028(entity_arg, clear_mask);

    source_check_mask = 0x20000000;
    ASM_KEEP_NV(source_check_mask);   /* MATCH pin: retail register colouring depends on it */
    source_check_flags = ((S_80026190_10 *)source)->unk_14;
    parent = ((S_80026190_17_pre *)entity)[-1].unk_00;
    source_check_flags &= source_check_mask;
    if (source_check_flags) {
        parent_value = func_800429E4(source) << 2;
    } else {
        parent_value = ((S_80026190_19 *)(((S_80026190_10_pre *)source)[-1].unk_00))->unk_12;
    }
    ((S_80026190_18 *)parent)->unk_12 = parent_value;
    ASM_KEEP(entity);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    object_or_kind = (s32)entity - 0x20;
    *(s32 *)((u8 *)container + (source_slot * 4) + 0xC) = object_or_kind;
    ((S_80026190_17 *)entity)->unk_5C = ((S_80026190_4 *)((void *)object_or_kind))->unk_10.u | 0x80000000;
    ((S_80026190_17 *)entity)->unk_58 = ((S_80026190_0 *)owner)->unk_00;
    ((S_80026190_17 *)entity)->unk_6A = source_slot;
    func_80044A50((void *)object_or_kind);
    func_800BC318((void *)object_or_kind);
    func_8009A3D0(((S_80026190_18 *)parent)->unk_24, ((S_80026190_18 *)parent)->unk_25, 0x300);
    ((S_80026190_17 *)entity)->unk_87 = 0xFF;
    ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = D_80025C94;

next:
    source_slot++;
    if (source_slot < 2) {
        goto loop;
    }

    object_or_kind = (s32)func_8003FC64(0x212);
    if (object_or_kind != 0) {
        ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = D_8002663C;
        ((S_80026190_0 *)owner)->unk_04 = (u8 *)object_or_kind + 0x20;
    }
    ((S_80026190_0 *)owner)->unk_1C.u++;

done:
    return;
}
