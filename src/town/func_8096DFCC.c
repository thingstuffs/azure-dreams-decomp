#include "common.h"

typedef struct {
    u8 pad00[0xC];
    u8 active;
    u8 pad0D;
    u8 flags;
} TownObject;
extern void townUpdateCatalogScrollIndicators(TownObject *);
void func_80126464(TownObject *object) { townUpdateCatalogScrollIndicators(object); }
