#ifndef DUNGEON_PLAYER_EQUIPMENT_STATUS_G00319_H
#define DUNGEON_PLAYER_EQUIPMENT_STATUS_G00319_H
/* Equipment status shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:dungeon/engine:800E07C0, PD:dungeon/engine:800E07D3. */

#include "common.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "m2c_compat.h"

typedef struct S_80098614_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x30];
    union { DungeonItemEntry * p; void * p2; } unk_50;   /* accessed as both */
    u8 pad_54[0x32];
    u8 unk_86;
} S_80098614_0;

extern u8 D_800E07C0[];
extern u8 D_800E07D3[];
extern s32 *actor_direction_sprites[];
/* Retail sets a3 to 10 at 0x80099114 before reading it; no incoming argument. */
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern void *write_text_byte_and_advance(s8 value, s8 *dest);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
void clear_alternate_texture_regions(s16 use_alt_rect);
void load_default_object_palette(short index);
int load_equipment_palette_for_category_sixteen(short index);
extern u8 D_80088B64[];
extern u8 D_800DD2B4[];
extern u8 D_800DD2C4[];
extern u8 D_800DD2D4[];
extern u8 D_800DD2E0[];
extern u8 D_800E080A[];
extern u8 D_800E081C[];
extern u8 D_800E0844[];
extern u8 D_800E0853[];
extern u8 D_800E0862[];
extern u8 unequipped_actor_sprite_sources[];
extern u8 equipped_actor_sprite_sources[];
void load_equipment_change_palette(short index);
extern u8 D_800DD2EC[];
extern u8 D_800E0874[];
extern u8 D_800E089C[];
extern u8 D_800E08AB[];
extern u8 D_800E08BA[];

struct DungeonItemEntry;
extern u8 *append_typed_formatted_value(struct DungeonItemEntry *, u8 *);

/* Functions defined in this translation unit. */
void change_equipped_item_and_notify(S_80098614_0 *actor, DungeonItemEntry *requested_item);

#endif
