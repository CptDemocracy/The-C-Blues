/*
[ref.href] http://www.cprogramming.com/challenges/print_reverse.html

PROBLEM:
Using whatever programming techniques you know, write the cleanest possible function 
you can think of to print a singly linked list in reverse. The format for the node 
should be a struct containing an integer value, val, and a next pointer to the following node.

SOLUTION:
The technique we are going to use in our LinkedListInReverse(struct node*) function is recursion.
While a node is not a NULL (the end of the linked list is demarcated by a NULL), simply have the
function call itself on the next node in the list, and then proceed to outputting the value of
the node the function has been currently called upon.
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct node {
    int val;
    struct node *nxt;
};

void LinkedListInReverse(struct node *head);

int main() {
    struct node *head = (struct node*)calloc(1, sizeof(struct node));
    struct node *curr = head;
    size_t count = 10;
    for (size_t i = 1; i < count; ++i) {
        curr->nxt = (struct node*)calloc(1, sizeof(struct node));
        if (!curr->nxt) {
            errno = ENOMEM;
            return 1;
        }
        curr = curr->nxt;
        curr->val = i;
    }
    curr = NULL;

    LinkedListInReverse(head);

    curr = head;
    for (size_t i = 0; i < count; ++i) {
        head = curr->nxt;
        free(curr);
        curr = head;
    }
    head = NULL;
    getchar();

    return 0;
}

void LinkedListInReverse(struct node *head) {
    if (head) {
        LinkedListInReverse(head->nxt);
    }
    else return;
    printf("%d ", head->val);
}
