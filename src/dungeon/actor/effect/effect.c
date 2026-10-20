/* Complete native TU in retail file order. Review pending. */
#include "dungeon/actor/effect/effect.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_engine_entity_effects_storage.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"

extern int abs(int);

typedef struct {
    u8 pad24[0x24];
    u8 x;
    u8 y;
    s8 kind;
} Entity;

typedef struct {
    u8 x;
    u8 y;
    u8 pad02[10];
} RegionPos;

s32 find_active_rect_containing_point();

/* Finds the nearest matching entry in the entity's region and writes its coordinates. */
u32 find_nearest_floor_item_in_room(Entity *entity, s32 filter, s16 *out_x, s16 *out_y) {
    s16 best_distance;
    s32 best_index;
    s32 i;
    s32 id;
    s32 type;
    s32 x;
    s32 y;
    s16 dx;
    s16 dy;
    s32 y_larger;
    s16 d;

    if (entity->kind < 0) {
        return 0;
    }
    best_distance = 0x100;
    best_index = -1;
    i = 0x3F;
    id = filter & 0xFF;
    type = (s16)filter >> 8;
    for (; i >= 0; i--) {
        if (D_800E3548[i].kind == id && (type == 0 || D_800E3548[i].unk_00 == type)) {
            x = ((RegionPos *)D_800E36C8)[i].x;
            y = ((RegionPos *)D_800E36C8)[i].y;
            if ((s16)find_active_rect_containing_point(x, y) == entity->kind) {
                dx = abs(x - entity->x);
                dy = abs(y - entity->y);
                y_larger = dx < dy;
                d = y_larger ? dy : dx;
                if (best_distance > d) {
                    best_distance = y_larger ? dy : dx;
                    *out_x = x;
                    *out_y = y;
                    best_index = i;
                }
            }
        }
    }
    return (s16)best_index >= 0;
}
#include "modules/dungeon_engine_entity_effects_storage.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad[10];
} Entry;

extern void update_map_cell_flags_with_item_limit(u8, u8, s32);

/* Clear active entries at the target coordinates and update their map tile. */
void remove_floor_items_at_tile(s16 target_x, s16 target_y) {
    Entry *entry;
    s32 *entry_state;
    s32 entry_index;
    s32 x;
    s32 y;
    u8 entry_x;
    u8 entry_y;

    entry_index = 0;
    x = target_x;
    y = target_y;
    entry_state = ((s32 *)D_800E3548);
    entry = ((Entry *)D_800E36C8);
    do {
        if (((u8 *) entry_state)[1] != 0) {
            entry_x = entry->unk0;
            if (entry_x == x) {
                entry_y = entry->unk1;
                if (entry_y == y) {
                    *entry_state = 0;
                    update_map_cell_flags_with_item_limit(entry_x, entry_y, 0x800);
                }
            }
        }
        entry_state++;
        entry_index++;
        entry++;
    } while (entry_index < 0x40);
}
#include "modules/dungeon_engine_entity_effects_storage.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"

typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 value;
    u8 pad6[6];
} PositionEntry;

extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);

/* Finds an active entry at the given tile within 64 height units if the left tile has flag 0x800. */
s32 find_floor_item_at_world_position(s32 input_x, s32 input_y, s32 input_z) {
    s32 held_x;
    s32 held_z;
    s32 held_y;
    s32 result;
    s32 entry_index;
    s32 y;
    u16 tile_flags;
    DungeonItemEntry *active_entry;
    PositionEntry *position;
    s32 height_delta;
    s32 x;
    s32 z;

    held_x = input_x;
    held_z = input_z;
    get_offset_map_cell_value_and_flags((s16)(held_x - 1), (held_y = (s16)input_y), 0, &tile_flags);
    entry_index = 0;
    if (tile_flags & 0x800) {
        goto scan;
    }
    result = -1;
    return result;
success:
    result = (s16)entry_index;
    return result;
scan:
    x = (s16)held_x;
    y = held_y;
    z = (s16)held_z;
    position = (PositionEntry *)D_800E36C8;
    active_entry = (DungeonItemEntry *)((u8 *)D_800E3548);
    do {
        if ((active_entry->kind != 0) && (position->x == x) && (position->y == y)) {
            height_delta = z - position->value;
            if (height_delta < 0) {
                height_delta = 0 - height_delta;
            }
            if (height_delta < 0x40) {
                goto success;
            }
        }
        position++;
        entry_index += 1;
        active_entry++;
        if (entry_index >= 0x40) {
            result = -1;
            return result;
        }
    } while (1);
    return result;
}

/* MECHANISM: True-space epilogue targets are two pre-scan return trampolines; s32 formals
   plus guarded s1/s2/s0 carriers reproduce the raw/narrow argument lifetimes and 0x28 saves.
   Counter/y carriers fix volatile roles; v0 page keeps emit the split +36C8/+3548 bases. */
#include "shared/dungeon_item_entries.h"
#include "common.h"

/* Returns the first entry index with a zero second byte among 64 entries, or -1. */
s32 find_first_empty_floor_item_slot(void) {
    u8 *entry;
    s32 entry_index;

    entry_index = 0;
    entry = ((u8 *)D_800E3548);
    do {
        if (entry[1] != 0) {
            entry_index++;
            entry += 4;
            continue;
        }
        return (s16)entry_index;
    } while (entry_index < 0x40);
    return -1;
}
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);
extern u16 D_800DCE6C[];
extern u16 D_800DCE8C[];

/* Finds a nearby unblocked position with a distance below 0x200. */
s32 find_valid_floor_item_position(s16 x, s16 y, s16 z, s16 *out_x, s16 *out_y, s16 *out_distance) {
    u16 tile_flags;
    s32 distance;
    s32 i;
    s16 dir;

    if (get_offset_map_cell_value_and_flags(x - 1, y, 0, &tile_flags) != 0 && !(tile_flags & 0x8820)) {
        distance = sample_terrain_surface_height(((x << 6) + 0x20) & 0xFFE0, ((y << 6) + 0x20) & 0xFFE0, z - 0x20);
        if ((s16)distance < 0x200) {
            *out_x = x;
            *out_y = y;
            *out_distance = distance;
            return 1;
        }
    }

    dir = g_dungeon_status.unk_1E & 7;
    for (i = 0; i < 8; i++, dir = (dir + 1) & 7) {
        if (get_offset_map_cell_value_and_flags(x, y, dir, &tile_flags) != 0 && !(tile_flags & 0x8820)) {
            distance = sample_terrain_surface_height((((x + dir_step_x[dir]) << 6) + 0x20) & 0xFFE0,
                (((y + dir_step_y[dir]) << 6) + 0x20) & 0xFFE0, z - 0x20);
            if ((s16)distance < 0x200) {
                *out_x = x + dir_step_x[dir];
                *out_y = y + dir_step_y[dir];
                *out_distance = distance;
                return 1;
            }
        }
    }

    dir = g_dungeon_status.unk_1E & 0xF;
    for (i = 0; i < 0x10; i++, dir = (dir + 1) & 0xF) {
        if (get_offset_map_cell_value_and_flags(x + D_800DCE6C[dir] - 1, y + D_800DCE8C[dir], 0, &tile_flags) != 0 && !(tile_flags & 0x8820)) {
            distance = sample_terrain_surface_height((((x + (s16)D_800DCE6C[dir]) << 6) + 0x20) & 0xFFE0,
                (((y + (s16)D_800DCE8C[dir]) << 6) + 0x20) & 0xFFE0, z - 0x20);
            if ((s16)distance < 0x200) {
                *out_x = x + D_800DCE6C[dir];
                *out_y = y + D_800DCE8C[dir];
                *out_distance = distance;
                return 1;
            }
        }
    }
    return 0;
}
#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad_a0[0xA0];
    union {
        s16 signed_value;
        u16 unsigned_value;
    } state;
    u16 pad_a2;
    u16 counter;
    u16 remaining;
} FuncState;

typedef struct {
    u8 pad_8[8];
    s32 value_8;
    u8 pad_14[8];
    s32 value_14;
} FuncArg1;

typedef struct {
    u8 pad_c[0xC];
    u8 value_c;
    u8 value_d;
    u8 value_e;
    u8 pad_f[0xD];
    u16 value_1c;
    u16 value_1e;
} FuncArg2;

extern s32 func_800644B8(s32);

