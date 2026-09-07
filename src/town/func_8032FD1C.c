/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001A51C_3 {
    u8 pad_00[0x24];
    void * unk_24;
} S_8001A51C_3;   /* D_80016000[0] in func_8001A51C */

typedef struct S_8001A51C_4 {
    u8 pad_00[0x70];
    void * unk_70;
} S_8001A51C_4;   /* ((S_8001A51C_3 *)(D_80016000[0]))->unk_24 in func_8001A51C */






extern void *D_80016000[3];

typedef struct S_8001A51C_0 {
    u8 pad_00[0x1DC];
    u16 * unk_1DC;
} S_8001A51C_0;   /* temp_v0 in func_8001A51C */

typedef struct S_8001A51C_1 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
} S_8001A51C_1;   /* arg1 in func_8001A51C */

typedef struct S_8001A51C_2 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_8001A51C_2;   /* var_t2 in func_8001A51C */

void func_8001A51C(u16 *arg0, S_8001A51C_1 *arg1) {
    s32 var_a2;
    s32 var_t0;
    register s32 var_a0 ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 var_v0;
    s32 var_v1;
    volatile u16 *var_a3;
    u16 *var_t1;
    register u16 *var_store ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s8 *var_t2;
    void *temp_v0;

    var_a3 = arg0;
    ASM_KEEP(var_a3);   /* MATCH pin: retail delay-slot fill depends on it */
    temp_v0 = ((S_8001A51C_4 *)(((S_8001A51C_3 *)(D_80016000[0]))->unk_24))->unk_70;
    var_t2 = (s8 *)temp_v0 + 0x1DC;
    var_t1 = ((S_8001A51C_0 *)temp_v0)->unk_1DC;
    var_t0 = 0;
    if (arg1->unk_06 > 0) {
        do {
            var_a2 = 0;
            if (arg1->unk_04 > 0) {
                do {
                    var_a0 = arg1->unk_00;
                    var_a0 += var_a2;
                    ASM_KEEP(var_a0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    var_v0 = arg1->unk_02;
                    var_v0 += var_t0;
                    ASM_KEEP(var_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    var_v1 = ((S_8001A51C_2 *)var_t2)->unk_14;
                    var_v0 <<= var_v1;
                    var_a0 += var_v0;
                    if (*var_a3 != 0) {
                        var_store = (u16 *)((var_a0 << 1) + (s32)var_t1);
                        ASM_KEEP(var_store);   /* MATCH pin: retail delay-slot fill depends on it */
                        *var_store = *var_a3;
                    }
                    var_a2 += 1;
                    var_a3 += 1;
                } while (var_a2 < arg1->unk_04);
            }
            do {
                var_t0 += 1;
            } while (0);
        } while (var_t0 < arg1->unk_06);
    }
}
