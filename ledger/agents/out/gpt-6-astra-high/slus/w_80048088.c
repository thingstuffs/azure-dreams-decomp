#include "common.h"

extern void func_800481E0(void);
extern void func_80047C00(void);
extern void *func_80047CD8(s16 a0);
extern void func_8003F320(void);
extern void func_80047EEC(s32 a0, void *a1);
extern void func_80047FF4(s32 a0, void *a1);

/* Initializes an entity by type, running housekeeping first for type 0x38. */
void func_80048088(s16 entity_type)
{
    void *entity;

    if (entity_type == 0x38) {
        func_800481E0();
        func_80047C00();
    }
    entity = func_80047CD8(entity_type);
    if (entity) {
        func_8003F320();
        if (entity_type == 0x38) {
            func_80047EEC(0x38, entity);
        } else {
            func_80047FF4(entity_type, entity);
        }
    }
}
