#include "common.h"
#include "main/data.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 index;
} Struct8001B74C_arg0;

extern s32 D_80408B2C[][4];

extern void locate_utf16_word_and_report_length(s32 value, s32 value_2, s32 *out_a, s32 *out_b, s32 *out_c);
extern void position_object_record_and_update_row(void *object, s32 value, s32 value_2, s32 index, s32 value_3);

/* Resolve and apply the last table entry when the object's table is enabled. */
void layout_last_row_item(Struct8001B74C_arg0 *object) {
    s32 resolved_a;
    s32 resolved_b;
    s32 resolved_c;
    s32 table_index = object->index;
    s32 last_index = D_80408ADD[table_index][0] - 1;

    if (D_80408ADD[table_index][1] != 0) {
        locate_utf16_word_and_report_length(D_80408B2C[table_index][last_index], object->unk0, &resolved_a, &resolved_b, &resolved_c);
        position_object_record_and_update_row(object, resolved_a, resolved_b, last_index, resolved_c);
    }
}
