#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8001F354_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_8001F354_0;   /* temp_v0 in func_8001F354 */

typedef struct S_8001F354_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8001F354_1;   /* temp_a0 in func_8001F354 */



extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80044BB0[3];
extern s32 D_800A5AF0[3];

/* Creates an object with the requested position, tint, and render parameter. */
void func_8001F354(s16 x, s16 y, s32 tinted, s32 render_param)
{
    register s16 saved_x ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 saved_render_param ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u16 flags;
    S_8001F354_1 *render_state;
    void *object;
    s16 *position;
    s16 *object_data;

    saved_render_param = render_param;
    ASM_KEEP_NV(saved_render_param);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    object = func_8003FC64(2);
    if (object != NULL) {
        saved_x = x;
        ASM_KEEP(saved_x);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ((S_8001F354_0 *)object)->unk_10 = (s32)D_800A5AF0;
        func_8004491C(object, D_80044BB0);
        position = (s16 *)((S_8001F354_0 *)object)->unk_08;
        position[1] = x + 0x280;
        position[3] = y;
        position[5] = 1;
        render_state = ((S_8001F354_0 *)object)->unk_0C;
        render_state->unk_1C = 0x2000;
        render_state->unk_1E = 0x1000;
        render_state->unk_08 = saved_render_param;
        if ((tinted << 0x10) != 0) {
            render_state->unk_0C = 0x202080;
        } else {
            render_state->unk_0C = 0x808080;
        }
        flags = render_state->unk_14;
        render_state->unk_10 = 0x20;
        object_data = (s16 *)(object + 0x20);
        render_state->unk_14 = flags | 0xC;
        object_data[3] = 0x18;
        object_data[4] = saved_x;
    }
}
