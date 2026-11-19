#ifndef LIST_H
#define LIST_H

#include "common.h"

/* Singly linked list with an iteration cursor. The helpers are static
 * inline: retail has copies of them inlined in more than one file. */

typedef struct ListNode {
    struct ListNode *next;
} ListNode;

typedef struct {
    /* 0x0 */ ListNode *head;
    /* 0x4 */ ListNode *cur;
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 count;
} List;

extern List D_00359710;
extern void func_0033B2E8(void *); /* free */

/* Unlink n (if present), free it, and reset the cursor. */
static inline void ListRemove(List *l, ListNode *n) {
    ListNode *it;
    ListNode *prev;

    if (l->head != NULL) {
        prev = NULL;
        it = l->head;
        do {
            if (it == n) {
                if (prev != NULL) {
                    prev->next = n->next;
                } else {
                    l->head = n->next;
                }
                l->count--;
                break;
            }
            prev = it;
            it = it->next;
        } while (it != NULL);
    }
    func_0033B2E8(n);
    l->cur = l->head;
}

static inline ListNode *ListNext(List *l) {
    ListNode *n = l->cur;

    if (n == NULL) {
        return NULL;
    }
    l->cur = n->next;
    return n;
}

/* Free every node and reset the list. */
static inline void ListClear(List *l) {
    ListNode *n;

    l->cur = l->head;
    while ((n = ListNext(l)) != NULL) {
        ListRemove(l, n);
    }
    l->count = 0;
    l->head = NULL;
    l->cur = NULL;
    l->unk8 = 0;
}

#endif /* LIST_H */
