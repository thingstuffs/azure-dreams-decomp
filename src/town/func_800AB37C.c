#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct {
    Vec3 first;
    Vec3 second;
} Pair;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused_0C;
    s32 unused_10;
} Work;

extern s32 func_800374F4();
extern void func_80097AD0();
extern void func_800A895C();
extern Pair D_80089128;

/* Process a position and its raised copy using a local vector pair. */
void func_800A8ADC(s32 unused_arg, s32 *position) {
    Pair pair;
    Work raised_pos;

    pair = D_80089128;
    raised_pos.x = position[0];
    raised_pos.y = position[1];
    raised_pos.z = position[2] + 0x100000;
    func_800A895C(position, &pair, (func_800374F4(2) & 0xFFFF) + 2);
    func_80097AD0(&raised_pos, &pair, (func_800374F4(2) & 0xFFFF) + 2);
}
