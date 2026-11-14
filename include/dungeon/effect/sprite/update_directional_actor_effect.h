#ifndef DUNGEON_OVL_19A8800_H
#define DUNGEON_OVL_19A8800_H
#include "modules/dungeon_native_abi.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/spell_effect.h"

/* Spell state for spawned target effects and their delayed attack. */
typedef struct TimedTargetHitSpellBody {
    SpellEffectHeader spell;
    u8 pad_0C[0x44];
    s16 unk_50;
    union { s16 s; u16 u; } unk_52;
} TimedTargetHitSpellBody;
typedef struct FragmentSpawningEffectBody {
    void *owner;
} FragmentSpawningEffectBody;
struct MainObject;
struct DirectionalGridEffectBody;
struct ObjectPosition;
void update_directional_actor_effect(TimedTargetHitSpellBody *state, struct ObjectPosition *position);
s32 create_counted_sprite_effect(void *first_item);
void update_effect_and_spawn_fragments(struct MainObject *object);
void mark_referenced_object_and_update_flags(FragmentSpawningEffectBody *entry, void *unused, SpriteFrameState *target);
void update_directional_grid_segments(struct DirectionalGridEffectBody *effect);
#endif
