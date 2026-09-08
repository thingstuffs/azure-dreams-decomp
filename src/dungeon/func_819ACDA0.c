#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_819ACDA0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_819ACDA0_0;   /* entity in func_819ACDA0 */

typedef struct S_819ACDA0_1 {
    u8 pad_00[0x2C];
    volatile u16 unk_2C;
} S_819ACDA0_1;   /* motion in func_819ACDA0 */




typedef struct {
    u8 pad0[0x14];
    s16 target_x;
    s16 target_y;
    s16 target_z;
    u8 pad1A[2];
    s16 current_x;
    s16 current_y;
    s16 current_z;
    u8 pad22[0xA];
    s16 state;
    u8 pad2E[2];
    s16 timer;
    u8 pad32[2];
    s16 effect_timer;
    u8 pad36[2];
    s16 phase;
} Motion;

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
    u8 padC[2];
    s16 next_x;
    u8 pad10[2];
    s16 next_y;
    u8 pad14[2];
    s16 next_z;
} Position;

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Origin;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u;

extern u8 D_80082E80[];
extern u16 D_80027450;
extern u8 D_80027452[16];
extern s16 D_80083228;
extern Origin D_80083780;
extern s32 D_800814A0;
extern void **D_800E3D18;
extern u8 *D_800E3D7C;

extern void func_800248E0(void) __attribute__((noreturn));
extern void func_800249C4(void) __attribute__((noreturn));
extern void func_800255B8(s16, s16, s16, s16);
extern void func_8002614C(s16, s16, s16, s16, s32);
extern void *func_8003DE58(void *, void *, u16 *, s32);
extern void func_800B8D64(s16, s16, s16);

void func_819ACDA0(Motion *motion, Position *position, u8 *color)
{
    Vec3u delta;
    Vec3u base;
    register Origin *origin;
    register u8 *entity;
    register u8 *source;
    register u16 final_state;
    s32 index;

    *(u16 *)D_80027452 = *(u16 *)D_80027452 + 1;

    if (motion->state == 1) {
        goto update_position;
    }
    if (motion->state >= 2) {
        goto check_upper_states;
    }
    if (motion->state == 0) {
        goto initialize;
    }
    func_800249C4();

check_upper_states:
    ASM_KEEP(color);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    if (motion->state == 2) {
        goto fade;
    }
    if (motion->state == 3) {
        goto effect;
    }
    func_800249C4();

initialize:
    origin = &D_80083780;
    base.x = origin->x;
    base.y = origin->y;
    entity = D_800E3D7C;
    base.z = ((S_819ACDA0_0 *)entity)->unk_88 - 0x50;
    index =
        ((D_80083228 + ((S_819ACDA0_0 *)entity)->unk_2A + 0x100) >> 7) & 0x1C;

    func_8003DE58(
        *(void **)(index + (s32)D_800E3D18),
        D_80082E80, &delta, 0);

    base.x += delta.x;
    motion->target_x = base.x;
    base.y += delta.y;
    motion->target_y = base.y;
    base.z += delta.z;
    motion->target_z = base.z;
    motion->state++;

update_position:
        position->next_x +=
            (motion->current_x +
                 ((motion->target_x - motion->current_x) / 8) *
                     (motion->phase + 1) -
             position->next_x) /
            motion->timer;

        position->next_y +=
            (motion->current_y +
                 ((motion->target_y - motion->current_y) / 8) *
                     (motion->phase + 1) -
             position->next_y) /
            motion->timer;

        position->next_z +=
            (motion->current_z +
                 ((motion->target_z - motion->current_z) / 8) *
                     (motion->phase + 1) -
             position->next_z) /
            motion->timer;

        motion->current_x += (position->next_x - motion->current_x) >> 2;
        position->x = motion->current_x;
        motion->current_y += (position->next_y - motion->current_y) >> 2;
        position->y = motion->current_y;
        motion->current_z += (position->next_z - motion->current_z) >> 2;
        position->z = motion->current_z;

        motion->timer--;
        if (motion->timer > 0) {
            return;
        }
        func_800B8D64(motion->target_x, motion->target_y, motion->target_z);
        final_state = ((S_819ACDA0_1 *)motion)->unk_2C;
        {
            register u16 five ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            five = 5;
            motion->timer = five;
        }
        func_800248E0();

fade:
    color[0xD] -= color[0xD] / motion->timer;
    motion->timer--;
    if (motion->timer > 0) {
        return;
    }
    if (motion->phase == 0) {
        color[0xD] = 0;
        motion->effect_timer = 4;
        D_80027450 = 0;
        motion->state++;
        func_800249C4();
    }
    goto finish;

effect:
    source = D_80082E80;
    if (func_8003DE58(*(void **)(source + 8), source, &base, 0) != 0) {
        func_8002614C(
            D_80083780.x + base.x,
            D_80083780.y + base.y,
            D_80083780.z + base.z,
            ((Rec_D_800E3D7C *)D_800E3D7C)->unk_2A.as_s16, 0);
    }

    motion->effect_timer--;
    if (motion->effect_timer > 0) {
        return;
    }
    func_800255B8(
        D_80083780.x,
        D_80083780.y,
        D_80083780.z - 0x20,
        ((Rec_D_800E3D7C *)D_800E3D7C)->unk_2A.as_s16);

finish:
    (*(u16 *)((u8 *)motion + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;
}
