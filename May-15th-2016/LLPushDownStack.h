#ifndef PUSHDOWNSTACK_H_
#define PUSHDOWNSTACK_H_

#include "LinkedList.h"

struct PushDownStack {
	struct LinkedList _list;
};

int PushDownStackNew(struct PushDownStack* self);

void PushDownStackDispose(struct PushDownStack* self);

int PushDownStackPush(struct PushDownStack* self, int item);

int PushDownStackPop(struct PushDownStack* self, int* OutResult);

int PushDownStackIsEmpty(struct PushDownStack* self);

#endif /* PUSHDOWNSTACK_H_ */
