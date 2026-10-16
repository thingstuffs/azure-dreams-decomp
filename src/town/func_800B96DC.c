#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"

extern s32 Control_CD();
extern s32 getEnabledRecordFlagPriority();
extern s16 townGetMappedObjectCode();
extern void townInitializeCoordinateEntry();
extern void townClearMonsterStatusTexture();
extern s32 townReleaseMonsterStatusRequestHandles();
extern s16 D_80083D78[8];
extern u8 D_800B5B20[16];


typedef struct S_800B6E3C_1 {
    s16 unk_00;
    s16 unk_02;
} S_800B6E3C_1;   /* temp_a0 in townInvalidateCachedStateAndQueueRead */

typedef struct S_800B6E3C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800B6E3C_2;   /* (void *)temp_idx in townInvalidateCachedStateAndQueueRead */

/* Invalidates changed cached state and starts the corresponding CD operations. */
s32 townInvalidateCachedStateAndQueueRead(void *state) {
    s32 state_code;
    s32 cache_addr;
    S_800B6E3C_1 *cached_state;

    ((Rec_func_800B683C_arg0 *)state)->unk_0A = townGetMappedObjectCode(((Rec_func_800B683C_arg0 *)state)->unk_04);
    state_code = getEnabledRecordFlagPriority(((Rec_func_800B683C_arg0 *)state)->unk_04);
    ((Rec_func_800B683C_arg0 *)state)->unk_10 = state_code;
    if (state_code == 3) {
        ((Rec_func_800B683C_arg0 *)state)->unk_10 = 0;
    }
    if (townReleaseMonsterStatusRequestHandles(state) != 0) {
        *((((Rec_func_800B683C_arg0 *)state)->unk_08 * 2) + D_80083D78) = -1;
    }
    cached_state = (((Rec_func_800B683C_arg0 *)state)->unk_08 * 2) + D_80083D78;
    if ((cached_state->unk_00 != ((Rec_func_800B683C_arg0 *)state)->unk_0A)
        || (cached_state->unk_02 != ((Rec_func_800B683C_arg0 *)state)->unk_10)) {
        cached_state->unk_00 = -1;
        cache_addr = ((Rec_func_800B683C_arg0 *)state)->unk_08;
        cache_addr <<= 2;
        cache_addr += (s32)D_80083D78;
        ((S_800B6E3C_2 *)((void *)cache_addr))->unk_02 = -1;
        townClearMonsterStatusTexture(((Rec_func_800B683C_arg0 *)state)->unk_14);
        ((Rec_func_800B683C_arg0 *)state)->unk_DC = 0;
        townInitializeCoordinateEntry(state);
        ((Rec_func_800B683C_arg0 *)state)->unk_D0 = Control_CD(6, state + 0xD8, NULL);
        ((Rec_func_800B683C_arg0 *)state)->unk_D4 = Control_CD(0xFF, &D_800B5B20, state);
        return 1;
    }
    return 0;
}
