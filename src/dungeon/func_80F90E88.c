#include "common.h"
#include "shared/game_work.h"
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





s32 func_80065420();
s32 func_80066460();
M2C_UNK func_80066640();
M2C_UNK func_80066708();
M2C_UNK func_80067F20();

struct PackedPair {
    s32 first;
    s32 second;
} __attribute__((packed));
typedef struct PackedPair PackedPair;

typedef struct {
    M2C_UNK *input;
    M2C_UNK *output;
    s16 rot_x;
    s16 rot_y;
    s16 rot_z;
    s16 pad36;
    PackedPair translation;
    s16 count;
    s16 flags;
    s16 pad44;
    s16 pad46;
} TransformRec;

typedef struct {
    s16 x;
    s16 y;
    s32 z;
} ScreenPoint;

typedef struct {
    s16 value;
    s16 zero2;
    s16 zero4;
    s16 pad6;
} WorkCell;




typedef struct S_80F90E88_7 {
    u8 pad_00[0x8D0];
    s32 * unk_8D0;
} S_80F90E88_7;   /* gameWork.unk_000 in func_80F90E88 */


#define getaddr(t) ((t) & address_mask)
#define setaddr(t, a) ((t) = ((t) & 0xFF000000) | ((a) & address_mask))

/* Draws paired gradient quads from the projected bounds of each linked object. */
s32 func_80F90E88(void *object) {
    WorkCell work[2];
    TransformRec transform_rec;
    void *transform;
    ScreenPoint screen;
    void *model;
    s32 *z_ptr;
    WorkCell *points;
    s32 max_xy;
    s32 min_xy;
    s32 address_mask;
    s32 *quad;
    s32 *draw_mode;
    s32 next_object;
    s32 bottom_y;
    s32 color;
    s32 side;
    u32 depth;
    WorkCell *endpoint;
    s32 half_width;
    s32 left_offset;
    u16 view_angle;
    s16 coord;
    u32 coord_bits;
    s32 hi_mask;
    s32 ot_offset;
    s32 mode_ot_offset;
    u16 center_x;
    s32 upper;
    s32 merged;
    GameWork *gw;
    s32 link;
    register s32 tag ASM_REG("$2");   /* UNRESOLVED C shape (pin): local-alloc gives the OT-link block's temps $v0 first; the source shape that leaves $v0 to the tag chain has not been found */

    points = work;
    z_ptr = &screen.z;
    address_mask = 0x00FFFFFF;
    hi_mask = 0xFFFF0000;
    gw = &gameWork;
draw_object:
    screen.z = 8;
    half_width = (u16) screen.z;
    side = 1;
    model = object;
    left_offset = -half_width;
    endpoint = &points[1];
loop_0:
    endpoint->value = half_width;
    if (side != 0) {
        endpoint->value = left_offset;
        endpoint->zero4 = 0;
    } else {
        endpoint->zero4 = 0;
    }
    endpoint->zero2 = 0;
    side--;
    endpoint--;
    if (side >= 0) goto loop_0;
    transform = &transform_rec;
    view_angle = gw->view.viewAngle;
    transform_rec.rot_y = 0;
    transform_rec.rot_x = 0;
    transform_rec.input = (M2C_UNK *) points;
    transform_rec.output = (M2C_UNK *) points;
    transform_rec.rot_z = -view_angle;
    transform_rec.translation = *(PackedPair *)((s8 *)model + 0xC);
    transform_rec.count = 2;
    transform_rec.flags = 0;
    func_800DBA90(transform);
    min_xy &= 0xFFFF;
    max_xy &= 0xFFFF;
    side = 1;
    min_xy |= 0x75300000;
    min_xy &= hi_mask;
    min_xy |= 0x7530;
    max_xy |= 0x8AD00000;
    max_xy &= hi_mask;
    max_xy |= 0x8AD0;
loop_1:
    depth = func_80065420(&points[side], &screen, z_ptr, z_ptr);
    depth -= 4;
    coord = screen.x;
    coord_bits = (u16) screen.x;
    if ((s16) max_xy < coord) {
        max_xy &= hi_mask;
        merged = coord_bits | max_xy;
        max_xy = merged;
    }
    if (coord < (s16) min_xy) {
        min_xy &= hi_mask;
        merged = coord_bits | min_xy;
        min_xy = merged;
    }
    coord = screen.y;
    coord_bits = (u16) screen.y;
    if ((max_xy >> 0x10) < coord) {
        upper = coord_bits << 0x10;
        max_xy &= 0xFFFF;
        max_xy |= upper;
    }
    if (coord < (min_xy >> 0x10)) {
        upper = coord_bits << 0x10;
        min_xy &= 0xFFFF;
        min_xy |= upper;
    }
    side--;
    if (side >= 0) goto loop_1;
    if (depth < 0x1E0U) {
        half_width = (u32) max_xy << 16;
        half_width >>= 16;
        half_width += (s16) min_xy;
        half_width >>= 1;
        screen.z = half_width;
        side = 1;
        bottom_y = max_xy >> 0x10;
        ot_offset = depth * 4;
        do {
            quad = ((S_80F90E88_7 *)gw->unk_000)->unk_8D0;
            ((S_80F90E88_7 *)gw->unk_000)->unk_8D0 = (s32 *) ((s8 *) quad + 0x24);
            if (side != 0) {
                color = ((S_80F90E88_0 *)((u8 *)model - 0x8))->unk_60;
                ((S_80F90E88_1 *)quad)->unk_1C = 0;
                ((S_80F90E88_1 *)quad)->unk_14 = 0;
                ((S_80F90E88_1 *)quad)->unk_0C = color;
                ((S_80F90E88_1 *)quad)->unk_04 = color;
                center_x = (u16) screen.z;
                ((S_80F90E88_1 *)quad)->unk_20 = max_xy;
                ((S_80F90E88_1 *)quad)->unk_18 = max_xy;
                ((S_80F90E88_1 *)quad)->unk_10 = center_x;
                ((S_80F90E88_1 *)quad)->unk_08.s = center_x;
            } else {
                ((S_80F90E88_1 *)quad)->unk_0C = 0;
                ((S_80F90E88_1 *)quad)->unk_04 = 0;
                color = ((S_80F90E88_0 *)((u8 *)model - 0x8))->unk_60;
                ((S_80F90E88_1 *)quad)->unk_1C = color;
                ((S_80F90E88_1 *)quad)->unk_14 = color;
                center_x = (u16) screen.z;
                ((S_80F90E88_1 *)quad)->unk_10 = (u16) min_xy;
                ((S_80F90E88_1 *)quad)->unk_08.u = min_xy;
                ((S_80F90E88_1 *)quad)->unk_20 = center_x;
                ((S_80F90E88_1 *)quad)->unk_18 = center_x;
            }
            func_80066708(quad);
            func_80066640(quad, 1);
            ((S_80F90E88_1 *)quad)->unk_1A = 0;
            ((S_80F90E88_1 *)quad)->unk_0A = 0;
            ((S_80F90E88_1 *)quad)->unk_22 = bottom_y;
            ((S_80F90E88_1 *)quad)->unk_12 = bottom_y;
            link = (s32) gw->unk_000;
            tag = ((S_80F90E88_1 *)quad)->unk_00;
            link = ((S_80F90E88_2 *)(ot_offset + link))->unk_B0;
            tag &= 0xFF000000;
            link &= address_mask;
            tag |= link;
            ((S_80F90E88_1 *)quad)->unk_00 = tag;
            side--;
            tag = ((S_80F90E88_2 *)(ot_offset + (s32)gw->unk_000))->unk_B0;
            tag &= 0xFF000000;
            tag |= (s32) quad & address_mask;
            ((S_80F90E88_2 *)(ot_offset + (s32)gw->unk_000))->unk_B0 = tag;
        } while (side >= 0);
        draw_mode = ((S_80F90E88_7 *)gw->unk_000)->unk_8D0;
        ((S_80F90E88_7 *)gw->unk_000)->unk_8D0 = (s32 *) ((s8 *) draw_mode + 0xC);
        func_80067F20(draw_mode, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
        mode_ot_offset = depth * 4;
        link = getaddr(((S_80F90E88_2 *)(mode_ot_offset + (s32)gw->unk_000))->unk_B0);
        setaddr(*draw_mode, link);
        setaddr(((S_80F90E88_2 *)(mode_ot_offset + (s32)gw->unk_000))->unk_B0, (s32) draw_mode);
    }
    next_object = ((S_80F90E88_0 *)((u8 *)object - 0x8))->unk_00;
    if (next_object != 0) {
        object = (void *) (next_object + 0x20);
        goto draw_object;
    }
    return 0;
}
