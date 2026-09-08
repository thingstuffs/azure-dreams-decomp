#include "common.h"

extern void func_800C3050(void *arg0, s32 arg1, void *arg2, void *arg3,
                           void *arg4, void *arg5);
extern void func_800C641C(void *arg0, s32 arg1, s32 arg2);

extern u8 D_800D5958[];
extern u8 D_800D5960[];
extern u8 D_800D5988[];
extern u8 D_800D598C[];

/* Initialize object slot 9 and set its data pointers. */
void func_800C64C8(void *object, s32 setup_arg1, s32 setup_arg2) {
    func_800C3050(object, 9, D_800D5988, D_800D598C, D_800D5958,
                  D_800D5960);
    func_800C641C(object, setup_arg1, setup_arg2);
}
