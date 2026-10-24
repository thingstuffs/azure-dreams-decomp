/* Forward surface query with argument.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01117 - CL:town/func_8008F958, CL:town/func_8008FE64, CL:town/func_80090320, CL:town/func_80090854, CL:town/func_80090D8C, CL:town/func_800912C0, PD:town/engine:800FE480, PD:town/engine:800FE484.
 */
#include "town/map/forward_surface_query_with_argument_g01117.h"

/* Pass the signed position components and plane output to the height query. */
s16 forward_surface_query_with_argument(SignedPositionView *record, void **plane_out) {
    return find_min_qualifying_plane_height(record->x, record->y, record->z, plane_out);
}

/* Pass three signed record components to find_highest_surface_within_range. */
s16 forward_highest_surface_query(SignedPositionView *record) {
    return find_highest_surface_within_range(record->x, record->y, record->z);
}

/* Pass three signed record components to find_smallest_surface_x_across_tiles. */
s16 forward_smallest_surface_x_query(SignedPositionView *record) {
    return find_smallest_surface_x_across_tiles(record->x, record->y, record->z);
}

/* Evaluate the three signed components stored in the input record. */
s16 evaluate_surface_components_a(SignedPositionView *components) {
    return find_greatest_cell_intersection(components->x, components->y, components->z);
}

/* Evaluate the three signed components stored in the input record. */
s16 evaluate_surface_components_b(SignedPositionView *components) {
    return find_lowest_surface_height(components->x, components->y, components->z);
}

/* Evaluate the three signed components stored in the input record. */
s16 evaluate_surface_components_c(SignedPositionView *components) {
    return find_highest_valid_cell_height(components->x, components->y, components->z);
}

/* Set the two view scales from the stored shift counts. */
void update_map_world_extents(void)
{
    TownViewState *state;

    state = (TownViewState *)((u8 *)(&g_game_work));

    state = (TownViewState *)((u8 *)state + 0x1DC);

    ((s32 *)town_map_column_extent)[0] = 0x40 << state->unk14;
    ((s32 *)town_map_row_extent)[0] = 0x40 << state->unk16;
}

