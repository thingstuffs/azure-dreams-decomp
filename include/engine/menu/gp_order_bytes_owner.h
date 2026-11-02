#ifndef SLUS_GP_ORDER_BYTES_OWNER_H
#define SLUS_GP_ORDER_BYTES_OWNER_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "engine/menu/animated_panel.h"

typedef struct S_8002E5D8
{
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
}
S_8002E5D8;

typedef struct S_8002E5E8
{
    s32 f0;
    s32 f4;
    s32 f8;
}
S_8002E5E8;




extern S_8002E5D8 display_block_defaults;
extern S_8002E5E8 display_vector_defaults;
extern u8 menu_element_order[4];

/* Initialize element defaults and link elements in the configured order. */

void sound_initialize_ordered_elements(AnimatedMenuPanelBody *obj);

#endif
