typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned long uptr;

typedef struct Vec4 {
    s32 x;
    s32 y;
    s32 z;
    s32 pad;
} Vec4;

typedef struct WorkVec {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[3];
} WorkVec;

extern s32 func_8008CFE8(WorkVec *, Vec4 *, s32);

s16 func_8008C570(Vec4 *arg0, Vec4 *arg1, s32 arg2)
{
    WorkVec sum;
    s32 offset = arg2 * 16;
    Vec4 *entry = (Vec4 *)((uptr)offset + (uptr)arg1);
    s32 result;

    sum.x = arg0->x + entry->x;
    sum.y = arg0->y + entry->y;
    sum.z = arg0->z + entry->z;
    result = func_8008CFE8(&sum, arg1, offset);

    if ((result << 16) == 0) {
        return 0;
    }
    return (s16)(result - (entry->x / 0x10000));
}
