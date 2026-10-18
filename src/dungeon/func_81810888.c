#include "modules/dungeon_ovl_1830850.h"

void inventory_set_paired_index_offset(ovl_1830850_81810888_S_80025888_0 *pair, s32 index) {
    s16 offset;

    offset = (index * 0x10) - 0x38;
    ((ovl_1830850_81810888_S_80025888_3 *)(((ovl_1830850_81810888_S_80025888_1 *)(pair->unk_04))->unk_04))->unk_0A = offset;
    ((ovl_1830850_81810888_S_80025888_4 *)(((ovl_1830850_81810888_S_80025888_2 *)(pair->unk_08))->unk_04))->unk_0A = offset;
}
