#include "common.h"

extern u8 D_80083160_addr[] asm("D_80083160");
extern void func_80026A18(void) __attribute__((noreturn));
extern s32 func_800654B0();
extern s32 func_8006658C();
extern s32 func_800666F4();

/* Project a textured quad and queue it with semitransparency when its depth is in range. */
s32 func_819611CC(void *quad_data, s32 unused, void *material)
{
    u8 *scratch;
    u8 *state_slot;
    u32 state_snapshot;
    u8 *render_state;
    u8 *initial_state;
    u8 *packet;
    register u8 *quad_code ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *texture ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 tex_u;
    u8 tex_v;
    u8 code;
    register u8 uv_end ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 uv_size ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 vertex_z;
    u16 last_z;
    u32 depth_bucket;
    register u32 last_xy ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *vertex0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *vertex1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *vertex3;
    u8 *screen_xy0;
    u8 *draw_packet;
    void *vertex_or_link;
    register void *quad ASM_REG("$19") = quad_data;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *quad_material = material;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    initial_state = *((u8 **) D_80083160_addr);
    state_slot = D_80083160_addr;
    packet = *((u8 **) (initial_state + 0x8D0));
    scratch = (volatile u8 *) 0x1F800000;
    *((u32 *) (scratch + 0x20)) = (u32) (initial_state + 0xB0);
    ASM_KEEP_MEMDEP(scratch, state_snapshot, *((u8 **) D_80083160_addr));   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    quad_code = packet + 7;
    ASM_KEEP(quad_code);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    *((u32 *) (scratch + 0x70)) = *((u32 *) (((u8 *) quad) + 0x10));
    *((u32 *) (scratch + 0x78)) = *((u32 *) (((u8 *) quad) + 0x18));
    *((u32 *) (scratch + 0x80)) = *((u32 *) (((u8 *) quad) + 0x20));
    vertex0 = scratch + 0x70;
    vertex_z = *((u16 *) (((u8 *) quad) + 0x14));
    texture = *((u8 **) (((u8 *) quad_material) + 8));
    ASM_KEEP(texture);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    last_xy = *((u32 *) (((u8 *) quad) + 0x28));
    vertex1 = scratch + 0x78;
    *((u16 *) (scratch + 0x74)) = vertex_z;
    vertex_z = *((u16 *) (((u8 *) quad) + 0x1C));
    vertex_or_link = scratch + 0x80;
    *((u16 *) (scratch + 0x7C)) = vertex_z;
    vertex_z = *((u16 *) (((u8 *) quad) + 0x24));
    ASM_SET(vertex3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    vertex3 = scratch + 0x88;
    *((u32 *) (scratch + 0x88)) = last_xy;
    *((u16 *) (scratch + 0x84)) = vertex_z;
    last_z = *((u16 *) (((u8 *) quad) + 0x2C));
    screen_xy0 = packet + 8;
    *((u16 *) (scratch + 0x8C)) = last_z;
    ASM_KEEP_NV(state_slot);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_JALDELAY_PIN(last_z);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    depth_bucket = func_800654B0(vertex0, vertex1, vertex_or_link, vertex3, screen_xy0,
                            packet + 0x10, packet + 0x18, packet + 0x20,
                            (void *) (scratch + 0x90), (void *) (scratch + 0x94)) - 8;
    *((u32 *) (scratch + 0xC0)) = depth_bucket;
    if (depth_bucket < 480) {
        tex_u = texture[8];
        quad_code[0x15] = tex_u;
        quad_code[5] = tex_u;
        uv_end = texture[8];
        uv_size = texture[0xA];
        uv_end = uv_end + uv_size;
        quad_code[0x1D] = uv_end;
        quad_code[0xD] = uv_end;
        tex_v = texture[9];
        quad_code[0xE] = tex_v;
        quad_code[6] = tex_v;
        uv_end = texture[9];
        uv_size = texture[0xB];
        uv_end = uv_end + uv_size;
        quad_code[0x1E] = uv_end;
        quad_code[0x16] = uv_end;
        *((u16 *) (quad_code + 0xF)) = *((u16 *) (texture + 4));
        *((s32 *) (quad_code - 3)) = *((s32 *) (((u8 *) quad_material) + 0xC));
        func_800666F4(packet);
        draw_packet = packet;
        code = quad_code[0];
        packet += 0x28;
        quad_code[0] = code | 2;
        quad_code += 0x28;
        ASM_KEEP(quad_code);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        func_8006658C((*((u32 *) (scratch + 0x20))) + ((*((u32 *) (scratch + 0xC0))) << 2), draw_packet);
    }
    vertex_or_link = ((void **) quad)[-2];
    if (vertex_or_link != 0) {
        quad = ((u8 *) vertex_or_link) + 32;
        ASM_KEEP(quad);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        quad_material = *((void **) (((u8 *) vertex_or_link) + 12));
        ASM_KEEP(quad_material);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        func_80026A18();
    }
    render_state = *((u8 **) state_slot);
    ASM_SET(zero);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    result = zero;
    do {
        *((u32 *) (render_state + 0x8D0)) = (u32) packet;
    } while (0);
    return result;
}
