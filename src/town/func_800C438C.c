#include "common.h"
#include "shared/object_node.h"

typedef struct {
    u8 pad[0x1E];
    u16 flag;
} S800083498;

extern void func_8004EE50(void *object);

/* Set up mcard_func_set after clearing flag bit 0x2000. */
void mcard_func_set(void) {
    D_80083498.flags &= 0xDFFF;
    func_8004EE50(((S800083498 *)&D_80083498));
}
