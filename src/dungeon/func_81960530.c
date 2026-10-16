#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/game_work.h"

   /* scratch in dungeonSelectContainingCellSurface */

   /* map_entry in dungeonSelectContainingCellSurface */

   /* best in dungeonSelectContainingCellSurface */

   /* current in dungeonSelectContainingCellSurface */

   /* copy_vertex in dungeonSelectContainingCellSurface */

   /* plane_ptr in dungeonSelectContainingCellSurface */

   /* dot_vertex in dungeonSelectContainingCellSurface */

   /* planes + ((S_81960530_3 *)best)->unk_10 * 8 in dungeonSelectContainingCellSurface */

   /* planes + ((S_81960530_4 *)current)->unk_10 * 8 in dungeonSelectContainingCellSurface */




/* Select a cell surface at the given position using plane height and containment tests. */
void *dungeonSelectContainingCellSurface(s32 world_x, s32 world_y, s16 min_height) {
    u8 *scratch;
    u8 *polygon;
    u8 *vertices;
    u8 *planes;
    u8 *best_polygon;
    u8 *map_entry;
    u8 *vertex;
    u8 *plane_vertex;
    MapGrid *map_data;
    u8 *plane;
    s16 cell_index;
    s32 height;
    u16 cell_x;
    u16 cell_y;

    scratch = (u8 *)0x1F800000;
    ((S_81960530_0 *)scratch)->unk_148 = 0x400;
    ((S_81960530_0 *)scratch)->unk_140.s = world_x & 0x3F;
    ((S_81960530_0 *)scratch)->unk_142.s = world_y & 0x3F;
    ((S_81960530_0 *)scratch)->unk_14C = min_height;

    cell_index = (u16)world_x >> 6;
    ((S_81960530_0 *)scratch)->unk_150 = cell_index;
    map_data = &gameWork.map;
    cell_index += ((u16)world_y >> 6) << map_data->shiftX;
    (*(s16 *)((u8 *)scratch + 0x150)) = cell_index;
    map_entry = (u8 *)((long)cell_index * 6 + (unsigned long)*(u8 **)((u8 *)(&gameWork.map)));
    vertices = ((u8 *)map_data->unk_08);
    planes = ((u8 *)map_data->unk_0C);
    best_polygon = 0;
    if (((S_81960530_2 *)map_entry)->unk_00 != 0) {
        ((S_81960530_0 *)scratch)->unk_152.s = -((S_81960530_2 *)map_entry)->unk_02;
        best_polygon = (*(u8 * *)((u8 *)(((u8 **)map_data->unk_04)) + ((S_81960530_2 *)map_entry)->unk_00 * 4));
        polygon = best_polygon;
        if (((S_81960530_8 *)(planes + ((S_81960530_3 *)best_polygon)->unk_10 * 8))->unk_04 < -0x7FF) {
            do {
                if ((((S_81960530_4 *)polygon)->unk_17.u & 1) == 0) {
                    cell_x = ((S_81960530_0 *)scratch)->unk_140.u;
                    cell_y = ((S_81960530_0 *)scratch)->unk_142.u;

                    vertex = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_00 * 8 + (unsigned long)vertices);
                    ((S_81960530_0 *)scratch)->unk_154.at00.v = ((S_81960530_5 *)vertex)->unk_00;
                    ((S_81960530_0 *)scratch)->unk_154.at00u.v = ((S_81960530_0 *)scratch)->unk_154.at00p.v - cell_x;
                    ((S_81960530_0 *)scratch)->unk_154.at02.v = ((S_81960530_0 *)scratch)->unk_154.at02u.v - cell_y;

                    vertex = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_02 * 8 + (unsigned long)vertices);
                    ((S_81960530_0 *)scratch)->unk_158.at00.v = ((S_81960530_5 *)vertex)->unk_00;
                    ((S_81960530_0 *)scratch)->unk_158.at00u.v = ((S_81960530_0 *)scratch)->unk_158.at00p.v - cell_x;
                    ((S_81960530_0 *)scratch)->unk_158.at02.v = ((S_81960530_0 *)scratch)->unk_158.at02u.v - cell_y;

                    vertex = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_06 * 8 + (unsigned long)vertices);
                    ((S_81960530_0 *)scratch)->unk_15C.at00.v = ((S_81960530_5 *)vertex)->unk_00;
                    ((S_81960530_0 *)scratch)->unk_15C.at00u.v = ((S_81960530_0 *)scratch)->unk_15C.at00p.v - cell_x;
                    ((S_81960530_0 *)scratch)->unk_15C.at02.v = ((S_81960530_0 *)scratch)->unk_15C.at02u.v - cell_y;

                    vertex = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_04 * 8 + (unsigned long)vertices);
                    ((S_81960530_0 *)scratch)->unk_160.at00.v = ((S_81960530_5 *)vertex)->unk_00;
                    ((S_81960530_0 *)scratch)->unk_160.at00u.v = ((S_81960530_0 *)scratch)->unk_160.at00p.v - cell_x;
                    ((S_81960530_0 *)scratch)->unk_160.at02.v = ((S_81960530_0 *)scratch)->unk_160.at02u.v - cell_y;

                    if (dungeonAreQuadCornerTurnsWithinHalfRevolution(scratch) != 0) {
                        plane = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_10 * 8 + (unsigned long)planes);
                        plane_vertex = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_00 * 8
                            + (unsigned long)vertices);
                        height = (((S_81960530_6 *)plane)->unk_00 * (((S_81960530_7 *)plane_vertex)->unk_00
                            - (s16)((S_81960530_0 *)scratch)->unk_140.u) +
                                  ((S_81960530_6 *)plane)->unk_02 * (((S_81960530_7 *)plane_vertex)->unk_02
                                      - (s16)((S_81960530_0 *)scratch)->unk_142.u) +
                                  ((S_81960530_6 *)plane)->unk_04 * ((S_81960530_7 *)plane_vertex)->unk_04) /
                                ((S_81960530_6 *)plane)->unk_04;
                        ((S_81960530_0 *)scratch)->unk_144 = height;
                        height += (s16)((S_81960530_0 *)scratch)->unk_152.u;
                        ((S_81960530_0 *)scratch)->unk_144 = height;
                        if (height >= ((S_81960530_0 *)scratch)->unk_14C &&
                            height < ((S_81960530_0 *)scratch)->unk_148) {
                            best_polygon = polygon;
                            ((S_81960530_0 *)scratch)->unk_148 = height;
                        }
                    }
                }

                if ((((S_81960530_4 *)polygon)->unk_16 & 0xF) == 1) {
                    if (((S_81960530_4 *)polygon)->unk_17.s < 0) {
                        break;
                    }
                    if ((((S_81960530_4 *)polygon)->unk_16 & 0xF0) != 0) {
                        polygon += ((((S_81960530_4 *)polygon)->unk_16 >> 4) * 3) * 8 + 0x18;
                        continue;
                    }
                }
                polygon += 0x18;
            } while (((S_81960530_9 *)(planes + ((S_81960530_4 *)polygon)->unk_10 * 8))->unk_04 < -0x7FF);
        }
    }

    return best_polygon;
}
