#include "common.h"

typedef struct {
    u8 pad12[0x12];
    s16 value12;
    u16 value14;
} Func800CF16CArg;

extern s32 dungeonFadeActorToRemoval(void *first_ptr, void *second_ptr, Func800CF16CArg *record, s32 value);
extern void func_800A56C0(void);

void dungeonInitializeActorActionData(void *first_ptr, void *second_ptr, Func800CF16CArg *record, s32 value) {
    if (dungeonFadeActorToRemoval(first_ptr, second_ptr, record, value) != 0) {
        func_800A56C0();
        return;
    }

    record->value12 = 0x7E40;
    record->value14 |= 0x100;
}
