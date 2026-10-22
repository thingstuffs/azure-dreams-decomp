#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"

typedef struct {
    u32 words[6];
} Copy24;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u16;

extern void register_node(void *object, void *callback);
extern void select_sprite_entry(void *object, s32 kind, s32 value);
extern void *resolve_record_orientation_or_fallback(void *ptr, void *ptr1, Vec3u16 *out, s32 value3);

extern u8 D_80175978;

typedef struct S_80175D04_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x86];
    s16 unk_B2;
} S_80175D04_0;   /* arg0 in create_source_adjusted_motion_object */

typedef struct S_80175D04_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_80175D04_1;   /* &local in create_source_adjusted_motion_object */

typedef struct S_80175D04_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x1C];
    s32 unk_28;
} S_80175D04_3;   /* source in create_source_adjusted_motion_object */

typedef struct S_80175D04_4 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    u16 unk_0E;
    s32 unk_10;
    s32 unk_14;
} S_80175D04_4;   /* out in create_source_adjusted_motion_object */

   /* child in create_source_adjusted_motion_object */

/* Creates an object with a source-adjusted position and motion toward a directional target. */
void *create_source_adjusted_motion_object(S_80175D04_0 *actor, Copy24 *start_pos, S_80175D04_3 *source)
{
    Copy24 target_pos;
    Vec3u16 source_offset;
    u16 direction_bits;
    s32 direction_offset;
    s16 axis_step;
    Copy24 *motion;
    ObjectNodeHeader * object;
    MovingPosition *child_pos;
    SpriteFrameState *render;

    direction_bits = actor->unk_2A;
    target_pos = *start_pos;
    direction_offset = (direction_bits >> 8) & 0xE;

    axis_step = *(s16 *)((u8 *)((u8 *)dir_step_x) + direction_offset);
    ((S_80175D04_1 *)(&target_pos))->unk_02 +=
        (axis_step * actor->unk_B2 * 0x40) +
        (axis_step * 0x20);

    axis_step = *(s16 *)((u8 *)((u8 *)dir_step_y) + direction_offset);
    ((S_80175D04_1 *)(&target_pos))->unk_06 +=
        (axis_step * actor->unk_B2 * 0x40) +
        (axis_step * 0x20);

    object = allocate_flagged_object_node(0x312);
    if (object != 0) {
        (object->unk_10) = &D_80175978;
        register_node(object, project_sprite_chain);

        render = (object->sprite);
        render->unk_28 = source->unk_28;
        render->scale_y = 0x800;
        render->scale_x = 0x800;
        render->color.word = 0x00808080;
        render->flags |= 0xC;
        render->tpage_abr |= 0x20;
        select_sprite_entry(render, 0x47, 0);

        child_pos = (object->position);
        (*(Copy24 *)((u8 *)object + 0x24)) = *start_pos;
        motion = (Copy24 *)((u8 *)object + 0x20);

        source_offset.z = 0;
        source_offset.y = 0;
        source_offset.x = 0;
        if (resolve_record_orientation_or_fallback(source->unk_08, source, &source_offset, 1) != 0) {
            ((S_80175D04_4 *)motion)->unk_04.at02.v += source_offset.x;
            child_pos->unk_02 = ((S_80175D04_4 *)motion)->unk_04.at02.v;
            ((S_80175D04_4 *)motion)->unk_08.at02.v += source_offset.y;
            child_pos->unk_06 = ((S_80175D04_4 *)motion)->unk_08.at02.v;
            ((S_80175D04_4 *)motion)->unk_0E += source_offset.z;
            child_pos->unk_0A = ((S_80175D04_4 *)motion)->unk_0E;
        }

        ((S_80175D04_4 *)motion)->unk_10 =
            ((s32)target_pos.words[0] - ((S_80175D04_4 *)motion)->unk_04.at00.v) / 0x20;
        ((S_80175D04_4 *)motion)->unk_14 =
            ((s32)target_pos.words[1] - ((S_80175D04_4 *)motion)->unk_08.at00.v) / 0x20;

        return object;
    }

    return 0;
}
