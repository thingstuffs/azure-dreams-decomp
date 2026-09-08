#include "common.h"

typedef struct {
    void (*field_0)();
    unsigned char pad4[0x1C - 4];
    void *field_1C;
    unsigned char pad20[0x2C - 0x20];
    char *field_2C;
} S_800509C4;

extern void func_8005097C(char *a0);
extern void func_80050640(void);

/* Stores the object's context, reinitializes its sub-object, and installs its dispatch handler. */
void func_800509C4(S_800509C4 *object, void *context)
{
    object->field_1C = context;
    func_8005097C(object->field_2C);
    object->field_0 = func_80050640;
}
