#include "common.h"
#include "dungeon/item.h"
#include "dungeon/item/effect.h"
#include "dungeon/item/return_magic_sprite_data.h"

typedef struct {
    s32 value;
    s32 pad[2];
} GlobalS32;

extern GlobalS32 return_magic_effect_object;

/* Store the lookup result for the adjusted global value and report success. */
s32 create_and_store_pending_actor_fade(void) {
    struct ObjectNodeHeader *result;

    result = create_linked_actor_fade_effect(return_magic_effect_object.value - 0x20);
    return_magic_fade_object = result;
    return result != 0;
}
