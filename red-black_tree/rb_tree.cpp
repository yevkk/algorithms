#include "rb_tree.hpp"

RBTree::RBTree() {
    _nullNode = new RBNode(0);
    _nullNode->parent = _nullNode->left = _nullNode->right = _nullNode;
    _nullNode->setColor(BLACK);
    _nullNode->size = 0;
    _root = _nullNode;
}

RBNode *RBTree::nil() {
    return _nullNode;
}

RBNode *RBTree::root() {
    return _root;
}

void RBTree::printStep(RBNode *node, int level) {
    std::cout << '|';
    for (int i = 0; i < level; i++) {
        std::cout << '\t' << '|';
    }

    if (node == _nullNode) {
        std::cout << '*' << std::endl;
    } else {
        std::cout << osRank(node) << "| ";
        std::cout << node->data() << "   (c:" << node->color() << ", s:" << node->size << ")" << std::endl;
        printStep(node->left, level + 1);
        printStep(node->right, level + 1);
    }
}

void RBTree::print() {
    printStep(_root, 0);
}

void RBTree::transplant(RBNode *dst, RBNode *src) {
    if (dst->parent == _nullNode) {
        _root = src;
    } else if (dst == dst->parent->left) {
        dst->parent->left = src;
    } else {
        dst->parent->right = src;
    }
    if (src != _nullNode) {
        src->parent = dst->parent;
    }
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

RBNode *RBTree::predecessor(RBNode *node) {
    if (node->left != _nullNode) {
        return max(node->right);
    }
    RBNode *ptr = node->parent;
    while ((ptr != _nullNode) && (node == ptr->left)) {
        node = ptr;
        ptr = ptr->parent;
    }
    return ptr;
}

RBNode *RBTree::search(RBNode *root, int key) {
    if ((root == _nullNode) || (key == root->data())) {
        return root;
    }
    if (key < root->data()) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
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
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
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
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

void RBTree::insertNode(RBNode *node) {
    auto y = _nullNode;
    auto x = _root;
    while (x != _nullNode) {
        y = x;
        x->size++;
        if (node->data() < x->data()) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == _nullNode) {
        _root = node;
    } else if (node->data() < y->data()) {
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

void RBTree::deleteNode(RBNode *node) {
    RBNode *y = node;
    RBNode *x;

    RBNode *tmp = node;
    while (tmp != _nullNode) {
        tmp->size--;
        tmp = tmp->parent;
    }

    COLOR yInitColor = y->color();
    if (node->left == _nullNode) {
        x = node->right;
        transplant(node, node->right);
    } else if (node->right == _nullNode) {
        x = node->left;
        transplant(node, node->left);
    } else {
        y = min(node->right);
        yInitColor = y->color();
        x = y->right;
        if (y->parent == node) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        transplant(node, y);
        y->left = node->left;
        y->left->parent = y;
        y->setColor(node->color());
        y->size = node->size;
    }
    delete node;

    if (yInitColor == BLACK) {
        deleteFixup(x);
    }
}

void RBTree::deleteFixup(RBNode *node) {
    while ((node != _root) && (node->color() == BLACK)) {
        if (node == node->parent->left) {
            RBNode *w = node->parent->right;
            if (w->color() == RED) {
                w->setColor(BLACK);
                node->parent->setColor(RED);
                leftRotate(node->parent);
                w = node->parent->right;
            }
            if (w->left->color() == BLACK && w->right->color() == BLACK) {
                w->setColor(RED);
                node = node->parent;
            } else {
                if (w->right->color() == BLACK) {
                    w->left->setColor(BLACK);
                    w->setColor(RED);
                    rightRotate(w);
                    w = node->parent->right;
                }
                w->setColor(node->parent->color());
                node->parent->setColor(BLACK);
                w->right->setColor(BLACK);
                leftRotate(node->parent);
                node = _root;;
            };
        } else {
            RBNode *w = node->parent->left;
            if (w->color() == RED) {
                w->setColor(BLACK);
                node->parent->setColor(RED);
                rightRotate(node->parent);
                w = node->parent->left;
            }
            if (w->right->color() == BLACK && w->left->color() == BLACK) {
                w->setColor(RED);
                node = node->parent;
            } else {
                if (w->left->color() == BLACK) {
                    w->right->setColor(BLACK);
                    w->setColor(RED);
                    leftRotate(w);
                    w = node->parent->left;
                }
                w->setColor(node->parent->color());
                node->parent->setColor(BLACK);
                w->left->setColor(BLACK);
                rightRotate(node->parent);
                node = _root;;
            };
        }
    }
    node->setColor(BLACK);
}

RBNode *RBTree::osSelectStep(RBNode *root, int index) {
    int r = root->left->size + 1;
    if (index == r) {
        return root;
    } else if (index < r) {
        return osSelectStep(root->left, index);
    } else {
        return osSelectStep(root->right, index - r);
    }
}

RBNode *RBTree::osSelect(int index) {
    RBNode *res = osSelectStep(_root, index);
    return (res == _nullNode) ? nullptr : res;
}

int RBTree::osRank(RBNode *node) {
    int r = node->left->size + 1;
    RBNode *ptr = node;
    while (ptr != _root) {
        if (ptr == ptr->parent->right) {
            r += ptr->parent->left->size + 1;
        }
        ptr = ptr->parent;
    }
    return r;
}