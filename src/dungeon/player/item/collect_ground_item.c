#include "shared/monster_ids.h"
#include "dungeon/level/tile_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/item_ids.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"

typedef struct Ent {
    u8 a;
    u8 b;
    u8 pad[10];
} Ent;

typedef struct Ctx {
    u8 pad0[0xA2];
    u16 flags;
    u8 pad1[0x18];
    void *link;
    u8 pad2[0x3B];
    u8 done;
    s32 total;
    s16 mode;
} Ctx;

typedef struct Item {
    u8 pad[0x24];
    u8 kind;
    u8 sub;
} Item;

typedef struct Unit {
    u8 pad[0x88];
    s16 id;
} Unit;

extern u8 held_item_kind_alias[16];
extern u16 D_80012094;
extern Ent dungeon_ground_item_positions[];
extern char D_80088A80[];
extern char D_80088A84[];
extern char D_800E0A76[];
extern char D_800E0A83[];
extern char D_800E0A90[];
extern char D_800E0AA1[];
extern char D_800E0ABC[];
extern char D_800E0AD8[];
extern char D_800E0AFA[];
extern char D_800E0B07[];

s32 find_floor_item_at_world_position(s32, s32, s32);
void begin_player_trap_trigger(Ctx *, char *, Item *, Unit *);
s32 get_unused_text_buffer(void);
char *write_text_byte_and_advance(s8 value, s8 *dest);
char *expand_text_control_codes(char *, char *);
char *append_typed_formatted_value(DungeonItemEntry *, char *);
void clear_byte_and_advance(char *);
void display_text_with_fullwidth_adjustment(s8 *text);
s32 find_last_zero_entry_run_start(void);
s32 find_and_clear_empty_item_slot(void);
void append_packed_action_record(void *object_ptr, s32 action_code, s32 payload, s8 extra_byte);
u8 *advance_monster_timed_sequence(void);
void read_monster_script_entry(void);
s32 get_scaled_byte_value(DungeonItemEntry *);
void create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
void update_map_cell_flags_with_item_limit(s32, s32, s32);

