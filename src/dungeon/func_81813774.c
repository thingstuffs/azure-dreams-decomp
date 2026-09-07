#include "common.h"

typedef struct {
    s32 words[3];
} __attribute__((packed)) UnalignedBlock12;

typedef struct {
    UnalignedBlock12 chunks[2];
} UnalignedBlock24;

extern UnalignedBlock24 D_80029550;

void func_80028774(UnalignedBlock12 *arg0) {
    register UnalignedBlock12 *dst ASM_REG("$2") = arg0;   /* MATCH pin: retail register colouring depends on it */

    ASM_KEEP(dst);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    dst[0] = D_80029550.chunks[0];
    dst[1] = D_80029550.chunks[1];
}

/* MECHANISM: Frameless leaf split into two packed 12-byte aggregate copies.
   A guarded $v0 destination hold under 2.7.2-cdk-G0 preserves the output base
   and yields retail's retained $v1 page plus $a0/$a1/$a2 copy registers. */
