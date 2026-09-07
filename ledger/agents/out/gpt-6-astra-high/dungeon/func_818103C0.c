#include "common.h"

typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s32 field_24;
    s32 field_28;
    s32 field_2C;
    s32 field_30;
    s32 field_34;
} Entity;

extern void func_80026294();
extern void func_800285B0();
extern void func_80026B94();
extern void func_8004A464();
extern void func_800DBF5C();
extern void strcpy();
extern u8 D_80082E6A[9];

/* Processes entity fields and copies its string for selected type and state values. */
void func_800253C0(Entity *entity) {
    s32 state;

    func_80026294(entity->field_20);
    func_800285B0(entity->field_24);
    func_80026B94(entity->field_28);
    func_8004A464(entity->field_2C, 0);
    func_8004A464(entity->field_30, 0);
    func_8004A464(entity->field_34, 0);
    if (D_80082E6A[0] != 1) {
        func_800DBF5C();
    }
    if (entity->field_14 == 0x13) {
        state = entity->field_1C;
        if (state == 2 || state == 0x39) {
            strcpy((void *)0x80010238, entity->field_4);
        }
    }
}
