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

extern void select_available_option_triggers_associated(s32 records, s32 count);
extern s32 func_800174D8(s32 flag);
extern s32 D_80017794;

/* Return the first entry whose flag is clear and whose callback returns zero, rescanning while D_80017794 is set. */
s32 func_80016D68(ScriptContext *context) {
    s32 entry_index;

    select_available_option_triggers_associated(context->unk_14, context->unk_1A);
    do {
        D_80017794 = 0;
        entry_index = 0;
        while (func_800174D8(context->entries[entry_index].flag) != 0 ||
               context->entries[entry_index].callback(context, entry_index) != 0) {
            entry_index++;
        }
    } while (D_80017794 != 0);
    return entry_index;
}
