#include "modules/dungeon_floor_generate.h"

void load_floor_spawn_tables(s16 resource_index)
{
    s32 load_result;
    u8 *resource_data;

    resource_data = (u8 *)&D_8014A000;
    pack_tagged_resource_descriptor(1, resource_data, &load_result, resource_index + 0x3F5E);
    Control_CD(6, &load_result, 0);
    drain_cd_command_queue();
    *(floor_generate_isolated_802864C4_Copy32 *)g_dungeon_status.unk_18 = D_8014A000;
    (*(floor_generate_isolated_802864C4_Copy32 *)D_800DDC9C) = *(floor_generate_isolated_802864C4_Copy32 *)(resource_data + 0x20);
    D_8001F584 = resource_data[0x40];
}

/* MECHANISM: Packed 32-byte assignments express both retail unaligned copies.
   Mixing one direct D_8014A000 copy with a held full-address local creates the retail
   s1 high-page and s0 full-address roles, 0x28 frame, and 3+3+2 copy-register chunks. */
