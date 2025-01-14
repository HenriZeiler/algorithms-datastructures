struct Node {
  ll l_, r_;              // left and right bounds of the implicit segment
  ll val_ = 0, lazy_ = 0; // value of the segment
  Node *left_ = nullptr, *right_ = nullptr;
  bool isLeaf() { return l_ == r_; }
  void apply(ll v) {
    val_ += (r_ + 1 - l_) * v;
    lazy_ += v;
  }
  void push() {
    assert(left_ != nullptr);
    left_->apply(lazy_);
    right_->apply(lazy_);
    lazy_ = 0;
  }
  /**
   * \brief constructor that guarantees that children exist if !isLeaf
   */
  Node(ll l, ll r) : l_(l), r_(r) {
    val_ = 0;
    lazy_ = 0;
  }
};

template <typename Predicate> struct ImplicitSegTree {
  void point_update(const ll idx, const ll new_val, Node *cur_seg_node) {
    if (cur_seg_node->isLeaf())
      cur_seg_node->val_ = new_val;
    else {
      ll m = (cur_seg_node->l_ + cur_seg_node->r_) / 2;
      if (cur_seg_node->left_ == nullptr) {
        cur_seg_node->left_ = new Node(cur_seg_node->l_, m);
        cur_seg_node->right_ = new Node(m + 1, cur_seg_node->r_);
      }
      if (idx <= m)
        point_update(idx, new_val, cur_seg_node->left_);
      else
        point_update(idx, new_val, cur_seg_node->right_);
      cur_seg_node->val_ =
          pred(cur_seg_node->left_->val_, cur_seg_node->right_->val_);
    }
  }

  void range_update(const ll l, const ll r, const ll val, Node *cur_seg_node) {
    if (l > r) {
      return;
    } else if (l == cur_seg_node->l_ && r == cur_seg_node->r_) {
      cur_seg_node->apply(val);
    } else {
      ll m = (cur_seg_node->l_ + cur_seg_node->r_) / 2;
      if (cur_seg_node->left_ == nullptr) {
        cur_seg_node->left_ = new Node(cur_seg_node->l_, m);
        cur_seg_node->right_ = new Node(m + 1, cur_seg_node->r_);
      }
      cur_seg_node->push(); // not sure if this is neccessary
      range_update(l, min(m, cur_seg_node->left_->r_), val,
                   cur_seg_node->left_);
      range_update(m + 1, max(m + 1, cur_seg_node->right_->l_), val,
                   cur_seg_node->right_);
      cur_seg_node->val_ =
          pred(cur_seg_node->left_->val_, cur_seg_node->right_->val_);
    }
  }

  ll query(const ll ql, const ll qr, Node *cur_seg_node) {
    if (cur_seg_node->l_ == ql &&
        cur_seg_node->r_ == qr) { // potentially case in which l>r is missing
      return cur_seg_node->val_;
    } else if (cur_seg_node->isLeaf()) {
      return cur_seg_node->val_;
    } else {
      if (cur_seg_node->left_ == nullptr) {
        ll m = (cur_seg_node->l_ + cur_seg_node->r_) / 2;
        cur_seg_node->left_ = new Node(cur_seg_node->l_, m);
        cur_seg_node->right_ = new Node(m + 1, cur_seg_node->r_);
      }
      cur_seg_node->push();
      ll qm = (ql + qr) / 2;
      return pred(
          query(ql, min(qm, cur_seg_node->left_->r_), cur_seg_node->left_),
          query(max(qm + 1, cur_seg_node->right_->l_), qr,
                cur_seg_node->right_));
    }
  }

  void debug(Node *cur_seg_node) const {
    cur_seg_node->print();
    if (cur_seg_node->left_)
      debug(cur_seg_node->left_);
    if (cur_seg_node->right_)
      debug(cur_seg_node->right_);
  }

  ImplicitSegTree(ll n, Node *root) : n(n), root(root){};

  Predicate pred;
  ll n;
};