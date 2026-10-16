#include "modules/dungeon_ovl_cd7000.h"

void func_8014C87C(CL_CD7000_8017087C_Object *object, s32 field60_value, CL_CD7000_8017087C_CopyFields *source_coords)
{
    CL_CD7000_8017087C_Part *part;
    CL_CD7000_8017087C_CopyFields *copy;

    object->field60 = field60_value;
    func_8004491C(object, func_80045340);

    part = object->part;
    part->field10 = 0x20;
    part->field14 |= 0xC;

    copy = object->copy;
    copy->x = source_coords->x;
    copy->y = source_coords->y;
    copy->z = source_coords->z;

    part = object->part;
    part->field1E = 0x1000;
    part->field1C = 0x1000;
    part->b = 0x80;
    part->g = 0x80;
    part->r = 0x80;
}

