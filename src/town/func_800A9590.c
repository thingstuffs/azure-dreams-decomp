#include "common.h"
#include "shared/object_flags.h"

/* Global 32-bit "used"/flags word, same one touched by func_8004B530 /
 * slusSetObjectCleanupFlag / func_800510DC family. Declared as an array (>8B) so gcc
 * uses %hi/%lo addressing with a SINGLE shared base register across the
 * read and write halves of the |= (see w_800510DC.c), matching retail's
 * one lui reused for both the load and the store. */

extern int townClassifyObjectAgainstBounds(void *, void *);
extern void townUnlinkSceneListNode(void *node);
extern void func_80033D08(void *object);

typedef void (*S_800A9590_Callback)(void *, void *, void *, void *);

/* Cleans up and flags the object when its check succeeds, otherwise invokes its callback. */
void townRetireObjectOnCheckOrCallback(void *object, void *input, void *context)
{
    u8 *status_byte;
    S_800A9590_Callback callback;

    if (townClassifyObjectAgainstBounds(object, input) != 0) {
        townUnlinkSceneListNode(object);
        status_byte = *(u8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }
    callback = *(S_800A9590_Callback *)((u8 *)object + 0x50);
    if (callback != 0) {
        callback(object, object, input, context);
    }
}
