#ifndef SHARED_ACTOR_PROPERTY_FLAGS_H
#define SHARED_ACTOR_PROPERTY_FLAGS_H

/* Actor +0x14 properties. Class enablement is the guard in get_entity_class;
 * +0x1C uses the same 0x2000 value for current side instead. Party membership
 * is also copied to +0x1C by familiar constructors. Resistance bits are set
 * by apply_entity_effects and suppress the matching active status. */
/* Genus bits are copied to live +0x1C too. apply_genus_change_item selects
 * the decoded fire/water/wind text when it writes 1/2/4 respectively. */
enum ActorPropertyFlags {
    ACTOR_ELEMENT_FIRE = 0x1,
    ACTOR_ELEMENT_WATER = 0x2,
    ACTOR_ELEMENT_WIND = 0x4,
    ACTOR_ELEMENT_MASK = 0x7,
    ACTOR_RESIST_BLIND = 0x10, /* blindness resistance; derived effect bit 0x08000000 installs this resistance and clears active blindness */
    ACTOR_RESIST_PARALYSIS = 0x20, /* paralysis resistance; derived effect bit 0x10000000 installs this resistance and clears active paralysis */
    ACTOR_RESIST_POISON = 0x40, /* poison resistance; derived effect bit 0x20000000 installs this resistance and clears active poison */
    ACTOR_RESIST_MAGIC_BIND = 0x80, /* magic-bind resistance; derived effect bit 0x40000000 installs it and clears active magic-bind */
    ACTOR_RESIST_SLEEP = 0x200, /* sleep resistance; derived effect bit 0x02000000 installs this resistance and clears active sleep */
    ACTOR_RESIST_CONFUSION = 0x400, /* confusion resistance; derived effect bit 0x04000000 installs it and clears active confusion */
    ACTOR_CLASS_ENABLED = 0x2000, /* get_entity_class returns class 0 unless set; enabled class selection uses the low three property bits */
    ACTOR_PARTY_MEMBER = 0x4000, /* familiar/party membership used by constructors and status-message gating; independent of temporary current side */
};

#endif
