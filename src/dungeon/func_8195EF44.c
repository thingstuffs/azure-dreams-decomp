#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif


extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 D_80024648;
extern s32 D_80046398;


typedef struct S_8195EF44_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_8195EF44_2;   /* work in func_8195EF44 */

typedef struct S_8195EF44_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195EF44_4;   /* render in func_8195EF44 */

typedef struct S_8195EF44_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    u8 pad_3E[0xE];
    s16 unk_4C;
    u8 pad_4E[0x12];
    s16 unk_60;
    s16 unk_62;
} S_8195EF44_5;   /* coord in func_8195EF44 */

/* Allocate and initialize an object using the map cell at the supplied position. */
void *func_8195EF44(s16 world_x, s16 world_y, s16 world_z, s16 coord_60)
{
    void *obj;
    S_8195EF44_2 *work;
    MapGrid *map;
    u8 *coord;
    void *render;
    s32 cell_x;
    s32 cell_y;
    u16 cell;

    map = &gameWork.map;
    obj = func_8003FC64(2);
    if (obj != NULL) {
        work = *(void **)((u8 *)obj + 0xC);
        cell_x = world_x / 64;
        cell_y = world_y / 64;
        cell = ((u16 *)map->cells)[(cell_x + (cell_y << map->shiftX)) * 3];
        work->unk_08 = cell;
        if (cell == 0) {
            u16 obj_flags = *(u16 *)((u8 *)obj + 0x1E) | 0x8000;
            s32 global_flags = objectFlagBlock.flags | 0x8000;
            *(u16 *)((u8 *)obj + 0x1E) = obj_flags;
            objectFlagBlock.flags = global_flags;
            return NULL;
        }
        coord = (u8 *)obj + 0x20;
        *(void **)((u8 *)obj + 0x10) = &D_80024648;
        func_8004491C(obj, &D_80046398);
        render = *(void **)((u8 *)obj + 8);
        ((S_8195EF44_4 *)render)->unk_02 = world_x;
        ((S_8195EF44_5 *)coord)->unk_38 = world_x;
        ((S_8195EF44_4 *)render)->unk_06 = world_y;
        ((S_8195EF44_5 *)coord)->unk_3A = world_y;
        ((S_8195EF44_4 *)render)->unk_0A = world_z;
        ((S_8195EF44_5 *)coord)->unk_3C = world_z;
        work->unk_20 = 0x1000;
        work->unk_1E = 0x1000;
        work->unk_1C = 0x1000;
        work->unk_10 = 0x20;
        work->unk_0C = 0x808080;
        work->unk_14 = 0xC;
        ((S_8195EF44_5 *)coord)->unk_4C = 0xC;
        ((S_8195EF44_5 *)coord)->unk_60 = coord_60;
        ((S_8195EF44_5 *)coord)->unk_62 = world_z;
    }
    return obj;
}
