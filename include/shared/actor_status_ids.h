#ifndef SHARED_ACTOR_STATUS_IDS_H
#define SHARED_ACTOR_STATUS_IDS_H

/* IDs in the four actor status slots at +0x2C, shared by the resident
 * get_entity_effect_value/clear_slots_of_type helpers and dungeon handlers.
 * Names follow the status-end messages and the matching item handlers.
 * STATUS_SPEED uses the value's sign: positive is faster, negative is slower.
 * STATUS_DAMAGE_GUARD suppresses negative HP deltas; STATUS_NO_MP_DRAIN
 * makes spend_actor_mp ignore its base reduction. */
enum ActorStatusId {
    /* Behavioral slots: player-side conversion and tile occupancy suppression.
     * Anorexia is named explicitly by the feeding refusal text. */
    STATUS_PLAYER_SIDE = 0xB,
    STATUS_ANOREXIA = 0x19,
    STATUS_NO_TILE_OCCUPANCY = 0x1B,
    STATUS_SLEEP = 0x1,
    STATUS_CONFUSION = 0x2,
    STATUS_BLIND = 0x3,
    STATUS_PARALYSIS = 0x4,
    STATUS_POISON = 0x5,
    STATUS_MAGIC_BIND = 0x6,
    STATUS_SPEED = 0x7,
    STATUS_CURSE = 0x8,
    STATUS_ANGER = 0x9,
    STATUS_FROG = 0xA,
    STATUS_BRAINWASH = 0xC,
    STATUS_MP_DRAIN = 0xF,
    STATUS_FIRE_PROTECT = 0x12,
    STATUS_WATER_PROTECT = 0x13,
    STATUS_WIND_PROTECT = 0x14,
    STATUS_DAMAGE_GUARD = 0x1D,
    STATUS_NO_MP_DRAIN = 0x20,
};

#endif
