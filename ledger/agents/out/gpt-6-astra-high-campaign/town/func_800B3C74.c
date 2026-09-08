#include "common.h"

extern void func_800B1390(void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_800B0944(void *, void *, void *);
extern void func_800B1188(void *);

/* Configure the object, update its embedded records, and finalize it. */
void func_800B13D4(void *object, s32 setup_value_1, s32 setup_value_2, s32 setup_value_3,
                   s32 setup_value_4, s32 setup_value_5, s32 setup_value_6, s32 setup_value_7) {
    func_800B1390(object, setup_value_1, setup_value_2, setup_value_3, setup_value_4, setup_value_5, setup_value_6, setup_value_7);
    func_800B0944((u8 *)object + 0xBC, (u8 *)object + 0x94,
                  (u8 *)object + 0xA4);
    func_800B1188(object);
}
