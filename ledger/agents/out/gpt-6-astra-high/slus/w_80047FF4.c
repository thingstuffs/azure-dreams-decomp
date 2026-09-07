#include "common.h"

#ifdef NON_MATCHING
#define LOCAL_ASM_REG(reg)
#define LOCAL_ASM_KEEP(var) ((void)0)
#else
#define LOCAL_ASM_REG(reg) asm(reg)
#define LOCAL_ASM_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

typedef struct {
    s32 flag;
    u16 status;
    u16 pad6;
} S_80083D08;

extern S_80083D08 D_80083D08[6];
extern void *D_80080A90[4];
extern s32 func_80047C60(void *a0);
extern void *func_80047AB0(void *a0, s32 a1, s32 a2, s32 a3, void *a4);
extern void *func_80047EEC(s32 a0, void *a1);

/* Records an object's slot and type, with a separate handler for type 0x38. */
void *func_80047FF4(s32 object_type, void *object)
{
    void *lookup_object;
    void **resource_table;
    void **resources;
    s32 slot;
    register s32 special_type LOCAL_ASM_REG("$2") = 0x38;

    if (object_type != special_type) {
        lookup_object = object;
        resource_table = D_80080A90;
        resources = resource_table;
        slot = func_80047C60(lookup_object);
        (*(D_80083D08 + slot)).flag = (s32)object;
        (*(&D_80083D08[slot])).pad6 = (u16)object_type;
        return func_80047AB0(object, slot + 5,
                             ((slot * 3) + 0x1D2) << 6,
                             0xD, resources[0]);
    }
    LOCAL_ASM_KEEP(special_type);
    return func_80047EEC(special_type, object);
}
