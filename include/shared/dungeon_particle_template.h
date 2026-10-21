#ifndef SHARED_DUNGEON_PARTICLE_TEMPLATE_H
#define SHARED_DUNGEON_PARTICLE_TEMPLATE_H

/* Twelve bytes are copied into particle +0x56. This is the observed
 * read span; the allocation beyond it is not established. */
typedef struct Packed12 {
    unsigned char bytes[12];
} Packed12;
extern Packed12 particle_sprite_template;

#endif
