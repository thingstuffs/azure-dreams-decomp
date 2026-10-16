#include "common.h"

typedef struct {
    u8 pad00[0xC];
    u8 active;
    u8 pad0D;
    u8 flags;
} TownObject;
extern void func_80125730(TownObject *);
void func_80125F98(TownObject *object) { func_80125730(object); }
