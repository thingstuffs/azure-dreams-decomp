#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80024600_arg1.h"


extern void func_80024A34();
extern void func_800478B8();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 D_800814A0;


typedef struct S_80024C0C_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x8];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_80024C0C_0;   /* arg0 in func_80024C0C */

typedef struct S_80024C0C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u16 unk_16;
} S_80024C0C_1;   /* object in func_80024C0C */



/* Move the effect toward its target, then expand and fade it until completion. */
void func_80024C0C(void *motion, void *position, void *effect) {
    register s32 direction_scale ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 target_x;
    s32 current_x;
    s32 next_x;
    s32 next_distance;
    register s32 past_target ASM_REG("$2");   /* MATCH: keep the merged comparison in retail's result register. */
    u16 size;
    u8 intensity;
    void *object;
    s32 *global_flags;
    s16 state;

    object = ((S_80024C0C_0 *)motion)->unk_00;
    ((S_80024C0C_1 *)object)->unk_14++;
    state = ((S_80024C0C_0 *)motion)->unk_04.s;
    if (state == 0) {
        goto moving;
    }
    if (state == 1) {
        goto fading;
    }
    return;

moving:
    ((Rec_D_80082E80 *)effect)->unk_1A.as_u16 += 0x200;
    direction_scale = func_800644B8(((S_80024C0C_0 *)motion)->unk_0E);
    direction_scale = (direction_scale >> 4) * (func_800644B8(((S_80024C0C_0 *)motion)->unk_10) >> 4);
    ((Rec_func_80024600_arg1 *)position)->unk_00 += direction_scale * 0x1C;
    direction_scale = func_800644B8(((S_80024C0C_0 *)motion)->unk_0E);
    direction_scale = (direction_scale >> 4) * (func_80064584(((S_80024C0C_0 *)motion)->unk_10) >> 4);
    ((Rec_func_80024600_arg1 *)position)->unk_04 += direction_scale * 0x1C;
    ((Rec_func_80024600_arg1 *)position)->unk_08 += (func_80064584(((S_80024C0C_0 *)motion)->unk_0E) >> 4) * 0x1C00;
    direction_scale = func_800644B8(((S_80024C0C_0 *)motion)->unk_0E);
    direction_scale = (direction_scale >> 4) * (func_800644B8(((S_80024C0C_0 *)motion)->unk_10) >> 4);
    current_x = ((Rec_func_80024600_arg1 *)position)->unk_00;
    state = ((S_80024C0C_0 *)motion)->unk_12;
    next_x = current_x + direction_scale * 0x1C;
    if (state != 0) {
        target_x = ((Rec_func_80024600_arg1 *)position)->unk_0C;
        past_target = target_x < current_x;
    } else {
        target_x = ((Rec_func_80024600_arg1 *)position)->unk_0C;
        past_target = current_x < target_x;
    }
    if (past_target) {
        s32 distance;

        distance = current_x - target_x;
        if (distance < 0) {
            distance = -distance;
        }
        ASM_KEEP(distance);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        next_distance = next_x - target_x;
        if (next_distance < 0) {
            next_distance = -next_distance;
        }
        if (next_distance < distance) {
            goto done;
        }
    }
    func_80024A34(motion, position, effect);
    ((S_80024C0C_0 *)motion)->unk_04.u++;
    return;

fading:
    if (((Rec_D_80082E80 *)effect)->unk_0C.at00_u8.v != 0) {
        intensity = ((Rec_D_80082E80 *)effect)->unk_0C.at02_u8.v - 0x20;
        ((Rec_D_80082E80 *)effect)->unk_0C.at02_u8.v = intensity;
        ((Rec_D_80082E80 *)effect)->unk_0C.at01_u8.v = intensity;
        ((Rec_D_80082E80 *)effect)->unk_0C.at00_u8.v = intensity;
    }
    size = ((Rec_D_80082E80 *)effect)->unk_1C.at02_u16.v + 0x400;
    ((Rec_D_80082E80 *)effect)->unk_1C.at02_u16.v = size;
    ((Rec_D_80082E80 *)effect)->unk_1C.at00_u16.v = size;
    func_800478B8(effect);
    func_800478B8(effect);
    if (((Rec_D_80082E80 *)effect)->unk_14.at00_u16.v & 0x6000) {
        object = ((S_80024C0C_0 *)motion)->unk_00;
        ((S_80024C0C_1 *)object)->unk_16++;
        global_flags = &D_800814A0;
        (*(u16 *)((u8 *)motion + (-2))) |= 0x8000;
        *global_flags |= 0x8000;
    }

done:
    return;
}
