#include <bits/stdc++.h>

template<class T>
class Node {
private:
    Node<T> *mLeft;
    Node<T> *mRight;
    T mValue;
public:
    explicit Node(T value) {
        setValue(value);
        setLeft((Node<T> *) nullptr);
        setRight((Node<T> *) nullptr);
    }

    Node<T> *getLeft() {
        return mLeft;
    }

    Node<T> *setLeft(Node<T> *node) {
        mLeft = node;
        return mLeft;
    }

    Node<T> *getRight() {
        return mRight;
    }

    Node<T> *setRight(Node<T> *node) {
        mRight = node;
        return mRight;
    }

    T getValue() {
        return mValue;
    }

    T setValue(T value) {
        mValue = value;
        return mValue;
    }
};


template<class T>
class Tree {
private:
    Node<T> *mRoot;

public:
    Tree() {
        setRoot(nullptr);
    }

    Node<T> *getRoot() {
        return mRoot;
    }

    Node<T> *setRoot(Node<T> *node) {
        mRoot = node;
    }

    Node<T> *insert(T value) {
        if (getRoot() == nullptr) {
            return setRoot(new Node<T>(value));
        }
        return insert(getRoot(), value);
    }

    Node<T> *insert(Node<T> *node, T value) {
        if (node == ((Node<T> *) nullptr)) {
            return new Node<T>(value);
        }
        if (value < node->getValue()) {
            node->setLeft(insert(node->getLeft(), value));
        } else {
            node->setRight(insert(node->getRight(), value));
        }
        return node;
    }

    Node<T> *searchByValue(T value) {
        return searchByValue(getRoot(), value);
    }

    Node<T> *searchByValue(Node<T> *node, T value) {
        if (node->getValue() == value) {
            return node;
        }
        if (value < node->getValue()) {
            return searchByValue(node->getLeft(), value);
        } else if (value > node->getValue()) {
            return searchByValue(node->getRight(), value);
        }
        return node;
    }

    void print(Node<T> *node) {
        if (node != (Node<T> *) nullptr) {
            print(node->getLeft());
            std::cout << node->getValue() << std::endl;
            print(node->getRight());
        }
    }

    void print() {
        print(getRoot());
    }

    void deleteByValue(T value) {
        deleteByValue(getRoot(), value);
    }

    Node<T> *getMinimumChildValue(Node<T> *node) {
        Node<T> *tmp = node;
        while (tmp->getLeft() != (Node<T> *) nullptr) {
            tmp = tmp->getLeft();
        }
        return tmp;
    }

    Node<T> *deleteByValue(Node<T> *node, T value) {

        if (node == (Node<T> *) nullptr) {
            return node;
        }

        if (value < node->getValue()) {
            node->setLeft(deleteByValue(node->getLeft(), value));
        } else if (value > node->getValue()) {
            node->setRight((deleteByValue(node->getRight(), value)));
        }

            /*Node to be deleted has two children: Find inorder successor of the node. Copy contents of the inorder
             * successor to the node and delete the inorder successor. Note that inorder predecessor can also be used.
             * The important thing to note is, inorder successor is needed only when right child is not empty.
             * In this particular case, inorder successor can be obtained by finding the minimum value in right child of
             * the node.*/
        else {
            //Node to be deleted has only one child: Copy the child to the node and delete the child
            if (node->getLeft() == (Node<T> *) nullptr) {
                Node<T> *tmp = node->getRight();
                delete (node);
                return tmp;
            } else if (node->getRight() == (Node<T> *) nullptr) {
                Node<T> *tmp = node->getLeft();
                delete (node);
                return tmp;
            }
            Node<T> *min = getMinimumChildValue(node->getRight());
            node->setValue(min->getValue());
            node->setRight(deleteByValue(node->getRight(), min->getValue()));
        }
        return node;
    }
};


int main() {
    std::vector<int> v = {6, 2, 1, 7, 7, 9, 4, 5, 0, 65, 43, 21};
    Tree<int> tree;
    for (int value:v) {
        tree.insert(value);
    }
    tree.print();
    printf("\n");
    tree.deleteByValue(4);
    tree.print();
    return 0;
}