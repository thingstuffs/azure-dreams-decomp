#include "common.h"

extern void func_8004F3D0(int *a0, int a1);
extern void func_8004EEFC(void *a0, void *a1, void *a2);
extern void func_8004F2BC(void *a0);

/* Stores the object's initial value and initializes its substructures. */
void func_8004F3D8(int *object, int initial_value)
{
    func_8004F3D0(object, initial_value);
    func_8004EEFC((char *)object + 0x210, (char *)object + 0x1E8, (char *)object + 0x1F8);
    func_8004F2BC(object);
}
