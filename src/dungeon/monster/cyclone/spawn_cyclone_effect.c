#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "dungeon/monster/cyclone.h"
#include "dungeon/monster/cyclone/bobbing_motion.h"

typedef struct {
    s32 word[6];
} Copy24;

extern s32 cyclone_spawn_update_address;

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


/* Spawn a 0x312 effect object at the source's position, offset into the owner's room and depth-sorted against the camera. */
void *create_source_to_owner_sprite(ActorRecord *owner, ObjectPosition *position, SpriteFrameState *sprite)
{
    GteOffset offset;
    S_80E122F4_5 *reference;
    ObjectNodeHeader * obj;
    SpriteFrameState *source_obj;
    ObjectPosition *coords;
    SpriteFrameState *child;
    CycloneBobbingMotionBody *part;
    s32 delta;

    source_obj = sprite;
    reference = ((S_80E122F4_6_pre *)(owner->target))[-1].unk_00;
    obj = allocate_flagged_object_node(0x312);
    if (obj != 0) {
        (obj->update_callback) = &cyclone_spawn_update_address;
        register_node(obj, project_sprite_chain);

        child = obj->sprite;
        child->animation_resource = source_obj->animation_resource;
        child->scale_y = 0x800;
        child->scale_x = 0x800;
        child->color.word = 0x808080;
        child->flags |= 0xC;
        child->tpage_abr |= 0x20;
        select_sprite_entry(child, 0x47, 0);

        coords = obj->position;
        (*(Copy24 *)((u8 *)obj + 0x24)) = *(Copy24 *)position;

        offset.distance[2] = 0;
        offset.distance[1] = 0;
        offset.distance[0] = 0;
        part = NODE_BODY(obj);
        if (resolve_record_orientation_or_fallback(source_obj->source, source_obj, &offset.orientation, 1) != 0) {
            part->path.x.unsigned_parts.integer += offset.distance[0];
            coords->x.w.i = part->path.x.unsigned_parts.integer;
            part->path.y.unsigned_parts.integer += offset.distance[1];
            coords->y.w.i = part->path.y.unsigned_parts.integer;
            part->path.z.unsigned_parts.integer += offset.distance[2];
            coords->z.w.i = part->path.z.unsigned_parts.integer;
        }

        delta = reference->unk_00 - part->path.x.v;
        if (delta < 0) {
            delta += 31;
        }
        delta >>= 5;
        part->path.velocity_x = delta;
        delta = reference->unk_04 - part->path.y.v;
        if (delta < 0) {
            delta += 31;
        }
        delta >>= 5;
        part->path.velocity_y = delta;
        delta = (reference->unk_08 -
                 ((s32)entity_height_offsets[((ActorRecord *)(owner->target))->species] << 15) -
                 part->path.z.v) / 32;
        part->path.velocity_z = delta;
        return obj;
    }
    return 0;
}

/* MECHANISM: Reverse-order Vec3 zero stores and explicit negative-add-31/shift CFGs reproduce retail
   scheduling. The row's own `j` to its epilogue is spelled honestly as `return obj;`. */
