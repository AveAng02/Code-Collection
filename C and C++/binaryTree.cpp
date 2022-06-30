#include <iostream>
#include <queue>

// pointer to pointer method is more effecient for binary tree
// create a tree and binary tree class 
// under a DSA library

struct node{
    int data;
    node* leftChild;
    node* rightChild;
};

node* createNewNode(int data){
    node* newNode = new node();
    (*newNode).data = data;
    (*newNode).leftChild = (*newNode).rightChild = NULL;
    return newNode;
}

node* insert(node* hook, int data){
    if(hook == NULL){
        hook = createNewNode(data);
    }
    else if(hook->data > data){
        hook->leftChild = insert(hook->leftChild, data);
    }
    else if(hook->data < data){
        hook->rightChild = insert(hook->rightChild, data);
    }
    else{
        std::cout << "ERROR!! in insert section!" << hook->data << data << std::endl;
    }
    return hook;
}

node* search(node* hook, int data){
    if(hook == NULL){
        return NULL;
    }
    else if((hook->leftChild)->data == data || (hook->rightChild)->data == data){
        return hook;
    }
    else if(hook->data > data){
        return search(hook->leftChild, data);
    }
    else if(hook->data < data){
        return search(hook->rightChild, data);
    }
    else{
        std::cout << "Error!! In search function!" << std::endl;
        return NULL;
    }
}

int Minimum(node* hook){
    if(hook == NULL){
        return -1;
    }
    else if(hook->leftChild == NULL){
        return hook->data;
    }
    else{
        return Minimum(hook->leftChild);
    }
}

node* minimum(node* hook){
    if(hook == NULL){
        return hook;
    }
    else if(hook->leftChild == NULL){
        return hook;
    }
    else{
        return minimum(hook->leftChild);
    }
}

int maximum(node* hook){
    if(hook == NULL){
        return -1;
    }
    else if(hook->rightChild == NULL){
        return hook->data;
    }
    else{
        return maximum(hook->rightChild);
    }
}

int height(node* hook){
    if(hook == NULL){
        return -1;
    }
    else if(height(hook->leftChild) > height(hook->rightChild)){
        return height(hook->leftChild) + 1;
    }
    else{
        return height(hook->rightChild) + 1;
    }
}

//Breadth first traversal is level order traversal
void BFT(node* hook){
    if(hook == NULL){
        return;
    }

    std::queue<node*> q;
    node* front = NULL;

    q.push(hook);

    while(!q.empty()){
        front = q.front();

        std::cout << front->data << std::endl;

        if(front->leftChild != NULL){
            q.push(front->leftChild);
        }
        if(front->rightChild != NULL){
            q.push(front->rightChild);
        }
        q.pop();
    }
}

/*
 * Depth first search is of three types:
 ** preorder <root><left><right>
 ** inorder <left><root><right>
 ** postorder <left><right><root>
 */

void DFT_preorder(node* hook){
    if(hook == NULL){
        return;
    }
    
    std::cout << hook->data << std::endl;
    DFT_preorder(hook->leftChild);
    DFT_preorder(hook->rightChild);
}

void DFT_inorder(node* hook){
    if(hook == NULL){
        return;
    }
    
    DFT_preorder(hook->leftChild);
    std::cout << hook->data << std::endl;
    DFT_preorder(hook->rightChild);
}

void DFT_postorder(node* hook){
    if(hook == NULL){
        return;
    }
    
    DFT_postorder(hook->leftChild);
    DFT_postorder(hook->rightChild);
    std::cout << hook->data << std::endl;
}

bool isBST(node* hook){
    if(hook == NULL || hook->leftChild == NULL || hook->rightChild == NULL){
        return true;
    }

    if(isBST(hook->leftChild) == true && isBST(hook->rightChild) == true && maximum(hook->leftChild) <= hook->data && hook->data <= Minimum(hook->rightChild)){
        return true;
    }
    else{
        return false;
    }
}

node* deleteNode(node* hook, int data){
    
    node* result = hook;
    
    if(result == NULL){
        return hook;
    }
    else if(data > hook->data){
        hook->rightChild = deleteNode(hook->rightChild, data);
    }
    else if(data < hook->data){
        hook->leftChild = deleteNode(hook->leftChild, data);
    }
    else{ // when the node is found
        if(hook->leftChild == NULL && hook->rightChild == NULL){
            delete hook;
            return NULL;    
        }
        else if(hook->leftChild == NULL){
            hook = hook->rightChild;
            delete result;
        }
        else if(hook->rightChild == NULL){
            hook = hook->leftChild;
            delete result;
        }
        else{ // for when both sides have data
            result = minimum(hook);
            hook->data = result->data;
            hook->rightChild = deleteNode(hook->rightChild, hook->data);
        }
    }

    return hook;
}


int main() {

    node* root = NULL;

    int arr[12] = {8, 4, 11, 2, 6, 10, 9, 13, 12, 14, 5, 3};

    for(int i = 0; i < 12; i++){
        root = insert(root, arr[i]);
    }

    BFT(root);

    root = deleteNode(root, 9);

    std::cout << "after deleting 9:\n";
    BFT(root);

    root = deleteNode(root, 6);

    std::cout << "after deleting 6:\n";
    BFT(root);

    root = deleteNode(root, 4);

    std::cout << "after deleting 4:\n";
    BFT(root);

    return 0;
}








