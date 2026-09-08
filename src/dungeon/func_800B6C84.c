#include "common.h"

typedef struct S_800BC3E4_0_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_800BC3E4_0_pre;   /* the 0x8 bytes before node in func_800BC3E4, addressed as node[-1] */

typedef struct S_800BC3E4_0 {
    void * unk_00;
} S_800BC3E4_0;   /* node in func_800BC3E4 */

typedef struct S_800BC3E4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800BC3E4_1;   /* object in func_800BC3E4 */

typedef struct S_800BC3E4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800BC3E4_2;   /* primitive in func_800BC3E4 */

typedef struct S_800BC3E4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC3E4_3;   /* coord in func_800BC3E4 */

typedef struct S_800BC3E4_4 {
    void * unk_00;
} S_800BC3E4_4;   /* state in func_800BC3E4 */

typedef struct S_800BC3E4_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800BC3E4_5;   /* ((S_800BC3E4_4 *)state)->unk_00 in func_800BC3E4 */



extern s32 D_80083160[];
extern s32 func_80045310(void *);
extern void func_800BC4D4(void *, void *, s16, s32);
extern s16 func_800BCB04(u16, u16, s16);

/* Traverse object nodes backward and process unflagged primitives with their computed depth. */
s32 func_800BC3E4(void *start_node) {
    void *node = start_node;
    s32 *state = D_80083160;
    volatile u16 *scratch = (volatile u16 *)0x1F800000;
    register void *previous ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    scratch[0x80] = -((u16 *)state)[0x62];
    scratch[0x81] = -((u16 *)state)[0x63];
    scratch[0x82] = ((u16 *)state)[0x5C];

    for (;;) {
        S_800BC3E4_1 *object = ((S_800BC3E4_0 *)node)->unk_00;
        S_800BC3E4_2 *primitive = object->unk_0C;

        if (!(primitive->unk_14 & 0x8000)) {
            S_800BC3E4_3 *coord = object->unk_08;
            s16 depth = func_800BCB04(coord->unk_02, coord->unk_06, coord->unk_0A);
            func_800BC4D4(coord, primitive, depth, 0);
            if (func_80045310(((S_800BC3E4_5 *)(((S_800BC3E4_4 *)state)->unk_00))->unk_8D0) != 0) {
                break;
            }
        }
        previous = ((S_800BC3E4_0_pre *)node)[-1].unk_00;
        node = (u8 *)previous + 0x20;
        if (previous == 0) {
            break;
        }
    }
    return 0;
}
