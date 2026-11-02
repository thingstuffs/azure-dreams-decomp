#include "common.h"
#include "town/devkit.h"
#include "town/devkit/flag_test_imports.h"

typedef s32 (*Callback)(s32);

extern u8 devkit_globals_page[];

/* Scan the table for the first entry the query rejects and dispatch that index's callback. */
s32 dispatch_first_rejected_entry(void) {
    s32 index = 0;
    s32 offset = 0;

    while (func_80700D74(*(u16 *)(devkit_globals_page + offset + 0x650)) != 0) {
        offset += 4;
        index++;
    }
    return ((Callback *)(devkit_globals_page + 0x6DC))
    [((s8 *)(devkit_globals_page + 0x6E4))[index]](index);
}
