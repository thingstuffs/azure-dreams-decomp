typedef signed short s16;
typedef signed int s32;

extern s32 func_80065F90(s32, s32);
extern s32 func_80064710(s32);

struct Delta {
    s32 x;
    s32 y;
    s32 z;
};

void func_80024654(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4,
                   s16 arg5, s16 *out)
{
    struct Delta delta;
    s32 divisor;

    delta.x = arg3 - arg0;
    delta.y = arg4 - arg1;
    delta.z = arg5 - arg2;

    divisor = delta.z;
    if (divisor == 0) {
        divisor = 1;
    }
    out[0] = -func_80065F90(delta.y, divisor);

    divisor = func_80064710(delta.y * delta.y + delta.z * delta.z);
    if (divisor == 0) {
        divisor = 1;
    }
    out[1] = func_80065F90(delta.x, divisor);
    out[2] = 0;
}
