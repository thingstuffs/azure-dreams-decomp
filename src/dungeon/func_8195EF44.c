#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif




   /* work in func_80024744 */

   /* render in func_80024744 */

   /* coord in func_80024744 */

/* Allocate and initialize an object using the map cell at the supplied position. */
void *func_80024744(s16 world_x, s16 world_y, s16 world_z, s16 coord_60)
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
        *(void **)((u8 *)obj + 0x10) = func_80024648;
        func_8004491C(obj, func_80046398);
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
