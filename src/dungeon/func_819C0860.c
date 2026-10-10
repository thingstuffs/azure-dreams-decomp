/* Selector 72, retail file [0x19E0860, 0x19E092C); complete callable clone. */
#include "common.h"

/* The owner's table of 0x16-byte entries. */
typedef struct Bank19de800_19e0860_EntryOwner {
    u8 pad_00[0xC];
    s32 entries;
} Bank19de800_19e0860_EntryOwner;

/* An object that tracks one entry of its owner's table. */
typedef struct Bank19de800_19e0860_EntryCursor {
    s32 entry;                      /* address of the current entry */
    s8 index;
    u8 pad_05[3];
    Bank19de800_19e0860_EntryOwner *owner;
    u8 pad_0C[8];
    u16 flags;                       /* 0x4000 = index clamped */
} Bank19de800_19e0860_EntryCursor;

/* Resolve the current entry, apply an index step, and enforce the index bounds. */
void func_80026060(void *object, s16 *index_step, s32 min_index, s32 max_index) {
    s16 step;
    u32 clamp_flags;
    u8 index;
    Bank19de800_19e0860_EntryCursor *obj = object;
    s32 initial_index = obj->index;
    Bank19de800_19e0860_EntryOwner *owner = obj->owner;

    obj->entry =
        owner->entries + (initial_index * 22);
    step = *index_step;
    if (step > 0) {
        obj->index = obj->index + 1;
    } else if (step < 0) {
        obj->index =
            obj->index - 1;
    }
    index = (u8)obj->index;
    if ((s8)index < (s16)min_index) {
        clamp_flags = obj->flags | 0x4000;
        obj->index = min_index;
        obj->flags = clamp_flags;
        return;
    }
    if ((s8)index > (s16)max_index) {
        clamp_flags = obj->flags | 0x4000;
        obj->index = max_index;
        obj->flags = clamp_flags;
        return;
    }
    obj->flags &= 0xBFFF;
}

