#include "common.h"

typedef struct {
    u8 pad00[0x10];
    u16 unk10;
    u16 unk12;
    u8 pad14[0x0C];
    s32 unk20;
    u16 unk24;
    u16 unk26;
    u8 pad28[0x04];
    s32 unk2C;
} MovieEntity;

/* Waits for readiness, switching entries and copying the selected pair on timeout. */
void func_800408BC(MovieEntity *entity) {
    volatile s32 timeout;
    s32 entry_index;
    u16 *entry;
    s32 entry_stride;

    timeout = 0x800000;
    if (entity->unk2C == 0) {
        do {
            timeout = timeout - 1;
            if (0 == timeout) {
                entity->unk2C = 1;
                entry_index = entity->unk20 == 0;
                entity->unk20 = entry_index;
                entry = (u16 *) ((s32) entity + (entry_index * 8) + 0x10);
                entry_stride = 8;
                entity->unk24 = *entry;
                entity->unk26 = *(u16 *) ((s32) entity + (entity->unk20 * entry_stride) + 0x12);
            }
        } while (entity->unk2C == 0);
    }
    entity->unk2C = 0;
}
