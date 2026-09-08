#include "common.h"

extern s16 D_80083460[10];

typedef struct {
    s8 pad_00[0x14];
    u32 flags_14;
    u8 pad_18[4];
    u32 flags_1C;
    u8 pad_20[0x21];
    s8 field_41;
    s8 field_42;
    u8 pad_43[0x29];
    u16 value_6C;
    s16 velocity_6E;
    u8 pad_70;
    u8 field_71;
} Entity94744;

/* Apply scaled velocity and reset the entity motion state. */
void func_80099EA4(Entity94744 *entity) {
    entity->field_71 = 0x80;
    entity->value_6C += ((s32)(entity->velocity_6E * D_80083460[0])) >> 8;
    entity->field_42 = 0;
    entity->field_41 = 0;
    entity->flags_1C &= 0x7FFFFFFF;
    entity->flags_14 &= 0x7FFE7FFF;
}
