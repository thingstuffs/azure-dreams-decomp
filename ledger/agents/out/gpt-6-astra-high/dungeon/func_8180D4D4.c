#include "common.h"
#include "m2c_compat.h"

typedef struct S_800264D4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800264D4_0;   /* temp_v0 in func_800264D4 */

typedef struct S_800264D4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800264D4_1;   /* arg0 in func_800264D4 */

typedef struct S_800264D4_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800264D4_2;   /* temp_a1 in func_800264D4 */

typedef struct S_800264D4_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800264D4_3;   /* temp_a0 in func_800264D4 */

typedef struct S_800264D4_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x42];
    s16 unk_66;
    u8 pad_68[0x6];
    s16 unk_6E;
    u8 pad_70[0x2];
    s16 unk_72;
} S_800264D4_4;   /* temp_a0_2 in func_800264D4 */

typedef struct S_800264D4_5 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
} S_800264D4_5;   /* var_v1 in func_800264D4 */


typedef struct {
    u8 unk00[8];
    void *addr;
    u8 unk0c[4];
    s16 unk10;
    s16 unk12;
    u16 flags;
    u8 unk16[6];
    s16 unk1c;
    s16 unk1e;
} NodeA;

extern u8 D_80083498[];
extern u8 D_80028808;
extern u8 D_800260DC[];
extern u8 D_800CEF54[];

void *func_8003FD64(s32, void *);
M2C_UNK func_8004491C(void *, void *);

/* Creates six linked objects at the source position and initializes their position histories. */
void *func_800264D4(S_800264D4_1 *source_pos, s32 effect_value, s16 sprite_id, s16 effect_option) {
    s32 object_index;
    s32 sprite_index;
    s32 fixed_x;
    s32 fixed_y;
    s32 fixed_z;
    s32 history_index;
    u16 pos_x;
    u16 pos_y;
    u16 pos_z;
    register u16 sprite_flags ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    S_800264D4_3 *sprite;
    S_800264D4_4 *effect_state;
    S_800264D4_2 *position;
    void *object;
    void *previous_object;
    void *history_entry;
    u8 *page_base;

    previous_object = NULL;
    object_index = 0;
    page_base = &D_800260DC[0];
    sprite_index = (sprite_id << 0x10) >> 16;
create_object:
    object = func_8003FD64(0x12, D_80083498);
    if (object != NULL) {
        ((S_800264D4_0 *)object)->unk_10 = page_base;
        func_8004491C(object, &D_800CEF54);
        position = ((S_800264D4_0 *)object)->unk_08;
        pos_x = source_pos->unk_02;
        position->unk_00.at02.v = pos_x;
        position->unk_0E = pos_x;
        pos_y = source_pos->unk_06;
        position->unk_04.at02.v = pos_y;
        position->unk_12 = pos_y;
        pos_z = source_pos->unk_0A;
        position->unk_08.at02.v = pos_z;
        position->unk_16 = pos_z;
        sprite = ((S_800264D4_0 *)object)->unk_0C;
        sprite_flags = sprite->unk_14;
        sprite->unk_08 = (void *) ((sprite_index * 0xC) + &D_80028808);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_10 = 0x60;
        sprite->unk_14 = (u16) (sprite_flags | 0xC);
        effect_state = object + 0x20;
        effect_state->unk_04 = effect_value;
        ((S_800264D4_0 *)object)->unk_20 = source_pos;
        effect_state->unk_66 = 0x20;
        effect_state->unk_6E = object_index;
        fixed_x = position->unk_00.at00.v;
        effect_state->unk_18 = fixed_x;
        effect_state->unk_0C = fixed_x;
        fixed_y = position->unk_04.at00.v;
        history_index = 0;
        effect_state->unk_1C = fixed_y;
        effect_state->unk_10 = fixed_y;
        history_entry = effect_state;
        fixed_z = position->unk_08.at00.v;
        effect_state->unk_20 = fixed_z;
        effect_state->unk_14 = fixed_z;
        do {
            ((S_800264D4_5 *)history_entry)->unk_24 = (u16) position->unk_00.at02.v;
            ((S_800264D4_5 *)history_entry)->unk_26 = (u16) position->unk_04.at02.v;
            history_index += 1;
            ((S_800264D4_5 *)history_entry)->unk_28 = (u16) position->unk_08.at02.v;
            history_entry += 8;
        } while (history_index < 8);
        effect_state->unk_08 = previous_object;
        previous_object = object;
        object_index += 1;
        effect_state->unk_72 = effect_option;
        if (object_index >= 6) {

        } else {
            goto create_object;
        }
    }
    return object;
}
