#include "common.h"
#include "town/scene/collision.h"
#include "shared/entity.h"
extern int abs(int);



/*
 * Walks the collider ring, rejects disabled or separated boxes, and dispatches overlapping boxes
 * to an axis response using the signed face separations. Prefers the Z response when vertical
 * motion covers its separation; otherwise chooses the least penetration, then clears the per-face
 * response flags.
 */
void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(ColliderView *collider, ObjectPosition *position) {
    CollisionScratch *scratch;
    CollisionBounds *bounds;
    CollisionBounds *other_bounds;
    s32 shift_x;
    s32 shift_y;
    s32 shift_z;
    s32 min_separation;
    s32 face_index;
    s32 self_size;
    void *box_operand;
    register s32 axis_operand;

    bounds = collider->bounds;
    scratch = (CollisionScratch *)0x1F800000;
    scratch->face_index = 0;
    scratch->self_bounds = bounds;
    do {
        collider->pending_flags[scratch->face_index] = 0;
        face_index = scratch->face_index + 1;
        scratch->face_index = face_index;
    } while (face_index < 6);

    scratch->other = collider->linked;
    for (; scratch->other != collider; scratch->other = scratch->other->linked) {
        {
            ColliderView *other;
            ColliderView *object_ref;

            scratch->other_position = scratch->other->position;
            other = scratch->other;
            other_bounds = other->bounds;
            scratch->other_bounds = other_bounds;
            object_ref = scratch->other;
            if (object_ref->enabled == 0) {
                continue;
            }
        }

        {
            CollisionBounds *self_box;
            s32 self_offset;
            s32 other_edge;
            s32 other_offset;

            self_box = scratch->self_bounds;
            do {
                min_separation = position->x.v;
            } while (0);
            self_offset = self_box->offset_x;
            axis_operand = (s32)scratch->other_position;
            min_separation += self_offset;
            other_edge = ((EntityRec *)(axis_operand))->x.v;
            other_offset = other_bounds->offset_x;
            box_operand = (void *)other_bounds->size_x;
            other_edge += other_offset;
            other_edge += (s32)box_operand;
            min_separation -= other_edge;
            scratch->x_near = min_separation;
            if (min_separation > 0) {
                continue;
            }
        }

        {
            void *other_pos;
            s32 separation;
            s32 other_edge;

            box_operand = scratch->self_bounds;
            separation = position->x.v;
            other_pos = (void *)((CollisionBounds *)(box_operand))->offset_x;
            self_size = ((CollisionBounds *)(box_operand))->size_x;
            box_operand = scratch->other_bounds;
            separation += (s32)other_pos;
            other_pos = scratch->other_position;
            box_operand = (void *)((CollisionBounds *)(box_operand))->offset_x;
            other_edge = ((EntityRec *)(other_pos))->x.v;
            separation += self_size;
            other_edge += (s32)box_operand;
            separation -= other_edge;
            scratch->x_far = separation;
            if (separation < 0) {
                continue;
            }
        }

        {
            CollisionBounds *self_box;
            void *other_pos;
            CollisionBounds *other_box;
            s32 self_offset;
            s32 other_edge;

            self_box = scratch->self_bounds;
            do {
                min_separation = position->y.v;
                self_offset = self_box->offset_y;
            } while (0);
            other_box = scratch->other_bounds;
            min_separation += self_offset;
            other_pos = scratch->other_position;
            box_operand = (void *)other_box->offset_y;
            other_edge = ((EntityRec *)(other_pos))->y.v;
            axis_operand = other_box->size_y;
            other_edge += (s32)box_operand;
            other_edge += axis_operand;
            min_separation -= other_edge;
            scratch->y_near = min_separation;
            if (min_separation > 0) {
                continue;
            }
        }

        {
            void *other_pos;
            s32 separation;
            s32 other_edge;

            box_operand = scratch->self_bounds;
            separation = position->y.v;
            other_pos = (void *)((CollisionBounds *)(box_operand))->offset_y;
            self_size = ((CollisionBounds *)(box_operand))->size_y;
            box_operand = scratch->other_bounds;
            separation += (s32)other_pos;
            other_pos = scratch->other_position;
            box_operand = (void *)((CollisionBounds *)(box_operand))->offset_y;
            other_edge = ((EntityRec *)(other_pos))->y.v;
            separation += self_size;
            other_edge += (s32)box_operand;
            separation -= other_edge;
            scratch->y_far = separation;
            if (separation < 0) {
                continue;
            }
        }

        {
            CollisionBounds *self_box;
            void *other_pos;
            CollisionBounds *other_box;
            s32 self_offset;
            s32 other_edge;

            self_box = scratch->self_bounds;
            do {
                min_separation = position->z.v;
                self_offset = self_box->offset_z;
            } while (0);
            other_box = scratch->other_bounds;
            min_separation += self_offset;
            other_pos = scratch->other_position;
            box_operand = (void *)other_box->offset_z;
            other_edge = ((EntityRec *)(other_pos))->z.v;
            axis_operand = other_box->size_z;
            other_edge += (s32)box_operand;
            other_edge += axis_operand;
            min_separation -= other_edge;
            scratch->z_near = min_separation;
            if (min_separation > 0) {
                continue;
            }
        }

        {
            void *other_pos;
            s32 separation;
            s32 other_edge;

            box_operand = scratch->self_bounds;
            separation = position->z.v;
            other_pos = (void *)((CollisionBounds *)(box_operand))->offset_z;
            self_size = ((CollisionBounds *)(box_operand))->size_z;
            box_operand = scratch->other_bounds;
            separation += (s32)other_pos;
            other_pos = scratch->other_position;
            box_operand = (void *)((CollisionBounds *)(box_operand))->offset_z;
            other_edge = ((EntityRec *)(other_pos))->z.v;
            separation += self_size;
            other_edge += (s32)box_operand;
            separation -= other_edge;
            scratch->z_far = separation;
            if (separation < 0) {
                continue;
            }
        }

        {
            s32 max_shift;
            s32 max_depth;

            axis_operand = scratch->x_near;
            max_shift = scratch->x_far;
            axis_operand = abs(axis_operand);
            max_depth = max_shift;
            max_depth = abs(max_depth);
            axis_operand = axis_operand < max_depth;
            if (axis_operand) {
                scratch->face_x = collider->response_flags[3];
                scratch->axis_x = 2;
            } else {
                scratch->x_near = max_shift;
                scratch->face_x = collider->response_flags[2];
                scratch->axis_x = 3;
            }

            axis_operand = scratch->y_near;
            max_shift = scratch->y_far;
            axis_operand = abs(axis_operand);
            max_depth = max_shift;
            max_depth = abs(max_depth);
            axis_operand = axis_operand < max_depth;
            if (axis_operand) {
                scratch->face_y = collider->response_flags[5];
                scratch->axis_y = 4;
            } else {
                scratch->y_near = max_shift;
                scratch->face_y = collider->response_flags[4];
                scratch->axis_y = 5;
            }

            axis_operand = scratch->z_near;
            max_shift = scratch->z_far;
            axis_operand = abs(axis_operand);
            max_depth = max_shift;
            max_depth = abs(max_depth);
            axis_operand = axis_operand < max_depth;
            if (axis_operand) {
                scratch->face_z = collider->response_flags[1];
                scratch->axis_z = 0;
            } else {
                scratch->z_near = max_shift;
                scratch->face_z = collider->response_flags[0];
                scratch->axis_z = 1;
            }
        }

        shift_x = scratch->x_near;
        if (shift_x == 0) {
            if (scratch->y_near == 0) {
                continue;
            }
            if (scratch->z_near == 0) {
                continue;
            }
        }
        shift_y = scratch->y_near;
        if (shift_y == 0 && scratch->z_near == 0) {
            continue;
        }
        shift_z = scratch->z_near;
        if (shift_z > 0 && position->velocity_z >= shift_z && shift_x != 0 && shift_y != 0) {
            update_second_axis_slot_value(collider, position, scratch);
            continue;
        }
        {
            s32 abs_x;
            s32 y_depth;
            s32 z_depth;
            s32 abs_z;

            abs_x = abs(scratch->x_near);
            y_depth = abs(scratch->y_near);
            if (abs_x < y_depth) {
                z_depth = scratch->z_near;
                abs_z = z_depth;
                abs_z = abs(abs_z);
                z_depth = y_depth < abs_z;
                if (!z_depth) {
                    z_depth = abs_x < abs_z;
                    if (!z_depth) {
                        update_second_axis_slot_value(collider, position, scratch);
                        continue;
                    }
                }
                apply_the_entry_adjustment_increment_slot_count_store_slot(collider, position, scratch);
                continue;
            }
            z_depth = scratch->z_near;
            z_depth = abs(z_depth);
            if (y_depth >= z_depth) {
                update_second_axis_slot_value(collider, position, scratch);
                continue;
            }
            update_first_axis_slot_value(collider, position, scratch);
        }
    }

    scratch->face_index = 0;
    do {
        collider->response_flags[scratch->face_index] = 0;
        face_index = scratch->face_index + 1;
        scratch->face_index = face_index;
    } while (face_index < 6);
}
