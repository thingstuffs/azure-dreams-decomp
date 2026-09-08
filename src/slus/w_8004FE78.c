#include "common.h"

/* Canonical global flags word shared by several sibling functions in this
 * TU family (code9.c, code10.c, code11.c, code5.c, w_8004F558.c, ...).
 * w_8004F558.c (same D_800814A0 |= 0x8000 tail as this function) declares
 * it as a plain `extern int` and matches with the address recomputed
 * TWICE (load then store, in different registers) -- follow that. */
extern int D_800814A0;

/* Entity struct as seen by func_8004FE78: a 16-bit flags field at 0x1E and
 * an embedded sub-object at 0x20 (same sub-object base referenced by
 * func_8004FF00 in this TU) whose second word (a 3-element id/handle
 * array starting at 0x24) is walked here. */
typedef struct S_8004FE78_a0 {
    u8 pad00[0x1E];
    u16 field_1E;   /* 0x1E */
    u8 pad20[0x24 - 0x20];
    s32 unk24[3];   /* 0x24, 0x28, 0x2C */
} S_8004FE78_a0;

extern void func_8001832C(s32 arg0);

/* Process a non-null entity's nonzero handles and set its flags and the global flags to include 0x8000. */
void func_8004FE78(S_8004FE78_a0 *entity)
{
    s32 handle_index;
    s32 *handle_cursor;

    if (entity != 0) {
        handle_index = 0;
        handle_cursor = (s32 *)((char *)entity + 0x20);
        for (; handle_index < 3; handle_index++) {
            if (handle_cursor[1] != 0) {
                func_8001832C(handle_cursor[1]);
            }
            handle_cursor++;
        }
        entity->field_1E |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
