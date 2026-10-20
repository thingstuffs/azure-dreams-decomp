#include "common.h"

extern void clear_entity_record_fields(s32 record);
extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern u8 D_800D0078[];
extern void *D_80097DE8[];
extern s8 D_80082669[16];

typedef struct {
    s32 unk0;
    void **unk4;
} Struct8009B1C8;

/* Initialize the record, assign its handler table, and clear the first flag. */
void initialize_record_with_handler_table(Struct8009B1C8 *record, s32 setup_value, s32 init_value) {
    clear_entity_record_fields(setup_value);
    call_the_handler_selects_nonzero_entry(D_800D0078, record, init_value);
    record->unk4 = D_80097DE8;
    D_80082669[0] = 0;
}
