#include "common.h"

extern void func_8004F3D0(int *a0, int a1);
extern void initializeTextEntityTemplates(void *a0, void *a1, void *a2);
extern void buildMenuBackdropDisplayBuffers(void *a0);

/* Stores the object's initial value and initializes its substructures. */
void initializeMenuBackdropLayout(int *object, int initial_value)
{
    func_8004F3D0(object, initial_value);
    initializeTextEntityTemplates((char *)object + 0x210, (char *)object + 0x1E8, (char *)object + 0x1F8);
    buildMenuBackdropDisplayBuffers(object);
}
