/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;
typedef struct {
    s32 _0;
    s32 _4;
} M2C_ENTRY;
typedef struct {
    void *_0;
    s32 _4;
    s32 _8;
} M2C_PTR_GLOBAL;

extern M2C_PTR_GLOBAL D_80016000;
extern M2C_UNK D_80016178[3];
extern M2C_UNK D_80017720[3];
extern M2C_PTR_GLOBAL D_8001794C;
extern M2C_UNK D_80017B88[3];

void func_8047E130(void) {
    do { D_8001794C._0 = &D_80017720[0]; } while (0);
    {
        void *p = D_80016000._0;
        M2C_FIELD(M2C_FIELD(p, void **, 0x1C), M2C_UNK **, 0x40) = &D_80017B88[0];
        M2C_FIELD(M2C_FIELD(p, s32 *, 8) * 8 +
                  (s8 *)M2C_FIELD(p, void **, 0x40),
                  M2C_ENTRY **, 0) = (M2C_ENTRY *)&D_80016178[0];
    }
}
