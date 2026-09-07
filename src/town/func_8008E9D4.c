/* cfail-repair: unary-star-typing; preserve the warm source shape */
#include "common.h"
#include "m2c_compat.h"

struct S_8003E2D8 {
    u8 byte_0;
};
extern struct S_8003E2D8 D_80083160;

typedef struct S_8008C134_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
} S_8008C134_0;   /* temp_a2 in func_8008C134 */

typedef struct S_8008C134_1 {
    u8 pad_00[0x1DC];
    s32 unk_1DC;
} S_8008C134_1;   /* temp_a3 in func_8008C134 */

s32 func_8008C134(s32 arg0, s32 arg1) {
    u8 *temp_a3;
    u8 *temp_a2;

    temp_a3 = (u8 *)&D_80083160;
    ASM_KEEP(temp_a3);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    temp_a2 = temp_a3 + 0x1DC;
    ASM_KEEP(temp_a2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    return *(u16 *)(((s32) (((((S_8008C134_0 *)temp_a2)->unk_18 & arg0) + ((s16) (((S_8008C134_0 *)temp_a2)->unk_1A & arg1) << ((S_8008C134_0 *)temp_a2)->unk_14)) << 0x10) >> 0xF) + ((S_8008C134_1 *)temp_a3)->unk_1DC) & 0x3FFF;
}
