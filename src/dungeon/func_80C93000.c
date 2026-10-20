#include "modules/dungeon_ovl_cb3000.h"

void func_8017087C(CB_8017087C_Object *object, s32 field60_value, CB_8017087C_CopyFields *source_coords)
{
    CB_8017087C_Part *part;
    CB_8017087C_CopyFields *copy;

    object->field60 = field60_value;
    register_node(object, project_sprite_chain);

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

