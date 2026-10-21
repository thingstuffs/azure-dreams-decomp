/* Dialog packet setup; G00380; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_8000F90C, CL:main/func_8000F934, CL:main/func_8000FA30. */
#include "frontend/libcard/dialog_packet_setup_g00380.h"

/* Initializes four pairs of records from the value table and returns the buffer end. */
void *card_boot_build_paired_dialog_packets(void *buffer, s32 unused)
{
    Bytes4 values;
    s32 value_index;
    s32 first_x;
    s32 first_y;
    s32 kind;
    u32 address;
    s32 second_x;
    s32 second_y;
    u8 *record;
    Fields *fields;
    Fields *fields2;
    u8 *value;

    record = buffer;
    values = *(Bytes4 *)D_800200A0;
    value_index = 0;
    first_x = 5;
    first_y = first_x;
    kind = 0x48;
    address = 0x104058;
    second_x = 6;
    second_y = second_x;
    do {
        fields = (Fields *)(record + 4);
        fields->x = first_x;
        fields->y = first_y;
        ((u8 *)fields)[-3] = kind;
        fields->address = address;
        value = &values.bytes[value_index];
        record[0] = *value;
        record += 12;
        fields2 = (Fields *)(record + 4);
        fields2->x = second_x;
        fields2->y = second_y;
        ((u8 *)fields2)[-3] = kind;
        fields2->address = address;
        record[0] = *value;
        record += 12;
        value_index++;
    } while (value_index < 4);
    record[-24] |= 0x80;
    return record;
}

/* Processes the embedded data and then updates the record. */
void card_boot_initialize_dialog_packets_and_display(s32 record) {
    card_boot_build_paired_dialog_packets((void *)(record + 0x24), record);
    card_boot_center_message_dialog_display((void *)(record));
}
