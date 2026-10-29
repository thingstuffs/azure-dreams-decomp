#include "common.h"
#include "town/scene/object.h"
s32 func_80058588(s32, s32, const char *);
s32 func_80071424(const char *);
extern s32 scene_object_flags;
/* Submits the linked value each tick, clears flag 2 after a delay, and handles linked cleanup. */
void tick_timed_object_and_mark_complete(void *ptr)
{
    s16 selector;
    u16 value;
    u16 next_value;
    void *field_ptr;
    field_ptr = *((void **) (((s8 *) ptr) + 0xC));
    func_80058588(*(*((s16 **) (((s8 *) ptr) + 8))), func_80071424(*((const char **) (((s8 *) ptr) + 4))),
        *((const char **) (((s8 *) ptr) + 4)));
    selector = *((s16 *) (((s8 *) ptr) + 0));
    switch (selector) {
    case 0:
        value = (*((u16 *) (((s8 *) ptr) + 2))) - 1;
        *((u16 *) (((s8 *) ptr) + 2)) = value;
        if ((value << 0x10) > 0) {
            return;
        }
        next_value = (*((u16 *) (((s8 *) ptr) + 0))) + 1;
        *((u16 *) (((s8 *) ptr) + 0x1C)) &= 0xFFFD;
        *((u16 *) (((s8 *) ptr) + 0)) = next_value;
        return;
    case 1:
        if ((*((u16 *) (((s8 *) field_ptr) + 0x2A))) & 1) {
            *((u16 *) (((s8 *) ptr) + (-2))) = (u16) ((*((u16 *) (((s8 *) ptr) + (-2)))) | 0x8000);
            *((s32 *) 0x80084D5C) = scene_object_flags | 0x8000;
        }
    }
}
