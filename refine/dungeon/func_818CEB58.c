#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_818CEB58_0 {
    u8 pad_00[0x8];
    union { void * s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_818CEB58_0;   /* temp_s0 in func_818CEB58 */

typedef struct S_818CEB58_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_818CEB58_1;   /* held_arg0 in func_818CEB58 */

typedef struct S_818CEB58_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_818CEB58_2;   /* dest1 in func_818CEB58 */

typedef struct S_818CEB58_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_818CEB58_3;   /* dest2 in func_818CEB58 */

typedef struct S_818CEB58_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_818CEB58_4;   /* call_obj in func_818CEB58 */

typedef struct S_818CEB58_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_818CEB58_5;   /* dest3 in func_818CEB58 */

typedef struct S_818CEB58_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818CEB58_6;   /* ((S_818CEB58_1 *)held_arg0)->unk_08 in func_818CEB58 */



extern void *func_8003FD64(s32, void *);
extern s32 rand(void);
extern void func_8004491C(void *, void *, void *);
extern u8 D_8002403C[];
extern u8 D_8002428C[];

/* Creates an object at a randomized offset from the source and initializes its fields. */
void func_818CEB58(
    void *source,
    s16 field_34,
    s32 field_28,
    s16 field_52,
    s32 offset_x,
    s32 offset_y,
    s32 offset_z)
{
    register s32 saved_offset_x ASM_REG("$18") = offset_x;   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *source_obj = source;
    register s16 saved_field_34 ASM_REG("$21") = field_34;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 saved_field_28 ASM_REG("$23") = field_28;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s16 saved_field_52 ASM_REG("$22") = field_52;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 saved_offset_y = offset_y;
    s32 saved_offset_z = offset_z;
    void *object_cursor;
    s32 jitter_x;
    s32 jitter_y;
    s32 jitter_z;
    s32 bias_x;
    s32 bias_y;
    s32 bias_z;
    s32 position_x;
    s32 position_y;
    s32 position_z;
    u32 descriptor_page;
    register void *new_object ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    void *init_data;
    S_818CEB58_2 *dest_x;
    S_818CEB58_3 *dest_y;
    S_818CEB58_5 *dest_z;

    object_cursor = func_8003FD64(0x211, source_obj);
    if (object_cursor != NULL) {
        descriptor_page = 0x80020000;
        ASM_KEEP(descriptor_page);   /* MATCH pin: load-bearing for the whole function shape */
        ((S_818CEB58_0 *)object_cursor)->unk_10 = descriptor_page + 0x428C;
        jitter_x = rand() & 0x1F;
        position_x = ((S_818CEB58_6 *)(((S_818CEB58_1 *)source_obj)->unk_08))->unk_02;
        dest_x = ((S_818CEB58_0 *)object_cursor)->unk_08.s;
        position_x += jitter_x;
        bias_x = saved_offset_x - 0x10;
        position_x += bias_x;
        dest_x->unk_02 = (s16)position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((S_818CEB58_6 *)(((S_818CEB58_1 *)source_obj)->unk_08))->unk_06;
        dest_y = ((S_818CEB58_0 *)object_cursor)->unk_08.s;
        position_y += jitter_y;
        bias_y = saved_offset_y - 0x10;
        position_y += bias_y;
        dest_y->unk_06 = (s16)position_y;

        jitter_z = rand();
        new_object = object_cursor;
        init_data = &D_8002403C;
        ASM_USE2(new_object, init_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        jitter_z &= 0x1F;
        position_z = ((S_818CEB58_6 *)(((S_818CEB58_1 *)source_obj)->unk_08))->unk_0A;
        object_cursor = (u8 *)new_object + 0x20;
        dest_z = ((S_818CEB58_4 *)new_object)->unk_08;
        position_z += jitter_z;
        bias_z = saved_offset_z - 0x10;
        position_z += bias_z;
        dest_z->unk_0A = (s16)position_z;
        ASM_KEEP(saved_offset_x);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_KEEP(object_cursor);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ((S_818CEB58_0 *)object_cursor)->unk_14 = saved_field_34;
        ASM_KEEP(saved_field_34);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_818CEB58_0 *)object_cursor)->unk_32 = saved_field_52;
        func_8004491C(new_object, init_data, dest_z);
        ASM_KEEP(saved_field_52);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_818CEB58_0 *)object_cursor)->unk_08.u = saved_field_28;
        ASM_KEEP(saved_field_28);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
}

/* MECHANISM: The true-space definition and guarded s0-s7 role map reproduce the 0x38 frame.
   Separate random/value/destination/offset lifetimes plus the three-argument callee ABI align the body.
   A kept 0x80020000 page plus 0x40E4 exposes the branch-delay lui; the tail keep anchors s0 stores. */
