#include "common.h"

typedef struct Entity {
    volatile s32 state;
    u8 pad_04[0x44];
    void *object;
} Entity;

extern void func_80025A0C(void);
extern u8 D_80025BD4[];

void func_80025BF4(Entity *entity) {
    s32 state;

    *(s16 *)((u8 *)entity->object + 6) = entity->state << 10;
    state = entity->state + 1;
    entity->state = state;
    if (state >= 5) {
        entity->state = 0;
        *(void **)((u8 *)entity - 0x10) = D_80025BD4;
    }
    func_80025A0C();
}
