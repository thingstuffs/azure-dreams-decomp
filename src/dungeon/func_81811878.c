#include "modules/dungeon_ovl_1831370.h"

void initialize_object_destination_fields(ovl_1831370_81811878_Source *src, ovl_1831370_81811878_Destinations *dst)
{
    *dst->dst0 = D_80029508[src->word10];
    *dst->dst4 = &src->word2C;
    set_indexed_object_field(dst, 0);
    *dst->dst8 = &src->word20;
    dst->dstC->unk0 = func_8004DC14(src->word14, 0);
    dst->dstC->unk4->unk8 = 0x68;
    dst->dstC->unk4->unkA = 0x88;
}
