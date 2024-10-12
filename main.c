#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int main () {

    BTree* bTree = init();

    bTree = insertNode(bTree, 310);
    bTree = insertNode(bTree, 412);
    bTree = insertNode(bTree, 4000);
    bTree = insertNode(bTree, 3510);
    bTree = insertNode(bTree, 2614);
    bTree = insertNode(bTree, 2915);
    bTree = insertNode(bTree, 3738);
    bTree = insertNode(bTree, 3601);
    bTree = insertNode(bTree, 4114);
    bTree = insertNode(bTree, 1121);
    bTree = insertNode(bTree, 3197);
    bTree = insertNode(bTree, 522);

    bTree = removeNode(bTree, 3601);
    bTree = removeNode(bTree, 4114);
    bTree = removeNode(bTree, 522);

    bTree = updateDepths(bTree);

    printf("%s\n", "#############################");
    printf("%s", "# Traverse (in ascending order): ");
    traverse(bTree);

    printf("\n%s\n", "#############################");
    printf("%s", "# Left depth (from root): ");
    printf("%d\n", bTree->leftDepth);
    printf("%s\n", "#############################");
    printf("%s", "# Right depth (from root): ");
    printf("%d\n", bTree->rightDepth);

    int sought = 12;
    BTree* found = search(bTree, sought);
    printf("%s\n", "#############################");
    printf("# Found %d? %d\n", sought, found? found->value : 0);

    sought = 1121;
    found = search(bTree, sought);
    printf("%s\n", "#############################");
    printf("# Found %d? %d\n", sought, found? found->value : 0);
    printf("%s\n", "#############################");

    return 0;
}