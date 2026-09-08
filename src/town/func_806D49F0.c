#include "common.h"

extern void *func_80016D98(s32 arg0);
extern s32 func_800178A8(void *arg0, s32 arg1, s32 arg2);
extern void *func_80017960(void *arg0, void *arg1, s32 arg2, s32 arg3);

extern u8 D_800189FC[16];
extern u8 D_80018B98[16];
extern u8 D_8001ABA0[16];

/* Returns a direct lookup result or a table entry, with a special case for type 0xB. */
void *func_800169F0(s32 entry_id, s32 unused, s32 entry_type)
{
    void *result;
    u8 *entry_table;

    result = func_80016D98(entry_type);
    if (result != 0) {
        return result;
    }

    entry_table = D_800189FC;
    result = func_80017960(entry_table, D_80018B98, entry_id, entry_type);
    if ((entry_type == 0xB) && (func_800178A8(entry_table, entry_id, 0xB) != 0)) {
        return D_8001ABA0;
    }
    return result;
}
