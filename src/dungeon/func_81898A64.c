#include "common.h"
#include "records/Rec_func_80024264_arg1.h"



#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800241D8;
extern M2C_UNK D_80024EF4;
extern M2C_UNK D_80045340;

typedef struct S_80024264_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} S_80024264_0;   /* temp_v0 in func_80024264 */

typedef struct S_80024264_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024264_1;   /* temp_s0 in func_80024264 */

typedef struct S_80024264_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024264_2;   /* temp_a0 in func_80024264 */


/* Creates a type 0x212 object with default appearance and an offset copy of the supplied state. */
void *func_80024264(s32 object_tag, Rec_func_80024264_arg1 *initial_state)
{
    S_80024264_2 *state;
    S_80024264_1 *appearance;
    S_80024264_0 *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = &D_800241D8;
        appearance = object->unk_0C;
        object->unk_20 = object_tag;
        object->unk_24 = 0;
        appearance->unk_0E = 0x80;
        appearance->unk_0D = 0x80;
        appearance->unk_0C = 0x80;
        func_8003DB94(appearance, &D_80024EF4, 0);
        appearance->unk_1C = 0x2000;
        appearance->unk_1E = 0x1000;
        appearance->unk_1A = 0xC00;
        func_8004491C(object, &D_80045340);
        state = object->unk_08;
        state->unk_00 = initial_state->unk_00.at00_s32.v;
        state->unk_04 = initial_state->unk_04.at00_s32.v;
        state->unk_08 = initial_state->unk_08.at00_s32.v + 0x500000;
        state->unk_0C = initial_state->unk_0C.at00_s32.v;
        state->unk_10 = initial_state->unk_10.at00_s32.v;
        state->unk_14 = initial_state->unk_14;
        return object;
    } else {
        return NULL;
    }
}
