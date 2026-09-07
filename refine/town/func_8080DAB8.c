/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8080DAB8_5 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8080DAB8_5;   /* (u8 *)((u32)temp_a1 + (u32)*rootp) in func_8080DAB8 */


typedef struct S_8080DAB8_0 {
    u8 pad_00[0x8D0];
    s32 unk_8D0;
} S_8080DAB8_0;   /* *rootp in func_8080DAB8 */

typedef struct S_8080DAB8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_8080DAB8_1;   /* temp_s0 in func_8080DAB8 */

typedef struct S_8080DAB8_2 {
    s32 unk_00;
    u8 pad_04[0x1C];
    s32 unk_20;
    s32 unk_24;
} S_8080DAB8_2;   /* var_s3 in func_8080DAB8; pointer addresses record offset 0x8 */

typedef struct S_8080DAB8_3 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8080DAB8_3;   /* temp_a0_2 in func_8080DAB8 */

typedef struct S_8080DAB8_4 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8080DAB8_4;   /* (u8 *)temp_a1 in func_8080DAB8 */


#define M2C_BREAK() ((void)0)

M2C_UNK func_8006BFA0();
s32 func_8006D9DC();
M2C_UNK func_8006DBBC();
M2C_UNK func_8006DD4C();
M2C_UNK func_8006F49C();
extern u8 *D_8012F130;

/* Build projected primitives and draw modes for linked records and add them to the ordering table. */
s32 func_8080DAB8(void *first_record) {
    register s32 next_record ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 ot_slot;
    s32 primitive;
    M2C_UNK *draw_mode;
    s32 primitive_cursor;
    s32 mode_cursor;
    u16 depth0_raw;
    u16 depth1_raw;
    u32 primitive_end;
    u32 mode_end;
    u32 depth0_shifted;
    u32 depth1_shifted;
    s32 depth0;
    s32 depth1;
    u32 packet_addr;
    register S_8080DAB8_3 *ot_entry ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    void *unused_ptr;
    void *record;
    u8 **render_root;
    register u8 *screen_coords;
    u8 *depths;
    u8 *transform_scratch;
    register u8 *primitive_base ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *mode_base ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register u32 addr_mask ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u32 tag_mask;
    register u32 buffer_limit ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

    record = first_record;
    render_root = &D_8012F130;
    screen_coords = (u8 *)0x1F800000;
    depths = (u8 *)0x1F800100;
    transform_scratch = (u8 *)0x1F800180;
    addr_mask = 0x00FFFFFF;
    tag_mask = 0xFF000000;
    do {
        func_8006BFA0(record + 8, screen_coords, depths, transform_scratch, transform_scratch, 2);
        primitive_cursor = 0;
        ASM_KEEP_NV(primitive_cursor);   /* MATCH pin: load-bearing for the whole function shape */
        primitive = ((S_8080DAB8_0 *)(*render_root))->unk_8D0;
        if (primitive != 0) {
            primitive_end = primitive + 0x14;
            primitive_base = (u8 *)*render_root;
            ASM_KEEP_NV(primitive_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            buffer_limit = 0x108D4;
            primitive_cursor = primitive_end & (0 - ((u32)(primitive_base + buffer_limit) >= primitive_end));
        }
        ((S_8080DAB8_0 *)(*render_root))->unk_8D0 = primitive_cursor;
        mode_cursor = 0;
        ASM_KEEP_NV(mode_cursor);   /* MATCH pin: load-bearing for the whole function shape */
        draw_mode = ((S_8080DAB8_0 *)(*render_root))->unk_8D0;
        if (draw_mode != 0) {
            mode_end = (u8 *)draw_mode + 0xC;
            mode_base = (u8 *)*render_root;
            ASM_KEEP_NV(mode_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            buffer_limit = 0x108D4;
            mode_cursor = mode_end & (0 - ((u32)(mode_base + buffer_limit) >= mode_end));
        }
        ((S_8080DAB8_0 *)(*render_root))->unk_8D0 = mode_cursor;
        func_8006F49C((s32 *)draw_mode, 0, 0, func_8006D9DC(0, 0, 0, 0) & 0xFFFF, 0);
        ((S_8080DAB8_1 *)primitive)->unk_04 = (s32)((S_8080DAB8_2 *)((u8 *)record - 0x8))->unk_20;
        ((S_8080DAB8_1 *)primitive)->unk_0C = (s32)((S_8080DAB8_2 *)((u8 *)record - 0x8))->unk_24;
        func_8006DD4C((s32 *)primitive);
        func_8006DBBC((s32 *)primitive, 1);
        ((S_8080DAB8_1 *)primitive)->unk_08 = (s32)*(s32 *)screen_coords;
        ((S_8080DAB8_1 *)primitive)->unk_10 = (s32)*(s32 *)(screen_coords + 4);
        depth0_raw = *(volatile u16 *)depths;
        depth0_shifted = depth0_raw << 0x10;
        depth1_raw = *((volatile u16 *)depths + 1);
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        depth0 = (s32)depth0_shifted >> 0x10;
        depth1_shifted = depth1_raw << 0x10;
        depth1 = (s32)depth1_shifted >> 0x10;
        depth0_shifted = (u32)((s32)depth0_shifted >> 0x13);
        if (depth0 >= depth1) {
            depth0_shifted = (u32)((s32)depth1_shifted >> 0x13);
        }
        ot_slot = (s32)(depth0_shifted << 0x10) >> 0xE;
        ((S_8080DAB8_1 *)primitive)->unk_00 = (s32)((((S_8080DAB8_1 *)primitive)->unk_00 & tag_mask) | (((S_8080DAB8_5 *)((u8 *)((u32)ot_slot + (u32)*render_root)))->unk_B0 & addr_mask));
        ot_entry = (void *)((u32)ot_slot + (u32)*render_root);
        packet_addr = primitive & addr_mask;
        ot_entry->unk_B0 = (s32)((ot_entry->unk_B0 & tag_mask) | packet_addr);
        *draw_mode = (s32)((*draw_mode & tag_mask) | (((S_8080DAB8_5 *)((u8 *)((u32)ot_slot + (u32)*render_root)))->unk_B0 & addr_mask));
        ot_slot = ot_slot + (u8 *)*render_root;
        packet_addr = (u32)draw_mode & addr_mask;
        ((S_8080DAB8_4 *)((u8 *)ot_slot))->unk_B0 = (s32)((((S_8080DAB8_4 *)((u8 *)ot_slot))->unk_B0 & tag_mask) | packet_addr);
        next_record = ((S_8080DAB8_2 *)((u8 *)record - 0x8))->unk_00;
        record = next_record + 0x20;
    } while (next_record != 0);
    ASM_KEEP_NV(next_record);   /* MATCH pin: retail register colouring depends on it */
    return 0;
}
