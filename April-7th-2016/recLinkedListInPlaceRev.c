#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct node {
    int val;
    struct node *nxt;
};

struct node *ReverseLinkedList(struct node *head);

struct node *ReverseLinkedListHelper(struct node *head);

int main() {
    
    // Linked list initialization.
    // Usually we would have it done in a separate function, as 
    // encapsulated as C allows, but for this problem, we keep
    // initialization and de-allocation all in one function
    
    struct node *head = (struct node*)calloc(1, sizeof(struct node));
    struct node *curr = head;
    size_t count = 5;
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

    head = ReverseLinkedList(head);

    // De-allocate the linked list
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

// Does the actual recursive in-place reverse of the linked list
struct node *ReverseLinkedListHelper(struct node *head) {
    if (!head->nxt) {
        return head;
    }    
    struct node *n = NULL;
    n = ReverseLinkedListHelper(head->nxt);
    n->nxt = head;
    return n->nxt;
}

// Helper function, saves the pointer to the tail (new head) node
// and returns it after the helper function is done with the in-place
// reverse
struct node *ReverseLinkedList(struct node *head) {
    struct node *tail = head;
    while (tail->nxt) tail = tail->nxt;
    ReverseLinkedListHelper(head);
    return tail;
}
