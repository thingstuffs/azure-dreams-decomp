#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"





typedef struct Position {
    s32 x;
    s32 y;
    s32 z;
    s32 half_dx;
    s32 half_dy;
    s32 half_dz;
} Position;

extern u8 D_8009AE88[];
extern u8 D_800D0078[];
extern s32 D_800D0624[];

extern void func_80094984();
extern void func_80099754();

void func_8009AD70(Rec_func_80094268_arg0 *arg0, Position *arg1, s32 arg2)
{
    u16 timer;
    s32 *position;

    position = D_800D0624;
    arg1->half_dx = (position[0] - arg1->x) / 2;
    arg1->half_dy = (position[1] - arg1->y) / 2;
    arg1->half_dz = (position[2] - arg1->z) / 2;

    timer = arg0->unk_0A.as_u16 - 1;
    arg0->unk_0A.as_u16 = timer;
    if ((s16)timer < 0) {
        arg1->x = *(volatile s32 *)&D_800D0624[0];
        arg1->y = position[1];
        arg1->z = position[2];
        func_80099754(arg1);

        arg0->unk_30 = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_u16.v;
        arg0->unk_32 = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_u16.v;
        func_80094984(D_800D0078, arg0, arg2);

        arg0->unk_04.as_pv = D_8009AE88;
        arg0->unk_10.as_s16 = 0x400;
    }
}

/* MECHANISM: A named D_800D0624 base supplies the vector accesses, with a
   volatile fresh x reload after expiry to retain retail's load-delay split.
   The three arguments span calls in s0/s1/s2; s16(timer) gives sll/bgez. */
