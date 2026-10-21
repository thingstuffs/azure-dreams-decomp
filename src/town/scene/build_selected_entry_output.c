#include "common.h"

typedef struct S_8001A86C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_8001A86C_0;   /* out in build_selected_entry_output */


extern void copy_callback_value_to_destination(void *, void *);
extern void dispatch_records_by_kind(void *, void *);
extern s32 func_8001E670(s32);

typedef struct {
    u8 pad0[4];
    s16 field4;
    u8 pad6[2];
    s32 field8;
} Record12;

extern Record12 town_selection_records[];
extern u8 D_80017ADC;
extern u8 D_80017AE8;
extern u8 D_80017AF4;
extern u8 D_80017B00;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017D50;


/* Sets entry flags from record state and selection, then prepares the output buffer. */
u8 *build_selected_entry_output(s32 selected_index) {
    s32 entry_index;
    s32 first_marked;
    u8 *output_base;
    Record12 *record;
    void *entry;

    first_marked = 0;
    output_base = &D_80017D50;
    if (selected_index != 0) {
        for (entry_index = 1; entry_index < 8; entry_index++) {
            record = &town_selection_records[entry_index];
            entry = output_base + entry_index * 0x14;
            if (func_8001E670(record->field4) != 0) {
                if (record->field8 != 0) {
                    ((S_8001A86C_0 *)entry)->unk_02 = 0x400;
                    if (entry_index == 1) {
                        first_marked = 1;
                    }
                } else if (selected_index == entry_index) {
                    ((S_8001A86C_0 *)entry)->unk_02 = 0x400;
                }
            }
        }

    }

    dispatch_records_by_kind(output_base, &D_80017ADC);
    copy_callback_value_to_destination(output_base, &D_80017AE8);
    if (first_marked != 0) {
        *(s16 *)(output_base + 0xA2) = 0x400;
        copy_callback_value_to_destination(output_base + 0xA0, &D_80017B00);
    } else {
        *(s16 *)(output_base + 0xB6) = 0x400;
        copy_callback_value_to_destination(output_base + 0xB4, &D_80017B0C);
    }
    copy_callback_value_to_destination(output_base + 0xDC, &D_80017AF4);
    copy_callback_value_to_destination(output_base + 0xC8, &D_80017B18);
    return output_base;
}
