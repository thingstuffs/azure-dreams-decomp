#include "common.h"

extern void copy_callback_value_to_destination(void *, void *);
extern void dispatch_records_by_kind(void *, void *);
extern u8 D_8001791C[];
extern u8 D_80017AD0;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017E54[];

/* Initialize the shared buffer using the selected table entry and return it. */
void *build_selected_record_buffer(s32 entry_index) {
    u8 *buffer = D_80017E54;

    *(s32 *)(buffer + 0xC) = *(s32 *)(D_8001791C + (entry_index * 0xC));
    dispatch_records_by_kind(buffer, &D_80017AD0);
    copy_callback_value_to_destination(buffer + 0x14, &D_80017B0C);
    copy_callback_value_to_destination(buffer + 0x28, &D_80017B18);
    return buffer;
}
