#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct tnode {
    char* info;
    char* key;
    struct tnode *left;
    struct tnode *right;
    struct tnode* parent;
}tnode;
int add_nTree(tnode** root,char*key,char* info);
int del_nTree(tnode* root,char* key);
tnode* search_nTree(tnode* root,char* key);
void treeprint1(tnode *root);
void treeprint2(tnode *root);
void treeprint3(tnode *root);
tnode *create_node(char *key, char *info, tnode *parent) {
    tnode *node = calloc(1, sizeof(tnode));
    node->key = key;
    node->info = info;
    node->parent = parent;
    return node;
}

int add_nTree(tnode **root, char *key, char *info) {
    tnode *ptr = NULL;
    if ((*root) == NULL) {
        *root = create_node(key, info, NULL);
        return 0;
    }
    ptr = *root;
    while (ptr) {
        if (strcmp(key, ptr->key) > 0) {
            if (ptr->right) {
                ptr = ptr->right;
                continue;
            } else {
                ptr->right = create_node(key, info, ptr);
                return 0;
            }
        } else if (strcmp(key, ptr->key) < 0) {
            if (ptr->left) {
                ptr = ptr->left;
                continue;
            } else {
                ptr->left = create_node(key, info, ptr);
                return 0;
            }
        } else {
            perror("duplicate key");
            return -1;
        }
    }
    return 0;
}

tnode *search_nTree(tnode *root, char *key) {
    while (root) {
        if (strcmp(key, root->key) < 0) {
            root = root->left;
            continue;
        } else if (strcmp(key, root->key) > 0) {
            root = root->right;
            continue;
        } else {
            return root;
        }
    }
    return NULL;
}

tnode *getMaxNode(tnode *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

tnode *getMinNode(tnode *root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

void removeNodeByPtr(tnode *target) {
    if (target->left && target->right) {
        tnode *localMax = getMaxNode(target->left);
        target->key = localMax->key;
        removeNodeByPtr(localMax);
        return;
    } else if (target->left) {
        if (target == target->parent->left) {
            target->parent->left = target->left;
        } else {
            target->parent->right = target->left;
        }
    } else if (target->right) {
        if (target == target->parent->right) {
            target->parent->right = target->right;
        } else {
            target->parent->left = target->right;
        }
    } else {
        if (target == target->parent->left) {
            target->parent->left = NULL;
        } else {
            target->parent->right = NULL;
        }
    }
    free(target);
}

int del_nTree(tnode *root, char *key) {
    tnode *meow = search_nTree(root, key);
    removeNodeByPtr(meow);
}

/*префиксный обход*/
void treeprint1(tnode *root) {
    if (root != NULL) {
        printf("%s\n", root->key);
        treeprint1(root->left);
        treeprint1(root->right);
    }
}

/*инфиксный обход*/
void treeprint2(tnode *root) {
    if (root != NULL) {
        treeprint2(root->left);
        printf("%s\n", root->key);
        treeprint2(root->right);
    }
}

/*постфиксный обход*/
void treeprint3(tnode *root) {
    if (root != NULL) {
        treeprint3(root->left);
        treeprint3(root->right);
        printf("%s\n", root->key);
    }
}
int main() {
    tnode* tree;
    add_nTree(&tree,"bebra1","bebra1");
    add_nTree(&tree,"bebra2","bebra1");
    add_nTree(&tree,"bebra3","bebra1");
    add_nTree(&tree,"bebra4","bebra1");
    add_nTree(&tree,"bebra5","bebra1");
    add_nTree(&tree,"bebra6","bebra1");
    add_nTree(&tree,"bebra7","bebra1");
    treeprint1(tree);
    return 0;
}
