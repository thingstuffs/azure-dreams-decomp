#include "common.h"

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
    u8 padC[10];
    s16 unk16;
} LocalRecord;

extern s32 func_800374F4(u16);
extern void rand(void);
extern void func_800A84D0(LocalRecord *, s32);

/* Builds and submits records at randomized offsets from the origin. */
void func_800A85C0(void *origin, void *spread, s32 count) {
    LocalRecord record;
    register s32 index ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 z;

    if (count != 0) {
        index = 0;
        rand();
        record.z = *(u16 *)((u8 *)origin + 0xA);
        record.unk16 = -4;
        if (count > 0) {
            do {
                index++;
                record.x = (*(u16 *)((u8 *)origin + 2) +
                           func_800374F4(*(u16 *)spread)) -
                          (*(s32 *)spread / 2);
                record.y = (*(u16 *)((u8 *)origin + 6) +
                           func_800374F4(*(u16 *)((u8 *)spread + 4))) -
                          (*(s32 *)((u8 *)spread + 4) / 2);
                z = (*(u16 *)((u8 *)origin + 0xA) -
                         func_800374F4(*(u16 *)((u8 *)spread + 8))) -
                        (*(s32 *)((u8 *)spread + 8) / 2);
                record.z = z;
                func_800A84D0(&record, z);
            } while (index < count);
        }
    }
}

/* MECHANISM: One escaping 24-byte record preserves the fields at
   sp+0x12/+0x16/+0x1A/+0x26 and forces the retail 0x40 frame. Guarded pins hold
   ranges in s1 and the counter in s0; last-use ASM_KEEP leaves the prologue slot free.
   Loading record.z before storing -4 produces retail's lhu-v1 then li-v0 order. */
