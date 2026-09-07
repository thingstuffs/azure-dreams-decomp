#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_808138C0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_808138C0_0;   /* temp_v0 in func_808138C0 */

typedef struct S_808138C0_1 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_808138C0_1;   /* temp_a0 in func_808138C0 */

typedef struct S_808138C0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_808138C0_2;   /* ((S_808138C0_0 *)temp_v0)->unk_08 in func_808138C0 */



extern void *func_800373DC();
extern void func_8003BC18();
extern u8 D_8003C558[12];
extern u8 D_8052F210[];
extern u8 D_80284430[];
extern s32 D_80284434[];

/* Creates an object at the given position and configures its color and rendering. */
void func_808138C0(s32 color, s32 x, s32 y, s32 z) {
    S_808138C0_1 *render_data;
    S_808138C0_0 *object;
    s32 resource_word;

    object = func_800373DC(0x136);
    if (object != NULL) {
        object->unk_10 = (s32)D_8052F210;
        func_8003BC18(object, D_8003C558);
        render_data = object->unk_0C;
        ((S_808138C0_2 *)(object->unk_08))->unk_00 = x;
        ((S_808138C0_2 *)(object->unk_08))->unk_04 = y;
        ((S_808138C0_2 *)(object->unk_08))->unk_08 = z;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        render_data->unk_00 = (s32)D_80284430;
        resource_word = D_80284434[0];
        render_data->unk_04 = 0;
        render_data->unk_05 = 0;
        render_data->unk_0C = color;
        render_data->unk_08 = resource_word;
        if (color != 0x808080) {
            if (color == 0xF0F0F0) {
                render_data->unk_10 = 0x60;
                ((S_808138C0_2 *)(object->unk_08))->unk_14 = 0xFFF00000;
                goto block_4;
            }
        } else {
block_4:
            render_data->unk_14 = render_data->unk_14 | 0xC;
        }
    }
}
