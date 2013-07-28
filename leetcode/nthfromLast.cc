/****
 * Author: Sriharsha Gangam
 *
 * Given a linked List given by the following definiton. Remove the Nth node from the last by a single pass.
 * The problem was tested with the data sets from Leetcode.com
 *
 * Keep two pointers. Move first one n + 1  positions ahead. 
 * Start second pointer from head and move both pointers until the first reaches NULL. 
 * The second pointer is n + 1 positions behind. So we call call removeNextNode. 
 * However, the first pointer can reach NULL after n positions head. In this case we remove the head.
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};



ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode* curr = head;            
    for(int i = 0; i < n ; i++) // move ahead n positions
        curr = curr->next;

    //Remove the head.
    if (curr == NULL) {
        ListNode* nextHead = head->next;
        free(head);
        return nextHead;
    }
    // Go ahead N + 1 positions.
    curr = curr->next;

    ListNode* prev = head;
    while (curr != NULL) {
        curr = curr->next;
        prev = prev->next;
    }

    removeNextNode(prev);
    return head;   
}

void removeNextNode (ListNode* node) {
    ListNode* nextNode = node->next;
    node->next = nextNode->next;
    free(nextNode);
}
