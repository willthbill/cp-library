template<class Int>
struct BIT { // all input should be 0-indexed, only supports sum-queries
    // one of the following may be used
        // rangequery: q(idx), q(a,b), add(idx,val), set(idx,Val), setupsingle(initial)
        // rangeupdate: q(idx), rangeadd(a,b,val), setuprange(initial)
    int n;
    vector<Int> arr, values;
    Int q(int idx){
        idx++; Int s = 0;
        while(idx>0) s+=arr[idx], idx-=(idx&(-idx));
        return s;
    }
    Int q(int a, int b){
        if(a == b) return values[a];
        return q(b)-q(a-1);
    }
    void add(int idx, Int val){
        values[idx]+=val;
        idx++;
        while(idx<n) arr[idx]+=val, idx+=(idx&(-idx));
    }
    void set(int idx, Int val){
        add(idx, val - values[idx]);
    }
    void rangeadd(int a, int b, Int val){
        add(a, val);
        if(b < n - 2) add(b + 1, -val);
    }
    BIT(){}
    void setup(int _n){
        n=_n+1, arr=vector<Int>(n), values=vector<Int> (_n);
    }
    BIT(int _n){
        setup(_n);
    }
    void setupsingle(vector<Int> initial){
        for(int i = 0; i < n - 1; i++) add(i,initial[i]);
    }
    void setuprange(vector<Int> initial){
        for(int i = 0; i < n - 1; i++) rangeadd(i,i,initial[i]);
    }
};