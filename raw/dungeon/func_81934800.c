#include "common.h"


typedef struct DungeonCell {
    s16 flags;
    u8 pad02[0x12];
} DungeonCell;

typedef struct DungeonGroup {
    u8 pad00[0xC];
    DungeonCell *cells;
    u8 pad10[4];
} DungeonGroup;

typedef struct DungeonObjectEntry {
    u8 column;
    u8 group;
    s8 amount;
    u8 pad03[0x11];
} DungeonObjectEntry;

typedef struct DungeonObject {
    u8 pad00[0x4C];
    DungeonObjectEntry *entry4C;
    DungeonObjectEntry *entry50;
} DungeonObject;

extern s32 func_800C80F0(void);
extern DungeonGroup D_80073414[];

#ifdef __mips__
extern u8 D_80024128[];
__asm__(".set D_80024128, 0x80024128");
static u8 *const func_81934800_prefix[] __asm__("func_81934800")
    __attribute__((used, section(".text.func_81934800"), aligned(4))) = {
    D_80024128,
};
__asm__(".globl func_81934800\n"
        ".size func_81934800, 296");
#define FUNC_81934800_BODY func_81934804
#else
#define FUNC_81934800_BODY func_81934800
#endif

s32 FUNC_81934800_BODY(DungeonObject *object) {
    s32 count;
    DungeonObjectEntry *entry;
    u8 group;
    u8 column;

    count = 0;
    if (func_800C80F0() != 0) {
        return count;
    }
    entry = object->entry4C;
    if (entry != 0) {
        group = entry->group;
        column = entry->column;
        if ((D_80073414[group].cells[column].flags & 0x8000) != 0 &&
            entry->amount >= -0x62) {
            entry->amount = (u8)entry->amount - 1;
            count = 1;
        }
    }
    entry = object->entry50;
    if (entry != 0) {
        group = entry->group;
        column = entry->column;
        if ((D_80073414[group].cells[column].flags & 0x8000) != 0) {
            if (entry->amount >= -0x62) {
                entry->amount = (u8)entry->amount - 1;
                count += 1;
            }
        }
    }
    return count;
}
