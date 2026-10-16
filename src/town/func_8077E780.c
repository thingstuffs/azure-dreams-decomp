#include "common.h"

/* Copy, in this TOWN script module, of the module-0 helper townFindEligibleEntry (src/town/func_8032F794.c). */

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

extern void func_80016E94(s32 records, s32 count);
extern s32 func_800176F0(s32 flag);
extern s32 D_80017768;

/* Return the first entry whose flag is clear and whose callback returns zero, rescanning while D_80017768 is set. */
s32 func_80016F80(ScriptContext *context) {
    s32 entry_index;

    func_80016E94(context->unk_14, context->unk_1A);
    do {
        D_80017768 = 0;
        entry_index = 0;
        while (func_800176F0(context->entries[entry_index].flag) != 0 ||
               context->entries[entry_index].callback(context, entry_index) != 0) {
            entry_index++;
        }
    } while (D_80017768 != 0);
    return entry_index;
}
