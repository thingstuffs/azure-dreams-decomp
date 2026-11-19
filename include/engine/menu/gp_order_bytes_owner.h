#ifndef SLUS_GP_ORDER_BYTES_OWNER_H
#define SLUS_GP_ORDER_BYTES_OWNER_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/menu_display.h"
#include "engine/menu/animated_panel.h"

extern u8 menu_element_order[4];

/* Initialize element defaults and link elements in the configured order. */

void init_animated_panel_elements(AnimatedMenuPanelBody *obj);

#endif
