#include "modules/dungeon_ovl_d54c.h"

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
