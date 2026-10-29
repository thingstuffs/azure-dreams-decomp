#include "common.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"
#include "dungeon/item/effect.h"
struct EntityFields;

extern s16 actor_event_values[];

extern s32 get_entity_class(void *);

/* Update the two occupied object slots using their table heights when enabled. */
s32 begin_return_magic_for_player_and_familiars(void)
{
    s32 slot_index;
    void *object;
    u8 *object_page;
    s16 *height_table;

    if (create_linked_actor_fade_effect(((s32 *)&scene_object_list_anchor.next)) == 0) {
        return 0;
    }

    slot_index = 1;
    object_page = (u8 *)0x800E0000;
    height_table = actor_event_values;
    do {
        object = *(void **)(*(u8 **)(object_page + 0x3D7C) + 0xAC + slot_index * 4);
        if (object != 0) {
            create_orbiting_teleport_effect(object, height_table[get_entity_class(object)],
                          (s16)slot_index, 0);
        }
        slot_index--;
    } while (slot_index >= 0);

    return 1;
}
