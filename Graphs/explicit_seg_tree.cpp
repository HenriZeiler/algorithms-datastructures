const int MAXN = 2*1e5;

template<typename ValueType, typename predicate>
struct explicitSegTree {
    void build(int cur, const vector<ll>& data, int l, int r) {
        if(l==r) {
            seg[cur] = data[l];
        }
        else {
            int mid=(l+r)/2;
            build(2*cur,data,l,mid);
            build(2*cur+1,data,mid+1,r);
            seg[cur] = pred(seg[2*cur],seg[2*cur+1]);
        }
    }
    void point_update(const int idx, const ValueType new_val, int cur_seg_idx, int l, int r) {
        if(l==r) seg[cur_seg_idx] = new_val;
        else {
            int mid = (l+r)/2;
            if(idx<=mid) point_update(idx,new_val,2*cur_seg_idx,l,mid);
            else         point_update(idx,new_val,2*cur_seg_idx+1,mid+1,r);
            seg[cur_seg_idx] = pred(seg[2*cur_seg_idx],seg[2*cur_seg_idx+1]);
        }
    }

    int lower_bound(const ValueType value, int cur_seg_idx=1) {
        if(cur_seg_idx>=n) return cur_seg_idx-n+1;
        if(seg[2*cur_seg_idx]>=value) return lower_bound(value,2*cur_seg_idx);
        else if(seg[2*cur_seg_idx+1]>=value) return lower_bound(value,2*cur_seg_idx+1);
        else return 0;
    }

    int upper_bound(const ValueType value, int cur_seg_idx=1) {
        if(cur_seg_idx>=n) return cur_seg_idx-n+1;
        if(seg[2*cur_seg_idx+1]>=value) return upper_bound(value,2*cur_seg_idx+1);
        else if(seg[2*cur_seg_idx]>=value) return upper_bound(value,2*cur_seg_idx);
        else return 0;
    }

    explicitSegTree(int n) : n(n) {};

    predicate pred;
    ValueType seg[4*MAXN];
    int n;
};