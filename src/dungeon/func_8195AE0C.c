#include "common.h"

typedef struct {
    u32 value;
    s8 index;
    u8 pad05[3];
    void *owner;
    u8 pad0C[8];
    u16 flags;
} Entry;

typedef struct {
    u8 pad00[0xC];
    s32 base;
} Owner;

/* Refresh the entry value and handle index stepping and bounds. */
void func_8195AE0C(Entry *entry, s16 *step, s32 lower, s32 upper)
{
    Entry *active_entry = entry;
    s32 pending_update;
    s32 index_high_byte;
    Owner *owner;
    u8 index;

    owner = active_entry->owner;
    active_entry->value = owner->base + active_entry->index * 0x18;
    if (*step > 0) {
        active_entry->index = (u8)active_entry->index + 1;
    } else if (*step < 0) {
        active_entry->index = (u8)active_entry->index - 1;
    }

    index = (u8)active_entry->index;
    index_high_byte = index << 24;
    if ((s8)index < (s16)lower) {
        pending_update = active_entry->flags | 0x4000;
        active_entry->index = lower;
        active_entry->flags = pending_update;
        return;
    }
    if ((s8)index > (s16)upper) {
        pending_update = active_entry->flags | 0x4000;
        active_entry->index = upper;
        active_entry->flags = pending_update;
        return;
    }
    active_entry->flags &= 0xBFFF;
}
