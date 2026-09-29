#include "common.h"
#include "shared/object_flags.h"

typedef struct S_80020488_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u8 pad_02[0xA];
    void * unk_0C;
    u8 pad_10[0xC];
    u16 unk_1C;
} S_80020488_0;   /* arg0 in func_80020488 */

typedef struct S_80020488_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0xA];
    s16 unk_36;
} S_80020488_1;   /* entity in func_80020488 */


/* Advances the context state and sets completion flags in response to entity fields. */
void func_80020488(void *context) {
    s16 state;
    void *entity;

    state = ((S_80020488_0 *)context)->unk_00.s;
    entity = ((S_80020488_0 *)context)->unk_0C;
    switch (state) {
    case 0:
        if (((S_80020488_1 *)entity)->unk_36 == 0xFF) {
            ((S_80020488_0 *)context)->unk_1C &= 0xFFFD;
            ((S_80020488_0 *)context)->unk_00.u++;
        }
        break;
    case 1:
        if (((S_80020488_1 *)entity)->unk_2A & 1) {
            (*(u16 *)((u8 *)context + -2)) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        break;
    }
}

/* MECHANISM: Frameless leaf with an explicit dispatch, state 0 before state 1, and a shared return.
   A zero-word scheduling barrier preserves the common epilogue; width-accurate fields keep RMW order. */
