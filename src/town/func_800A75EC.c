#include "common.h"

typedef struct Func800A75ECState {
    s32 *current;
    s32 *previous;
    s32 center_x;
    s32 center_y;
    s32 center_z;
    s32 unk14;
    s32 unk18;
    s32 unk1c;
    s32 unk20;
    s32 unk24;
    void (*callback)(void *);
    s32 *other;
} Func800A75ECState;

extern void func_800A4E0C(void);
extern void func_800A4E1C(void *arg0);

void func_800A4D4C(Func800A75ECState *arg0) {
    s32 *current;

    current = arg0->current;
    if (current != arg0->previous) {
        arg0->unk20 = 9;
        arg0->callback = func_800A4E1C;
        arg0->unk14 = 0;
        arg0->unk18 = 0;
        arg0->unk1c = 0;
        arg0->previous = arg0->current;
        func_800A4E1C(arg0);
        return func_800A4E0C();
    }
    arg0->center_x = (current[0] + arg0->other[0]) / 2;
    arg0->center_y = (arg0->current[1] + arg0->other[1]) / 2;
    arg0->center_z = (arg0->current[2] + arg0->other[2]) / 2;
}

/* MECHANISM: Preserve the seed's 0x18 frame, sole $ra save, and existing live-range splits.
   The cdk-G0 lineage schedules previous=current into the jal slot and LEAD 22 forms the tail j.
   Config orientation removes plain 2.7.2-G0's two-word move/lw code-motion residue. */
