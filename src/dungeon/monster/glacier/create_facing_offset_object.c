#include "shared/sprite_frame_state.h"
#include "shared/actor_status_flags.h"

struct ObjectPosition;
#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/slus_callbacks.h"

typedef struct {
    s32 value0;
    s32 value4;
    s32 value8;
} PayloadObject;

typedef struct {
    u8 pad0[6];
    s16 field6;
    void *ptr8;
    u8 fieldc;
    u8 fieldd;
    u8 fielde;
    u8 padf;
    s16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    s16 field1c;
    s16 field1e;
} ChildObject;

typedef struct {
    u8 pad0[0x1a];
    u16 angle_copy;
    s16 angle_index;
    u8 pad1e[0xa];
    void *owner;
    s32 field2c;
    void *field30;
    u8 pad34[0x18];
    s8 field4c;
    s8 field4d;
} BlockObject;

typedef struct {
    u8 pad0[8];
    PayloadObject *payload;
    ChildObject *child;
    u8 *resource10;
    u8 pad14[0x40];
    u32 copy54[3];
} AllocationObject;

typedef struct {
    u8 pad0[0x2a];
    u16 angle;
} Arg0Object;

typedef struct {
    u8 pad0[0xa];
    u16 height;
} Arg1Object;

typedef struct {
    u8 pad0[0x24];
    u8 x24;
    u8 y25;
} Arg2Object;

typedef struct {
    u8 bytes[12];
} Copy12;

typedef struct {
    u8 pad0[0xc];
    void *child;
} SecondaryObject;

typedef struct {
    u8 pad0[0x24];
    u8 x24;
    u8 y25;
} SecondaryChild;

typedef struct {
    u8 pad0[0x14];
    u32 flags14;
    u8 pad18[4];
    u32 flags1c;
} SecondaryBlock;

extern u8 glacier_object_callback_2[];
extern u8 glacier_direction_offsets[];
extern u8 D_8017612C[];

extern void register_node(AllocationObject *allocation, void *callback);
extern void update_map_cell_flags_with_item_limit(u8 x, u8 y, s32 mode);
extern s32 sample_terrain_surface_height(u16 x, u16 y, s16 height);
extern void select_nearby_target_and_initialize_slot(s32 slot_id,struct ObjectPosition *target, s32 target_id, s16 slot_value);
extern void *find_nearby_eligible_entry(u8 *current, s32 wanted_24, s32 wanted_25, s32 height_center);

/* Creates an object offset from the origin in the owner's facing direction and links its secondary object. */
void create_facing_offset_object(Arg0Object *owner, Arg1Object *height_source, Arg2Object *origin) {
    ObjectNodeHeader *allocated;
    BlockObject *block;
    ObjectPosition *payload;
    SpriteFrameState *child;
    s32 mode;
    u8 secondary_x;
    u8 secondary_y;
    SecondaryChild *secondary_child;
    SecondaryBlock *secondary_block;
    void *secondary;

    allocated = allocate_flagged_object_node(0x212);
    if (allocated != 0) {
        block = (BlockObject *)((u8 *)allocated + 0x20);
        block->owner = owner;
        block->field30 = 0;
        block->field2c = 0;
        allocated->update_callback = glacier_object_callback_2;
        register_node(allocated, project_sprite_chain);
        child = allocated->sprite;
        child->tpage_abr = 0x20;
        child->flags |= 0xc;
        block->field4c = (s8)(origin->x24 + glacier_direction_offsets[(owner->angle >> 7) & 0x1c]);
        {
            u8 origin_y = origin->y25;
            u16 angle = owner->angle;
            u8 *direction_offset = glacier_direction_offsets + ((angle >> 7) & 0x1c);
            block->field4d = (s8)(origin_y + direction_offset[2]);
        }
        child->depth_bias = 6;
        payload = allocated->position;
        payload->x.v = (((block->field4c << 6) + 0x20) << 0x10);
        payload->y.v = (((block->field4d << 6) + 0x20) << 0x10);
        payload->z.v = sample_terrain_surface_height(*(u16 *)((u8 *)payload + 2), *(u16 *)&payload->y.w.i,
            (s16)(height_source->height - 0x20)) << 0x10;
        block->angle_copy = owner->angle;
        block->angle_index = (owner->angle >> 9) & 7;
        child = allocated->sprite;
        child->scale_x = 0x2400;
        child->scale_y = 0x1c00;
        child->color.c.b = 0;
        child->color.c.g = 0;
        child->color.c.r = 0;
        *(Copy12 *)((u8 *)allocated + 0x54) = *(Copy12 *)D_8017612C;
        child->source = (u8 *)allocated + 0x54;
        secondary = find_nearby_eligible_entry(owner, (u16)(s8)block->field4c, (u16)(s8)block->field4d, payload->z.w.i);
        block->field30 = secondary;
        if (secondary != 0) {
            secondary_block = (SecondaryBlock *)((u8 *)secondary + 0x20);
            secondary_child = ((SecondaryObject *)secondary)->child;
            secondary_block->flags14 |= 0x100000;
            secondary_x = secondary_child->x24;
            secondary_y = secondary_child->y25;
            if (secondary_block->flags1c & ACTOR_PLAYER_SIDE) {
                mode = 0x300;
            } else {
                mode = 0x3000;
            }
            update_map_cell_flags_with_item_limit(secondary_x, secondary_y, mode);
        }
        select_nearby_target_and_initialize_slot(allocated, payload, 8, 0x300);
    }
}
