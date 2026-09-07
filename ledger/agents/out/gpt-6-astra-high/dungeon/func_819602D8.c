#include "common.h"
#include "m2c_compat.h"

extern u16 D_800273CC[8];
extern u8 D_8002744C[9];
extern u8 D_8002744D[9];
extern u8 *D_800E3D7C[];
extern u8 D_8008333C[32];
extern s16 D_8008333C_second[16] __asm__("D_8008333C");
extern s32 D_800274DC[7][8];
void func_80025C14(void) __attribute__((noreturn));
s32 func_80025D30(s32, s32, s32);
void *func_8009B4B0(void *, u16, u16);
s32 func_800BCA68(s32, u16);
extern s32 D_8002732C;

typedef struct S_819602D8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_819602D8_0;   /* temp_v0 in func_819602D8 */

/* Sample a 7 by 7 area around the given tile and flag the tiles found there. */
void func_819602D8(s16 center_x, s32 center_y) {
    volatile union {
        u16 h;
        u8 b;
    } saved_center_x;
    register s32 tile_x ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 signed_y ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 tile_y;
    u8 *sample_row;
    s32 world_y;
    s32 sample_y;
    register u16 *sample_ptr ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u32 col ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u32 row;
    u8 *store_page;
    s32 sample_x;
    s32 tile_sample;
    void *map;
    S_819602D8_0 *tile;

    tile_y = center_y - 3;
    row = 0;
    sample_row = D_800273CC;
    store_page = (u8 *)0x80020000;
    saved_center_x.h = center_x;
    {
        register u32 center_x_byte ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
        center_x_byte = saved_center_x.b;
        ASM_KEEP4_NV(store_page, row, tile_y, sample_row);   /* MATCH pin: retail immediate-load split depends on it */
        store_page[0x744C] = center_x_byte;
    }
    do { *D_8002744D = center_y; } while (0);
row_loop:
    {
        register u32 row_center_x ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
        register s32 shifted_y ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        row_center_x = saved_center_x.h;
        ASM_KEEP_NV(row_center_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
        col = 0;
        shifted_y = tile_y << 16;
        signed_y = shifted_y >> 16;
        world_y = signed_y << 6;
        ASM_KEEP_NV(world_y);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        sample_y = world_y + 0x20;
        ASM_KEEP_NV(world_y);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        sample_ptr = (u16 *)sample_row;
        tile_x = row_center_x - 3;
    }
    ASM_USE2_NV(world_y, tile_y);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_USE_NV(row);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
col_loop:
    tile_sample = func_800BCA68((tile_x << 6) & 0xFFC0, world_y);
    map = *D_800E3D7C;
    *sample_ptr = 0 - tile_sample;
    tile = func_8009B4B0(map, tile_x, tile_y);
    if ((tile != NULL) && (tile != D_8002732C)) {
        tile->unk_14 = (s32)(tile->unk_14 | 0x100000);
    }
    sample_x = (s16)tile_x;
    if (sample_x < 0) {
        goto bounds_fail;
    }
    {
        s32 width_check;
        {
            register s16 *width_info ASM_REG("$7") = (s16 *)D_8008333C;   /* MATCH pin: retail register colouring depends on it */
            width_check = width_info[10];
            ASM_USE_NV(width_info);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        }
        {
            register s32 width_unit ASM_REG("$7") = 1;   /* MATCH pin: retail register colouring depends on it */
            width_check = width_unit << width_check;
        }
        width_check = sample_x < width_check;
        if (!width_check) {
            goto bounds_fail;
        }
    }
    if (signed_y < 0) {
        goto bounds_fail;
    }
    {
        s32 height_check;
        {
            register s16 *height_info ASM_REG("$7") = D_8008333C_second;   /* MATCH pin: retail register colouring depends on it */
            height_check = height_info[11];
            ASM_USE_NV(height_info);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        }
        {
            register s32 height_unit ASM_REG("$7") = 1;   /* MATCH pin: retail register colouring depends on it */
            height_check = height_unit << height_check;
        }
        height_check = signed_y < height_check;
        if (height_check) {
            goto bounds_ok;
        }
    }
bounds_fail:
    {
        register s32 zero_arg ASM_REG("$4") = 0;   /* MATCH pin: load-bearing for the whole function shape */
        ASM_TAILSLOT_PIN(zero_arg);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80025C14();
    }
bounds_ok:
    {
        s32 *output_base;
        register u32 output_row ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
        s32 output_value;
        sample_x <<= 6;
        sample_x += 0x20;
        sample_x &= 0xFFE0;
        output_value = func_80025D30(sample_x, sample_y & 0xFFFF, -0x400);
        ASM_KEEP_NV(output_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        output_base = &D_800274DC[0][0];
        ASM_KEEP_NV(output_base);   /* MATCH pin: retail schedule: same instructions, different order without it */
        output_row = row << 5;
        output_row += (u32)output_base;
        ((s32 *)output_row)[col] = output_value;
    }
    sample_ptr += 1;
    col += 1;
    tile_x += 1;
    if (col >= 7U) {
        sample_row += 16;
        row += 1;
        tile_y += 1;
        if (row >= 7U) {
            return;
        }
        goto row_loop;
    }
    goto col_loop;
}
