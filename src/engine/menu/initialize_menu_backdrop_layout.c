#include "common.h"
#include "engine/menu.h"
#include "slus.h"

extern void initialize_text_entity_templates(void *a0, void *a1, void *a2);

/* Stores the object's initial value and initializes its substructures. */
void initialize_menu_backdrop_layout(SevenEntryMenuBackdropBody *object, int initial_value)
{
    set_menu_backdrop_initial_value(&object->owner, initial_value);
    initialize_text_entity_templates((char *)object + 0x210, (char *)object + 0x1E8, (char *)object + 0x1F8);
    build_menu_backdrop_display_buffers(object);
}
