#include "common.h"
#include "shared/entity.h"
extern int abs(int);


extern void townApplyTheEntryAdjustmentIncrementSlotCountStoreSlot(void *, void *, void *);
extern void func_8008F5B4(void *, void *, void *);
extern void func_8008F60C(void *, void *, void *);

typedef struct CollisionBounds {
    s32 offset_x, offset_y, offset_z;
    s32 size_x, size_y, size_z;
} CollisionBounds;

typedef struct ColliderView {
    void *unused_00;
    void *linked;
    void *position;
    void *bounds;
    u8 pad_10[5];
    u8 enabled;
    u8 pad_16[0x1E];
    u8 response_flags[6];
    u8 pending_flags[6];
} ColliderView;

typedef struct CollisionScratch {
    void *self_bounds;
    void *other;
    void *other_position;
    void *other_bounds;
    s32 x_near, x_far;
    s32 y_near, y_far;
    s32 z_near, z_far;
    u8 face_x, face_y, face_z, pad_2B;
    s32 axis_x, axis_y, axis_z;
    s32 face_index;
} CollisionScratch;

/* Resolve bounding-box overlaps with linked colliders along the least-penetrating axis. */
void townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(void *collider, void *position) {
    u8 *scratch;
    void *bounds;
    void *other_bounds;
    s32 shift_x;
    s32 shift_y;
    s32 shift_z;
    s32 min_separation;
    s32 face_index;
    s32 self_size;
    void *box_operand;
    register s32 axis_operand;

    bounds = ((ColliderView *)(collider))->bounds;
    scratch = (u8 *)0x1F800000;
    ((CollisionScratch *)scratch)->face_index = 0;
    ((CollisionScratch *)scratch)->self_bounds = bounds;
    do {
        ((ColliderView *)collider)->pending_flags[((CollisionScratch *)scratch)->face_index] = 0;
        face_index = ((CollisionScratch *)scratch)->face_index + 1;
        ((CollisionScratch *)scratch)->face_index = face_index;
    } while (face_index < 6);

    ((CollisionScratch *)scratch)->other = ((ColliderView *)(collider))->linked;
    for (; ((CollisionScratch *)scratch)->other != collider; ((CollisionScratch *)scratch)->other = ((ColliderView *)(((CollisionScratch *)scratch)->other))->linked) {
        {
            void *other;
            void *object_ref;

            ((CollisionScratch *)scratch)->other_position = ((ColliderView *)(((CollisionScratch *)scratch)->other))->position;
            other = ((CollisionScratch *)scratch)->other;
            other_bounds = ((ColliderView *)(other))->bounds;
            ((CollisionScratch *)scratch)->other_bounds = other_bounds;
            object_ref = ((CollisionScratch *)scratch)->other;
            if (((ColliderView *)(object_ref))->enabled == 0) {
                continue;
            }
        }

        {
            void *self_box;
            s32 self_offset;
            s32 other_edge;
            s32 other_offset;

            self_box = ((CollisionScratch *)scratch)->self_bounds;
            do {
                min_separation = ((EntityRec *)(position))->x.v;
            } while (0);
            self_offset = ((CollisionBounds *)(self_box))->offset_x;
            axis_operand = (s32)((CollisionScratch *)scratch)->other_position;
            min_separation += self_offset;
            other_edge = ((EntityRec *)(axis_operand))->x.v;
            other_offset = ((CollisionBounds *)(other_bounds))->offset_x;
            box_operand = (void *)((CollisionBounds *)(other_bounds))->size_x;
            other_edge += other_offset;
            other_edge += (s32)box_operand;
            min_separation -= other_edge;
            ((CollisionScratch *)scratch)->x_near = min_separation;
            if (min_separation > 0) {
                continue;
            }
        }

        {
            void *other_pos;
            s32 separation;
            s32 other_edge;

            box_operand = ((CollisionScratch *)scratch)->self_bounds;
            separation = ((EntityRec *)(position))->x.v;
            other_pos = (void *)((CollisionBounds *)(box_operand))->offset_x;
            self_size = ((CollisionBounds *)(box_operand))->size_x;
            box_operand = ((CollisionScratch *)scratch)->other_bounds;
            separation += (s32)other_pos;
            other_pos = ((CollisionScratch *)scratch)->other_position;
            box_operand = (void *)((CollisionBounds *)(box_operand))->offset_x;
            other_edge = ((EntityRec *)(other_pos))->x.v;
            separation += self_size;
            other_edge += (s32)box_operand;
            separation -= other_edge;
            ((CollisionScratch *)scratch)->x_far = separation;
            if (separation < 0) {
                continue;
            }
        }

        {
            void *self_box;
            void *other_pos;
            void *other_box;
            s32 self_offset;
            s32 other_edge;

            self_box = ((CollisionScratch *)scratch)->self_bounds;
            do {
                min_separation = ((EntityRec *)(position))->y.v;
                self_offset = ((CollisionBounds *)(self_box))->offset_y;
            } while (0);
            other_box = ((CollisionScratch *)scratch)->other_bounds;
            min_separation += self_offset;
            other_pos = ((CollisionScratch *)scratch)->other_position;
            box_operand = (void *)((CollisionBounds *)(other_box))->offset_y;
            other_edge = ((EntityRec *)(other_pos))->y.v;
            axis_operand = ((CollisionBounds *)(other_box))->size_y;
            other_edge += (s32)box_operand;
            other_edge += axis_operand;
            min_separation -= other_edge;
            ((CollisionScratch *)scratch)->y_near = min_separation;
            if (min_separation > 0) {
                continue;
            }
        }

        {
            void *other_pos;
            s32 separation;
            s32 other_edge;

            box_operand = ((CollisionScratch *)scratch)->self_bounds;
            separation = ((EntityRec *)(position))->y.v;
            other_pos = (void *)((CollisionBounds *)(box_operand))->offset_y;
            self_size = ((CollisionBounds *)(box_operand))->size_y;
            box_operand = ((CollisionScratch *)scratch)->other_bounds;
            separation += (s32)other_pos;
            other_pos = ((CollisionScratch *)scratch)->other_position;
            box_operand = (void *)((CollisionBounds *)(box_operand))->offset_y;
            other_edge = ((EntityRec *)(other_pos))->y.v;
            separation += self_size;
            other_edge += (s32)box_operand;
            separation -= other_edge;
            ((CollisionScratch *)scratch)->y_far = separation;
            if (separation < 0) {
                continue;
            }
        }

        {
            void *self_box;
            void *other_pos;
            void *other_box;
            s32 self_offset;
            s32 other_edge;

            self_box = ((CollisionScratch *)scratch)->self_bounds;
            do {
                min_separation = ((EntityRec *)(position))->z.v;
                self_offset = ((CollisionBounds *)(self_box))->offset_z;
            } while (0);
            other_box = ((CollisionScratch *)scratch)->other_bounds;
            min_separation += self_offset;
            other_pos = ((CollisionScratch *)scratch)->other_position;
            box_operand = (void *)((CollisionBounds *)(other_box))->offset_z;
            other_edge = ((EntityRec *)(other_pos))->z.v;
            axis_operand = ((CollisionBounds *)(other_box))->size_z;
            other_edge += (s32)box_operand;
            other_edge += axis_operand;
            min_separation -= other_edge;
            ((CollisionScratch *)scratch)->z_near = min_separation;
            if (min_separation > 0) {
                continue;
            }
        }

        {
            void *other_pos;
            s32 separation;
            s32 other_edge;

            box_operand = ((CollisionScratch *)scratch)->self_bounds;
            separation = ((EntityRec *)(position))->z.v;
            other_pos = (void *)((CollisionBounds *)(box_operand))->offset_z;
            self_size = ((CollisionBounds *)(box_operand))->size_z;
            box_operand = ((CollisionScratch *)scratch)->other_bounds;
            separation += (s32)other_pos;
            other_pos = ((CollisionScratch *)scratch)->other_position;
            box_operand = (void *)((CollisionBounds *)(box_operand))->offset_z;
            other_edge = ((EntityRec *)(other_pos))->z.v;
            separation += self_size;
            other_edge += (s32)box_operand;
            separation -= other_edge;
            ((CollisionScratch *)scratch)->z_far = separation;
            if (separation < 0) {
                continue;
            }
        }

        {
            s32 max_shift;
            s32 max_depth;

            axis_operand = ((CollisionScratch *)scratch)->x_near;
            max_shift = ((CollisionScratch *)scratch)->x_far;
            axis_operand = abs(axis_operand);
            max_depth = max_shift;
            max_depth = abs(max_depth);
            axis_operand = axis_operand < max_depth;
            if (axis_operand) {
                ((CollisionScratch *)scratch)->face_x = ((ColliderView *)(collider))->response_flags[3];
                ((CollisionScratch *)scratch)->axis_x = 2;
            } else {
                ((CollisionScratch *)scratch)->x_near = max_shift;
                ((CollisionScratch *)scratch)->face_x = ((ColliderView *)(collider))->response_flags[2];
                ((CollisionScratch *)scratch)->axis_x = 3;
            }

            axis_operand = ((CollisionScratch *)scratch)->y_near;
            max_shift = ((CollisionScratch *)scratch)->y_far;
            axis_operand = abs(axis_operand);
            max_depth = max_shift;
            max_depth = abs(max_depth);
            axis_operand = axis_operand < max_depth;
            if (axis_operand) {
                ((CollisionScratch *)scratch)->face_y = ((ColliderView *)(collider))->response_flags[5];
                ((CollisionScratch *)scratch)->axis_y = 4;
            } else {
                ((CollisionScratch *)scratch)->y_near = max_shift;
                ((CollisionScratch *)scratch)->face_y = ((ColliderView *)(collider))->response_flags[4];
                ((CollisionScratch *)scratch)->axis_y = 5;
            }

            axis_operand = ((CollisionScratch *)scratch)->z_near;
            max_shift = ((CollisionScratch *)scratch)->z_far;
            axis_operand = abs(axis_operand);
            max_depth = max_shift;
            max_depth = abs(max_depth);
            axis_operand = axis_operand < max_depth;
            if (axis_operand) {
                ((CollisionScratch *)scratch)->face_z = ((ColliderView *)(collider))->response_flags[1];
                ((CollisionScratch *)scratch)->axis_z = 0;
            } else {
                ((CollisionScratch *)scratch)->z_near = max_shift;
                ((CollisionScratch *)scratch)->face_z = ((ColliderView *)(collider))->response_flags[0];
                ((CollisionScratch *)scratch)->axis_z = 1;
            }
        }

        shift_x = ((CollisionScratch *)scratch)->x_near;
        if (shift_x == 0) {
            if (((CollisionScratch *)scratch)->y_near == 0) {
                continue;
            }
            if (((CollisionScratch *)scratch)->z_near == 0) {
                continue;
            }
        }
        shift_y = ((CollisionScratch *)scratch)->y_near;
        if (shift_y == 0 && ((CollisionScratch *)scratch)->z_near == 0) {
            continue;
        }
        shift_z = ((CollisionScratch *)scratch)->z_near;
        if (shift_z > 0 && ((EntityRec *)(position))->flags14 >= shift_z && shift_x != 0 && shift_y != 0) {
            func_8008F60C(collider, position, scratch);
            continue;
        }
        {
            s32 abs_x;
            s32 y_depth;
            s32 z_depth;
            s32 abs_z;

            abs_x = abs(((CollisionScratch *)scratch)->x_near);
            y_depth = abs(((CollisionScratch *)scratch)->y_near);
            if (abs_x < y_depth) {
                z_depth = ((CollisionScratch *)scratch)->z_near;
                abs_z = z_depth;
                abs_z = abs(abs_z);
                z_depth = y_depth < abs_z;
                if (!z_depth) {
                    z_depth = abs_x < abs_z;
                    if (!z_depth) {
                        func_8008F60C(collider, position, scratch);
                        continue;
                    }
                }
                townApplyTheEntryAdjustmentIncrementSlotCountStoreSlot(collider, position, scratch);
                continue;
            }
            z_depth = ((CollisionScratch *)scratch)->z_near;
            z_depth = abs(z_depth);
            if (y_depth >= z_depth) {
                func_8008F60C(collider, position, scratch);
                continue;
            }
            func_8008F5B4(collider, position, scratch);
        }
    }

    ((CollisionScratch *)scratch)->face_index = 0;
    do {
        ((ColliderView *)collider)->response_flags[((CollisionScratch *)scratch)->face_index] = 0;
        face_index = ((CollisionScratch *)scratch)->face_index + 1;
        ((CollisionScratch *)scratch)->face_index = face_index;
    } while (face_index < 6);
}
