#include "modules/dungeon_ovl_18ee800.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif



   /* held_arg0 in func_80024358 */

   /* dest1 in func_80024358 */

   /* dest2 in func_80024358 */

   /* call_obj in func_80024358 */

   /* dest3 in func_80024358 */

   /* ((B32_818CEB58_S_818CEB58_1 *)held_arg0)->unk_08 in func_80024358 */



extern s32 rand(void);

/* Creates an object at a randomized offset from the source and initializes its fields. */
void func_80024358(
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
    B32_818CEB58_S_818CEB58_0 *fields;
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
    B32_818CEB58_S_818CEB58_2 *dest_x;
    B32_818CEB58_S_818CEB58_3 *dest_y;
    B32_818CEB58_S_818CEB58_5 *dest_z;

    object_cursor = func_8003FD64(0x211, source_obj);
    if (object_cursor != NULL) {
        ((B32_818CEB58_S_818CEB58_0 *)object_cursor)->unk_10 = (s32)func_8002428C;
        jitter_x = rand() & 0x1F;
        position_x = ((B32_818CEB58_S_818CEB58_6 *)(((B32_818CEB58_S_818CEB58_1 *)source_obj)->unk_08))->unk_02;
        dest_x = ((B32_818CEB58_S_818CEB58_0 *)object_cursor)->unk_08.s;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->unk_02 = (s16)position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((B32_818CEB58_S_818CEB58_6 *)(((B32_818CEB58_S_818CEB58_1 *)source_obj)->unk_08))->unk_06;
        dest_y = ((B32_818CEB58_S_818CEB58_0 *)object_cursor)->unk_08.s;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->unk_06 = (s16)position_y;

        jitter_z = rand();
        init_data = func_8002403C;
        jitter_z &= 0x1F;
        position_z = ((B32_818CEB58_S_818CEB58_6 *)(((B32_818CEB58_S_818CEB58_1 *)source_obj)->unk_08))->unk_0A;
        fields = (B32_818CEB58_S_818CEB58_0 *)((u8 *)object_cursor + 0x20);
        dest_z = ((B32_818CEB58_S_818CEB58_4 *)object_cursor)->unk_08;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->unk_0A = (s16)position_z;
        fields->unk_14 = field_34;
        fields->unk_32 = saved_field_52;
        func_8004491C(object_cursor, init_data);
        fields->unk_08.u = saved_field_28;
    }
}

/* MECHANISM: 2.7.2-cdk-G0 splits func_8002428C / func_8002403C itself (the lui in the beqz delay slot).
   The s16 stack offsets stay in s2-s4 from the prologue, and fields is the 0x20-advanced record. */
