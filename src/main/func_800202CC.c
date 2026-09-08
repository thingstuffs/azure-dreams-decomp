#include "common.h"

extern void func_8004DDBC(void *arg0, void *arg1, void *arg2);
extern void func_80407160(void *arg0);
extern u8 D_80408A30[];

/* Updates or clears selected slot outputs, then refreshes the state if any were selected. */
void func_804072CC(void *state, s32 *enabled, s32 *selected) {
    s32 slot;
    s32 updated;
    s32 data_offset;
    u8 *record;
    void **output_table;
    void *output;

    updated = 0;
    slot = 0;
    record = state;
    data_offset = 4;
    do {
        if (selected[slot] != 0) {
            output_table = *(void ***)((u8 *)state + 0x60);
            output = *(void **)((u8 *)output_table + (slot * 4) + 8);
            updated = 1;
            if (enabled[slot] != 0) {
                func_8004DDBC((u8 *)state + data_offset, D_80408A30, output);
            } else {
                *(s32 *)output = 0;
                *(s32 *)(record + 8) = 0;
            }
        }
        record += 0xC;
        data_offset += 0xC;
        slot++;
    } while (slot < 2);

    if (updated != 0) {
        func_80407160(state);
    }
}
