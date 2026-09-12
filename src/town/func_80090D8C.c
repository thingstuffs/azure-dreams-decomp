#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vec8;

typedef struct {
    u16 vertex0;
    u16 vertex2;
    u16 vertex4;
    u16 vertex6;
    u8 pad08[8];
    u16 plane;
    u8 pad12[4];
    u16 flags;
} CellRecord;

typedef struct {
    u16 *grid;
    CellRecord **records;
    Vec8 *vertices;
    Vec8 *planes;
    u8 pad10[4];
    s16 shift;
    u8 pad16[2];
    u16 x_mask;
    u16 y_mask;
} MapInfo;

typedef struct {
    u8 pad00[4];
    s16 cell;
    u8 pad06[0x12];
    Vec8 *planes;
    s16 x;
    s16 y;
    s16 z;
    u8 pad22[0x1A];
    s32 best;
    s32 lower;
    s32 base_y;
    u8 pad48[2];
    s16 outer_bias;
    s16 base_x;
    u8 pad4E[2];
    s16 scan_x;
    s16 scan_y;
    s32 step_x;
    s32 step_y;
    s32 inner_count;
    s32 outer_count;
    s32 inner_delta;
    s32 outer_delta;
    s16 quad[8];
} Scratch;

typedef struct {
    u8 pad000[0x1DC];
    MapInfo map;
} GlobalState;

extern GlobalState D_80083160;
extern s32 D_800FE480;
extern s32 D_800FE484;

extern s32 func_8008CE08(Scratch *);

