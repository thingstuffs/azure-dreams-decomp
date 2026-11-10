#ifndef DUNGEON_OVL_1954800_H
#define DUNGEON_OVL_1954800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/effect/spell_effect.h"
#include "shared/slus_callbacks.h"
#include "sdk/libc.h"

typedef struct DungeonCell {
    s16 flags;
    u8 pad02[0x12];
} DungeonCell;

typedef struct DungeonGroup {
    u8 pad00[0xC];
    DungeonCell *cells;
    u8 pad10[4];
} DungeonGroup;

typedef struct DungeonObjectEntry {
    u8 column;
    u8 group;
    s8 amount;
    u8 pad03[0x11];
} DungeonObjectEntry;

typedef struct DungeonObject {
    u8 pad00[0x4C];
    DungeonObjectEntry *entry4C;
    DungeonObjectEntry *entry50;
} DungeonObject;

extern DungeonGroup item_category_groups[];

/* Decrement eligible entry amounts on flagged cells and return the number changed. */

#ifndef NULL
#define NULL 0
#endif

/* Spell state for the falling particle field and its timed attack. */
typedef struct FallingParticleFieldSpellBody {
    SpellEffectHeader spell;
    u16 unk_0C;
    u16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
} FallingParticleFieldSpellBody;

typedef struct {
    s32 word[6];
} Copy24;

extern s32 random_particle_update_address[];
extern s32 D_80024740[];

/* Spawns a timed particle effect, processes its midpoint target, and marks completion. */

#ifndef NULL
#define NULL 0
#endif

typedef struct FallingParticleEffectBody {
    void * unk_00;
    u8 pad_04[0x8];
    u16 unk_0C;
    s16 unk_0E; /* initialized by the falling-particle creator */
    u16 unk_10;
    u8 pad_12[0xA];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_1C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_20;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_24;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_28;   /* overlapping accesses */
    u8 pad_2C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_30;   /* overlapping accesses */
    u8 pad_34[0x14];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} FallingParticleEffectBody;   /* particle node body passed to draw_red */

typedef struct S_81934C5C_1 {
    u8 pad_00[0xE];
    u16 unk_0E;
} S_81934C5C_1;   /* temp_v1 in func_8002445C */

typedef struct S_81934C5C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81934C5C_2;   /* temp_v0_3 in func_8002445C */

typedef struct S_81934C5C_4 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_81934C5C_4;   /* temp_spawn_base in func_8002445C */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80024928;
#include "shared/sprite_source.h"
extern SpriteSourceEntry rising_sprite_entries[];
extern SpriteSourceEntry moving_sprite_entries[];

/* Updates effect motion and spawns an impact effect on reaching the surface. */

extern void (*const D_80024000)(FallingParticleFieldSpellBody *, void *);


void *allocate_list_node(s32, void *);
void register_node(void *, void *);
void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);
s16 sample_terrain_surface_height();
s32 decrement_flagged_item_parameters(DungeonObject *object);
void update_random_particle_field(FallingParticleFieldSpellBody *self, void *output);
void draw_red(FallingParticleEffectBody *effect);
#endif
