#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
typedef unsigned long uptr;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30();
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_80047784(void *, s32, s32);
extern void func_800478E8(void *, void *, s32);

extern s32 D_80045340;
extern s16 D_80083228;
extern u8 D_80083498[];
extern u8 D_800D71A8[];
extern u8 D_800D78C0[];
extern u8 D_80158BF8[];
extern u8 D_80159400[];
extern u8 D_8015D140[];
extern u8 D_8015D168[];
extern u8 D_8015D188[];

void *func_801588DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    struct {
        void *root;
        void *copy;
        s32 outer_index;
    } stack;
    register s32 saved_kind ASM_REG("$16");
    register s32 saved_arg3 ASM_REG("$17");
    register s32 saved_arg2 ASM_REG("$18");
    register void *object ASM_REG("$19");
    register void *outer ASM_REG("$20");
    register void *stable_object ASM_REG("$21");
    register s32 kind_copy ASM_REG("$22");
    register void *part ASM_REG("$23");
    register void *allocated ASM_REG("$2");
    register uptr temp_t0 ASM_REG("$8");
    register s32 allocation_size ASM_REG("$4");
    register void *allocation_pool ASM_REG("$5");

    saved_kind = arg0;
    object = 0;
    allocation_size = 0x112;
    ASM_KEEP_NV(allocation_size);
    outer = (void *)(s32)arg1;
    allocation_pool = D_80083498;
    ASM_KEEP_NV(allocation_pool);
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    allocated = func_8003FD64(allocation_size, allocation_pool);
    ASM_KEEP(object);
    kind_copy = saved_kind;
    stack.root = allocated;
    if (allocated == 0) {
        goto done;
    }

    {
        register void *init_root ASM_REG("$4");
        register void *setup ASM_REG("$5");

        object = (u8 *)allocated + 0x20;
        init_root = allocated;
        setup = &D_80045340;
        FIELD(init_root, void *, 0x10) = D_80158BF8;
        FIELD(object, u8, 0x13) = 4;
        func_8004491C(init_root, setup);
    }

    {
        register void *part_callback ASM_REG("$2");

        temp_t0 = (uptr)stack.root;
        part_callback = D_8015D140;
        temp_t0 = (uptr)FIELD((void *)temp_t0, void *, 8);
        stack.copy = (void *)temp_t0;
        FIELD((void *)temp_t0, s16, 0xA) = saved_arg3;
        temp_t0 = (uptr)stack.root;
        ASM_KEEP(temp_t0);
        stable_object = object;
        part = FIELD((void *)temp_t0, void *, 0xC);
        FIELD(part, void *, 0x2C) = part_callback;
    }
    FIELD(part, s8, 0x24) = (s8)(s32)outer;
    FIELD(part, s8, 0x25) = saved_arg2;

    {
        register s32 flags0 ASM_REG("$2");
        register s32 flags1 ASM_REG("$3");

        if ((saved_kind & 3) == 1) {
            flags0 = FIELD(object, s32, 0x14) | 0x6000;
            flags1 = FIELD(object, s32, 0x1C) | 0x6000;
            goto store_flags;
        }
        if ((saved_kind & 3) >= 2) {
            flags0 = FIELD(object, s32, 0x14) | 0x2000;
            flags1 = FIELD(object, s32, 0x1C) | 0x2000;
            goto store_flags;
        }
        goto update_kind;

store_flags:
        FIELD(object, s32, 0x14) = flags0;
        FIELD(object, s32, 0x1C) = flags1;
        goto flags_done;

update_kind:
        flags0 = (saved_kind & -4) << 16;
        if (flags0 == 0) {
            if ((FIELD(object, s32, 0x14) & 0x200) == 0) {
                if (func_800A6D30() & 1) {
                    FIELD(object, s32, 0x1C) |= 0x200;
                    func_800A48F0(object, 1,
                        (func_800A6D30() & 0x3F) | 0x20);
                    FIELD(part, void *, 0x2C) = D_8015D188;
                }
            }
        }

flags_done:
        ;
    }

    func_800A9C18(stack.root, stack.copy, part, (s16)kind_copy);

    outer = stable_object;
    stack.outer_index = 0;
    FIELD(stable_object, u8, 0x9A) = 0xFF;
    FIELD(stable_object, s8, 0x9C) = -1;
    FIELD(stable_object, void *, 0x8C) = D_80159400;
    FIELD(object, s32, 0x1C) |= 0x40000;
    FIELD(stable_object, s16, 0x92) = -0x20;
    FIELD(stable_object, s16, 0xA8) = 0;
    FIELD(stable_object, s16, 0x9E) = 1;
    FIELD(stable_object, u16, 0x98) |= 0x4000;

    do {
        void *child;

        child = func_8003FD64(0x112, D_80083498);
        allocated = child;
        FIELD(outer, void *, 0xA4) = allocated;
        if (allocated != 0) {
            register void *entry ASM_REG("$16");
            register s32 entry_offset ASM_REG("$17");
            register s32 inner_index ASM_REG("$18");
            register void *outer_base;
            register u8 *table ASM_REG("$22");
            register s32 inner_more ASM_REG("$3");

            entry = (u8 *)allocated + 0x20;
            temp_t0 = 1;
            FIELD(entry, s16, 2) = (s16)temp_t0;
            inner_index = 0;
            outer_base = outer;
            ASM_KEEP(outer_base);
            {
                register u8 *table_page ASM_REG("$2");

                table_page = (u8 *)0x80160000;
                ASM_KEEP(table_page);
                table = table_page - 0x2E98;
            }
            entry_offset = 8;
            do {
                void *item;
                s32 table_index;
                register s32 color ASM_REG("$5");
                register s32 part_value ASM_REG("$3");
                register s32 call_zero ASM_REG("$6");
                register void *outer_child ASM_REG("$2");
                register void *new_link ASM_REG("$2");

                ASM_KEEP(inner_index);
                color = 0x00808080;
                item = (u8 *)entry + entry_offset;
                FIELD(entry, u16, 4) |= 0x8000;
                part_value = FIELD(part, s32, 0x28);
                FIELD(item, s16, 0x10) = 0x20;
                FIELD(item, s32, 0xC) = color;
                FIELD(item, s32, 0x28) = part_value;
                outer_child = FIELD(outer_base, void *, 0xA4);
                ASM_KEEP(outer_child);
                call_zero = 0;
                ASM_KEEP(call_zero);
                temp_t0 = (uptr)D_800D78C0;
                FIELD(outer_child, void *, 0x10) = (void *)temp_t0;
                FIELD(item, void *, 0x2C) = table;
                table_index = ((D_80083228 +
                    FIELD(object, s16, 0x2A) + 0x100) >> 9) & 7;
                entry_offset += 0x30;
                ASM_KEEP(entry_offset);
                func_80047784(item,
                    *(u8 *)((uptr)table_index + (uptr)table), call_zero);
                inner_index++;
                {
                    register void *call_part ASM_REG("$4");
                    register void *call_data ASM_REG("$5");
                    register s32 call_one ASM_REG("$6");

                    call_part = part;
                    call_data = D_800D71A8;
                    call_one = 1;
                    ASM_KEEP(call_one);
                    temp_t0 = (uptr)call_one;
                    FIELD(entry, s16, 6) = (s16)temp_t0;
                    func_800478E8(call_part, call_data, call_one);
                }
                temp_t0 = (uptr)stack.root;
                new_link = (u8 *)temp_t0 + 0x1E;
                inner_more = inner_index < FIELD(entry, s16, 2);
                FIELD(entry, void *, 0x98) = new_link;
            } while (inner_more);
        }
        outer = (u8 *)outer + 4;
        ASM_KEEP(outer);
        {
            register s32 outer_limit ASM_REG("$2");
            register s32 outer_more ASM_REG("$2");

            temp_t0 = (uptr)stack.outer_index;
            outer_limit = FIELD(stable_object, s16, 0x9E);
            temp_t0++;
            stack.outer_index = (s32)temp_t0;
            outer_more = (s32)temp_t0 < outer_limit;
            if (!outer_more) {
                break;
            }
        }
    } while (1);

    func_800AA36C(stable_object, stack.copy, part, object);

done:
    return object;
}
