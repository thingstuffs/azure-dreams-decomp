#include "common.h"

struct S_800475A4_Entry {
    u8 flags;
    u8 pad[0xB];
};

extern void func_80047338(struct S_800475A4_Entry *a0, s32 a1, u16 a2);

/* Walks a 0xC-byte-stride entry array starting at arg0. For each entry whose
   flags byte has neither bit 0x20 nor 0x40 set, decrements a rolling u16
   cursor (aliased onto the same entry memory, stepping 2 bytes at a time,
   independent of the entry stride) and invokes func_80047338(entry, *arg1,
   *cursor). Stops (do-while, tested after advancing to next entry) once an
   entry's flags & 0x80 bit is set. */
void func_800475A4(struct S_800475A4_Entry *arg0, s32 *arg1)
{
    struct S_800475A4_Entry *s0 = arg0;
    s32 *s2 = arg1;
    u16 *s1 = (u16 *)arg0;

    do {
        if (!(s0->flags & 0x60)) {
            s1--;
            func_80047338(s0, *s2, *s1);
        }
    } while (!((s0++)->flags & 0x80));
}
