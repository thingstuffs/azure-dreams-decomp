#include "common.h"
#include "dungeon/item.h"

typedef struct {
    u8 pad0[8];
    u16 count;
    u16 index;
    s16 *data;
} ScriptState;

/* Returns the current script entry, updating its index and repeat count. */
s16 *read_monster_script_entry(void) {
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

            repeat_count = *(u8 *)count_byte;
            script->count = repeat_count - 1;
        } else {
            script->count = 0;
        }
    } else {
        script->count = script->count - 1;
    }
    return script_entry;
}
