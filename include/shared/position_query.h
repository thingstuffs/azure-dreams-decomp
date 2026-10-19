#ifndef SHARED_POSITION_QUERY_H
#define SHARED_POSITION_QUERY_H
/* Scratch output word for position queries. Both query implementations store
 * one signed word through their second argument and callers pass its address
 * to the follow-up position update. The encoded value's meaning is unknown. */
extern int D_800FE488;

/* Exact access views shared across registered binary consumers. */
/* Unsigned angle value read from the town overlay rotation global. */
typedef struct AngleHalfView {
    unsigned short unk_00;
} AngleHalfView;

#endif
