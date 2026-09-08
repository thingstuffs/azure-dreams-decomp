#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u8 pad0A[0xA];
    s16 height;
} FuncArg1;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
extern void *D_800E3D7C;
s32 func_8009A350();            /* extern */
void *func_8009B25C();           /* extern */
s32 func_800A0548();                        /* extern */
s16 func_800BCB04();                   /* extern */
extern s8 D_800DD7DC;


typedef struct S_8009AF18_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8009AF18_0;   /* arg2 in func_8009AF18 */

typedef struct S_8009AF18_1 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_8009AF18_1;   /* world in func_8009AF18 */

typedef struct S_8009AF18_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8009AF18_2;   /* temp_v0 in func_8009AF18 */

typedef struct S_8009AF18_3 {
    u8 pad_00[0x124];
    void * unk_124;
} S_8009AF18_3;   /* *(void **)(page + 0x3D7C) in func_8009AF18 */

typedef struct S_8009AF18_4 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8009AF18_4;   /* ((S_8009AF18_3 *)(*(void **)(page + 0x3D7C)))->unk_124 in func_8009AF18 */

/* Checks successive tiles in a direction and returns the stopping distance. */
s32 func_8009AF18(u32 direction_flags, FuncArg1 *origin, S_8009AF18_0 *start_tile, u16 max_steps) {
    u16 tile_info[5];
    u16 *tile_dx_ptr;
    s32 tile_dx_base;
    s32 direction_index;
    s32 direction;
    register s32 direction_offset;
    s32 next_step;
    s32 height_result;
    s32 shifted_limit;
    s32 check_x;
    register s32 step ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 world_y;
    s32 world_x;
    s32 shifted_step;
    s32 tile_x;
    s32 tile_y;
    S_8009AF18_2 *occupant;

    step = 1;
    ASM_KEEP_NV(step);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    D_800DD7DC = 0;
    tile_x = start_tile->unk_24;
    tile_y = start_tile->unk_25;
    direction_index = (direction_flags >> 9) & 7;
    tile_info[4] = max_steps;
    world_x = (tile_x << 6) | 0x20;
    world_y = (tile_y << 6) | 0x20;
    if ((max_steps << 0x10) > 0) {
        direction = direction_index;
        tile_dx_base = (s32)D_8006CCD8;
        direction_offset = direction << 1;
        tile_dx_ptr = (u16 *)(tile_dx_base + direction_offset);
check_tile:
        check_x = (s16) tile_x;
        if (func_800A0548(check_x, (s16) tile_y) != 0) {
            return (s16) (step - 1);
        }
        if ((func_8009A350(check_x, (s16) tile_y, direction, tile_info) << 0x10) == 0) {
            goto blocked;
        }
        {
            register u16 *tile_dx_reload ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            tile_dx_reload = tile_dx_ptr;
            ASM_KEEP_NV(tile_dx_reload);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            tile_x += *tile_dx_reload;
        }
        tile_y += *(u16 *)((u8 *)D_8006CCE8 + direction_offset);
        if (tile_info[0] & 0x3300) {
            {
                register u8 *page ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                S_8009AF18_1 *world;

                page = (u8 *)0x800E0000;
                ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                world = *(void **)(page + 0x3D7C);
                occupant = func_8009B25C(world, tile_x & 0xFFFF, tile_y & 0xFFFF, world->unk_88);
            }
            if (occupant != NULL) {
                if (occupant->unk_13 == 0x1F) {
                    if (!(occupant->unk_1C & 0x228)) {
                        {
                            register u8 *page ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                            do { } while (0);
                            page = (u8 *)0x800E0000;
                            ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                            if (((S_8009AF18_4 *)(((S_8009AF18_3 *)(*(void **)(page + 0x3D7C)))->unk_124))->unk_13 < 0) {
                                D_800DD7DC = 1;
                                occupant->unk_14 |= 0x800000;
                                goto done;
                            }
                        }
                    }
                }
                return (s16)step;
            }
            goto done;
        }
        world_x += *(u16 *)((u8 *)D_800DCEAC + direction_offset);
        world_y += *(u16 *)((u8 *)D_800DCEBC + direction_offset);
        {
            register FuncArg1 *origin_reload ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            origin_reload = origin;
            ASM_KEEP(origin_reload);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            height_result = func_800BCB04(world_x & 0xFFFF, world_y & 0xFFFF, origin_reload->height);
        }
        next_step = step + 1;
        if (height_result < 0x200) {
            goto advance_step;
        }
        return (s16) (step - 1);
blocked:
        return (s16) (step - 1);
advance_step:
        step = next_step;
        do { } while (0);
        {
            register s32 step_limit ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 shifted_next_step;

            step_limit = tile_info[4];
            shifted_next_step = next_step << 0x10;
            ASM_KEEP_NV(shifted_next_step);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            shifted_limit = step_limit << 0x10;
            ASM_KEEP_DEP_NV(shifted_limit, step_limit);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (shifted_next_step <= shifted_limit) {
                goto check_tile;
            }
        }
        goto done;
    }
done:
    shifted_step = step << 0x10;
    return shifted_step >> 0x10;
}
