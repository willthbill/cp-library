// generates random integers on the range [l, r] (see constructor)
struct randint {
	random_device device;
	mt19937 generator;
	uniform_int_distribution<int> distribution;
	randint(int l, int r) {
		generator = mt19937(device());
		distribution = uniform_int_distribution<int>(l, r);
	}
	int get() {
		return distribution(generator);
	}
};