/* Finds the lowest qualifying surface height and plane at the query position. */
s32 find_min_qualifying_plane_height(u32 query_x, u32 query_y, s16 query_height, void **plane_out)
{
    TargetScratch *scratch;
    TargetGlobal *globals;
    TargetMap *world;
    u16 *tiles;
    Vec8 *vertices;
    Vec8 *planes;
    u8 *face;
    u16 x;
    s16 y;
    void **result_plane;
    s32 threshold;
    s32 left_half;
    s32 cell_x_coord;
    s32 cell_y_coord;
    u16 cell;
    u16 local_x;
    u16 local_y;
    s32 height;
    s32 x_step;
    s32 x_sum;
    s32 signed_x;
    u32 scan_x_value;
    u32 query_x_value;
    u32 masked_y;
    u8 flags;
    u32 masked_x;

    query_x_value = query_x + query_y;
    query_x_value -= query_y;
    x = query_x_value;
    y = query_y;
    result_plane = plane_out;
    scratch = (TargetScratch *)0x1F800000;
    scratch->best = 0x400;
    scratch->result = (void *)D_800CFCAC;
    masked_y = query_y & 0x3F;
    globals = ((TargetGlobal *)&g_game_work);
    world = &globals->map;
    masked_x = query_x & 0x3F;
    threshold = query_height - 0x14;
    scratch->origin_x = masked_x;
    scratch->origin_y = masked_y;
    scratch->threshold = threshold;
    planes = world->planes;
    scratch->x_base = masked_x;
    left_half = (s32)masked_x < 0x20;
    scratch->y_base = masked_y;
    scratch->planes = planes;
    tiles = world->tiles;
    vertices = world->vertices;

    if (!left_half) {
        scratch->x_step = 0x40;
    } else {
        scratch->x_step = -0x40;
    }
    if ((s16)scratch->origin_y < 0x20) {
        scratch->y_step = -0x40;
    } else {
        scratch->y_step = 0x40;
    }

    scratch->outer_count = 0;
    scratch->x_scan = x;
    scratch->y_scan = y;
    scratch->outer_offset = 0;

    while (scratch->outer_count < 2) {
        y = scratch->y_scan + scratch->outer_offset;
        if (scratch->y_step >= 0) {
            if (y >= (*((s32 *)town_map_row_extent))) {
                break;
            }
        } else if (y < 0) {
            break;
        }
        scratch->inner_count = 0;
        scratch->inner_offset = 0;
        scratch->origin_y = scratch->y_base - scratch->outer_offset;

        while (scratch->inner_count < 2) {
            x_sum = scratch->x_scan + (u16)scratch->inner_offset;
            if ((u16)x_sum != 0) {
                x_step = scratch->x_step;
            } else {
                x_step = scratch->x_step + ((u16)x_sum != 0);
            }
            scan_x_value = (u32)x_sum + (u32)x_step;
            scan_x_value -= (u32)x_step;
            x = scan_x_value;
            if (x_step >= 0) {
                if ((s16)x_sum >= (*((s32 *)town_map_column_extent))) {
                    break;
                }
            } else {
                signed_x = (s16)x_sum;
                if ((s16)signed_x < 0) {
                    break;
                }
            }
            cell_x_coord = (s16)x;
            cell = world->x_mask & (cell_x_coord / 64);
            scratch->cell = cell;
            cell_y_coord = (s16)y;
            cell += (s16)(world->y_mask & (cell_y_coord / 64)) << world->shift;
            scratch->cell = cell;
            if (tiles[(s16)cell] != 0) {
                scratch->origin_x = scratch->x_base - scratch->inner_offset;
                face = world->cells[(tiles[(s16)scratch->cell] & 0x3FFF)];
                while (scratch->planes[*(u16 *)(face + 0x10)].z < 0) {
                    if (!(face[0x17] & 1)) {
                        local_x = scratch->origin_x;
                        local_y = scratch->origin_y;

                        scratch->quad.words[0] = vertices[*(u16 *)(face + 0)].xy;
                        scratch->quad.halves[0] -= local_x;
                        scratch->quad.halves[1] -= local_y;

                        scratch->quad.words[1] = vertices[*(u16 *)(face + 2)].xy;
                        scratch->quad.halves[2] -= local_x;
                        scratch->quad.halves[3] -= local_y;

                        scratch->quad.words[2] = vertices[*(u16 *)(face + 6)].xy;
                        scratch->quad.halves[4] -= local_x;
                        scratch->quad.halves[5] -= local_y;

                        scratch->quad.words[3] = vertices[*(u16 *)(face + 4)].xy;
                        scratch->quad.halves[6] -= local_x;
                        scratch->quad.halves[7] -= local_y;
                        if (check_scratch_quad_half_turn_gaps((struct ScratchQuad *)(scratch)) != 0) {
                            height = ((s16)scratch->planes[*(u16 *)(face + 0x10)].xy *
                                      ((s16)vertices[*(u16 *)face].xy -
                                       (s16)scratch->origin_x) +
                                      (s16)(scratch->planes[*(u16 *)(face + 0x10)].xy >> 16) *
                                      ((s16)(vertices[*(u16 *)face].xy >> 16) -
                                       (s16)scratch->origin_y) +
                                      scratch->planes[*(u16 *)(face + 0x10)].z *
                                      vertices[*(u16 *)face].z) /
                                     scratch->planes[*(u16 *)(face + 0x10)].z;
                            scratch->height = height;
                            if (height >= scratch->threshold && height < scratch->best) {
                                scratch->best = height;
                                scratch->result = &scratch->planes[*(u16 *)(face + 0x10)];
                            }
                        }
                    }

                    flags = face[0x16];
                    if ((flags & 0xF) == 1) {
                        if ((s8)face[0x17] < 0) {
                            break;
                        }
                        if (flags & 0xF0) {
                            face += ((flags >> 4) * 3 << 3) + 0x18;
                            continue;
                        }
                    }
                    face += 0x18;
                }
            }
            scratch->inner_count++;
            scratch->inner_offset += scratch->x_step;
        }

        scratch->outer_count++;
        scratch->outer_offset += scratch->y_step;
    }

    *result_plane = scratch->result;
    return (s16)scratch->best;
}

