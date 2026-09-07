#include "common.h"

extern void func_800C3050(void *arg0, s32 arg1, void *arg2, void *arg3,
                           void *arg4, void *arg5);
extern void func_800C641C(void *arg0, s32 arg1, s32 arg2);

extern u8 D_800D5958[];
extern u8 D_800D5960[];
extern u8 D_800D5988[];
extern u8 D_800D598C[];

void func_800C64C8(void *arg0, s32 arg1, s32 arg2) {
    func_800C3050(arg0, 9, D_800D5988, D_800D598C, D_800D5958,
                  D_800D5960);
    func_800C641C(arg0, arg1, arg2);
}
