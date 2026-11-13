/* Position object initialization g01134.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800A2ACC, CL:town/func_800A2B1C, CL:town/func_800A2CA4, CL:town/func_800A2D54, PD:town/engine:80100AA0.
 */
#include "town/shop/position_object_initialization_g01134.h"
#include "town/shop.h"
#include "town/scene.h"
#include "town/event/state.h"
#include "town/player/position.h"
#include "engine/menu.h"

/* Initialize the record and active flag, then install the object handler. */
void start_item_object_motion(S_800A022C_2 *object, S_800A022C_0 *state, ObjectPosition *record, void *unused_render) {
    state->unk_15 = 1;
    record->velocity_x = 0;
    record->velocity_y = 0;
    record->velocity_z = 0xFFF20000;
    add_motion_deltas_to_position(record);
    object->unk_50 = &D_8009BC44;
}

/* Creates an object at the supplied position and initializes its graphics and state. */
void *create_item_object_at(S_800A027C_5 *config, MovingPosition *position) {
    u8 type;
    S_800A027C_4 *state;
    S_800A027C_3 *render;
    MovingPosition *coords;
    ProjectileObject *object;

    object = allocate_list_node(0x136, &scene_object_list_anchor.next);
    if (object == 0) {
        return 0;
    }
    coords = object->position;
    render = object->sprite;
    coords->x = (u16) position->x;
    coords->y = (u16) position->y;
    state = NODE_BODY(object);
    coords->z = (u16) position->z;
    render->unk_1E = 0x1000;
    render->unk_1C = 0x1000;
    render->unk_0C = 0x808080;
    state->unk_48 = 0;
    state->unk_98 = 0;
    state->unk_93 = 0;
    state->unk_4C = (u8) config->unk_00;
    state->unk_4D = (u8) config->unk_01;
    state->unk_4E = (u8) config->unk_02;
    state->unk_4F = (u8) config->unk_03;
    init_scene_node_mode_4(state, coords, &D_800D073C);
    initialize_optional_object_state(state, coords, render, &D_800D076C);
    type = state->unk_4D;
    if (type == 0x12) {
        state->unk_0C = &D_800D0754;
    }
    if (type == 0x12 && type == state->unk_4D) {
        render->unk_08 = (s32) &item_effect_descriptor;
    } else {
        render->unk_08 = lookup_item_category_mapped_value(state->unk_4D, state->unk_4C);
    }
    object->update_callback = &dispatch_object_or_switch_alternate_state;
    start_item_object_motion((S_800A022C_2 *)state, (S_800A022C_0 *)state, (ObjectPosition *)coords, render);

    return object;
}

/* Clears all 20 shop_record_queue words in reverse order. */
void clear_entry_table(void) {
    s32 *entry;
    s32 index;

    index = 19;
    entry = (s32 *)shop_record_queue;
    entry += 19;
    do {
        *entry = 0;
        index--;
        entry--;
    } while (index >= 0);
}

/* Inserts a record into the first free slot, discarding the first record if full. */
void enqueue_shop_record(TownRecord *record) {
    TownRecord *dst;
    s32 slot;

    slot = 0;
    dst = shop_record_queue;
    while (slot < 20) {
        if (dst->bytes.unk1 == 0) {
            break;
        }
        slot++;
        dst++;
    }

    if (slot == 20) {
        for (slot = 0; slot < 19; slot++) {
            shop_record_queue[slot] = shop_record_queue[slot + 1];
        }
    }

    shop_record_queue[slot].bytes.unk0 = record->bytes.unk0;
    shop_record_queue[slot].bytes.unk1 = record->bytes.unk1;
    shop_record_queue[slot].bytes.unk2 = record->bytes.unk2;
    shop_record_queue[slot].bytes.unk3 = record->bytes.unk3;
}

/* Returns the address of shop_record_queue. */
s32 *get_shop_record_queue(void) {
    return (s32 *)&shop_record_queue;
}

/*
 * Shifts shop_record_queue words left while the current word second byte is nonzero, stopping
 * after at most 19 moves and clearing the vacated word.
 */
void dequeue_shop_record(void) {
    s32 entry_index;
    s32 *entries = (s32 *)&shop_record_queue[0];
    s32 *write_entry;
    s32 *src;

    entry_index = 0;
    write_entry = entries;
    src = entries + 1;
    while (entry_index < 19) {
        if (((u8 *)write_entry)[1] == 0) {
            break;
        }
        *write_entry = *src;
        src++;
        entry_index++;
        write_entry++;
    }
    entries[entry_index] = 0;
}

/* Run the follow-up action when the current record has an eligible type and passes the check. */
void spawn_queued_item_object(s32 check_value) {
    u8 record_type;
    S_800A0504_0 *record;

    record = (S_800A0504_0 *)get_shop_record_queue();
    record_type = record->unk_01;
    if ((record_type != 0) && (record_type != 0x13) && (create_item_object_at(record, check_value) != 0)) {
        dequeue_shop_record();
    }
}

/* Process active type-4 town links that have no associated object. */
void process_unlinked_type_four_entries(void)
{
    TownLink *sentinel = (TownLink *)&town_actor_control;
    TownLink *link = sentinel->next;

    if (is_map_state_in_special_range() != 0) {
        return;
    }

    if (link == sentinel) {
        return;
    }

    do {
        if (link->type == 4 && link->state != -1 && link->object == 0) {
            enqueue_shop_record((u8 *)link + 0x4C);
        }
        link = link->next;
    } while (link != sentinel);
}
