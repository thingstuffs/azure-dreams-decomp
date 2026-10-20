#include "common.h"

/* Struct for init_gauge_object's first argument: only the accessed offset (0x68, a pointer)
   is given a real field; 0x30/0x40/0x58 are only address-taken (sub-object bases). */
typedef struct {
    u8 pad0[0x68];
    void *field_68;
} S_80050A00;

extern void set_gauge_context(void *a0, void *a1);
extern void init_gauge_blocks(void *a0, void *a1, void *a2, void *a3);
extern void func_800506BC(void *a0, void *a1, void *a2);

/* Reinitializes the object, sets up its sub-objects, and initializes its linked object. */
void init_gauge_object(S_80050A00 *object, void *context)
{
    set_gauge_context(object, context);
    init_gauge_blocks(object, (u8 *)object + 0x58, (u8 *)object + 0x30, (u8 *)object + 0x40);
    func_800506BC(object->field_68, object, context);
}
