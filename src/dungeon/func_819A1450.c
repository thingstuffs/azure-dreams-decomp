#include "modules/dungeon_ovl_19c088c.h"

void func_80024C50(Row_819A1450_S_819A1450_4 *source, s32 unused_1, s32 unused_2, s16 offset_x, s16 offset_y,
                   s16 offset_z)
{
    Row_819A1450_LocalTable direction_table;
    void *node;
    Row_819A1450_S_819A1450_2 *part;
    Row_819A1450_S_819A1450_3 *coords;
    u8 *setup;
    s16 direction;

    direction_table = D_80024034;
    node = func_8003FC64(0x212);
    if (node != 0) {
        setup = (u8 *)node + 0x20;
        ((Row_819A1450_S_819A1450_0 *)setup)->unk_3A = 5;
        ((Row_819A1450_S_819A1450_0 *)setup)->unk_3C = 5;
        ((Row_819A1450_S_819A1450_1 *)node)->unk_10 = D_800246F0;
        func_8004491C(node, func_80045340);

        part = ((Row_819A1450_S_819A1450_1 *)node)->unk_0C;
        part->unk_10 = 0x20;
        part->unk_14 |= 0xC;
        part->unk_1A = (rand() & 7) << 9;
        part->unk_06 = 0;

        coords = ((Row_819A1450_S_819A1450_1 *)node)->unk_08;
        coords->unk_02 = offset_x;
        coords->unk_06 = offset_y;
        coords->unk_0A = offset_z;
        coords->unk_02 += source->unk_84;
        coords->unk_06 += source->unk_86;
        coords->unk_0A += source->unk_88;

        direction = source->unk_36;
        coords->unk_0C =
            (s32)direction_table.entries[direction].first << 20;
        direction = source->unk_36;
        coords->unk_10 =
            (s32)direction_table.entries[direction].second << 20;

        part = ((Row_819A1450_S_819A1450_1 *)node)->unk_0C;
        part->unk_1E = 0x800;
        part->unk_1C = 0x800;
        part->unk_0E = 0x80;
        part->unk_0D = 0x80;
        part->unk_0C = 0x80;
        func_8003DB94(part, D_800DEC00, 0);
    }
}
