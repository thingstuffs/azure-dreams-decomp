#include "common.h"
#include "shared/object_flags.h"

typedef struct FuncArg {
    u8 pad0[4];
    s32 field4;
    u8 pad8[0x20];
    s32 field28;
    s32 field2C;
} FuncArg;

extern void func_800AE148(void *source);
extern void func_800B1718(s32 object);
extern void func_800B1DBC(s32 object);
extern s32 D_80082AB4[];

// Set the record and global flags, apply the stored values, and process the record.
void func_800AE2A4(FuncArg *record) {
    s32 firstUpdateValue;
    *(u16 *)((u8 *)record - 2) |= 0x8000;
    firstUpdateValue = record->field28;
    objectFlagBlock.flags |= 0x8000;
    func_800B1718(firstUpdateValue);
    func_800B1DBC(record->field2C);
    D_80082AB4[0] = record->field4;
    func_800AE148(record);
}
