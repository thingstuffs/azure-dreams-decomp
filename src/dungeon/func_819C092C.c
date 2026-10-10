/* Selector 72, retail file [0x19E092C, 0x19E095C); complete callable clone. */
#include "common.h"

/* The owner's table of 0x16-byte entries. */
typedef struct Bank19de800_19e092c_EntryOwner {
    u8 pad_00[0xC];
    s32 entries;
} Bank19de800_19e092c_EntryOwner;

/* An object that tracks one entry of its owner's table. */
typedef struct Bank19de800_19e092c_EntryCursor {
    s32 entry;          /* address of the current entry */
    u8 pad_04[4];
    Bank19de800_19e092c_EntryOwner *owner;
} Bank19de800_19e092c_EntryCursor;

/* Sets the object entry address using a 22-byte stride. */
void func_8002612C(Bank19de800_19e092c_EntryCursor *object, s16 entry_index) {
    object->entry = object->owner->entries + entry_index * 0x16;
}

