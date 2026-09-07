#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u8 bytes[12];
} Packed12;

typedef struct {
    u8 pad[0xA];
    u16 count;
} DungeonState;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern u8 D_80044BB0[];
extern Packed12 D_80077818;
extern DungeonState D_80083460;
extern u8 D_8016A9FC[];

void func_8016AC30(void) {
    void *object;
    void *position;
    void *primitive;

    object = func_8003FC64(0x12);
    if (object != 0) {
        FIELD(object, void *, 0x10) = D_8016A9FC;
        func_8004491C(object, D_80044BB0);

        do { position = FIELD(object, void *, 8); } while (0);
        FIELD(position, s16, 0xA) = 0;
        FIELD(position, s16, 6) = 0;
        FIELD(position, s16, 2) = 0;

        primitive = FIELD(object, void *, 0xC);
        FIELD(primitive, s16, 0x1E) = 0;
        FIELD(primitive, s16, 0x1C) = 0;
        FIELD(primitive, s8, 0xE) = 0;
        FIELD(primitive, s8, 0xD) = 0;
        FIELD(primitive, s8, 0xC) = 0;

        FIELD(object, Packed12, 0x4C) = D_80077818;
        FIELD(primitive, void *, 8) = (u8 *)object + 0x4C;
        D_80083460.count++;
    }
}
