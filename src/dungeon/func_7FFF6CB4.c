#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK SD_Call();
void func_80094984(s32 *entries, void *record, s32 handler_param); /* extern */
void func_80094C1C(void *record);                /* extern */
extern M2C_UNK D_800924EC;
extern M2C_UNK D_800D0110;

/* Run setup 0x50B and initialize the object's state data. */
void func_80094414(M2C_UNK **object, M2C_UNK unused, M2C_UNK context) {
    SD_Call(0x50B);
    func_80094C1C(object);
    func_80094984(&D_800D0110, object, context);
    *object = &D_800924EC;
}
