#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800CCA14_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x1];
    s8 unk_27;
} S_800CCA14_0;   /* temp_v0 in func_800CCA14 */

typedef struct S_800CCA14_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CCA14_1;   /* count_base in func_800CCA14 */

typedef struct S_800CCA14_2 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    s8 unk_26;
    s8 unk_27;
} S_800CCA14_2;   /* temp_v0_2 in func_800CCA14 */



void *func_8003FE78();      /* extern */
s32 func_8009B390();                   /* extern */
M2C_UNK func_8009CE1C(); /* extern */
M2C_UNK func_800CC5F0(); /* extern */
M2C_UNK func_800CC88C();     /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_800CC370;
extern M2C_UNK D_800CC9BC;
extern Rec_D_800E3D7C *D_800E3D7C;
extern u8 D_800E5908;
extern M2C_UNK D_8014A000;

/* Creates a five-part effect at the given position and applies its target effect. */
void func_800CCA14(u16 x, u16 y, u16 z) {
    s32 direction;
    s32 first_base_angle;
    s32 first_angle;
    s32 base_angle;
    s32 angle;
    s32 target;
    s32 part_index;
    u16 part_x;
    u16 part_y;
    u16 part_z;
    u8 *count_base;
    S_800CCA14_0 *effect;
    S_800CCA14_2 *part;

    effect = func_8003FE78(0, (D_800E5908 * 0xC8) + (u8 *)&D_8014A000, 0xA);
    effect->unk_10 = &D_800CC9BC;
    effect->unk_20 = x;
    effect->unk_22 = y;
    effect->unk_24 = z;
    effect->unk_27 = 8;
    count_base = (u8 *)&D_80083460;
    ((S_800CCA14_1 *)count_base)->unk_0A = (u16) (((S_800CCA14_1 *)count_base)->unk_0A + 1);
    part_index = 3;
    do {
        part = func_8003FE78(0, (((D_800E5908 * 5) + part_index) * 0x28) + ((u8 *)&D_8014A000 + 0x28), 0xA);
        part->unk_10 = &D_800CC370;
        part_x = (u16) effect->unk_20;
        direction = part_index * 2;
        part->unk_20 = part_x;
        part_y = (u16) effect->unk_22;
        part_index -= 1;
        part->unk_22 = part_y;
        part_z = (u16) effect->unk_24;
        part->unk_27 = 8;
        part->unk_26 = direction;
        part->unk_24 = part_z;
    } while (part_index >= 0);
    base_angle = (part_index << 0x1A) >> 0x10;
    first_base_angle = base_angle;
    ASM_KEEP(first_base_angle);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    part_index = 3;
    func_800CC88C((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, first_base_angle, 0);
    func_800CC88C((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, base_angle, 1);
    do {
        angle = (part_index << 0x1A) >> 0x10;
        first_angle = angle;
        ASM_KEEP(first_angle);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        part_index -= 1;
        func_800CC5F0((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, first_angle, 0, 0);
        func_800CC5F0((s16) effect->unk_20, (s16) effect->unk_22, (s16) effect->unk_24, angle, 1, 1);
    } while (part_index >= 0);
    target = func_8009B390(effect->unk_20, effect->unk_22, (s16) effect->unk_24);
    if (target != 0) {
        func_8009CE1C(target, 0xC, D_800E3D7C->unk_10.at01_u8.v, 9, 0x400, 0, 3);
    }
}
