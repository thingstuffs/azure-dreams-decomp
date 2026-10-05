#include "common.h"

extern s32 func_8001ADE0(s32 flagIndex);
extern void func_8001ACE8(s32 bit_index);
extern void *func_80019DFC(void *entries, void *object, s32 context, s32 selection);

extern u8 D_8001BE24[];
extern u8 D_8001C354[];
extern u8 D_8001DCD4[];
extern u8 D_8001E16A[];
extern u8 D_8001E42A[];

/* Selects an entry pointer, with state-dependent alternatives for entry 0x1E. */
void *func_80018420(s32 table_index, s32 unused, s32 entry_id) {
    void *result;

    if (entry_id == 0x1E) {
        if (func_8001ADE0(0x145E) != 0) {
            if (func_8001ADE0(0x145F) != 0) {
                result = D_8001E42A;
            } else {
                result = D_8001E16A;
            }
        } else {
            result = D_8001DCD4;
            func_8001ACE8(0x145E);
        }
    } else {
        result = func_80019DFC(D_8001BE24, D_8001C354, table_index, entry_id);
    }
    return result;
}
