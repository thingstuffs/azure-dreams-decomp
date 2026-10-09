#ifndef DUNGEON_NATIVE_ABI_H
#define DUNGEON_NATIVE_ABI_H
#include "common.h"
#include "shared/object_node.h"
/* Retail 8003FD64: links through *head and returns the allocated 0x20-byte node header.
 * Retail 8004491C: stores/compares a 32-bit registration key and returns 0 or 1.
 * Retail 800478B8: updates the supplied render entry in place; callers discard no value.
 * The registration key may carry a callback's address (func_80045340).
 */
ObjectNodeHeader *func_8003FD64(s32 flags, ObjectNodeHeader **head);
/* Some retail callers supply an additional ignored context word in a2. */
s32 func_8004491C(void *entry, s32 registration_key, ...);
void func_800478B8(void *render_entry);
s32 func_800BCB04(s32 x, s32 y, s16 minimum_height);
s32 func_800A56E0(s32 query_value);
#endif
