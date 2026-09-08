#include "common.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

extern s32 func_8009CFE0(void *, void *);
extern void func_80033D08(void *arg0);
extern s32 func_800644B8(s32 angle);
extern s32 func_80064584(s32 angle);

typedef struct {
    s32 unused;
    void *record;
} D_80082660_entry;

extern s32 D_800814A0[3];
extern D_80082660_entry D_80082660[];

void func_800A7EC0(void *arg0, void *arg1)
{
    s32 value;
    s32 value2;
    s8 *flag;
    u8 state;
    u8 index;
    void *record;
    void *entity;
    void *position;

    state = FIELD(arg0, u8 *, 0x60);
    index = state & 0xFF;
    if (func_8009CFE0(arg0, arg1) != 0) {
        flag = FIELD(arg0, s8 **, 0x98);
        if (flag != 0) {
            *flag = 0;
        }
        func_80033D08(arg0);
        FIELD(arg0, u16 *, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    if (index != 0) {
        record = D_80082660[index].record;
        entity = (u8 *)record + 0x20;
        if (record != 0) {
            position = FIELD(record, void **, 8);
            value = func_800644B8(FIELD(entity, s16 *, 0x72));
            if (value < 0) {
                value += 0xFF;
            }
            FIELD(arg1, s16 *, 2) =
                FIELD(position, u16 *, 2) + (value >> 8);

            value2 = func_80064584(FIELD(entity, s16 *, 0x72));
            if (value2 < 0) {
                value2 += 0xFF;
            }
            FIELD(arg1, s16 *, 6) =
                FIELD(position, u16 *, 6) + (value2 >> 8);
            FIELD(arg1, s16 *, 0xA) = FIELD(position, u16 *, 0xA) - 0x20;
        }
    }
}
