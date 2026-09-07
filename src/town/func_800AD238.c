#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} InitPosition;

extern void func_80094984(void *arg0, void *arg1);

extern u8 D_800AA5F8[];
extern u8 D_800D0130[];
extern void *D_800D0B14;
extern volatile s16 D_80100D18;
extern volatile s32 D_80100D1C;
extern InitPosition D_80100D28;
extern volatile s16 D_80100D40;
extern volatile s16 D_80100D42;
extern volatile s16 D_80100D60;
extern u8 D_80100D68[];
extern volatile s16 D_80100D80;
extern volatile s16 D_80100D82;

void func_800AA998(void **arg0, InitPosition *arg1) {
    volatile s16 *rotation;
    s32 *position;

    func_80094984(D_800D0130, arg0);
    *arg0 = D_800AA5F8;
    D_80100D1C = 0;
    D_80100D80 = 8;
    D_80100D82 = 8;
    D_80100D40 = 0;
    D_80100D42 = 0;
    D_80100D18 = 0;
    rotation = &D_80100D60;
    rotation[1] = 0;
    rotation[0] = 0;
    D_80100D28.x = arg1->x;
    position = &D_80100D28.x;
    position[1] = arg1->y;
    D_800D0B14 = D_80100D68;
    position[2] = arg1->z;
}
