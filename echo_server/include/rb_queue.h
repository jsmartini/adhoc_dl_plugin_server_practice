#ifndef QUEUE_H
#define QUEUE_H


#include "stdint.h"
#include "unistd.h"
#include "string.h"
#include "stdbool.h"

#define GEN_FIFO_QUEUE_TYPE(NAME, MAX_SIZE, PAYLOAD)                                                                             \
typedef struct                                                                                                              \
{                                                                                                                           \
    PAYLOAD                                                                                                                 \
} Rb_Queue_Entry_##NAME;                                                                                                    \
                                                                                                                            \
typedef struct                                                                                                              \
{                                                                                                                           \
    Rb_Queue_Entry_##NAME queue[MAX_SIZE];                                                                                  \
    size_t index_spread_st0;                                                                                                \
    size_t tail_index;                                                                                                      \
    size_t size;                                                                                                            \
} Rb_Fifo_Queue_##NAME;                                                                                                     \
                                                                                                                            \
static inline size_t Rb_Queue_Get_Front_Index_##NAME(Rb_Fifo_Queue_##NAME* q_ptr)                                           \
{                                                                                                                           \
    bool is_wrapped_around = (long)q_ptr->tail_index - (long)q_ptr->index_spread_st0 < 0;                                   \
    if (is_wrapped_around)                                                                                                  \
        return (MAX_SIZE - 1 - q_ptr->index_spread_st0 )  - q_ptr->tail_index;                                              \
    return q_ptr->tail_index - q_ptr->index_spread_st0;                                                                     \
};                                                                                                                          \
                                                                                                                            \
static inline size_t Rb_Queue_Size_##NAME(Rb_Fifo_Queue_##NAME* q_ptr)                                                      \
{                                                                                                                           \
    return q_ptr->size;                                                                                                     \
};                                                                                                                          \
                                                                                                                            \
static inline void Rb_Queue_Push_Tail_##NAME(Rb_Fifo_Queue_##NAME *q_ptr, Rb_Queue_Entry_##NAME data)                       \
{                                                                                                                           \
    if (q_ptr->index_spread_st0 + 1 == MAX_SIZE && q_ptr->tail_index + 1 == MAX_SIZE)                                       \
        q_ptr->tail_index = 0;                                                                                              \
    else                                                                                                                    \
        q_ptr->tail_index++;                                                                                                \
    if(q_ptr->index_spread_st0 + 1 < MAX_SIZE)                                                                              \
        q_ptr->index_spread_st0++;                                                                                          \
    if (q_ptr->size < MAX_SIZE)                                                                                             \
        q_ptr->size++;                                                                                                      \
    memcpy(&q_ptr->queue[q_ptr->tail_index], &data, sizeof(data));                                                          \
};                                                                                                                          \
                                                                                                                            \
static inline bool Rb_Queue_Pop_Front_##NAME(Rb_Fifo_Queue_##NAME *q_ptr, Rb_Queue_Entry_##NAME* target_data_ptr)           \
{                                                                                                                           \
    if (q_ptr->size == 0)                                                                                                   \
        return false;                                                                                                       \
    q_ptr->size--;                                                                                                          \
    memcpy((char*)target_data_ptr, &q_ptr->queue[Rb_Queue_Get_Front_Index_##NAME(q_ptr)], sizeof(Rb_Queue_Entry_##NAME));   \
    q_ptr->index_spread_st0--;                                                                                              \
};                                                                                                                          \
                                                                                                                            \
static inline void Rb_Queue_Init_##NAME(Rb_Fifo_Queue_##NAME *q_ptr)                                                        \
{                                                                                                                           \
    memset(q_ptr, 0, sizeof(Rb_Fifo_Queue_##NAME));                                                                         \
};                       



#endif