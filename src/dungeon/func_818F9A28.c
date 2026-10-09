#include "common.h"
#include "modules/dungeon_native_abi.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80025228_0 {
    u8 pad_00[0x8];
    union { void * s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_80025228_0;   /* temp_s0 in func_80025228 */

typedef struct S_80025228_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80025228_1;   /* held_arg0 in func_80025228 */

typedef struct S_80025228_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80025228_2;   /* dest1 in func_80025228 */

typedef struct S_80025228_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80025228_3;   /* dest2 in func_80025228 */

typedef struct S_80025228_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80025228_4;   /* call_obj in func_80025228 */

typedef struct S_80025228_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80025228_5;   /* dest3 in func_80025228 */

typedef struct S_80025228_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025228_6;   /* ((S_80025228_1 *)held_arg0)->unk_08 in func_80025228 */



extern s32 rand(void);
extern s32 func_80024EDC(void *, void *);
extern void func_8002515C();

/* Creates an object at a randomized offset from the source and initializes its fields. */
void func_80025228(
    void *source,
    s16 field_34,
    s32 field_28,
    s16 field_52,
    s16 offset_x,
    s16 offset_y,
    s16 offset_z)
{
    void *source_obj = source;
    u32 saved_field_28 = field_28;
    s16 saved_field_52 = field_52;
    void *object_cursor;
    S_80025228_0 *fields;
    s32 jitter_x;
    s32 jitter_y;
    s32 jitter_z;
    s16 bias_x;
    s16 bias_y;
    s16 bias_z;
    s16 position_x;
    s16 position_y;
    s16 position_z;
    void *init_data;
    S_80025228_2 *dest_x;
    S_80025228_3 *dest_y;
    S_80025228_5 *dest_z;

    object_cursor = func_8003FD64(0x211, (ObjectNodeHeader **)source_obj);
    if (object_cursor != NULL) {
        ((S_80025228_0 *)object_cursor)->unk_10 = (s32)func_8002515C;
        jitter_x = rand() & 0x1F;
        position_x = ((S_80025228_6 *)(((S_80025228_1 *)source_obj)->unk_08))->unk_02;
        dest_x = ((S_80025228_0 *)object_cursor)->unk_08.s;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->unk_02 = (s16)position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((S_80025228_6 *)(((S_80025228_1 *)source_obj)->unk_08))->unk_06;
        dest_y = ((S_80025228_0 *)object_cursor)->unk_08.s;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->unk_06 = (s16)position_y;

        jitter_z = rand();
        init_data = func_80024EDC;
        jitter_z &= 0x1F;
        position_z = ((S_80025228_6 *)(((S_80025228_1 *)source_obj)->unk_08))->unk_0A;
        fields = (S_80025228_0 *)((u8 *)object_cursor + 0x20);
        dest_z = ((S_80025228_4 *)object_cursor)->unk_08;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->unk_0A = (s16)position_z;
        fields->unk_14 = field_34;
        fields->unk_32 = saved_field_52;
        func_8004491C(object_cursor, (s32)init_data);
        fields->unk_08.u = saved_field_28;
    }
}

