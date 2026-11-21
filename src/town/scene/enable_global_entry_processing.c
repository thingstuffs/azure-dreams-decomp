#include "common.h"
#include "town/scene.h"

extern s32 D_8001C378;

/* Ask the object-set selector to scan the choices again. */
void enable_global_entry_processing(void) {
    D_8001C378 = 1;
}
