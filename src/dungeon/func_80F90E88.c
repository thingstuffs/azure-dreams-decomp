#include "common.h"
#include "m2c_compat.h"

typedef struct S_80F90E88_0 {
    s32 unk_00;
    u8 pad_04[0x4];
    void * unk_08;
    u8 pad_0C[0x54];
    s32 unk_60;
    u8 pad_64[0x6C];
    u16 unk_D0;
} S_80F90E88_0;   /* global_base in func_80F90E88; pointer addresses record offset 0x8 */

typedef struct S_80F90E88_1 {
    s32 unk_00;
    s32 unk_04;
    union { u16 s; s16 u; } unk_08;   /* accessed as both */
    s16 unk_0A;
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    s32 unk_14;
    s16 unk_18;
    s16 unk_1A;
    s32 unk_1C;
    s16 unk_20;
    s16 unk_22;
} S_80F90E88_1;   /* temp_s0 in func_80F90E88 */

typedef struct S_80F90E88_2 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80F90E88_2;   /* temp_s4 + link_global in func_80F90E88 */

typedef struct S_80F90E88_3 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80F90E88_3;   /* var_a0 in func_80F90E88 */

typedef struct S_80F90E88_4 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80F90E88_4;   /* final_global in func_80F90E88 */

typedef struct S_80F90E88_5 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80F90E88_5;   /* temp_a0_3 in func_80F90E88 */


struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern struct S_8003E2D8 D_80083160_init __asm__("D_80083160");
extern struct S_8003E2D8 D_80083160_alloc __asm__("D_80083160");
extern struct S_8003E2D8 D_80083160_link __asm__("D_80083160");
extern struct S_8003E2D8 D_80083160_final __asm__("D_80083160");
s32 func_80065420();
s32 func_80066460();
M2C_UNK func_80066640();
M2C_UNK func_80066708();
M2C_UNK func_80067F20();

typedef struct {
    M2C_UNK *p28;
    M2C_UNK *p2C;
    s16 p30;
    s16 p32;
    s16 p34;
    s16 pad36;
    M2C_UNK p38;
    M2C_UNK p3C;
    s16 p40;
    s16 p42;
    s16 pad44;
    s16 pad46;
    s16 p48;
    s16 p4A;
    s32 p4C;
    void *volatile p50;
    s32 *p54;
    s8 *volatile p58;
} LocalRecord;

typedef struct {
    s8 work[16];
    LocalRecord record;
} LocalFrame;

typedef struct {
    s16 value;
    s16 zero2;
    s16 zero4;
    s16 pad6;
} WorkCell;

struct PackedPair {
    s32 first;
    s32 second;
} __attribute__((packed));
typedef struct PackedPair PackedPair;

struct PackedWord {
    s32 value;
} __attribute__((packed));
typedef struct PackedWord PackedWord;

typedef struct S_80F90E88_6 {
    void * unk_00;
} S_80F90E88_6;   /* global_base in func_80F90E88 */

typedef struct S_80F90E88_7 {
    u8 pad_00[0x8D0];
    s32 * unk_8D0;
} S_80F90E88_7;   /* ((S_80F90E88_6 *)global_base)->unk_00 in func_80F90E88 */


