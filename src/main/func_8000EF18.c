#include "common.h"

extern void func_80021B18(void *arg0, s32 arg1);
extern s32 func_80021C4C(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_80021DF4(s32 arg0, void *arg1);
extern void func_80021EB8(void *arg0);
extern void func_800220DC(void);
extern void rename(void *arg0, void *arg1);

extern s32 D_80083E98[][32];

/* Updates slot data using a temporary filename before restoring the slot filename. */
s32 func_80021F18(s32 slot, void *data) {
    s32 slot_name[8];
    s32 temp_name[8];
    s32 *slot_table;
    s32 *slot_entry;
    s32 result;

    func_80021B18(slot_name, slot);
    func_80021B18(temp_name, 5);
    slot_table = (s32 *)&D_80083E98;
    slot_entry = (s32 *)((u8 *)slot_table + (slot << 7));
    if (*slot_entry != 0) {
        rename(slot_name, temp_name);
    }
    *(s32 *)((u8 *)data + 0x204) = 0;
    func_80021EB8(data);
    result = func_80021C4C(temp_name, data, 0xC0, 0, *slot_entry);
    if (result != 0) {
        func_80021DF4(slot, data);
        func_800220DC();
    }
    rename(temp_name, slot_name);
    return result;
}
