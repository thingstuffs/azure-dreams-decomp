#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct {
    s8 x;
    s8 y;
    s8 z;
} Vec3s;

char * func_8004E5A0(int, unsigned short, char *);      /* extern */
char * func_8004E634(u32, char *);             /* extern */
char *strcat();           /* extern */
s32 compare_values_to_display_code(s32, s32);               /* extern */
extern M2C_UNK D_800892D8;
extern Vec3s D_800892F0;
extern M2C_UNK D_800892F4;
extern M2C_UNK D_800892F8;
extern M2C_UNK D_800892FC;
extern M2C_UNK D_80089304;


/* Formats two pairs of stat values with comparison indicators. */
void *format_compared_stat_pairs(void *text, EntityRec *stats) {
    s32 format_buf[3];
    s32 first_indicator;
    s32 second_indicator;
    Vec3s *prefix;

    prefix = &D_800892F0;
    *(Vec3s *)text = *prefix;
    first_indicator = compare_values_to_display_code(stats->unk_68, stats->unk_26);
    if (first_indicator != 0) {
        strcat(text, &D_800892F4);
        strcat(text, func_8004E634(first_indicator, (char *)(&format_buf)));
    }
    strcat(text, &D_800892F8);
    func_8004E5A0(stats->unk_26, 3, (char *)(&format_buf));
    strcat(text, &format_buf);
    strcat(text, &D_800892F4);
    strcat(text, func_8004E634(0, (char *)(&format_buf)));
    strcat(text, &D_800892FC);
    second_indicator = compare_values_to_display_code(stats->unk_69, stats->unk_27);
    if (second_indicator != 0) {
        strcat(text, &D_800892F4);
        strcat(text, func_8004E634(second_indicator, (char *)(&format_buf)));
    }
    func_8004E5A0(stats->unk_27, 3, (char *)(&format_buf));
    strcat(text, &format_buf);
    strcat(text, &D_800892F4);
    strcat(text, func_8004E634(0, (char *)(&format_buf)));
    strcat(text, &D_800892D8);
    strcat(text, &D_80089304);
    func_8004E5A0(stats->unk_68, 3, (char *)(&format_buf));
    strcat(text, &format_buf);
    strcat(text, &D_800892FC);
    func_8004E5A0(stats->unk_69, 3, (char *)(&format_buf));
    strcat(text, &format_buf);
    return text;
}
