#include "modules/dungeon_ovl_19a332c.h"

void inventoryCopyAndSignExtendRecordFields(ovl_19a332c_81984A40_Dest81984A40 *dst, ovl_19a332c_81984A40_Source81984A40 *src)
{
    s32 sourceHalfword;

    dst->words = src->words;
    sourceHalfword = src->field_10;
    dst->field_10 = sourceHalfword;
    dst->field_14 = src->field_12;
    dst->field_18 = src->field_13;
    dst->field_1C = src->field_14;
}
