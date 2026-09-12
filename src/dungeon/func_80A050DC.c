#include "common.h"

typedef unsigned long uptr;

typedef struct S_8015E8DC_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8015E8DC_0;   /* init_root in func_8015E8DC */

typedef struct S_8015E8DC_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_8015E8DC_1;   /* object in func_8015E8DC */

typedef struct S_8015E8DC_2 {
    u8 pad_00[0x8];
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    void * unk_0C;
} S_8015E8DC_2;   /* (void *)temp_t0 in func_8015E8DC */

typedef struct S_8015E8DC_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    void * unk_2C;
} S_8015E8DC_3;   /* part in func_8015E8DC */

typedef struct S_8015E8DC_4 {
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
} S_8015E8DC_4;   /* stable_object in func_8015E8DC */

typedef struct S_8015E8DC_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015E8DC_5;   /* outer in func_8015E8DC */

typedef struct S_8015E8DC_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} S_8015E8DC_6;   /* entry in func_8015E8DC */

typedef struct S_8015E8DC_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x16];
    s32 unk_28;
} S_8015E8DC_7;   /* item in func_8015E8DC */

typedef struct S_8015E8DC_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015E8DC_8;   /* outer_base in func_8015E8DC */

typedef struct S_8015E8DC_9 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8015E8DC_9;   /* outer_child in func_8015E8DC */


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
extern u8 D_8015EBF8[];
extern u8 D_8015F400[];
extern u8 D_80163140[];
extern u8 D_80163188[];

