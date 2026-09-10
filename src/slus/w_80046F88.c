#include "common.h"

#include "common.h"

/* Object self-relocation: if live address != last-known anchor at +0x24,
 * add the byte delta to every embedded absolute pointer inside the object
 * and the two trailing arrays it owns. Returns the applied delta (0 if
 * the object had not moved). */
typedef struct S_80046F88 {
    /*0x00*/ s32 *arr;
    /*0x04*/ s32 count;
    /*0x08*/ s32 *end;
    /*0x0C*/ s32 val0C;
    /*0x10*/ s32 unk10;
    /*0x14*/ s32 val14;
    /*0x18*/ s32 unk18;
    /*0x1C*/ s32 val1C;
    /*0x20*/ s32 unk20;
    /*0x24*/ void *anchor;
} S_80046F88;

/* Relocates embedded and array pointers after the object moves, returning the address delta. */
s32 func_80046F88(void *object_addr)
{
    S_80046F88 *obj = (S_80046F88 *)object_addr;
    /* delta must live in $a3; counter entry_index takes $a2. Guarded pin for PC port. */
    s32 delta;
    s32 addr_or_count;
    s32 ptr_value;
    s32 entry_index;
    s32 *cursor;
    s32 *pair_ptr;

    delta = 0;
    if (object_addr != obj->anchor) {
        do {
            delta = (s32)object_addr - (s32)obj->anchor;
        } while (0);
        ptr_value = (s32)obj->arr;
        do {
            addr_or_count = (obj->val14) + ptr_value;
            addr_or_count -= ptr_value;
            entry_index = 0;
        } while (0);
        obj->anchor = object_addr;
        ptr_value = ptr_value + delta;
        obj->arr = (s32 *)ptr_value;
        ptr_value = (s32)obj->end;
        cursor = obj->arr;
        ptr_value = ptr_value + delta;
        obj->end = (s32 *)ptr_value;
        ptr_value = obj->val0C;
        addr_or_count = addr_or_count + delta;
        obj->val14 = addr_or_count;
        ptr_value = ptr_value + delta;
        obj->val0C = ptr_value;
        ptr_value = obj->val1C;
        addr_or_count = obj->count;
        ptr_value = ptr_value + delta;
        obj->val1C = ptr_value;
        if (addr_or_count > 0) {
            do {
                entry_index++;
                *cursor += delta;
                cursor++;
            } while (entry_index < obj->count);
        }
        if ((u32)cursor < (u32)obj->end) {
            pair_ptr = cursor + 1;
            do {
                cursor += 2;
                *pair_ptr += delta;
                pair_ptr += 2;
            } while ((u32)cursor < (u32)obj->end);
        }
    }
    return delta;
}
