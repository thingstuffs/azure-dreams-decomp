#include "common.h"

extern void func_8004F3D0(int *a0, int a1);
extern void initialize_text_entity_templates(void *a0, void *a1, void *a2);
extern void build_menu_backdrop_display_buffers(void *a0);

/* Stores the object's initial value and initializes its substructures. */
void initialize_menu_backdrop_layout(int *object, int initial_value)
{
    func_8004F3D0(object, initial_value);
    initialize_text_entity_templates((char *)object + 0x210, (char *)object + 0x1E8, (char *)object + 0x1F8);
    build_menu_backdrop_display_buffers(object);
}
