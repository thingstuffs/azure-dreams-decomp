#include "common.h"

typedef struct {
    void (*field_0)();
    unsigned char pad4[0x1C - 4];
    void *field_1C;
    unsigned char pad20[0x2C - 0x20];
    char *field_2C;
} S_800509C4;

extern void init_panel_prims(char *a0);
extern void start_gauge_ramp(void);

/* Stores the object's context, reinitializes its sub-object, and installs its dispatch handler. */
void set_gauge_context(S_800509C4 *object, void *context)
{
    object->field_1C = context;
    init_panel_prims(object->field_2C);
    object->field_0 = start_gauge_ramp;
}
