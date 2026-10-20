#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct S_800ACBE4_0 {
    u8 pad_00[0x9B];
    u8 unk_9B;
} S_800ACBE4_0;   /* arg0 in fade_out_and_remove_actor */

typedef struct S_800ACBE4_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800ACBE4_1;   /* arg2 in fade_out_and_remove_actor */

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
extern s32 D_800C6AEC;

/* Fades the actor to black, then triggers an effect and marks it for removal. */
void fade_out_and_remove_actor(void *actor_data, s32 unused, void *visual, void *current_actor)
{
    s32 actor_status;
    s32 actor_flags;
    s32 effect_size;
    u8 state;
    u8 brightness;
    u8 effect_x;
    u8 effect_y;
    void *actor;

    state = ((S_800ACBE4_0 *)actor_data)->unk_9B;
    actor = current_actor;
    switch (state) {
    case 0:
        actor = (u8 *)actor_data - 0x20;
        unlink_node(actor);
        ((S_800ACBE4_1 *)visual)->unk_12 -= 0x80;
        ((S_800ACBE4_1 *)visual)->unk_14 |= 0xC;
        register_node(actor, &D_800C6AEC);
        ((S_800ACBE4_1 *)visual)->unk_0F = 0;
        ((S_800ACBE4_0 *)actor_data)->unk_9B++;
        return;
    case 1:
        break;
    default:
        return;
    }
    if (((S_800ACBE4_1 *)visual)->unk_0F < 8) {
        brightness = ((S_800ACBE4_1 *)visual)->unk_0E;
        ((S_800ACBE4_1 *)visual)->unk_0F++;
        brightness += -brightness / ((S_800ACBE4_1 *)visual)->unk_0F;
        ((S_800ACBE4_1 *)visual)->unk_0E = brightness;
        ((S_800ACBE4_1 *)visual)->unk_0D = brightness;
        ((S_800ACBE4_1 *)visual)->unk_0C = brightness;
        return;
    }

    if (((s32)g_dungeon_status.unk_10) == (s32)((u8 *)actor - 0x20)) {
        *(s32 *)&g_dungeon_status.unk_10 &= 0x7FFFFFFF;
    }
    detach_record_and_update_slot_state(actor);
    actor_status = ((S_800ACBE4_2 *)actor)->unk_1C;
    effect_x = ((S_800ACBE4_1 *)visual)->unk_24;
    effect_y = ((S_800ACBE4_1 *)visual)->unk_25;
    effect_size = 0x3000;
    if (actor_status & 0x2000) {
        effect_size = 0x300;
    }
    update_map_cell_flags_with_item_limit(effect_x, effect_y, effect_size);
    actor_flags = ((S_800ACBE4_2 *)actor)->unk_14;
    if (actor_flags & 0x400000) {
        ((S_800ACBE4_2 *)actor)->unk_14 = actor_flags & 0xFFBFFFFF;
        ((S_800ACBE4_2 *)actor)->unk_1C |= 0x400000;
    }
    unlink_entity_node(actor);
    (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
    object_flag_block.flags |= 0x8000;

    return;
}
