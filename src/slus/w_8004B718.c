#include "common.h"

extern void func_8004B634(void);
extern void func_8003F320(void);
extern void func_800253A0(void *a0, void *a1, s32 a2, void *a3);

/* Calls two helpers, then forwards the data pointers to func_800253A0 with a zero third argument. */
void func_8004B718(void *first_data, void *second_data, void *extra_data)
{
    func_8004B634();
    func_8003F320();
    func_800253A0(first_data, second_data, 0, extra_data);
}
