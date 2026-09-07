#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s8 unk0[0x1C];
    u16 count;
} DungeonState;

typedef struct {
    u8 unk0;
    s8 type;
    u8 count;
} Entry;

extern void func_800A159C(void) __attribute__((noreturn));
extern Entry *func_800A1618(s16 arg0, s16 arg1);
extern DungeonState D_80083460;

s32 func_800A152C(s16 arg0, s16 arg1) {
    s16 type;
    Entry *entry;

    type = arg0;
    if (arg0 == 0x39) {
        type = 2;
    }
    entry = func_800A1618(type, arg1);
    if (entry == NULL) {
        register s32 result ASM_REG("$2");

        result = 0;
        ASM_TAILSLOT_PIN(result);
        func_800A159C();
    }
    entry->type = type;
    entry->count++;
    D_80083460.count++;
    return 1;
}
