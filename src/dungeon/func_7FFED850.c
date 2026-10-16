#include "modules/dungeon_ovl_d54c.h"

s32 townInstallResourceDescriptorAtFront(s32 resource_kind, s32 resource_group, s32 resource_id, s32 entry_index) {
    s32 entry = entry_index;
    u32 *resource;
    s32 alloc_size;
    register s32 free_bytes;
    s8 *entry_ptr;
    s32 block_count;
    register s32 capacity;
    s32 used_bytes;

    resource = townFindPackedResourceDescriptor(resource_kind, resource_group, resource_id);
    block_count = 0;
    if (resource == NULL)
        return block_count;

    block_count = (u32) *resource >> 0xB;
    alloc_size = (block_count + 1) << 0xB;
    used_bytes = townSumResourceBytes(entry);
    capacity = 0x8000;
    free_bytes = capacity - used_bytes;
    if (alloc_size > 0x7FFF) {
        entry = 0;
        func_8008AC84(entry);
    } else if (free_bytes < alloc_size) {
        s8 *entries = (s8 *)D_800CF720;
        u32 entry_offset = entry << 3;
        entry_ptr = entries + entry_offset;
        free_bytes += ((s32 *)entry_ptr)[1];
        func_8008AC84(entry);
        while (free_bytes < alloc_size) {
            entry_ptr -= 8;
            entry--;
            free_bytes += ((s32 *)entry_ptr)[1];
            func_8008AC84(entry);
        }
    }
    townShiftResourceEntriesAndData(entry, alloc_size);
    func_8008AC84(entry + 1);
    D_800CF720[0].field_0 = resource_kind;
    ((ovl_d54c_7FFED850_S_8008AFB0_0 *)(&D_800CF720[0]))->unk_01 = resource_group;
    ((ovl_d54c_7FFED850_S_8008AFB0_0 *)(&D_800CF720[0]))->unk_02 = resource_id;
    ((ovl_d54c_7FFED850_S_8008AFB0_0 *)(&D_800CF720[0]))->unk_04 = alloc_size;
    func_80053CFC(resource, D_801131E4[0]);
    return 0;
}
