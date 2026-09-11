#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern void func_800A2B04(void *, u8, u8);

extern s16 D_80083228;
extern u8 D_80174A7C[];
extern u8 D_80170000[];


typedef struct S_801740F8_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_801740F8_0;   /* arg0 in func_801740F8 */

typedef struct S_801740F8_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801740F8_1;   /* arg2 in func_801740F8 */

typedef struct S_801740F8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_801740F8_2;   /* arg3 in func_801740F8 */


/* Updates a timed animation offset and restores the actor's directional animation. */
void func_801740F8(void *actor, void *transform, void *animation, void *motion)
{
    s32 timer;
    s16 next_timer;
    s32 state;
    u8 *anim_table;

    state = ((S_801740F8_0 *)actor)->unk_9B;
    if (state == 1) {
        goto update_offset;
    }
    if (state < 2) {
        if (state == 0) {
            goto init_animation;
        }
        return;
    } else {
        if (state == 2) {
            goto check_done;
        }
        if (state == 3) {
            goto restore_animation;
        }
        return;
    }

init_animation:
    anim_table = D_80170000 + 0x4A7C;
    if (((S_801740F8_1 *)animation)->unk_2C != anim_table) {
        (*(u8 * *)((u8 *)animation + (0x2C))) = anim_table;
        func_80047784(
            animation,
            *(u8 *)(((((D_80083228 + ((S_801740F8_2 *)motion)->unk_2A + 0x100) >> 9) & 7)) + (u32)anim_table),
            0);
    }
    ((S_801740F8_0 *)actor)->unk_98 |= 8;
    ((S_801740F8_2 *)motion)->unk_1C &= 0xF7FFFFFF;
    ((S_801740F8_0 *)actor)->unk_9E = 5;
    ((S_801740F8_0 *)actor)->unk_A4 = 0;
    ((S_801740F8_0 *)actor)->unk_9B++;

update_offset:
    timer = ((S_801740F8_0 *)actor)->unk_9E;
    ((S_801740F8_0 *)actor)->unk_90 -= ((S_801740F8_0 *)actor)->unk_A4;
    if (timer != 0) {
        ((S_801740F8_0 *)actor)->unk_A4 = -func_800644B8(timer * 0x199) << 10;
    }

    ((S_801740F8_0 *)actor)->unk_90 += ((S_801740F8_0 *)actor)->unk_A4;
    next_timer = (u16)((S_801740F8_0 *)actor)->unk_9E - 1;
    ((S_801740F8_0 *)actor)->unk_9E = next_timer;
    if (next_timer < 0) {
        ((S_801740F8_0 *)actor)->unk_90 = 0;
        ((S_801740F8_0 *)actor)->unk_98 &= 0xFFF7;
        ((S_801740F8_2 *)motion)->unk_1C |= 0x08000000;
        ((S_801740F8_0 *)actor)->unk_9B++;
    }

check_done:
    if (!(((S_801740F8_2 *)motion)->unk_1C & 0x08000000)) {
        goto end;
    }
    ((S_801740F8_0 *)actor)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
    func_800A2B04(transform, ((S_801740F8_1 *)animation)->unk_24, ((S_801740F8_1 *)animation)->unk_25);
    ((S_801740F8_0 *)actor)->unk_9B++;
    return;

restore_animation:
    if (((S_801740F8_1 *)animation)->unk_2C != D_80174A7C - 0x50) {
        (*(u8 * *)((u8 *)animation + (0x2C))) = D_80174A7C - 0x50;
        func_80047784(
            animation,
            (D_80174A7C - 0x50)[((D_80083228 + ((S_801740F8_2 *)motion)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

end:
    return;
}
