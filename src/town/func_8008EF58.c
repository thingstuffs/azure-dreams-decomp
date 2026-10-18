/* Recovered retail twin; complete-function proof is in the lane receipt. */
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

extern s32 evaluate_surface_components_c(WorkVec *);

s16 adjust_summed_vector_by_entry_component(Vec4 *vector, Vec4 *entries, s32 entry_index)
{
    WorkVec sum;
    s32 offset = entry_index * 16;
    Vec4 *entry = (Vec4 *)((uptr)offset + (uptr)entries);
    s32 result;

    sum.x = vector->x + entry->x;
    sum.y = vector->y + entry->y;
    sum.z = vector->z + entry->z;
    result = evaluate_surface_components_c(&sum);

    if ((result << 16) == 0) {
        return 0;
    }
    return (s16)(result - (entry->y / 0x10000));
}
