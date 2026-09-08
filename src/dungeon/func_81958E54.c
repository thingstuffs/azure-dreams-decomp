typedef signed short s16;
typedef signed int s32;

extern s32 func_80065F90(s32, s32);
extern s32 func_80064710(s32);

struct Delta {
    s32 x;
    s32 y;
    s32 z;
};

/* Compute direction angles between two points, with the third angle set to zero. */
void func_80024654(s16 from_x, s16 from_y, s16 from_z, s16 to_x, s16 to_y,
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
    angles[0] = -func_80065F90(delta.y, divisor);

    divisor = func_80064710(delta.y * delta.y + delta.z * delta.z);
    if (divisor == 0) {
        divisor = 1;
    }
    angles[1] = func_80065F90(delta.x, divisor);
    angles[2] = 0;
}
