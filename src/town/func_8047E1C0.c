/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800175E0();
extern M2C_UNK D_8001624C;
extern M2C_UNK D_800177C8;
extern M2C_UNK *D_8001794C[3];
extern M2C_UNK D_8001802A;
extern u8 D_80010000[];

typedef void (*TownCall)(s32, s32, void *);

/* Updates town state pointers and dispatches a town call. */
void func_8047E1C0(void) {
    void *state_data;
    s32 call_code;
    register void *dispatch_table ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    call_code = 0x3B0;
    state_data = &D_8001802A;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(D_80010000, void **, 0x6000), void **, 0x1C), M2C_UNK **, 0x40) = state_data;
    dispatch_table = M2C_FIELD(M2C_FIELD(D_80010000, void **, 0x6000), void **, 0x20);
    *(volatile M2C_UNK **)&D_8001794C[0] = &D_800177C8;
    M2C_FIELD(dispatch_table, TownCall *, 0x2EC)(call_code, 0x100, M2C_FIELD(D_80010000, void **, 0x6000));
    func_800175E0(0x98);
    *(void **)((s8 *)M2C_FIELD(M2C_FIELD(D_80010000, void **, 0x6000), s32 *, 0x40) + M2C_FIELD(M2C_FIELD(D_80010000, void **, 0x6000), s32 *, 8) * 8) = &D_8001624C;
}
