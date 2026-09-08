#include "common.h"

typedef struct {
    u8 pad0[8];
    u16 count;
    u16 index;
    s16 *data;
} ScriptState;

/* Return the script entry while updating its index and repeat count. */
s32 func_8009F988(void) {
    ScriptState *script;
    u16 entry_index;
    s16 *script_entry;

    script = (ScriptState *)0x80013710;
    entry_index = script->index;
    script_entry = &script->data[entry_index];

    if (script->count == 0) {
        s8 *count_byte = (s8 *)--script_entry;

        script->index = entry_index - 1;
        if (*count_byte >= 0) {
            s32 repeat_count;

            repeat_count = *(volatile u8 *)count_byte;
            script->count = repeat_count - 1;
        } else {
            script->count = 0;
        }
    } else {
        script->count = script->count - 1;
    }
    return (s32)script_entry;
}

/* MECHANISM: Frameless leaf under the true-space func_8009F988 name, with both
   apparent 0x8009F9DC/0x8009F9E0 calls recovered as local count-update joins.
   The shared pointer return then sinks move $v0,$v1 into the jr $ra delay slot. */
