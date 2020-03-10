#ifndef LINK_H
#define LINK_H

#include <stdbool.h>
#include <stddef.h>
typedef struct _link_node{
    struct _link_node *prev, *next ;
}link_node ;

#define DEFAULT_LINK_HEAD(link_head) {&(link_head), &(link_head)}
#define INIT_LINK_HEAD(link_node_pointer) (*(link_node_pointer) = (link_node){(link_node_pointer), (link_node_pointer)})
#define ADDR_LINK2DATA(link_node_pointer, type, member) ((type*)((unsigned char *)(link_node_pointer) - offsetof(type, member)))

static inline void _link_add(link_node *prev, link_node *next, link_node *new_pointer)
{
    prev->next = new_pointer ;
    new_pointer->prev = prev ;
    new_pointer->next = next ;
    next->prev =new_pointer ;
}

static inline void _link_remove(link_node *target_pointer)
{
    target_pointer->next->prev = target_pointer->prev ;
    target_pointer->prev->next = target_pointer->next ;
    INIT_LINK_HEAD(target_pointer) ;
}

static inline void link_add(link_node *head_pointer, link_node *new_pointer)
{
    _link_add(head_pointer->prev, head_pointer, new_pointer) ;
}

static inline void link_push(link_node *head_pointer, link_node *new_pointer)
{
    _link_add(head_pointer->prev, head_pointer, new_pointer) ;
}

static inline link_node *link_pop(link_node *head_pointer)
{
    link_node *top_pointer = NULL;
    if(head_pointer->next != head_pointer)
    {
        top_pointer = head_pointer->prev ;
        _link_remove(top_pointer) ;
    }

    return top_pointer ;
}

static inline link_node *link_out(link_node *head_pointer)
{
    link_node *first_pointer = NULL ;
    if(head_pointer->next != head_pointer)
    {
        first_pointer = head_pointer->next ;
        _link_remove(first_pointer) ;
    }
    return first_pointer ;
}

static inline bool link_isempty(link_node *head_pointer)
{
    return head_pointer->next == head_pointer ;
}

#endif // LINK_H
