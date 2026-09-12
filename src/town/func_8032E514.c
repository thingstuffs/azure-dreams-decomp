#include "common.h"


typedef void (*TownCall3)(void *, void *, s32);
typedef void (*TownCall1)(s32);

typedef struct S_80018D14_0 {
    u8 pad_00[0x6000];
    u8 * unk_6000;
} S_80018D14_0;   /* page in func_80018D14 */

typedef struct S_80018D14_1 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x14];
    u8 * unk_38;
} S_80018D14_1;   /* root in func_80018D14 */

typedef struct S_80018D14_2 {
    u8 pad_00[0x20];
    u8 * unk_20;
} S_80018D14_2;   /* root2 in func_80018D14 */


extern s8 D_80016000[];
extern u8 D_80016034[16];
extern u8 D_8001605C[];

/* Clear a shop object and its linked state after asserting that the reference matches. */
void func_80018D14(u8 *object_ref)
{
    void **global_page;
    u8 *context;
    u8 object_flags;
    u8 *callbacks;
    TownCall3 callback_168;
    u8 *updated_context;
    u8 *updated_callbacks;
    TownCall1 callback_174;
    u8 *state_base;
    u8 *object_table;
    u8 *entry;
    u8 *link_state;
    s32 slot;
    u32 link_flags;
    s32 object_offset;
    s32 link_offset;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    global_page = (void **)0x80010000;
    context = ((S_80018D14_0 *)global_page)->unk_6000;
    callbacks = ((S_80018D14_1 *)context)->unk_38;
    object_table = callbacks + 0x2F0;
    state_base = callbacks;
    object_flags = object_ref[3];
    ASM_KEEP(object_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    slot = object_flags & 0x1F;

    if (object_ref[0] != object_table[slot * 0x54 + 0x13]) {
        callbacks = ((S_80018D14_1 *)context)->unk_20;
        callback_168 = (*(TownCall3 *)((u8 *)callbacks + 0x168));
        do {
            callback_168(D_80016034, D_8001605C, 0x41);
        } while (0);
        updated_context = ((S_80018D14_0 *)global_page)->unk_6000;
        updated_callbacks = ((S_80018D14_2 *)updated_context)->unk_20;
        callback_174 = (*(TownCall1 *)((u8 *)updated_callbacks + 0x174));
        callback_174(1);
        ASM_KEEP(slot);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    }

    object_offset = slot * 4;
    entry = (u8 *)((u32)(((object_offset + slot) * 4 + slot) * 4) +
                    (u32)object_table);
    entry[0x13] = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    link_flags = entry[0x43];
    slot = link_flags & 0x3F;
    link_offset = slot * 4;
    link_state = state_base + link_offset;
    link_state[0x980] = 0;
    do {
        link_state[0x981] = 0;
    } while (0);
    entry = (((link_offset + slot) * 4 + slot) * 4) + state_base;
    entry[0xA93] = 0;
}

/* MECHANISM: Four values span the call region: literal page base, root-derived base,
   object-table base, and masked index, inducing retail's s3/s2/s1/s0 hold set.
   The record address is recomputed at the branch join instead of held across calls. */
