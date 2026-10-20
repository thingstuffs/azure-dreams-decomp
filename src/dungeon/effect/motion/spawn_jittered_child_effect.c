#include "dungeon/effect/motion/spawn_jittered_child_effect.h"


void spawn_jittered_child_effect(
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
    Row_818FECCC_S_818FECCC_0 *fields;
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
    Row_818FECCC_S_818FECCC_2 *dest_x;
    Row_818FECCC_S_818FECCC_3 *dest_y;
    Row_818FECCC_S_818FECCC_5 *dest_z;

    object_cursor = allocate_list_node(0x211, source_obj);
    if (object_cursor != NULL) {
        ((Row_818FECCC_S_818FECCC_0 *)object_cursor)->unk_10 = (s32)D_80024400;
        jitter_x = func_80069EF8() & 0x1F;
        position_x = ((Row_818FECCC_S_818FECCC_6 *)(((Row_818FECCC_S_818FECCC_1 *)source_obj)->unk_08))->unk_02;
        dest_x = ((Row_818FECCC_S_818FECCC_0 *)object_cursor)->unk_08.s;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->unk_02 = (s16)position_x;

        jitter_y = func_80069EF8() & 0x1F;
        position_y = ((Row_818FECCC_S_818FECCC_6 *)(((Row_818FECCC_S_818FECCC_1 *)source_obj)->unk_08))->unk_06;
        dest_y = ((Row_818FECCC_S_818FECCC_0 *)object_cursor)->unk_08.s;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->unk_06 = (s16)position_y;

        jitter_z = func_80069EF8();
        init_data = &D_800241B0;
        jitter_z &= 0x1F;
        position_z = ((Row_818FECCC_S_818FECCC_6 *)(((Row_818FECCC_S_818FECCC_1 *)source_obj)->unk_08))->unk_0A;
        fields = (Row_818FECCC_S_818FECCC_0 *)((u8 *)object_cursor + 0x20);
        dest_z = ((Row_818FECCC_S_818FECCC_4 *)object_cursor)->unk_08;
        position_z += jitter_z;
        bias_z = offset_z + 0x10;
        position_z += bias_z;
        dest_z->unk_0A = (s16)position_z;
        fields->unk_14 = field_34;
        fields->unk_32 = saved_field_52;
        register_node(object_cursor, init_data);
        fields->unk_08.u = saved_field_28;
    }
}
