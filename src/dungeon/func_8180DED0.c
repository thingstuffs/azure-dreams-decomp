#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80026ED0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80026ED0_0;   /* temp_v0 in func_80026ED0 */

typedef struct S_80026ED0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80026ED0_1;   /* temp_v0_2 in func_80026ED0 */

typedef struct S_80026ED0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80026ED0_2;   /* temp_v1 in func_80026ED0 */

typedef struct S_80026ED0_3 {
    u8 pad_00[0x66];
    s16 unk_66;
    u8 pad_68[0x2];
    s16 unk_6A;
} S_80026ED0_3;   /* temp_v1_2 in func_80026ED0 */



extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 D_80026E3C;
extern s32 D_80045340;
extern s32 D_80083498;
extern s32 D_800DF358;

/* Creates a visual object with the given position and size. */
void *func_80026ED0(s16 x, s16 y, s16 z, s16 size) {
    void *object;
    S_80026ED0_1 *position;
    S_80026ED0_2 *render_data;
    S_80026ED0_3 *effect_data;
    register s16 saved_size ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    saved_size = size;

    object = func_8003FD64(0x12, &D_80083498);
    ASM_KEEP(saved_size);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (object != NULL) {
        ((S_80026ED0_0 *)object)->unk_10 = &D_80026E3C;
        func_8004491C(object, &D_80045340);
        position = ((S_80026ED0_0 *)object)->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        render_data = ((S_80026ED0_0 *)object)->unk_0C;
        render_data->unk_08 = &D_800DF358;
        render_data->unk_0C = 0x808080;
        render_data->unk_1E = saved_size;
        render_data->unk_1C = saved_size;
        render_data->unk_10 = 0x20;
        render_data->unk_14 |= 0xC;
        effect_data = (u8 *)object + 0x20;
        effect_data->unk_66 = 0x20;
        effect_data->unk_6A = 0x80;
    }
    return object;
}
