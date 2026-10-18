#include "common.h"

typedef struct S_80099A1C_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0xB2];
    u16 unk_B8;
    u8 pad_BA[0x6];
    s32 unk_C0;
} S_80099A1C_0;   /* scratch in apply_scratch_parameters_to_chain */

typedef struct S_80099A1C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80099A1C_1;   /* arg1 in apply_scratch_parameters_to_chain */

typedef struct S_80099A1C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80099A1C_2;   /* arg2 in apply_scratch_parameters_to_chain */

typedef struct S_80099A1C_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80099A1C_3_pre;   /* the 0x8 bytes before arg0 in apply_scratch_parameters_to_chain, addressed as arg0[-1] */

typedef struct S_80099A1C_3 {
    u16 unk_00;
    u8 pad_02[0x6];
    s32 unk_08;
    s16 unk_0C;
} S_80099A1C_3;   /* arg0 in apply_scratch_parameters_to_chain */

typedef struct S_80099A1C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80099A1C_4;   /* next in apply_scratch_parameters_to_chain */


extern s32 func_800644B8(s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern void queue_visible_rectangle_copy(void *, void *);

/* Build scratch parameters and apply them to each object in a linked chain. */
s32 apply_scratch_parameters_to_chain(void *object, S_80099A1C_1 *position, S_80099A1C_2 *offset_data)
{
    u8 *scratch;
    void *next_node;
    s32 transform_result;

    scratch = (u8 *)0x1F800000;

    do {
        ((S_80099A1C_0 *)scratch)->unk_00 = position->unk_02;
        ((S_80099A1C_0 *)scratch)->unk_02 = position->unk_06;
        ((S_80099A1C_0 *)scratch)->unk_04 = position->unk_0A;

        transform_result = func_80065420(
            scratch,
            scratch + 0xB8,
            scratch + 0x90,
            scratch + 0x94);
        ((S_80099A1C_0 *)scratch)->unk_C0 = transform_result - offset_data->unk_06;

        {
            s32 half_offset;
            u32 adjusted_coord;

            half_offset = ((S_80099A1C_3 *)object)->unk_00;
            adjusted_coord = ((S_80099A1C_0 *)scratch)->unk_B8;
            half_offset = (half_offset << 16) >> 17;
            adjusted_coord -= half_offset;
            ((S_80099A1C_0 *)scratch)->unk_B8 = adjusted_coord;
        }
        ((S_80099A1C_0 *)scratch)->unk_B8 +=
            (func_800644B8(
                (((S_80099A1C_3 *)object)->unk_0C << 8) +
                (((S_80099A1C_3 *)object)->unk_08 << 7)) *
             (((S_80099A1C_3 *)object)->unk_08 >> 2)) >> 9;

        queue_visible_rectangle_copy(object, scratch);

        next_node = ((S_80099A1C_3_pre *)object)[-1].unk_00;
        object = (u8 *)next_node + 0x20;
        if (next_node == 0) {
            break;
        }
        position = ((S_80099A1C_4 *)next_node)->unk_08;
        offset_data = ((S_80099A1C_4 *)next_node)->unk_0C;
    } while (1);
    return 0;
}
