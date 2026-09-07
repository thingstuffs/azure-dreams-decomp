#include "common.h"

typedef struct S_80171D64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80171D64_0;   /* created in func_80171D64 */

typedef struct S_80171D64_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    s8 unk_49;
    u8 pad_4A[0x1];
    s8 unk_4B;
} S_80171D64_1;   /* result in func_80171D64 */

typedef struct S_80171D64_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80171D64_2;   /* position in func_80171D64 */

typedef struct S_80171D64_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80171D64_3;   /* (void *)reused_arg3 in func_80171D64 */

typedef struct S_80171D64_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80171D64_4;   /* (void *)reused_arg2 in func_80171D64 */



extern void *func_8003FD64();
extern void func_8004491C();
extern void func_80047784();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();

extern s32 D_80045340;
extern s16 D_80083228;
extern u8 D_80083498[];
extern s8 D_800E2968;
extern u8 D_801720B4[];
extern u8 D_801724BC[];
extern u8 D_80175E24[];
extern u8 D_80175E2C[];
extern u8 D_80175E34[];
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];

void *func_80171D64(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 saved_arg0;
    void *result;
    s32 saved_arg1;
    s32 reused_arg3;
    register s32 reused_arg2 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 original_arg0 ASM_REG("$23");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *created;
    register void *position ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 selector ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 kind_e;
    s32 kind_f;
    s32 field_4b;
    void *new_callback;
    s32 kind;
    u32 global_kind;
    u32 branch_flags;
    void *current_callback;
    void *initial_callback;
    u8 *table;
    s32 table_index;

    saved_arg0 = arg0;
    result = 0;
    selector = 0x112;
    saved_arg1 = arg1;
    ASM_KEEP_DEP_NV(saved_arg1, selector);   /* MATCH pin: keeps a statement from moving across a call/branch */
    kind_e = (s32)D_80083498;
    ASM_KEEP_DEP_NV(kind_e, saved_arg1);   /* MATCH pin: retail immediate-load split depends on it */
    reused_arg3 = arg3;
    ASM_KEEP_DEP_NV(reused_arg3, kind_e);   /* MATCH pin: retail schedule: same instructions, different order without it */
    reused_arg2 = arg2;
    created = func_8003FD64(selector, (void *)kind_e);
    original_arg0 = saved_arg0;
    if (created == 0) {
        goto done;
    }

    result = (u8 *)created + 0x20;
    ((S_80171D64_0 *)created)->unk_10 = D_801720B4;
    ((S_80171D64_1 *)result)->unk_13 = 0x16;
    func_8004491C(created, &D_80045340);

    initial_callback = D_80175E24;
    kind_e = 0xE;
    position = ((S_80171D64_0 *)created)->unk_08;
    kind_f = 0xF;
    ((S_80171D64_2 *)position)->unk_0A = reused_arg3;
    reused_arg3 = (s32)((S_80171D64_0 *)created)->unk_0C;
    ASM_KEEP(reused_arg3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    selector = saved_arg0 & 3;
    ((S_80171D64_3 *)((void *)reused_arg3))->unk_2C = initial_callback;
    ASM_KEEP(initial_callback);   /* MATCH pin: retail schedule: same instructions, different order without it */
    field_4b = 0x20;
    ASM_KEEP(field_4b);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_80171D64_3 *)((void *)reused_arg3))->unk_25 = reused_arg2;
    reused_arg2 = (s32)result;
    ((S_80171D64_3 *)((void *)reused_arg3))->unk_24 = saved_arg1;
    ((S_80171D64_1 *)result)->unk_4B = field_4b;
    ((S_80171D64_1 *)result)->unk_48 = kind_e;
    ((S_80171D64_1 *)result)->unk_49 = kind_f;

    if (selector == 1) {
        (*(u32 *)((u8 *)result + 0x14)) |= 0x6000;
        branch_flags = ((S_80171D64_1 *)result)->unk_1C;
        global_kind = (u8)D_800E2968;
        ((S_80171D64_1 *)result)->unk_1C = branch_flags | 0x6000;
        if (global_kind >= 0xA) {
            if (global_kind < 0xD) {
                ((S_80171D64_1 *)result)->unk_48 = kind_f;
            } else {
                ((S_80171D64_1 *)result)->unk_48 = 0xD;
            }
        }
        goto setup;
    }

    if (selector >= 2) {
        ASM_KEEP(selector);   /* MATCH pin: load-bearing for the whole function shape */
        ((S_80171D64_1 *)result)->unk_14 |= 0x2000;
        ((S_80171D64_1 *)result)->unk_1C |= 0x2000;
        goto setup;
    }

    global_kind = (u8)D_800E2968;
    if (global_kind < 0xA) {
        ((S_80171D64_1 *)result)->unk_48 = kind_e;
    } else if (global_kind < 0xD) {
        ((S_80171D64_1 *)result)->unk_48 = kind_f;
    } else {
        ((S_80171D64_1 *)result)->unk_48 = 0xD;
    }

    if (((original_arg0 & ~3) << 16) == 0) {
        selector = (s32)created;
        ASM_KEEP_NV(selector);   /* MATCH pin: load-bearing for the whole function shape */
        if (!(((S_80171D64_1 *)result)->unk_14 & 0x200)) {
            kind_e = (s32)position;
            ASM_KEEP(kind_e);   /* MATCH pin: retail delay-slot contents depend on it */
            field_4b = func_800A6D30((void *)selector, (void *)kind_e);
            selector = (s32)created;
            if (field_4b & 1) {
                func_800A48F0(result, 1,
                    (func_800A6D30((void *)selector) & 0x3F) | 0x20);
                kind = ((S_80171D64_1 *)result)->unk_48;
                if (kind == 0xE) {
                    goto callback_e;
                }
                if (kind < 0xF) {
                    if (kind == 0xD) {
                        goto callback_d;
                    }
                    goto setup;
                }
                if (kind == 0xF) {
                    goto callback_f;
                }
                goto setup;

callback_d:
                current_callback = ((S_80171D64_3 *)((void *)reused_arg3))->unk_2C;
                new_callback = D_80175E54;
                goto callback_compare;
callback_e:
                current_callback = ((S_80171D64_3 *)((void *)reused_arg3))->unk_2C;
                new_callback = D_80175E5C;
                goto callback_compare;
callback_f:
                current_callback = ((S_80171D64_3 *)((void *)reused_arg3))->unk_2C;
                new_callback = D_80175E64;
callback_compare:
                if (current_callback != new_callback) {
                    ((S_80171D64_3 *)((void *)reused_arg3))->unk_2C = new_callback;
                }
            } else {
                goto setup_args_ready;
            }
        } else {
            kind_e = (s32)position;
            goto setup_args2_ready;
        }
    }

