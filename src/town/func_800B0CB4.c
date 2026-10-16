#include "common.h"
#include "shared/object_flags.h"

typedef struct FuncArg {
    s32 field0;
    s32 field4;
    s32 field8;
} FuncArg;

extern void townResetItemMenuObjectState(s32 object);
extern void townScheduleItemMenuChildRelease(s32 object);
extern void townSetObjectDataPointer(s32 object);
extern void func_8004E130(void);
extern void townHandleSelectionAndCreateObject(void);

// Set the high-bit flags and pass the three parameters to their handlers.
void townStartItemMenuObjectProcessing(FuncArg *parameters) {
    s32 firstParameter = parameters->field0;
    ((u16 *)parameters)[-1] |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
    townResetItemMenuObjectState(firstParameter);
    townScheduleItemMenuChildRelease(parameters->field4);
    townSetObjectDataPointer(parameters->field8);
    func_8004E130();
    townHandleSelectionAndCreateObject();
}
