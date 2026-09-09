#include "common.h"

typedef struct S_8001A86C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_8001A86C_0;   /* out in func_8001A86C */


extern void func_8001A1A0(void *, void *);
extern void func_8001A200(void *, void *);
extern s32 func_8001E670(s32);

typedef struct {
    u8 pad0[4];
    s16 field4;
    u8 pad6[2];
    s32 field8;
} Record12;

extern Record12 D_8001791C[];
extern u8 D_80017ADC;
extern u8 D_80017AE8;
extern u8 D_80017AF4;
extern u8 D_80017B00;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017D50;


/* Sets entry flags from record state and selection, then prepares the output buffer. */
u8 *func_8001A86C(s32 selected_index) {
    s32 entry_index;
    s32 first_marked;
    s32 entry_flag;
    u8 *output_base;
    Record12 *record_base;
    Record12 *record;
    void *entry;

    first_marked = 0;
    output_base = &D_80017D50;
    if (selected_index != 0) {
        entry_index = 1;
        do {
            entry_flag = 0x400;
        } while (0);
        entry = output_base + 0x14;
        record_base = D_8001791C;
        record = &record_base[1];
loop:
        if (func_8001E670(record->field4) != 0) {
            if (record->field8 != 0) {
                ((S_8001A86C_0 *)entry)->unk_02 = entry_flag;
                if (entry_index == 1) {
                    first_marked = 1;
                }
                goto next;
            }
            if (selected_index == entry_index) {
                ((S_8001A86C_0 *)entry)->unk_02 = entry_flag;
            }
        }
next:
        entry += 0x14;
        entry_index++;
        record++;
        if (entry_index < 8) {
            goto loop;
        }
    }

    func_8001A200(output_base, &D_80017ADC);
    func_8001A1A0(output_base, &D_80017AE8);
    if (first_marked != 0) {
        *(s16 *)(output_base + 0xA2) = 0x400;
        func_8001A1A0(output_base + 0xA0, &D_80017B00);
    } else {
        *(s16 *)(output_base + 0xB6) = 0x400;
        func_8001A1A0(output_base + 0xB4, &D_80017B0C);
    }
    func_8001A1A0(output_base + 0xDC, &D_80017AF4);
    func_8001A1A0(output_base + 0xC8, &D_80017B18);
    return output_base;
}
