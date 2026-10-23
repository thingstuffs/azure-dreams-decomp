#ifndef TOWN_SCENE_COLLISION_H
#define TOWN_SCENE_COLLISION_H

#include "shared/entity.h"

/* Linked-collider records used by the overlap resolver and its three responses.
 * The resolver loads bounds/position through +0x0C/+0x08. Each response stores
 * the other collider into the selected +0x1C slot and increments +0x3A + face.
 * These are observed extents; the allocation size is not established here. */
typedef struct CollisionBounds {
    int offset_x, offset_y, offset_z;
    int size_x, size_y, size_z;
} CollisionBounds;

typedef struct ColliderView {
    /* 0x00 */ void *unused_00;
    /* 0x04 */ struct ColliderView *linked;
    /* 0x08 */ ObjectPosition *position;
    /* 0x0C */ CollisionBounds *bounds;
    /* 0x10 */ unsigned char pad_10[5];
    /* 0x15 */ unsigned char enabled;
    /* 0x16 */ unsigned char pad_16[6];
    /* 0x1C */ struct ColliderView *slots[6];
    /* 0x34 */ unsigned char response_flags[6];
    /* 0x3A */ unsigned char pending_flags[6];
} ColliderView;

/* Scratchpad record at 0x1F800000. Near/far are the signed separations computed
 * for each axis; the chosen face indices select the collider's six slots. */
typedef struct CollisionScratch {
    /* 0x00 */ CollisionBounds *self_bounds;
    /* 0x04 */ ColliderView *other;
    /* 0x08 */ ObjectPosition *other_position;
    /* 0x0C */ CollisionBounds *other_bounds;
    /* 0x10 */ int x_near, x_far;
    /* 0x18 */ int y_near, y_far;
    /* 0x20 */ int z_near, z_far;
    /* 0x28 */ unsigned char face_x, face_y, face_z, pad_2B;
    /* 0x2C */ int axis_x, axis_y, axis_z;
    /* 0x38 */ int face_index;
} CollisionScratch;

void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(ColliderView *collider, ObjectPosition *position);
void apply_the_entry_adjustment_increment_slot_count_store_slot(ColliderView *collider, ObjectPosition *position, CollisionScratch *entry);
void update_first_axis_slot_value(ColliderView *collider, ObjectPosition *position, CollisionScratch *entry);
void update_second_axis_slot_value(ColliderView *collider, ObjectPosition *position, CollisionScratch *entry);

#endif
