#ifndef RED_BLACK_TREE_RB_NODE_HPP
#define RED_BLACK_TREE_RB_NODE_HPP

#include "department.hpp"

enum COLOR {
    RED = 0, BLACK
};

class RBNode {
private:
    COLOR _color;
    Student *_data;
public:
    RBNode *parent;
    RBNode *left;
    RBNode *right;

    explicit RBNode(Student *data) :
            _data(data),
            parent(nullptr),
            left(nullptr),
            right(nullptr),
            _color(RED) {};

    void switchColor() {
        if (_color == BLACK) {
            _color = RED;
        } else {
            _color = BLACK;
        }
    }

    void setColor(COLOR color) {
        _color = color;
    }

    COLOR color() {
        return _color;
    };

    Student* data() {
        return _data;
    };
};


#endif //RED_BLACK_TREE_RB_NODE_HPP
