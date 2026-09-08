#include "common.h"

/* Linked-entry struct used by the D_8006CE80 table: each 0xC-byte slot
 * holds an unrelated value, a "next"-style pointer to another entry of
 * the same layout, and a trailing value. */
typedef struct S_8006CE80 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ struct S_8006CE80 *unk4;
    /* 0x8 */ s32 unk8;
} S_8006CE80;

extern S_8006CE80 D_8006CE80[];

extern void func_8003F9E0(S_8006CE80 *a0);

/* Follow two links from the indexed entry and dispatch the final entry if both links exist. */
void func_80041038(u16 entry_index) {
    S_8006CE80 *entry = &D_8006CE80[(u16)entry_index & 0xFFFF];
    S_8006CE80 *linked_entry = entry->unk4;

    if (linked_entry != 0) {
        linked_entry = linked_entry->unk4;
        if (linked_entry != 0) {
            func_8003F9E0(linked_entry);
        }
    }
}