/* Find the highest surface at the given position within 20 units above the height. */
s32 find_highest_surface_within_range(s32 world_x, s32 world_y, s16 height) {
    u32 x_sum;
    u16 scan_x = world_x;
    s16 scan_y = world_y;
    ScratchArena *arena = (ScratchArena *)0x1F800000;
    Scratch *scratch = &arena->full;
    GlobalState *global = ((GlobalState *)&g_game_work);
    MapInfo *map;
    u16 *grid;
    Vec8 *vertices;
    Vec8 *plane_base;
    u32 plane_index;
    u32 normal_index;
    u32 vertex_index;
    s32 biased_x;
    s32 biased_y;
    s32 tile_x;
    s32 tile_index;
    s16 row_y;
    s16 col_x;
    s16 normal_z;
    s16 local_x;
    s32 result;
    s32 offset_x = world_x & 0x3F;
    s32 offset_y = world_y & 0x3F;

    scratch->best = -0x7FFF;
    map = &global->map;
    scratch->x = offset_x;
    scratch->y = offset_y;
    scratch->limit = height + 0x14;
    scratch->base_y = offset_y;
    scratch->planes = map->planes;
    scratch->base_x = offset_x;
    grid = global->map.grid;
    vertices = map->vertices;
    if (scratch->x >= 0x20) {
        offset_x = 0;
        scratch->step_x = 0x40;
    } else {
        scratch->step_x = -0x40;
    }
    if (scratch->y < 0x20) {
        scratch->step_y = -0x40;
    } else {
        scratch->step_y = 0x40;
    }
    scratch->outer_count = 0;
    scratch->orig_x = scan_x;
    scratch->orig_y = scan_y;
    scratch->outer_delta = 0;

    while (scratch->outer_count < 2) {
        scan_y = (u16)scratch->orig_y + (u16)scratch->outer_delta;
        row_y = scan_y;
        if (scratch->step_y >= 0) {
            if (row_y >= (*((s32 *)town_map_row_extent)))
                return (s16)(u16)scratch->best;
        } else {
            if (row_y < 0)
                return (s16)(u16)scratch->best;
        }
        scratch->inner_count = 0;
        scratch->inner_delta = 0;
        scratch->y = (u16)scratch->base_y - (u16)scratch->outer_delta;
        while (scratch->inner_count < 2) {
            s32 x_step;
            x_sum = (u16)scratch->orig_x + (u16)scratch->inner_delta;
            x_step = scratch->step_x;
            scan_x = x_sum;
            col_x = x_sum;
            if (x_step >= 0) {
                if (col_x >= (*((s32 *)town_map_column_extent)))
                    break;
            } else {
                col_x = x_sum;
                if (col_x < 0)
                    break;
            }
            biased_x = (s16)scan_x;
            if (biased_x < 0)
                biased_x += 0x3F;
            tile_x = map->x_mask & (biased_x >> 6);
            scratch->tile = tile_x;
            biased_y = scan_y;
            tile_index = tile_x + ((s16)(map->y_mask & (biased_y / 64)) << map->shift);
            scratch->tile = tile_index;

            if (grid[(s16)scratch->tile] != 0) {
                CellRecord *cell;
                u16 grid_value;
                scratch->x = (u16)scratch->base_x - (u16)scratch->inner_delta;
                grid_value = grid[(s16)scratch->tile];
                cell = map->records[grid_value & 0x3FFF];
                if (!(cell->flags & 0x40)) {
                    cell = (CellRecord *)((u8 *)cell - 0x0C);
                    do {
                        if ((scratch->planes[cell->v8].z > 0) && !(cell->edge_flags & 1)) {
                            scratch->quad.words[0] = vertices[cell->v4].xy;
                            scratch->quad.vals[0] -= scratch->x;
                            scratch->quad.vals[1] -= scratch->y;
                            scratch->quad.words[1] = vertices[cell->v6].xy;
                            scratch->quad.vals[2] -= scratch->x;
                            scratch->quad.vals[3] -= scratch->y;
                            scratch->quad.words[2] = vertices[cell->v2].xy;
                            scratch->quad.vals[4] -= scratch->x;
                            scratch->quad.vals[5] -= scratch->y;
                            scratch->quad.words[3] = vertices[cell->v0].xy;
                            scratch->quad.vals[6] -= scratch->x;
                            scratch->quad.vals[7] -= scratch->y;
                            result = check_scratch_quad_half_turn_gaps(scratch);
                            if (result != 0) {
                                s32 term_x;
                                s32 term_y;
                                s32 term_z;
                                if ((result & 1) != 0)
                                    plane_index = cell->v8;
                                else
                                    plane_index = cell->v8 + ((result & 1) != 0);
                                plane_base = scratch->planes;
                                vertex_index = cell->v0;
                                local_x = scratch->x;
                                if (plane_base != 0)
                                    normal_index = plane_index;
                                else
                                    normal_index = plane_index + (plane_base != 0);
                                normal_z = plane_base[normal_index].z;
                                term_x = (s16)plane_base[normal_index].xy *
                                         ((s16)vertices[vertex_index].xy - local_x);
                                term_y = (s16)(plane_base[normal_index].xy >> 16) *
                                         ((s16)(vertices[vertex_index].xy >> 16) -
                                          (s16)scratch->y);
                                term_z = normal_z * vertices[vertex_index].z;
                                result = term_x + term_y + term_z;
                                scratch->value = result / normal_z;
                                if (scratch->limit >= scratch->value &&
                                    scratch->best < scratch->value)
                                scratch->best = scratch->value;
                            }
                        }
                        if ((s8)cell->edge_flags < 0)
                            break;
                        cell = (CellRecord *)((u8 *)cell - 0x0C);
                    } while (1);
                }
            }
            scratch->inner_count += 1;
            scratch->inner_delta += scratch->step_x;
        }
        scratch->outer_count += 1;
        scratch->outer_delta += scratch->step_y;
    }
    return (s16)(u16)scratch->best;
}

