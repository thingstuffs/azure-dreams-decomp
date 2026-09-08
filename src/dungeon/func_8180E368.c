#include "common.h"

typedef struct S_80027368_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80027368_0;   /* object in func_80027368 */

typedef struct S_80027368_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80027368_1;   /* part in func_80027368 */

typedef struct S_80027368_2 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80027368_2;   /* arg3 in func_80027368 */

typedef struct S_80027368_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_80027368_3;   /* sprite in func_80027368 */

typedef struct S_80027368_4 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x5E];
    s16 unk_66;
} S_80027368_4;   /* work in func_80027368 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);

extern s32 D_80027164;
extern s32 D_80028874;
extern s32 D_80045340;
extern s32 D_80083498;
extern u8 D_800DDC40[];

/* Creates a sprite object at the given position with a source-dependent Z offset. */
void *func_80027368(s16 pos_x, s16 pos_y, s16 pos_z, S_80027368_2 *source)
{
    void *object;
    S_80027368_1 *part;
    S_80027368_3 *sprite;
    S_80027368_4 *work;

    object = func_8003FD64(0x12, &D_80083498);
    if (object != 0) {
        ((S_80027368_0 *)object)->unk_10 = &D_80027164;
        func_8004491C(object, &D_80045340);
        part = ((S_80027368_0 *)object)->unk_08;
        part->unk_02 = pos_x;
        part->unk_06 = pos_y;
        part->unk_0A =
            pos_z - (D_800DDC40[source->unk_13] >> 1);
        sprite = ((S_80027368_0 *)object)->unk_0C;
        sprite->unk_08 = &D_80028874;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        work = (u8 *)object + 0x20;
        work->unk_04 = source;
        work->unk_66 = 0x10;
    }
    return object;
}
