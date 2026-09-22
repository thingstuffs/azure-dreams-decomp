#include "common.h"


typedef void (*Callback)(void);

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);
extern s32 func_80071494(void);
extern void func_8028E170(void);
extern void func_8052FC8C(void);
extern u8 D_8003C558[];


typedef struct SpawnMotion {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} SpawnMotion;   /* motion in func_80814F08 */

typedef struct SpawnSeed {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
} SpawnSeed;   /* seed in func_80814F08 */

/* Spawn a 0x136 effect scattered +-20 around the seed, with a randomised vertical kick. */
void func_80814F08(SpawnSeed *seed) {
    void *sprite;
    SpawnMotion *motion;
    void *slot;

    slot = func_800373DC(0x136);
    if (slot != 0) {
        (*(Callback *)((u8 *)slot + 0x10)) = func_8052FC8C;
        func_8003BC18(slot, D_8003C558);
        motion = (*(void * *)((u8 *)slot + 8));
        sprite = (*(void * *)((u8 *)slot + 0xC));
        motion->unk_02 =
            (seed->unk_02 + (func_80071494() % 40)) - 0x14;
        motion->unk_06 =
            (seed->unk_06 + (func_80071494() % 40)) - 0x14;
        motion->unk_0A =
            (seed->unk_0A + (func_80071494() % 40)) - 0x14;
        motion->unk_0C = seed->unk_0C;
        motion->unk_14 =
            ((func_80071494() & 0x1FF) - 0x100) * 0x400;
        (*(s16 *)((u8 *)slot + 0x2E)) = 3;
        (*(s16 *)((u8 *)sprite + 0x1E)) = 0x1000;
        (*(s16 *)((u8 *)sprite + 0x1C)) = 0x1000;
        (*(Callback *)((u8 *)sprite + 8)) = func_8028E170;
        (*(s8 *)((u8 *)sprite + 4)) = 0;
        (*(s8 *)((u8 *)sprite + 5)) = 0;
        (*(s32 *)((u8 *)sprite + 0xC)) = 0x808080;
        (*(u16 *)((u8 *)sprite + 0x14)) |= 0xC;
    }
}