/* Allocate and initialize an object and its child entries. */
void *func_8015E8DC(s32 kind, s32 part_byte_24, s32 part_byte_25, s32 copy_value)
{
    struct {
        void *root;
        void *copy;
        s32 outer_index;
    } stack;
    register s32 saved_kind ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 saved_copy_value ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 saved_part_byte_25 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *object;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *outer ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *stable_object;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 kind_copy;
    void *part;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *allocated;
    register uptr setup_scratch ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 allocation_size;
    void *allocation_pool;

    saved_kind = kind;
    object = 0;
    allocation_size = 0x112;
    ASM_KEEP_NV(allocation_size);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    outer = (void *)(s32)part_byte_24;
    allocation_pool = D_80083498;
   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    saved_copy_value = copy_value;
    saved_part_byte_25 = part_byte_25;
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
        ((S_8015E8DC_0 *)init_root)->unk_10 = D_8015EBF8;
        ((S_8015E8DC_1 *)object)->unk_13 = 4;
        func_8004491C(init_root, setup);
    }

    {
        void *part_callback;

        setup_scratch = (uptr)stack.root;
        part_callback = D_80163140;
        setup_scratch = (uptr)((S_8015E8DC_2 *)((void *)setup_scratch))->unk_08.at00.v;
        stack.copy = (void *)setup_scratch;
        ((S_8015E8DC_2 *)((void *)setup_scratch))->unk_08.at02.v = saved_copy_value;
        setup_scratch = (uptr)stack.root;
        stable_object = object;
        part = ((S_8015E8DC_2 *)((void *)setup_scratch))->unk_0C;
        ((S_8015E8DC_3 *)part)->unk_2C = part_callback;
    }
    ((S_8015E8DC_3 *)part)->unk_24 = (s8)(s32)outer;
    ((S_8015E8DC_3 *)part)->unk_25 = saved_part_byte_25;

    {
        s32 flags_14;
        s32 flags_1c;

        if ((saved_kind & 3) == 1) {
            flags_14 = ((S_8015E8DC_1 *)object)->unk_14 | 0x6000;
            flags_1c = ((S_8015E8DC_1 *)object)->unk_1C | 0x6000;
            ((S_8015E8DC_1 *)object)->unk_14 = flags_14;
            ((S_8015E8DC_1 *)object)->unk_1C = flags_1c;
            goto flags_done;
        }
        if ((saved_kind & 3) >= 2) {
            flags_14 = ((S_8015E8DC_1 *)object)->unk_14 | 0x2000;
            flags_1c = ((S_8015E8DC_1 *)object)->unk_1C | 0x2000;
            ((S_8015E8DC_1 *)object)->unk_14 = flags_14;
            ((S_8015E8DC_1 *)object)->unk_1C = flags_1c;
            goto flags_done;
        }
        goto update_kind;


update_kind:
        flags_14 = saved_kind & ~3;
        if ((s16)flags_14 == 0) {
            if ((((S_8015E8DC_1 *)object)->unk_14 & 0x200) == 0) {
                if (func_800A6D30() & 1) {
                    ((S_8015E8DC_1 *)object)->unk_1C |= 0x200;
                    func_800A48F0(object, 1,
                        (func_800A6D30() & 0x3F) | 0x20);
                    ((S_8015E8DC_3 *)part)->unk_2C = D_80163188;
                }
            }
        }

flags_done:
        ;
    }

    func_800A9C18(stack.root, stack.copy, part, (s16)kind_copy);

    outer = stable_object;
    stack.outer_index = 0;
    ((S_8015E8DC_4 *)stable_object)->unk_9A = 0xFF;
    ((S_8015E8DC_4 *)stable_object)->unk_9C = -1;
    ((S_8015E8DC_4 *)stable_object)->unk_8C = D_8015F400;
    ((S_8015E8DC_1 *)object)->unk_1C |= 0x40000;
    ((S_8015E8DC_4 *)stable_object)->unk_92 = -0x20;
    ((S_8015E8DC_4 *)stable_object)->unk_A8 = 0;
    ((S_8015E8DC_4 *)stable_object)->unk_9E = 1;
    ((S_8015E8DC_4 *)stable_object)->unk_98 |= 0x4000;

    do {
        void *child;

        child = func_8003FD64(0x112, D_80083498);
        allocated = child;
        ((S_8015E8DC_5 *)outer)->unk_A4 = allocated;
        if (allocated != 0) {
            register void *entry ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            s32 item_offset;
            s32 item_index;
            register void *outer_base;
            register u8 *direction_table ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 more_items;

            entry = (u8 *)allocated + 0x20;
            setup_scratch = 1;
            ((S_8015E8DC_6 *)entry)->unk_02 = (s16)setup_scratch;
            item_index = 0;
            do {
                outer_base = outer;
            } while (0);
            {
                register u8 *direction_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                direction_page = (u8 *)0x80160000;
                ASM_KEEP(direction_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                direction_table = direction_page + 0x3168;
            }
            item_offset = 8;
            do {
                void *item;
                s32 direction_index;
                register s32 color ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                s32 part_value;
                s32 call_zero;
                void *outer_child;
                register void *root_link ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                color = 0x00808080;
                item = (u8 *)entry + item_offset;
                ((S_8015E8DC_6 *)entry)->unk_04 |= 0x8000;
                part_value = ((S_8015E8DC_3 *)part)->unk_28;
                ((S_8015E8DC_7 *)item)->unk_10 = 0x20;
                ((S_8015E8DC_7 *)item)->unk_0C = color;
                ((S_8015E8DC_7 *)item)->unk_28 = part_value;
                outer_child = ((S_8015E8DC_8 *)outer_base)->unk_A4;
                do {
                    call_zero = 0;
                } while (0);
                ASM_KEEP(call_zero);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                setup_scratch = (uptr)D_800D78C0;
                ((S_8015E8DC_9 *)outer_child)->unk_10 = (void *)setup_scratch;
                (*(void * *)((u8 *)item + 0x2C)) = direction_table;
                direction_index = ((D_80083228 +
                    ((S_8015E8DC_1 *)object)->unk_2A + 0x100) >> 9) & 7;
                item_offset += 0x30;
                func_80047784(item,
                    *(u8 *)((uptr)direction_index + (uptr)direction_table), call_zero);
                item_index++;
                {
                    register void *call_part ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    register void *call_data ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                    register s32 call_one ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                    call_part = part;
                    call_data = D_800D71A8;
                    call_one = 1;
                    ASM_KEEP(call_one);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                    setup_scratch = (uptr)call_one;
                    ((S_8015E8DC_6 *)entry)->unk_06 = (s16)setup_scratch;
                    func_800478E8(call_part, call_data, call_one);
                }
                setup_scratch = (uptr)stack.root;
                root_link = (u8 *)setup_scratch + 0x1E;
                more_items = item_index < ((S_8015E8DC_6 *)entry)->unk_02;
                ((S_8015E8DC_6 *)entry)->unk_98 = root_link;
            } while (more_items);
        }
        outer = (u8 *)outer + 4;
        {
            s32 child_count;
            register s32 more_children ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            setup_scratch = (uptr)stack.outer_index;
            child_count = ((S_8015E8DC_4 *)stable_object)->unk_9E;
            setup_scratch++;
            stack.outer_index = (s32)setup_scratch;
            more_children = (s32)setup_scratch < child_count;
            if (!more_children) {
                break;
            }
        }
    } while (1);

    func_800AA36C(stable_object, stack.copy, part, object);

done:
    return object;
}
