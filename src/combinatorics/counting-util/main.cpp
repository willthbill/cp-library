%include<number-theory/mod>%

struct CountingUtil {
    int maxInputSize, modulo;
    vector<int> factorials;
    CountingUtil(int _maxInputSize, int _modulo) {
        maxInputSize = _maxInputSize;
        modulo = _modulo;
        factorials = vector<int>(maxInputSize + 1);
        factorials[0] = 1;
        for(int i = 1; i <= maxInputSize; i++) {
            factorials[i] = i * factorials[i - 1] % modulo;
        }
    }
    int choose(int n, int k) {
        if(k > n || k < 0) return 0;
        return factorials[n] * mpow(factorials[n - k] * factorials[k] % modulo, modulo - 2, modulo) % modulo;
    }
    int permute(int n, int k) {
        if(k > n || k < 0) return 0;
        return factorials[n] * mpow(factorials[n - k], modulo - 2, modulo) % modulo;
    }
    int factorial(int n) {
        return factorials[n];
    }
};
