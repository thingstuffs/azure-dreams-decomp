#include "common.h"

extern void copy_callback_value_to_destination(void *, void *);
extern void dispatch_records_by_kind(void *, void *);

extern u8 D_80017ADC;
extern u8 D_80017AE8;
extern u8 D_80017AF4;
extern u8 D_80017B00;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017D50;

/* Builds the entry list and flags entries according to the selected index. */
void *build_entry_list(s32 entry_index) {
    u8 *entries = &D_80017D50;

    if (entry_index != 0) {
        *(s16 *)(entries + (entry_index * 0x14) + 2) = 0x400;
    }

    dispatch_records_by_kind(entries, &D_80017ADC);
    copy_callback_value_to_destination(entries, &D_80017AE8);

    if (entry_index == 1) {
        *(s16 *)(entries + 0xA2) = 0x400;
        copy_callback_value_to_destination(entries + 0xA0, &D_80017B00);
    } else {
        *(s16 *)(entries + 0xB6) = 0x400;
        copy_callback_value_to_destination(entries + 0xB4, &D_80017B0C);
    }

    copy_callback_value_to_destination(entries + 0xDC, &D_80017AF4);
    copy_callback_value_to_destination(entries + 0xC8, &D_80017B18);
    return entries;
}
