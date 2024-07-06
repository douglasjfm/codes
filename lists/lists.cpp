#include <stdio.h>
#include <stdlib.h>

typedef struct SinglyLinkedListNode {
    int data;
    struct SinglyLinkedListNode* next;
}SinglyLinkedListNode;


int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {

    SinglyLinkedListNode *p1 = head1, *p2 = head2;
    int iFlagPass1 = 0, iFlagPass2 = 0;
    
    while (p1 && p2) {
        
        if ((p1->next == NULL) && (iFlagPass1 == 0)) {
            p1 = head2;
            iFlagPass1++;
        }
        else if ((p1->next == NULL) && (iFlagPass1 != 0)) {
            p1 = NULL; // end iter
            break;
        }
        else {
            p1 = p1->next;
        }
        
        if ((p2->next == NULL) && (iFlagPass2 == 0)) {
            p2 = head1;
            iFlagPass2++;
        }
        else if ((p2->next == NULL) && (iFlagPass2 != 0)) {
            p2 = NULL; // end iter
            break;
        }
        else {
            p2 = p2->next;
        }
        
        if (p1 == p2) {
            break;
        }
    }
    
    if (p1 == p2){
        return p1->data;
    }
    
    return -1;
}

SinglyLinkedListNode* insertANdCatchNew(SinglyLinkedListNode* h, int data, SinglyLinkedListNode **nNode) {
    if (!h) {
        h = (SinglyLinkedListNode*) malloc(sizeof(SinglyLinkedListNode));
        h->data = data;
        h->next = NULL;
        if (nNode) *nNode = h;
    } else {
        SinglyLinkedListNode* n, *p = h;
        n = (SinglyLinkedListNode*) malloc(sizeof(SinglyLinkedListNode));
        n->data = data;
        n->next = NULL;

        while (p->next) p = p->next;
        p->next = n;
        if (nNode) *nNode = n;
    }
    return h;
}

void freeList(SinglyLinkedListNode *p) {
    while(p->next){
        SinglyLinkedListNode *t = p;
        p = p->next;
        free(t);
    }
    free(p);
}

// Test code
int main (){
    SinglyLinkedListNode* h1 = NULL;
    SinglyLinkedListNode* h2 = NULL;
    SinglyLinkedListNode *p3;

    h1 = insertANdCatchNew(h1, 10, NULL);
    h1 = insertANdCatchNew(h1, 11, NULL);
    h1 = insertANdCatchNew(h1, 12, &p3); //Merge NOde
    h1 = insertANdCatchNew(h1, 13, NULL);
    h1 = insertANdCatchNew(h1, 14, NULL);


    h2 = insertANdCatchNew(h2, 20, NULL);
    h2->next = p3;

    printf("NODE: %d\n", findMergeNode(h1,h2));

    free(h2);
    freeList(h1);

    return 0;
}