/* Updates a two-phase visual effect's size, brightness, and motion. */
void update_effect_bounce_and_fade(FuncState *effect, FuncArg1 *motion, FuncArg2 *visual) {
    s16 phase;
    u16 updated_value;
    u16 min_counter;

    phase = effect->state.signed_value;
    min_counter = 1;
    switch (phase) {
    case 0:
        effect->remaining = 4;
        effect->counter = 0;
        effect->state.unsigned_value = effect->state.unsigned_value + 1;
    case 1:
        updated_value = effect->counter + 1;
        effect->counter = updated_value;
        visual->value_1c = visual->value_1c + func_800644B8((s32)(updated_value << 16) >> 11);
        visual->value_1e = visual->value_1e - func_800644B8(((s16)effect->counter) << 5);
        updated_value = effect->remaining - 1;
        effect->remaining = updated_value;
        if ((s16)updated_value > 0) {
            break;
        }
        effect->state.unsigned_value = effect->state.unsigned_value + 1;
        break;
    case 2:
        updated_value = effect->counter - 1;
        effect->counter = updated_value;
        if ((s16)updated_value <= 0) {
            effect->counter = min_counter;
        }
        visual->value_1c = visual->value_1c - (func_800644B8(((s16)effect->counter) << 5) * 2);
        visual->value_1e = visual->value_1e + (func_800644B8(((s16)effect->counter) << 5) * 4);
        motion->value_14 = motion->value_14 - 0x20000;
        updated_value = visual->value_e - 4;
        visual->value_e = updated_value;
        visual->value_d = updated_value;
        visual->value_c = updated_value;
        if ((s16)visual->value_1c <= 0) {
            ((u16 *)effect)[-1] = ((u16 *)effect)[-1] | 0x8000;
            object_flag_block.flags = object_flag_block.flags | 0x8000;
        }
        break;
    }
    motion->value_8 = motion->value_8 + motion->value_14;
}
#include "common.h"
#include "shared/object_node.h"

#include "m2c_compat.h"

typedef struct DungeonInner {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} DungeonInner;

typedef struct DungeonDescriptor {
    u8 pad0[8];
    DungeonInner *inner;
    u8 padC[4];
    void *field10;
    u8 pad14[0xA4];
    u32 fieldB8;
} DungeonDescriptor;

extern M2C_UNK D_800A7548;
extern void * create_item_render_object(s32 parent, s32 sprite_source, s16 x, s32 y, s16 z);

/* Create a dungeon descriptor centered on the given tile at the specified z coordinate. */
DungeonDescriptor *create_timed_effect_at_tile(s32 tile_x, s32 tile_y, s32 z, s32 *init_data) {
    DungeonDescriptor *descriptor;
    DungeonInner *inner;

    descriptor = create_item_render_object(((u8 *)(&D_80083498)), init_data, 0, 0, 0);
    if (descriptor == 0) {
        return 0;
    }
    descriptor->field10 = &D_800A7548;
    inner = descriptor->inner;
    inner->x = (s16)((tile_x << 6) + 0x20);
    inner->y = (s16)((tile_y << 6) + 0x20);
    inner->z = (s16)z;
    descriptor->fieldB8 = *init_data;
    return descriptor;
}
#include "modules/dungeon_engine_entity_effects_abi_views.h"
#include "modules/dungeon_engine_entity_effects_storage.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void select_position_data_and_update_owner(void *entity, void *search_state);

typedef struct {
    u8 x;
    u8 y;
    u16 value2;
    u16 value4;
    u16 pad6;
    s32 value8;
} D_800E36C8_Entry;

typedef struct {
    u8 pad0[0x98];
    s32 field98;
    u8 pad9C[4];
    s16 fieldA0;
    u8 padA2[8];
    s16 fieldAA;
    s16 fieldAC;
    s16 fieldAE;
} FuncObj;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} FuncVec;

/* Ease the thrown object toward its landing tile; on arrival record it in the floor's item table and finish. */
void update_floor_object_motion(FuncObj *obj, FuncVec *pos, FuncVec *target) {
    s16 steps;
    u16 remaining;
    s32 slot;
    s32 x;
    s32 y;
    s32 z;
    u16 height;
    D_800E36C8_Entry *entry;
    D_800E36C8_Entry *tab;

    x = pos->x;
    pos->x = x +
        (((((obj->fieldAA << 6) + 0x20) << 0x10) - x) /
         obj->fieldA0);
    y = pos->y;
    pos->y = y +
        (((((obj->fieldAC << 6) + 0x20) << 0x10) - y) /
         obj->fieldA0);
    z = pos->z;
    steps = obj->fieldA0;
    pos->z = z +
        (((obj->fieldAE << 0x10) - z) / steps);

    remaining = (u16)obj->fieldA0 - 1;
    obj->fieldA0 = remaining;
    if ((s16)remaining <= 0) {
        slot = free_entry_short();
        if (slot >= 0) {
            ((s32 *)D_800E3548)[slot] = obj->field98;
            tab = ((D_800E36C8_Entry *)D_800E36C8);
            entry = &tab[slot];
            entry->x = obj->fieldAA;
            entry->y = obj->fieldAC;
            height = obj->fieldAE;
            entry->value2 = height;
            entry->value4 = height;
            entry->value8 = target->z;
            cycle_map_cell_flags(obj->fieldAA, obj->fieldAC, 0x800);
            select_position_data_and_update_owner(&D_80082E80.unk_000, ((s32)D_800E3D7C));
        }
        g_dungeon_status.unk_0A--;
                /* the u16 two bytes BEFORE the object: a negative offset, which the field-typing
           pass (tools/xform/t4_fields.py) refuses to fold into a struct; a `_pre` struct
           spelling was tried here and costs 9 words (const-remat), so it stays an explicit cast */
        *(u16 *)((u8 *)obj - 2) |= 0x8000;
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}

/* MECHANISM: Preserve the seed's 0x20 frame, s0 object hold, s1 target hold, and v0 entry pin.
   The allocator call is zero-arity: the preceding signed divisor may remain incidental in a0,
   avoiding the false unsigned reload at word 36 and restoring retail's post-mflo nop. */
#include "common.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"

typedef struct S_800A794C_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_800A794C_0;   /* object in func_800A794C */

typedef struct S_800A794C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800A794C_1;   /* position in func_800A794C */

typedef struct S_800A794C_2 {
    u8 pad_00[0x98];
    s32 unk_98;
    u8 pad_9C[0x4];
    s16 unk_A0;
    u8 pad_A2[0x8];
    s16 unk_AA;
    s16 unk_AC;
    s16 unk_AE;
} S_800A794C_2;   /* fields in func_800A794C */

extern void * create_item_render_object(s32 parent, s32 sprite_source, s16 x, s32 y, s16 z);

extern u8 D_800A77AC[];

/* Create an object at the tile center, initialize its fields, and increment the object count. */
s32 func_800A794C(s32 tile_x, s32 tile_y, s32 height, s32 *payload_ptr,
                  s32 field_aa, s32 field_ac, s32 field_ae) {
    u8 *object;
    u8 *position;
    u8 *fields;
    s32 payload;

    object = create_item_render_object(((s32 *)&D_80083498.next), payload_ptr, 0, 0, 0);
    if (object == 0) {
        return 0;
    }
    ((S_800A794C_0 *)object)->unk_10 = D_800A77AC;
    position = ((S_800A794C_0 *)object)->unk_08;
    ((S_800A794C_1 *)position)->unk_02 = (s16)((tile_x << 6) + 0x20);
    ((S_800A794C_1 *)position)->unk_06 = (s16)((tile_y << 6) + 0x20);
    ((S_800A794C_1 *)position)->unk_0A = height;

    fields = object + 0x20;
    payload = *payload_ptr;
    ((S_800A794C_2 *)fields)->unk_A0 = 4;
    ((S_800A794C_2 *)fields)->unk_AA = (s16)field_aa;
    ((S_800A794C_2 *)fields)->unk_AC = (s16)field_ac;
    ((S_800A794C_2 *)fields)->unk_98 = payload;
    ((S_800A794C_2 *)fields)->unk_AE = (s16)field_ae;
    g_dungeon_status.unk_0A++;
    return (s32)object;
}
#include "common.h"
extern u8 D_8006E240[];

extern s32 lookup_item_category_mapped_value(s32, s32);

/* Resolve the item's description: kind 0x12 uses the fixed table, everything else is looked up. */
s32 get_item_category_value(u8 *item)
{
    s32 result;

    if (item[1] == 0x12) {

        result = D_8006E240;
    } else {
        result = lookup_item_category_mapped_value(item[1], item[0]);
    }
    return result;
}
#include "modules/dungeon_engine_entity_effects_storage.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"

typedef struct {
    u8 b0;
    u8 b1;
    u16 w2;
    u16 w4;
    u16 pad6;
    s32 value;
} DungeonRecord;

extern s32 D_800E0B54;

extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 func_80099290(s8 *byte_ptr);
extern s32 append_typed_formatted_value(s32 *, s32);
extern void select_position_data_and_update_owner(void *entity, void *search_state);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s32 find_first_empty_floor_item_slot(void);
extern s32 find_valid_floor_item_position(s16 x, s16 y, s16 z, s16 *out_x, s16 *out_y, s16 *out_distance);
struct DungeonDescriptor;
extern struct DungeonDescriptor * create_timed_effect_at_tile(s32 tile_x, s32 tile_y, s32 z, s32 *init_data);
extern s32 func_800A794C(s32, s32, s32, s32 *, s32, s32, s32);
extern s32 get_item_category_value(u8 *item);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);

