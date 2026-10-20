#include "common.h"

/* --- gcc 2.7.2 -O2 -fno-expensive-optimizations translation unit --- */

extern char D_80080B88[8];
extern char D_80080B90[4];
extern void fill_primitive_pair();
extern void build_tinted_gradient_rect();

/* Initializes the sub-objects at offsets 0 and 0x18 from shared templates. */
void init_panel_prims(char *object)
{
    char *base = object;
    fill_primitive_pair(base, D_80080B88);
    build_tinted_gradient_rect(base + 0x18, D_80080B88, D_80080B90);
}