/* Draws paired gradient quads from the projected bounds of each linked object. */
s32 func_80F90E88(void *object) {
    LocalFrame frame;
    register s32 max_xy ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 min_xy ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 address_mask ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 tag_mask;
    s32 *quad;
    s32 *draw_mode;
    s32 next_object;
    s32 mode_ot_offset;
    register s32 ot_offset ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 bottom_y;
    s32 right_color;
    s32 left_color;
    register s32 quad_ot_slot ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 side;
    register s8 *base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register u32 depth ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register S_80F90E88_5 *mode_ot_slot ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register WorkCell *endpoint ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 half_width;
    s32 left_offset;
    void *transform;
    u16 view_angle;
    s32 position_xy;
    s32 position_z;
    register s8 *stack_base ASM_REG("$29");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 upper_mask ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 coord;
    register u32 coord_bits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 point_addr ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *screen_out;
    s32 *depth_out;
    s32 bound_test;
    u32 upper_coord;
    register s32 right_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 left_x;
    s32 midpoint_x;
    u16 center_x;
    s32 mode_tag_mask;
    s32 quad_ot_link;
    s32 quad_tag;
    register s32 mode_ot_link ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 mode_tag;

#define point_storage frame.work[0]
#define transform_input frame.record.p28
#define transform_output frame.record.p2C
#define rotation_x frame.record.p30
#define rotation_y frame.record.p32
#define rotation_z frame.record.p34
#define translation_xy frame.record.p38
#define translation_z frame.record.p3C
#define point_count frame.record.p40
#define transform_flags frame.record.p42
#define record_pad44 frame.record.pad44
#define record_pad46 frame.record.pad46
#define screen_x frame.record.p48
#define screen_y frame.record.p4A
#define projection_scratch frame.record.p4C
#define saved_object frame.record.p50
#define scratch_ptr frame.record.p54
#define points frame.record.p58

    base = &point_storage;
    points = base;
    base = (s8 *) &projection_scratch;
    address_mask = 0x00FFFFFF;
    scratch_ptr = (s32 *) base;
draw_object:
    base = (s8 *) object;
    projection_scratch = 8;
    half_width = (u16) projection_scratch;
    side = 1;
    saved_object = base;
    base = points;
    ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    left_offset = 0 - half_width;
    ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    endpoint = (WorkCell *) (base + 8);
    do {
        endpoint->value = half_width;
        if (side != 0) {
            endpoint->value = left_offset;
            endpoint->zero4 = 0;
        } else {
            endpoint->zero4 = 0;
        }
        endpoint->zero2 = 0;
        side -= 1;
        endpoint -= 1;
    } while (side >= 0);
    transform = &transform_input;
    ASM_KEEP_NV(transform);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    min_xy &= 0xFFFF;
    max_xy &= 0xFFFF;
    base = (s8 *) &D_80083160_init;
    ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    view_angle = ((S_80F90E88_0 *)((u8 *)base - 0x8))->unk_D0;
    base = points;
    ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    side = 1;
    rotation_y = 0;
    rotation_x = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    transform_input = (M2C_UNK *) base;
    transform_output = (M2C_UNK *) base;
    base = (s8 *) saved_object;
    rotation_z = 0 - view_angle;
    position_xy = ((PackedWord *) (base + 0xC))->value;
    position_z = ((PackedWord *) (base + 0x10))->value;
#ifdef NON_MATCHING
    stack_base = (s8 *) &translation_xy - 0x38;
#else
#endif
    ((PackedWord *) (stack_base + 0x38))->value = position_xy;
    ((PackedWord *) (stack_base + 0x3C))->value = position_z;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    point_count = 2;
    transform_flags = 0;
    func_800DBA90(transform);
    min_xy |= 0x75300000;
    upper_mask = 0xFFFF0000;
    min_xy &= upper_mask;
    min_xy |= 0x7530;
    max_xy |= 0x8AD00000;
    max_xy &= upper_mask;
    max_xy |= 0x8AD0;
    do {
        point_addr = side * 8;
        screen_out = &screen_x;
        base = points;
        depth_out = scratch_ptr;
        point_addr = (s32) base + point_addr;
        depth = func_80065420(point_addr, screen_out, depth_out, depth_out) - 4;
        ASM_KEEP_NV(depth);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        bound_test = (s16) max_xy;
        coord = screen_x;
        coord_bits = (u16) screen_x;
        bound_test = bound_test < coord;
        if (bound_test) {
            upper_mask = 0xFFFF0000;
            max_xy &= upper_mask;
            max_xy = coord_bits | max_xy;
        }
        bound_test = (s16) min_xy;
        bound_test = coord < bound_test;
        if (bound_test) {
            upper_mask = 0xFFFF0000;
            min_xy &= upper_mask;
            min_xy = coord_bits | min_xy;
        }
        bound_test = max_xy >> 0x10;
        coord = screen_y;
        coord_bits = (u16) screen_y;
        bound_test = bound_test < coord;
        if (bound_test) {
            upper_coord = coord_bits << 0x10;
            max_xy &= 0xFFFF;
            max_xy |= upper_coord;
        }
        bound_test = min_xy >> 0x10;
        bound_test = coord < bound_test;
        if (bound_test) {
            upper_coord = coord_bits << 0x10;
            min_xy &= 0xFFFF;
            min_xy |= upper_coord;
        }
        side -= 1;
    } while (side >= 0);
    if (depth < 0x1E0U) {
        right_x = (s16) max_xy;
        left_x = (s16) min_xy;
        midpoint_x = right_x + left_x;
        midpoint_x >>= 1;
        projection_scratch = midpoint_x;
        side = 1;
        bottom_y = max_xy >> 0x10;
        ASM_USE(bottom_y);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ot_offset = depth * 4;
        tag_mask = 0xFF000000;
draw_side:
        base = (s8 *) &D_80083160_alloc;
        ASM_KEEP_DEP_NV(base, tag_mask);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        quad = ((S_80F90E88_7 *)(((S_80F90E88_6 *)base)->unk_00))->unk_8D0;
        ((S_80F90E88_7 *)(((S_80F90E88_6 *)base)->unk_00))->unk_8D0 = (s32 *) ((s8 *) quad + 0x24);
        if (side != 0) {
            base = (s8 *) saved_object;
            right_color = ((S_80F90E88_0 *)((u8 *)base - 0x8))->unk_60;
            ((S_80F90E88_1 *)quad)->unk_1C = 0;
            ((S_80F90E88_1 *)quad)->unk_14 = 0;
            ((S_80F90E88_1 *)quad)->unk_0C = right_color;
            ((S_80F90E88_1 *)quad)->unk_04 = right_color;
            center_x = (u16) projection_scratch;
            ((S_80F90E88_1 *)quad)->unk_20 = max_xy;
            ((S_80F90E88_1 *)quad)->unk_18 = max_xy;
            ((S_80F90E88_1 *)quad)->unk_10 = center_x;
            ((S_80F90E88_1 *)quad)->unk_08.s = center_x;
            goto setup_quad;
        }
        {
            register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            hard_zero = 0;
#else
#endif
            ((S_80F90E88_1 *)quad)->unk_0C = hard_zero;
            ((S_80F90E88_1 *)quad)->unk_04 = hard_zero;
        }
        base = (s8 *) saved_object;
        left_color = ((S_80F90E88_0 *)((u8 *)base - 0x8))->unk_60;
        ((S_80F90E88_1 *)quad)->unk_1C = left_color;
        ((S_80F90E88_1 *)quad)->unk_14 = left_color;
        center_x = (u16) projection_scratch;
        ((S_80F90E88_1 *)quad)->unk_10 = (u16) min_xy;
        ((S_80F90E88_1 *)quad)->unk_08.u = min_xy;
        ((S_80F90E88_1 *)quad)->unk_20 = center_x;
        ((S_80F90E88_1 *)quad)->unk_18 = center_x;
setup_quad:
        func_80066708(quad);
        func_80066640(quad, 1);
        ((S_80F90E88_1 *)quad)->unk_1A = 0;
        ((S_80F90E88_1 *)quad)->unk_0A = 0;
        ((S_80F90E88_1 *)quad)->unk_22 = (s16) bottom_y;
        ((S_80F90E88_1 *)quad)->unk_12 = (s16) bottom_y;
        base = (s8 *) &D_80083160_link;
        ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        quad_ot_link = (s32) ((S_80F90E88_0 *)((u8 *)base - 0x8))->unk_08;
        quad_tag = ((S_80F90E88_1 *)quad)->unk_00;
        quad_ot_link = ((S_80F90E88_2 *)(ot_offset + quad_ot_link))->unk_B0;
        quad_tag &= tag_mask;
        quad_ot_link &= address_mask;
        quad_tag |= quad_ot_link;
        ((S_80F90E88_1 *)quad)->unk_00 = quad_tag;
        side -= 1;
        quad_ot_slot = ot_offset + (s32) ((S_80F90E88_0 *)((u8 *)base - 0x8))->unk_08;
        ((S_80F90E88_3 *)quad_ot_slot)->unk_B0 = (s32) ((((S_80F90E88_3 *)quad_ot_slot)->unk_B0 & tag_mask) | ((s32) quad & address_mask));
        if (side < 0) {
            draw_mode = ((S_80F90E88_7 *)(((S_80F90E88_6 *)base)->unk_00))->unk_8D0;
            ((S_80F90E88_7 *)(((S_80F90E88_6 *)base)->unk_00))->unk_8D0 = (s32 *) ((s8 *) draw_mode + 0xC);
            func_80067F20(draw_mode, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            base = (s8 *) &D_80083160_final;
            ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            mode_ot_offset = depth * 4;
            mode_tag_mask = 0xFF000000;
            mode_ot_link = (s32) ((S_80F90E88_0 *)((u8 *)base - 0x8))->unk_08;
            mode_tag = *draw_mode;
            mode_ot_link = mode_ot_offset + mode_ot_link;
            mode_ot_link = ((S_80F90E88_4 *)mode_ot_link)->unk_B0;
            mode_tag &= mode_tag_mask;
            mode_ot_link &= address_mask;
            mode_tag |= mode_ot_link;
            *draw_mode = mode_tag;
            mode_ot_link = (s32) ((S_80F90E88_0 *)((u8 *)base - 0x8))->unk_08;
            mode_ot_slot = (void *) (mode_ot_offset + mode_ot_link);
            mode_ot_slot->unk_B0 = (s32) ((mode_ot_slot->unk_B0 & mode_tag_mask) | ((s32) draw_mode & address_mask));
            goto advance_object;
        }
        goto draw_side;
    }
advance_object:
    base = (s8 *) object;
    ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    next_object = ((S_80F90E88_0 *)((u8 *)base - 0x8))->unk_00;
    if (next_object == 0) {
        goto return_zero;
    }
    object = (void *) (next_object + 0x20);
    goto draw_object;
return_zero:
    {
        register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        hard_zero = 0;
#else
#endif
        result = hard_zero;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        return result;
    }
}
