#include "common.h"
#include "shared/object_node.h"

typedef struct {
    u8 pad[0x1E];
    u16 flag;
} S800083498;

extern void create_linked_zukan_task(void *related_entity);

/* Set up zukan_func_set after clearing flag bit 0x2000. */
void zukan_func_set(void) {
    scene_object_list_anchor.flags &= 0xDFFF;
    create_linked_zukan_task(((S800083498 *)&scene_object_list_anchor));
}