/* Registers an object at a resolved dungeon position or processes its fallback placement. */
s32 place_item_at_valid_floor_position(s32 x, s32 y, s32 z, s32 unused, s32 *object_data) {
    s16 tile_x;
    s16 tile_y;
    s16 tile_value;
    s32 output_start;
    s32 output_cursor;
    s16 x_short;
    s16 y_short;
    s16 z_short;

    x_short = (s16)x;
    y_short = (s16)y;
    z_short = (s16)z;
    if ((find_valid_floor_item_position(x_short, y_short, z_short,
                       &tile_x, &tile_y, &tile_value) << 16) != 0) {
        s16 record_index;
        DungeonRecord *record;

        record_index = find_first_empty_floor_item_slot();
        if (record_index >= 0) {
            if (func_800A794C(x_short, y_short, z_short, object_data,
                              tile_x, tile_y, tile_value) == 0) {
                ((s32 *)D_800E3548)[record_index] = *object_data;
                record = &((DungeonRecord *)D_800E36C8)[record_index];
                record->b0 = (u8)tile_x;
                record->b1 = (u8)tile_y;
                record->w4 = (u16)tile_value;
                record->w2 = (u16)tile_value;
                record->value = get_item_category_value(object_data);
                cycle_map_cell_flags(tile_x, tile_y, 0x800);
                select_position_data_and_update_owner(((u8 *)(&D_80082E80)), ((u8 *)D_800E3D7C));
            }
            return 1;
        }
    }

    create_timed_effect_at_tile(x_short, y_short, z_short, object_data);
    output_cursor = get_unused_text_buffer();
    output_start = output_cursor;
    output_cursor = append_typed_formatted_value(object_data, output_cursor);
    output_cursor = expand_text_control_codes(&D_800E0B54, output_cursor);
    func_80099290(output_cursor);
    display_text_with_fullwidth_adjustment(output_start);
    return 0;
}
#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

extern s32 register_node(void *entry, s32 registration_id);
extern M2C_UNK D_800A7CC4;

typedef struct S_800A7C64_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
} S_800A7C64_0;

/* Create an object and initialize its render data to neutral color and unit scale. */
void create_floor_item_renderer(void) {
    SpriteFrameState *render_data;
    S_800A7C64_0 *object;

    object = func_8003FC64(2);
    if (object != NULL) {
        render_data = object->unk_0C;
        object->unk_10 = 0;
        register_node(object, &D_800A7CC4);
        render_data->color.c.b = 0x80;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        render_data->scale_y = 0x1000;
        render_data->scale_x = 0x1000;
    }
}
#include "modules/dungeon_engine_entity_effects_storage.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/game_work.h"

extern void func_80064840();
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0();
extern void func_80064CF0();
extern void func_80064D80();
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800654B0();
extern void func_80065820();
extern void func_8006658C();
extern void func_800666F4();

extern u8 D_8006CD30[];
typedef struct { u8 b0, b1, b2, b3; } Ent4;
typedef struct { u8 b0, b1; u16 h2, h4; u8 *p8; } Ent12;

#define U8(p, o)  (*(u8  *)((u8 *)(p) + (o)))
#define S8(p, o)  (*(s8  *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

typedef struct {
    s32 vx, vy, vz, pad;
} Vec4;

