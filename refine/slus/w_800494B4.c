#include "common.h"

extern int func_800B8C90(void *a0);
extern int func_80049374(void *a0, int *a1);

extern int D_80080B34[4]; /* >8B forces %hi/%lo addressing (matches target's lui/addiu) */
extern int D_80080B40[4]; /* >8B forces %hi/%lo addressing (matches target's lui/addiu) */

/* Selects a global array based on the object check and returns func_80049374's result. */
int func_800494B4(void *object)
{
    void *saved_object = object;
    int check_result = func_800B8C90(object);
    int *selected_array;

    if (check_result) {
        selected_array = D_80080B34;
    } else {
        selected_array = D_80080B40;
    }

    return func_80049374(saved_object, selected_array);
}
