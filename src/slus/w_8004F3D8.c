#include "common.h"

/* Trivial dispatcher: stores a1 into *a0 via func_8004F3D0, then initializes
 * three sub-structures at fixed offsets from a0 via func_8004EEFC, then
 * dispatches further sub-init via func_8004F2BC(a0). */

extern void func_8004F3D0(int *a0, int a1);
extern void func_8004EEFC(void *a0, void *a1, void *a2);
extern void func_8004F2BC(void *a0);

void func_8004F3D8(int *a0, int a1)
{
    func_8004F3D0(a0, a1);
    func_8004EEFC((char *)a0 + 0x210, (char *)a0 + 0x1E8, (char *)a0 + 0x1F8);
    func_8004F2BC(a0);
}