/* Picks up an item, applying special effects or moving it into inventory. */
s32 collect_ground_item(Ctx *ctx, char *text, Item *item, Unit *unit) {
    GameWork *sys;
    s32 item_lookup;
    s16 item_id;
    char *message;
    s32 message_handle;
    s32 free_entry;
    s32 free_slot;
    s16 slot_index;
    s16 entry_index;
    s32 pickup_value;
    DungeonItemEntry *ground_item;
    DungeonItemEntry *named_item;
    DungeonItemEntry *special_item;
    DungeonItemEntry *stored_item;
    DungeonItemEntry *consumed_item;
    u16 *state_page;
    s32 unused_three;
    void **inventory_slot;
    u8 *active_effect;
    s32 consumed_id;
    s16 stored_id;
    u32 *pickup_slot;
    DungeonItemEntry *ground_items;
    DungeonItemEntry *special_items;
    DungeonItemEntry *consumed_items;
    u8 *inventory_page;
    s32 item_kind;

    sys = &g_game_work;
    item_lookup = find_floor_item_at_world_position(((SpriteFrameState *)item)->tile_x, ((SpriteFrameState *)item)->tile_y, unit->id);
    item_id = item_lookup;
    if (item_id < 0) {
        if (ctx->mode < 0) {
            return 1;
        }
        begin_player_trap_trigger(ctx, text, item, unit);
        return 0;
    }
    message_handle = get_unused_text_buffer();
    message = write_text_byte_and_advance(8, message_handle);
    if (held_item_kind_alias[0] != 0) {
        clear_byte_and_advance(expand_text_control_codes(D_80088A80, append_typed_formatted_value(&dungeon_ground_items[item_id], expand_text_control_codes(D_800E0A76,
            message))));
        display_text_with_fullwidth_adjustment(message_handle);
        return 1;
    }
    free_slot = find_last_zero_entry_run_start();
    free_entry = find_and_clear_empty_item_slot();
    if ((system_update_flags & 1) == 0) {
        if ((sys->buttons & 0x20) != 0) {
            append_packed_action_record(unit, 64, 0, 0);
            clear_byte_and_advance(expand_text_control_codes(D_80088A80, append_typed_formatted_value(&dungeon_ground_items[item_id], expand_text_control_codes(D_800E0A83,
                message))));
            display_text_with_fullwidth_adjustment(message_handle);
            return 1;
        }
    } else {
        active_effect = advance_monster_timed_sequence();
        if (active_effect != 0) {
            if ((active_effect[1] & 0xF8) == 0x40) {
                return 1;
            }
            read_monster_script_entry();
        }
    }
    ground_items = dungeon_ground_items;
    ground_item = &ground_items[(s16) item_lookup];
    if ((ground_item->kind == ITEM_KIND_COIN) || ((ground_item->kind == 12) && (ground_item->unk_00 == ITEM_BLUE_COLLAR))
        || ((ground_item->kind == ITEM_KIND_EGG) && (ground_item->unk_00 == MONSTER_HIKEWNE))) {
        named_item = &dungeon_ground_items[(s16) item_lookup];
        message = append_typed_formatted_value(named_item, message);
        if (named_item->kind == ITEM_KIND_COIN) {
            message = expand_text_control_codes(D_80088A84, message);
        } else {
            message = expand_text_control_codes(D_800E0A90, message);
        }
        special_items = dungeon_ground_items;
        ctx->flags |= 0x80;
        special_item = &special_items[(s16) item_lookup];
        item_kind = special_item->kind;
        if (item_kind == 12) {
            message = expand_text_control_codes(D_800E0ABC, write_text_byte_and_advance(10, expand_text_control_codes(D_800E0AA1, write_text_byte_and_advance(10,
                message))));
            ctx->done = 1;
            state_page = (u16 *) 0x80010000;
            if (state_page[0x104A] != 3) {
                state_page[0x104B] = 3;
            } else {
                state_page[0x104B] = 5;
            }
            *(u16 *) 0x8001209A = 0;
        } else if (item_kind == ITEM_KIND_COIN) {
            pickup_value = get_scaled_byte_value(special_item);
            ctx->total += pickup_value;
            create_actor_value_popup(151, unit, (s16) pickup_value, 1);
        }
        consumed_id = (s16) item_lookup;
        pickup_slot = (u32 *) 0x80010298;
        consumed_items = dungeon_ground_items;
        consumed_item = &consumed_items[consumed_id];
        *pickup_slot = *(u32 *) consumed_item;
        consumed_item->unk_00 = 0;
        consumed_item->kind = ITEM_KIND_NONE;
        update_map_cell_flags_with_item_limit(dungeon_ground_item_positions[consumed_id].a, dungeon_ground_item_positions[consumed_id].b, TILE_HAS_ITEM);
        ctx->link = pickup_slot;
    } else {
        slot_index = free_slot;
        entry_index = free_entry;
        if ((slot_index < 0) || (entry_index < 0)) {
            message = expand_text_control_codes(D_80088A80, append_typed_formatted_value(&dungeon_ground_items[(s16) item_lookup], expand_text_control_codes(D_800E0AFA,
                write_text_byte_and_advance(10, expand_text_control_codes(D_800E0AD8, message)))));
        } else {
            stored_id = item_lookup;
            stored_item = &dungeon_ground_items[stored_id];
            message = expand_text_control_codes(D_800E0B07, append_typed_formatted_value(stored_item, message));
            inventory_slot = (void **) 0x80010248 + slot_index;
            *inventory_slot = *(void **) stored_item;
            inventory_page = (u8 *) 0x80010000;
            *(void ***) (inventory_page + (entry_index * 4) + 0x29C) = inventory_slot;
            ctx->flags |= 0x80;
            stored_item->unk_00 = 0;
            stored_item->kind = ITEM_KIND_NONE;
            update_map_cell_flags_with_item_limit(dungeon_ground_item_positions[stored_id].a, dungeon_ground_item_positions[stored_id].b, TILE_HAS_ITEM);
            ctx->link = inventory_slot;
        }
    }
    clear_byte_and_advance(message);
    display_text_with_fullwidth_adjustment(message_handle);
    return 1;
}
