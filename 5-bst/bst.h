//
//  bst.h
//  tarea5
//
//  Created by Isabel Vaca on 12/10/25.
//
#include <string>
#include <sstream>
#include <vector>
template <class T> class BST;

template <class T>
class TreeNode {
private:
    T value;
    TreeNode *left, *right;

    TreeNode<T>* predecesor();

public:
    TreeNode(T);
    TreeNode(T, TreeNode<T>*, TreeNode<T>*);
    void add(T);
    void remove(T);
    bool find(T)const;
    void inorder(std::stringstream&) const;
    void preorder(std::stringstream&) const;
    void postorder(std::stringstream&) const;
    void levelOrder(std::vector<std::vector<T>>& levels, int level) const;
    int height()const;

    

    friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val)
: value(val), left(0), right(0) {}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri)
: value(val), left(le), right(ri){}

template <class T>
void TreeNode<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            left->add(val);
        } else {
            left = new TreeNode<T>(val);
        }
    } else {
        if (right != 0) {
            right->add(val);
        } else {
            right = new TreeNode<T>(val);
        }
    }
}

template <class T>
TreeNode<T>* TreeNode<T>::predecesor() {
    TreeNode<T> *le, *ri;

    le = left;
    ri = right;

    if (left == 0) {
        if (right != 0) {
            right = 0;
        }
        return ri;
    }

    if (left->right == 0) {
        left = left->left;
        le->left = 0;
        return le;
    }

    TreeNode<T> *parent, *child;
    parent = left;
    child = left->right;
    while (child->right != 0) {
        parent = child;
        child = child->right;
    }
    parent->right = child->left;
    child->left = 0;
    return child;
}

template <class T>
void TreeNode<T>::remove(T val) {
    TreeNode<T> * succ, *old;

    if (val < value) {
        if (left != 0) {
            if (left->value == val) {
                old = left;
                succ = left->predecesor();
                if (succ != 0) {
                    succ->left = old->left;
                    succ->right = old->right;
                }
                left = succ;
                delete old;
            } else {
                left->remove(val);
            }
        }
    } else if (val > value) {
        if (right != 0) {
            if (right->value == val) {
                old = right;
                succ = right->predecesor();
                if (succ != 0) {
                    succ->left = old->left;
                    succ->right = old->right;
                }
                right = succ;
                delete old;
            } else {
                right->remove(val);
            }
        }
    }
}

template <class T>
bool TreeNode<T>::find( T val) const {
    if (val == value) return true;
    if (val < value)  return (left  != 0 && left->find(val));
      return (right != 0 && right->find(val));
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;
    if (right != 0) {
        right->inorder(aux);
    }
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
    aux << value;
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const {
        if (left != 0) {
            left->postorder(aux);
        }
        if (right != 0) {
            right->postorder(aux);
        }
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << value;
    }


template <class T>
void TreeNode<T>::levelOrder(std::vector<std::vector<T>>& levels, int level) const {
    if (levels.size() <= (size_t)level) {
        levels.push_back(std::vector<T>());
    }
    levels[level].push_back(value);
    if (left  != 0) left->levelOrder(levels, level + 1);
    if (right != 0) right->levelOrder(levels, level + 1);
}

template<class T>
int TreeNode<T>::height()const{
    int hl = (left  != 0) ? left->height()  : 0;
    int hr = (right != 0) ? right->height() : 0;
    int m;
    if (hl > hr) m = hl;
    else         m = hr;
    return 1 + m;
}


template <class T>
class BST {
private:
    TreeNode<T> *root;

public:
    BST();

    bool empty() const;
    void add(T);
    bool find(T) const;
    void remove(T);
    std::string inorder() const;
    std::string preorder() const;
    std::string postorder() const;
    std::string levelOrder() const;
    std::string visit() const;
    int height()const;
    std::string ancestors(T) const;
    int whatlevelamI(T)const;
};

template <class T>
BST<T>::BST() : root(0) {}



template <class T>
bool BST<T>::empty() const {
    return (root == 0);
}


template <class T>
bool BST<T>::find(T val) const {
    if (root != 0) {
        return root->find(val);
    } else {
        return false;
    }
}


template<class T>
void BST<T>::add(T val) {
    if (root != 0) {
            if (!root->find(val)) { 
                root->add(val);
            }
        } else {
            root = new TreeNode<T>(val);
        }
}


template <class T>
std::string BST<T>::inorder() const {
    std::stringstream aux;

    aux << "[";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
    std::stringstream aux;

    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->postorder(aux);
    }
    aux << "]";
    return aux.str();
}


template <class T>
std::string BST<T>::levelOrder() const {
    std::stringstream aux;
    aux << "[";

    if (root != 0) {
        std::vector<std::vector<T>> levels;
        root->levelOrder(levels, 0);

        for (int i = 0; i < levels.size(); ++i) {
            const std::vector<T>& lvl = levels[i];
            for (size_t j = 0; j < lvl.size(); ++j) {
                const T& x = lvl[j];
                if (aux.tellp() != 1) aux << " ";
                aux << x;
            }
        }
    }

    aux << "]";
    return aux.str();
}


template <class T>
std::string BST<T>::visit() const {
    std::stringstream aux;
    aux << preorder()   << "\n"
        << inorder()    << "\n"
        << postorder()  << "\n"
        << levelOrder();

    return aux.str();
}

template <class T>
int BST<T>::height()const{
    return (root == 0) ? 0 : root->height();


    }



template <class T>
std::string BST<T>::ancestors( T val) const {
    if (root == 0) return "[]";

    std::stringstream aux;
    aux << "[";

    TreeNode<T>* cur = root;
    while (cur != 0) {
        if (val == cur->value) {
            aux << "]";
            return aux.str();
        }
        if (aux.tellp() != 1) aux << " ";
        aux << cur->value;

        cur = (val < cur->value) ? cur->left : cur->right;
    }

  
    return "[]";
}

template <class T>
int BST<T>::whatlevelamI( T val) const {
    TreeNode<T>* cur = root;
    int level = 1;

    while (cur != 0) {
        if (val == cur->value) {
            return level;
        }
        cur = (val < cur->value) ? cur->left : cur->right;
        level++;
    }
    return -1;
}
