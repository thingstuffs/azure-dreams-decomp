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

void func_800A85C0(void *arg0, void *arg1, s32 count) {
    LocalRecord local;
    void *data = arg1;
    register s32 i ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 value;

    if (count != 0) {
        i = 0;
        rand();
        local.z = *(u16 *)((u8 *)arg0 + 0xA);
        local.unk16 = -4;
        if (count > 0) {
            do {
                i++;
                local.x = (*(u16 *)((u8 *)arg0 + 2) +
                           func_800374F4(*(u16 *)data)) -
                          (*(s32 *)data / 2);
                local.y = (*(u16 *)((u8 *)arg0 + 6) +
                           func_800374F4(*(u16 *)((u8 *)data + 4))) -
                          (*(s32 *)((u8 *)data + 4) / 2);
                value = (*(u16 *)((u8 *)arg0 + 0xA) -
                         func_800374F4(*(u16 *)((u8 *)data + 8))) -
                        (*(s32 *)((u8 *)data + 8) / 2);
                local.z = value;
                func_800A84D0(&local, value);
            } while (i < count);
            ASM_KEEP(data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        }
    }
}

/* MECHANISM: One escaping 24-byte record preserves the fields at
   sp+0x12/+0x16/+0x1A/+0x26 and forces the retail 0x40 frame. Guarded pins hold
   data in s1 and the counter in s0; last-use ASM_KEEP leaves the prologue slot free.
   Loading local.z before storing -4 produces retail's lhu-v1 then li-v0 order. */
