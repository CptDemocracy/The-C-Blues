#include "PushDownStack.h"

int PushDownStackNew(struct PushDownStack* self) {
    if (!self) return 1;
    return LinkedListNew(&self->_list);
}

void PushDownStackDispose(struct PushDownStack* self) {
    if (!self) return;
    LinkedListDispose(&self->_list);
}

int PushDownStackPush(struct PushDownStack* self, int item) {
    if (!self) return 1;
    return LinkedListAddFirst(&self->_list, item);
}

int PushDownStackPop(struct PushDownStack* self, int* OutResult) {
    if (!self) return 1;
    if (LinkedListGetCount(&self->_list) < 1U) return 2;
    *OutResult = LinkedListGetFirst(&self->_list)->key;
    return LinkedListRemoveFirst(&self->_list);
}

int PushDownStackIsEmpty(struct PushDownStack* self) {
    return LinkedListGetCount(&self->_list) == 0U;
}
