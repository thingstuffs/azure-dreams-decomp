#include "common.h"
#include "m2c_compat.h"

extern void func_80053CFC(u32 *, s32);
extern s32 func_8008AC84(s32);
extern s32 func_8008ACE8(s32);
extern void func_8008AD90(s32, s32);
extern u32 *func_8008AF2C(s32, s32, s32);
extern s8 D_800CF720[0x8E4];
extern s32 D_801131E4[3];

typedef struct S_8008AFB0_0 {
    u8 pad_00[0x1];
    s8 unk_01;
    s16 unk_02;
    s32 unk_04;
} S_8008AFB0_0;   /* &D_800CF720[0] in func_8008AFB0 */

/* Loads a resource into the buffer, freeing entries until enough space is available. */
s32 func_8008AFB0(s32 resource_kind, s32 resource_group, s32 resource_id, s32 entry_index) {
    s32 entry = entry_index;
    u32 *resource;
    s32 alloc_size;
    register s32 free_bytes;
    s8 *entry_ptr;
    s32 block_count;
    register s32 capacity;
    s32 used_bytes;

    resource = func_8008AF2C(resource_kind, resource_group, resource_id);
    block_count = 0;
    if (resource == NULL)
        return block_count;

    block_count = (u32) *resource >> 0xB;
    alloc_size = (block_count + 1) << 0xB;
    used_bytes = func_8008ACE8(entry);
    capacity = 0x8000;
    free_bytes = capacity - used_bytes;
    if (alloc_size > 0x7FFF) {
        entry = 0;
        func_8008AC84(entry);
    } else if (free_bytes < alloc_size) {
        s8 *entries = D_800CF720;
        u32 entry_offset = entry << 3;
        entry_ptr = entries + entry_offset;
        goto loop_body;
        do {
            entry_ptr -= 8;
            entry--;
loop_body:
            free_bytes += ((s32 *)entry_ptr)[1];
            func_8008AC84(entry);
        } while (free_bytes < alloc_size);
    }
    func_8008AD90(entry, alloc_size);
    func_8008AC84(entry + 1);
    D_800CF720[0] = resource_kind;
    ((S_8008AFB0_0 *)(&D_800CF720[0]))->unk_01 = resource_group;
    ((S_8008AFB0_0 *)(&D_800CF720[0]))->unk_02 = resource_id;
    ((S_8008AFB0_0 *)(&D_800CF720[0]))->unk_04 = alloc_size;
    func_80053CFC(resource, D_801131E4[0]);
    return 0;
}
