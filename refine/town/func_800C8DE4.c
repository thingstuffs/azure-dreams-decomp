#include "common.h"

extern void func_800C3050(void *arg0, s32 arg1, void *arg2, void *arg3,
                           void *arg4, void *arg5);
extern void func_800C6440(void *arg0, s32 arg1, s32 arg2);
extern void func_800C6C10(void *arg0);

extern u8 D_800D5958[];
extern u8 D_800D5960[];
extern u8 D_800D5988[];
extern u8 D_800D598C[];

/* Initialize object slot 9, set its data pointers, and create its display object. */
void func_800C6544(void *object, s32 unused_a, s32 unused_b) {
    func_800C3050(object, 9, D_800D5988, D_800D598C, D_800D5958,
                  D_800D5960);
    func_800C6440(object, unused_a, unused_b);
    func_800C6C10(object);
}
