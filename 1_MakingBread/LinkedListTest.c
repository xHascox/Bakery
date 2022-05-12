
#include "LinkedList.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    printf("just some testing with the Linked-List\n");

    // Create an empty list
    LinkedList* pList1 = CreateLinkedList(0, "Foo");
    assert(getLength(pList1) == 0);
    assert(strcmp(pList1->name, "Foo") == 0);

    // and one with some items
    LinkedList* pList2 = CreateLinkedList(4,"Bar");
    assert(strcmp(pList2->name, "Bar") == 0);
    assert(getLength(pList2) == 4);

    // Test removing some nodes
    assert(removeNode(pList1) == false);
    assert(getLength(pList1) == 0);

    assert(removeNode(pList2) == true);
    assert(getLength(pList2) == 3);
    assert(removeNode(pList2) == true);
    assert(getLength(pList2) == 2);
    assert(removeNode(pList2) == true);
    assert(getLength(pList2) == 1);
    assert(removeNode(pList2) == true);
    assert(getLength(pList2) == 0);
    assert(removeNode(pList2) == false);
    assert(getLength(pList2) == 0);

    // and add some nodes again
    appendNode(pList1);
    appendNode(pList1);
    appendNode(pList2);
    appendNode(pList2);
    assert(getLength(pList1) == 2);
    assert(getLength(pList2) == 2);

    // and cleanup
    DeleteLinkedList(pList1);
    DeleteLinkedList(pList2);

    printf("All tests passed fine\n");
}