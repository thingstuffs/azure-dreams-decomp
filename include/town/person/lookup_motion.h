#ifndef TOWN_PERSON_LOOKUP_MOTION_H
#define TOWN_PERSON_LOOKUP_MOTION_H

struct Rec_func_800AB030_arg0;
struct ObjectPosition;

int advance_person_sine_offset(struct Rec_func_800AB030_arg0 *record);
void set_object_z_from_lookup(struct Rec_func_800AB030_arg0 *source, struct ObjectPosition *object);

#endif
