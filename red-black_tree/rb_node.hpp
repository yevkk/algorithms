#ifndef RED_BLACK_TREE_RB_NODE_HPP
#define RED_BLACK_TREE_RB_NODE_HPP

enum COLOR {RED = 0, BLACK};

template <typename DataType>
class RBNode {
private:
    COLOR _color;
    RBNode* _parent;
    RBNode* _left;
    RBNode* _right;
    DataType* _data;
public:
    RBNode (DataType* data, RBNode* parent, RBNode* left, RBNode* right, COLOR color = RED):
    _data(data),
    _parent(parent),
    _left(left),
    _right(right),
    _color(color) {};

    static RBNode* createNullNode() {
        auto ptr = new RBNode(nullptr, nullptr, nullptr, nullptr, BLACK);
        ptr->_parent = ptr->_left = ptr->_right = ptr;
        return ptr;
    }

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

    RBNode* parent() {
        return _parent;
    };

    RBNode* left() {
        return _left;
    };

    RBNode* right() {
        return _right;
    };

    DataType* data() {
        return _data;
    };
};


#endif //RED_BLACK_TREE_RB_NODE_HPP
