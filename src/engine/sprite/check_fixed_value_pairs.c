#include "common.h"

extern int check_fixed_value_pairs(void);
extern int get_item_name_text(void *a0, int *a1);

extern int D_80080B34[4]; /* >8B forces %hi/%lo addressing (matches target's lui/addiu) */
extern int D_80080B40[4]; /* >8B forces %hi/%lo addressing (matches target's lui/addiu) */

/* Selects a global array based on the object check and returns get_item_name_text's result. */
int func_800494B4(void *object)
{
    void *saved_object = object;
    int check_result = check_fixed_value_pairs();
    int *selected_array;

    if (check_result) {
        selected_array = D_80080B34;
    } else {
        selected_array = D_80080B40;
    }

    return get_item_name_text(saved_object, selected_array);
}
