#include "common.h"
#include "m2c_compat.h"

extern s32 D_800814A0[3];
extern s32 D_800DEDB0[3];
M2C_UNK func_80024600();
s32 func_8003DB94();
s32 func_800644B8();
s32 func_80064584();
s32 rand();

typedef struct S_80024A34_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80024A34_0;   /* temp_a0 in func_80024A34 */

typedef struct S_80024A34_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024A34_1;   /* arg2 in func_80024A34 */

typedef struct S_80024A34_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024A34_2;   /* arg1 in func_80024A34 */

/* Initialize the object's visual state and apply a random spherical position offset. */
void func_80024A34(void *object, S_80024A34_2 *position, S_80024A34_1 *visual) {
    s16 azimuth;
    s16 polar_angle;
    s32 radial_x;
    s32 radial_y;
    s32 rotation_rand;
    s32 polar_rand;
    s32 azimuth_rand;
    s32 node_index;
    s32 azimuth_biased;
    s32 rotation_quotient;
    s32 polar_quotient;
    s32 *flags_base;
    void **node_slot;
    S_80024A34_0 *node;

    node_index = 0;
    flags_base = (s32 *)(u32)0x80080000;
    node_slot = (void **)object;
    do {
        if ((node = node_slot[5]) != NULL) {
            u16 node_flags;
            s32 global_flags;
            node_flags = node->unk_1E;
            global_flags = flags_base[0x528];
            node_flags = (u16)(node_flags | 0x8000);
            global_flags = global_flags | 0x8000;
            node->unk_1E = node_flags;
            flags_base[0x528] = global_flags;
        }
        node_index += 1;
        node_slot += 1;
    } while (node_index < 3);
    func_8003DB94(visual, D_800DEDB0, 0, flags_base);
    visual->unk_0E = 0xC0;
    visual->unk_0D = 0xC0;
    visual->unk_0C = 0xC0;
    visual->unk_1E = 0x800;
    visual->unk_1C = 0x800;
    visual->unk_14 = (u16) (visual->unk_14 | 0xC);
    visual->unk_10 = (u16) (visual->unk_10 | 0x20);
    rotation_quotient = rand();
    rotation_rand = rotation_quotient;
    if (rotation_rand < 0) {
        rotation_quotient = (s32) (rotation_rand + 0xFFF);
    }
    rotation_quotient >>= 0xC;
    visual->unk_1A = (s16) (rotation_rand - (rotation_quotient << 0xC));
    polar_rand = rand();
    polar_quotient = polar_rand;
    if (polar_rand < 0) {
        polar_quotient = polar_rand + 0xFFF;
    }
    polar_quotient >>= 0xC;
    polar_angle = polar_rand - (polar_quotient << 0xC);
    azimuth_rand = rand();
    azimuth_biased = azimuth_rand;
    if (azimuth_rand < 0) {
        azimuth_biased = azimuth_rand + 0xFFF;
    }
    azimuth = azimuth_rand - ((azimuth_biased >> 0xC) << 0xC);
    radial_x = func_800644B8(polar_angle);
    position->unk_00 = (s32) (position->unk_00 + ((radial_x >> 4) * (func_800644B8(azimuth) >> 4) * 0x10));
    radial_y = func_800644B8(polar_angle);
    position->unk_04 = (s32) (position->unk_04 + ((radial_y >> 4) * (func_80064584(azimuth) >> 4) * 0x10));
    position->unk_08 = (s32) (position->unk_08 + ((func_80064584(polar_angle) >> 4) << 0xC));
    func_80024600(object, position);
}
