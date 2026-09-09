#include "common.h"

extern void obj_disp23_cancel_sw_set(u32 arg0);
extern void came_bright_set(s32 arg0);
extern void func_800B2A38(void *arg0);
extern void func_800B3A80(s32 arg0);
extern void func_800B46CC(s32 arg0);
extern void func_800B50BC(s32 arg0);
extern s32 D_800814A0[];

/* Apply three record values, set status flags, and process the record. */
void func_800B2C6C(void *record)
{
    func_800B3A80(*(s32 *)((s8 *)record + 0));
    func_800B50BC(*(s32 *)((s8 *)record + 4));
    func_800B46CC(*(s32 *)((s8 *)record + 8));
    *(u16 *)((s8 *)record - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
    came_bright_set(3);
    obj_disp23_cancel_sw_set(0);
    func_800B2A38(record);
}
