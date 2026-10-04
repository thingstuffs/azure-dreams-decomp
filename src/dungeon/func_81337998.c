#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_8016E998_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x58];
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    s16 unk_86;
    s16 unk_88;
    s16 unk_8A;
} S_8016E998_0;   /* temp_s0 in func_8016E998 */

typedef struct S_8016E998_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s8 unk_20;
} S_8016E998_1;   /* temp_v0 in func_8016E998 */

typedef struct S_8016E998_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_8016E998_2;   /* temp_a1 in func_8016E998 */

typedef struct S_8016E998_3 {
    s32 unk_00;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_8016E998_3;   /* temp_v1 in func_8016E998 */


typedef struct S_8016E998_5 {
    u8 pad_00[0xC];
    s8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8016E998_5;   /* temp_a1_3 in func_8016E998 */


void *func_8003FC64();                       /* extern */
s32 func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                        /* extern */
extern M2C_UNK D_8016E4E8;
extern void *D_80175D78;

/* Creates sixteen radial effect segments around the supplied position. */
void func_8016E998(EntityRec *origin) {
    s32 origin_z;
    s32 start_angle;
    s32 end_x;
    s32 start_x;
    s32 end_z;
    s16 unit_scale;
    s32 initial_count;
    s8 color_level = 0;
    s32 end_angle;
    s32 segment_index;
    M2C_UNK *effect_handler;
    void **effect_slot;
    S_8016E998_5 *appearance;
    S_8016E998_0 *effect_data;
    void *effect;
    S_8016E998_3 *position;

    segment_index = 0;
    effect_handler = &D_8016E4E8;
    effect_slot = &D_80175D78;
    end_angle = 0x100;
    do {
        effect = func_8003FC64(0x12);
        if (effect != NULL) {
            effect_data = effect + 0x20;
            initial_count = 0x32;
            effect_data->unk_18 = (s16) initial_count;
            effect_data->unk_1A = (s16) initial_count;
            ((S_8016E998_1 *)effect)->unk_10 = effect_handler;
            func_8004491C(effect, func_80045340);
            appearance = ((S_8016E998_1 *)effect)->unk_0C;
            ((S_8016E998_2 *)appearance)->unk_14 |= 0xC;
            ((S_8016E998_2 *)appearance)->unk_10 = 0x20;
            ((S_8016E998_2 *)appearance)->unk_14 |= 0x80;
            position = ((S_8016E998_1 *)effect)->unk_08;
            position->unk_00 = (s32) origin->x.v;
            position->unk_04.at00.v = (s32) origin->y.v;
            origin_z = origin->z.v;
            position->unk_04.at02.v = (u16) (position->unk_04.at02.v - 0x440);
            position->unk_08 = origin_z;
            effect_data->unk_7E = -0x40;
            effect_data->unk_78 = -0x40;
            effect_data->unk_8A = 0;
            effect_data->unk_84 = 0;
            start_angle = segment_index << 8;
            end_x = (s32) (func_80064584(end_angle) << 5) >> 0xC;
            effect_data->unk_80 = (s16) end_x;
            effect_data->unk_74 = (s16) end_x;
            start_x = (s32) (func_80064584(start_angle) << 5) >> 0xC;
            effect_data->unk_86 = (s16) start_x;
            effect_data->unk_7A = (s16) start_x;
            end_z = (s32) (func_800644B8(end_angle) << 5) >> 0xC;
            effect_data->unk_82 = (s16) end_z;
            effect_data->unk_76 = (s16) end_z;
            unit_scale = (s32) (func_800644B8(start_angle) << 5) >> 0xC;
            effect_data->unk_88 = (s16) unit_scale;
            effect_data->unk_7C = (s16) unit_scale;
            appearance = ((S_8016E998_1 *)effect)->unk_0C;
            color_level = 0x40;
            appearance->unk_0C = color_level;
            appearance->unk_1E = 0x1000;
            appearance->unk_1C = 0x1000;
            appearance->unk_0D = color_level;
            appearance->unk_0E = color_level;
            ((S_8016E998_1 *)effect)->unk_20 = appearance->unk_0C;
            effect_data->unk_01 = appearance->unk_0D;
            effect_data->unk_02 = appearance->unk_0E;
            *effect_slot = effect;
        }
        effect_slot = (void **)((s8 *)((void **)((s8 *)effect_slot + 4)));
        segment_index += 1;
        end_angle += 0x100;
    } while (segment_index < 0x10);
}

/* MECHANISM: the flag word is two compound ORs (cse keeps them apart and
   post-reload CSE turns the re-read into `move`); effect->unk_20 re-reads the
   just-stored colour byte; one pointer variable carries both effect->unk_0C
   loads (two sets -> global pseudo -> $a1); color_level is a user variable
   declared with an initialiser, so loop.c does not hoist the 0x40 set. */