/* Finds the smallest eligible surface X coordinate across neighboring grid tiles. */
s16 find_smallest_surface_x_across_tiles(s32 query_x, s32 query_y, s32 query_z)
{
    Scratch80090320 *scratch;
    Grid80090320 *grid;
    u16 *occupancy;
    GameWork *grid_data;
    u8 *vertices;
    u8 *entry;
    u8 *plane;
    u8 *vertex;
    s16 block_base;
    s16 tile;
    s16 candidate_x;
    s16 x;
    u16 y;
    s32 row_y;
    s32 plane_x;
    s16 column_x;

    x = query_x;
    y = query_y;
    scratch = (Scratch80090320 *)0x1F800000;
    scratch->best = 0x7FFF;
    block_base = query_x & ~0x3F;
    scratch->block_base = block_base;
    scratch->lower_bound = (s16)query_x - block_base - 0x14;
    scratch->origin_y = query_y & 0x3F;
    scratch->origin_z = query_z;
    grid_data = &g_game_work;
    grid = (Grid80090320 *)((u8 *)grid_data + 0x1DC);
    scratch->result = query_x & 0x3F;
    query_x &= 0x3F;
    scratch->saved_y = query_y & 0x3F;
    scratch->height_data = grid->height_data;
    occupancy = ((u16 *)grid_data->map.cells);
    vertices = grid->vertices;
    if (query_x >= 0x20) {
        scratch->x_step = 0x40;
    } else {
        scratch->x_step = -0x40;
    }
    if ((s16)scratch->origin_y >= 0x20) {
        s32 y_step_pos = 0x40;
        scratch->y_step = y_step_pos;
    } else {
        s32 y_step_neg = -0x40;
        scratch->y_step = y_step_neg;
    }

    scratch->outer_count = 0;
    scratch->start_x = x;
    scratch->start_y = y;
    scratch->outer_offset = 0;
    while (scratch->outer_count < 2) {
        row_y = (u16)scratch->start_y + (u16)scratch->outer_offset;
        y = row_y;
        if (scratch->y_step >= 0) {
            if ((s16)row_y >= (*((s32 *)town_map_row_extent)))
                break;
        } else if ((s16)row_y < 0) {
            break;
        }
        scratch->inner_count = 0;
        scratch->inner_offset = 0;
        scratch->origin_y = scratch->saved_y - (u16)scratch->outer_offset;
        while (scratch->inner_count < 2) {
            column_x = (u16)scratch->start_x + (u16)scratch->inner_offset;
            x = column_x;
            if (scratch->x_step >= 0) {
                if ((s16)column_x >= (*((s32 *)town_map_column_extent)))
                    break;
            } else if ((s16)column_x < 0) {
                break;
            }

            scratch->tile = grid->x_mask &
                ((s16)x / 64);
            tile = scratch->tile +
                ((s16)(grid->y_mask & ((s16)y / 64)) << grid->shift);
            scratch->tile = tile;
            if (occupancy[tile] != 0) {
                scratch->inner_index = scratch->inner_offset;
                entry = grid->entries[occupancy[(s16)scratch->tile] & 0x3FFF];
                for (;;) {
                    if (((S_8008DA80_4 *)(((S_8008DA80_1 *)entry)->unk_10 * 8 + scratch->height_data))->unk_00 < 0 &&
                        !(((S_8008DA80_1 *)entry)->unk_16.at01.v & 1)) {
                        scratch->d0 = ((S_8008DA80_5 *)(((S_8008DA80_1 *)entry)->unk_00 * 8 + vertices))->unk_02
                            - scratch->origin_y;
                        scratch->d1 = ((S_8008DA80_5 *)(((S_8008DA80_1 *)entry)->unk_00 * 8 + vertices))->unk_04
                            - scratch->origin_z;
                        scratch->d2 = ((S_8008DA80_6 *)(((S_8008DA80_1 *)entry)->unk_02 * 8 + vertices))->unk_02
                            - scratch->origin_y;
                        scratch->d3 = ((S_8008DA80_6 *)(((S_8008DA80_1 *)entry)->unk_02 * 8 + vertices))->unk_04
                            - scratch->origin_z;
                        scratch->d4 = ((S_8008DA80_7 *)(((S_8008DA80_1 *)entry)->unk_06 * 8 + vertices))->unk_02
                            - scratch->origin_y;
                        scratch->d5 = ((S_8008DA80_7 *)(((S_8008DA80_1 *)entry)->unk_06 * 8 + vertices))->unk_04
                            - scratch->origin_z;
                        scratch->d6 = ((S_8008DA80_8 *)(((S_8008DA80_1 *)entry)->unk_04 * 8 + vertices))->unk_02
                            - scratch->origin_y;
                        scratch->d7 = ((S_8008DA80_8 *)(((S_8008DA80_1 *)entry)->unk_04 * 8 + vertices))->unk_04
                            - scratch->origin_z;

                        if (check_scratch_quad_half_turn_gaps((struct ScratchQuad *)(scratch)) != 0) {
                            plane = (u8 *)(((S_8008DA80_1 *)entry)->unk_10 * 8 +
                                           (u32)scratch->height_data);
                            vertex = (u8 *)(((S_8008DA80_1 *)entry)->unk_00 * 8 +
                                            (u32)vertices);
                            plane_x =
                                (((S_8008DA80_2 *)plane)->unk_02 *
                                 (((S_8008DA80_3 *)vertex)->unk_02 -
                                  (s16)scratch->origin_y) +
                                 ((S_8008DA80_2 *)plane)->unk_04 *
                                 (((S_8008DA80_3 *)vertex)->unk_04 -
                                  (s16)scratch->origin_z) +
                                 ((S_8008DA80_2 *)plane)->unk_00 * ((S_8008DA80_3 *)vertex)->unk_00) /
                                ((S_8008DA80_2 *)plane)->unk_00;
                            scratch->result = plane_x;
                            plane_x += scratch->inner_index;
                            scratch->result = plane_x;
                            candidate_x = plane_x;
                            if (candidate_x >= scratch->lower_bound && candidate_x < scratch->best)
                                scratch->best = candidate_x;
                        }
                    }
                    if ((((S_8008DA80_1 *)entry)->unk_16.at00.v & 0x80FF) == 0x8001)
                        break;
                    entry += 0x18;
                }
            }
            scratch->inner_count++;
            scratch->inner_offset += scratch->x_step;
        }
        scratch->outer_count++;
        scratch->outer_offset += scratch->y_step;
    }
    if (scratch->best == 0x7FFF)
        return 0x7FFF;
    return (s16)((u16)scratch->block_base + (u16)scratch->best);
}

