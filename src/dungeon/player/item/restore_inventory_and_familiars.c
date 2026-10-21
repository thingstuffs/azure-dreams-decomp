#include "common.h"
#include "shared/sys_flags.h"
#include "shared/entity.h"

typedef struct S_80041E28_Dst S_80041E28_Dst;
typedef struct S_80041E28_Src S_80041E28_Src;
typedef struct CallbackObject CallbackObject;

struct S_800E3E48 {
    u8 pad00[0x14];
    s32 unk14;
    u8 pad18[0x1C - 0x18];
    s32 unk1C;
    u8 pad20[0x8C - 0x20];
};
typedef struct S_800E3E48 S_800E3E48;

typedef struct {
    u8 bytes[4];
} Unaligned4;

extern s32 familiar_record_slots[];
extern S_800E3E48 familiar_record_storage[];
extern s32 familiar_turn_counters_alias;
extern s16 D_800DCED4[];
extern u8 D_800E045C[];

extern void restore_actor_stats_from_snapshot(S_80041E28_Dst *dst, S_80041E28_Src *src);
extern void apply_actor_template_and_class(void *, s32, void *);
extern void call_script(s32 value);
extern void replay_actor_status_slots(CallbackObject *object);
extern void func_80042640(void *obj, s16 monsterId);
extern void update_owner_class_bits(void *entity);
extern s32 get_entity_class();





extern void equip_item_and_update_status();
extern void change_equipped_item_and_notify();
extern s32 find_valid_nearby_position();
extern void *(*load_monster_resource_data(s32 resource_id, s32 resource_slot, s32 wait_for_read))(s32, s16, s16, s16);
extern s32 retain_spawn_resource();
extern s32 find_or_retain_sprite_resource_slot();
extern s32 select_dungeon_spawn_tile();
extern void restore_item_flag_400_bitmap();
extern void *create_orbiting_teleport_effect();

typedef struct S_80094988_0 {
    u8 pad_00[0x2D50];
    u16 unk_2D50;
    u8 pad_2D52[0x6];
    s32 unk_2D58;
    u8 pad_2D5C[0x9B8];
    s16 unk_3714;
} S_80094988_0;   /* page in restore_inventory_and_familiars */

typedef struct S_80094988_1 {
    u8 pad_00[0xF8];
    u16 unk_F8;
    u8 pad_FA[0x2];
    s32 unk_FC;
} S_80094988_1;   /* dungeon in restore_inventory_and_familiars */

typedef struct S_80094988_4 {
    u8 pad_00[0x29C];
    s32 unk_29C;
} S_80094988_4;   /* save_page + scaled_i in restore_inventory_and_familiars */

typedef struct S_80094988_5 {
    u8 pad_00[0x2D52];
    u8 unk_2D52;
} S_80094988_5;

typedef struct S_80094988_6 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_80094988_6;

typedef struct S_80094988_7 {
    u8 pad_00[0x21E0];
    u8 unk_21E0;
    u8 unk_21E1;
} S_80094988_7;   /* (void *)probe in restore_inventory_and_familiars */

typedef struct S_80094988_9_pre {
    u8 unk_00;
    u8 pad_01[0x1];
} S_80094988_9_pre;   /* the 0x2 bytes before slot_flags in restore_inventory_and_familiars, addressed as slot_flags[-1] */

typedef struct S_80094988_9 {
    u8 unk_00;
} S_80094988_9;   /* slot_flags in restore_inventory_and_familiars */

typedef struct S_80094988_10 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_80094988_10;   /* cursor in restore_inventory_and_familiars */

typedef struct S_80094988_12 {
    u8 pad_00[0xAC];
    void * unk_AC;
    u8 pad_B0[0x20];
    void ** unk_D0;
} S_80094988_12;   /* slot_rec in restore_inventory_and_familiars */

typedef struct S_80094988_13 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
} S_80094988_13;   /* spawned in restore_inventory_and_familiars */