/* Draw visible entity sprite quads and their translucent shadows. */
s32 render_floor_items(s32 unused0, s32 unused1, void *render_params) {
    s32 entity_index;
    u8 *scratch;
    GameWork *render_state;
    u8 *render_ctx;
    u8 *entity;
    u8 *prim;
    u8 *sprite;
    s32 world_z, depth, angle_y_offset, sort_depth;
    s32 tex_u, tex_width, tex_v, tex_height;
    s32 tex_left;
    s32 tex_right;
    s32 tex_top;
    s32 tex_bottom;
    s16 quad_left, quad_top, quad_right, quad_bottom;
    u8 offset_x_byte, offset_y_byte;
    s32 visible, visible1, visible2, visible3;
    s32 screen_bottom;
    struct { u16 a, b, c; } camera_angles;
    Vec4 shadow_scale;
    u8 *vertex0, *vertex1, *vertex2, *vertex3, *screen0, *screen1, *screen2, *screen3, *depth_out;
    u8 *flags_out;
    u8 *entities;
    u8 *view_matrix;
    u8 *rotation_matrix;
    u8 *transform;
    u8 *matrix_page;
    s32 depth_offset, flags_offset;
    u8 *matrix_or_prim;
    s32 angle_z;
    s32 angle_y;

    matrix_page = (u8 *)0x80070000;
    depth_offset = 0x90;
    flags_offset = 0x94;
    entity_index = 0;
    view_matrix = D_8006CD30;
    rotation_matrix = (u8 *)0x1F8000D0;
    transform = (u8 *)0x1F800050;
    vertex0 = (u8 *)0x1F800070;
    vertex1 = (u8 *)0x1F800078;
    vertex2 = (u8 *)0x1F800080;
    scratch = (u8 *)0x1F800000;
    render_state = &g_game_work;
    render_ctx = *(u8 **)((u8 *)(&g_game_work));
    prim = *(u8 **)(render_ctx + 0x8D0);
    U32(scratch, 0x20) = (u32)(render_ctx + 0xB0);
    U32(scratch, 0xE4) = 0;
    U32(scratch, 0xE8) = 0;
    U32(scratch, 0xEC) = 0;
    U16(scratch, 0x8C) = 0;
    U16(scratch, 0x84) = 0;
    U16(scratch, 0x7C) = 0;
    U16(scratch, 0x74) = 0;
    camera_angles.a = U16(render_state, 196);
    camera_angles.b = U16(render_state, 198);
    camera_angles.c = U16(render_state, 200);

    do {
        if (((Ent4 *)((entity_index * 4) + (s32)((Ent4 *)D_800E3548)))->b1 != 0) {
            entities = (u8 *)((Ent12 *)D_800E36C8);
            entity = entities + entity_index * 12;
            U16(scratch, 0) = (U8(entity, 0) << 6) + 0x20;
            U16(scratch, 2) = (U8(entity, 1) << 6) + 0x20;
            world_z = U16(entity, 4);
            U16(scratch, 4) = world_z;
            sprite = *(u8 **)(entity + 8);
            U16(entity, 2) = world_z;
            depth = func_80065420(scratch, scratch + 0xB8, scratch + depth_offset, scratch + flags_offset);
            U32(scratch, 0xC0) = depth;
            U32(view_matrix, 0x1C) = depth * 4;
            U32(scratch, 0xC0) -= 2;
            sort_depth = U32(scratch, 0xC0);
            if ((u32)sort_depth < 0x1E0) {
                func_800649A0();
                matrix_or_prim = rotation_matrix;
                U16(scratch, 0xB8) = U16(scratch, 0xB8) - 0xA0;
                U16(scratch, 0xBA) = U16(scratch, 0xBA) - 0x78;
                U16(scratch, 0x100) = U16(render_params, 0x16);
                angle_z = U16(render_params, 0x1A) - camera_angles.b;
                U16(scratch, 0x104) = U16(render_state, 184) + angle_z;
                angle_y = (camera_angles.c + 0x100) & 0x1FF;
                angle_y_offset = U16(render_params, 0x18) - 0x100;
                U16(scratch, 0x102) = angle_y + angle_y_offset;
                func_80065820(scratch + 0x100, matrix_or_prim);
                vertex3 = scratch + 0x88;
                screen0 = scratch + 0xF0;
                screen1 = scratch + 0xF4;
                screen2 = scratch + 0xF8;
                screen3 = scratch + 0xFC;
                depth_out = scratch + 0x90;
                flags_out = scratch + 0x94;
                func_80064840(view_matrix, rotation_matrix, transform);
                func_80064D80(transform);
                func_80064CF0(transform);
                for (;;) {
                    if (!(U8(sprite, 0) & 0x20)) {
                        tex_u = U8(sprite, 0x8);
                        U32(scratch, 8) = tex_u;
                        tex_width = U8(sprite, 0xA);
                        U32(scratch, 0x10) = tex_width;
                        if (tex_u + tex_width >= 0x100) {
                            U32(scratch, 0x10) = tex_width - 1;
                        }
                        tex_v = U8(sprite, 0x9);
                        U32(scratch, 0xC) = tex_v;
                        tex_height = U8(sprite, 0xB);
                        U32(scratch, 0x14) = tex_height;
                        if (tex_v + tex_height >= 0x100) {
                            U32(scratch, 0x14) = tex_height - 1;
                        }
                        offset_x_byte = U8(sprite, 0x2);
                        quad_left = (s8)offset_x_byte;
                        S16(scratch, 0x80) = quad_left;
                        S16(scratch, 0x70) = quad_left;
                        quad_right = quad_left + U16(scratch, 0x10);
                        S16(scratch, 0x88) = quad_right;
                        S16(scratch, 0x78) = quad_right;
                        offset_y_byte = U8(sprite, 0x3);
                        quad_top = (s8)offset_y_byte;
                        S16(scratch, 0x7A) = quad_top;
                        S16(scratch, 0x72) = quad_top;
                        quad_bottom = quad_top + U16(scratch, 0x14);
                        S16(scratch, 0x8A) = quad_bottom;
                        S16(scratch, 0x82) = quad_bottom;
                        func_800654B0(vertex0, vertex1, vertex2, vertex3, screen0, screen1, screen2, screen3,
                            depth_out, flags_out);
                        U16(prim, 0x8) = U16(scratch, 0xF0) + U16(scratch, 0xB8);
                        U16(prim, 0xA) = U16(scratch, 0xF2) + U16(scratch, 0xBA);
                        U16(prim, 0x10) = U16(scratch, 0xF4) + U16(scratch, 0xB8);
                        U16(prim, 0x12) = U16(scratch, 0xF6) + U16(scratch, 0xBA);
                        U16(prim, 0x18) = U16(scratch, 0xF8) + U16(scratch, 0xB8);
                        U16(prim, 0x1A) = U16(scratch, 0xFA) + U16(scratch, 0xBA);
                        U16(prim, 0x20) = U16(scratch, 0xFC) + U16(scratch, 0xB8);
                        screen_bottom = U16(scratch, 0xFE) + U16(scratch, 0xBA);
                        U16(prim, 0x22) = screen_bottom;
                        visible = 0;
                        if ((u16)(U16(prim, 0x8) + 0x20) < 0x181) {
                            visible = (u16)(U16(prim, 0xA) + 0x20) < 0x121;
                        }
                        visible1 = 0;
                        if ((u16)(U16(prim, 0x10) + 0x20) < 0x181) {
                            visible1 = (u16)(U16(prim, 0x12) + 0x20) < 0x121;
                        }
                        visible2 = 0;
                        visible = visible | visible1;
                        if ((u16)(U16(prim, 0x18) + 0x20) < 0x181) {
                            visible2 = (u16)(U16(prim, 0x1A) + 0x20) < 0x121;
                        }
                        visible3 = 0;
                        visible |= visible2;
                        visible2 = visible;
                        if ((u16)(U16(prim, 0x20) + 0x20) < 0x181) {
                            visible3 = (u16)(screen_bottom + 0x20) < 0x121;
                        }
                        if ((visible2 | visible3) != 0) {
                            tex_right = U32(scratch, 0x10);
                            tex_left = U32(scratch, 8);
                            tex_bottom = U32(scratch, 0x14);
                            tex_top = U32(scratch, 0xC);
                            U32(scratch, 0x10) = tex_right + tex_left;
                            U32(scratch, 0x14) = (tex_bottom + tex_top) << 8;
                            U32(scratch, 0xC) <<= 8;
                            S32(prim, 0xC) = U32(scratch, 0xC) + U32(scratch, 8) + (U16(sprite, 0x6) << 16);
                            S32(prim, 0x14) = U32(scratch, 0xC) + U32(scratch, 0x10) + (S16(sprite, 0x4) << 16);
                            S16(prim, 0x1C) = U32(scratch, 0x14) + U32(scratch, 8);
                            S16(prim, 0x24) = U32(scratch, 0x14) + U32(scratch, 0x10);
                            if ((s16)U16(scratch, 0x50) >= 0x1800) {
                                U8(prim, 0x14) = U8(prim, 0x24)--;
                            }
                            if ((s16)U16(scratch, 0x58) >= 0x1800) {
                                U8(prim, 0x1D) = U8(prim, 0x25)--;
                            }
                            if (S16(prim, 0x8) > S16(prim, 0x20)) {
                                U8(prim, 0x14) = U8(prim, 0x14) - 1;
                                U8(prim, 0x24) = U8(prim, 0x24) - 1;
                            }
                            if (S16(prim, 0xA) > S16(prim, 0x22)) {
                                U8(prim, 0x1D) = U8(prim, 0x1D) - 1;
                                U8(prim, 0x25) = U8(prim, 0x25) - 1;
                            }
                            S32(prim, 0x4) = S32(render_params, 0xC);
                            func_800666F4(prim);
                            matrix_or_prim = prim;
                            func_8006658C(U32(scratch, 0x20) + U32(scratch, 0xC0) * 4, matrix_or_prim);
                            prim += 40;
                            func_800649A0();
                            shadow_scale.vz = (s32)(s16)(*(u16 *)(scratch + 4)) - 4;
                            shadow_scale.vz = ((shadow_scale.vz - (s32)(s16)(*(u16 *)(scratch + 4))) << 5) + 0x1000;
                            if (shadow_scale.vz < 0) {
                                shadow_scale.vz = 0;
                            }
                            U16(scratch, 0x102) = 0;
                            shadow_scale.vx = shadow_scale.vz;
                            shadow_scale.vy = shadow_scale.vz / 2;
                            U16(scratch, 0x100) = -camera_angles.a;
                            U16(scratch, 0x104) = U16(render_state, 184) - camera_angles.b;
                            func_80065820(scratch + 0x100, rotation_matrix);
                            func_80064840(matrix_page - 0x32D0, rotation_matrix, transform);
                            func_80064BC0(transform, &shadow_scale);
                            func_80064D80(transform);
                            func_80064CF0(transform);
                            U16(scratch, 0x70) = U16(scratch, 0x70) + 6;
                            U16(scratch, 0x78) = U16(scratch, 0x78) + 6;
                            func_800654B0(vertex0, vertex1, vertex2, vertex3, screen0, screen1, screen2, screen3,
                                depth_out, flags_out);
                            U16(prim, 0x8) = U16(scratch, 0xF0) + U16(scratch, 0xB8);
                            U16(prim, 0xA) = U16(scratch, 0xF2) + U16(scratch, 0xBA);
                            U16(prim, 0x10) = U16(scratch, 0xF4) + U16(scratch, 0xB8);
                            U16(prim, 0x12) = U16(scratch, 0xF6) + U16(scratch, 0xBA);
                            U16(prim, 0x18) = U16(scratch, 0xF8) + U16(scratch, 0xB8);
                            U16(prim, 0x1A) = U16(scratch, 0xFA) + U16(scratch, 0xBA);
                            U16(prim, 0x20) = U16(scratch, 0xFC) + U16(scratch, 0xB8);
                            U16(prim, 0x22) = U16(scratch, 0xFE) + U16(scratch, 0xBA);
                            S32(prim, 0xC) = U32(scratch, 0xC) + U32(scratch, 8) + 0x7FC00000;
                            S32(prim, 0x14) = U32(scratch, 0xC) + U32(scratch, 0x10) + (S16(sprite, 0x4) << 16);
                            S16(prim, 0x1C) = U32(scratch, 0x14) + U32(scratch, 8);
                            S16(prim, 0x24) = U32(scratch, 0x14) + U32(scratch, 0x10);
                            if (S16(prim, 0x8) > S16(prim, 0x20)) {
                                U8(prim, 0x14) = U8(prim, 0x14) - 1;
                                U8(prim, 0x24) = U8(prim, 0x24) - 1;
                            }
                            if (S16(prim, 0xA) > S16(prim, 0x22)) {
                                U8(prim, 0x1D) = U8(prim, 0x1D) - 1;
                                U8(prim, 0x25) = U8(prim, 0x25) - 1;
                            }
                            S32(prim, 0x4) = S32(render_params, 0xC);
                            func_800666F4(prim);
                            U8(prim, 0x7) = U8(prim, 0x7) | 2;
                            func_8006658C(U32(scratch, 0x20) + U32(scratch, 0xC0) * 4, prim);
                            prim += 40;
                            func_80064A40();
                        }
                    }
                    if (S8(sprite, 0) < 0) {
                        break;
                    }
                    sprite += 12;
                }
                func_80064A40();
            }
        }
        entity_index += 1;
    } while (entity_index < 64);
    *(u8 **)(*(u8 **)render_state + 0x8D0) = prim;
    return 0;
}
#include "common.h"
#include "shared/slus_callbacks.h"
#ifndef NULL
#define NULL 0
#endif
#define F(e,t,o) (*(t)((s8 *)(e)+(o)))
extern void * allocate_list_node(s32 flags, void **list_head);
extern s32 register_node(void *entry, s32 registration_id);
extern s32 get_item_category_value(u8 *item);
extern void create_tracked_effect(void *, s32, s32, s32);