setup:
    selector = (s32)created;
setup_args_ready:
    kind_e = (s32)position;
setup_args2_ready:
    func_800A9C18((void *)selector, (void *)kind_e, (void *)reused_arg3,
        (s16)original_arg0);
    ((S_80171D64_4 *)((void *)reused_arg2))->unk_9A = 0xFF;
    ((S_80171D64_4 *)((void *)reused_arg2))->unk_9C = -1;
    ((S_80171D64_4 *)((void *)reused_arg2))->unk_8C = D_801724BC;
    func_800AA36C((void *)reused_arg2, position, (void *)reused_arg3, result);

    kind = ((S_80171D64_1 *)result)->unk_48;
    if (kind == 0xE) {
        goto select_e;
    }
    if (kind < 0xF) {
        if (kind == 0xD) {
            goto select_d;
        }
        return result;
    }
    if (kind == 0xF) {
        goto select_f;
    }
    return result;

select_d:
    current_callback = ((S_80171D64_3 *)((void *)reused_arg3))->unk_2C;
    table = D_80175E24;
    if (current_callback == table) {
        goto done;
    }
    goto table_store;
select_e:
    current_callback = ((S_80171D64_3 *)((void *)reused_arg3))->unk_2C;
    table = D_80175E2C;
    if (current_callback == table) {
        goto done;
    }
    goto table_store;
select_f:
    current_callback = ((S_80171D64_3 *)((void *)reused_arg3))->unk_2C;
    table = D_80175E34;
    if (current_callback == table) {
        goto done;
    }
table_store:
    (*(void * *)((u8 *)((void *)reused_arg3) + 0x2C)) = table;
    table_index = ((D_80083228 + ((S_80171D64_1 *)result)->unk_2A + 0x100) >> 9) & 7;
    func_80047784((void *)reused_arg3,
        *(u8 *)((u32)table_index + (u32)table),
        0);
done:
    return result;
}
