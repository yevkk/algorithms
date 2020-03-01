#include "rb_tree.hpp"

RBTree::RBTree() {
    _nullNode = new RBNode(nullptr);
    _nullNode->parent = _nullNode->left = _nullNode->right = _nullNode;
    _nullNode->setColor(BLACK);
    _root = _nullNode;
}

void RBTree::printNode(RBNode *node, int level) {
    if (node == _nullNode) return;

    std::cout << '|';
    for (int i = 0; i < level; i++) {
        std::cout << '\t' << '|';
    }
    std::cout << *(node->data()) << "   (" << node->color() << ")" << std::endl;
    printNode(node->left, level + 1);
    printNode(node->right, level + 1);
}

void RBTree::print() {
    printNode(_root, 0);
}

RBNode *RBTree::min(RBNode *root) {
    RBNode *ptr = root;
    while (ptr->left != _nullNode) {
        ptr = ptr->left;
    }
    return ptr;
}

RBNode *RBTree::max(RBNode *root) {
    RBNode *ptr = root;
    while (ptr->right != _nullNode) {
        ptr = ptr->right;
    }
    return ptr;
}

RBNode *RBTree::successor(RBNode *node) {
    if (node->right != _nullNode) {
        return min(node->right);
    }
    RBNode *ptr = node->parent;
    while ((ptr != _nullNode) && (node == ptr->right)) {
        node = ptr;
        ptr = ptr->parent;
    }
    return ptr;
}

void RBTree::leftRotate(RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;

    if (y->left != _nullNode) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == _nullNode) {
        _root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(RBNode *x) {
    RBNode *y = x->left;
    x->left = y->right;

    if (y->right != _nullNode) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == _nullNode) {
        _root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

void RBTree::insert(RBNode *node) {
    auto y = _nullNode;
    auto x = _root;
    while (x != _nullNode) {
        y = x;
        if (*(node->data()) < *(x->data())) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == _nullNode) {
        _root = node;
    } else if (*(node->data()) < *(y->data())) {
        y->left = node;
    } else {
        y->right = node;
    }
    node->left = node->right = _nullNode;
    node->setColor(RED);
    insertFixup(node);
}

void RBTree::insertFixup(RBNode *node) {
    while (node->parent->color() == RED) {
        if (node->parent == node->parent->parent->left) {
            RBNode *y = node->parent->parent->right;
            if (y->color() == RED) {
                node->parent->setColor(BLACK);
                y->setColor(BLACK);
                node->parent->parent->setColor(RED);
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->setColor(BLACK);
                node->parent->parent->setColor(RED);
                rightRotate(node->parent->parent);
            }
        } else {
            RBNode *y = node->parent->parent->left;
            if (y->color() == RED) {
                node->parent->setColor(BLACK);
                y->setColor(BLACK);
                node->parent->parent->setColor(RED);
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->setColor(BLACK);
                node->parent->parent->setColor(RED);
                leftRotate(node->parent->parent);
            }
        }
    }
    _root->setColor(BLACK);
}
