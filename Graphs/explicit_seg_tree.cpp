const int MAXN = 2 * 1e5;

template <typename ValueType, typename predicate> struct explicitSegTree {
  void build(int cur, const vector<ValueType> &data, int l, int r) {
    if (l == r) {
      seg[cur] = data[l];
    } else {
      int mid = (l + r) / 2;
      build(2 * cur, data, l, mid);
      build(2 * cur + 1, data, mid + 1, r);
      seg[cur] = pred(seg[2 * cur], seg[2 * cur + 1]);
    }
  }

  void build_from_seperate_idx_and_val(int cur, const vi &index_data,
                                       const vector<ValueType> &value_data,
                                       int l, int r) {
    if (l == r) {
      seg[cur] = value_data[index_data[l]];
    } else {
      int mid = (l + r) / 2;
      build_from_seperate_idx_and_val(2 * cur, index_data, value_data, l, mid);
      build_from_seperate_idx_and_val(2 * cur + 1, index_data, value_data,
                                      mid + 1, r);
      seg[cur] = pred(seg[2 * cur], seg[2 * cur + 1]);
    }
  }

  void point_update(const int idx, const ValueType new_val, int cur_seg_idx,
                    int l, int r) {
    if (l == r)
      seg[cur_seg_idx] = new_val;
    else {
      int mid = (l + r) / 2;
      if (idx <= mid)
        point_update(idx, new_val, 2 * cur_seg_idx, l, mid);
      else
        point_update(idx, new_val, 2 * cur_seg_idx + 1, mid + 1, r);
      seg[cur_seg_idx] = pred(seg[2 * cur_seg_idx], seg[2 * cur_seg_idx + 1]);
    }
  }

  ValueType lower_bound(const ValueType value, int cur_seg_idx = 1) {
    if (cur_seg_idx >= n)
      return cur_seg_idx - n + 1;
    if (seg[2 * cur_seg_idx] >= value)
      return lower_bound(value, 2 * cur_seg_idx);
    else if (seg[2 * cur_seg_idx + 1] >= value)
      return lower_bound(value, 2 * cur_seg_idx + 1);
    else
      return 0;
  }

  ValueType upper_bound(const ValueType value, int cur_seg_idx = 1) {
    if (cur_seg_idx >= n)
      return cur_seg_idx - n + 1;
    if (seg[2 * cur_seg_idx + 1] >= value)
      return upper_bound(value, 2 * cur_seg_idx + 1);
    else if (seg[2 * cur_seg_idx] >= value)
      return upper_bound(value, 2 * cur_seg_idx);
    else
      return 0;
  }

  ValueType get_pred_for_range(int v, int tl, int tr, int l, int r) {
    // WARNING: l <= r must be guaranteed in the initial function call
    if (l > r)
      return pred.neutral_element;
    if (l == tl && r == tr)
      return seg[v];
    int tm = (tl + tr) / 2;
    return pred(get_pred_for_range(v * 2, tl, tm, l, min(r, tm)),
                get_pred_for_range(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
  }

  ExplicitSegTree(int n) : n(n) { seg.resize(pow(2, ceil(log2(n)) + 1) + 1); };

  predicate pred;
  vector<ValueType> seg;
  int n;
};