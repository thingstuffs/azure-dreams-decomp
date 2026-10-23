#include "common.h"

/* Copy, in this TOWN script module, of the module-0 helper find_eligible_entry (src/town/func_8032F794.c). */

typedef struct ScriptContext ScriptContext;

typedef struct ScriptEntry16 {
    s32 (*callback)(ScriptContext *context, s32 entry_index);
    u8 pad_04[0x8];
    s16 flag;
    u8 pad_0E[0x2];
} ScriptEntry16;

struct ScriptContext {
    u8 pad_00[0x10];
    ScriptEntry16 *entries;
    s32 unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
};

extern void func_80016B98(s32 records, s32 count);
extern s32 func_800173F4(s32 flag);
extern s32 script_rescan_request;

/*
 * Returns the first entry whose flag check and callback both return zero, restarting the scan
 * while script_rescan_request is set.
 */
s32 find_eligible_entry_b(ScriptContext *context) {
    s32 entry_index;

    func_80016B98(context->unk_14, context->unk_1A);
    do {
        script_rescan_request = 0;
        entry_index = 0;
        while (func_800173F4(context->entries[entry_index].flag) != 0 ||
               context->entries[entry_index].callback(context, entry_index) != 0) {
            entry_index++;
        }
    } while (script_rescan_request != 0);
    return entry_index;
}
