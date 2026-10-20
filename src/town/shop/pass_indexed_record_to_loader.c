#include "common.h"
#include "records/Rec_func_800AD7F8_arg0.h"

int get_item_name_with_shared_text_table(void *object);

/* Pass the record's base plus its index scaled by four to func_80049490. */
void pass_indexed_record_to_loader(Rec_func_800AD7F8_arg0 *record) {
    get_item_name_with_shared_text_table(record->unk_20 + (record->unk_04 * 4));
}
