typedef signed int s32;
typedef unsigned int u32;

extern u32 func_8001A250(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

u32 func_8047339C(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 value;

    if (value) {
        value = arg2;
        return func_8001A250(arg0, arg1, arg2, arg3) < (u32)(value * value);
    } else {
        value = arg2;
        return func_8001A250(arg0, arg1, arg2, arg3) < (u32)(value * value);
    }
}
