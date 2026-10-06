#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} InitPosition;

void func_80094984(void *, void *, void *);

extern u8 D_800AA5F8[];
extern u8 D_800D0130[];
extern void *D_800D0B14;
extern s16 D_80100D18;
extern s32 D_80100D1C;
extern InitPosition D_80100D28;
extern s16 D_80100D40;
extern s16 D_80100D42;
extern s16 D_80100D60[];
extern u8 D_80100D68[];
extern s16 D_80100D80;
extern s16 D_80100D82;

/* Initializes object state and sets its starting position. */
void func_800AA998(void **object, InitPosition *start_position, void *ptr2) {
        s32 *position;

    func_80094984(D_800D0130, object, ptr2);
    *object = D_800AA5F8;
    D_80100D1C = 0;
    D_80100D80 = 8;
    D_80100D82 = 8;
    D_80100D40 = 0;
    D_80100D42 = 0;
    D_80100D18 = 0;
    D_80100D60[1] = 0;
    D_80100D60[0] = 0;
    D_80100D28.x = start_position->x;
    position = &D_80100D28.x;
    position[1] = start_position->y;
    D_800D0B14 = D_80100D68;
    position[2] = start_position->z;
}
