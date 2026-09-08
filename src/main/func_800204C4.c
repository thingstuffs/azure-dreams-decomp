#include "common.h"

extern void func_8004DDBC(void *arg0, void *arg1, void *arg2);
extern u8 D_80408A30[];

/* Configures two object entries and initializes them with shared data. */
void func_800204C4(void *object) {
    void *entry;
    void *shared_data;

    shared_data = D_80408A30;
    entry = *(void **)((u8 *)(*(void **)((u8 *)object + 0x60)) + 8);
    *(s16 *)(*(void **)((u8 *)entry + 4) + 8) = 0x40;
    *(s16 *)(*(void **)((u8 *)entry + 4) + 0xA) = 0x20;
    func_8004DDBC((u8 *)object + 4, shared_data, entry);

    entry = *(void **)((u8 *)(*(void **)((u8 *)object + 0x60)) + 0xC);
    *(s16 *)(*(void **)((u8 *)entry + 4) + 8) = 0xC0;
    *(s16 *)(*(void **)((u8 *)entry + 4) + 0xA) = 0x20;
    func_8004DDBC((u8 *)object + 0x10, shared_data, entry);
}
