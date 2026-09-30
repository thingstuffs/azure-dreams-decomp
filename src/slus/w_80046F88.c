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
    s32 delta;
    s32 entry_index;
    s32 *cursor;

    delta = 0;
    if (object_addr != obj->anchor) {
        delta = (s32)object_addr - (s32)obj->anchor;
        obj->anchor = object_addr;
        obj->arr = (s32 *)((s32)obj->arr + delta);
        obj->end = (s32 *)((s32)obj->end + delta);
        obj->val0C += delta;
        obj->val14 += delta;
        obj->val1C += delta;
        cursor = obj->arr;
        for (entry_index = 0; entry_index < obj->count; entry_index++) {
            *cursor++ += delta;
        }
        for (; (u32)cursor < (u32)obj->end; cursor += 2) {
            cursor[1] += delta;
        }
    }
    return delta;
}
