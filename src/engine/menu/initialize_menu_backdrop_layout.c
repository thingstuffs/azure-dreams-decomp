#include "common.h"
#include "engine/menu.h"
#include "slus.h"
#include "engine/text.h"

/* Stores the object's initial value and initializes its substructures. */
void initialize_menu_backdrop_layout(SevenEntryMenuBackdropBody *object, struct ObjectNodeHeader *owner)
{
    set_menu_backdrop_owner(&object->owner, owner);
    initialize_text_entity_templates((char *)object + 0x210, &object->template_block, &object->template_vector);
    build_menu_backdrop_display_buffers(object);
}
