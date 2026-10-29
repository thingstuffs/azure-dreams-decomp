#include "common.h"
#include "engine/cd.h"
#include "dungeon/item/monster_resource_slots_g00325.h"
#include "sdk/libc.h"
#include "slus.h"

extern u8 D_800E58A8[];
extern u8 D_80164800[];
extern u8 D_8016A800[];
extern u8 D_80170800[];

/* Loads or reuses entry resource data, optionally waiting for the CD read. */
MonsterFactory load_monster_resource_data(s32 resource_id, void *resource_entry, s32 wait_for_read) {
    MonsterResourceSlot *entry = resource_entry;
    s16 asset_id = resource_id;
    s32 wait_mode = wait_for_read;
    s32 cached_id_abs = entry->type;
    MonsterFactory result = 0;
    u8 *data;
    u8 *cd_params;
    s32 compare_id;
    register s32 requested_id;
    register s32 id_high;
    s32 loaded_id;
    s32 read_size;
    s32 disc_offset;
    s32 slot_base;
    s32 slot_part;
    s32 asset_index;
    register s32 asset_offset;
    register s32 slot;

    if (cached_id_abs != 2) {
        compare_id = monster_resource_cache_ids[entry->cache_index];
        cached_id_abs = abs(compare_id);
        compare_id = (u32)resource_id << 16;
        compare_id >>= 16;
        if ((cached_id_abs == compare_id) && (cached_id_abs != 0x39)) {
            entry->resource_id = asset_id;
        }
    }

    if (entry->resource_id == 0) {
        id_high = (u32)asset_id << 0x10;
        requested_id = id_high >> 0x10;
        if (requested_id == 0x38) {
            data = D_80164800;
            disc_offset = 0x56B1;
            read_size = 0x24;
        } else if (requested_id == 0x31) {
            data = D_8016A800;
            disc_offset = 0x569C;
            read_size = 0x18;
        } else {
            slot = entry->cache_index;
            read_size = 0xC;
            slot_base = slot * 3;
            /* Select a PS1 bank address in the 32-bit address domain. */
            data = (u8 *)((u32)D_80170800 - (slot_base << 13));
            asset_index = requested_id - 1;
            asset_offset = asset_index * 0x54;
            slot_part = slot * 12 + 0x4340;
            disc_offset = asset_offset + slot_part;
        }
        cd_params = D_800E58A8;
        pack_tagged_resource_descriptor(read_size, data, cd_params, disc_offset);
        Control_CD(6, cd_params, 0);

        if ((wait_mode << 0x10) != 0) {
            drain_cd_command_queue();
            if (entry->type != 2) {
                monster_resource_cache_ids[entry->cache_index] = asset_id;
                result = *(MonsterFactory *)data;
            } else {
                result = *(MonsterFactory *)data;
            }
            entry->factory = result;
        } else if (entry->type != 2) {
            monster_resource_cache_ids[entry->cache_index] = -asset_id;
        }
    } else {
        if (entry->type != 2) {
            monster_resource_cache_ids[entry->cache_index] = asset_id;
        }
        loaded_id = (s16)asset_id;
        if (loaded_id == 0x38) {
            data = D_80164800;
        } else if (loaded_id == 0x31) {
            data = D_8016A800;
        } else {
            data = (u8 *)((u32)D_80170800 - (entry->cache_index * 0x6000));
        }
        result = *(MonsterFactory *)data;
    }
    return result;
}
