// https://codeforces.com/contest/1567/submission/127969832
// thanks to temmie

template <typename node> class Segtree {
	
public:
	
	int size, n_size;
	std::vector <node> v;
	
	Segtree(int _size) :
	n_size(_size)
	{
		assert(_size > 0);
		size = 1;
		while (size < _size) {
			size <<= 1;
		}
		v.resize(size << 1, node { });
		make();
	}
	
	template <typename A> Segtree(const std::vector <A>& _v) :
	n_size(_v.size())
	{
		assert(!_v.empty());
		size = 1;
		while (size < (int)_v.size()) {
			size <<= 1;
		}
		v.resize(size << 1, node { });
		make(_v);
	}
	
	template <typename A> Segtree(int _size, const std::vector <A>& _v) :
	n_size(_size)
	{
		assert(_size > 0);
		size = 1;
		while (size < _size) {
			size <<= 1;
		}
		v.resize(size << 1, node { });
		make(_v);
	}
	
	void make() {
		m_make(0, 0, size);
	}
	
	template <typename A> void make(const std::vector <A>& _v) {
		m_make(_v, 0, 0, size);
	}
	
	template <typename A> void update(int ind, const A& arg) {
		assert(ind >= 0 && ind < size);
		m_update(ind, 0, 0, size, arg);
	}
	
	node query(int l, int r) {
		assert(l >= 0 && l < r && r <= size);
		return m_query(l, r, 0, 0, size);
	}
	
	node query() {
		return query(0, n_size);
	}
	
	int find_first(int l, int r, const std::function <bool(const node&)>& check) {
		assert(l >= 0 && l < r && r <= size);
		return m_find_first(l, r, 0, 0, size, check);
	}
	
	int find_first(const std::function <bool(const node&)>& check) {
		return find_first(0, size, check);
	}
	
	int find_last(int l, int r, const std::function <bool(const node&)>& check) {
		assert(l >= 0 && l < r && r <= size);
		return m_find_last(l, r, 0, 0, size, check);
	}
	
	int find_last(const std::function <bool(const node&)>& check) {
		return find_last(0, size, check);
	}
	
private:
	
	inline int m_mid(int l, int r) {
		return (l + r) >> 1;
	}
	
	inline bool m_outside(int l, int r, int tl, int tr) {
		return l >= tr || r <= tl;
	}
	
	void m_make(int now, int l, int r) {
		if (!(r - l - 1)) {
			return;
		}
		int mid = m_mid(l, r);
		m_make((now << 1) + 1, l, mid);
		m_make((now << 1) + 2, mid, r);
		v[now] = node::merge(v[(now << 1) + 1], v[(now << 1) + 2]);
	}
	
	template <typename A> void m_make(const std::vector <A>& _v, int now, int l, int r) {
		if (!(r - l - 1)) {
			if (l < (int)_v.size()) {
				v[now].apply(_v[l]);
			}
			return;
		}
		int mid = m_mid(l, r);
		m_make(_v, (now << 1) + 1, l, mid);
		m_make(_v, (now << 1) + 2, mid, r);
		v[now] = node::merge(v[(now << 1) + 1], v[(now << 1) + 2]);
	}
	
	template <typename A> void m_update(int ind, int now, int l, int r, const A& arg) {
		if (!(r - l - 1)) {
			v[now].apply(arg);
			return;
		}
		int mid = m_mid(l, r);
		if (ind < mid) {
			m_update(ind, (now << 1) + 1, l, mid, arg);
		} else {
			m_update(ind, (now << 1) + 2, mid, r, arg);
		}
		v[now] = node::merge(v[(now << 1) + 1], v[(now << 1) + 2]);
	}
	
	node m_query(int tl, int tr, int now, int l, int r) {
		if (l >= tl && r <= tr) {
			return v[now];
		}
		int mid = m_mid(l, r);
		node ret { };
		if (m_outside(l, mid, tl, tr)) {
			ret = m_query(tl, tr, (now << 1) + 2, mid, r);
		} else {
			if (m_outside(mid, r, tl, tr)) {
				ret = m_query(tl, tr, (now << 1) + 1, l, mid);
			} else {
				ret = node::merge(
				m_query(tl, tr, (now << 1) + 1, l, mid),
				m_query(tl, tr, (now << 1) + 2, mid, r));
			}
		}
		return ret;
	}
	
	int m_find_first_exists(int now, int l, int r,
	const std::function <bool(const node&)>& check) {
		if (!(r - l - 1)) {
			return l;
		}
		int mid = m_mid(l, r);
		if (check(v[(now << 1) + 1])) {
			return m_find_first_exists((now << 1) + 1, l, mid, check);
		}
		return m_find_first_exists((now << 1) + 2, mid, r, check);
	}
	
	int m_find_first(int tl, int tr, int now, int l, int r,
	const std::function <bool(const node&)>& check) {
		if (l >= tl && r <= tr) {
			if (!check(v[now])) {
				return -1;
			}
			return m_find_first_exists(now, l, r, check);
		}
		int mid = m_mid(l, r);
		int ret = -1;
		if (!m_outside(l, mid, tl, tr)) {
			ret = m_find_first(tl, tr, (now << 1) + 1, l, mid, check);
		}
		if (!m_outside(mid, r, tl, tr) && ret == -1) {
			ret = m_find_first(tl, tr, (now << 1) + 2, mid, r, check);
		}
		return ret;
	}
	
	int m_find_last_exists(int now, int l, int r,
	const std::function <bool(const node&)>& check) {
		if (!(r - l - 1)) {
			return l;
		}
		int mid = m_mid(l, r);
		if (check(v[(now << 1) + 2])) {
			return m_find_last_exists((now << 1) + 2, mid, r, check);
		}
		return m_find_last_exists((now << 1) + 1, l, mid, check);
	}
	
	int m_find_last(int tl, int tr, int now, int l, int r,
	const std::function <bool(const node&)>& check) {
		if (l >= tl && r <= tr) {
			if (!check(v[now])) {
				return -1;
			}
			return m_find_last_exists(now, l, r, check);
		}
		int mid = m_mid(l, r);
		int ret = -1;
		if (!m_outside(mid, r, tl, tr)) {
			ret = m_find_last(tl, tr, (now << 1) + 2, mid, r, check);
		}
		if (!m_outside(l, mid, tl, tr) && ret == -1) {
			ret = m_find_last(tl, tr, (now << 1) + 1, l, mid, check);
		}
		return ret;
	}
	
};
 
struct Node {
	
	inline void apply(int x) {
	}
	
	static inline Node merge(const Node& a, const Node& b) {
	}
	
};
