#include "sdk/libc.h"
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "dungeon/item.h"
#include "dungeon/menu.h"
#include "dungeon/menu/state.h"
struct ObjA464;

typedef struct {
    s32 field_0;
    const char *field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s32 field_24;
    s32 field_28;
    void *field_2C;
    void *field_30;
    void *field_34;
} Entity;

extern void cleanup_object_resources();
extern void flag_object_and_release_inner(struct ObjA464 *obj, s32 unused);

/* Processes entity fields and copies its string for selected type and state values. */
void advance_paired_object_sequence(Entity *entity) {
    s32 state;

    inventory_process_resources_and_set_flags(entity->field_20);
    retire_menu_object(entity->field_24);
    cleanup_object_resources(entity->field_28);
    flag_object_and_release_inner(entity->field_2C, 0);
    flag_object_and_release_inner(entity->field_30, 0);
    flag_object_and_release_inner(entity->field_34, 0);
    if (runtime_dispatch_state.mode != 1) {
        set_state_flag_when_clear();
    }
    if (entity->field_14 == 0x13) {
        state = entity->field_1C;
        if (state == 2 || state == 0x39) {
            strcpy((void *)0x80010238, entity->field_4);
        }
    }
}
