#include "common.h"

extern void func_80022C48(s32 record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20);
extern void func_800226E0(s32 entity, s32 primary_data, s32 secondary_data);
extern void func_80022AE8(s32 record);

/* Sets record fields, processes its embedded data, and updates the record. */
void func_80022C90(s32 record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20) {
    func_80022C48(record, value_14, entry_index, value_0c, value_20);
    func_800226E0(record + 0x8BC, record + 0x894, record + 0x8A4);
    func_80022AE8(record);
}
