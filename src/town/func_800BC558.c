#include "common.h"
#include "shared/object_flags.h"

extern s32 classify_object_against_bounds(void *, void *);
extern void func_80033D08(void *object);

/* Clear the object's linked flag and mark completion, or advance its wrapped angle. */
void update_object_link_or_angle_state(void *object, void *context)
{
    u8 *linked_flag;

    if (classify_object_against_bounds(object, context) != 0) {
        linked_flag = *(u8 **)((u8 *)object + 0x98);
        if (linked_flag != 0) {
            *linked_flag = 0;
        }
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    *(u16 *)((u8 *)object + 0x66) =
        *(u16 *)((u8 *)object + 0x66) + *(s8 *)((u8 *)object + 0x97);
    *(s16 *)((u8 *)object + 0x66) %= 0x1000;
}
