/*************************************************************************
    > File Name: BinaryTree.c
    > Author: ldp
    > ################### 
    > Mail: ################### 
    > Created Time: Mon 08 Feb 2016 01:27:07 AM CST
    > 二叉查找樹
 ************************************************************************/
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////
//1.the define of tree
typedef int data_type;
typedef struct bst_node{
    data_type data;
    struct bst_node *lchild, *rchild;

}bst_t, *bst_p;
//it means bst_p is a pointer that point to the struct
////////////////////////////////////////////////////////
//2.the insert of tree
static bst_p search_bst_for_insert(bst_p *root, data_type key){
    bst_p s,p = *root;
    //the content of root is a struct
    
    //this loop find the minimum data of nodes of tree, and insert the new lchild as the minimum
    while(p){
        s = p;
        //means s and p are point to same memory
        if(p->data == key)
            return NULL;
        p = (key < p->data) ? p->lchild : p->rchild;

    }
    return s;
    //the type of return value is the same as line 20 : struct bst_p
}

void insert_bst_node (bst_p *root, data_type data){
    bst_p s, p;
    s = (bst_p)malloc(sizeof(struct bst_node));
    if(!s)
        perror("Allocate dynamic memory");

    s->data = data;
    s->lchild = NULL;
    s->rchild = NULL;

    if (*root == NULL)
        *root = s;
    else{
        p = search_bst_for_insert(root, data);
        if (p == NULL){
            fprintf(stderr, "The %d aleardy exits\n",data);
            free(s);
            return;

        }
        if (data < p->data)
            p->lchild = s;
        else
            p->rchild = s;
    }
}
////////////////////////////////////////////////////////////////
//3.traversal
static int print(data_type data){
    printf(" %d ", data);
    return 1;
}
//visit is a function point
int pre_order_traverse(bst_p root, int (*visit)(data_type)){
    if(root){
        if(visit(root->data)){
            if(pre_order_traverse(root->lchild, visit)){
                if(pre_order_traverse(root->rchild, visit))
                    return 1;
            }
        }
        return 0;
    }
    else
        return 1;
}

int in_order_traverse(bst_p root, int (*visit)(data_type data)){
    if(root){
        if(in_order_traverse(root->lchild, visit)){
            if(visit(root->data)){
                if(in_order_traverse(root->rchild, visit)){
                    return 1;

                }
            }
        }
        return 0;
    }
    else
        return 1;
}
int post_order_traverse(bst_p root, int (*visit)(data_type data)){
    if(root){
        if(post_order_traverse(root->lchild, visit)){
            if(post_order_traverse(root->rchild, visit)){
                if(visit(root->data)){
                    return 1;

                }
            }
        }
        return 0;
    }
    else
        return 1;
}
//////////////////////////////////////////////////////////////////
//4.delete
void delete_bst_node(bst_p  *root, data_type data){
    bst_p p = *root, parent, s;
    if(!p){
        fprintf(stderr, "notfound %d", data);
        return;
    }

    if(p->data == data){
        //it is a leaf node
        if(!p->rchild && !p->lchild){
            *root = NULL;
            free(p);

        }
        //the right child is NULL
        else if(!p->rchild){
            *root = p->lchild;
            free(p);

        }
        //the light child is NULL
        else if(!p->lchild){
            *root = p->rchild;
            free(p);

        }
        //the node has both children
        else{
            s = p->rchild;
            //the without left child
            if(!s->lchild){
                s->lchild = p->lchild;
                //the s have left child
            }
            else{
                //find the smallest node in the left subtree of s
                while(s->lchild){
                    parent = s;
                    s = s->lchild;
                }
                parent->lchild = s->rchild;
                s->lchild = p->lchild;
                s->rchild = p->rchild;
            }
            *root = s;
            free(p);

        }
    }
    else if(data > p->data){
        delete_bst_node(&(p->rchild), data);

    }
    else if(data < p->data){
        delete_bst_node(&(p->lchild), data);
    }
}

//main function
int main(int argc, char* argv[]){
    int i, num;
    bst_p root = NULL;

    if (argc < 2){
        fprintf(stderr, "useage:%s num\n", argv[0]);
        exit(-1);
    }
//atoi: can transfer a string to a lang int 
    num = atoi(argv[1]);
    data_type arr[num];
    printf("please inter %d integers:\n",num);
    for(i = 0; i<num; i++){
        scanf("%d", &arr[i]);
        insert_bst_node(&root, arr[i]);

    }

    printf("\n pre order traverse");
    pre_order_traverse(root, print);
    printf("\n post order traverse ");
    post_order_traverse(root, print);
    printf("\n");

    delete_bst_node(&root, 45);

    printf("\n pre order traverse");
    pre_order_traverse(root, print);
    printf("\n post order traverse ");
    post_order_traverse(root, print);
    printf("\n");

    return 0;
}

