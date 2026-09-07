#include "common.h"

typedef unsigned long uptr;

typedef struct S_801588DC_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_801588DC_0;   /* init_root in func_801588DC */

typedef struct S_801588DC_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_801588DC_1;   /* object in func_801588DC */

typedef struct S_801588DC_2 {
    u8 pad_00[0x8];
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    void * unk_0C;
} S_801588DC_2;   /* (void *)temp_t0 in func_801588DC */

typedef struct S_801588DC_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    void * unk_2C;
} S_801588DC_3;   /* part in func_801588DC */

typedef struct S_801588DC_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
    u8 pad_A0[0x8];
    s16 unk_A8;
} S_801588DC_4;   /* stable_object in func_801588DC */

typedef struct S_801588DC_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_801588DC_5;   /* outer in func_801588DC */

typedef struct S_801588DC_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} S_801588DC_6;   /* entry in func_801588DC */

typedef struct S_801588DC_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x16];
    s32 unk_28;
} S_801588DC_7;   /* item in func_801588DC */

typedef struct S_801588DC_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_801588DC_8;   /* outer_base in func_801588DC */

typedef struct S_801588DC_9 {
    u8 pad_00[0x10];
    void * unk_10;
} S_801588DC_9;   /* outer_child in func_801588DC */


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

