#include "common.h"
#include "dungeon/effect.h"
#include "dungeon/actor.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct S_800ACBE4_0 {
    u8 pad_00[0x9B];
    u8 unk_9B;
} S_800ACBE4_0;   /* arg0 in fade_out_and_remove_actor */

typedef struct S_800ACBE4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_800ACBE4_2;   /* actor in fade_out_and_remove_actor */

extern void register_node(void *, void *);
extern void unlink_node(void *);
extern void unlink_entity_node(void *);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void detach_record_and_update_slot_state(void *);

/* Fades the actor to black, then triggers an effect and marks it for removal. */
void fade_out_and_remove_actor(void *actor_data, s32 unused, SpriteFrameState *visual, void *current_actor)
{
    s32 actor_status;
    s32 actor_flags;
    s32 effect_size;
    u8 state;
    u8 brightness;
    u8 effect_x;
    u8 effect_y;
    S_800ACBE4_2 *actor;

    state = ((S_800ACBE4_0 *)actor_data)->unk_9B;
    actor = current_actor;
    switch (state) {
    case 0:
        actor = (S_800ACBE4_2 *)((u8 *)actor_data - 0x20);
        unlink_node(actor);
        visual->clut -= 0x80;
        visual->flags |= 0xC;
        register_node(actor, process_linked_states_mode_zero);
        visual->color.c.code = 0;
        ((S_800ACBE4_0 *)actor_data)->unk_9B++;
        return;
    case 1:
        break;
    default:
        return;
    }
    if (visual->color.c.code < 8) {
        brightness = visual->color.c.b;
        visual->color.c.code++;
        brightness += -brightness / visual->color.c.code;
        visual->color.c.b = brightness;
        visual->color.c.g = brightness;
        visual->color.c.r = brightness;
        return;
    }

    if ((g_dungeon_status.pending_display_owner) == (u8 *)actor - 0x20) {
        *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
    }
    detach_record_and_update_slot_state(actor);
    actor_status = actor->unk_1C;
    effect_x = visual->tile_x;
    effect_y = visual->tile_y;
    effect_size = 0x3000;
    if (actor_status & 0x2000) {
        effect_size = 0x300;
    }
    update_map_cell_flags_with_item_limit(effect_x, effect_y, effect_size);
    actor_flags = actor->unk_14;
    if (actor_flags & 0x400000) {
        actor->unk_14 = actor_flags & 0xFFBFFFFF;
        actor->unk_1C |= 0x400000;
    }
    unlink_entity_node(actor);
    (*(u16 *)((u8 *)actor + -2)) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;

    return;
}
