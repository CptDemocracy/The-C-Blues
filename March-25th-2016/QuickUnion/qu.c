// Quick Union implementation in C
// inspired by a Java implementation of Robert Sedgewick
// in his course on algorithms:
// [ref.] coursera.org/course/algs4partI

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "qu.h"

int QuickUnionNew(struct QuickUnion* qu, int size) {
    if (qu == NULL) {
        return 1;
    }
    if (size < 0) {
        return 1;
    }
    
    if (!(qu->_nodes = malloc(size * sizeof(int)))) {
        return 1;
    }
    qu->_size = size;
    
    for (int i = size; i && (qu->_nodes[i - 1] = i - 1); --i) {
      continue;
    }
        
    return 0;
}

int QuickUnionDispose(struct QuickUnion* qu) {
    if (qu == NULL) {
        return 1;
    }
    free(qu->_nodes);
    return 0;
}

int QuickUnionGetRoot(struct QuickUnion* qu, int pid) {
    if (qu == NULL) {
        return -1;
    }
    if (pid < 0 || pid >= qu->_size) {
        return -1;
    }
    while (qu->_nodes[pid] != pid) {
        pid = qu->_nodes[pid];
    }
    return pid;
}

int QuickUnionConnect(struct QuickUnion* qu, int pid, int qid) {
    if (qu == NULL) {
        return 1;
    }
    if (pid < 0 || pid >= qu->_size) {
        return 1;
    }
    if (qid < 0 || qid >= qu->_size) {
        return 1;
    }
    int p = QuickUnionGetRoot(qu, pid);
    int q = QuickUnionGetRoot(qu, qid);
    qu->_nodes[q] = p;
    return 0;
}

int QuickUnionAreConnected(struct QuickUnion* qu, int pid, int qid) {
    if (qu == NULL) {
        return 0;
    }
    if (pid < 0 || pid >= qu->_size) {
        return 0;
    }
    if (qid < 0 || qid >= qu->_size) {
        return 0;
    }
    int p = QuickUnionGetRoot(qu, pid);
    int q = QuickUnionGetRoot(qu, qid);
    return p == q;
}
