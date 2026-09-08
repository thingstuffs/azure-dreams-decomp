#include "common.h"

#ifndef NULL
#define NULL 0
#endif


typedef long long s64_local;

typedef struct S_818B6954_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818B6954_0;   /* temp_v0 in func_818B6954 */

typedef struct S_818B6954_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_818B6954_1;   /* temp_v0_2 in func_818B6954 */

typedef struct S_818B6954_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818B6954_2;   /* temp_s0_2 in func_818B6954 */


extern s32 func_800242DC() __attribute__((noreturn));
extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 rand();

extern u8 D_800240B8[];
extern u8 D_80045340[];
extern u8 D_800DEC70[];

/* Create an object with randomized rotation and a radial position offset. */
s32 func_818B6954(s32 context_value, void *source_state, s32 render_param) {
    s16 offset_angle;
    register s32 coord_work ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 state_word_3;
    s64_local position_xy;
    s32 state_word_4;
    s32 state_word_5;
    register s32 object_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 offset_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 random_angle;
    s32 random_rotation;
    s32 angle_dividend;
    s32 rotation_dividend;
    S_818B6954_2 *render_state;
    void *object_state;
    register void *object ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_818B6954_1 *object_data;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        ((S_818B6954_0 *)object)->unk_10 = D_800240B8;
        object_data = (u8 *)object + 0x20;
        ((S_818B6954_0 *)object)->unk_20 = context_value;
        object_data->unk_04 = 0;
        object_data->unk_06 = 0;
        render_state = ((S_818B6954_0 *)object)->unk_0C;
        render_state->unk_0C = render_param;
        render_state->unk_12 = 0x7DCF;
        render_state->unk_14 |= 0xC;
        render_state->unk_10 |= 0x20;
        render_state->unk_14 |= 0x100;
        func_8003DB94(render_state, D_800DEC70, 0);
        rotation_dividend = rand();
        random_rotation = rotation_dividend;
        if (random_rotation < 0) {
            rotation_dividend = random_rotation + 0xFFF;
        }
        ASM_KEEP(random_rotation);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        render_state->unk_1A = random_rotation - ((rotation_dividend >> 0xC) << 0xC);
        render_state->unk_1E = 0xC00;
        render_state->unk_1C = 0xC00;
        func_8004491C(object, D_80045340);
        object_state = ((S_818B6954_0 *)object)->unk_08;
        position_xy = (*(s64_local *)((u8 *)source_state + 0));
        coord_work = (*(s32 *)((u8 *)source_state + 8));
        state_word_3 = (*(s32 *)((u8 *)source_state + 0xC));
        (*(s64_local *)((u8 *)object_state + 0)) = position_xy;
        (*(s32 *)((u8 *)object_state + 8)) = coord_work;
        (*(s32 *)((u8 *)object_state + 0xC)) = state_word_3;
        state_word_4 = (*(s32 *)((u8 *)source_state + 0x10));
        state_word_5 = (*(s32 *)((u8 *)source_state + 0x14));
        (*(s32 *)((u8 *)object_state + 0x10)) = state_word_4;
        (*(s32 *)((u8 *)object_state + 0x14)) = state_word_5;
        random_angle = rand(coord_work, state_word_3);
        angle_dividend = random_angle;
        if (random_angle < 0) {
            angle_dividend = random_angle + 0xFFF;
        }
        offset_angle = random_angle - ((angle_dividend >> 0xC) << 0xC);
        (*(s32 *)((u8 *)object_state + 0)) += (func_80064584(offset_angle) >> 4) * 0x1200;
        coord_work = func_800644B8(offset_angle) >> 4;
        object_result = (s32)object;
        ASM_KEEP(object_result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        offset_y = coord_work * 0x1200;
        coord_work = (*(s32 *)((u8 *)object_state + 4)) + offset_y;
        (*(s32 *)((u8 *)object_state + 4)) = coord_work;
        func_800242DC(coord_work);
    }
    return 0;
}
