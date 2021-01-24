#include <iostream>
#include <queue>
#include <cassert>
using namespace std;
typedef int type;
class BinaryTree
{
    struct Node
    {
        type item;
        Node* left;
        Node* right;
    };
    Node* root;
    void PreOrder(Node *p)
    {
        if(p!=NULL)
            cout<<p->item<<" ";
        PreOrder(p->left);
        PreOrder(p->right);
    }
    void InOrder(Node *p)
    {
        if(p!=NULL)
            InOrder(p->left);
        cout<<p->item<<" ";
        InOrder(p->right);
    }
    void PostOrder(Node *p)
    {
        if(p!=NULL)
            PostOrder(p->left);
        PostOrder(p->right);
        cout<<p->item<<" ";
    }
    void LevelOrder(Node *root)
    {
        if(root==NULL) return;
        queue <Node*> Q;
        Q.push(root);
        while(!Q.empty())
        {
            Node* curr=Q.front();
            cout<<curr->item<<" ";
            if(curr->left!=NULL)
                Q.push(curr->left);
            if(curr->right!=NULL)
                Q.push(curr->right);
            Q.pop();
        }
    }
    int NodeCount(Node *p)
    {
        if(p==NULL) return 0;
        return 1+NodeCount(p->left)+NodeCount(p->right);
    }
     void Clear(Node* &p)
    {
        if(p != NULL)
        {
            Clear(p->left);
            Clear(p->right);
            delete p;
            p = NULL;
        }
    }
public:
    BinaryTree()
    {
        root=NULL;
    }
    ~BinaryTree()
    {
        Clear(root);
    }
    bool IsEmpty()
    {
        return root==NULL;
    }
    void InorderTraversal()
    {
        InOrder(root);
    }
    void PreorederTraversal()
    {
        PreOrder(root);
    }
    void PostorderTraversal()
    {
        PostOrder(root);
    }
    int TreeNodeCount()
    {
        return NodeCount(root);
    }
    int LeavesCount(Node *p)
    {
        if(p==NULL) return 0;
        else if((p->left==NULL) && (p->right==NULL)) return 1;
        else return LeavesCount(p->left) + LeavesCount(p->right);
    }
    void ClearTree()
    {
        Clear(root);
    }
    bool Search(type Element)
    {
        Node *current = root;

        while(current != NULL)
        {
            if(current->item == Element)
                return true;
            else if(current->item > Element)
                current = current->left;
            else
                current = current->right;
        }

        return false;
    }
    void Insert(type Element)
    {
        Node *current;
        Node *trailCurrent;
        Node *NewNode;

        NewNode = new Node;
        assert(NewNode != NULL);
        NewNode->item = Element;
        NewNode->left = NULL;
        NewNode->right = NULL;

        if(root == NULL)
            root = NewNode;
        else
        {
            current = root;

            while(current != NULL)
            {
                trailCurrent = current;

                if(current->item == Element)
                {
                    cout<<"The insert item is already in the list -- ";
                    cout<<"duplicates are not allowed."<<endl;
                    return;
                }
                else if(current->item > Element)
                    current = current->left;
                else
                    current = current->right;
            }
            if(trailCurrent->item > Element)
                trailCurrent->left = NewNode;
            else
                trailCurrent->right = NewNode;
        }
    }
    void Remove(type Element)
    {
        Node *current;
        Node *trailCurrent;

        if(root == NULL)
        {
            cout<<"Cannot delete from the empty tree."<<endl;
            return;
        }
        if(root->item == Element)
        {
            deleteFromTree(root);
            return;
        }

        trailCurrent = root;

        if(root->item > Element)
            current = root->left;
        else
            current = root->right;

        while(current != NULL)
        {
            if(current->item == Element)
                break;
            else
            {
                trailCurrent = current;
                if(current->item > Element)
                    current = current->left;
                else
                    current = current->right;
            }
        }
        if(current == NULL)
            cout<<"The delete item is not in the tree."<<endl;
        else if(trailCurrent->item > Element)
            deleteFromTree(trailCurrent->left);
        else
            deleteFromTree(trailCurrent->right);
    }
    void deleteFromTree(Node* &p)
    {
        Node *current;
        Node *trailCurrent;
        Node *temp;

        if(p->left == NULL && p->right == NULL)
        {
            delete p;
            p = NULL;
        }
        else if(p->left == NULL)
        {
            temp = p;
            p = p->right;
            delete temp;
        }
        else if(p->right == NULL)
        {
            temp = p;
            p = p->left;
            delete temp;
        }
        else
        {
            current = p->left;
            trailCurrent = NULL;

            while(current->right != NULL)
            {
                trailCurrent = current;
                current = current->right;
            }

            p->item = current->item;

            if(trailCurrent == NULL)
                p->left = current->left;
            else
                trailCurrent->right = current->left;

            delete current;
        }
    }

};

int main()
{
    BinaryTree B;
    B.Insert(20);
    B.Insert(10);
    B.Insert(15);
    B.ClearTree();
    cout<<B.IsEmpty();
    return 0;
}
