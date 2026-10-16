#include "common.h"

extern void townInitializeShopSubrecord(void *, s32, s32, s32, s32, s32, s32, s32);
extern void townInitializeShopParts(void *, void *, void *);
extern void townInitializeShopWindowLayout(void *);

/* Configure the object, update its embedded records, and finalize it. */
void townConfigureShopObjectAndFinalize(void *object, s32 setup_value_1, s32 setup_value_2, s32 setup_value_3,
                   s32 setup_value_4, s32 setup_value_5, s32 setup_value_6, s32 setup_value_7) {
    townInitializeShopSubrecord(object, setup_value_1, setup_value_2, setup_value_3, setup_value_4, setup_value_5, setup_value_6,
        setup_value_7);
    townInitializeShopParts((u8 *)object + 0xBC, (u8 *)object + 0x94,
                  (u8 *)object + 0xA4);
    townInitializeShopWindowLayout(object);
}
