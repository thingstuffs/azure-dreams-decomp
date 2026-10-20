#include "modules/dungeon_resource06_slot0.h"

void advance_actor_action_and_update_status(
    void *source,
    s16 value_34,
    s32 value_28,
    s16 value_52,
    s16 x_offset,
    s16 y_offset,
    s16 z_offset)
{
    R06_80174214_S_80174214_1 *source_obj = source;
    s16 saved_value_34 = value_34;
    u32 saved_value_28 = value_28;
    s16 saved_value_52 = value_52;
    R06_80174214_S_80174214_0 *object_fields;
    R06_80174214_S_80174214_0 *fields;
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
    R06_80174214_S_80174214_2 *x_dest;
    R06_80174214_S_80174214_3 *y_dest;
    R06_80174214_S_80174214_5 *z_dest;

    object_fields = allocate_list_node(0x211, source_obj);
    if (object_fields != NULL) {
        object_fields->unk_10 = (s32)((u8 *)advance_randomized_motion_and_complete);
        x_jitter = rand() & 0x1F;
        x_pos = ((R06_80174214_S_80174214_6 *)(source_obj->unk_08))->unk_02;
        x_dest = object_fields->unk_08.s;
        x_pos += x_jitter;
        x_bias = x_offset - 0x10;
        x_pos += x_bias;
        x_dest->unk_02 = (s16)x_pos;

        y_jitter = rand() & 0x1F;
        y_pos = ((R06_80174214_S_80174214_6 *)(source_obj->unk_08))->unk_06;
        y_dest = object_fields->unk_08.s;
        y_pos += y_jitter;
        y_bias = y_offset - 0x10;
        y_pos += y_bias;
        y_dest->unk_06 = (s16)y_pos;

        z_jitter = rand();
        init_data = ((void *)append_linked_shaded_point_packets);
        z_pos = ((R06_80174214_S_80174214_6 *)(source_obj->unk_08))->unk_0A;
        z_jitter &= 0x1F;
        fields = (R06_80174214_S_80174214_0 *)((u8 *)object_fields + 0x20);
        z_dest = ((R06_80174214_S_80174214_4 *)object_fields)->unk_08;
        z_pos += z_jitter;
        z_bias = z_offset - 0x10;
        z_pos += z_bias;
        z_dest->unk_0A = (s16)z_pos;
        fields->unk_14 = saved_value_34;
        fields->unk_32 = saved_value_52;
        register_node(object_fields, init_data);
        fields->unk_08.u = saved_value_28;
    }
}

/* MECHANISM: a splitting cell (2.8.0-G0) emits ((u8 *)advance_randomized_motion_and_complete) / ((u8 *)append_linked_shaded_point_packets) as HIGH/LO pairs itself (the lui in the beqz delay slot).
   The s16 stack offsets stay in s2-s4 from the prologue, and fields is the 0x20-advanced record. */
