#ifndef TOWN_PERSON_LOOKUP_MOTION_H
#define TOWN_PERSON_LOOKUP_MOTION_H

struct TownObjectRecord;
struct ObjectPosition;

int advance_person_sine_offset(struct TownObjectRecord *record);
void set_object_z_from_lookup(struct TownObjectRecord *source, struct ObjectPosition *object);

#endif
