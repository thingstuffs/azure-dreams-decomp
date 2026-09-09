#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern s32 D_800814A0[3];

extern void func_8009A028();
extern void func_8009A21C();
extern void func_800A2B04();
extern void func_800A32A4();
extern s16 func_800BCB04();


typedef struct S_800AC5C8_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_800AC5C8_0;   /* arg0 in func_800AC5C8 */

typedef struct S_800AC5C8_1_pre {
    u16 unk_00;
} S_800AC5C8_1_pre;   /* the 0x2 bytes before arg3 in func_800AC5C8, addressed as arg3[-1] */



typedef struct S_800AC5C8_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800AC5C8_3;   /* arg2 in func_800AC5C8 */

/* Advance the object's timed animation and perform its final cleanup. */
s32 func_800AC5C8(S_800AC5C8_0 *animation, Rec_D_800E3D7C *position, S_800AC5C8_3 *tile, void *object) {
    s32 force;
    u16 ticks_left;
    s32 state;
    u8 tile_x;
    u8 tile_y;

    state = animation->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    return 0;

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    return 0;

state_0:
    ((Rec_D_80082E80 *)object)->unk_6A = ((Rec_D_80082E80 *)object)->unk_28.at02_u16.v & 0xFFF;
    animation->unk_9B++;
    /* fall through */

state_1:
    ((Rec_D_80082E80 *)object)->unk_28.at02_u16.v += 0x200;
    position->unk_14.as_s32 -= 0x10000;

    ticks_left = animation->unk_96 - 1;
    animation->unk_96 = ticks_left;
    if ((s16)ticks_left > 0) {
        return 0;
    }

    position->unk_14.as_s32 = 0;
    func_800A2B04(position, tile->unk_24, tile->unk_25);
    animation->unk_96 = 0x10;

    if (!(((Rec_D_80082E80 *)object)->unk_14.at00_s32.v & 0x4000)) {
        D_80083460.field_A--;
        func_800A32A4(object);
        func_8009A028(object);
        ((S_800AC5C8_1_pre *)object)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        goto return_zero;
    }

    ((Rec_D_80082E80 *)object)->unk_88.as_u16 = func_800BCB04(
        (tile->unk_24 << 6) | 0x20,
        (tile->unk_25 << 6) | 0x20,
        -0x400);
    animation->unk_98 &= 0xFFF7;
    ((Rec_D_80082E80 *)object)->unk_1C.at00_s32.v &= 0xFFFEFFFF;
    animation->unk_96 = 0x10;
    animation->unk_9B++;
    goto return_zero;

state_2:
    ((Rec_D_80082E80 *)object)->unk_28.at02_u16.v += 0x200;
    ticks_left = animation->unk_96 - 1;
    animation->unk_96 = ticks_left;
    if ((s16)ticks_left > 0) {
        return 0;
    }

    animation->unk_90 = 0;
    tile_x = tile->unk_24;
    tile_y = tile->unk_25;
    if (((Rec_D_80082E80 *)object)->unk_1C.at00_s32.v & 0x2000) {
        force = 0x300;
    } else {
        force = 0x3000;
    }
    func_8009A21C(tile_x, tile_y, force);
    {
        D_80083460_t *status;

        status = &D_80083460;
        status->field_A--;
    }
    {
        u16 saved_angle;
        s32 finished;

        saved_angle = ((Rec_D_80082E80 *)object)->unk_6A;
        finished = 1;
        ((Rec_D_80082E80 *)object)->unk_28.at02_u16.v = saved_angle;
        return finished;
    }
return_zero:
    return 0;
}
