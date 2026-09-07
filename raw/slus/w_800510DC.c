#include "common.h"

/* Guards on a0->field4's sub-entity flags bit 0x2000: if set, calls
 * func_80051228(), then marks the same bit on a0->field0's (freshly
 * reloaded) sub-entity, marks bit 0x8000 on a's 16-bit flags word located
 * 2 bytes before the parameter itself, and marks bit 0x8000 on the global
 * 32-bit flags word D_800814A0 (same global touched by the func_8004B530 /
 * func_8004F52C / func_8004EE90 family). Matches at gcc 2.7.2 -O2 -G0 (also
 * 2.6.3 -G0): a plain `extern int D_800814A0;` scalar compiled with small-data
 * disabled (-G0) forces lui/%hi + lw|sw/%lo addressing while still emitting
 * the bare-macro codegen shape (fresh independent lui for the load AND for
 * the store, no shared base register) -- declaring D_800814A0 as an
 * array/struct (>8B) to force hi/lo the "usual" way instead makes gcc
 * materialize a single shared address (`la`/lui+addiu, reused for both the
 * read and the write), which never matches retail's two-independent-lui
 * form for this compiler family. */
/* generic sub-entity type: only offset 0x1E (a "used"/flags halfword) is
 * accessed by this function. */
typedef struct {
    u8 pad[0x1E];
    u16 flags; /* offset 0x1E */
} S_800510DC_Ent;

/* a0 points 2 bytes into a larger record: offset -2 holds a u16 flags word
 * belonging to the record itself; offset 0/4 hold pointers to sub-entities
 * of type S_800510DC_Ent. */
typedef struct {
    S_800510DC_Ent *field0; /* offset 0x0 */
    S_800510DC_Ent *field4; /* offset 0x4 */
} S_800510DC;

extern int D_800814A0; /* global 32-bit "used"/flags word */
extern void func_80051228(void);

void func_800510DC(S_800510DC *a0)
{
    S_800510DC_Ent *v1;

    if (a0->field4->flags & 0x2000) {
        func_80051228();
        v1 = a0->field0;
        v1->flags |= 0x2000;
        *(u16 *)((u8 *)a0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
