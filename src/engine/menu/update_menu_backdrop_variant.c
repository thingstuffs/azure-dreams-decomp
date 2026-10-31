#include "common.h"
#include "engine/menu.h"

/* Selects one of two embedded subobjects according to the linked state, when present. */
void update_menu_backdrop_variant(SevenEntryMenuBackdropBody *object)
{
    if (object->state.state != 0) {
        if (object->state.state->value != 0) {
            object->view.variant.upper_buffer = 0;
            object->view.variant.lower_buffer = (char *)object + 0xF8;
        } else {
            object->view.variant.upper_buffer = (char *)object + 0x80;
            object->view.variant.lower_buffer = 0;
        }
    }
}
