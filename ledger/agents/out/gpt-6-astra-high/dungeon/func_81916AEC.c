#include "common.h"

typedef s32 unk32;

typedef struct Copy6 {
    s32 word[6];
} Copy6;

#ifndef NULL
#define NULL 0
#endif


extern void *func_8003FC64(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);

extern unk32 D_800241E4;
extern unk32 D_80045340;
extern unk32 D_800DEC70;


typedef struct S_800242EC_0 {
    u8 pad_00[0x8];
    Copy6 * unk_08;
    void * unk_0C;
    unk32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800242EC_0;   /* temp_v0 in func_800242EC */

typedef struct S_800242EC_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u16 unk_0A;
} S_800242EC_1;   /* temp_v1 in func_800242EC */

typedef struct S_800242EC_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800242EC_2;   /* arg2 in func_800242EC */

typedef struct S_800242EC_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800242EC_3;   /* temp_s0 in func_800242EC */

/* Creates an object, initializes its visual state, and copies the initial data. */
void *func_800242EC(s32 object_id, void *initial_data, S_800242EC_2 *source)
{
    S_800242EC_3 *visual;
    void *object;
    S_800242EC_1 *state;
    Copy6 *object_data;
    register void *result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    object = func_8003FC64(0x212);
    result = NULL;
    if (object != NULL) {
        state = (u8 *)object + 0x20;
        ((S_800242EC_0 *)object)->unk_10 = &D_800241E4;
        ((S_800242EC_0 *)object)->unk_20 = object_id;
        state->unk_04 = 0;
        state->unk_06 = 8;
        state->unk_08 = 8;
        state->unk_0A = source->unk_2A;
        visual = ((S_800242EC_0 *)object)->unk_0C;
        visual->unk_0D = 0x30;
        visual->unk_0C = 0x30;
        visual->unk_0E = 0xC0;
        visual->unk_12 = 0x7DCF;
        visual->unk_14 |= 0xC;
        visual->unk_10 |= 0x20;
        visual->unk_14 |= 0x100;
        func_8003DB94(visual, &D_800DEC70, 0);
        visual->unk_1E = 0x1000;
        visual->unk_1C = 0x1000;
        func_8004491C(object, &D_80045340);
        object_data = ((S_800242EC_0 *)object)->unk_08;
        result = object;
        *object_data = *(Copy6 *)initial_data;
    }
    return result;
}
