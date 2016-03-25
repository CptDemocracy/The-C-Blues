// Quick Union implementation in C
// inspired by a Java implementation of Robert Sedgewick
// in his course on algorithms:
// [ref.] coursera.org/course/algs4partI

struct QuickUnion {
    int  _size;
    int* _nodes;
};

int QuickUnionNew           (struct QuickUnion* qu, int size);
int QuickUnionDispose       (struct QuickUnion* qu);
int QuickUnionGetRoot       (struct QuickUnion* qu, int pid);
int QuickUnionConnect       (struct QuickUnion* qu, int pid, int qid);
int QuickUnionAreConnected  (struct QuickUnion* qu, int pid, int qid);
