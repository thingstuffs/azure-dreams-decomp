#ifndef DUNGEON_OVL_1972800_H
#define DUNGEON_OVL_1972800_H
struct SpriteFrameState;
#include "modules/dungeon_native_abi.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/effect/spell_effect.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"
#include "dungeon/effect/motion.h"
/* Spell state for model launch, target color, and completion timing. */
typedef struct TimedModelTintSpellBody {
    SpellEffectHeader spell;
    u8 pad_0C[0x8];
    union { u16 u; s16 s; } unk_14;
    u16 unk_16;
    s16 unk_18;
} TimedModelTintSpellBody;

void update_directional_actor_effect(TimedModelTintSpellBody *, void *);
void update_spiraling_effect_growth_and_fade(SpiralingBody *, ObjectPosition *, struct SpriteFrameState *);
void spawn_spiral_effect(void *, s16, s16, void *, s32);
void update_spiral_spawner(void *);
void create_spiral_spawner(ObjectNodeHeader *, s16, s16, ActorRecord *);
#include "dungeon/effect/screen.h"
#include "sdk/libgte.h"
extern u8 D_800DF334[];
extern u8 linked_mesh_processor_address[];
extern u8 D_80024980[];
extern u8 directional_effect_sprite_data[];
extern s16 D_800249A4;
extern u16 D_800249A6[5];
#endif
