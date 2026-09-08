#include "common.h"
#include "records/Rec_D_80082EB0.h"

typedef struct S_80091958_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x2C];
    void * unk_C8;
} S_80091958_0;   /* arg0 in func_80091958 */


typedef struct S_80091958_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80091958_2;   /* arg3 in func_80091958 */

typedef struct S_80091958_3 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80091958_3;   /* ((S_80091958_0 *)arg0)->unk_C8 in func_80091958 */



extern s32 D_80082EB0;
extern s32 D_8008ACDC;
extern u8 D_8008EAC8[];

void *func_800BA074(s32);

/* Starts an operation, waits for completion, then selects the next action from context flags. */
void func_80091958(S_80091958_0 *state, s32 unused_1, s32 unused_2, S_80091958_2 *context)
{
    void *operation;

    switch (state->unk_9B) {
    case 0:
        operation = func_800BA074(D_80082EB0);
        state->unk_C8 = operation;
        if (operation == 0) {
            break;
        }
        state->unk_9B++;
    case 1:
        if (((S_80091958_3 *)(state->unk_C8))->unk_1E & 0x8000) {
            state->unk_C8 = 0;
            state->unk_9B++;
        }
        break;
    case 2:
        ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_08 = 0;
        if (context->unk_1C & 0x100000) {
            state->unk_8C = D_8008EAC8;
        } else {
            state->unk_8C = &D_8008ACDC;
        }
        break;
    }
}