/* Create a sprite object with the supplied position and default color and scale. */
void *create_item_render_object(s32 parent, s32 sprite_source, s16 x, s32 y, s16 z) {
    void *object;
    SpriteFrameState *sprite;
    void *position;

    object = allocate_list_node(0x12, (void *)parent);
    if (object != NULL) {
        position = F(object, void **, 8);
        sprite = F(object, void **, 0xC);
        F(position, s16 *, 2) = x;
        F(position, s16 *, 6) = y;
        F(position, s16 *, 0xA) = z;
        register_node(object, project_sprite_chain);
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->source = get_item_category_value((void *)sprite_source);
        create_tracked_effect(object, 0, 0, 0);
    }
    return object;
}
#include "common.h"

/* Removes an entry by shifting subsequent entries down and clearing the final slot. */
void compact_item_entry_table(s32 entry_index) {
    u8 *ptr = (u8 *)0x80010000;

    if (entry_index < 19) {
        ptr += entry_index * 4;
loop_0:
        {
            entry_index++;
            *(s32 *)(ptr + 0x29C) = *(s32 *)(ptr + 0x2A0);
            ptr += 4;
        }
        if (entry_index < 19)
            goto loop_0;
    }
    {
        u8 *page = (u8 *)0x80010000;
        s32 entry_offset;

        entry_offset = entry_index * 4;
        *(s32 *)(entry_offset + (u32)page + 0x29C) = 0;
    }
}
#include "modules/dungeon_engine_entity_effects_abi_views.h"
#include "modules/dungeon_engine_entity_effects_fragment_c2fbc.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

s32 resolve_record_orientation_or_fallback();
s32 dispatch_dungeon_category_action();
void unlink_entity_node();
s32 check_neighbor_tile_blocking();
void *find_eligible_actor_at_tile_and_height();
void set_record_integer_tile_center();
s32 place_item_at_valid_floor_position();
void emit_scattered_effects_unless_blocked();
extern M2C_UNK D_80081484;
extern u8 D_800DD7DC[];
extern s32 D_800E3540;

#define DUNGEON_FLAGS_PAGE ((s8 *)0x80080000)

typedef struct S_800A871C_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A871C_0;

typedef struct S_800A871C_1_pre {
    u16 unk_00;
} S_800A871C_1_pre;   /* the 0x2 bytes before r_arg0 in update_dropped_object_motion, addressed as r_arg0[-1] */

typedef struct S_800A871C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    s32 * unk_9C;
    s16 unk_A0;
    s16 unk_A2;
    s16 unk_A4;
} S_800A871C_1;   /* r_arg0 in update_dropped_object_motion */

typedef struct S_800A871C_2 {
    s16 unk_00;
} S_800A871C_2;   /* &sp18[2] in update_dropped_object_motion */

typedef struct S_800A871C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A871C_3;   /* r_arg1 in update_dropped_object_motion */

typedef struct S_800A871C_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x18];
    union { u8 n; u8 v; } unk_24;   /* accessed as both */
    union { u8 n; u8 v; } unk_25;   /* accessed as both */
} S_800A871C_4;   /* r_arg2 in update_dropped_object_motion */

typedef struct S_800A871C_5 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800A871C_5;

typedef struct S_800A871C_6 {
    s16 unk_00;
} S_800A871C_6;

typedef struct S_800A871C_7 {
    u8 unk_00;
} S_800A871C_7;

typedef struct S_800A871C_8 {
    u8 unk_00;
} S_800A871C_8;

typedef struct S_800A871C_9 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A871C_9;

typedef struct S_800A871C_11_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A871C_11_pre;   /* 0x14-byte header immediately before the payload. */

typedef struct S_800A871C_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800A871C_11;

typedef struct S_800A871C_12 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A871C_12;

typedef struct S_800A871C_13 {
    u8 unk_00;
} S_800A871C_13;

typedef struct S_800A871C_14 {
    u8 unk_00;
} S_800A871C_14;

typedef struct S_800A871C_15 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800A871C_15;

typedef struct S_800A871C_16 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800A871C_16;

typedef struct S_800A871C_17 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x28];
    s32 unk_48;
} S_800A871C_17;

typedef struct S_800A871C_18 {
    u8 unk_00;
} S_800A871C_18;

typedef struct S_800A871C_19 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_800A871C_19;

typedef struct S_800A871C_20 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    s32 ** unk_28;
    void * unk_2C;
} S_800A871C_20;   /* ((S_800A871C_1 *)r_arg0)->unk_90 in update_dropped_object_motion */

   /* ((S_800A871C_1 *)r_arg0)->unk_8C in update_dropped_object_motion */

typedef struct S_800A871C_22 {
    u8 pad_00[0x124];
    s32 unk_124;
} S_800A871C_22;

typedef struct S_800A871C_23 {
    s32 unk_00;
} S_800A871C_23;   /* ((S_800A871C_1 *)r_arg0)->unk_9C in update_dropped_object_motion */

typedef struct S_800A871C_24 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800A871C_24;   /* ((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_2C in update_dropped_object_motion */

typedef struct S_800A871C_25 {
    s32 unk_00;
} S_800A871C_25;   /* **((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_28 +
                                ((s32) ((S_800A871C_24 *)(((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_2C))->unk_02 * 4) in update_dropped_object_motion */

typedef struct S_800A871C_26 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800A871C_26;   /* ((S_800A871C_25 *)(**((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_28 +
                                ((s32) ((S_800A871C_24 *)(((S_800A871C_20 *)(((S_800A871C_1 *)r_arg0)->unk_90))->unk_2C))->unk_02 * 4)))->unk_00 in update_dropped_object_motion */

