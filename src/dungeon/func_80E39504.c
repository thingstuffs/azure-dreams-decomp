#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172D04_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
} S_80172D04_0;   /* script in func_80172D04 */






extern void func_800A2B04(void *, u8, u8);
extern s32 func_800A6D30(void);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);
extern void func_8017516C(void *, void *, void *, void *);
extern void func_80176480(void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170EE4[];
extern u8 D_80176640[];

/* Three-stage knockback script driven by the 0x9B step byte: stage 0 seeds the velocity from the facing table and picks the timer, stage 1 decays that velocity a quarter per frame, stage 2 steers back to the tile centre and ends by clearing the motion record. */
void func_80172D04(S_80172D04_0 *script, Rec_D_800E3D7C *motion, Rec_D_80082E80 *tile, void *actor)
{
    s16 timer;
    s32 value;
    s32 value2;
    s32 adjusted;
    s32 state;
    s32 random;
    s32 one;

    state = script->unk_9B;
    one = 1;
    if (state == one) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    func_80176480(motion, tile);
    func_800AD4D0(actor);
    motion->unk_0C.as_s32 =
        -*(s16 *)((u8 *)&D_8006CCD8 +
            ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 15;
    motion->unk_10.at00_s32.v =
        -*(s16 *)((u8 *)&D_8006CCE8 +
            ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 15;
    script->unk_9B++;

    if (((Rec_D_800E3D7C *)actor)->unk_28 == 0) {
        goto reset_motion;
    }
    random = func_800A6D30() & 3;
    if (tile->unk_14.at00_u16.v & 0x8000) {
        if (random == 0) {
            func_8017516C(script, motion, tile, actor);
        }
        script->unk_A8.s = -1;
        script->unk_96.s = 0;
        script->unk_9B = 2;
        return;
    }
    timer = -1;
    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x228) {
        timer = 8;
    }
    script->unk_96.s = timer;
    if (random != 0) {
        script->unk_A8.s = -1;
        goto state_1;
    }
    script->unk_A8.u = one;

state_1:
    value = motion->unk_0C.as_s32;
    adjusted = value;
    if (value < 0) {
        adjusted = value + 3;
    }
    value2 = motion->unk_10.at00_s32.v;
    motion->unk_0C.as_s32 = value - (adjusted >> 2);

    adjusted = value2;
    if (value2 < 0) {
        adjusted = value2 + 3;
    }
    motion->unk_10.at00_s32.v = value2 - (adjusted >> 2);

    timer = script->unk_A8.u - 1;
    script->unk_A8.u = timer;
    if ((timer << 16) == 0) {
        func_8017516C(script, motion, tile, actor);
    }

    if (script->unk_96.s > 0) {
        script->unk_96.u = script->unk_96.u - 1;
    } else if (tile->unk_14.at00_u16.v & 0x6000) {
        script->unk_96.s = 0;
    }

    if (script->unk_96.s != 0) {
        return;
    }
    if (((Rec_D_800E3D7C *)actor)->unk_28 != 0) {
        goto increment_state;
    }

reset_motion:
    motion->unk_14.as_s32 = 0;
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    func_800AAA54(script, motion, tile, D_80176640);
    return;

increment_state:
    script->unk_96.s = 8;
    script->unk_9B++;
    return;

state_2:
    timer = script->unk_96.s;
    if (timer != 0) {
        s32 sub, m;
        m = tile->unk_24;
        m <<= 6;
        sub = motion->unk_00.at02_s16.v - 0x20;
        motion->unk_0C.as_s32 = ((m - sub) << 15) / timer;
        sub = motion->unk_04.at02_s16.v - 0x20;
        motion->unk_10.at00_s32.v =
            (((tile->unk_25 << 6) - sub) << 15) /
            script->unk_96.s;
    }

    timer = script->unk_A8.u - 1;
    script->unk_A8.u = timer;
    if ((timer << 16) == 0) {
        func_8017516C(script, motion, tile, actor);
    }

    timer = script->unk_96.u - 1;
    script->unk_96.s = timer;
    if ((timer << 16) > 0) {
        return;
    }

    motion->unk_14.as_s32 = 0;
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    func_800A2B04(motion, tile->unk_24,
        tile->unk_25);
    {
        s32 *global;

        global = &D_80083460;
        value = *(s32 *)((u8 *)global + 0x10);
        if (value == (s32)((u8 *)actor - 0x20)) {
            *(s32 *)((u8 *)global + 0x10) = value & 0x7FFFFFFF;
        }
    }
    script->unk_8C = D_80170EE4;
}
