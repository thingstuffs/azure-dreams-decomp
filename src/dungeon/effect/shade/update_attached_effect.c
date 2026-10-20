#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800D4954_0_pre {
    u16 unk_00;
} S_800D4954_0_pre;   /* the 0x2 bytes before arg0 in update_attached_effect, addressed as arg0[-1] */

typedef struct S_800D4954_0 {
    u8 pad_00[0x5A];
    u16 unk_5A;
    u8 pad_5C[0x2C];
    void * unk_88;
} S_800D4954_0;   /* arg0 in update_attached_effect */

typedef struct S_800D4954_1_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800D4954_1_pre;

typedef struct S_800D4954_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D4954_2;   /* arg1 in update_attached_effect */



typedef struct S_800D4954_4 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_800D4954_4;   /* arg2 in update_attached_effect */

typedef struct S_800D4954_5 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800D4954_5;


extern s32 get_entity_effect_value(void *, s32);

/* Updates an attached effect's position, color, growth, and removal flags. */
void update_attached_effect(void *effect, S_800D4954_2 *position, S_800D4954_4 *appearance) {
    u16 next_scale;
    void *source;
    S_800D4954_5 *source_header;
    MovingPosition *source_position;

    source = ((S_800D4954_0 *)effect)->unk_88;
    source_position = ((S_800D4954_1_pre *)source)[-1].unk_00;
    source_header = source - 0x20;
    position->unk_02 = source_position->unk_02;
    position->unk_06 = source_position->unk_06;
    position->unk_0A = source_position->unk_0A - 0x32;
    appearance->unk_0E = 0x28;
    appearance->unk_0D = 0x28;
    appearance->unk_0C = 0x28;
    appearance->unk_1A = appearance->unk_1A + 0x190;
    if (((S_800D4954_0 *)effect)->unk_5A & 1) {
        appearance->unk_0C = 0x64;
    }
    if (((S_800D4954_0 *)effect)->unk_5A & 2) {
        appearance->unk_0D = 0x64;
    }
    if (((S_800D4954_0 *)effect)->unk_5A & 4) {
        appearance->unk_0E = 0x64;
    }
    if (appearance->unk_1C < 0x1800U) {
        next_scale = appearance->unk_1E + 0x190;
        appearance->unk_1E = next_scale;
        appearance->unk_1C = next_scale;
    }
    if ((get_entity_effect_value(source, 0x1D) << 0x10) == 0) {
        ((S_800D4954_0_pre *)effect)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
    if (source_header->unk_1E & 0x8000) {
        ((S_800D4954_0_pre *)effect)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