/* Updates an object's launch, movement, collisions, and landing. */
void update_dropped_object_motion(void *object, register void *motion, void *tile) {
    void *object_data;
    u16 offset[3];
    s16 move_ticks;
    s32 travel_steps;
    s16 ticks_left;
    s16 state;
    s16 land_height;
    s16 drop_height;
    s32 *payload;
    s32 next_dir_offset;
    s32 launch_dir_offset;
    s32 drop_dir_offset;
    s32 axis_origin;
    s32 axis_target;
    s16 direction;
    s32 dir_offset;
    u16 drop_heading;
    u16 steps_left;
    u16 launch_heading;
    u8 *next_y_step;
    u8 *launch_y_step;
    u8 *launch_x_steps;
    u8 *drop_x_steps;
    u8 *next_x_steps;
    S_800A871C_5 *launch_source;
    S_800A871C_9 *source_sprite;
    void *drop_sprite;
    S_800A871C_17 *hit_object;
    void *drop_source;
    u8 *y_steps;
    u8 *y_step;
    s32 target_height;
    s32 height_delta;
    u8 *world_page;
    EntityRec *height_source;
    s32 source_height;
    s32 dungeon_flags;
    s32 height;

    object_data = object;
    payload = (((S_800A871C_1 *)object_data)->unk_9C);
    if ((payload == &D_80081484) && (((S_800A871C_0 *)payload)->unk_01 == 0)) {
        (((S_800A871C_1 *)object_data)->unk_9C) = &D_800E3540;
    }
    state = ((S_800A871C_1 *)object)->unk_A0;
    switch (state) {
    case 0:
    {
        if ((*(s32 *)((u8 *)object_data + (0x1C))) & 0x200000) {
            (*(u16 *)((u8 *)object_data + (0x2A))) = (u16) ((S_800A871C_19 *)((*(void **)((u8 *)object_data
                + (0x60)))))->unk_2A;
            if (resolve_record_orientation_or_fallback(
                    ((S_800A871C_26 *)(((S_800A871C_25 *)(**((S_800A871C_20 *)(((S_800A871C_1 *)object)->unk_90))->unk_28
                        +
                                ((s32) ((S_800A871C_24 *)(((S_800A871C_20 *)(((S_800A871C_1 *)object)->unk_90))->unk_2C))->unk_02 * 4)))->unk_00))->unk_04,
                    ((S_800A871C_1 *)object)->unk_90, offset, 0) == 0) {
                ((S_800A871C_2 *)(&offset[2]))->unk_00 = -0x30;
            }
            ((S_800A871C_3 *)motion)->unk_08.at02.v =
                (s16) (((MovingPosition *)(((S_800A871C_1 *)object)->unk_8C))->unk_0A + offset[2]);
            ((S_800A871C_4 *)tile)->unk_24.n = (u8) ((S_800A871C_20 *)(((S_800A871C_1 *)object)->unk_90))->unk_24;
            ((S_800A871C_4 *)tile)->unk_25.n = (u8) ((S_800A871C_20 *)(((S_800A871C_1 *)object)->unk_90))->unk_25;
            set_record_integer_tile_center(motion, ((S_800A871C_4 *)tile)->unk_24.v, ((S_800A871C_4 *)tile)->unk_25.v);
            ((S_800A871C_1 *)object)->unk_A0 = (s16) ((u16) ((S_800A871C_1 *)object)->unk_A0 + 1);
            launch_source = (*(void * *)((u8 *)object_data + (0x60)));
            travel_steps = (*(s16 *)((u8 *)object_data + (0x8A)));
            launch_heading = launch_source->unk_2A;
            (*(s16 *)((u8 *)object_data + (0x6A))) = (s16) launch_heading;
            direction = (launch_heading >> 9) & 7;
            if (travel_steps != 0) {
                s16 *x_steps = (s16 *)((s8 *)dir_step_x);
                dir_offset = direction * 2;
                y_steps = (u8 *)((s8 *)dir_step_y);
                y_step = (u8 *)((unsigned long)dir_offset + (unsigned long)y_steps);
                target_height = effect_height_short((((((S_800A871C_4 *)tile)->unk_24.n + (*(s16 *)((u8 *)x_steps
                    + dir_offset) * travel_steps)) << 6) + 0x20) & 0xFFE0,
                    (((((S_800A871C_4 *)tile)->unk_25.n + (((S_800A871C_6 *)y_step)->unk_00 * travel_steps)) << 6)
                    + 0x20) & 0xFFE0, ((S_800A871C_3 *)motion)->unk_08.at02.v);
                if (target_height < 0x200) {
                    height_delta = target_height - ((S_800A871C_3 *)motion)->unk_08.at02.v;
                } else {
                    target_height = ((S_800A871C_3 *)motion)->unk_08.at02.v;
                    height_delta = ((S_800A871C_19 *)((*(void **)((u8 *)object_data + (0x60)))))->unk_88;
                    height_delta -= target_height;
                }
                ((S_800A871C_3 *)motion)->unk_14 = (s32) (height_delta << 0xF) / (s16) (*(u16 *)((u8 *)object_data
                    + (0x8A)));
            }
            launch_x_steps = (u8 *)((s8 *)dir_step_x);
            launch_dir_offset = direction * 2;
            ((S_800A871C_4 *)tile)->unk_24.n = (u8) (((S_800A871C_4 *)tile)->unk_24.n
                + ((S_800A871C_7 *)((u8 *)((unsigned long)launch_dir_offset + (unsigned long)launch_x_steps)))->unk_00);
            launch_y_step = (u8 *)((s8 *)dir_step_y) + launch_dir_offset;
            ((S_800A871C_4 *)tile)->unk_25.n = (u8) (((S_800A871C_4 *)tile)->unk_25.n
                + ((S_800A871C_8 *)launch_y_step)->unk_00);
            ((S_800A871C_1 *)object)->unk_A4 = 2;
            return;
        }
        source_sprite = ((S_800A871C_1 *)object)->unk_90;
        if ((resolve_record_orientation_or_fallback(source_sprite->unk_08, source_sprite, offset, 0) != 0)
            && ((*(s32 *)((u8 *)object_data + (0x1C))) & 0x80000)) {
            ((S_800A871C_1 *)object)->unk_A2 = 1;
            ((S_800A871C_3 *)motion)->unk_00.at02.v =
                (s16) (((MovingPosition *)(((S_800A871C_1 *)object)->unk_8C))->unk_02 + offset[0]);
            ((S_800A871C_3 *)motion)->unk_04.at02.v =
                (s16) (((MovingPosition *)(((S_800A871C_1 *)object)->unk_8C))->unk_06 + offset[1]);
            source_height = ((MovingPosition *)(((S_800A871C_1 *)object)->unk_8C))->unk_0A + offset[2];
            height_source = D_800814A8;
            ((S_800A871C_3 *)motion)->unk_08.at02.v = (s16) (source_height + 8);
            (*(u16 *)((u8 *)object_data + (0x88))) = ((u16)height_source->unk_88);
        } else if (((S_800A871C_1 *)object)->unk_A2 != 0) {
            if ((*(s32 *)((u8 *)object_data + (0x1C))) & 0x80000) {
                world_page = (u8 *)0x800E0000;
                goto check_completion;
            }
            {
                drop_source = (*(void **)((u8 *)object_data + (0x60)));
                drop_x_steps = (u8 *)((s8 *)dir_step_x);
                drop_heading = ((S_800A871C_11 *)drop_source)->unk_2A;
                drop_sprite = ((S_800A871C_11_pre *)drop_source)[-1].unk_00;
                (*(s16 *)((u8 *)object_data + (0x6A))) = (s16) drop_heading;
                drop_dir_offset = (drop_heading >> 8) & 0xE;
                ((S_800A871C_4 *)tile)->unk_24.n = (u8) (((S_800A871C_12 *)drop_sprite)->unk_24
                    + ((S_800A871C_13 *)((u8 *)((unsigned long)drop_dir_offset
                    + (unsigned long)drop_x_steps)))->unk_00);
                ((S_800A871C_4 *)tile)->unk_25.n = (u8) (((S_800A871C_12 *)drop_sprite)->unk_25
                    + ((S_800A871C_14 *)((u8 *)((s8 *)dir_step_y) + drop_dir_offset))->unk_00);
                set_record_integer_tile_center(motion, ((S_800A871C_4 *)tile)->unk_24.v, ((S_800A871C_4 *)tile)->unk_25.v);
                drop_height = effect_height_short((((S_800A871C_4 *)tile)->unk_24.n << 6) | 0x20,
                    (((S_800A871C_4 *)tile)->unk_25.n << 6) | 0x20, ((S_800A871C_3 *)motion)->unk_08.at02.v);
                if (drop_height >= 0x201) {
                    drop_height = (s16) (u16) ((S_800A871C_3 *)motion)->unk_08.at02.v;
                }
                place_item_at_valid_floor_position(((S_800A871C_4 *)tile)->unk_24.n, ((S_800A871C_4 *)tile)->unk_25.n, drop_height,
                    ((S_800A871C_4 *)tile)->unk_08, ((S_800A871C_1 *)object)->unk_9C);
                ((S_800A871C_1_pre *)object)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)object)[-1].unk_00 | 0x8000);
                dungeon_flags = object_flag_block.flags;
                height = ((S_800A871C_3 *)motion)->unk_08.at02.v;
                object_flag_block.flags = (s32) (dungeon_flags | 0x8000);
                ((S_800A871C_3 *)motion)->unk_08.at02.v = effect_height_short((((S_800A871C_4 *)tile)->unk_24.n << 6) | 0x20,
                    (((S_800A871C_4 *)tile)->unk_25.n << 6) | 0x20, height);
                emit_scattered_effects_unless_blocked(motion);
                unlink_entity_node(object_data);
                return;
            }
        } else {
            return;
        }
        world_page = (u8 *)0x800E0000;
