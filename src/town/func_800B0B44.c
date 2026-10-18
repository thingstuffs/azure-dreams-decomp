#include "common.h"
#include "shared/object_flags.h"

typedef struct FuncArg {
    u8 pad0[4];
    s32 field4;
    u8 pad8[0x20];
    s32 field28;
    s32 field2C;
} FuncArg;

extern void initialize_state_from_source(void *source);
extern void set_shop_object_data_if_present(s32 object);
extern void set_object_data_pointer_2(s32 object);
extern s32 D_80082AB4[];

// Set the record and global flags, apply the stored values, and process the record.
void process_record_and_apply_flags(FuncArg *record) {
    s32 firstUpdateValue;
    *(u16 *)((u8 *)record - 2) |= 0x8000;
    firstUpdateValue = record->field28;
    object_flag_block.flags |= 0x8000;
    set_shop_object_data_if_present(firstUpdateValue);
    set_object_data_pointer_2(record->field2C);
    D_80082AB4[0] = record->field4;
    initialize_state_from_source(record);
}
