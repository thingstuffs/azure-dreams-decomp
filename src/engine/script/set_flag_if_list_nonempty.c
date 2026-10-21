#include "common.h"

#include "common.h"
#include "engine/script.h"

/* Sets the output flag when is_list_nonempty returns nonzero. */
void set_flag_if_list_nonempty(s8 *result_flag) {
    if (is_list_nonempty(result_flag) != 0) {
        *result_flag = 1;
    }
}
