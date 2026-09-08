#include "common.h"
#include "records/Rec_func_801744DC_arg1.h"
#include "records/Rec_func_801744DC_arg0.h"

typedef struct S_801746EC_0 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    u8 pad_20[0x30];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    u8 pad_5C[0x8];
    s32 unk_64;
} S_801746EC_0;   /* work in func_801746EC */

typedef struct S_801746EC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801746EC_1;   /* node in func_801746EC */

typedef struct S_801746EC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_801746EC_2;   /* part in func_801746EC */

typedef struct S_801746EC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801746EC_3;   /* coords in func_801746EC */





typedef struct {
    s16 x;
    s16 y;
} Pair16;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);
extern s32 rand(void);

extern s32 D_80045340;
extern u8 D_800DECF8[];
extern s32 D_80174300;
extern Pair16 D_8017610C[];

void func_801746EC(Rec_func_801744DC_arg0 *arg0, Rec_func_801744DC_arg1 *arg1)
{
    void *node;
    S_801746EC_0 *work;
    S_801746EC_2 *part;
    S_801746EC_3 *coords;
    s32 bias;

    node = func_8003FC64(0x212);
    if (node != 0) {
        work = (u8 *)node + 0x20;
        work->unk_1E = 0x4;
        ((S_801746EC_1 *)node)->unk_10 = &D_80174300;
        func_8004491C(node, &D_80045340);

        part = ((S_801746EC_1 *)node)->unk_0C;
        part->unk_10 = 0x20;
        part->unk_14 |= 0xC;
        part->unk_1A = (rand() & 7) << 9;
        part->unk_06 = 0;

        coords = ((S_801746EC_1 *)node)->unk_08;
        coords->unk_02 = arg1->unk_02;
        coords->unk_06 = arg1->unk_06;
        coords->unk_0A = arg1->unk_0A;
        coords->unk_02 = ({ coords->unk_02 - 0x20; }) + (rand() & 0x3F);
        coords->unk_06 = ({ coords->unk_06 - 0x20; }) + (rand() & 0x3F);
        coords->unk_0A = ({ coords->unk_0A - 0x40; }) + (rand() & 0x3F);

        work->unk_58 = 0xFFFA0000;
        work->unk_64 = 0x20000;
        work->unk_50 = D_8017610C[arg0->unk_1C].x << 18;
        work->unk_54 = D_8017610C[arg0->unk_1C].y << 18;

        bias = 0xFFF80000;
        work->unk_50 = (work->unk_50 + bias) + ((rand() & 0x3FFF) << 6);
        work->unk_54 = (work->unk_54 + bias) + ((rand() & 0x3FFF) << 6);
        work->unk_58 = (work->unk_58 + bias) + ((rand() & 0x3FFF) << 6);

        part = ((S_801746EC_1 *)node)->unk_0C;
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
        part->unk_0E = 0x80;
        part->unk_0D = 0x80;
        part->unk_0C = 0x80;
        part->unk_14 |= 0x100;
        part->unk_12 = 0x7DCE;
        func_8003DB94(part, D_800DECF8, 0);
    }
}
