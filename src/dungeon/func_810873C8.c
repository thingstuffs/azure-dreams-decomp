#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80174BC8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80174BC8_0;   /* obj in func_80174BC8 */

typedef struct S_80174BC8_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80174BC8_1;   /* prim in func_80174BC8 */


typedef struct S_80174BC8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174BC8_3;   /* dst in func_80174BC8 */



typedef struct {
    s32 w[6];
} Block24;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_8003DE58(s32, void *, u16 *, s32);

extern u8 D_80045340[9];
extern u8 D_80174A00[9];

/* Creates and initializes an object, copies its data, and applies queried offsets. */
s32 func_80174BC8(void *unused, void *source_data, Rec_D_80082E80 *source_state)
{
    u16 offsets[3];
    S_80174BC8_0 *object;
    S_80174BC8_3 *object_data;
    S_80174BC8_1 *primitive;

    object = func_8003FC64(0x312);
    if (object != 0) {
        object->unk_10 = D_80174A00;
        func_8004491C(object, D_80045340);

        primitive = object->unk_0C;
        primitive->unk_28 = source_state->unk_28.at00_s32.v;
        primitive->unk_0E = 0x80;
        primitive->unk_0D = 0x80;
        primitive->unk_0C = 0x80;
        primitive->unk_1E = 0x1000;
        primitive->unk_1C = 0x1000;
        primitive->unk_06 = 1;
        primitive->unk_14 |= 0xC;
        primitive->unk_10 |= 0x20;
        func_80047784(primitive, 0x37, 0);

        object_data = object->unk_08;
        *(Block24 *)object_data = *(Block24 *)source_data;

        offsets[2] = 0;
        offsets[1] = 0;
        offsets[0] = 0;
        if (func_8003DE58(source_state->unk_08, source_state, offsets, 0) != 0) {
            object_data->unk_02 += offsets[0];
            object_data->unk_06 += offsets[1];
            object_data->unk_0A += offsets[2];
        }
        return (s32)object;
    }
    return 0;
}
