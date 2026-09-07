#include "common.h"

typedef struct Vec_80090854 {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vec_80090854;

typedef struct Cell_80090854 {
    u16 v0;
    u16 v2;
    u16 v4;
    u16 v6;
    u8 pad08[8];
    u16 plane;
    u8 pad12[4];
    u16 flags;
} Cell_80090854;

typedef struct Map_80090854 {
    u16 *tiles;
    Cell_80090854 **cells;
    Vec_80090854 *vertices;
    Vec_80090854 *planes;
    u8 pad10[4];
    s16 shift;
    u16 pad16;
    u16 x_mask;
    u16 z_mask;
} Map_80090854;

typedef struct Scratch_80090854 {
    u8 pad00[4];
    s16 tile;
    u8 pad06[0x12];
    Vec_80090854 *planes;
    s16 result;
    s16 x;
    s16 z;
    u8 pad22[0xE];
    s32 best;
    s32 limit;
    s32 block;
    u8 pad3C[0xC];
    s16 inner_bias;
    u8 pad4A[4];
    s16 origin_x;
    s16 scan_x;
    s16 scan_z;
    s32 x_step;
    s32 z_step;
    s32 inner_count;
    s32 outer_count;
    s32 inner_offset;
    s32 outer_offset;
    s16 quad[8];
} Scratch_80090854;

typedef struct Global_80090854 {
    u8 pad000[0x1DC];
    Map_80090854 map;
} Global_80090854;

extern Global_80090854 D_80083160;
extern s32 D_800FE480;
extern s32 D_800FE484;

extern s32 func_8008CE08(Scratch_80090854 *);
extern void func_8008E05C(void) __attribute__((noreturn));
extern void func_8008E0EC(void) __attribute__((noreturn));
extern void func_8008E164(void) __attribute__((noreturn));
extern void func_8008E204(void) __attribute__((noreturn));
extern s32 func_8008E4C0(void);

s32 func_8008DFB4(s16 arg0, u16 arg1, u16 arg2)
{
    Scratch_80090854 *scratch = (Scratch_80090854 *)0x1F800000;
    s16 scan_z;
    s16 scan_x;
    s32 block = (s16)(arg0 & -0x40);
    Global_80090854 *global = &D_80083160;
    register Map_80090854 *map ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u16 *tiles ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    Vec_80090854 *vertices;

    scan_x = arg0;
    scan_z = arg1;
    map = &global->map;

    scratch->limit = ((s16)arg0 - block) + 0x14;
    scratch->best = 0;
    scratch->block = block;
    arg1 &= 0x3F;
    scratch->x = arg1;
    scratch->z = arg2;
    scratch->planes = map->planes;
    arg0 &= 0x3F;
    scratch->result = arg0;
    scratch->origin_x = arg1;
    tiles = global->map.tiles;
    vertices = map->vertices;

    if (arg0 >= 0x20) {
        scratch->x_step = 0x40;
        func_8008E05C();
    }
    scratch->x_step = -0x40;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */

    if ((s16)scratch->x >= 0x20) {
        s32 z_pos;

        z_pos = 0x40;
        scratch->z_step = z_pos;
    } else {
        register s32 z_neg ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */

        z_neg = -0x40;
        scratch->z_step = z_neg;
    }

    scratch->outer_count = 0;
    scratch->scan_x = scan_x;
    scratch->scan_z = scan_z;
    scratch->outer_offset = 0;
    if (scratch->outer_count >= 2) {
        goto finished;
    }

outer_loop:
    {
        s16 sum_z = (u16)scratch->scan_z + (u16)scratch->outer_offset;

        scan_z = sum_z;
        if (scratch->z_step >= 0) {
            if (sum_z < D_800FE484) {
                func_8008E0EC();
            }
            goto finished;
        }
        if (sum_z < 0) {
            goto finished;
        }
    }

    scratch->inner_count = 0;
    scratch->inner_offset = 0;
    scratch->x = (u16)scratch->origin_x - (u16)scratch->outer_offset;
    if (scratch->inner_count >= 2) {
        goto next_outer;
    }

inner_loop:
    {
        s16 sum_x = (u16)scratch->scan_x + (u16)scratch->inner_offset;

        scan_x = sum_x;
        if (scratch->x_step >= 0) {
            if (sum_x < D_800FE480) {
                register s32 e164_arg ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
                register s32 e164_hi ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */

                e164_hi = (s32)((u32)(u16)scan_x << 16);
                e164_arg = e164_hi >> 16;
                ASM_TAILSLOT_PIN(e164_arg);   /* MATCH pin: retail delay-slot contents depend on it */
                func_8008E164();
            }
            goto next_outer;
        }
        if (sum_x < 0) {
            goto next_outer;
        }
    }

    {
        s16 x_part;
        u16 tile;
        s32 sx;
        s32 sx_hi;

        sx_hi = (s32)((u32)(u16)scan_x << 16);
        sx = sx_hi >> 16;
        x_part = map->x_mask & (sx / 64);
        scratch->tile = x_part;
        tile = x_part +
            ((s16)(map->z_mask & (scan_z / 64)) << map->shift);
        scratch->tile = tile;

        if (tiles[scratch->tile] != 0) {
            Cell_80090854 *cell;
            u8 *tail;
            u16 tile_value;
            s32 tmp;

            scratch->inner_bias = scratch->inner_offset;
            tile_value = tiles[scratch->tile];
            cell = map->cells[tile_value & 0x3FFF];
            tail = (u8 *)cell + 0x16;

            if (scratch->planes[*(u16 *)(tail - 6)].x > 0 &&
                !(tail[1] & 1)) {
                s32 value;

                tmp = (u16)vertices[*(u16 *)(tail - 0x12)].y;
                tmp -= (u16)scratch->x;
                scratch->quad[0] = tmp;
                tmp = (u16)vertices[*(u16 *)(tail - 0x12)].z;
                tmp -= (u16)scratch->z;
                scratch->quad[1] = tmp;
                tmp = (u16)vertices[*(u16 *)(tail - 0x10)].y;
                tmp -= (u16)scratch->x;
                scratch->quad[2] = tmp;
                tmp = (u16)vertices[*(u16 *)(tail - 0x10)].z;
                tmp -= (u16)scratch->z;
                scratch->quad[3] = tmp;
                tmp = (u16)vertices[*(u16 *)(tail - 0x14)].y;
                tmp -= (u16)scratch->x;
                scratch->quad[4] = tmp;
                tmp = (u16)vertices[*(u16 *)(tail - 0x14)].z;
                tmp -= (u16)scratch->z;
                scratch->quad[5] = tmp;
                tmp = (u16)vertices[cell->v0].y;
                tmp -= (u16)scratch->x;
                scratch->quad[6] = tmp;
                tmp = (u16)vertices[cell->v0].z;
                tmp -= (u16)scratch->z;
                scratch->quad[7] = tmp;

                if (func_8008CE08(scratch) != 0) {
                    u16 pi = *(u16 *)(tail - 6);
                    u16 ci = cell->v0;
                    register Vec_80090854 *plane ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
                    register Vec_80090854 *vertex ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
                    s32 dy;
                    s32 dz;
                    s32 y_product;
                    s32 z_product;
                    s32 x_product;

                    plane = (Vec_80090854 *)(pi * 8 + (u32)scratch->planes);
                    vertex = (Vec_80090854 *)(ci * 8 + (u32)vertices);
                    dy = vertex->y - (s16)scratch->x;
                    dz = vertex->z - (s16)scratch->z;
                    y_product = plane->y * dy;
                    z_product = plane->z * dz;
                    x_product = plane->x * vertex->x;
                    value = (y_product + z_product + x_product) / plane->x;
                    scratch->result = value;
                    scratch->result += scratch->inner_bias;
                    if (scratch->limit >= scratch->result &&
                        scratch->best < scratch->result) {
                        scratch->best = scratch->result;
                    }
                }
            }

            {
            register u16 fl ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            fl = *(u16 *)tail & 0x80FF;
            if (fl != 0x8001) {
                tail += 0x18;
                ASM_KEEP(tail);   /* MATCH pin: retail keeps a computation the compiler would drop */
                cell = (Cell_80090854 *)((u8 *)cell + 0x18);
                ASM_TAILSLOT_PIN(cell);   /* MATCH pin: load-bearing for the whole function shape */
                func_8008E204();
            }
            }
        }
    }

    scratch->inner_count++;
    scratch->inner_offset += scratch->x_step;
    if (scratch->inner_count < 2) {
        goto inner_loop;
    }

next_outer:
    scratch->outer_count++;
    scratch->outer_offset += scratch->z_step;
    if (scratch->outer_count < 2) {
        goto outer_loop;
    }

finished:
    if (scratch->best == 0) {
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        return 0;
    }
    {
        s32 result;
        result = (s16)((u16)scratch->block + (u16)scratch->best);
        ASM_TAILSLOT_PIN(result);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        return func_8008E4C0();
    }
}
