#include "common.h"

extern void func_800AEEBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_800AEBC4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void func_800AECA4(s32 arg0);

/* Initialize a list object's configuration, position, and display entries. */
void func_800AEEF0(s32 objectData, s32 owner, s32 listConfig, s32 entryCount, s32 x, s32 y, s32 entryIds) {
    func_800AEEBC(objectData, owner, listConfig, entryCount, entryIds);
    func_800AEBC4(objectData, objectData + 0xC8, objectData + 0xA0, objectData + 0xB0, x, y);
    func_800AECA4(objectData);
}
