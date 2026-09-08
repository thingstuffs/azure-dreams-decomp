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
    register s32 saved_object ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *saved_context ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 entry_index;
    Position *position;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    saved_entries = entries;
    saved_object = object;
    saved_context = context;
    ASM_USE(saved_context);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    entry_index = func_800194E4(saved_entries, selection);
    position = (Position *)(saved_entries[entry_index].selector * 8
             + *(s32 *)((u8 *)saved_context + 0x14));
    func_80019860(position->x, position->y, position->z);

    if (saved_object != 0 && func_80019CD8(saved_object) != 0) {
        func_8001ACE8(*(s16 *)((u8 *)saved_context + 0x18));
    }

    return saved_entries[entry_index].result;
}
