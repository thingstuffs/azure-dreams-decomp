#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B3FB8_arg0.h"

M2C_UNK func_8004E6F4(); /* extern */
M2C_UNK func_800B3FB8();      /* extern */
M2C_UNK func_800B40E0();                         /* extern */
M2C_UNK func_800B4188();                         /* extern */
M2C_UNK func_800B426C();                         /* extern */
M2C_UNK func_800B4350();                      /* extern */
extern M2C_UNK D_800D1658;
extern M2C_UNK D_800D175C;


/* Processes three data blocks and five table entries for the object. */
void func_800B43E8(Rec_func_800B3FB8_arg0 *object) {
    s8 *entry_data;
    s32 entry_index;

    entry_index = 0;
    func_800B40E0(object->unk_20);
    func_800B4188(object->unk_20 + 0x48);
    func_800B426C(object->unk_20 + 0x90);
    func_8004E6F4(0x10, &D_800D175C, &D_800D175C, &D_800D175C, 0, 0xA);
    entry_data = &D_800D1658;
    do {
        func_800B3FB8(object, entry_data, entry_index);
        entry_index += 1;
        entry_data += 0x14;
    } while (entry_index < 5);
    func_800B4350(object);
}
