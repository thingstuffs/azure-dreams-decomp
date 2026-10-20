#include "common.h"

extern int check_fixed_value_pairs(void);
extern int get_item_name_text(void *a0, int *a1);

extern int item_text_checked_fallback_pair[4]; /* >8B forces %hi/%lo addressing (matches target's lui/addiu) */
extern int item_text_default_fallback_pair[4]; /* >8B forces %hi/%lo addressing (matches target's lui/addiu) */

/* Selects a global array based on the object check and returns get_item_name_text's result. */
int select_item_name_table_from_pair_check(void *object)
{
    void *saved_object = object;
    int check_result = check_fixed_value_pairs();
    int *selected_array;

    if (check_result) {
        selected_array = item_text_checked_fallback_pair;
    } else {
        selected_array = item_text_default_fallback_pair;
    }

    return get_item_name_text(saved_object, selected_array);
}
