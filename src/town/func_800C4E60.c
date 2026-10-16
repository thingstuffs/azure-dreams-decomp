#include "common.h"
#include "shared/object_flags.h"

typedef void (*Callback)(void *, s32, s32);

extern u32 townClassifyObjectAgainstBounds(void *, s32);
extern void townUnlinkSceneListNode(void *);
extern void func_80033D08(void *);

/* Clears and flags the object when the check succeeds, or invokes its callback. */
void townFinalizeTransformObjectOrCallback(void *object, s32 check_value, s32 callback_value) {
    u16 *object_flags;
    s8 *status_byte;

    if (townClassifyObjectAgainstBounds(object, check_value) != 0) {
        townUnlinkSceneListNode(object);
        status_byte = *(s8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        func_80033D08(object);
        object_flags = (u16 *)object - 1;
        *object_flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    } else {
        (*(Callback *)((u8 *)object + 0x50))(object, check_value, callback_value);
    }
}
