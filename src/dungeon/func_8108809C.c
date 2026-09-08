#include "common.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct {
    u32 words[6];
} Copy24;

extern void *func_8003FD64(s32, s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern void func_80047784(void *, s32, s32);
extern s32 func_8003DE58(s32, void *, u16 *, s32);
extern u8 D_80045340;
extern u8 D_80175018;


typedef struct S_8017589C_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8017589C_0;   /* object in func_8017589C */

typedef struct S_8017589C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    union { u16 u; s16 s; } unk_0E;   /* accessed as both */
    u8 pad_10[0x30];
    s32 unk_40;
    void * unk_44;
    void * unk_48;
    s32 unk_4C;
} S_8017589C_1;   /* work in func_8017589C */

typedef struct S_8017589C_2 {
    u8 pad_00[0xC];
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
} S_8017589C_2;   /* node in func_8017589C */


typedef struct S_8017589C_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8017589C_4;   /* source in func_8017589C */

typedef struct S_8017589C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017589C_5;   /* copy in func_8017589C */

/* Creates an object with randomized initial state and source-derived offsets. */
void *func_8017589C(s32 allocation_param, Copy24 *initial_data, Rec_D_80082E80 *source_node)
{
    u16 delta[3];
    s32 random_value;
    s32 random_quotient;
    s32 adjusted_random;
    void *object;
    S_8017589C_1 *work;
    S_8017589C_2 *node;
    S_8017589C_4 *source;
    Copy24 *copy;

    object = func_8003FD64(0x312, allocation_param - 0x20);
    if (object != NULL) {
        ((S_8017589C_0 *)object)->unk_10 = &D_80175018;
        func_8004491C(object, &D_80045340);
        work = (u8 *)object + 0x20;

        random_quotient = rand();
        random_value = random_quotient;
        ASM_KEEP(random_quotient);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        random_quotient >>= 0xC;
        if (random_value < 0) {
            random_quotient = (s32)(random_value + 0xFFF) >> 0xC;
        }
        work->unk_06 = (s16)(random_value - (random_quotient << 0xC));

        adjusted_random = rand();
        random_value = adjusted_random;
        if (random_value < 0) {
            adjusted_random = random_value + 0xFFF;
        }
        work->unk_08 = (s16)(random_value - ((adjusted_random >> 0xC) << 0xC));

        work->unk_40 = allocation_param;
        work->unk_44 = initial_data;
        work->unk_48 = source_node;
        work->unk_4C = allocation_param;

        node = ((S_8017589C_0 *)object)->unk_0C;
        node->unk_28 = source_node->unk_28.at00_s32.v;
        node->unk_0E = 0x80;
        node->unk_0D = 0x80;
        node->unk_0C = 0x80;
        node->unk_1E = 0x1000;
        node->unk_1C = 0x1000;
        node->unk_14 |= 0xC;
        node->unk_10 |= 0x20;
        func_80047784(node, 0x3F, 0);

        copy = ((S_8017589C_0 *)object)->unk_08;
        *copy = *initial_data;

        delta[2] = 0;
        delta[1] = 0;
        delta[0] = 0;
        source = work->unk_48;
        if (func_8003DE58(source->unk_08, source, delta, 3) != 0) {
            ((S_8017589C_5 *)copy)->unk_02 += delta[0];
            ((S_8017589C_5 *)copy)->unk_06 += delta[1];
            ((S_8017589C_5 *)copy)->unk_0A += delta[2];
            work->unk_0A = delta[0];
            work->unk_0C = delta[1];
            work->unk_0E.u = delta[2];
        } else {
            work->unk_0A = 0;
            work->unk_0C = 0;
            work->unk_0E.s = -0x40;
        }
        return object;
    }
    return NULL;
}
