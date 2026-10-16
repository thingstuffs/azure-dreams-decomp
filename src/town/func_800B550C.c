#include "common.h"
#include "shared/object_flags.h"

extern void obj_disp23_cancel_sw_set(u32);
extern void came_bright_set(s32);
extern void func_800B2A38(void *);
extern void func_800B3A80(s32);
extern void townRefreshObjectComponentsAndHighFlag(u8 *object);
extern void townProcessObjectResourcesAndHighFlag(u8 *object);

/* Apply three record values, set status flags, and process the record. */
void func_800B2C6C(void *record)
{
    func_800B3A80(*(s32 *)((s8 *)record + 0));
    townProcessObjectResourcesAndHighFlag(*(s32 *)((s8 *)record + 4));
    townRefreshObjectComponentsAndHighFlag(*(s32 *)((s8 *)record + 8));
    *(u16 *)((s8 *)record - 2) |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
    came_bright_set(3);
    obj_disp23_cancel_sw_set(0);
    func_800B2A38(record);
}