/* Allocate and initialize an object and its child items for the given kind. */
void *func_801588DC(s32 kind, s32 part_x, s32 part_y, s32 copy_value)
{
    struct {
        void *root;
        void *copy;
        s32 outer_index;
    } stack;
    register s32 saved_kind ASM_REG("$16");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 saved_copy_value ASM_REG("$17");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 saved_part_y ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *object ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *outer ASM_REG("$20");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *stable_object ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    s32 kind_copy;
    register void *part ASM_REG("$23");   /* MATCH pin: retail register colouring depends on it */
    void *allocated;
    register uptr address_or_count ASM_REG("$8");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 allocation_size ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *allocation_pool;   /* MATCH pin: retail schedule: same instructions, different order without it */

    saved_kind = kind;
    object = 0;
    allocation_size = 0x112;
    ASM_KEEP_NV(allocation_size);   /* MATCH pin: retail schedule: same instructions, different order without it */
    outer = (void *)(s32)part_x;
    allocation_pool = D_80083498;
       /* MATCH pin: retail schedule: same instructions, different order without it */
    saved_copy_value = copy_value;
    saved_part_y = part_y;
    allocated = func_8003FD64(allocation_size, allocation_pool);
    kind_copy = saved_kind;
    stack.root = allocated;
    if (allocated == 0) {
        goto done;
    }

    {
        void *init_root;
        void *setup;

        object = (u8 *)allocated + 0x20;
        init_root = allocated;
        setup = &D_80045340;
        ((S_801588DC_0 *)init_root)->unk_10 = D_80158BF8;
        ((S_801588DC_1 *)object)->unk_13 = 4;
        func_8004491C(init_root, setup);
    }

    {
        void *part_callback;

        address_or_count = (uptr)stack.root;
        part_callback = D_8015D140;
        address_or_count = (uptr)((S_801588DC_2 *)((void *)address_or_count))->unk_08.at00.v;
        stack.copy = (void *)address_or_count;
        ((S_801588DC_2 *)((void *)address_or_count))->unk_08.at02.v = saved_copy_value;
        address_or_count = (uptr)stack.root;
        stable_object = object;
        part = ((S_801588DC_2 *)((void *)address_or_count))->unk_0C;
        ((S_801588DC_3 *)part)->unk_2C = part_callback;
    }
    ((S_801588DC_3 *)part)->unk_24 = (s8)(s32)outer;
    ((S_801588DC_3 *)part)->unk_25 = saved_part_y;

    {
        register s32 flags_14 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 flags_1c;

        if ((saved_kind & 3) == 1) {
            flags_14 = ((S_801588DC_1 *)object)->unk_14 | 0x6000;
            flags_1c = ((S_801588DC_1 *)object)->unk_1C | 0x6000;
            goto store_flags;
        }
        if ((saved_kind & 3) >= 2) {
            flags_14 = ((S_801588DC_1 *)object)->unk_14 | 0x2000;
            flags_1c = ((S_801588DC_1 *)object)->unk_1C | 0x2000;
            goto store_flags;
        }
        goto update_kind;

store_flags:
        ((S_801588DC_1 *)object)->unk_14 = flags_14;
        ((S_801588DC_1 *)object)->unk_1C = flags_1c;
        goto flags_done;

update_kind:
        flags_14 = (saved_kind & -4) << 16;
        if (flags_14 == 0) {
            if ((((S_801588DC_1 *)object)->unk_14 & 0x200) == 0) {
                if (func_800A6D30() & 1) {
                    ((S_801588DC_1 *)object)->unk_1C |= 0x200;
                    func_800A48F0(object, 1,
                        (func_800A6D30() & 0x3F) | 0x20);
                    ((S_801588DC_3 *)part)->unk_2C = D_8015D188;
                }
            }
        }

flags_done:
        ;
    }

    func_800A9C18(stack.root, stack.copy, part, (s16)kind_copy);

    outer = stable_object;
    stack.outer_index = 0;
    ((S_801588DC_4 *)stable_object)->unk_9A = 0xFF;
    ((S_801588DC_4 *)stable_object)->unk_9C = -1;
    ((S_801588DC_4 *)stable_object)->unk_8C = D_80159400;
    ((S_801588DC_1 *)object)->unk_1C |= 0x40000;
    ((S_801588DC_4 *)stable_object)->unk_92 = -0x20;
    ((S_801588DC_4 *)stable_object)->unk_A8 = 0;
    ((S_801588DC_4 *)stable_object)->unk_9E = 1;
    ((S_801588DC_4 *)stable_object)->unk_98 |= 0x4000;

    do {
        void *child;

        child = func_8003FD64(0x112, D_80083498);
        allocated = child;
        ((S_801588DC_5 *)outer)->unk_A4 = allocated;
        if (allocated != 0) {
            register void *entry ASM_REG("$16");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            s32 item_offset;
            s32 item_index;
            register void *outer_base;
            register u8 *table ASM_REG("$22");   /* MATCH pin: load-bearing for the whole function shape */
            s32 more_items;

            entry = (u8 *)allocated + 0x20;
            address_or_count = 1;
            ((S_801588DC_6 *)entry)->unk_02 = (s16)address_or_count;
            item_index = 0;
            outer_base = outer;
            ASM_KEEP(outer_base);   /* MATCH pin: retail schedule: same instructions, different order without it */
            {
                register u8 *table_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

                table_page = (u8 *)0x80160000;
                ASM_KEEP(table_page);   /* MATCH pin: load-bearing for the whole function shape */
                table = table_page - 0x2E98;
            }
            item_offset = 8;
            do {
                void *item;
                s32 direction_index;
                register s32 color ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
                s32 part_value;
                s32 call_zero;
                void *outer_child;
                register void *new_link ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

                color = 0x00808080;
                item = (u8 *)entry + item_offset;
                ((S_801588DC_6 *)entry)->unk_04 |= 0x8000;
                part_value = ((S_801588DC_3 *)part)->unk_28;
                ((S_801588DC_7 *)item)->unk_10 = 0x20;
                ((S_801588DC_7 *)item)->unk_0C = color;
                ((S_801588DC_7 *)item)->unk_28 = part_value;
                outer_child = ((S_801588DC_8 *)outer_base)->unk_A4;
                ASM_KEEP(outer_child);   /* MATCH pin: retail schedule: same instructions, different order without it */
                call_zero = 0;
                ASM_KEEP(call_zero);   /* MATCH pin: retail schedule: same instructions, different order without it */
                address_or_count = (uptr)D_800D78C0;
                ((S_801588DC_9 *)outer_child)->unk_10 = (void *)address_or_count;
                (*(void * *)((u8 *)item + 0x2C)) = table;
                direction_index = ((D_80083228 +
                    ((S_801588DC_1 *)object)->unk_2A + 0x100) >> 9) & 7;
                item_offset += 0x30;
                func_80047784(item,
                    *(u8 *)((uptr)direction_index + (uptr)table), call_zero);
                item_index++;
                {
                    register void *call_part ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
                    register void *call_data ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
                    register s32 call_one ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */

                    call_part = part;
                    call_data = D_800D71A8;
                    call_one = 1;
                    ASM_KEEP(call_one);   /* MATCH pin: keeps a constant in a register as retail does */
                    address_or_count = (uptr)call_one;
                    ((S_801588DC_6 *)entry)->unk_06 = (s16)address_or_count;
                    func_800478E8(call_part, call_data, call_one);
                }
                address_or_count = (uptr)stack.root;
                new_link = (u8 *)address_or_count + 0x1E;
                more_items = item_index < ((S_801588DC_6 *)entry)->unk_02;
                ((S_801588DC_6 *)entry)->unk_98 = new_link;
            } while (more_items);
        }
        outer = (u8 *)outer + 4;
        {
            s32 child_count;
            register s32 more_children ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

            address_or_count = (uptr)stack.outer_index;
            child_count = ((S_801588DC_4 *)stable_object)->unk_9E;
            address_or_count++;
            stack.outer_index = (s32)address_or_count;
            more_children = (s32)address_or_count < child_count;
            if (!more_children) {
                break;
            }
        }
    } while (1);

    func_800AA36C(stable_object, stack.copy, part, object);

done:
    return object;
}
