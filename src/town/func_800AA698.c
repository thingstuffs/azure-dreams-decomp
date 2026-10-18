/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_flags.h"

extern s32 classify_object_against_bounds(void *, void *);
extern void func_80033D08(void *object);
extern void func_800478B8(void *fallback_data);

void handle_object_bounds_and_cleanup(void *object, void *check_data, void *fallback_data)
{
    u8 *status_byte;

    if (classify_object_against_bounds(object, check_data) != 0) {
        status_byte = *(u8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    } else {
        func_800478B8(fallback_data);
    }
}
