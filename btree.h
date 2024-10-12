#include <stdio.h>
#include <stdlib.h>

typedef struct BTree {
    int value;
    int leftDepth;
    int rightDepth;
    struct BTree* leftSubTree;
    struct BTree* rightSubTree;
} BTree;

BTree* init() {
    return NULL;
}

BTree* rotateClockwise(BTree* bTree) {
    BTree *leftBTree, *temp;
    leftBTree = bTree->leftSubTree;
    temp = leftBTree->rightSubTree;
    leftBTree->rightSubTree = bTree;
    bTree->leftSubTree = temp;

    if (!temp)
        bTree->leftDepth = 0;
    else if (temp->rightDepth > temp->leftDepth)
        bTree->leftDepth = temp->rightDepth + 1;
    else
        bTree->leftDepth = temp->leftDepth + 1;
    if (bTree->rightDepth > bTree->leftDepth)
        leftBTree->rightDepth = bTree->rightDepth + 1;
    else
        leftBTree->rightDepth = bTree->leftDepth + 1;
    return leftBTree;
}

BTree* rotateCounterclockwise(BTree* bTree) {
    BTree *rightBTree, *temp;
    rightBTree = bTree->rightSubTree;
    temp = rightBTree->leftSubTree;
    rightBTree->leftSubTree = bTree;
    bTree->rightSubTree = temp;

    if (!temp)
        bTree->rightDepth = 0;
    else if (temp->rightDepth > temp->leftDepth)
        bTree->rightDepth = temp->rightDepth + 1;
    else
            bTree->rightDepth = temp->leftDepth + 1;
    if (bTree->rightDepth > bTree->leftDepth)
        rightBTree->leftDepth = bTree->rightDepth + 1;
    else
        rightBTree->leftDepth = bTree->leftDepth + 1;
    return rightBTree;
}

BTree* balance(BTree* bTree) {
    int balanceFactor = bTree->rightDepth - bTree->leftDepth;

    if (balanceFactor > 1) {
        int balanceFactorRightSubTree = bTree->rightSubTree->rightDepth - bTree->rightSubTree->leftDepth;
        if (balanceFactorRightSubTree >= 0)
            bTree = rotateCounterclockwise(bTree);
        else {
            bTree->rightSubTree = rotateClockwise(bTree->rightSubTree);
            bTree = rotateCounterclockwise(bTree);
        }
    } else {
        if (balanceFactor < -1) {
        int balanceFactorLeftSubTree = bTree->leftSubTree->rightDepth - bTree->leftSubTree->leftDepth;
        if (balanceFactorLeftSubTree <= 0)
            bTree = rotateClockwise(bTree);
        else {
            bTree->leftSubTree = rotateCounterclockwise(bTree->leftSubTree);
            bTree = rotateClockwise(bTree);
        }
    }
    }
    return bTree;
}

BTree* updateDepths(BTree* bTree) {
    if (bTree) {
        bTree->leftSubTree = updateDepths(bTree->leftSubTree);
        if (!bTree->leftSubTree)
            bTree->leftDepth = 0;
        else if (bTree->leftSubTree->leftDepth > bTree->leftSubTree->rightDepth)
            bTree->leftDepth = bTree->leftSubTree->leftDepth + 1;
        else
            bTree->leftDepth = bTree->leftSubTree->rightDepth + 1;
        bTree->rightSubTree = updateDepths(bTree->rightSubTree);
        if (!bTree->rightSubTree)
            bTree->rightDepth = 0;
        else if (bTree->rightSubTree->leftDepth > bTree->rightSubTree->rightDepth)
            bTree->rightDepth = bTree->rightSubTree->leftDepth + 1;
        else
            bTree->rightDepth = bTree->rightSubTree->rightDepth + 1;
        bTree = balance(bTree);
    }
    return bTree;
}

BTree* insertNode(BTree* bTree, int value) {
    if (!bTree) {
        bTree = malloc(sizeof(BTree));
        bTree->value = value;
        bTree->leftSubTree = NULL;
        bTree->rightSubTree = NULL;
        bTree->rightDepth = 0;
        bTree->leftDepth = 0;
    } else if (value < bTree->value) {
        bTree->leftSubTree = insertNode(bTree->leftSubTree, value);
        if (bTree->leftSubTree->rightDepth > bTree->leftSubTree->leftDepth)
            bTree->leftDepth = bTree->leftSubTree->rightDepth + 1;
        else
            bTree->leftDepth = bTree->leftSubTree->leftDepth + 1;
        bTree = balance(bTree);
    } else {
        bTree->rightSubTree = insertNode(bTree->rightSubTree, value);
        if (bTree->rightSubTree->rightDepth > bTree->rightSubTree->leftDepth)
            bTree->rightDepth = bTree->rightSubTree->rightDepth + 1;
        else
            bTree->rightDepth = bTree->rightSubTree->leftDepth + 1;
        bTree = balance(bTree);
    }
    return bTree;
}

BTree* removeNode(BTree* bTree, int value) {
    if (bTree) {
        if (value == bTree->value) {
            if (!bTree->leftSubTree && !bTree->rightSubTree)
                return NULL;
            if (!bTree->leftSubTree)
                return bTree->rightSubTree;
            else {
                if (!bTree->rightSubTree)
                    return bTree->leftSubTree;
                else {
                    BTree *aux, *ref;
                    ref = bTree->rightSubTree;
                    aux = ref;
                    while (aux->leftSubTree)
                        aux = aux->leftSubTree;
                    aux->leftSubTree = bTree->leftSubTree;
                    return ref;
                }
            }
        }
        else {
            if (value < bTree->value)
                bTree->leftSubTree = removeNode(bTree->leftSubTree, value);
            else
                bTree->rightSubTree = removeNode(bTree->rightSubTree, value);
        }
    }
    return bTree;
}

BTree* search(BTree* bTree, int value) {
    if (bTree) {
        if (bTree->value == value)
            return bTree;
        else {
            if (value > bTree->value)
                bTree = search(bTree->rightSubTree, value);
            else
                bTree = search(bTree->leftSubTree, value);
        }
    }
    return bTree;
}

void traverse(BTree* bTree) {
    if (bTree) {
        traverse(bTree->leftSubTree);
        printf("%d ", bTree->value);
        traverse(bTree->rightSubTree);
    }
}