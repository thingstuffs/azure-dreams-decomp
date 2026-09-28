#include "common.h"
#include "shared/game_work.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern s32 rcos(s32);
extern s32 rsin(s32);

/* Projects input x into the xy plane using the global angle and doubles input y into z. */
void func_8003E02C(Vec3s *input, Vec3s *output) {
    output->x = (rcos(gameWork.view.viewAngle) * input->x) >> 12;
    output->y = (-(rsin(gameWork.view.viewAngle) * input->x)) >> 12;
    output->z = input->y * 2;
}
