typedef signed int s32;
typedef unsigned int u32;

extern u32 func_8001A250(void);

u32 func_8047339C(s32 arg0, s32 arg1, s32 arg2)
{
    s32 value;

    if (value) {
        value = arg2;
        return func_8001A250() < (u32)(value * value);
    } else {
        value = arg2;
        return func_8001A250() < (u32)(value * value);
    }
}
