#include "shared/object_node.h"
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;

extern void register_node(void *object, void *data);
extern s16 D_80080B04;
extern void *D_80081508;
extern s32 D_800D1824;

/* Creates an object, attaches its data, and clears the shared state. */
void create_mesh_effect_object(void)
{
    void *object;

    object = func_8003FC64(0);
    register_node(object, &D_800D1824);
    D_80081508 = ((u8 *)object) + 0x20;
    *((s8 *)(((u8 *)object) + 0x20)) = 0;
    D_80080B04 = 0;
}