/* Finds the greatest cell-plane intersection within the query position's search limit. */
s32 find_greatest_cell_intersection(query_x, query_y, query_z)
s16 query_x;
u16 query_y;
u16 query_z;
{
    Scratch_80090854 *scratch = (Scratch_80090854 *)0x1F800000;
    s16 scan_z;
    s16 scan_x;
    s32 block = (s16)(query_x & -0x40);
    Global_80090854 *global = ((Global_80090854 *)&g_game_work);
    Map_80090854 *map;
    u16 *tiles;
    Vec_80090854 *vertices;

    scan_x = query_x;
    scan_z = query_y;
    map = &global->map;

    (scratch->limit) = ((s16)query_x - block) + 0x14;
    scratch->best = 0;
    scratch->block = block;
    query_y &= 0x3F;
    scratch->x = query_y;
    scratch->z = query_z;
    scratch->planes = map->planes;
    query_x &= 0x3F;
    scratch->result = query_x;
    scratch->origin_x = query_y;
    tiles = global->map.tiles;
    vertices = map->vertices;

    if (query_x >= 0x20) {
        scratch->x_step = 0x40;
    } else {
        scratch->x_step = -0x40;
    }

    if ((s16)scratch->x >= 0x20) {
        s32 positive_step;

        positive_step = 0x40;
        scratch->z_step = positive_step;
    } else {
        register s32 negative_step;

        negative_step = -0x40;
        scratch->z_step = negative_step;
    }

    scratch->outer_count = 0;
    scratch->scan_x = scan_x;
    scratch->scan_z = scan_z;
    scratch->outer_offset = 0;
    while (scratch->outer_count < 2) {
        {
            s16 next_z = (u16)scratch->scan_z + (u16)scratch->outer_offset;

            scan_z = next_z;
            if (scratch->z_step >= 0) {
                if (next_z >= (*((s32 *)town_map_row_extent))) {
                    break;
                }
            } else if (next_z < 0) {
                break;
            }
        }

        scratch->inner_count = 0;
        scratch->inner_offset = 0;
        scratch->x = (u16)scratch->origin_x - (u16)scratch->outer_offset;
        while (scratch->inner_count < 2) {
            {
                s16 next_x = (u16)scratch->scan_x + (u16)scratch->inner_offset;

                scan_x = next_x;
                if (scratch->x_step >= 0) {
                    if (next_x >= (*((s32 *)town_map_column_extent))) {
                        break;
                    }
                } else if (next_x < 0) {
                    break;
                }
            }

            {
                s16 tile_x;
                u16 tile_index;
                s32 signed_x;
                s32 shifted_x;

                shifted_x = (s32)((u32)(u16)scan_x << 16);
                signed_x = shifted_x >> 16;
                tile_x = map->x_mask & (signed_x / 64);
                scratch->tile = tile_x;
                tile_index = tile_x +
                    ((s16)(map->z_mask & (scan_z / 64)) << map->shift);
                scratch->tile = tile_index;

                if (tiles[scratch->tile] != 0) {
                    Cell_80090854 *cell;
                    u16 tile_value;
                    s32 vertex_delta;

                    scratch->inner_bias = scratch->inner_offset;
                    tile_value = tiles[scratch->tile];
                    cell = map->cells[tile_value & 0x3FFF];
                    for (;;) {
                        if (scratch->planes[cell->plane].x > 0 &&
                            !(((u8 *)&cell->flags)[1] & 1)) {
                            s32 plane_x;

                            vertex_delta = (u16)vertices[cell->v4].y;
                            vertex_delta -= (u16)scratch->x;
                            scratch->quad[0] = vertex_delta;
                            vertex_delta = (u16)vertices[cell->v4].z;
                            vertex_delta -= (u16)scratch->z;
                            scratch->quad[1] = vertex_delta;
                            vertex_delta = (u16)vertices[cell->v6].y;
                            vertex_delta -= (u16)scratch->x;
                            scratch->quad[2] = vertex_delta;
                            vertex_delta = (u16)vertices[cell->v6].z;
                            vertex_delta -= (u16)scratch->z;
                            scratch->quad[3] = vertex_delta;
                            vertex_delta = (u16)vertices[cell->v2].y;
                            vertex_delta -= (u16)scratch->x;
                            scratch->quad[4] = vertex_delta;
                            vertex_delta = (u16)vertices[cell->v2].z;
                            vertex_delta -= (u16)scratch->z;
                            scratch->quad[5] = vertex_delta;
                            vertex_delta = (u16)vertices[cell->v0].y;
                            vertex_delta -= (u16)scratch->x;
                            scratch->quad[6] = vertex_delta;
                            vertex_delta = (u16)vertices[cell->v0].z;
                            vertex_delta -= (u16)scratch->z;
                            scratch->quad[7] = vertex_delta;

                            if (check_scratch_quad_half_turn_gaps(scratch) != 0) {
                                u16 plane_index = cell->plane;
                                u16 vertex_index = cell->v0;
                                register Vec_80090854 *plane;
                                register Vec_80090854 *vertex;
                                s32 delta_y;
                                s32 delta_z;
                                s32 y_product;
                                s32 z_product;
                                s32 x_product;

                                plane = (Vec_80090854 *)(plane_index * 8 + (u32)scratch->planes);
                                vertex = (Vec_80090854 *)(vertex_index * 8 + (u32)vertices);
                                delta_y = vertex->y - (s16)scratch->x;
                                delta_z = vertex->z - (s16)scratch->z;
                                y_product = plane->y * delta_y;
                                z_product = plane->z * delta_z;
                                x_product = plane->x * vertex->x;
                                plane_x = (y_product + z_product + x_product) / plane->x;
                                scratch->result = plane_x;
                                scratch->result += scratch->inner_bias;
                                if (scratch->limit >= scratch->result &&
                                    scratch->best < scratch->result) {
                                    scratch->best = scratch->result;
                                }
                            }
                        }

                        {
                            s32 end_flags;
                            end_flags = cell->flags & 0x80FF;
                            if (end_flags != 0x8001) {
                                cell = (Cell_80090854 *)((u8 *)cell + 0x18);
                            } else {
                                break;
                            }
                        }
                    }
                }
            }

            scratch->inner_count++;
            scratch->inner_offset += scratch->x_step;
        }
        scratch->outer_count++;
        scratch->outer_offset += scratch->z_step;
    }

    if (scratch->best == 0) {
        return 0;
    }
    {
        map = (Map_80090854 *)((s16)((u16)scratch->block + (u16)scratch->best));
        return (s32)map;
    }
}

