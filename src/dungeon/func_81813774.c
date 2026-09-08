#include "common.h"

typedef struct {
    s32 words[3];
} __attribute__((packed)) UnalignedBlock12;

typedef struct {
    UnalignedBlock12 chunks[2];
} UnalignedBlock24;

extern UnalignedBlock24 D_80029550;

/* Copies the 24-byte block at D_80029550 to the destination. */
void func_80028774(UnalignedBlock12 *dest) {
    register UnalignedBlock12 *dst ASM_REG("$2") = dest;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    ASM_KEEP(dst);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    dst[0] = D_80029550.chunks[0];
    dst[1] = D_80029550.chunks[1];
}

/* MECHANISM: Frameless leaf split into two packed 12-byte aggregate copies.
   A guarded $v0 destination hold under 2.7.2-cdk-G0 preserves the output base
   and yields retail's retained $v1 page plus $a0/$a1/$a2 copy registers. */
