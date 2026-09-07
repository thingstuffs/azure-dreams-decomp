#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
} TownRecord;

extern s16 D_800834C8;
extern s32 D_80083780;
extern s32 D_80100E40;

void func_800AAF5C(void)
{
    s32 destination_offset;
    s32 i;
    u8 *base;
    volatile TownRecord *destination;
    volatile TownRecord *source;

    i = 7;
    base = (u8 *)&D_80100E40;
    do {
        ASM_KEEP(i);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        destination_offset = i * 8;
        i--;
        source = (TownRecord *)((i * 8) + (u32)base);
        destination = (TownRecord *)(destination_offset + (u32)base);
        destination->field_0 = source->field_0;
        destination->field_2 = source->field_2;
        destination->field_4 = source->field_4;
        ((TownRecord *)destination)->field_6 = source->field_6;
    } while (i > 0);

    {
        u16 *tail_source;
        TownRecord *tail_destination;

        tail_source = (u16 *)&D_80083780;
        tail_destination = (TownRecord *)&D_80100E40;
        tail_destination->field_0 = tail_source[1];
        tail_destination->field_2 = tail_source[3];
        tail_destination->field_4 = tail_source[5];
        tail_destination->field_6 = D_800834C8;
    }
}

/* MECHANISM: Frameless leaf with explicit volatile halfword copies in the descending loop.
   Guarded runtime pins encode the a1 index, a0 destination offset, and v1 source roles;
   the loop-head index fence keeps its sll below the backedge and frees the branch slot.
   The final nonvolatile store can fill the branch slot; loop/tail bases stay split. */
