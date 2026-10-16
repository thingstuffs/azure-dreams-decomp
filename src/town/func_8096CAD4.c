#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80124F6C_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
} S_80124F6C_0;   /* arg0 in townEnterCatalogDetailInput */


void townResetCatalogScrollIndicators(S_80124F6C_0 *);
/* Initialize the state fields before calling townResetCatalogScrollIndicators. */
void townEnterCatalogDetailInput(S_80124F6C_0 *state) {
    state->unk_0A = 8;
    state->unk_04 = 0;
    state->unk_06 = 0;
    townResetCatalogScrollIndicators(state);
}
