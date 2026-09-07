#include "common.h"

typedef struct {
    s16 unk0;
    s16 selector;
    s32 result;
} Entry;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 unk6;
} Position;

extern s32 func_800194E4();
extern void func_80019860();
extern s32 func_80019CD8();
extern void func_8001ACE8();

/* Applies the selected entry's position and returns its result. */
s32 func_80019DFC(Entry *entries, s32 object, void *context, s32 selection)
{
    Entry *saved_entries;
    register s32 saved_object ASM_REG("$18");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *saved_context ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    s32 entry_index;
    Position *position;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    saved_entries = entries;
    saved_object = object;
    saved_context = context;
    ASM_USE(saved_context);   /* MATCH pin: retail schedule: same instructions, different order without it */

    entry_index = func_800194E4(saved_entries, selection);
    position = (Position *)(saved_entries[entry_index].selector * 8
             + *(s32 *)((u8 *)saved_context + 0x14));
    func_80019860(position->x, position->y, position->z);

    if (saved_object != 0 && func_80019CD8(saved_object) != 0) {
        func_8001ACE8(*(s16 *)((u8 *)saved_context + 0x18));
    }

    return saved_entries[entry_index].result;
}
