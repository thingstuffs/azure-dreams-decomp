#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800254A4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800254A4_0;   /* obj in func_800254A4 */

typedef struct S_800254A4_1 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800254A4_1;   /* root in func_800254A4 */

typedef struct S_800254A4_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800254A4_2;   /* packet in func_800254A4 */

typedef struct S_800254A4_3 {
    u8 pad_00[0x4C];
    void * unk_4C;
    u8 pad_50[0x6];
    s16 unk_56;
} S_800254A4_3;   /* part1 in func_800254A4 */

typedef struct S_800254A4_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800254A4_4;   /* draw in func_800254A4 */

typedef struct S_800254A4_5 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x4];
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800254A4_5;   /* part2 in func_800254A4 */

typedef struct S_800254A4_6 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800254A4_6;   /* part3 in func_800254A4 */

typedef struct S_800254A4_7 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 unk_08;
    volatile s16 unk_0C;
    volatile s16 unk_0E;
    s16 unk_10;
    volatile s16 unk_12;
    s16 unk_14;
    volatile u16 unk_16;
} S_800254A4_7;   /* final_part in func_800254A4 */



extern u8 D_8002012C[];
extern u8 D_80020134[];
extern u8 D_8002013C[];
extern u8 D_80020140[];
extern u8 D_80020144[];
extern u8 D_80020148[];
extern u8 D_8002582C[];
extern u8 D_80025BC8[];
extern u8 D_80026B78[];
extern u8 D_80026BC4[];
extern u8 D_80026C54[];
extern u8 D_80026F50[];
extern u8 D_80045340[];
extern s32 D_80053858[4];
extern s32 D_80053A88;
extern u8 D_80083498[];
extern u8 D_800F7968[];

