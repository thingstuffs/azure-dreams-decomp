#include "common.h"

typedef struct TableEntry_800252CC {
    s32 value;
    u8 pad04[0x7C];
} TableEntry_800252CC;

extern void func_80022F8C(void *, void *);
extern void func_800230A4(void *);
extern u8 D_80024FAC[];
extern u8 D_800252A4[];
extern u8 D_8002593C[];
extern TableEntry_800252CC D_80083E98[];

#define FIELD32(base, offset) (*(s32 *)((u8 *)(base) + (offset)))
#define FIELDP(base, offset) (*(void **)((u8 *)(base) + (offset)))

void func_800252CC(void *arg0)
{
    s32 one;
    void *parent;

    parent = (u8 *)arg0 - 0x20;
    if (D_80083E98[FIELD32(arg0, 0x28)].value != 0) {
        one = 1;
        FIELD32(arg0, 0x3C) = one;
        func_80022F8C(parent, (u8 *)arg0 + 0x40);
        FIELD32(arg0, 0x40) = one;
        FIELDP(arg0, -0x10) = D_800252A4;
    } else {
        FIELDP(arg0, 0x34) = D_8002593C;
        func_800230A4(parent);
        FIELDP(arg0, -0x10) = D_80024FAC;
    }
}
