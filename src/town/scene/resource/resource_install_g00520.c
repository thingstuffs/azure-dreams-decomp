/* Resource install (G00520).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8008D588, CL:town/func_8008D5BC, CL:town/func_8008D630, CL:town/func_8008D6EC, CL:town/func_8008D7CC, CL:town/func_8008D850, CL:town/func_8008D988, PD:town/engine:800CF720.
 */
#include "town/scene/resource/resource_install_g00520.h"

/* Look up a value by three packed key fields in the zero-value-terminated table. */
u32 *find_packed_resource_descriptor(s32 flag_bit, s32 high_key, s32 low_key) {
    u32 *flags;
    u32 *value;
    u32 bits;
    u32 high_mask;
    u32 low_mask;

    flags = D_801131EC[0];
    if (flags[1] != 0) {
        high_mask = 0x3F000000;
        low_mask = 0x007F0000;
        value = flags + 1;
        do {
            bits = *flags;
            if (flag_bit == ((bits >> 23) & 1) &&
                high_key == ((bits & high_mask) >> 24) &&
                low_key == ((bits & low_mask) >> 16)) {
                return (u32 *)*value;
            }

            value += 2;
            flags += 2;
        } while (*value != 0);
    }

    return 0;
}

/* Make room for an allocation, record its metadata, and transfer its data. */
s32 install_resource_descriptor_at_front(s32 kind, s32 state, s32 value, s32 start_index)
{
    s32 alloc_size;
    s32 available;
    s32 index;
    u32 *allocation;
    TownAllocEntry *entry;
    TownAllocEntry *entry_base;
    s32 entry_offset;
    TownAllocEntry *table;

    index = start_index;
    allocation = find_packed_resource_descriptor(kind, state, value);
    if (allocation == 0) {
        return 0;
    }

    alloc_size = ((*allocation >> 11) + 1) << 11;
    available = 0x8000 - sum_resource_bytes(index);
    if (alloc_size > 0x7FFF) {
        index = 0;
        func_8008AC84(index);
    } else if (available < alloc_size) {
        entry_base = (TownAllocEntry *)resource_cache_records;
        entry_offset = index * sizeof(TownAllocEntry);
        entry = (TownAllocEntry *)(entry_offset + (s32)entry_base);
        available += entry->size;
        func_8008AC84(index);
        while (available < alloc_size) {
            entry--;
            index--;
            available += entry->size;
            func_8008AC84(index);
        }
    }

    shift_resource_entries_and_data(index, alloc_size);
    func_8008AC84(index + 1);
    table = (TownAllocEntry *)resource_cache_records;
    table[0].kind = kind;
    table[0].state = state;
    table[0].value = value;
    table[0].size = alloc_size;
    start_cd_read(allocation, town_resource_buffer);
    return 0;
}

/* Find or allocate the matching entry and move it to the front. */
void ensure_resource_at_front(s32 kind, s32 state, s32 value) {
    s32 entry_index;

    entry_index = find_resource_index_by_key(kind, state, value);
    if (entry_index < 0) {
        entry_index = install_resource_descriptor_at_front(kind, state, value, entry_index & 0x7FFFFFFF);
    }
    if (entry_index != 0) {
        move_resource_to_front(entry_index);
    }
}

/* Loads town state from item flags and dispatches the selected object value. */
void submit_object_resource_data(Object *object) {
    Item *item;
    u32 type_mask;
    u32 extra_flags;
    s32 call_value;
    u32 high_code;
    u32 low_code;
    register u32 data_base;
    register u32 data_offset;

    item = object->item98;
    if (item != 0 && (type_mask = item->flags0 & 0xC0000000) == 0xC0000000) {
        town_resource_context.value0 = object->value60;
        call_value = (item->flags0 >> 23) & 1;
        town_resource_context.value4 = call_value;
        high_code = (item->flags0 & 0x3F000000) >> 24;
        town_resource_context.value8 = high_code;
        low_code = (item->flags0 & 0x007F0000) >> 16;
        town_resource_context.valueC = low_code;
        extra_flags = item->flags1;
        if ((extra_flags & type_mask) == type_mask) {
            town_resource_context.value10 = (extra_flags & 0x3F000000) >> 24;
            town_resource_context.value14 = (item->flags1 & 0x007F0000) >> 16;
        }
        ensure_resource_at_front(call_value, high_code, low_code);
        data_base = 0x80016000;
        data_offset = *(u16 *)&item->flags0;
        call_value = data_base + data_offset;
    } else {
        call_value = object->value48;
    }
    call_script(call_value);
}

/* Unpack and dispatch each entry until its second word is zero. */
void ensure_packed_resource_list(u8 *entries_in) {
    u8 *entries;
    u32 packed_fields;
    entries = entries_in;

    entries_in = entries;
    if (((S_8008B23C_0 *)entries_in)->unk_04 != 0) {
        do {
            packed_fields = ((S_8008B23C_0 *)entries_in)->unk_00;
            ensure_resource_at_front(
                (packed_fields >> 0x17) & 1,
                (u32)(packed_fields & 0x3F000000) >> 0x18,
                (u32)(packed_fields & 0x7F0000) >> 0x10
                );
            entries_in += 8;
        } while (((S_8008B23C_0 *)entries_in)->unk_04 != 0);
    }
}
