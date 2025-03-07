#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define MAX_WORD_LEN  50

typedef struct node_t {
    char           *word;
    struct node_t  *next;
} node_t;

node_t *new_node(char *val);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
node_t *add_inorder(node_t *, node_t *);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);
void    apply(node_t *, void(*fn)(node_t *, void *), void *arg);

#endif
