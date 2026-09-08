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
extern void func_8008E598(void) __attribute__((noreturn));
extern void func_8008E628(void) __attribute__((noreturn));
extern s32 func_8008E698(s32);
extern void func_8008E740(void) __attribute__((noreturn));

s32 func_8008E4EC(s32 arg0, s32 arg1, u16 arg2)
{
    Scratch *sc = (Scratch *)0x1F800000;
    u16 *grid;
    Vec8 *vertices;
    register s16 scan_x ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s16 scan_y;
    s32 base_y;
    GlobalState *global;
    MapInfo *map;

    scan_x = arg0;
    scan_y = arg1;
    base_y = (s16)(arg1 & -0x40);
    sc->best = 0x7FFF;
    sc->lower = ((s16)arg1 - base_y) - 0x14;
    sc->base_y = base_y;
    sc->x = arg0 & 0x3F;
    sc->z = arg2;
    sc->y = arg1 & 0x3F;
    sc->base_x = arg0 & 0x3F;
    global = &D_80083160;
    map = &D_80083160.map;
    sc->planes = map->planes;
    grid = global->map.grid;
    vertices = map->vertices;

    if (sc->x >= 0x20) {
        sc->step_x = 0x40;
        func_8008E598();
    }
    sc->step_x = -0x40;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    if ((s16)sc->y >= 0x20) {
        sc->step_y = 0x40;
    } else {
        register s32 nv ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        nv = -0x40;
        sc->step_y = nv;
    }

    sc->outer_count = 0;
    sc->scan_x = scan_x;
    sc->scan_y = scan_y;
    sc->outer_delta = 0;

    while (sc->outer_count < 2) {
        s32 ty = (u16)sc->scan_y + (u16)sc->outer_delta;
        scan_y = ty;
        if (sc->step_y >= 0) {
            if ((s16)ty < D_800FE484) {
                func_8008E628();
            }
            break;
        }
        if ((s16)ty < 0) {
            break;
        }

        sc->inner_count = 0;
        sc->inner_delta = 0;
        sc->outer_bias = sc->outer_delta;

        while (sc->inner_count < 2) {
            s32 tx = (u16)sc->scan_x + (u16)sc->inner_delta;
            scan_x = tx;
            if (sc->step_x >= 0) {
                if ((s16)tx < D_800FE480) {
                    register s32 t2 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    t2 = ((s32)scan_x) << 16;
                    return func_8008E698(t2 >> 16);
                }
                break;
            }
            if ((s16)tx < 0) {
                break;
            }

            {
                s32 xq;
                s32 yq;
                u16 cell;
                { register s32 t2 ASM_REG("$2"); t2 = ((s32)scan_x) << 16; xq = t2 >> 16; }

                if (xq < 0) {
                    xq += 0x3F;
                }
                yq = scan_y;
                { u16 xm; s32 xs; xm = map->x_mask; xs = xq >> 6; sc->cell = xm & xs; }
                if (yq < 0) {
                    yq += 0x3F;
                }
                cell = sc->cell + ((s16)(map->y_mask & (yq >> 6)) << map->shift);
                sc->cell = cell;

                if (grid[sc->cell] != 0) {
                    CellRecord *record;
                    u8 *end;
                    u16 grid_value;

                    sc->x = sc->base_x - sc->inner_delta;
                    grid_value = grid[sc->cell];
                    record = map->records[grid_value & 0x3FFF];
                    end = (u8 *)record + 0x16;

                    if ((sc->planes[*(u16 *)(end - 6)].y < 0) && !(*(end + 1) & 1)) {
                        s32 value;
                        u32 vertex_index;
                        register s16 qtmp ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        Scratch *call_arg;
                        call_arg = sc;
                        ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

                        vertex_index = *(u16 *)(end - 0x12);
                        qtmp = vertices[vertex_index].x; sc->quad[0] = qtmp - *(volatile s16 *)&sc->x;
                        vertex_index = *(u16 *)(end - 0x12);
                        qtmp = vertices[vertex_index].z; sc->quad[1] = qtmp - *(volatile s16 *)&sc->z;
                        vertex_index = *(u16 *)(end - 0x10);
                        qtmp = vertices[vertex_index].x; sc->quad[2] = qtmp - *(volatile s16 *)&sc->x;
                        vertex_index = *(u16 *)(end - 0x10);
                        qtmp = vertices[vertex_index].z; sc->quad[3] = qtmp - *(volatile s16 *)&sc->z;
                        vertex_index = *(u16 *)(end - 0x14);
                        qtmp = vertices[vertex_index].x; sc->quad[4] = qtmp - *(volatile s16 *)&sc->x;
                        vertex_index = *(u16 *)(end - 0x14);
                        qtmp = vertices[vertex_index].z; sc->quad[5] = qtmp - *(volatile s16 *)&sc->z;
                        vertex_index = record->vertex0;
                        qtmp = vertices[vertex_index].x; sc->quad[6] = qtmp - *(volatile s16 *)&sc->x;
                        vertex_index = record->vertex0;
                        qtmp = vertices[vertex_index].z; sc->quad[7] = qtmp - *(volatile s16 *)&sc->z;

                        if (func_8008CE08(call_arg) != 0) {
                            {
                                register s32 vx ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                                register s32 pv ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                                value = ((pv = sc->planes[*(u16 *)(end - 6)].x) * ((vx = vertices[record->vertex0].x) - (s16)sc->x)
                                       + sc->planes[*(u16 *)(end - 6)].z * ((vx = vertices[record->vertex0].z) - (s16)sc->z)
                                       + sc->planes[*(u16 *)(end - 6)].y * vertices[record->vertex0].y) / sc->planes[*(u16 *)(end - 6)].y;
                            }
                            sc->y = value;
                            sc->y += sc->outer_bias;
                            if ((sc->y >= sc->lower) && (sc->y < sc->best)) {
                                sc->best = sc->y;
                            }
                        }
                    }

                    {
                        u16 fl;
                        fl = *(u16 *)end & 0x80FF;
                        end += 0x18;
                        if (fl != 0x8001) {
                            record = (CellRecord *)((u8 *)record + 0x18);
                            ASM_TAILSLOT_PIN(record);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                            func_8008E740();
                        }
                    }
                    ASM_KEEP(end);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                }
            }

            sc->inner_count++;
            sc->inner_delta += sc->step_x;
        }

        sc->outer_count++;
        sc->outer_delta += sc->step_y;
    }

    if (sc->best != 0x7FFF) {
        return (s16)(sc->base_y + sc->best);
    }
    return 0x7FFF;
}
