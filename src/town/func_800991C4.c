#include "common.h"

typedef struct Vec3i {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct Record {
    u8 flags;
    u8 pad1;
    s8 scale;
    s8 height;
} Record;

extern void *func_80096A30(void *object, u8 *values, s32 index);
extern Record *func_8004CAE8(void *entry, u32 target_id);
extern s32 func_80064584(s32 angle);
extern s32 func_800644B8(s32 angle);

extern Vec3i D_800D0AE4;
extern Vec3i D_800D0AFC;
extern Vec3i *D_80100D20;

/* Computes the record-based position offset and publishes the resulting vector. */
void func_80096924(void *object, Vec3i *offset, void *resources) {
    Record *record;
    s32 angle;
    s32 x;
    s32 y;
    s32 height;

    record = func_8004CAE8(
        func_80096A30(resources, *(s32 *)((u8 *)object + 0x1C), 4), 0);
    if (record != 0) {
        angle = (*(u16 *)((u8 *)object + 0x10) - 0xC00) & 0xFFF;
        x = (record->scale * func_80064584(angle)) << 5;
        y = (-record->scale * func_800644B8(angle)) << 5;
        height = record->height;
        D_80100D20 = &D_800D0AFC;
        D_800D0AFC.x = D_800D0AE4.x + offset->x + x;
        D_800D0AFC.y = D_800D0AE4.y + offset->y + y;
        height <<= 17;
        D_800D0AFC.z = D_800D0AE4.z + offset->z + height;
        return;
    }
    D_80100D20 = 0;
}
