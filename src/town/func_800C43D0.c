#include "common.h"
#include "shared/object_node.h"

typedef struct {
    u8 pad[0x1E];
    u16 flag;
} S800083498;

extern void func_800511B4(void *arg0);

/* Set up zukan_func_set after clearing flag bit 0x2000. */
void zukan_func_set(void) {
    D_80083498.flags &= 0xDFFF;
    func_800511B4(((S800083498 *)&D_80083498));
}
