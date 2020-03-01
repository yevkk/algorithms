#ifndef RED_BLACK_TREE_RB_NODE_HPP
#define RED_BLACK_TREE_RB_NODE_HPP

enum COLOR {RED = 0, BLACK};

template <typename DataType>
class RBNode {
private:
    COLOR _color;
    DataType* _data;
public:
    RBNode* parent;
    RBNode* left;
    RBNode* right;

    RBNode (DataType* data, RBNode* parentArg, RBNode* leftArg, RBNode* rightArg, COLOR color = RED):
    _data(data),
    parent(parentArg),
    left(leftArg),
    right(rightArg),
    _color(color) {};

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

    DataType* data() {
        return _data;
    };
};


#endif //RED_BLACK_TREE_RB_NODE_HPP
