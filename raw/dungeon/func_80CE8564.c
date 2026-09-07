#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
    register s32 saved_arg0 ASM_REG("$21");
    register void *result ASM_REG("$16");
    register s32 saved_arg1 ASM_REG("$20");
    register s32 reused_arg3 ASM_REG("$17");
    register s32 reused_arg2 ASM_REG("$19");
    register s32 original_arg0 ASM_REG("$23");
    register void *created ASM_REG("$18");
    register void *position ASM_REG("$22");
    register s32 selector ASM_REG("$4");
    register s32 kind_e ASM_REG("$5");
    register s32 kind_f ASM_REG("$6");
    register s32 field_4b ASM_REG("$2");
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
    ASM_KEEP_DEP_NV(saved_arg1, selector);
    kind_e = (s32)D_80083498;
    ASM_KEEP_DEP_NV(kind_e, saved_arg1);
    reused_arg3 = arg3;
    ASM_KEEP_DEP_NV(reused_arg3, kind_e);
    reused_arg2 = arg2;
    created = func_8003FD64(selector, (void *)kind_e);
    original_arg0 = saved_arg0;
    if (created == 0) {
        goto done;
    }

    result = (u8 *)created + 0x20;
    FIELD(created, void *, 0x10) = D_801720B4;
    FIELD(result, s8, 0x13) = 0x16;
    func_8004491C(created, &D_80045340);

    initial_callback = D_80175E24;
    ASM_KEEP(initial_callback);
    kind_e = 0xE;
    position = FIELD(created, void *, 8);
    ASM_KEEP(position);
    kind_f = 0xF;
    FIELD(position, s16, 0xA) = reused_arg3;
    reused_arg3 = (s32)FIELD(created, void *, 0xC);
    ASM_KEEP(reused_arg3);
    selector = saved_arg0 & 3;
    FIELD((void *)reused_arg3, void *, 0x2C) = initial_callback;
    ASM_KEEP(initial_callback);
    field_4b = 0x20;
    ASM_KEEP(field_4b);
    FIELD((void *)reused_arg3, s8, 0x25) = reused_arg2;
    reused_arg2 = (s32)result;
    FIELD((void *)reused_arg3, s8, 0x24) = saved_arg1;
    FIELD(result, s8, 0x4B) = field_4b;
    FIELD(result, u8, 0x48) = kind_e;
    FIELD(result, s8, 0x49) = kind_f;

    if (selector == 1) {
        FIELD(result, u32, 0x14) |= 0x6000;
        branch_flags = FIELD(result, u32, 0x1C);
        global_kind = (u8)D_800E2968;
        FIELD(result, u32, 0x1C) = branch_flags | 0x6000;
        if (global_kind >= 0xA) {
            if (global_kind < 0xD) {
                FIELD(result, u8, 0x48) = kind_f;
            } else {
                FIELD(result, u8, 0x48) = 0xD;
            }
        }
        goto setup;
    }

    if (selector >= 2) {
        ASM_KEEP(selector);
        FIELD(result, u32, 0x14) |= 0x2000;
        FIELD(result, u32, 0x1C) |= 0x2000;
        goto setup;
    }

    global_kind = (u8)D_800E2968;
    ASM_UNDEF(kind_e);
    if (global_kind < 0xA) {
        FIELD(result, u8, 0x48) = kind_e;
    } else if (global_kind < 0xD) {
        FIELD(result, u8, 0x48) = kind_f;
    } else {
        FIELD(result, u8, 0x48) = 0xD;
    }

    if (((original_arg0 & ~3) << 16) == 0) {
        selector = (s32)created;
        ASM_KEEP_NV(selector);
        if (!(FIELD(result, u32, 0x14) & 0x200)) {
            kind_e = (s32)position;
            ASM_KEEP(kind_e);
            field_4b = func_800A6D30((void *)selector, (void *)kind_e);
            selector = (s32)created;
            if (field_4b & 1) {
                ASM_KEEP(selector);
                func_800A48F0(result, 1,
                    (func_800A6D30((void *)selector) & 0x3F) | 0x20);
                kind = FIELD(result, u8, 0x48);
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
                current_callback = FIELD((void *)reused_arg3, void *, 0x2C);
                new_callback = D_80175E54;
                goto callback_compare;
callback_e:
                current_callback = FIELD((void *)reused_arg3, void *, 0x2C);
                new_callback = D_80175E5C;
                goto callback_compare;
callback_f:
                current_callback = FIELD((void *)reused_arg3, void *, 0x2C);
                new_callback = D_80175E64;
callback_compare:
                if (current_callback != new_callback) {
                    FIELD((void *)reused_arg3, void *, 0x2C) = new_callback;
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
    FIELD((void *)reused_arg2, u8, 0x9A) = 0xFF;
    FIELD((void *)reused_arg2, s8, 0x9C) = -1;
    FIELD((void *)reused_arg2, void *, 0x8C) = D_801724BC;
    func_800AA36C((void *)reused_arg2, position, (void *)reused_arg3, result);

    kind = FIELD(result, u8, 0x48);
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
    current_callback = FIELD((void *)reused_arg3, void *, 0x2C);
    table = D_80175E24;
    if (current_callback == table) {
        goto done;
    }
    goto table_store;
select_e:
    current_callback = FIELD((void *)reused_arg3, void *, 0x2C);
    table = D_80175E2C;
    if (current_callback == table) {
        goto done;
    }
    goto table_store;
select_f:
    current_callback = FIELD((void *)reused_arg3, void *, 0x2C);
    table = D_80175E34;
    if (current_callback == table) {
        goto done;
    }
table_store:
    FIELD((void *)reused_arg3, void *, 0x2C) = table;
    table_index = ((D_80083228 + FIELD(result, s16, 0x2A) + 0x100) >> 9) & 7;
    func_80047784((void *)reused_arg3,
        *(u8 *)((u32)table_index + (u32)table),
        0);
done:
    ASM_KEEP(result);
    ASM_KEEP(created);
    ASM_KEEP(position);
    ASM_KEEP(saved_arg0);
    ASM_KEEP(saved_arg1);
    ASM_KEEP(original_arg0);
    return result;
}
