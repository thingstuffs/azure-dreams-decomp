#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s8 x;
    s8 y;
    s8 z;
} Vec3s;

M2C_UNK func_8004E5A0();      /* extern */
M2C_UNK *func_8004E634();             /* extern */
M2C_UNK strcat();           /* extern */
s32 func_800B555C();               /* extern */
extern M2C_UNK D_800892D8;
extern Vec3s D_800892F0;
extern M2C_UNK D_800892F4;
extern M2C_UNK D_800892F8;
extern M2C_UNK D_800892FC;
extern M2C_UNK D_80089304;

typedef struct S_800B557C_0 {
    u8 pad_00[0x26];
    u8 unk_26;
    u8 unk_27;
    u8 pad_28[0x40];
    u8 unk_68;
    u8 unk_69;
} S_800B557C_0;   /* arg1 in func_800B557C */

/* Formats two pairs of stat values with comparison indicators. */
void *func_800B557C(void *text, S_800B557C_0 *stats) {
    M2C_UNK format_buf[3];
    s32 first_indicator;
    s32 second_indicator;
    Vec3s *prefix;

    prefix = &D_800892F0;
    *(Vec3s *)text = *prefix;
    first_indicator = func_800B555C(stats->unk_68, stats->unk_26);
    if (first_indicator != 0) {
        strcat(text, &D_800892F4);
        strcat(text, func_8004E634(first_indicator, &format_buf));
    }
    strcat(text, &D_800892F8);
    func_8004E5A0(stats->unk_26, 3, &format_buf);
    strcat(text, &format_buf);
    strcat(text, &D_800892F4);
    strcat(text, func_8004E634(0, &format_buf));
    strcat(text, &D_800892FC);
    second_indicator = func_800B555C(stats->unk_69, stats->unk_27);
    if (second_indicator != 0) {
        strcat(text, &D_800892F4);
        strcat(text, func_8004E634(second_indicator, &format_buf));
    }
    func_8004E5A0(stats->unk_27, 3, &format_buf);
    strcat(text, &format_buf);
    strcat(text, &D_800892F4);
    strcat(text, func_8004E634(0, &format_buf));
    strcat(text, &D_800892D8);
    strcat(text, &D_80089304);
    func_8004E5A0(stats->unk_68, 3, &format_buf);
    strcat(text, &format_buf);
    strcat(text, &D_800892FC);
    func_8004E5A0(stats->unk_69, 3, &format_buf);
    strcat(text, &format_buf);
    return text;
}
