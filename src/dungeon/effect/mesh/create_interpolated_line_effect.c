#include "shared/object_node.h"
#include "common.h"

typedef struct ObjSub {
    u8 pad00[4];
    s32 x0;
    s32 y0;
    s32 z0;
    u8 pad10[0xC];
    s32 x1;
    s32 y1;
    s32 z1;
    u8 pad28[0xC];
    s32 x2;
    s32 y2;
    s32 z2;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s16 unk4C;
    s16 unk4E;
} ObjSub;

typedef struct Obj {
    u8 pad00[0x10];
    void *callback;
    u8 pad14[0xC];
    s32 arg;
} Obj;

extern s16 get_surface_height_at_record(void *);
extern void build_and_enqueue_interpolated_depth_sorted_shaded_lines_linked_list(Obj *);
extern u8 D_80025940[];
extern void *D_80026208;

/* Creates an object with height-adjusted endpoints and movement increments for 12 steps. */
void create_interpolated_line_effect(s32 object_arg, s32 *start_pos, s32 *end_pos)
{
    Obj *obj;
    ObjSub *motion;
    s32 end_z;
    s32 start_z;
    s32 step_z;
    s32 step_y;
    s32 z_value;
    s16 height;

    obj = (Obj *)allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->arg = object_arg;
        motion = (ObjSub *)&obj->arg;
        obj->callback = D_80025940;
        motion->unk4C = 0;
        motion->unk4E = 0;
        motion->x1 = start_pos[0];
        motion->x2 = motion->x1;
        motion->y1 = start_pos[1];
        motion->y2 = motion->y1;
        height = get_surface_height_at_record(start_pos);
        if (height >= 0x201) {
            z_value = start_pos[2];
        } else {
            z_value = height << 16;
        }
        motion->z1 = z_value;
        motion->z2 = z_value;
        motion->x0 = end_pos[0];
        motion->y0 = end_pos[1];
        height = get_surface_height_at_record(end_pos);
        if (height >= 0x201) {
            motion->z0 = start_pos[2];
        } else {
            motion->z0 = height << 16;
        }
        motion->unk40 = (end_pos[0] - start_pos[0]) / 12;
        end_z = motion->z0;
        start_z = motion->z1;
        D_80026208 = &motion->x2;
        step_z = (end_z - start_z) / 12;
        step_y = (end_pos[1] - start_pos[1]) / 12;
        motion->unk48 = step_z;
        motion->unk44 = step_y;
        build_and_enqueue_interpolated_depth_sorted_shaded_lines_linked_list(obj);
    }
}
