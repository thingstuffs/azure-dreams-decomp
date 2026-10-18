#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern unsigned char D_800717D0[16];
extern M2C_UNK D_800D42CC;

/* Passes the global buffer and data address to append_town_movie_list_node. */
void create_familiar_restoration_effect(void) {
    append_town_movie_list_node(D_800717D0, &D_800D42CC);
}
