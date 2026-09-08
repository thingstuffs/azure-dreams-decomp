#include "common.h"

extern void func_80021B18(void *arg0, s32 arg1);
extern s32 func_80021B98(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 func_80021C4C(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_80021EB8(void *arg0);
extern s32 func_80021EE0(void *arg0);

extern s32 D_80083E98[][32];

/* Marks quest data as loaded, optionally refreshing its indexed entry while preserving its state. */
void func_80021FF0(s32 entry_index, void *data, s32 update_entry) {
    s32 context[8];
    s32 *entry_table;
    s32 *entry;
    s32 saved_state;

    func_80021B18(context, entry_index);
    if (func_80021B98(context, data, 0xC0, 0) == 0) {
        return;
    }
    if (func_80021EE0(data) == 0) {
        return;
    }
    if (update_entry != 0) {
        saved_state = *(s16 *)((u8 *)data + 0x208);
        *(s16 *)((u8 *)data + 0x208) = 0;
        *(s32 *)((u8 *)data + 0x204) = 0;
        func_80021EB8(data);
        entry_table = (s32 *)&D_80083E98;
        entry = (s32 *)((u8 *)entry_table + (entry_index << 7));
        *(s16 *)((u8 *)entry + 8) = 0;
        *(s32 *)((u8 *)entry + 4) = *(s32 *)((u8 *)data + 0x204);
        func_80021C4C(context, entry, 1, 4, entry[0]);
        func_80021C4C(context, data, 1, 0, entry[0]);
        *(s16 *)((u8 *)data + 0x208) = saved_state;
        return;
    }
    *(s16 *)((u8 *)data + 0x208) = 0;
}
