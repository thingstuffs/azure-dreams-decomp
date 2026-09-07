#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80174214_0 {
    u8 pad_00[0x8];
    union { void * s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_80174214_0;   /* temp_s0 in func_80174214 */

typedef struct S_80174214_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174214_1;   /* held_arg0 in func_80174214 */

typedef struct S_80174214_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80174214_2;   /* dest1 in func_80174214 */

typedef struct S_80174214_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80174214_3;   /* dest2 in func_80174214 */

typedef struct S_80174214_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174214_4;   /* call_obj in func_80174214 */

typedef struct S_80174214_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80174214_5;   /* dest3 in func_80174214 */

typedef struct S_80174214_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174214_6;   /* ((S_80174214_1 *)held_arg0)->unk_08 in func_80174214 */



extern void *func_8003FD64(s32, void *);
extern s32 rand(void);
extern void func_8004491C(void *, void *, void *);
extern u8 D_80173E94[];
extern u8 D_801740E4[];

/* Creates an object with randomized offsets from the source position and initializes its fields. */
void func_80174214(
    void *source,
    s16 value_34,
    s32 value_28,
    s16 value_52,
    s32 x_offset,
    s32 y_offset,
    s32 z_offset)
{
    register s32 saved_x_offset ASM_REG("$18") = x_offset;   /* MATCH pin: retail schedule: same instructions, different order without it */
    S_80174214_1 *source_obj = source;
    register s16 saved_value_34 ASM_REG("$21") = value_34;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 saved_value_28 ASM_REG("$23") = value_28;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s16 saved_value_52 ASM_REG("$22") = value_52;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 saved_y_offset = y_offset;
    s32 saved_z_offset = z_offset;
    S_80174214_0 *object_fields;
    s32 x_jitter;
    s32 y_jitter;
    s32 z_jitter;
    s32 x_bias;
    s32 y_bias;
    s32 z_bias;
    s32 x_pos;
    s32 y_pos;
    s32 z_pos;
    u32 descriptor_page;
    register void *new_object ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    void *init_data;
    S_80174214_2 *x_dest;
    S_80174214_3 *y_dest;
    S_80174214_5 *z_dest;

    object_fields = func_8003FD64(0x211, source_obj);
    if (object_fields != NULL) {
        descriptor_page = 0x80170000;
        ASM_KEEP(descriptor_page);   /* MATCH pin: load-bearing for the whole function shape */
        object_fields->unk_10 = descriptor_page + 0x40E4;
        x_jitter = rand() & 0x1F;
        x_pos = ((S_80174214_6 *)(source_obj->unk_08))->unk_02;
        x_dest = object_fields->unk_08.s;
        x_pos += x_jitter;
        x_bias = saved_x_offset - 0x10;
        x_pos += x_bias;
        x_dest->unk_02 = (s16)x_pos;

        y_jitter = rand() & 0x1F;
        y_pos = ((S_80174214_6 *)(source_obj->unk_08))->unk_06;
        y_dest = object_fields->unk_08.s;
        y_pos += y_jitter;
        y_bias = saved_y_offset - 0x10;
        y_pos += y_bias;
        y_dest->unk_06 = (s16)y_pos;

        z_jitter = rand();
        new_object = object_fields;
        init_data = &D_80173E94;
        ASM_USE2(new_object, init_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        z_jitter &= 0x1F;
        z_pos = ((S_80174214_6 *)(source_obj->unk_08))->unk_0A;
        object_fields = (u8 *)new_object + 0x20;
        z_dest = ((S_80174214_4 *)new_object)->unk_08;
        z_pos += z_jitter;
        z_bias = saved_z_offset - 0x10;
        z_pos += z_bias;
        z_dest->unk_0A = (s16)z_pos;
        ASM_KEEP(saved_x_offset);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_KEEP(object_fields);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        object_fields->unk_14 = saved_value_34;
        ASM_KEEP(saved_value_34);   /* MATCH pin: retail schedule: same instructions, different order without it */
        object_fields->unk_32 = saved_value_52;
        func_8004491C(new_object, init_data, z_dest);
        ASM_KEEP(saved_value_52);   /* MATCH pin: retail schedule: same instructions, different order without it */
        object_fields->unk_08.u = saved_value_28;
        ASM_KEEP(saved_value_28);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
}

/* MECHANISM: The true-space definition and guarded s0-s7 role map reproduce the 0x38 frame.
   Separate random/value/destination/offset lifetimes plus the three-argument callee ABI align the body.
   A kept 0x80170000 page plus 0x40E4 exposes the branch-delay lui; the tail keep anchors s0 stores. */
