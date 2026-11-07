#ifndef DUNGEON_ITEM_EFFECT_H
#define DUNGEON_ITEM_EFFECT_H
/* Prototypes of the functions defined in src/dungeon/item/effect/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"

struct EntityFields;
struct SpriteFrameState;

/* Body initialized by create_orbiting_teleport_effect. The installed updater
 * still uses its S_800C4F20_0/_10 views at the same offsets. */
typedef struct OrbitingTeleportEffectBody {
    u8 pad_00[0x1C];
    ObjectPosition *owner_position;
    struct SpriteFrameState *owner_sprite;
    ActorRecord *owner;
    s16 phase;
    s16 phase_ticks;
    s16 orbit_offset_phase;
    s16 orbit_angle;
    s16 effect_value;
    s16 size_offset;
    u8 pad_34[2];
    s16 exit_mode;
} OrbitingTeleportEffectBody;

/* create_linked_actor_fade_effect.c */
void *create_linked_actor_fade_effect(struct EntityFields *source);

/* create_orbiting_teleport_effect.c */
void *create_orbiting_teleport_effect(void *owner, s16 effect_value, s16 direction, s16 effect_mode);

/* create_return_magic_effect.c */
void *create_return_magic_effect(s32 value);

/* create_timed_paired_particle_emitter.c */
void create_timed_paired_particle_emitter(ObjectPosition *source, s32 effect_param, void *state_param);

/* spawn_radial_particle_burst.c */
void spawn_radial_particle_burst(s16 x, s16 y, s16 z, s16 flags, s32 unused);

/* tick_height_restore_effect.c */
void tick_height_restore_effect(u16 *entity);

/* update_orbiting_teleport_effect.c */
void update_orbiting_teleport_effect(void *anim, ObjectPosition *position, struct SpriteFrameState *transform);

#endif
