#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

struct Node *find_lookable_person_six(void)
{
    return town_scene_root->services->psn_lookable_get(6);
}
