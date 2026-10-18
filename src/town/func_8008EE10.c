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

extern s32 evaluate_surface_components_a(WorkVec *);

/* Evaluate the vector sum and adjust a nonzero result by the entry's integer x component. */
s16 query_offset_position_minus_x(Vec4 *vector, Vec4 *entries, s32 entry_index)
{
    WorkVec sum;
    s32 offset = entry_index * 16;
    Vec4 *entry = (Vec4 *)((uptr)offset + (uptr)entries);
    s32 result;

    sum.x = vector->x + entry->x;
    sum.y = vector->y + entry->y;
    sum.z = vector->z + entry->z;
    result = evaluate_surface_components_a(&sum);

    if ((result << 16) == 0) {
        return 0;
    }
    return (s16)(result - (entry->x / 0x10000));
}