/* Find the lowest qualifying surface height among neighboring map cells. */
s32 find_lowest_surface_height(world_x, world_y, world_z)
s32 world_x;
s32 world_y;
u16 world_z;
{
    LowestSurfaceScratch *scratch = (LowestSurfaceScratch *)0x1F800000;
    u16 *grid;
    LowestSurfaceVector *vertices;
    register s16 scan_x;
    s16 scan_y;
    s32 base_y;
    LowestSurfaceGlobal *global;
    LowestSurfaceMap *map;

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
            if ((s16)next_y >= (*((s32 *)town_map_row_extent))) {
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
                if ((s16)next_x >= (*((s32 *)town_map_column_extent))) {
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
                    LowestSurfaceCell *record;
                    u16 grid_value;

                    scratch->x = scratch->base_x - scratch->inner_delta;
                    grid_value = grid[scratch->cell];
                    record = map->records[grid_value & 0x3FFF];
                    for (;;) {
                        if ((scratch->planes[record->plane].y < 0) && !(((u8 *)&record->flags)[1] & 1)) {
                            s32 height;
                            u32 vertex_index;

                            vertex_index = record->vertex4;
                            scratch->quad[0] = ((s16)(vertices[vertex_index].x)) - *(s16 *)&scratch->x;
                            vertex_index = record->vertex4;
                            scratch->quad[1] = ((s16)(vertices[vertex_index].z)) - *(s16 *)&scratch->z;
                            vertex_index = record->vertex6;
                            scratch->quad[2] = ((s16)(vertices[vertex_index].x)) - *(s16 *)&scratch->x;
                            vertex_index = record->vertex6;
                            scratch->quad[3] = ((s16)(vertices[vertex_index].z)) - *(s16 *)&scratch->z;
                            vertex_index = record->vertex2;
                            scratch->quad[4] = ((s16)(vertices[vertex_index].x)) - *(s16 *)&scratch->x;
                            vertex_index = record->vertex2;
                            scratch->quad[5] = ((s16)(vertices[vertex_index].z)) - *(s16 *)&scratch->z;
                            vertex_index = record->vertex0;
                            scratch->quad[6] = ((s16)(vertices[vertex_index].x)) - *(s16 *)&scratch->x;
                            vertex_index = record->vertex0;
                            scratch->quad[7] = ((s16)(vertices[vertex_index].z)) - *(s16 *)&scratch->z;

                            if (check_scratch_quad_half_turn_gaps(scratch) != 0) {
                                {
                                    s16 vertex_coord;
                                    s32 normal_x;
                                    height = ((normal_x = scratch->planes[record->plane].x) * ((vertex_coord = vertices[record->vertex0].x) - (s16)scratch->x)
                                              + scratch->planes[record->plane].z * ((vertex_coord = vertices[record->vertex0].z)
                                                  - (s16)scratch->z)
                                              + scratch->planes[record->plane].y * vertices[record->vertex0].y) / scratch->planes[record->plane].y;
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
                            flags = record->flags & 0x80FF;
                            if (flags != 0x8001) {
                                record = (LowestSurfaceCell *)((u8 *)record + 0x18);
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

/* Returns the highest valid cell height within the scan limit, or zero if none. */
s32 find_highest_valid_cell_height(s32 world_x, s32 world_z, s32 world_y)
{
    Scratch_8008EA20 *scratch = (Scratch_8008EA20 *)0x1F800000;
    s16 scan_x = world_x;
    s16 scan_z = world_z;
    s16 query_y = world_y;
    s32 z_base;
    s32 tile_mask;
    Global_8008EA20 *global = ((Global_8008EA20 *)&g_game_work);
    Map_8008EA20 *map = &global->map;
    u16 *tiles;
    Vec_8008EA20 *vertices;

    tile_mask = -0x40;
    z_base = (s32)((u32)(world_z & tile_mask) << 16) >> 16;
    scratch->limit = ((s16)world_z - z_base) + 0x14;
    scratch->best = 0;
    scratch->z_base = z_base;
    scratch->x = world_x & 0x3F;
    scratch->y = query_y;
    scratch->heights = map->heights;
    scratch->z = world_z & 0x3F;
    scratch->x_origin = world_x & 0x3F;
    tiles = global->map.tiles;
    vertices = map->vertices;

    if ((world_x & 0x3F) >= 0x20) {
        scratch->x_step = 0x40;
    } else {
        scratch->x_step = tile_mask;
    }

    if (scratch->z < 0x20) {
        scratch->z_step = -0x40;
    } else {
        scratch->z_step = 0x40;
    }

    scratch->z_count = 0;
    scratch->x_start = scan_x;
    scratch->z_start = scan_z;
    scratch->z_offset_acc = 0;

    while (scratch->z_count < 2) {
        scan_z = (u16)scratch->z_start + (u16)scratch->z_offset_acc;
        if (scratch->z_step >= 0) {
            if (scan_z >= (*((s32 *)town_map_row_extent))) {
                break;
            }
        } else if (scan_z < 0) {
            break;
        }

        scratch->x_count = 0;
        scratch->x_offset = 0;
        scratch->z_offset = (u16)scratch->z_offset_acc;

        while (scratch->x_count < 2) {
            s32 grid_x;
            s32 grid_z;

            scan_x = (u16)scratch->x_start + (u16)scratch->x_offset;
            if (scratch->x_step >= 0) {
                if (scan_x >= (*((s32 *)town_map_column_extent))) {
                    break;
                }
            } else if (scan_x < 0) {
                break;
            }

            grid_x = scan_x;
            scratch->tile = map->x_mask & (grid_x / 64);

            grid_z = scan_z;
            scratch->tile +=
                (s16)(map->z_mask & (grid_z / 64)) << map->shift;

            if (tiles[(s16)scratch->tile] != 0) {
                u16 tile_entry;
                Cell_8008EA20 *cell;

                scratch->x =
                    (u16)scratch->x_origin - (u16)scratch->x_offset;
                tile_entry = tiles[(s16)scratch->tile];
                cell = map->cells[tile_entry & 0x3FFF];

                for (;;) {
                    if (scratch->heights[cell->height_index].y > 0 &&
                        !(((u8 *)&cell->flags)[1] & 1)) {
                        s32 cell_height;

                        scratch->quad[0] =
                            vertices[cell->v0].x - (u16)scratch->x;
                        scratch->quad[1] =
                            vertices[cell->v0].z - (u16)scratch->y;
                        scratch->quad[2] =
                            vertices[cell->v1].x - (u16)scratch->x;
                        scratch->quad[3] =
                            vertices[cell->v1].z - (u16)scratch->y;
                        scratch->quad[4] =
                            vertices[cell->v2].x - (u16)scratch->x;
                        scratch->quad[5] =
                            vertices[cell->v2].z - (u16)scratch->y;
                        scratch->quad[6] =
                            vertices[cell->v3].x - (u16)scratch->x;
                        scratch->quad[7] =
                            vertices[cell->v3].z - (u16)scratch->y;

                        if (check_scratch_quad_half_turn_gaps(scratch) != 0) {
                            s16 local_x = scratch->x;

                            cell_height =
                                (scratch->heights[cell->height_index].x *
                                 (vertices[cell->v0].x - local_x) +
                                 scratch->heights[cell->height_index].z *
                                 (vertices[cell->v0].z - (s16)scratch->y) +
                                 scratch->heights[cell->height_index].y *
                                 vertices[cell->v0].y) /
                                scratch->heights[cell->height_index].y;
                            scratch->z = cell_height;
                            scratch->z += (u16)scratch->z_offset;
                            if (scratch->limit >= scratch->z &&
                                scratch->best < scratch->z) {
                                scratch->best = scratch->z;
                            }
                        }
                    }

                    if ((cell->flags & 0x80FF) == 0x8001) {
                        break;
                    }
                    cell = (Cell_8008EA20 *)((u8 *)cell + 0x18);
                }
            }

            scratch->x_count++;
            scratch->x_offset += scratch->x_step;
        }

        scratch->z_count++;
        scratch->z_offset_acc += scratch->z_step;
    }

    if (scratch->best == 0) {
        return 0;
    }
    return (s16)((u16)scratch->z_base + (u16)scratch->best);
}
