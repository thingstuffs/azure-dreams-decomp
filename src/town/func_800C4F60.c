#include "common.h"
#include "shared/object_flags.h"

extern s32 func_800352FC(void);
extern s32 townCheckActiveTransformObject(void *other);
extern void townUnlinkSceneListNode(void *node);

/* Process the object and set its header and global flags when both checks pass. */
void townProcessCheckedTransformObject(void *object, s32 check_value_1, s32 check_value_2, s32 check_value_3) {
    if ((func_800352FC() != 0) && (townCheckActiveTransformObject(object) != 0)) {
        townUnlinkSceneListNode(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
