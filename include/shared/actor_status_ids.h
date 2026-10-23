#ifndef SHARED_ACTOR_STATUS_IDS_H
#define SHARED_ACTOR_STATUS_IDS_H

/* Byte IDs in four actor status slots at +0x2C; 0 means empty, these values are not bit masks.
 * The next byte is a signed duration/value: nonzero counts toward zero per status update, zero does not time out.
 * get_entity_effect_value returns 0x100 for an active zero value and 0 for an absent named status. */
enum ActorStatusId {
    /* Behavioral slots: player-side conversion and tile occupancy suppression.
     * Anorexia is named explicitly by the feeding refusal text. */
    STATUS_PLAYER_SIDE = 0xB, /* temporarily sets current side; apply/end handlers move occupancy between the 0x300 and 0x3000 cell fields */
    STATUS_ANOREXIA = 0x19, /* feeding-refusal status, identified by the refusal text; duration follows the ordinary slot timer */
    STATUS_NO_TILE_OCCUPANCY = 0x1B, /* application removes actor occupancy; ending restores it and tries to reposition the actor */
    STATUS_SLEEP = 0x1, /* sets ACTOR_ASLEEP; adding sleep clears paralysis slots */
    STATUS_CONFUSION = 0x2, /* sets ACTOR_CONFUSED; end-status handler clears the bit and may print the recovery message */
    STATUS_BLIND = 0x3, /* sets ACTOR_BLIND and clears player-awareness; ending refreshes non-player proximity state */
    STATUS_PARALYSIS = 0x4, /* sets ACTOR_PARALYZED; adding paralysis clears sleep slots */
    STATUS_POISON = 0x5, /* sets ACTOR_POISONED; advance_status_timers applies poison damage before advancing the timer */
    STATUS_MAGIC_BIND = 0x6, /* sets ACTOR_MAGIC_BOUND; the end-status handler clears the active bit */
    STATUS_SPEED = 0x7, /* signed value selects faster (>0) or slower (<0) movement factors in apply_entity_effects */
    STATUS_CURSE = 0x8, /* sets ACTOR_CURSED; curse-removal items clear matching slots */
    STATUS_ANGER = 0x9, /* sets ACTOR_ANGRY; ending clears the bit */
    STATUS_FROG = 0xA, /* temporary frog form; ending restores the saved monster species and resource when needed */
    STATUS_BRAINWASH = 0xC, /* temporarily clears current player-side state; ending sets it again and updates cell occupancy */
    STATUS_MP_DRAIN = 0xF, /* doubles the reduction in spend_actor_mp after other MP-cost adjustments */
    STATUS_FIRE_PROTECT = 0x12, /* fire-protection slot; end_status_effect_message selects its elemental recovery text */
    STATUS_WATER_PROTECT = 0x13, /* water-protection slot; end_status_effect_message selects its elemental recovery text */
    STATUS_WIND_PROTECT = 0x14, /* wind-protection slot; end_status_effect_message selects its elemental recovery text */
    STATUS_DAMAGE_GUARD = 0x1D, /* checked by HP-delta handling to suppress negative damage; uses the ordinary slot timer */
    STATUS_NO_MP_DRAIN = 0x20, /* sets base MP reduction to zero in spend_actor_mp; the end handler may print the recovery text */
};

#endif
