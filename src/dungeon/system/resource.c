/* Packed resource lookup, cache reordering and loading, and object script submission. */
#include "dungeon/system/resource.h"


/* Copies byte_count / 4 words backward, starting at source + byte_count and destination + byte_count. */
void copy_words_backward_from_offset(s32 dest_addr, s32 src_addr, s32 byte_count) {
    s32 *dest_word;
    s32 *src_word;
    s32 word;
    s32 byte_offset;
    s32 words_left;

    byte_offset = byte_count;
    dest_word = (s32 *)(dest_addr + byte_offset);
    src_word = (s32 *)(src_addr + byte_offset);
    words_left = (byte_offset / 4);
    if (words_left > 0) {
        do {
            word = *src_word;
            src_word--;
            words_left--;
            *dest_word = word;
            dest_word--;
        } while (words_left > 0);
    }
}

s32 sum_resource_bytes(s32 entry_count) {
    s32 sum;
    s32 entry_index;

    sum = 0;
    for (entry_index = 0; entry_index < entry_count; entry_index++) {
        sum += resource_cache_records[entry_index].field_4;
    }
    return sum;
}

/* Finds the cache entry matching a three-part key, or returns the end index with bit 31 set. */
s32 find_resource_index_by_key(s32 first_byte, s32 second_byte, s32 halfword_value) {
    s32 entry_index;
    s8 *entry_table;
    s8 *entry;

    entry_table = resource_cache_records;
    for (entry_index = 0; entry_table[entry_index * 8 + 1] != -1; entry_index++) {
        entry = &entry_table[entry_index * 8];
        if ((first_byte == entry[0]) && (second_byte == entry[1]) && (halfword_value == *(s16 *)(entry + 2))) {
            return entry_index;
        }
    }
    return entry_index - 0x80000000;
}

/* Shifts cache records back one slot and moves their data backward by the requested byte offset. */
void shift_resource_entries_and_data(s32 record_count, s32 data_offset) {
    s32 data_addr;
    s32 record_value;
    s32 src_index;
    s32 dst_index;
    ovl_d54c_7FFED630_Record *dst_record;
    ovl_d54c_7FFED630_Record *src_record;
    s32 records_base;
    u8 *state;

    dst_index = record_count;
    if (dst_index != 0) {
        records_base = (s32)resource_cache_records;
        state = (u8 *)&town_resource_context;
        do {
            dst_record = (ovl_d54c_7FFED630_Record *)(dst_index * 8 + records_base);
            src_index = dst_index - 1;
            src_record = (ovl_d54c_7FFED630_Record *)(src_index * 8 + records_base);
            dst_record->b0 = src_record->b0;
            dst_record->b1 = src_record->b1;
            dst_record->h2 = src_record->h2;
            record_value = src_record->w4;
            dst_record->w4 = record_value;
            data_addr = *(s32 *)(state + 0x2c) + sum_resource_bytes(src_index);
            copy_words_backward_from_offset(data_addr + data_offset, data_addr, record_value);
            dst_index = src_index;
        } while (dst_index != 0);
    }
}

/* Saves a cached resource in scratch space, shifts earlier entries, and restores it at the cache front. */
void move_resource_to_front(s32 entry_index) {
    ovl_d54c_7FFED6EC_DungeonEntry *entries;
    ovl_d54c_7FFED6EC_DungeonEntry *entry;
    DungeonCacheState *state;
    s32 saved_field_0;
    s32 saved_field_1;
    s32 saved_field_2;
    s32 data_size;
    s32 scratch_buffer;

    entries = resource_cache_records;
    entry = &entries[entry_index];
    saved_field_0 = entry->field_0;
    saved_field_1 = entry->field_1;
    saved_field_2 = entry->field_2;
    data_size = entry->field_4;
    scratch_buffer = alloc_gpu_scratch_ring(0x8000);
    memcpy(scratch_buffer, town_resource_context.field_2C + sum_resource_bytes(entry_index), data_size);
    shift_resource_entries_and_data(entry_index, data_size);
    state = &town_resource_context;
    memcpy(state->field_2C, scratch_buffer, data_size);
    resource_cache_records[0].field_0 = saved_field_0;
    entries->field_1 = saved_field_1;
    entries->field_2 = saved_field_2;
    entries->field_4 = data_size;
}

/* Returns the resource descriptor matching three packed key fields, or NULL at the table terminator. */
u32 *find_packed_resource_descriptor(s32 key_flag, s32 key_high, s32 key_low) {
    u32 *value_ptr;
    u32 *entry;
    u32 packed_key;
    u32 high_mask;
    u32 low_mask;

    entry = D_801131EC;
    if (((ovl_d54c_7FFED7CC_S_8008AF2C_0 *)entry)->unk_04 != 0) {
        high_mask = 0x3F000000;
        low_mask = 0x007F0000;
        value_ptr = entry + 1;
        do {
            packed_key = *entry;
            if ((key_flag == ((packed_key >> 0x17) & 1)) && (key_high == ((packed_key & high_mask) >> 0x18))
            && (key_low == ((packed_key & low_mask) >> 0x10))) {
                return (u32 *)*value_ptr;
            }
            value_ptr += 2;
            entry += 2;
        } while (*value_ptr != 0);
    }
    return NULL;
}

