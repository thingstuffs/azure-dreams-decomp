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

extern void func_80017C8C(s32 records, s32 count);
extern s32 func_80018668(s32 flag);
extern s32 D_80019550;

/* Return the first entry whose flag is clear and whose callback returns zero, rescanning while D_80019550 is set. */
s32 get_first_entry_whose_flag(ScriptContext *context) {
    s32 entry_index;

    func_80017C8C(context->unk_14, context->unk_1A);
    do {
        D_80019550 = 0;
        entry_index = 0;
        while (func_80018668(context->entries[entry_index].flag) != 0 ||
               context->entries[entry_index].callback(context, entry_index) != 0) {
            entry_index++;
        }
    } while (D_80019550 != 0);
    return entry_index;
}
