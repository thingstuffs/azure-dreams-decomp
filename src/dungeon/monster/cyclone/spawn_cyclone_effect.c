#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

typedef struct {
    s32 word[6];
} Copy24;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u16;

extern s32 resolve_record_orientation_or_fallback();
extern void register_node();
extern void select_sprite_entry();

extern s32 cyclone_spawn_update_address;

typedef struct S_80E122F4_0 {
    u8 pad_00[0x60];
    void * unk_60;
} S_80E122F4_0;   /* owner in func_80E122F4 */

typedef struct S_80E122F4_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x1C];
    s32 unk_28;
} S_80E122F4_2;   /* source_obj in func_80E122F4 */

typedef struct S_80E122F4_3 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_0C;   /* overlapping accesses */
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
} S_80E122F4_3;   /* part in func_80E122F4 */

   /* coords in func_80E122F4 */

typedef struct S_80E122F4_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80E122F4_5;   /* reference in func_80E122F4 */

typedef struct S_80E122F4_6_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80E122F4_6_pre;   /* the 0x18 bytes before ((S_80E122F4_0 *)owner)->unk_60 in func_80E122F4, addressed as ((S_80E122F4_0 *)owner)->unk_60[-1] */

typedef struct S_80E122F4_6 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80E122F4_6;   /* ((S_80E122F4_0 *)owner)->unk_60 in func_80E122F4 */

/* Spawn a 0x312 effect object at the source's position, offset into the owner's room and depth-sorted against the camera. */
void *create_source_to_owner_sprite(S_80E122F4_0 *owner, void *transform, void *source)
{
    Vec3u16 offset;
    S_80E122F4_5 *reference;
    ObjectNodeHeader * obj;
    S_80E122F4_2 *source_obj;
    MovingPosition *coords;
    SpriteFrameState *child;
    S_80E122F4_3 *part;
    s32 delta;

    source_obj = source;
    reference = ((S_80E122F4_6_pre *)(owner->unk_60))[-1].unk_00;
    obj = allocate_flagged_object_node(0x312);
    if (obj != 0) {
        (obj->update_callback) = &cyclone_spawn_update_address;
        register_node(obj, project_sprite_chain);

        child = (obj->sprite);
        child->animation_resource = source_obj->unk_28;
        child->scale_y = 0x800;
        child->scale_x = 0x800;
        child->color.word = 0x808080;
        child->flags |= 0xC;
        child->tpage_abr |= 0x20;
        select_sprite_entry(child, 0x47, 0);

        coords = (obj->position);
        (*(Copy24 *)((u8 *)obj + 0x24)) = *(Copy24 *)transform;

        offset.z = 0;
        offset.y = 0;
        offset.x = 0;
        part = (u8 *)obj + 0x20;
        if (resolve_record_orientation_or_fallback(source_obj->unk_08, source_obj, &offset, 1) != 0) {
            part->unk_04.at02.v += offset.x;
            coords->x = part->unk_04.at02.v;
            part->unk_08.at02.v += offset.y;
            coords->y = part->unk_08.at02.v;
            part->unk_0C.at02.v += offset.z;
            coords->z = part->unk_0C.at02.v;
        }

        delta = reference->unk_00 - part->unk_04.at00.v;
        if (delta < 0) {
            delta += 31;
        }
        delta >>= 5;
        part->unk_10 = delta;
        delta = reference->unk_04 - part->unk_08.at00.v;
        if (delta < 0) {
            delta += 31;
        }
        delta >>= 5;
        part->unk_14 = delta;
        delta = (reference->unk_08 -
                 ((s32)entity_height_offsets[((S_80E122F4_6 *)(owner->unk_60))->unk_13] << 15) -
                 part->unk_0C.at00.v) / 32;
        part->unk_18 = delta;
        return obj;
    }
    return 0;
}

/* MECHANISM: Reverse-order Vec3 zero stores and explicit negative-add-31/shift CFGs reproduce retail
   scheduling. The row's own `j` to its epilogue is spelled honestly as `return obj;`. */
