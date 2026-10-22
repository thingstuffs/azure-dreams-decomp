#ifndef SHARED_DUNGEON_PARTICLE_TEMPLATE_H
#define SHARED_DUNGEON_PARTICLE_TEMPLATE_H

/* Twelve bytes are copied into particle +0x56. This is the observed
 * read span; the allocation beyond it is not established. */
/* Twelve-byte sprite template copied into effect particle data.
 * Particle constructors read particle_sprite_template; this view claims only the copied span. */
typedef struct Packed12 {
    unsigned char bytes[12]; /* 12-byte template copied to particle +0x56 */
} Packed12;
extern Packed12 particle_sprite_template;

#endif
