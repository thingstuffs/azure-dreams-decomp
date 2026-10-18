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

extern void func_80016B2C(s32 records, s32 count);
extern s32 func_80017388(s32 flag);
extern s32 D_800174DC;

/* Return the first entry whose flag is clear and whose callback returns zero, rescanning while D_800174DC is set. */
s32 func_80016C18(ScriptContext *context) {
    s32 entry_index;

    func_80016B2C(context->unk_14, context->unk_1A);
    do {
        D_800174DC = 0;
        entry_index = 0;
        while (func_80017388(context->entries[entry_index].flag) != 0 ||
               context->entries[entry_index].callback(context, entry_index) != 0) {
            entry_index++;
        }
    } while (D_800174DC != 0);
    return entry_index;
}