check_completion:
        if (((S_800A871C_22 *)(((S_800A871C_15 *)world_page)->unk_3D7C))->unk_124 == 0) {
            void *finished_object = object_data;
            s8 *flags_page = DUNGEON_FLAGS_PAGE;
            s32 dungeon_flags;
            ((S_800A871C_1_pre *)object)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)object)[-1].unk_00 | 0x8000);
            dungeon_flags = ((S_800A871C_16 *)flags_page)->unk_14A0;
            dungeon_flags |= 0x8000;
            unlink_entity_node((((S_800A871C_16 *)flags_page)->unk_14A0 = dungeon_flags, finished_object));
            return;
        }
        break;
    }
    case 1:
        move_ticks = ((S_800A871C_1 *)object)->unk_A4;
        if (move_ticks != 0) {
            axis_target = ((S_800A871C_4 *)tile)->unk_24.n;
            axis_origin = ((S_800A871C_3 *)motion)->unk_00.at02.v;
            axis_target <<= 6;
            axis_origin -= 0x20;
            ((S_800A871C_3 *)motion)->unk_0C = (s32) (((axis_target - axis_origin) << 0x10) / move_ticks);
            axis_target = ((S_800A871C_4 *)tile)->unk_25.n;
            axis_origin = ((S_800A871C_3 *)motion)->unk_04.at02.v;
            axis_origin -= 0x20;
            axis_target <<= 6;
            ((S_800A871C_3 *)motion)->unk_10 = (s32) (((axis_target - axis_origin)
                << 0x10) / (s16) ((S_800A871C_1 *)object)->unk_A4);
        }
        ticks_left = (u16) ((S_800A871C_1 *)object)->unk_A4 - 1;
        ((S_800A871C_1 *)object)->unk_A4 = ticks_left;
        if ((ticks_left << 0x10) > 0) {
            break;
        }
        hit_object = find_eligible_actor_at_tile_and_height(object_data, ((S_800A871C_4 *)tile)->unk_24.n, ((S_800A871C_4 *)tile)->unk_25.n,
            (*(s16 *)((u8 *)object_data + (0x88))));
        if (hit_object != NULL) {
            if ((hit_object->unk_13 == 0x1F) && !(hit_object->unk_1C & 0x228) && (D_800DD7DC[0] != 0)) {
                hit_object->unk_14 = (s32) (hit_object->unk_14 | 0x800000);
                hit_object->unk_48 = ((S_800A871C_23 *)(((S_800A871C_1 *)object)->unk_9C))->unk_00;
                ((S_800A871C_1_pre *)object)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)object)[-1].unk_00 | 0x8000);
                object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
                unlink_entity_node(object_data);
                g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
                return;
            }
            if (dispatch_dungeon_category_action(hit_object, ((S_800A871C_1 *)object)->unk_9C, 0xD, object_data) != 0) {
                ((S_800A871C_1_pre *)object)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)object)[-1].unk_00 | 0x8000);
                object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
                unlink_entity_node(object_data);
                g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
                return;
            }
        }
        if ((check_neighbor_tile_blocking((*(s16 *)((u8 *)object_data + (0x6A))), motion, tile) << 0x10) != 0) {
            steps_left = (*(u16 *)((u8 *)object_data + (0x8A))) - 1;
            (*(u16 *)((u8 *)object_data + (0x8A))) = steps_left;
            if ((steps_left << 0x10) > 0) {
                set_record_integer_tile_center(motion, ((S_800A871C_4 *)tile)->unk_24.n, ((S_800A871C_4 *)tile)->unk_25.n);
                next_x_steps = (u8 *)((s8 *)dir_step_x);
                next_dir_offset = ((u16) (*(s16 *)((u8 *)object_data + (0x6A))) >> 8) & 0xE;
                ((S_800A871C_4 *)tile)->unk_24.n = (u8) (((S_800A871C_4 *)tile)->unk_24.n
                    + ((S_800A871C_18 *)((u8 *)((unsigned long)next_dir_offset
                    + (unsigned long)(u8 *)((s8 *)dir_step_x))))->unk_00);
                next_y_step = (u8 *)((s8 *)dir_step_y) + next_dir_offset;
                ((S_800A871C_4 *)tile)->unk_25.n = (u8) (((S_800A871C_4 *)tile)->unk_25.n + *next_y_step);
                ((S_800A871C_1 *)object)->unk_A4 = 2;
                break;
            }
        }
        land_height = effect_height_short((((S_800A871C_4 *)tile)->unk_24.n << 6) | 0x20, (((S_800A871C_4 *)tile)->unk_25.n << 6)
            | 0x20, ((S_800A871C_3 *)motion)->unk_08.at02.v);
        if (land_height >= 0x201) {
            land_height = (s16) (u16) ((S_800A871C_3 *)motion)->unk_08.at02.v;
        }
        place_item_at_valid_floor_position(((S_800A871C_4 *)tile)->unk_24.n, ((S_800A871C_4 *)tile)->unk_25.n, land_height,
            ((S_800A871C_4 *)tile)->unk_08, ((S_800A871C_1 *)object)->unk_9C);
        ((S_800A871C_1_pre *)object)[-1].unk_00 = (u16) (((S_800A871C_1_pre *)object)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
        unlink_entity_node(object_data);
        g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
    default:
        break;
    }
    ((S_800A871C_3 *)motion)->unk_00.at00.v = (s32) (((S_800A871C_3 *)motion)->unk_00.at00.v
        + ((S_800A871C_3 *)motion)->unk_0C);
    ((S_800A871C_3 *)motion)->unk_04.at00.v = (s32) (((S_800A871C_3 *)motion)->unk_04.at00.v
        + ((S_800A871C_3 *)motion)->unk_10);
    ((S_800A871C_3 *)motion)->unk_08.at00.v = (s32) (((S_800A871C_3 *)motion)->unk_08.at00.v
        + ((S_800A871C_3 *)motion)->unk_14);
}
#include "modules/dungeon_engine_entity_effects_storage.h"
#include "modules/dungeon_engine_entity_effects_fragment_c2fbc.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad0[8];
    void *field8;
    void *fieldC;
    void *field10;
} DungeonObject;

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[2];
    u16 fieldA;
} DungeonCoords;

typedef struct {
    u8 pad0[6];
    s16 field6;
    s32 field8;
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF[0xD];
    s16 field1C;
    s16 field1E;
} DungeonState;

typedef struct {
    u8 pad0[0x60];
    void *field60;
    u8 pad64[0x24];
    u16 field88;
    s32 field8C;
    s32 field90;
    u8 pad94[4];
    s32 field98;
    void *field9C;
} DungeonData;

typedef struct {
    u8 field0;
    u8 field1;
    u16 field2;
    u16 field4;
    u8 pad6[6];
} DungeonTile;

extern u8 D_800A871C[];

extern void * allocate_list_node(s32 flags, void **list_head);
extern s32 register_node(void *entry, s32 registration_id);
extern s32 clear_entry_flag_and_link_owner(void *);
extern s32 get_item_category_value(u8 *item);
extern void create_tracked_effect(void *, s32, s32, s32);

