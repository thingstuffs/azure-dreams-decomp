#include "modules/dungeon_ovl_cd7000.h"
#include "shared/sprite_frame_state.h"

void func_8014C87C(CL_CD7000_8017087C_Object *object, s32 field60_value, CL_CD7000_8017087C_CopyFields *source_coords)
{
    SpriteFrameState *part;
    CL_CD7000_8017087C_CopyFields *copy;

    object->field60 = field60_value;
    register_node(object, project_sprite_chain);

    part = object->part;
    part->tpage_abr = 0x20;
    part->flags |= 0xC;

    copy = object->copy;
    copy->x = source_coords->x;
    copy->y = source_coords->y;
    copy->z = source_coords->z;

    part = object->part;
    part->scale_y = 0x1000;
    part->scale_x = 0x1000;
    part->color.c.b = 0x80;
    part->color.c.g = 0x80;
    part->color.c.r = 0x80;
}

