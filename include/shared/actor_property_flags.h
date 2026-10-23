#ifndef SHARED_ACTOR_PROPERTY_FLAGS_H
#define SHARED_ACTOR_PROPERTY_FLAGS_H

/* Actor +0x14 properties. Class enablement is the guard in get_entity_class;
 * +0x1C uses the same 0x2000 value for current side instead. Party membership
 * is also copied to +0x1C by familiar constructors. Resistance bits are set
 * by apply_entity_effects and suppress the matching active status. */
enum ActorPropertyFlags {
    ACTOR_RESIST_BLIND = 0x10,
    ACTOR_RESIST_PARALYSIS = 0x20,
    ACTOR_RESIST_POISON = 0x40,
    ACTOR_RESIST_MAGIC_BIND = 0x80,
    ACTOR_RESIST_SLEEP = 0x200,
    ACTOR_RESIST_CONFUSION = 0x400,
    ACTOR_CLASS_ENABLED = 0x2000,
    ACTOR_PARTY_MEMBER = 0x4000,
};

#endif
