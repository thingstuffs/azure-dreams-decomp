#include "common.h"
#include "town/scene.h"

extern s32 D_8001C378;

/* Sets D_8001C378 to one. */
void enable_global_entry_processing(void) {
    D_8001C378 = 1;
}
