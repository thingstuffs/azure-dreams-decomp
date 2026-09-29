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
    s16 x_offset,
    s16 y_offset,
    s16 z_offset)
{
    S_80174214_1 *source_obj = source;
    s16 saved_value_34 = value_34;
    u32 saved_value_28 = value_28;
    s16 saved_value_52 = value_52;
    S_80174214_0 *object_fields;
    S_80174214_0 *fields;
    s32 x_jitter;
    s32 y_jitter;
    s32 z_jitter;
    s16 x_bias;
    s16 y_bias;
    s16 z_bias;
    s16 x_pos;
    s16 y_pos;
    s16 z_pos;
    void *init_data;
    S_80174214_2 *x_dest;
    S_80174214_3 *y_dest;
    S_80174214_5 *z_dest;

    object_fields = func_8003FD64(0x211, source_obj);
    if (object_fields != NULL) {
        object_fields->unk_10 = (s32)D_801740E4;
        x_jitter = rand() & 0x1F;
        x_pos = ((S_80174214_6 *)(source_obj->unk_08))->unk_02;
        x_dest = object_fields->unk_08.s;
        x_pos += x_jitter;
        x_bias = x_offset - 0x10;
        x_pos += x_bias;
        x_dest->unk_02 = (s16)x_pos;

        y_jitter = rand() & 0x1F;
        y_pos = ((S_80174214_6 *)(source_obj->unk_08))->unk_06;
        y_dest = object_fields->unk_08.s;
        y_pos += y_jitter;
        y_bias = y_offset - 0x10;
        y_pos += y_bias;
        y_dest->unk_06 = (s16)y_pos;

        z_jitter = rand();
        init_data = &D_80173E94;
        z_pos = ((S_80174214_6 *)(source_obj->unk_08))->unk_0A;
        z_jitter &= 0x1F;
        fields = (S_80174214_0 *)((u8 *)object_fields + 0x20);
        z_dest = ((S_80174214_4 *)object_fields)->unk_08;
        z_pos += z_jitter;
        z_bias = z_offset - 0x10;
        z_pos += z_bias;
        z_dest->unk_0A = (s16)z_pos;
        fields->unk_14 = saved_value_34;
        fields->unk_32 = saved_value_52;
        func_8004491C(object_fields, init_data, z_dest);
        fields->unk_08.u = saved_value_28;
    }
}

/* MECHANISM: a splitting cell (2.8.0-G0) emits D_801740E4 / D_80173E94 as HIGH/LO pairs itself (the lui in the beqz delay slot).
   The s16 stack offsets stay in s2-s4 from the prologue, and fields is the 0x20-advanced record. */