extern void func_80026CE4(s32);
extern void func_8003DB94(void *, void *, s32, void *);
extern void func_8003E188(s32, s32);
extern void *func_8003FC64(s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern void func_8008F074(void *, void *, void *);
extern void tw_sd_sq_ld_call(s32, s32);

/* Creates a parent object, three children, paired display rows, and a final display element. */
s32 func_800254A4(void)
{
    void *left_data[2];
    void *right_data[2];
    register u8 *parent_state ASM_REG("$21") = NULL;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *object;
    S_800254A4_3 *child_state;
    S_800254A4_5 *left_state;
    S_800254A4_6 *right_state;
    S_800254A4_7 *final_state;
    S_800254A4_4 *draw_state;
    S_800254A4_2 *packet;
    void *value_ptr;
    void *row_data;
    void *child_callback;
    void *callback;
    void *child_data;
    void **child_slot;
    u8 *initial_data;
    u8 *src_byte;
    u8 *first_dst_byte;
    u8 *second_dst_byte;
    u8 initial_byte;
    s32 index;
    s32 final_color;
    register s32 final_extent ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 row_y;

    do {
        left_data[0] = D_8002012C;
    } while (0);
    left_data[1] = D_80020134;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    right_data[0] = D_8002013C;
    right_data[1] = D_80020140;
    initial_data = D_80020144;

    tw_sd_sq_ld_call(0x24, 0x200);
    func_80026CE4(0x5A);
    func_8003E188(0x3C, (s32)parent_state);

    object = func_8003FC64(2);
    if (object != NULL) {
        parent_state = (u8 *)object + 0x20;
        ((S_800254A4_0 *)object)->unk_10 = D_80025BC8;
        ((S_800254A4_1 *)parent_state)->unk_18 = rand() & 1;
    }

    index = 2;
    child_callback = D_8002582C;
    child_data = D_80020148;
    child_slot = (void **)(parent_state + 8);
create_child:
    object = func_8003FC64(0x136);
    *child_slot = object;
    if (object != NULL) {
        ((S_800254A4_0 *)object)->unk_10 = child_callback;
        func_8004491C(object, D_80045340);
        child_state = (u8 *)object + 0x20;
        draw_state = ((S_800254A4_0 *)object)->unk_0C;
        packet = ((S_800254A4_0 *)object)->unk_08;
        packet->unk_00 = 0x05600000;
        packet->unk_04 = (index << 0x16) + 0x03E00000;
        packet->unk_08 = 0x00800000;
        packet->unk_14 = 0xFFFC0000;
        ((S_800254A4_0 *)object)->unk_20 = parent_state;
        child_state->unk_56 = index;
        draw_state->unk_1E = 0x1000;
        draw_state->unk_1C = 0x1000;
        func_8003DB94(draw_state, D_800F7968, 0, packet);
        draw_state->unk_0C = 0x00808080;
        child_state->unk_4C = child_data;
        func_8008F074((u8 *)object + 0x24, ((S_800254A4_0 *)object)->unk_08, D_80026F50);
    }
    index--;
    child_slot--;
    if (index >= 0) {
        goto create_child;
    }

    index = 1;
    callback = D_80026B78;
    row_y = 0x2C;
    do {
        object = func_8003FD64(1, D_80083498);
        left_state = (u8 *)object + 0x20;
        if (object != NULL) {
            ((S_800254A4_0 *)object)->unk_10 = callback;
            func_8004491C(object, D_80053858);
            left_state->unk_14 = 0x20;
            left_state->unk_18 = 3;
            left_state->unk_1A = 0x7C80;
            left_state->unk_16 = row_y;
            left_state->unk_10 = 0x00808080;
            row_data = left_data[index];
            left_state->unk_0C = parent_state;
            left_state->unk_04 = row_data;
        }
        index--;
        row_y -= 0xC;
    } while (index >= 0);

    index = 1;
    do {
        src_byte = initial_data + index;
        first_dst_byte = (u8 *)right_data[0] + index;
        second_dst_byte = (u8 *)right_data[1] + index;
        initial_byte = *src_byte;
        index--;
        do {
            *second_dst_byte = initial_byte;
            *first_dst_byte = initial_byte;
        } while (0);
    } while (index >= 0);

    index = 1;
    callback = D_80026BC4;
    row_y = 0x2C;
    do {
        object = func_8003FD64(1, D_80083498);
        right_state = (u8 *)object + 0x20;
        if (object != NULL) {
            ((S_800254A4_0 *)object)->unk_10 = callback;
            func_8004491C(object, D_80053858);
            right_state->unk_14 = 0x50;
            right_state->unk_18 = 3;
            right_state->unk_1A = 0x7C80;
            right_state->unk_16 = row_y;
            right_state->unk_10 = 0x00808080;
            right_state->unk_04 = right_data[index];
            if (index != 0) {
                if (index == 1) {
                    goto link_second_value;
                }
                right_state->unk_0C = parent_state;
                goto next_right_row;
            } else {
                value_ptr = parent_state + 0x12;
                goto store_value_ptr;
            }
link_second_value:
            value_ptr = parent_state + 0x14;
store_value_ptr:
            right_state->unk_08 = value_ptr;
            right_state->unk_0C = parent_state;
        }
next_right_row:
        index--;
        row_y -= 0xC;
    } while (index >= 0);

    object = func_8003FD64(1, D_80083498);
    if (object != NULL) {
        ((S_800254A4_0 *)object)->unk_10 = D_80026C54;
        func_8004491C(object, &D_80053A88);
        final_color = 0x00404040;
        final_state = (u8 *)object + 0x20;
        ASM_KEEP(final_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        final_extent = 0x1C;
        final_state->unk_0C = final_extent;
        final_state->unk_0E = final_extent;
        final_state->unk_12 = final_extent;
        final_state->unk_16 |= 1;
        final_state->unk_10 = 0x48;
        final_state->unk_14 = 2;
        final_state->unk_08 = final_color;
        final_state->unk_04 = parent_state;
    }

    return 0;
}

/* MECHANISM: Sibling pointer arrays force the 0x48 frame; split first-loop callback
   liveness yields the retail s7/s6/s4 held-base roles. A prefix scheduling fence
   plus short-lived copy/link/final pins reproduce the call and join lifetimes.
   Volatile final stores retain the retail store-before-RMW emission order. */