/* Makes room at the front of the resource cache, records the descriptor, and starts its CD read. */
s32 install_resource_descriptor_at_front(s32 resource_kind, s32 resource_group, s32 resource_id, s32 entry_index) {
    s32 entry = entry_index;
    u32 *resource;
    s32 alloc_size;
    register s32 free_bytes;
    s8 *entry_ptr;
    s32 block_count;
    register s32 capacity;
    s32 used_bytes;

    resource = find_packed_resource_descriptor(resource_kind, resource_group, resource_id);
    block_count = 0;
    if (resource == NULL)
        return block_count;

    block_count = (u32) *resource >> 0xB;
    alloc_size = (block_count + 1) << 0xB;
    used_bytes = sum_resource_bytes(entry);
    capacity = 0x8000;
    free_bytes = capacity - used_bytes;
    if (alloc_size > 0x7FFF) {
        entry = 0;
        func_8008AC84(entry);
    } else if (free_bytes < alloc_size) {
        s8 *entries = (s8 *)resource_cache_records;
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
    shift_resource_entries_and_data(entry, alloc_size);
    func_8008AC84(entry + 1);
    resource_cache_records[0].field_0 = resource_kind;
    ((ovl_d54c_7FFED850_S_8008AFB0_0 *)(&resource_cache_records[0]))->unk_01 = resource_group;
    ((ovl_d54c_7FFED850_S_8008AFB0_0 *)(&resource_cache_records[0]))->unk_02 = resource_id;
    ((ovl_d54c_7FFED850_S_8008AFB0_0 *)(&resource_cache_records[0]))->unk_04 = alloc_size;
    start_cd_read(resource, town_resource_buffer[0]);
    return 0;
}

void ensure_resource_at_front(s32 resource_flag, s32 resource_group, s32 resource_id) {
    s32 entry_index;

    entry_index = find_resource_index_by_key(resource_flag, resource_group, resource_id);
    if (entry_index < 0) {
        entry_index = install_resource_descriptor_at_front(resource_flag, resource_group, resource_id, entry_index & 0x7FFFFFFF);
    }
    if (entry_index != 0) {
        move_resource_to_front(entry_index);
    }
}

/* Resolves tagged object resource data through the cache, or uses the direct data pointer, then runs
   its script. */
void submit_object_resource_data(ovl_d54c_7FFED9F8_Object *object) {
    ovl_d54c_7FFED9F8_Item *item;
    u32 tag_mask;
    u32 extra_flags;
    s32 option_bit;
    u32 high_field;
    u32 middle_field;
    u8 *data;
    u32 data_base;
    u32 data_offset;

    item = object->item98;
    if ((item != 0) && (tag_mask = item->flags0 & 0xC0000000, tag_mask == 0xC0000000)) {
        town_resource_context.value0 = object->value60;
        option_bit = (item->flags0 >> 23) & 1;
        town_resource_context.value4 = option_bit;
        high_field = (item->flags0 & 0x3F000000) >> 24;
        town_resource_context.value8 = high_field;
        middle_field = (item->flags0 & 0x007F0000) >> 16;
        town_resource_context.valueC = middle_field;
        extra_flags = item->flags1;
        if ((extra_flags & tag_mask) == tag_mask) {
            town_resource_context.value10 = (extra_flags & 0x3F000000) >> 24;
            town_resource_context.value14 = (item->flags1 & 0x007F0000) >> 16;
        }
        ensure_resource_at_front(option_bit, high_field, middle_field);
        data_base = 0x80016000;
        data_offset = *(u16 *)&item->flags0;
        data = (u8 *)(data_base + data_offset);
    } else {
        data = (u8 *)object->value48;
    }
    call_script(data);
}

void ensure_packed_resource_list(u8 *entries_in) {
    u8 *entries;
    u32 packed_fields;
    entries = entries_in;

    entries_in = entries;
    if (((ovl_d54c_7FFEDADC_S_8008B23C_0 *)entries_in)->unk_04 != 0) {
        do {
            packed_fields = ((ovl_d54c_7FFEDADC_S_8008B23C_0 *)entries_in)->unk_00;
            ensure_resource_at_front(
                (packed_fields >> 0x17) & 1,
                (u32)(packed_fields & 0x3F000000) >> 0x18,
                (u32)(packed_fields & 0x7F0000) >> 0x10
                );
            entries_in += 8;
        } while (((ovl_d54c_7FFEDADC_S_8008B23C_0 *)entries_in)->unk_04 != 0);
    }
}
