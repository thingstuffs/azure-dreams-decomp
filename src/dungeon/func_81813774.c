#include "common.h"

typedef struct {
    s32 words[3];
} __attribute__((packed)) UnalignedBlock12;

typedef struct {
    UnalignedBlock12 chunks[2];
} UnalignedBlock24;

extern UnalignedBlock24 D_80029550;

/* Copies the 24-byte block at D_80029550 to the destination and returns it. */
UnalignedBlock12 *func_80028774(UnalignedBlock12 *dest) {
    dest[0] = D_80029550.chunks[0];
    dest[1] = D_80029550.chunks[1];
    return dest;
}

/* MECHANISM: Frameless leaf split into two packed 12-byte aggregate copies.
   Returning the destination makes the $v0 return value the store base, which
   yields retail's leading move $v0,$a0 and the $a0/$a1/$a2 copy registers. */
