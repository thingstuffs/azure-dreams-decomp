#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u32 word[3];
} __attribute__((packed)) Copy12;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);

extern u8 D_80045340;
extern u8 D_80174600;
extern u8 D_8017520C[12];


typedef struct S_80174800_0 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
} S_80174800_0;   /* part in func_80174800 */

typedef struct S_80174800_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80174800_1;   /* data in func_80174800 */

typedef struct S_80174800_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80174800_2;   /* pos in func_80174800 */


/* Creates an effect at an offset from the source position with a random rotation. */
void func_80174800(void *unused_ptr, Rec_D_800E3D7C *source_pos, s32 unused_value, s16 scale)
{
    void *node;
    S_80174800_0 *part;
    S_80174800_1 *data;
    S_80174800_2 *pos;

    node = func_8003FC64(0x212);
    if (node != 0) {
        part = (u8 *)node + 0x20;
        part->unk_1A = 65;
        (*(void * *)((u8 *)node + 0x10)) = &D_80174600;
        func_8004491C(node, &D_80045340);
        data = (*(void * *)((u8 *)node + 0xC));
        data->unk_10 = 0x60;
        data->unk_14 |= 0xC;
        pos = (*(void * *)((u8 *)node + 8));
        pos->unk_02 = source_pos->unk_00.at02_u16.v;
        pos->unk_06 = source_pos->unk_04.at02_u16.v;
        pos->unk_0A = source_pos->unk_08.at02_u16.v - 0x28;
        data = (*(void * *)((u8 *)node + 0xC));
        data->unk_06 = 6;
        data->unk_1E = scale;
        data->unk_1C = scale;
        (*(s8 *)((u8 *)node + 0x20)) = 0x70;
        part->unk_01 = 0x10;
        part->unk_02 = 0x10;
        data->unk_0E = 0;
        data->unk_0D = 0;
        data->unk_0C = 0;
        data->unk_1A = rand() & 0xFFF;
        (*(Copy12 *)((u8 *)node + 0x48)) = (*(Copy12 *)((u8 *)D_8017520C + 0));
        data->unk_08 = (u8 *)node + 0x48;
    }
}
