#include "common.h"

#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))
#define SC32(p, o)   (*(s32 *)((u8 *)(p) + (o)))
#define VSC32(p, o)  (*(volatile s32 *)((u8 *)(p) + (o)))
#define SCU8(p, o)   (*(u8 *)((u8 *)(p) + (o)))
#define SCPTR(p, o)  (*(void **)((u8 *)(p) + (o)))
#define VSPTR(p, o)  (*(void * volatile *)((u8 *)(p) + (o)))

extern void func_8008F55C(void *, void *, void *);
extern void func_8008F5B4(void *, void *, void *);
extern void func_8008F60C(void *, void *, void *);

/* Resolve bounding-box overlaps with linked colliders along the least-penetrating axis. */
void func_8008F664(void *collider, void *position) {
    u8 *scratch;
    void *bounds;
    void *other_bounds;
    s32 shift_x;
    s32 shift_y;
    s32 shift_z;
    s32 face_index;

    bounds = PTR_AT(collider, 0xC);
    scratch = (u8 *)0x1F800000;
    SC32(scratch, 0x38) = 0;
    SCPTR(scratch, 0) = bounds;
    do {
        *(u8 *)((u32)collider + SC32(scratch, 0x38) + 0x3A) = 0;
        face_index = SC32(scratch, 0x38) + 1;
        SC32(scratch, 0x38) = face_index;
    } while (face_index < 6);

    SCPTR(scratch, 4) = PTR_AT(collider, 4);
    if (SCPTR(scratch, 4) == collider) {
        goto clear_tail;
    }

object_loop:
    {
        void *other;
        register void *object_ref ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

        other = SCPTR(scratch, 4);
        object_ref = PTR_AT(VSPTR(scratch, 4), 8);
        SCPTR(scratch, 8) = object_ref;
        other_bounds = PTR_AT(other, 0xC);
        ASM_KEEP_NV(other_bounds);   /* MATCH pin: keeps a statement from moving across a call/branch */
        object_ref = other;
        ASM_KEEP_NV(object_ref);   /* MATCH pin: load-bearing for the whole function shape */
        SCPTR(scratch, 0xC) = other_bounds;
        if (U8_AT(object_ref, 0x15) == 0) {
            goto next_object;
        }
    }

    {
        void *self_box;
        register void *other_pos ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        s32 separation;
        register s32 self_offset ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        register s32 other_edge ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        s32 other_offset;
        register s32 other_size ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

        self_box = VSPTR(scratch, 0);
        separation = S32_AT(position, 0);
        self_offset = S32_AT(self_box, 0);
        other_pos = VSPTR(scratch, 8);
        separation += self_offset;
        other_edge = S32_AT(other_pos, 0);
        other_offset = S32_AT(other_bounds, 0);
        other_size = S32_AT(other_bounds, 0xC);
        other_edge += other_offset;
        other_edge += other_size;
        separation -= other_edge;
        SC32(scratch, 0x10) = separation;
        if (separation > 0) {
            goto next_object;
        }
    }

    {
        register void *self_box ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        void *other_pos;
        register void *other_box ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        s32 separation;
        s32 self_offset;
        s32 self_size;
        s32 other_edge;
        register s32 other_offset ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

        self_box = VSPTR(scratch, 0);
        separation = S32_AT(position, 0);
        self_offset = S32_AT(self_box, 0);
        self_size = S32_AT(self_box, 0xC);
        other_box = VSPTR(scratch, 0xC);
        separation += self_offset;
        other_pos = VSPTR(scratch, 8);
        other_offset = S32_AT(other_box, 0);
        other_edge = S32_AT(other_pos, 0);
        separation += self_size;
        other_edge += other_offset;
        separation -= other_edge;
        SC32(scratch, 0x14) = separation;
        if (separation < 0) {
            goto next_object;
        }
    }

    {
        void *self_box;
        register void *other_pos ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        void *other_box;
        s32 separation;
        register s32 self_offset ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        s32 other_edge;
        register s32 other_offset ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        register s32 other_size ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

        self_box = VSPTR(scratch, 0);
        separation = S32_AT(position, 4);
        self_offset = S32_AT(self_box, 4);
        other_box = VSPTR(scratch, 0xC);
        separation += self_offset;
        other_pos = VSPTR(scratch, 8);
        other_offset = S32_AT(other_box, 4);
        other_edge = S32_AT(other_pos, 4);
        other_size = S32_AT(other_box, 0x10);
        other_edge += other_offset;
        other_edge += other_size;
        separation -= other_edge;
        SC32(scratch, 0x18) = separation;
        if (separation > 0) {
            goto next_object;
        }
    }

    {
        register void *self_box ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        void *other_pos;
        register void *other_box ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        s32 separation;
        s32 self_offset;
        s32 self_size;
        s32 other_edge;
        register s32 other_offset ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

        self_box = VSPTR(scratch, 0);
        separation = S32_AT(position, 4);
        self_offset = S32_AT(self_box, 4);
        self_size = S32_AT(self_box, 0x10);
        other_box = VSPTR(scratch, 0xC);
        separation += self_offset;
        other_pos = VSPTR(scratch, 8);
        other_offset = S32_AT(other_box, 4);
        other_edge = S32_AT(other_pos, 4);
        separation += self_size;
        other_edge += other_offset;
        separation -= other_edge;
        SC32(scratch, 0x1C) = separation;
        if (separation < 0) {
            goto next_object;
        }
    }

    {
        void *self_box;
        register void *other_pos ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        void *other_box;
        s32 separation;
        register s32 self_offset ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        s32 other_edge;
        register s32 other_offset ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        register s32 other_size ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

        self_box = VSPTR(scratch, 0);
        separation = S32_AT(position, 8);
        self_offset = S32_AT(self_box, 8);
        other_box = VSPTR(scratch, 0xC);
        separation += self_offset;
        other_pos = VSPTR(scratch, 8);
        other_offset = S32_AT(other_box, 8);
        other_edge = S32_AT(other_pos, 8);
        other_size = S32_AT(other_box, 0x14);
        other_edge += other_offset;
        other_edge += other_size;
        separation -= other_edge;
        SC32(scratch, 0x20) = separation;
        if (separation > 0) {
            goto next_object;
        }
    }

    {
        register void *self_box ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        void *other_pos;
        register void *other_box ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        s32 separation;
        s32 self_offset;
        s32 self_size;
        s32 other_edge;
        register s32 other_offset ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

        self_box = VSPTR(scratch, 0);
        separation = S32_AT(position, 8);
        self_offset = S32_AT(self_box, 8);
        self_size = S32_AT(self_box, 0x14);
        other_box = VSPTR(scratch, 0xC);
        separation += self_offset;
        other_pos = VSPTR(scratch, 8);
        other_offset = S32_AT(other_box, 8);
        other_edge = S32_AT(other_pos, 8);
        separation += self_size;
        other_edge += other_offset;
        separation -= other_edge;
        SC32(scratch, 0x24) = separation;
        if (separation < 0) {
            goto next_object;
        }
    }

    {
        s32 min_depth;
        s32 max_shift;
        register s32 max_depth ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        register s32 use_min ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

        min_depth = SC32(scratch, 0x10);
        max_shift = SC32(scratch, 0x14);
        if (min_depth < 0) {
            min_depth = -min_depth;
        }
        max_depth = max_shift;
        if (max_shift < 0) {
            max_depth = -max_depth;
        }
        use_min = min_depth < max_depth;
        if (use_min) {
            SCU8(scratch, 0x28) = U8_AT(collider, 0x37);
            SC32(scratch, 0x2C) = 2;
        } else {
            SC32(scratch, 0x10) = max_shift;
            SCU8(scratch, 0x28) = U8_AT(collider, 0x36);
            SC32(scratch, 0x2C) = 3;
        }

        min_depth = SC32(scratch, 0x18);
        max_shift = SC32(scratch, 0x1C);
        if (min_depth < 0) {
            min_depth = -min_depth;
        }
        max_depth = max_shift;
        if (max_shift < 0) {
            max_depth = -max_depth;
        }
        use_min = min_depth < max_depth;
        if (use_min) {
            SCU8(scratch, 0x29) = U8_AT(collider, 0x39);
            SC32(scratch, 0x30) = 4;
        } else {
            SC32(scratch, 0x18) = max_shift;
            SCU8(scratch, 0x29) = U8_AT(collider, 0x38);
            SC32(scratch, 0x30) = 5;
        }

        min_depth = SC32(scratch, 0x20);
        max_shift = SC32(scratch, 0x24);
        if (min_depth < 0) {
            min_depth = -min_depth;
        }
        max_depth = max_shift;
        if (max_shift < 0) {
            max_depth = -max_depth;
        }
        use_min = min_depth < max_depth;
        if (use_min) {
            SCU8(scratch, 0x2A) = U8_AT(collider, 0x35);
            SC32(scratch, 0x34) = 0;
        } else {
            SC32(scratch, 0x20) = max_shift;
            SCU8(scratch, 0x2A) = U8_AT(collider, 0x34);
            SC32(scratch, 0x34) = 1;
        }
    }

    shift_x = SC32(scratch, 0x10);
    if (shift_x == 0) {
        if (SC32(scratch, 0x18) == 0) {
            goto next_object;
        }
        if (SC32(scratch, 0x20) == 0) {
            goto next_object;
        }
    }
    shift_y = SC32(scratch, 0x18);
    if (shift_y == 0 && SC32(scratch, 0x20) == 0) {
        goto next_object;
    }
    shift_z = SC32(scratch, 0x20);
    if (shift_z > 0 && S32_AT(position, 0x14) >= shift_z && shift_x != 0 && shift_y != 0) {
        goto call_60c;
    }

    {
        s32 x_depth;
        register s32 abs_x ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
        s32 y_depth;
        s32 z_depth;
        register s32 abs_z ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

        x_depth = VSC32(scratch, 0x10);
        y_depth = VSC32(scratch, 0x18);
        abs_x = x_depth;
        if (x_depth < 0) {
            abs_x = -abs_x;
        }
        if (y_depth < 0) {
            y_depth = -y_depth;
        }
        ASM_KEEP_NV(y_depth);   /* MATCH pin: load-bearing for the whole function shape */
        if (abs_x < y_depth) {
            z_depth = VSC32(scratch, 0x20);
            abs_z = z_depth;
            if (z_depth < 0) {
                abs_z = -abs_z;
            }
            z_depth = y_depth < abs_z;
            if (z_depth) {
                goto call_55c;
            }
            z_depth = abs_x < abs_z;
            if (!z_depth) {
                goto call_60c;
            }
call_55c:
            func_8008F55C(collider, position, scratch);
            goto next_object;
        } else {
            z_depth = VSC32(scratch, 0x20);
            if (z_depth < 0) {
                z_depth = -z_depth;
            }
            if (y_depth < z_depth) {
                goto call_5b4;
            }
        }
    }

call_60c:
    func_8008F60C(collider, position, scratch);
    goto next_object;

call_5b4:
    func_8008F5B4(collider, position, scratch);

next_object:
    SCPTR(scratch, 4) = PTR_AT(SCPTR(scratch, 4), 4);
    if (SCPTR(scratch, 4) != collider) {
        goto object_loop;
    }

clear_tail:
    SC32(scratch, 0x38) = 0;
    do {
        *(u8 *)((u32)collider + SC32(scratch, 0x38) + 0x34) = 0;
        face_index = SC32(scratch, 0x38) + 1;
        SC32(scratch, 0x38) = face_index;
    } while (face_index < 6);
}
