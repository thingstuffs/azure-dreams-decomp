#include "common.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"

extern s16 D_800DCED4[];

extern s32 func_800429E4(void *);
extern s32 create_linked_actor_fade_effect(s32 *);
extern void create_orbiting_teleport_effect(void *owner, s16 effect_value, s16 direction, s16 effect_mode);

/* Update the two occupied object slots using their table heights when enabled. */
s32 begin_return_magic_for_player_and_familiars(void)
{
    s32 slot_index;
    void *object;
    u8 *object_page;
    s16 *height_table;

    if (create_linked_actor_fade_effect(((s32 *)&D_80083498.next)) == 0) {
        return 0;
    }

    slot_index = 1;
    object_page = (u8 *)0x800E0000;
    height_table = D_800DCED4;
    do {
        object = *(void **)(*(u8 **)(object_page + 0x3D7C) + 0xAC + slot_index * 4);
        if (object != 0) {
            create_orbiting_teleport_effect(object, height_table[func_800429E4(object)],
                          (s16)slot_index, 0);
        }
        slot_index--;
    } while (slot_index >= 0);

    return 1;
}
