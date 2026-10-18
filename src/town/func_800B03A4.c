#include "common.h"
#include "records/Rec_func_800AD7F8_arg0.h"

int func_80049490(void *object);

/* Pass the record's base plus its index scaled by four to func_80049490. */
void pass_indexed_record_to_loader(Rec_func_800AD7F8_arg0 *record) {
    func_80049490(record->unk_20 + (record->unk_04 * 4));
}