/* Creates a dungeon object at a tile or the supplied coordinates. */
void *create_indexed_floor_object(s32 object_key, DungeonCoords *source_coords, s32 unused,
                    DungeonData *source_data, s32 *init_data, s16 tile_id) {
    DungeonObject *object;
    DungeonData *data;
    DungeonCoords *coords;
    SpriteFrameState *state;
    DungeonTile *tiles;
    s32 init_value;

    object = allocate_list_node(0x110, object_key - 0x20);
    if (object != NULL) {
        data = (DungeonData *)((u8 *)object + 0x20);
        object->field10 = D_800A871C;
        coords = object->field8;
        state = object->fieldC;
        data->field60 = source_data;
        if (tile_id >= 0) {
            DungeonTile *tile;
            tiles = ((DungeonTile *)D_800E36C8);
            tile = &tiles[tile_id];
            coords->field2 = (tile->field0 << 6) + 0x20;
            coords->field6 = (tile->field1 << 6) + 0x20;
            coords->fieldA = tile->field2;
            data->field88 = tile->field4;
        } else {
            coords->field2 = source_coords->field2;
            coords->field6 = source_coords->field6;
            coords->fieldA = source_coords->fieldA;
            data->field88 = source_data->field88;
        }
        register_node(object, project_sprite_chain);
        state->color.c.b = 0x80;
        state->color.c.g = 0x80;
        state->color.c.r = 0x80;
        state->scale_y = 0x1000;
        state->scale_x = 0x1000;
        state->unk_06 = 2;
        state->source = get_item_category_value(init_data);
        data->field8C = *(s32 *)((u8 *)source_data - 0x18);
        data->field90 = *(s32 *)((u8 *)source_data - 0x14);
        init_value = *init_data;
        data->field9C = &data->field98;
        *(u8 *)((u8 *)data + 0x13) = 0xFF;
        data->field98 = init_value;
        clear_entry_flag_and_link_owner(object);
        create_tracked_effect(object, 0, 0, 0);
    }
    return object;
}
#include "modules/dungeon_engine_entity_effects_fragment_c2fbc.h"
#include "common.h"

/* Sets flag 0x400 and bitmap bits for items without flag 0x200 in selected item categories. */
void mark_category_items_flag_400(s32 group_bit) {
    DungeonGroup *group;
    s32 item_index;
    s32 item_offset;
    s32 group_index;
    s32 byte_index_bias;
    s32 group_bitset_offset;
    u32 ram_base;
    s32 bit_mask;
    s32 bit_index;
    u16 *item_flags;
    u16 flags;
    void *bitset_base;

    group_index = 0;
    ram_base = 0x80010000;
    bit_mask = 1;
    do {
        group = &D_80073414[group_index];
        if (((s32)*((u8 *)group + 1) >> group_bit) & 1) {
            item_index = 0;
            if (group->count != 0) {
                group_bitset_offset = group_index * 8;
                item_offset = 0;
                do {
                    item_flags = (u16 *)(item_offset + (s32)group->entries);
                    flags = *item_flags;
                    if (!(flags & 0x200)) {
                        *item_flags = flags | 0x400;
                        byte_index_bias = item_index;
                        bitset_base = (void *)(group_bitset_offset + (byte_index_bias / 8) + ram_base);
                        bit_index = item_index & 7;
                        *((u8 *) bitset_base + 0x5720) = (u8) (*((u8 *) bitset_base + 0x5720) | (bit_mask
                            << bit_index));
                    }
                    item_offset += sizeof(DungeonItem);
                } while (++item_index < (s32)group->count);
            }
        }
        group_index += 1;
    } while (group_index < 0x13);
}
#include "modules/dungeon_engine_entity_effects_fragment_c2fbc.h"
#include "common.h"

typedef struct {
    u8 index;
    u8 group;
} DungeonArg;

extern void item_clear_recorded_category_pair(u8, u8);

/* Updates the selected item through item_clear_recorded_category_pair and clears its flag 0x400 in the item category table. */
void clear_selected_item_flag_400(DungeonArg *selection)
{
    item_clear_recorded_category_pair(selection->group, selection->index);
    D_80073414[selection->group].entries[selection->index].flags &= 0xFBFF;
}
#include "modules/dungeon_engine_entity_effects_fragment_c2fbc.h"
#include "common.h"

typedef struct S_800A9160_0 {
    u8 pad_00[0x5720];
    u8 unk_5720;
} S_800A9160_0;

typedef struct S_800A9160_1 {
    u8 pad_00[0x5720];
    u8 unk_5720;
} S_800A9160_1;

typedef struct {
    u8 pad00[0x5720];
    u8 bits[1];
} RamPage;

/* Packs item flag 0x400 into a RAM bitset for each item category. */
void pack_item_flag_400_bitmap(void)
{
    DungeonGroup *item_category;
    DungeonGroup *cell_group;
    s32 group_bits_offset;
    s32 set_index;
    s32 bit_index;
    s32 cell_index;
    u8 *cell_offset;
    s32 group_index;
    s32 clear_index;
    s32 one = 0;
    S_800A9160_1 *bit_byte;
    RamPage *ram;

    group_index = 0;
    ram = (RamPage *)0x80010000;
    item_category = D_80073414;
    do {
        cell_index = 0;
        if (item_category->count != 0) {
            group_bits_offset = group_index * 8;
            cell_group = item_category;
            cell_offset = 0;
            do {
                if (!(cell_index & 7)) {
                    clear_index = cell_index;
                    ((S_800A9160_0 *)(group_bits_offset + (clear_index / 8) + (s32)ram))->unk_5720 = 0;
                }
                if (*(u16 *)(cell_offset + (s32)cell_group->entries) & 0x400) {
                    set_index = cell_index;
                    bit_byte = group_bits_offset + (set_index / 8) + (s32)ram;
                    bit_index = cell_index & 7;
                    one = 1;
                    bit_byte->unk_5720 =
                        bit_byte->unk_5720 |
                        (one << bit_index);
                }
                cell_offset += sizeof(DungeonCell);
            } while (++cell_index < (s32)cell_group->count);
        }
        group_index += 1;
        item_category += 1;
    } while (group_index < 0x13);
}

/* MECHANISM: Frameless leaf; typed 20-byte groups recover the two local do-loops
   and the outer +20 delay-slot stride. Held current/inner group roles plus an
   index-first 0x80010000 RAM address reproduce t2/t0 and the 0x5720 accesses.
   A preincrement condition emits count-load before index increment and closes. */
#include "shared/dungeon_item_entries.h"
#include "common.h"

extern s32 test_resident_bit(s32);
extern s32 has_recorded_value_pair(s32, s32);
extern s32 generate_random_value(void);
extern s32 random_dungeon_range_16(s32, s32);

extern s32 D_80012090[];
extern s16 D_8008146C;
extern s8 D_800DCF5A;
extern s16 D_800E3CCC;

/* Dungeon item pickup: run the one-off 0x11F9 event, then occasionally take one entry from the floor's item table. */
s32 select_random_eligible_item_entry(void *actor)
{
    s32 result;
    s32 state;
    s32 index;
    u8 *base;
    u8 *entry;
    u8 kind;

    result = 0;
    if (*(u8 *)((u8 *)actor + 0x13) == 0x20) {
        if (D_800E3CCC == 0) {
            D_800E3CCC = 1;
            state = *(s32 *)0x80012090;
            if (state == 0) {
                if (D_8008146C == 0x19) {
                    if (test_resident_bit(0x11F9) != 0) {
                        if (test_resident_bit(0x11FC) == 0) {
                            if ((s16)has_recorded_value_pair(0xD, 2) == 0) {
                                *(u8 *)&result = 2;
                                *((u8 *)&result + 1) = 0xD;
                                *(s16 *)((u8 *)*(void **)((u8 *)actor - 0x14) + 0x12) = 0xC;
                            }
                        }
                    }
                }
            }
        }
    }

    if (*(u8 *)&D_800DCF5A == 0) {
        return result;
    }
    if (*(u8 *)((u8 *)actor + 0x49) != 0) {
        return result;
    }
    if ((generate_random_value() & 3) != 0) {
        return result;
    }

    index = random_dungeon_range_16(1, 0x1F) & 0xFFFF;
    base = ((u8 *)D_800E3548);
    entry = &base[index * 4];
    kind = entry[1];
    if (kind == 0) {
        return result;
    }
    if (kind >= 0xB) {
        return result;
    }
    if (kind != 1) {
        return result;
    }
    if (entry[0] != 8) {
        return result;
    }
    result = *(s32 *)entry;
    *(s32 *)entry = 0;

    return result;
}

/* MECHANISM: A four-byte stack result and actor-only s0 lifetime produce the 0x20 frame.
   The literal D_80012090 read coalesces its address/load in v1; an unsigned lvalue gives lbu.
   Splitting table index, base, and entry moves sll after the held lui/addiu and closes reorder. */
