#include "modules/main_server_ship.h"
#include "common.h"

extern void rename(void *old_name, void *new_name);



/* Updates slot data using a temporary filename before restoring the slot filename. */
s32 func_80021F18(s32 slot, void *data) {
    s32 slot_name[8];
    s32 temporary_name[8];
    s32 *slot_table;
    s32 *slot_entry;
    s32 result;

    func_80021B18(slot_name, slot);
    func_80021B18(temporary_name, 5);
    slot_table = (s32 *)&(*(s32 (*)[][32])(&D_80083E98));
    slot_entry = (s32 *)((u8 *)slot_table + (slot << 7));
    if (*slot_entry != 0) {
        rename(slot_name, temporary_name);
    }
    *(s32 *)((u8 *)data + 0x204) = 0;
    func_80021EB8(data);
    result = func_80021C4C(temporary_name, data, 0xC0, 0, *slot_entry);
    if (result != 0) {
        func_80021DF4(slot, data);
        func_800220DC();
    }
    rename(temporary_name, slot_name);
    return result;
}
