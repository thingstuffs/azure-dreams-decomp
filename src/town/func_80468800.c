#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern void *func_80019AFC();
extern void *D_80016000[];
extern void *D_8001E950[];

/* Checks the active event and dispatches the 0x27/0x200 handler when matched. */
s32 func_80019800(void) {
    void *event;

    if ((u8) FIELD(D_8001E950[0], u8 *, 1) < 2U) {
        event = func_80019AFC(FIELD(D_8001E950[0], u8 *, 1),
                              FIELD(D_8001E950[0], u8 *, 5));
        if (FIELD(event, s16 *, 0) == 0x27) {
            if (FIELD(event, s16 *, 2) == 0x200) {
                FIELD(FIELD(D_80016000[0], void **, 0x20),
                      M2C_UNK (**)(M2C_UNK, M2C_UNK), 0x2F8)(0x27, 0x200);
            }
        }
        return 1;
    }
    return 0;
}