typedef struct S_80094988_15 {
    u8 pad_00[0x3714];
    s16 unk_3714;
} S_80094988_15;   /* save_page in restore_inventory_and_familiars */

/* Rebuild the dungeon's slot tables from the 0x80010000 save page: relink each of the 0x14 entries with its 0x8C record, re-point the two dispatch slots, then spawn and register an actor for every flagged party member. */
void restore_inventory_and_familiars(S_80094988_1 *dungeon, ActorRecord *actor, u16 base_x, u16 base_y) {
    s16 place_x;
    s16 place_y;
    u8 rand_x;
    u8 rand_y;
    u16 spawn_x;
    u16 spawn_y;
    u16 flag_was_set;
    u8 *slot_flags;
    u8 *page_base;
    s32 kind;
    u32 scratch;
    s32 slot_i;
    s32 i;
    u8 *slot_ptr;
    S_80094988_12 *slot_rec;
    S_80094988_13 *spawned;
    void *cursor;
    u8 *cursor_ptr;
    s16 entry_idx;
    u32 entry_idx32;
    u8 *save_page;
    void **dispatch_table;
    s32 ff2;
    s32 scaled_i;
    s32 sign_shift;
    s32 slot_index;
    s32 slot_offset;

    cursor_ptr = (u8 *)0x80010000;
    flag_was_set = (s16)((S_80094988_0 *)cursor_ptr)->unk_3714 & 2;
    ((S_80094988_0 *)cursor_ptr)->unk_3714 =
        (s16)((u16)((S_80094988_0 *)cursor_ptr)->unk_3714 | 2);
    spawn_x = base_x;
    spawn_y = base_y;
    restore_item_flag_400_bitmap();
    restore_actor_stats_from_snapshot(actor, (s32)cursor_ptr | 0x2194);
    dungeon->unk_F8 = (u16)((S_80094988_0 *)cursor_ptr)->unk_2D50;
    dungeon->unk_FC = (s32)((S_80094988_0 *)cursor_ptr)->unk_2D58;
    i = 0;
    do {
        *(Unaligned4 *)(cursor_ptr + 0x248 + i * 4) = *(Unaligned4 *)(cursor_ptr + 0x21E8 + i * 4);
        if (cursor_ptr[0x2238 + i] != 0xFF) {
            *(s32 *)(cursor_ptr + 0x29C + i * 4) = (s32)((void **)0x80010248 + cursor_ptr[0x2238 + i]);
        } else {
            *(s32 *)(cursor_ptr + 0x29C + i * 4) = 0;
        }
        familiar_record_storage[i] = *(S_800E3E48 *)(cursor_ptr + 0x2260 + i * 0x8C);
        entry_idx = cursor_ptr[0x224C + i];
        if (entry_idx != 0xFF) {
            entry_idx32 = entry_idx;
            familiar_record_slots[i] = (s32)&familiar_record_storage[entry_idx32];
        } else {
            familiar_record_slots[i] = 0;
        }
        i++;
    } while (i < 0x14);

    save_page = (u8 *)0x80010000;
    scaled_i = i * 4;
    ((S_80094988_4 *)(save_page + scaled_i))->unk_29C = 0;
    i = 0;
    page_base = save_page;
    ff2 = 0xFF;
    dispatch_table = (void **)(save_page + 0x248);
    do {
        entry_idx32 = (s32)((u8 *)(i + (u32)page_base));
        cursor_ptr = (u8 *)(((S_80094988_5 *)(u8 *)entry_idx32)->unk_2D52);
        if (((u8)cursor_ptr) != ff2) {
            ((S_80094988_6 *)((u8 *)dungeon + i * 4))->unk_D0 =
            (s32)((((u8)cursor_ptr) * 4) + (u32)dispatch_table);
        } else {
            ((S_80094988_6 *)((u8 *)dungeon + i * 4))->unk_D0 = 0;
        }
        i += 1;
    } while (i < 2);

    if (((S_80094988_7 *)0x80010000)->unk_21E0 != 0xFF) {
        slot_ptr = (u8 *)((void **)0x80010248 + ((S_80094988_7 *)0x80010000)->unk_21E0);
    } else {
        slot_ptr = 0;
    }
    equip_item_and_update_status(actor, slot_ptr);
    if (((S_80094988_7 *)0x80010000)->unk_21E1 != 0xFF) {
        slot_ptr = (u8 *)((void **)0x80010248 + ((S_80094988_7 *)0x80010000)->unk_21E1);
    } else {
        slot_ptr = 0;
    }
    change_equipped_item_and_notify(actor, slot_ptr);
    slot_ptr = (u8 *)0x80010248;
    slot_i = 0;
    slot_flags = (u8 *)0x8001024B;
    do {
        if (((S_80094988_9_pre *)slot_flags)[-1].unk_00 == 0x13) {
            i = 0;
            if (((S_80094988_9 *)slot_flags)->unk_00 & 0x20) {
                scratch = 0;
                cursor = dungeon;
                do {
                    if (((S_80094988_10 *)cursor)->unk_D0 == slot_ptr) {
                        scratch = i + 1;
                    }
                    i += 1;
                    cursor += 4;
                } while (i < 2);
                if ((scratch << 0x10) != 0) {
                    scratch -= 1;
                    kind = find_or_retain_sprite_resource_slot(*slot_ptr, 3);
                    if (kind != 0) {
                        if ((find_valid_nearby_position(0, (s16)spawn_x, (s16)spawn_y,
                                           &place_x, &place_y) << 0x10) == 0) {
                            do {
                            } while ((select_dungeon_spawn_tile(&rand_x, &rand_y) << 16) < 0);
                            place_x = (s16)rand_x;
                            place_y = (s16)rand_y;
                        }
                        spawned = load_monster_resource_data(*slot_ptr, kind, 1)(
                            1, place_x, place_y,
                            actor->ground_height);
                        sign_shift = scratch << 16;
                        slot_index = sign_shift >> 16;
                        slot_offset = slot_index * 4;
                        slot_rec = (void *)((u32)slot_offset +
                                            (u32)dungeon);
                        slot_rec->unk_AC = spawned;
                        if (spawned != 0) {
                            func_80042640(spawned,
                                          spawned->unk_13);
                            apply_actor_template_and_class(spawned,
                                          spawned->unk_13,
                                          slot_ptr);
                            slot_rec->unk_D0 = slot_ptr;
                            ((S_80094988_9 *)slot_flags)->unk_00 =
                                (u8)(((S_80094988_9 *)slot_flags)->unk_00 | 0x20);
                            ((s32 *)&familiar_turn_counters_alias)[slot_index] = 0;
                            if (spawned->unk_25 == 0) {
                                spawned->unk_1C =
                                    (s32)(spawned->unk_1C | 8);
                            }
                            familiar_record_slots[((S_80094988_9 *)slot_flags)->unk_00 & 0x1F] =
                                (s32)spawned;
                            update_owner_class_bits(spawned);
                            retain_spawn_resource(*slot_ptr, 3);
                            replay_actor_status_slots(spawned);
                            create_orbiting_teleport_effect(
                                spawned,
                                D_800DCED4[(scratch = get_entity_class(spawned))],
                                slot_index, 1);
                        }
                    }
                }
            }
        }
        slot_i += 1;
        slot_flags += 4;
        slot_ptr += 4;
    } while (slot_i < 0x14);
    if (flag_was_set == 0) {
        save_page = (u8 *)0x80010000;
        ((S_80094988_15 *)save_page)->unk_3714 =
            (s16)((u16)((S_80094988_15 *)save_page)->unk_3714 & 0xFFFD);
    }
    call_script(D_800E045C);
    return;
}