/* Find the lowest qualifying surface height among neighboring map cells. */
s32 func_8008E4EC(s32 world_x, s32 world_y, u16 world_z)
{
    Scratch *scratch = (Scratch *)0x1F800000;
    u16 *grid;
    Vec8 *vertices;
    register s16 scan_x;
    s16 scan_y;
    s32 base_y;
    GlobalState *global;
    MapInfo *map;

    scan_x = world_x;
    scan_y = world_y;
    base_y = (s16)(world_y & -0x40);
    scratch->best = 0x7FFF;
    scratch->lower = ((s16)world_y - base_y) - 0x14;
    scratch->base_y = base_y;
    scratch->x = world_x & 0x3F;
    scratch->z = world_z;
    scratch->y = world_y & 0x3F;
    scratch->base_x = world_x & 0x3F;
    global = &D_80083160;
    map = &D_80083160.map;
    scratch->planes = map->planes;
    grid = global->map.grid;
    vertices = map->vertices;

    if (scratch->x >= 0x20) {
        scratch->step_x = 0x40;
    } else {
        scratch->step_x = -0x40;
    }

    if ((s16)scratch->y >= 0x20) {
        scratch->step_y = 0x40;
    } else {
        register s32 negative_step;
        negative_step = -0x40;
        scratch->step_y = negative_step;
    }

    scratch->outer_count = 0;
    scratch->scan_x = scan_x;
    scratch->scan_y = scan_y;
    scratch->outer_delta = 0;

    while (scratch->outer_count < 2) {
        s32 next_y = (u16)scratch->scan_y + (u16)scratch->outer_delta;
        scan_y = next_y;
        if (scratch->step_y >= 0) {
            if ((s16)next_y >= D_800FE484) {
                break;
            }
        } else if ((s16)next_y < 0) {
            break;
        }

        scratch->inner_count = 0;
        scratch->inner_delta = 0;
        scratch->outer_bias = scratch->outer_delta;

        while (scratch->inner_count < 2) {
            s32 next_x = (u16)scratch->scan_x + (u16)scratch->inner_delta;
            scan_x = next_x;
            if (scratch->step_x >= 0) {
                if ((s16)next_x >= D_800FE480) {
                    break;
                }
            } else if ((s16)next_x < 0) {
                break;
            }

            {
                s32 cell_x;
                s32 cell_y;
                u16 cell;
                {
                    register s32 shifted_x;
                    shifted_x = ((s32)scan_x) << 16;
                    cell_x = shifted_x >> 16;
                }

                if (cell_x < 0) {
                    cell_x += 0x3F;
                }
                cell_y = scan_y;
                {
                    u16 x_mask;
                    s32 column;
                    x_mask = map->x_mask;
                    column = cell_x >> 6;
                    scratch->cell = x_mask & column;
                }
                if (cell_y < 0) {
                    cell_y += 0x3F;
                }
                cell = scratch->cell + ((s16)(map->y_mask & (cell_y >> 6)) << map->shift);
                scratch->cell = cell;

                if (grid[scratch->cell] != 0) {
                    CellRecord *record;
                    u8 *flags_ptr;
                    u16 grid_value;

                    scratch->x = scratch->base_x - scratch->inner_delta;
                    grid_value = grid[scratch->cell];
                    record = map->records[grid_value & 0x3FFF];
                    flags_ptr = (u8 *)record + 0x16;

                    for (;;) {
                        ASM_KEEP(flags_ptr);   /* MATCH: keep one flags_ptr pointer through the record loop, preventing an extra induction pointer. */
                        if ((scratch->planes[*(u16 *)(flags_ptr - 6)].y < 0) && !(*(flags_ptr + 1) & 1)) {
                            s32 height;
                            u32 vertex_index;
                            register s16 quad_coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                            Scratch *quad_scratch;
                            quad_scratch = scratch;
                            ASM_KEEP(quad_scratch);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

                            vertex_index = *(u16 *)(flags_ptr - 0x12);
                            quad_coord = vertices[vertex_index].x;
                            scratch->quad[0] = quad_coord - *(volatile s16 *)&scratch->x;
                            vertex_index = *(u16 *)(flags_ptr - 0x12);
                            quad_coord = vertices[vertex_index].z;
                            scratch->quad[1] = quad_coord - *(volatile s16 *)&scratch->z;
                            vertex_index = *(u16 *)(flags_ptr - 0x10);
                            quad_coord = vertices[vertex_index].x;
                            scratch->quad[2] = quad_coord - *(volatile s16 *)&scratch->x;
                            vertex_index = *(u16 *)(flags_ptr - 0x10);
                            quad_coord = vertices[vertex_index].z;
                            scratch->quad[3] = quad_coord - *(volatile s16 *)&scratch->z;
                            vertex_index = *(u16 *)(flags_ptr - 0x14);
                            quad_coord = vertices[vertex_index].x;
                            scratch->quad[4] = quad_coord - *(volatile s16 *)&scratch->x;
                            vertex_index = *(u16 *)(flags_ptr - 0x14);
                            quad_coord = vertices[vertex_index].z;
                            scratch->quad[5] = quad_coord - *(volatile s16 *)&scratch->z;
                            vertex_index = record->vertex0;
                            quad_coord = vertices[vertex_index].x;
                            scratch->quad[6] = quad_coord - *(volatile s16 *)&scratch->x;
                            vertex_index = record->vertex0;
                            quad_coord = vertices[vertex_index].z;
                            scratch->quad[7] = quad_coord - *(volatile s16 *)&scratch->z;

                            if (func_8008CE08(quad_scratch) != 0) {
                                {
                                    s16 vertex_coord;
                                    s32 normal_x;
                                    height = ((normal_x = scratch->planes[*(u16 *)(flags_ptr - 6)].x) * ((vertex_coord = vertices[record->vertex0].x) - (s16)scratch->x)
                                           + scratch->planes[*(u16 *)(flags_ptr - 6)].z * ((vertex_coord = vertices[record->vertex0].z) - (s16)scratch->z)
                                           + scratch->planes[*(u16 *)(flags_ptr - 6)].y * vertices[record->vertex0].y) / scratch->planes[*(u16 *)(flags_ptr - 6)].y;
                                }
                                scratch->y = height;
                                scratch->y += scratch->outer_bias;
                                if ((scratch->y >= scratch->lower) && (scratch->y < scratch->best)) {
                                    scratch->best = scratch->y;
                                }
                            }
                        }

                        {
                            u16 flags;
                            flags = *(u16 *)flags_ptr & 0x80FF;
                            flags_ptr += 0x18;
                            if (flags != 0x8001) {
                                record = (CellRecord *)((u8 *)record + 0x18);
                                continue;
                            }
                        }
                        break;
                    }
                }
            }

            scratch->inner_count++;
            scratch->inner_delta += scratch->step_x;
        }

        scratch->outer_count++;
        scratch->outer_delta += scratch->step_y;
    }

    if (scratch->best != 0x7FFF) {
        return (s16)(scratch->base_y + scratch->best);
    }
    return 0x7FFF;
}
