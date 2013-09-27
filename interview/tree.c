// Author: Sriharsha Gangam

#include<stdio.h>

Object* Convert_Objects_To_tree (Object* head_object_ptr) {
    unsigned int N = number_of_elements(head_object_ptr); // Get number of elements
    Object* pointer_Array[N];
    unsigned int children_Count_Array[N];
    Object* root = NULL;

    // Create a table, a map of IDs and pointers.
    Object* curr = head_object_ptr;
    while (curr != NULL) {
        pointer_Array[curr->ID] = curr;
        children_Count_Array[curr->parent_ID] += 1;
        //set the root
        if (curr->parent_ID == 0)
            root = curr;
        curr = curr->next_ptr;
    }

    // Set TREE fields
    Object* curr = head_object_ptr;
    while (curr != NULL) {
        curr->parent_ptr = pointer_Array[curr->parent_ID];
        curr->child_count = children_Count_Array[curr->ID];
        curr->child_ptr_array = (Object **) malloc(curr->child_count * sizeof(Object*));
        curr = curr->next_ptr;
    }
    // initialize children.
    Object* curr = head_object_ptr;
    while (curr != NULL) {
        Object* parent_ptr = curr->parent_ptr;
        unsigned int children_count = children_Count_Array[curr->ID];
        parent_ptr->child_ptr_array[children_count - 1] = curr;
        children_Count_Array[curr->ID] --;
        curr = curr->next_ptr;
    }
    return root;
}

unsigned int number_of_elements(Object* head_object_ptr) {
    unsigned int N = 0;
    Object* curr = head_object_ptr;
    while (curr != NULL) {
        curr = curr->next_ptr;
        N++;
    }
    return N;
}

int main() {
    return 0;
}
