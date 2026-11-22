#ifndef DUNGEON_ITEM_CALLBACKS_API_H
#define DUNGEON_ITEM_CALLBACKS_API_H

struct ActorRecord;

/* The linked fade factory initializes the counter and retains its source actor.
 * Its installed ascent callback advances the phase and draws this many streaks. */
typedef struct dungeon_return_magic_object {
    unsigned char pad_00[0x4A];
    short phase;
    unsigned short counter;
    unsigned char pad_4E[4];
    short streak_count;
    unsigned char pad_54[0x14];
    struct ActorRecord *owner;
} ReturnMagicAscentBody;

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct EffectState;
struct ObjectPosition;
struct RadialParticleBurstBody;
struct SpriteFrameState;
void advance_or_block_fading_record(struct RadialParticleBurstBody *state, struct ObjectPosition *motion, struct SpriteFrameState *record);
void animate_orbiting_effect_particle(struct EffectState *state, struct ObjectPosition *work, struct SpriteFrameState *color);
void update_return_magic_ascent(ReturnMagicAscentBody *obj, struct ObjectPosition *motion, struct SpriteFrameState *effect);

#endif
