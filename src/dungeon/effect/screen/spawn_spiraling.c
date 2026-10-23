typedef signed short s16;
typedef signed int s32;

extern s32 ratan2(s32, s32);
extern s32 SquareRoot0(s32);

struct Delta {
    s32 x;
    s32 y;
    s32 z;
};

/* Compute direction angles between two points, with the third angle set to zero. */
void spawn_spiraling(s16 from_x, s16 from_y, s16 from_z, s16 to_x, s16 to_y,
                   s16 to_z, s16 *angles)
{
    struct Delta delta;
    s32 divisor;

    delta.x = to_x - from_x;
    delta.y = to_y - from_y;
    delta.z = to_z - from_z;

    divisor = delta.z;
    if (divisor == 0) {
        divisor = 1;
    }
    angles[0] = -ratan2(delta.y, divisor);

    divisor = SquareRoot0(delta.y * delta.y + delta.z * delta.z);
    if (divisor == 0) {
        divisor = 1;
    }
    angles[1] = ratan2(delta.x, divisor);
    angles[2] = 0;
}
