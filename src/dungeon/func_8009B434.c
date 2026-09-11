#include "common.h"

extern s32 Control_CD();
extern s32 func_8003F320();
extern s32 func_8003F6D4();

extern s8 D_800E3DA0[];
extern u8 D_800E58A8[];
extern u8 D_80164800[];
extern u8 D_8016A800[];
extern u8 D_80170800[];

/* Loads or reuses entry resource data, optionally waiting for the CD read. */
s32 func_800A0B94(s32 resource_id, u8 *resource_entry, s32 wait_for_read) {
    u8 *entry = resource_entry;
    s32 asset_id = resource_id;
    s32 wait_mode = wait_for_read;
    s32 result = 0;
    u8 *data;
    u8 *cd_params;
    s32 cached_id_abs;
    register s32 compare_id ASM_REG("$2");
    register s32 requested_id;
    register s32 id_high;
    s32 loaded_id;
    s32 read_size;
    s32 disc_offset;
    register s32 slot_base ASM_REG("$4") = resource_id;
    s32 asset_index;
    register s32 asset_offset;
    register s32 slot;
    ASM_KEEP_NV(entry);

    if (entry[0] != 2) {
        compare_id = D_800E3DA0[entry[3]];
        cached_id_abs = compare_id;
        if (compare_id < 0) {
            cached_id_abs = -cached_id_abs;
        }
        compare_id = (s16)slot_base;
        if ((cached_id_abs == compare_id) && (cached_id_abs != 0x39)) {
            entry[1] = asset_id;
        }
    }

    if (entry[1] == 0) {
        id_high = (u32)asset_id << 0x10;
        requested_id = id_high >> 0x10;
        if (requested_id == 0x38) {
            data = D_80164800;
            disc_offset = 0x56B1;
            ASM_KEEP(data);
            read_size = 0x24;
        } else if (requested_id == 0x31) {
            data = D_8016A800;
            disc_offset = 0x569C;
            read_size = 0x18;
        } else {
            slot = entry[3];
            read_size = 0xC;
            slot_base = slot * 3;
            data = D_80170800 - (slot_base << 13);
            asset_index = requested_id - 1;
            asset_offset = asset_index * 0x54;
            do {
                slot_base = (slot_base << 2) + 0x4340;
            } while (0);
            disc_offset = asset_offset + slot_base;
        }
        cd_params = D_800E58A8;
        func_8003F6D4(read_size, data, cd_params, disc_offset);
        Control_CD(6, cd_params, 0);

        if ((wait_mode << 0x10) != 0) {
            func_8003F320();
            if (entry[0] != 2) {
                D_800E3DA0[entry[3]] = asset_id;
            }
            result = *(s32 *)data;
            *(s32 *)(entry + 4) = result;
            goto done;
        }

        if (entry[0] != 2) {
            D_800E3DA0[entry[3]] = -asset_id;
            goto done;
        }
        goto done;
    }

    if (entry[0] != 2) {
        D_800E3DA0[entry[3]] = asset_id;
    }
    loaded_id = (s16)asset_id;
    if (loaded_id == 0x38) {
        data = D_80164800;
    } else if (loaded_id == 0x31) {
        data = D_8016A800;
    } else {
        data = D_80170800 - (entry[3] * 0x6000);
    }
    result = *(s32 *)data;

done:
    return result;
}
