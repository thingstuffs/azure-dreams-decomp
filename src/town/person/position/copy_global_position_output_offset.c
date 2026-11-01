#include "shared/entity_objects.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 town_target_height_offset[];

/* Copy the global position to the output with an offset on the third component. */
void copy_global_position_output_offset(s32 unused, ObjectPosition *position_out) {
    position_out->x.v = view_reference_entity.x.v;
    position_out->y.v = view_reference_entity.y.v;
    position_out->z.v = view_reference_entity.z.v + town_target_height_offset[0];
}
