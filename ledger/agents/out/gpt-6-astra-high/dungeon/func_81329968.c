#include "common.h"
#include "m2c_compat.h"

extern s32 D_80174CD8[3];
extern u8 D_80082E80[];
typedef struct {
    u8 data[24];
} Config24;
extern u8 D_8016A87C[];
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A2B04(s32, u8, u8);
extern void func_8009A21C(u8, u8, s32);

typedef struct S_80171168_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_80171168_0;   /* *D_80174CD8 in func_80171168 */

typedef struct S_80171168_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80171168_1;   /* temp_s0 in func_80171168 */

typedef struct S_80171168_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80171168_2;   /* temp_s2 in func_80171168 */

/* Move the entity to a selected offset from the origin and update its cell flags. */
void func_80171168(s32 offset_index) {
    const Config24 *offset_table;
    Config24 offsets;
    M2C_UNK old_cell_mask;
    M2C_UNK new_cell_mask;
    u8 *offset_bytes;
    u8 *origin;
    u8 old_x;
    u8 old_y;
    u8 new_x;
    u8 new_y;
    register s16 *offset_pair;
    s32 entity_id;
    S_80171168_1 *entity;
    S_80171168_2 *entity_state;

    offset_table = (const Config24 *)D_8016A87C;
    offsets = *offset_table;
    offset_pair = (s16 *)offsets.data;
    old_cell_mask = 0x3000;
    entity_state = *D_80174CD8 + 0x20;
    entity = ((S_80171168_0 *)(*D_80174CD8))->unk_0C;
    entity_id = ((S_80171168_0 *)(*D_80174CD8))->unk_08;
    entity->unk_14 = (u16) (entity->unk_14 & 0xFF7F);
    old_x = entity->unk_24;
    old_y = entity->unk_25;
    if (entity_state->unk_1C & 0x2000) {
        old_cell_mask = 0x300;
    }
    func_8009A3D0(old_x, old_y, old_cell_mask);
    origin = D_80082E80;
    offset_pair = &offset_pair[offset_index];
    offset_bytes = (u8 *)offset_pair;
    entity->unk_24 = (u8) (origin[0x24] + offset_bytes[0]);
    entity->unk_25 = (u8) (origin[0x25] + offset_bytes[1]);
    func_800A2B04(entity_id, entity->unk_24, entity->unk_25);
    new_x = entity->unk_24;
    new_y = entity->unk_25;
    new_cell_mask = 0x3000;
    if (entity_state->unk_1C & 0x2000) {
        new_cell_mask = 0x300;
    }
    func_8009A21C(new_x, new_y, new_cell_mask);
}
