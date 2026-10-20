#include "common.h"
void func_80017E84(s32, void *);                 /* extern */

typedef struct S_8065C9D0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8065C9D0_0;   /* arg0 in forward_indexed_record_to_handler */

typedef struct S_8065C9D0_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_8065C9D0_1;

/* Pass the indexed record and its identifier to the shared handler. */
void forward_indexed_record_to_handler(S_8065C9D0_0 *record_table, s32 record_index) {
    S_8065C9D0_1 *record;

    record = (record_index * 0x10) + record_table->unk_10;
    func_80017E84(record->unk_0C, record);
}
