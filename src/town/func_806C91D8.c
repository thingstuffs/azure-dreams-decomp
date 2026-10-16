#include "common.h"

extern s32 townApplyRecordValueForEitherFlag(s32, s32);
extern s32 func_80016A78();
extern s32 func_80016B20();

/* Run the conditional handler for values of at least five, then process the inputs. */
void townRunConditionalHandlerAndProcess(s32 input_a, s32 input_b) {
    if (townApplyRecordValueForEitherFlag(input_a, input_b) >= 5) {
        func_80016A78();
    }
    func_80016B20(input_a, input_b);
}
