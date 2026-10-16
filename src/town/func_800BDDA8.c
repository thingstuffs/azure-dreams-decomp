#include "common.h"
#include "shared/object_flags.h"

extern s32 townClassifyObjectAgainstBounds(void *, void *);
extern void townUnlinkSceneListNode(void *node);
extern void func_80033D08(void *object);

typedef struct S_func_800BB508_0 {
    u8 pad_00[0x98];
    void *unk_98;
} S_func_800BB508_0;

/* On a successful object check, clear its linked byte and set object and global flags. */
void func_800BB508(S_func_800BB508_0 *object, void *context) {
    if (townClassifyObjectAgainstBounds(object, context) != 0) {
        townUnlinkSceneListNode(object);
        if (object->unk_98 != 0) {
            *(s8 *)object->unk_98 = 0;
        }
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
