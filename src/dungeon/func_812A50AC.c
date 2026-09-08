#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u8 pad0[2];
    s16 field2;
    u8 pad4[2];
    s16 field6;
    u8 pad8[2];
    u16 fieldA;
    u8 padC[0x18];
    u8 field24;
    u8 field25;
    u8 pad26[6];
    void *field2C;
} Func812A5000Child;

typedef struct {
    u8 pad0[8];
    Func812A5000Child *child1;
    Func812A5000Child *child0;
    void *field10;
} Func812A5000Parent;

typedef struct {
    u8 pad0[0x13];
    u8 field13;
    u32 field14;
    u8 pad18[4];
    u32 field1C;
    u8 pad20[0xA];
    s16 field2A;
    u8 pad2C[0x60];
    void *field8C;
    u8 pad90[2];
    s16 field92;
    u8 pad94[6];
    u8 field9A;
    u8 pad9B;
    s8 field9C;
} Func812A5000Entity;

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80175C30[];
extern u8 D_80171FA4[];
void *func_8003FD64();                 /* extern */
M2C_UNK func_8004491C();                /* extern */
M2C_UNK func_800A9C18(); /* extern */
M2C_UNK func_800AA36C(); /* extern */
s32 func_800F6D28();                          /* extern */
extern volatile void *D_800FBE1C[];
extern u8 D_80170A4C[];

/* Creates and initializes an entity at the center of the specified tile. */
void *func_812A50AC(s16 entity_id, s16 tile_x, u16 tile_y, u16 height) {
    Func812A5000Parent *parent;
    Func812A5000Child *tile_state;
    Func812A5000Child *position;
    Func812A5000Entity *entity;

    entity = NULL;
    parent = func_8003FD64(0x112, D_80083498);
    if (parent != NULL) {
        if (D_800FBE1C[0] == 0) {
            D_800FBE1C[0] = parent;
        }
        entity = (Func812A5000Entity *)((u8 *)parent + 0x20);
        parent->field10 = D_80170A4C;
        entity->field13 = 0x39;
        func_8004491C(parent, D_80045340);
        tile_state = parent->child0;
        position = parent->child1;
        tile_state->field24 = tile_x;
        tile_state->field25 = tile_y;
        tile_state->field2C = D_80175C30;
        position->field2 = (s16)((tile_state->field24 << 6) + 0x20);
        position->field6 = (s16)((tile_state->field25 << 6) + 0x20);
        position->fieldA = height;
        entity->field2A = (s16)(func_800F6D28(position) << 9);
        entity->field13 = 2;
        entity->field14 |= 0x6000;
        entity->field1C |= 0x6000;
        func_800A9C18(parent, position, tile_state, entity_id);
        entity->field9A = 0xFF;
        entity->field9C = -1;
        entity->field8C = D_80171FA4;
        entity->field92 = -0x20;
        entity->field13 = 0x39;
        entity->field1C |= 0x40000;
        func_800AA36C(entity, position, tile_state, entity);
    }
    return entity;
}
