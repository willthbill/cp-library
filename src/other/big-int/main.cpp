// NUMBER-LIKE ARRAY ===============================================================================
#define NULL 0

template <class Blk>
class NumberlikeArray {
public:

	// Type for the index of a block in the array
	typedef unsigned int Index;
	// The number of bits in a block, defined below.
	static const unsigned int N;

	// The current allocated capacity of this NumberlikeArray (in blocks)
	Index cap;
	// The actual length of the value stored in this NumberlikeArray (in blocks)
	Index len;
	// Heap-allocated array of the blocks (can be NULL if len == 0)
	Blk *blk;

	// Constructs a ``zero'' NumberlikeArray with the given capacity.
	NumberlikeArray(Index c) : cap(c), len(0) { 
		blk = (cap > 0) ? (new Blk[cap]) : NULL;
	}

	/* Constructs a zero NumberlikeArray without allocating a backing array.
	 * A subclass that doesn't know the needed capacity at initialization
	 * time can use this constructor and then overwrite blk without first
	 * deleting it. */
	NumberlikeArray() : cap(0), len(0) {
		blk = NULL;
	}

	// Destructor.  Note that `delete NULL' is a no-op.
	~NumberlikeArray() {
		delete [] blk;
	}

	/* Ensures that the array has at least the requested capacity; may
	 * destroy the contents. */
	void allocate(Index c);

	/* Ensures that the array has at least the requested capacity; does not
	 * destroy the contents. */
	void allocateAndCopy(Index c);

	// Copy constructor
	NumberlikeArray(const NumberlikeArray<Blk> &x);

	// Assignment operator
	void operator=(const NumberlikeArray<Blk> &x);

	// Constructor that copies from a given array of blocks
	NumberlikeArray(const Blk *b, Index blen);

	// ACCESSORS
	Index getCapacity()     const { return cap;      }
	Index getLength()       const { return len;      }
	Blk   getBlock(Index i) const { return blk[i];   }
	bool  isEmpty()         const { return len == 0; }

	/* Equality comparison: checks if both objects have the same length and
	 * equal (==) array elements to that length.  Subclasses may wish to
	 * override. */
	bool operator ==(const NumberlikeArray<Blk> &x) const;

	bool operator !=(const NumberlikeArray<Blk> &x) const {
		return !operator ==(x);
	}
};

/* BEGIN TEMPLATE DEFINITIONS.  They are present here so that source files that
 * include this header file can generate the necessary real definitions. */

template <class Blk>
const unsigned int NumberlikeArray<Blk>::N = 8 * sizeof(Blk);

template <class Blk>
void NumberlikeArray<Blk>::allocate(Index c) {
	// If the requested capacity is more than the current capacity...
	if (c > cap) {
		// Delete the old number array
		delete [] blk;
		// Allocate the new array
		cap = c;
		blk = new Blk[cap];
	}
}

template <class Blk>
void NumberlikeArray<Blk>::allocateAndCopy(Index c) {
	// If the requested capacity is more than the current capacity...
	if (c > cap) {
		Blk *oldBlk = blk;
		// Allocate the new number array
		cap = c;
		blk = new Blk[cap];
		// Copy number blocks
		Index i;
		for (i = 0; i < len; i++)
			blk[i] = oldBlk[i];
		// Delete the old array
		delete [] oldBlk;
	}
}

template <class Blk>
NumberlikeArray<Blk>::NumberlikeArray(const NumberlikeArray<Blk> &x)
		: len(x.len) {
	// Create array
	cap = len;
	blk = new Blk[cap];
	// Copy blocks
	Index i;
	for (i = 0; i < len; i++)
		blk[i] = x.blk[i];
}

template <class Blk>
void NumberlikeArray<Blk>::operator=(const NumberlikeArray<Blk> &x) {
	/* Calls like a = a have no effect; catch them before the aliasing
	 * causes a problem */
	if (this == &x)
		return;
	// Copy length
	len = x.len;
	// Expand array if necessary
	allocate(len);
	// Copy number blocks
	Index i;
	for (i = 0; i < len; i++)
		blk[i] = x.blk[i];
}

template <class Blk>
NumberlikeArray<Blk>::NumberlikeArray(const Blk *b, Index blen)
		: cap(blen), len(blen) {
	// Create array
	blk = new Blk[cap];
	// Copy blocks
	Index i;
	for (i = 0; i < len; i++)
		blk[i] = b[i];
}

template <class Blk>
bool NumberlikeArray<Blk>::operator ==(const NumberlikeArray<Blk> &x) const {
	if (len != x.len)
		// Definitely unequal.
		return false;
	else {
		// Compare corresponding blocks one by one.
		Index i;
		for (i = 0; i < len; i++)
			if (blk[i] != x.blk[i])
				return false;
		// No blocks differed, so the objects are equal.
		return true;
	}
}

// BIG UNSIGNED ====================================================================================
class BigUnsigned : protected NumberlikeArray<unsigned long> {

public:
	// Enumeration for the result of a comparison.
	enum CmpRes { less = -1, equal = 0, greater = 1 };

	// BigUnsigneds are built with a Blk type of unsigned long.
	typedef unsigned long Blk;

	typedef NumberlikeArray<Blk>::Index Index;
	NumberlikeArray<Blk>::N;

protected:
	// Creates a BigUnsigned with a capacity; for internal use.
	BigUnsigned(int, Index c) : NumberlikeArray<Blk>(0, c) {}

	// Decreases len to eliminate any leading zero blocks.
	void zapLeadingZeros() { 
		while (len > 0 && blk[len - 1] == 0)
			len--;
	}

public:
	// Constructs zero.
	BigUnsigned() : NumberlikeArray<Blk>() {}

	// Copy constructor
	BigUnsigned(const BigUnsigned &x) : NumberlikeArray<Blk>(x) {}

	// Assignment operator
	void operator=(const BigUnsigned &x) {
		NumberlikeArray<Blk>::operator =(x);
	}

	// Constructor that copies from a given array of blocks.
	BigUnsigned(const Blk *b, Index blen) : NumberlikeArray<Blk>(b, blen) {
		// Eliminate any leading zeros we may have been passed.
		zapLeadingZeros();
	}

	// Destructor.  NumberlikeArray does the delete for us.
	~BigUnsigned() {}
	
	// Constructors from primitive integer types
	BigUnsigned(unsigned long  x);
	BigUnsigned(         long  x);
	BigUnsigned(unsigned int   x);
	BigUnsigned(         int   x);
	BigUnsigned(unsigned short x);
	BigUnsigned(         short x);
protected:
	// Helpers
	template <class X> void initFromPrimitive      (X x);
	template <class X> void initFromSignedPrimitive(X x);
public:

	/* Converters to primitive integer types
	 * The implicit conversion operators caused trouble, so these are now
	 * named. */
	unsigned long  toUnsignedLong () const;
	long           toLong         () const;
	unsigned int   toUnsignedInt  () const;
	int            toInt          () const;
	unsigned short toUnsignedShort() const;
	short          toShort        () const;
protected:
	// Helpers
	template <class X> X convertToSignedPrimitive() const;
	template <class X> X convertToPrimitive      () const;
public:

	// BIT/BLOCK ACCESSORS

	// Expose these from NumberlikeArray directly.
	NumberlikeArray<Blk>::getCapacity;
	NumberlikeArray<Blk>::getLength;

	/* Returns the requested block, or 0 if it is beyond the length (as if
	 * the number had 0s infinitely to the left). */
	Blk getBlock(Index i) const { return i >= len ? 0 : blk[i]; }
	/* Sets the requested block.  The number grows or shrinks as necessary. */
	void setBlock(Index i, Blk newBlock);

	// The number is zero if and only if the canonical length is zero.
	bool isZero() const { return NumberlikeArray<Blk>::isEmpty(); }

	/* Returns the length of the number in bits, i.e., zero if the number
	 * is zero and otherwise one more than the largest value of bi for
	 * which getBit(bi) returns true. */
	Index bitLength() const;
	/* Get the state of bit bi, which has value 2^bi.  Bits beyond the
	 * number's length are considered to be 0. */
	bool getBit(Index bi) const {
		return (getBlock(bi / N) & (Blk(1) << (bi % N))) != 0;
	}
	/* Sets the state of bit bi to newBit.  The number grows or shrinks as
	 * necessary. */
	void setBit(Index bi, bool newBit);

	// COMPARISONS

	// Compares this to x like Perl's <=>
	CmpRes compareTo(const BigUnsigned &x) const;

	// Ordinary comparison operators
	bool operator ==(const BigUnsigned &x) const {
		return NumberlikeArray<Blk>::operator ==(x);
	}
	bool operator !=(const BigUnsigned &x) const {
		return NumberlikeArray<Blk>::operator !=(x);
	}
	bool operator < (const BigUnsigned &x) const { return compareTo(x) == less   ; }
	bool operator <=(const BigUnsigned &x) const { return compareTo(x) != greater; }
	bool operator >=(const BigUnsigned &x) const { return compareTo(x) != less   ; }
	bool operator > (const BigUnsigned &x) const { return compareTo(x) == greater; }

	/*
	 * BigUnsigned and BigInteger both provide three kinds of operators.
	 * Here ``big-integer'' refers to BigInteger or BigUnsigned.
	 *
	 * (1) Overloaded ``return-by-value'' operators:
	 *     +, -, *, /, %, unary -, &, |, ^, <<, >>.
	 * Big-integer code using these operators looks identical to code using
	 * the primitive integer types.  These operators take one or two
	 * big-integer inputs and return a big-integer result, which can then
	 * be assigned to a BigInteger variable or used in an expression.
	 * Example:
	 *     BigInteger a(1), b = 1;
	 *     BigInteger c = a + b;
	 *
	 * (2) Overloaded assignment operators:
	 *     +=, -=, *=, /=, %=, flipSign, &=, |=, ^=, <<=, >>=, ++, --.
	 * Again, these are used on big integers just like on ints.  They take
	 * one writable big integer that both provides an operand and receives a
	 * result.  Most also take a second read-only operand.
	 * Example:
	 *     BigInteger a(1), b(1);
	 *     a += b;
	 *
	 * (3) Copy-less operations: `add', `subtract', etc.
	 * These named methods take operands as arguments and store the result
	 * in the receiver (*this), avoiding unnecessary copies and allocations.
	 * `divideWithRemainder' is special: it both takes the dividend from and
	 * stores the remainder into the receiver, and it takes a separate
	 * object in which to store the quotient.  NOTE: If you are wondering
	 * why these don't return a value, you probably mean to use the
	 * overloaded return-by-value operators instead.
	 * 
	 * Examples:
	 *     BigInteger a(43), b(7), c, d;
	 *
	 *     c = a + b;   // Now c == 50.
	 *     c.add(a, b); // Same effect but without the two copies.
	 *
	 *     c.divideWithRemainder(b, d);
	 *     // 50 / 7; now d == 7 (quotient) and c == 1 (remainder).
	 *
	 *     // ``Aliased'' calls now do the right thing using a temporary
	 *     // copy, but see note on `divideWithRemainder'.
	 *     a.add(a, b); 
	 */

	// COPY-LESS OPERATIONS

	// These 8: Arguments are read-only operands, result is saved in *this.
	void add(const BigUnsigned &a, const BigUnsigned &b);
	void subtract(const BigUnsigned &a, const BigUnsigned &b);
	void multiply(const BigUnsigned &a, const BigUnsigned &b);
	void bitAnd(const BigUnsigned &a, const BigUnsigned &b);
	void bitOr(const BigUnsigned &a, const BigUnsigned &b);
	void bitXor(const BigUnsigned &a, const BigUnsigned &b);
	/* Negative shift amounts translate to opposite-direction shifts,
	 * except for -2^(8*sizeof(int)-1) which is unimplemented. */
	void bitShiftLeft(const BigUnsigned &a, int b);
	void bitShiftRight(const BigUnsigned &a, int b);

	/* `a.divideWithRemainder(b, q)' is like `q = a / b, a %= b'.
	 * / and % use semantics similar to Knuth's, which differ from the
	 * primitive integer semantics under division by zero.  See the
	 * implementation in BigUnsigned.cc for details.
	 * `a.divideWithRemainder(b, a)' throws an exception: it doesn't make
	 * sense to write quotient and remainder into the same variable. */
	void divideWithRemainder(const BigUnsigned &b, BigUnsigned &q);

	/* `divide' and `modulo' are no longer offered.  Use
	 * `divideWithRemainder' instead. */

	// OVERLOADED RETURN-BY-VALUE OPERATORS
	BigUnsigned operator +(const BigUnsigned &x) const;
	BigUnsigned operator -(const BigUnsigned &x) const;
	BigUnsigned operator *(const BigUnsigned &x) const;
	BigUnsigned operator /(const BigUnsigned &x) const;
	BigUnsigned operator %(const BigUnsigned &x) const;
	/* OK, maybe unary minus could succeed in one case, but it really
	 * shouldn't be used, so it isn't provided. */
	BigUnsigned operator &(const BigUnsigned &x) const;
	BigUnsigned operator |(const BigUnsigned &x) const;
	BigUnsigned operator ^(const BigUnsigned &x) const;
	BigUnsigned operator <<(int b) const;
	BigUnsigned operator >>(int b) const;

	// OVERLOADED ASSIGNMENT OPERATORS
	void operator +=(const BigUnsigned &x);
	void operator -=(const BigUnsigned &x);
	void operator *=(const BigUnsigned &x);
	void operator /=(const BigUnsigned &x);
	void operator %=(const BigUnsigned &x);
	void operator &=(const BigUnsigned &x);
	void operator |=(const BigUnsigned &x);
	void operator ^=(const BigUnsigned &x);
	void operator <<=(int b);
	void operator >>=(int b);

	/* INCREMENT/DECREMENT OPERATORS
	 * To discourage messy coding, these do not return *this, so prefix
	 * and postfix behave the same. */
	void operator ++(   );
	void operator ++(int);
	void operator --(   );
	void operator --(int);

	// Helper function that needs access to BigUnsigned internals
	friend Blk getShiftedBlock(const BigUnsigned &num, Index x,
			unsigned int y);

	// See BigInteger.cc.
	template <class X>
	friend X convertBigUnsignedToPrimitiveAccess(const BigUnsigned &a);
};

/* Implementing the return-by-value and assignment operators in terms of the
 * copy-less operations.  The copy-less operations are responsible for making
 * any necessary temporary copies to work around aliasing. */

inline BigUnsigned BigUnsigned::operator +(const BigUnsigned &x) const {
	BigUnsigned ans;
	ans.add(*this, x);
	return ans;
}
inline BigUnsigned BigUnsigned::operator -(const BigUnsigned &x) const {
	BigUnsigned ans;
	ans.subtract(*this, x);
	return ans;
}
inline BigUnsigned BigUnsigned::operator *(const BigUnsigned &x) const {
	BigUnsigned ans;
	ans.multiply(*this, x);
	return ans;
}
inline BigUnsigned BigUnsigned::operator /(const BigUnsigned &x) const {
	if (x.isZero()) throw "BigUnsigned::operator /: division by zero";
	BigUnsigned q, r;
	r = *this;
	r.divideWithRemainder(x, q);
	return q;
}
inline BigUnsigned BigUnsigned::operator %(const BigUnsigned &x) const {
	if (x.isZero()) throw "BigUnsigned::operator %: division by zero";
	BigUnsigned q, r;
	r = *this;
	r.divideWithRemainder(x, q);
	return r;
}
inline BigUnsigned BigUnsigned::operator &(const BigUnsigned &x) const {
	BigUnsigned ans;
	ans.bitAnd(*this, x);
	return ans;
}
inline BigUnsigned BigUnsigned::operator |(const BigUnsigned &x) const {
	BigUnsigned ans;
	ans.bitOr(*this, x);
	return ans;
}
inline BigUnsigned BigUnsigned::operator ^(const BigUnsigned &x) const {
	BigUnsigned ans;
	ans.bitXor(*this, x);
	return ans;
}
inline BigUnsigned BigUnsigned::operator <<(int b) const {
	BigUnsigned ans;
	ans.bitShiftLeft(*this, b);
	return ans;
}
inline BigUnsigned BigUnsigned::operator >>(int b) const {
	BigUnsigned ans;
	ans.bitShiftRight(*this, b);
	return ans;
}

inline void BigUnsigned::operator +=(const BigUnsigned &x) {
	add(*this, x);
}
inline void BigUnsigned::operator -=(const BigUnsigned &x) {
	subtract(*this, x);
}
inline void BigUnsigned::operator *=(const BigUnsigned &x) {
	multiply(*this, x);
}
inline void BigUnsigned::operator /=(const BigUnsigned &x) {
	if (x.isZero()) throw "BigUnsigned::operator /=: division by zero";
	/* The following technique is slightly faster than copying *this first
	 * when x is large. */
	BigUnsigned q;
	divideWithRemainder(x, q);
	// *this contains the remainder, but we overwrite it with the quotient.
	*this = q;
}
inline void BigUnsigned::operator %=(const BigUnsigned &x) {
	if (x.isZero()) throw "BigUnsigned::operator %=: division by zero";
	BigUnsigned q;
	// Mods *this by x.  Don't care about quotient left in q.
	divideWithRemainder(x, q);
}
inline void BigUnsigned::operator &=(const BigUnsigned &x) {
	bitAnd(*this, x);
}
inline void BigUnsigned::operator |=(const BigUnsigned &x) {
	bitOr(*this, x);
}
inline void BigUnsigned::operator ^=(const BigUnsigned &x) {
	bitXor(*this, x);
}
inline void BigUnsigned::operator <<=(int b) {
	bitShiftLeft(*this, b);
}
inline void BigUnsigned::operator >>=(int b) {
	bitShiftRight(*this, b);
}

/* Templates for conversions of BigUnsigned to and from primitive integers.
 * BigInteger.cc needs to instantiate convertToPrimitive, and the uses in
 * BigUnsigned.cc didn't do the trick; I think g++ inlined convertToPrimitive
 * instead of generating linkable instantiations.  So for consistency, I put
 * all the templates here. */

// CONSTRUCTION FROM PRIMITIVE INTEGERS

/* Initialize this BigUnsigned from the given primitive integer.  The same
 * pattern works for all primitive integer types, so I put it into a template to
 * reduce code duplication.  (Don't worry: this is protected and we instantiate
 * it only with primitive integer types.)  Type X could be signed, but x is
 * known to be nonnegative. */
template <class X>
void BigUnsigned::initFromPrimitive(X x) {
	if (x == 0)
		; // NumberlikeArray already initialized us to zero.
	else {
		// Create a single block.  blk is NULL; no need to delete it.
		cap = 1;
		blk = new Blk[1];
		len = 1;
		blk[0] = Blk(x);
	}
}

/* Ditto, but first check that x is nonnegative.  I could have put the check in
 * initFromPrimitive and let the compiler optimize it out for unsigned-type
 * instantiations, but I wanted to avoid the warning stupidly issued by g++ for
 * a condition that is constant in *any* instantiation, even if not in all. */
template <class X>
void BigUnsigned::initFromSignedPrimitive(X x) {
	if (x < 0)
		throw "BigUnsigned constructor: "
			"Cannot construct a BigUnsigned from a negative number";
	else
		initFromPrimitive(x);
}

// CONVERSION TO PRIMITIVE INTEGERS

/* Template with the same idea as initFromPrimitive.  This might be slightly
 * slower than the previous version with the masks, but it's much shorter and
 * clearer, which is the library's stated goal. */
template <class X>
X BigUnsigned::convertToPrimitive() const {
	if (len == 0)
		// The number is zero; return zero.
		return 0;
	else if (len == 1) {
		// The single block might fit in an X.  Try the conversion.
		X x = X(blk[0]);
		// Make sure the result accurately represents the block.
		if (Blk(x) == blk[0])
			// Successful conversion.
			return x;
		// Otherwise fall through.
	}
	throw "BigUnsigned::to<Primitive>: "
		"Value is too big to fit in the requested type";
}

/* Wrap the above in an x >= 0 test to make sure we got a nonnegative result,
 * not a negative one that happened to convert back into the correct nonnegative
 * one.  (E.g., catch incorrect conversion of 2^31 to the long -2^31.)  Again,
 * separated to avoid a g++ warning. */
template <class X>
X BigUnsigned::convertToSignedPrimitive() const {
	X x = convertToPrimitive<X>();
	if (x >= 0)
		return x;
	else
		throw "BigUnsigned::to(Primitive): "
			"Value is too big to fit in the requested type";
}

// .cc=============================================
// Memory management definitions have moved to the bottom of NumberlikeArray.hh.

// The templates used by these constructors and converters are at the bottom of
// BigUnsigned.hh.

BigUnsigned::BigUnsigned(unsigned long  x) { initFromPrimitive      (x); }
BigUnsigned::BigUnsigned(unsigned int   x) { initFromPrimitive      (x); }
BigUnsigned::BigUnsigned(unsigned short x) { initFromPrimitive      (x); }
BigUnsigned::BigUnsigned(         long  x) { initFromSignedPrimitive(x); }
BigUnsigned::BigUnsigned(         int   x) { initFromSignedPrimitive(x); }
BigUnsigned::BigUnsigned(         short x) { initFromSignedPrimitive(x); }

unsigned long  BigUnsigned::toUnsignedLong () const { return convertToPrimitive      <unsigned long >(); }
unsigned int   BigUnsigned::toUnsignedInt  () const { return convertToPrimitive      <unsigned int  >(); }
unsigned short BigUnsigned::toUnsignedShort() const { return convertToPrimitive      <unsigned short>(); }
long           BigUnsigned::toLong         () const { return convertToSignedPrimitive<         long >(); }
int            BigUnsigned::toInt          () const { return convertToSignedPrimitive<         int  >(); }
short          BigUnsigned::toShort        () const { return convertToSignedPrimitive<         short>(); }

// BIT/BLOCK ACCESSORS

void BigUnsigned::setBlock(Index i, Blk newBlock) {
	if (newBlock == 0) {
		if (i < len) {
			blk[i] = 0;
			zapLeadingZeros();
		}
		// If i >= len, no effect.
	} else {
		if (i >= len) {
			// The nonzero block extends the number.
			allocateAndCopy(i+1);
			// Zero any added blocks that we aren't setting.
			for (Index j = len; j < i; j++)
				blk[j] = 0;
			len = i+1;
		}
		blk[i] = newBlock;
	}
}

/* Evidently the compiler wants BigUnsigned:: on the return type because, at
 * that point, it hasn't yet parsed the BigUnsigned:: on the name to get the
 * proper scope. */
BigUnsigned::Index BigUnsigned::bitLength() const {
	if (isZero())
		return 0;
	else {
		Blk leftmostBlock = getBlock(len - 1);
		Index leftmostBlockLen = 0;
		while (leftmostBlock != 0) {
			leftmostBlock >>= 1;
			leftmostBlockLen++;
		}
		return leftmostBlockLen + (len - 1) * N;
	}
}

void BigUnsigned::setBit(Index bi, bool newBit) {
	Index blockI = bi / N;
	Blk block = getBlock(blockI), mask = Blk(1) << (bi % N);
	block = newBit ? (block | mask) : (block & ~mask);
	setBlock(blockI, block);
}

// COMPARISON
BigUnsigned::CmpRes BigUnsigned::compareTo(const BigUnsigned &x) const {
	// A bigger length implies a bigger number.
	if (len < x.len)
		return less;
	else if (len > x.len)
		return greater;
	else {
		// Compare blocks one by one from left to right.
		Index i = len;
		while (i > 0) {
			i--;
			if (blk[i] == x.blk[i])
				continue;
			else if (blk[i] > x.blk[i])
				return greater;
			else
				return less;
		}
		// If no blocks differed, the numbers are equal.
		return equal;
	}
}

// COPY-LESS OPERATIONS

/*
 * On most calls to copy-less operations, it's safe to read the inputs little by
 * little and write the outputs little by little.  However, if one of the
 * inputs is coming from the same variable into which the output is to be
 * stored (an "aliased" call), we risk overwriting the input before we read it.
 * In this case, we first compute the result into a temporary BigUnsigned
 * variable and then copy it into the requested output variable *this.
 * Each put-here operation uses the DTRT_ALIASED macro (Do The Right Thing on
 * aliased calls) to generate code for this check.
 * 
 * I adopted this approach on 2007.02.13 (see Assignment Operators in
 * BigUnsigned.hh).  Before then, put-here operations rejected aliased calls
 * with an exception.  I think doing the right thing is better.
 * 
 * Some of the put-here operations can probably handle aliased calls safely
 * without the extra copy because (for example) they process blocks strictly
 * right-to-left.  At some point I might determine which ones don't need the
 * copy, but my reasoning would need to be verified very carefully.  For now
 * I'll leave in the copy.
 */
#define DTRT_ALIASED(cond, op) \
	if (cond) { \
		BigUnsigned tmpThis; \
		tmpThis.op; \
		*this = tmpThis; \
		return; \
	}



void BigUnsigned::add(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, add(a, b));
	// If one argument is zero, copy the other.
	if (a.len == 0) {
		operator =(b);
		return;
	} else if (b.len == 0) {
		operator =(a);
		return;
	}
	// Some variables...
	// Carries in and out of an addition stage
	bool carryIn, carryOut;
	Blk temp;
	Index i;
	// a2 points to the longer input, b2 points to the shorter
	const BigUnsigned *a2, *b2;
	if (a.len >= b.len) {
		a2 = &a;
		b2 = &b;
	} else {
		a2 = &b;
		b2 = &a;
	}
	// Set prelimiary length and make room in this BigUnsigned
	len = a2->len + 1;
	allocate(len);
	// For each block index that is present in both inputs...
	for (i = 0, carryIn = false; i < b2->len; i++) {
		// Add input blocks
		temp = a2->blk[i] + b2->blk[i];
		// If a rollover occurred, the result is less than either input.
		// This test is used many times in the BigUnsigned code.
		carryOut = (temp < a2->blk[i]);
		// If a carry was input, handle it
		if (carryIn) {
			temp++;
			carryOut |= (temp == 0);
		}
		blk[i] = temp; // Save the addition result
		carryIn = carryOut; // Pass the carry along
	}
	// If there is a carry left over, increase blocks until
	// one does not roll over.
	for (; i < a2->len && carryIn; i++) {
		temp = a2->blk[i] + 1;
		carryIn = (temp == 0);
		blk[i] = temp;
	}
	// If the carry was resolved but the larger number
	// still has blocks, copy them over.
	for (; i < a2->len; i++)
		blk[i] = a2->blk[i];
	// Set the extra block if there's still a carry, decrease length otherwise
	if (carryIn)
		blk[i] = 1;
	else
		len--;
}

void BigUnsigned::subtract(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, subtract(a, b));
	if (b.len == 0) {
		// If b is zero, copy a.
		operator =(a);
		return;
	} else if (a.len < b.len)
		// If a is shorter than b, the result is negative.
		throw "BigUnsigned::subtract: "
			"Negative result in unsigned calculation";
	// Some variables...
	bool borrowIn, borrowOut;
	Blk temp;
	Index i;
	// Set preliminary length and make room
	len = a.len;
	allocate(len);
	// For each block index that is present in both inputs...
	for (i = 0, borrowIn = false; i < b.len; i++) {
		temp = a.blk[i] - b.blk[i];
		// If a reverse rollover occurred,
		// the result is greater than the block from a.
		borrowOut = (temp > a.blk[i]);
		// Handle an incoming borrow
		if (borrowIn) {
			borrowOut |= (temp == 0);
			temp--;
		}
		blk[i] = temp; // Save the subtraction result
		borrowIn = borrowOut; // Pass the borrow along
	}
	// If there is a borrow left over, decrease blocks until
	// one does not reverse rollover.
	for (; i < a.len && borrowIn; i++) {
		borrowIn = (a.blk[i] == 0);
		blk[i] = a.blk[i] - 1;
	}
	/* If there's still a borrow, the result is negative.
	 * Throw an exception, but zero out this object so as to leave it in a
	 * predictable state. */
	if (borrowIn) {
		len = 0;
		throw "BigUnsigned::subtract: Negative result in unsigned calculation";
	} else
		// Copy over the rest of the blocks
		for (; i < a.len; i++)
			blk[i] = a.blk[i];
	// Zap leading zeros
	zapLeadingZeros();
}

/*
 * About the multiplication and division algorithms:
 *
 * I searched unsucessfully for fast C++ built-in operations like the `b_0'
 * and `c_0' Knuth describes in Section 4.3.1 of ``The Art of Computer
 * Programming'' (replace `place' by `Blk'):
 *
 *    ``b_0[:] multiplication of a one-place integer by another one-place
 *      integer, giving a two-place answer;
 *
 *    ``c_0[:] division of a two-place integer by a one-place integer,
 *      provided that the quotient is a one-place integer, and yielding
 *      also a one-place remainder.''
 *
 * I also missed his note that ``[b]y adjusting the word size, if
 * necessary, nearly all computers will have these three operations
 * available'', so I gave up on trying to use algorithms similar to his.
 * A future version of the library might include such algorithms; I
 * would welcome contributions from others for this.
 *
 * I eventually decided to use bit-shifting algorithms.  To multiply `a'
 * and `b', we zero out the result.  Then, for each `1' bit in `a', we
 * shift `b' left the appropriate amount and add it to the result.
 * Similarly, to divide `a' by `b', we shift `b' left varying amounts,
 * repeatedly trying to subtract it from `a'.  When we succeed, we note
 * the fact by setting a bit in the quotient.  While these algorithms
 * have the same O(n^2) time complexity as Knuth's, the ``constant factor''
 * is likely to be larger.
 *
 * Because I used these algorithms, which require single-block addition
 * and subtraction rather than single-block multiplication and division,
 * the innermost loops of all four routines are very similar.  Study one
 * of them and all will become clear.
 */

/*
 * This is a little inline function used by both the multiplication
 * routine and the division routine.
 *
 * `getShiftedBlock' returns the `x'th block of `num << y'.
 * `y' may be anything from 0 to N - 1, and `x' may be anything from
 * 0 to `num.len'.
 *
 * Two things contribute to this block:
 *
 * (1) The `N - y' low bits of `num.blk[x]', shifted `y' bits left.
 *
 * (2) The `y' high bits of `num.blk[x-1]', shifted `N - y' bits right.
 *
 * But we must be careful if `x == 0' or `x == num.len', in
 * which case we should use 0 instead of (2) or (1), respectively.
 *
 * If `y == 0', then (2) contributes 0, as it should.  However,
 * in some computer environments, for a reason I cannot understand,
 * `a >> b' means `a >> (b % N)'.  This means `num.blk[x-1] >> (N - y)'
 * will return `num.blk[x-1]' instead of the desired 0 when `y == 0';
 * the test `y == 0' handles this case specially.
 */
inline BigUnsigned::Blk getShiftedBlock(const BigUnsigned &num,
	BigUnsigned::Index x, unsigned int y) {
	BigUnsigned::Blk part1 = (x == 0 || y == 0) ? 0 : (num.blk[x - 1] >> (BigUnsigned::N - y));
	BigUnsigned::Blk part2 = (x == num.len) ? 0 : (num.blk[x] << y);
	return part1 | part2;
}

void BigUnsigned::multiply(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, multiply(a, b));
	// If either a or b is zero, set to zero.
	if (a.len == 0 || b.len == 0) {
		len = 0;
		return;
	}
	/*
	 * Overall method:
	 *
	 * Set this = 0.
	 * For each 1-bit of `a' (say the `i2'th bit of block `i'):
	 *    Add `b << (i blocks and i2 bits)' to *this.
	 */
	// Variables for the calculation
	Index i, j, k;
	unsigned int i2;
	Blk temp;
	bool carryIn, carryOut;
	// Set preliminary length and make room
	len = a.len + b.len;
	allocate(len);
	// Zero out this object
	for (i = 0; i < len; i++)
		blk[i] = 0;
	// For each block of the first number...
	for (i = 0; i < a.len; i++) {
		// For each 1-bit of that block...
		for (i2 = 0; i2 < N; i2++) {
			if ((a.blk[i] & (Blk(1) << i2)) == 0)
				continue;
			/*
			 * Add b to this, shifted left i blocks and i2 bits.
			 * j is the index in b, and k = i + j is the index in this.
			 *
			 * `getShiftedBlock', a short inline function defined above,
			 * is now used for the bit handling.  It replaces the more
			 * complex `bHigh' code, in which each run of the loop dealt
			 * immediately with the low bits and saved the high bits to
			 * be picked up next time.  The last run of the loop used to
			 * leave leftover high bits, which were handled separately.
			 * Instead, this loop runs an additional time with j == b.len.
			 * These changes were made on 2005.01.11.
			 */
			for (j = 0, k = i, carryIn = false; j <= b.len; j++, k++) {
				/*
				 * The body of this loop is very similar to the body of the first loop
				 * in `add', except that this loop does a `+=' instead of a `+'.
				 */
				temp = blk[k] + getShiftedBlock(b, j, i2);
				carryOut = (temp < blk[k]);
				if (carryIn) {
					temp++;
					carryOut |= (temp == 0);
				}
				blk[k] = temp;
				carryIn = carryOut;
			}
			// No more extra iteration to deal with `bHigh'.
			// Roll-over a carry as necessary.
			for (; carryIn; k++) {
				blk[k]++;
				carryIn = (blk[k] == 0);
			}
		}
	}
	// Zap possible leading zero
	if (blk[len - 1] == 0)
		len--;
}

/*
 * DIVISION WITH REMAINDER
 * This monstrous function mods *this by the given divisor b while storing the
 * quotient in the given object q; at the end, *this contains the remainder.
 * The seemingly bizarre pattern of inputs and outputs was chosen so that the
 * function copies as little as possible (since it is implemented by repeated
 * subtraction of multiples of b from *this).
 * 
 * "modWithQuotient" might be a better name for this function, but I would
 * rather not change the name now.
 */
void BigUnsigned::divideWithRemainder(const BigUnsigned &b, BigUnsigned &q) {
	/* Defending against aliased calls is more complex than usual because we
	 * are writing to both *this and q.
	 * 
	 * It would be silly to try to write quotient and remainder to the
	 * same variable.  Rule that out right away. */
	if (this == &q)
		throw "BigUnsigned::divideWithRemainder: Cannot write quotient and remainder into the same variable";
	/* Now *this and q are separate, so the only concern is that b might be
	 * aliased to one of them.  If so, use a temporary copy of b. */
	if (this == &b || &q == &b) {
		BigUnsigned tmpB(b);
		divideWithRemainder(tmpB, q);
		return;
	}

	/*
	 * Knuth's definition of mod (which this function uses) is somewhat
	 * different from the C++ definition of % in case of division by 0.
	 *
	 * We let a / 0 == 0 (it doesn't matter much) and a % 0 == a, no
	 * exceptions thrown.  This allows us to preserve both Knuth's demand
	 * that a mod 0 == a and the useful property that
	 * (a / b) * b + (a % b) == a.
	 */
	if (b.len == 0) {
		q.len = 0;
		return;
	}

	/*
	 * If *this.len < b.len, then *this < b, and we can be sure that b doesn't go into
	 * *this at all.  The quotient is 0 and *this is already the remainder (so leave it alone).
	 */
	if (len < b.len) {
		q.len = 0;
		return;
	}

	// At this point we know (*this).len >= b.len > 0.  (Whew!)

	/*
	 * Overall method:
	 *
	 * For each appropriate i and i2, decreasing:
	 *    Subtract (b << (i blocks and i2 bits)) from *this, storing the
	 *      result in subtractBuf.
	 *    If the subtraction succeeds with a nonnegative result:
	 *        Turn on bit i2 of block i of the quotient q.
	 *        Copy subtractBuf back into *this.
	 *    Otherwise bit i2 of block i remains off, and *this is unchanged.
	 * 
	 * Eventually q will contain the entire quotient, and *this will
	 * be left with the remainder.
	 *
	 * subtractBuf[x] corresponds to blk[x], not blk[x+i], since 2005.01.11.
	 * But on a single iteration, we don't touch the i lowest blocks of blk
	 * (and don't use those of subtractBuf) because these blocks are
	 * unaffected by the subtraction: we are subtracting
	 * (b << (i blocks and i2 bits)), which ends in at least `i' zero
	 * blocks. */
	// Variables for the calculation
	Index i, j, k;
	unsigned int i2;
	Blk temp;
	bool borrowIn, borrowOut;

	/*
	 * Make sure we have an extra zero block just past the value.
	 *
	 * When we attempt a subtraction, we might shift `b' so
	 * its first block begins a few bits left of the dividend,
	 * and then we'll try to compare these extra bits with
	 * a nonexistent block to the left of the dividend.  The
	 * extra zero block ensures sensible behavior; we need
	 * an extra block in `subtractBuf' for exactly the same reason.
	 */
	Index origLen = len; // Save real length.
	/* To avoid an out-of-bounds access in case of reallocation, allocate
	 * first and then increment the logical length. */
	allocateAndCopy(len + 1);
	len++;
	blk[origLen] = 0; // Zero the added block.

	// subtractBuf holds part of the result of a subtraction; see above.
	Blk *subtractBuf = new Blk[len];

	// Set preliminary length for quotient and make room
	q.len = origLen - b.len + 1;
	q.allocate(q.len);
	// Zero out the quotient
	for (i = 0; i < q.len; i++)
		q.blk[i] = 0;

	// For each possible left-shift of b in blocks...
	i = q.len;
	while (i > 0) {
		i--;
		// For each possible left-shift of b in bits...
		// (Remember, N is the number of bits in a Blk.)
		q.blk[i] = 0;
		i2 = N;
		while (i2 > 0) {
			i2--;
			/*
			 * Subtract b, shifted left i blocks and i2 bits, from *this,
			 * and store the answer in subtractBuf.  In the for loop, `k == i + j'.
			 *
			 * Compare this to the middle section of `multiply'.  They
			 * are in many ways analogous.  See especially the discussion
			 * of `getShiftedBlock'.
			 */
			for (j = 0, k = i, borrowIn = false; j <= b.len; j++, k++) {
				temp = blk[k] - getShiftedBlock(b, j, i2);
				borrowOut = (temp > blk[k]);
				if (borrowIn) {
					borrowOut |= (temp == 0);
					temp--;
				}
				// Since 2005.01.11, indices of `subtractBuf' directly match those of `blk', so use `k'.
				subtractBuf[k] = temp; 
				borrowIn = borrowOut;
			}
			// No more extra iteration to deal with `bHigh'.
			// Roll-over a borrow as necessary.
			for (; k < origLen && borrowIn; k++) {
				borrowIn = (blk[k] == 0);
				subtractBuf[k] = blk[k] - 1;
			}
			/*
			 * If the subtraction was performed successfully (!borrowIn),
			 * set bit i2 in block i of the quotient.
			 *
			 * Then, copy the portion of subtractBuf filled by the subtraction
			 * back to *this.  This portion starts with block i and ends--
			 * where?  Not necessarily at block `i + b.len'!  Well, we
			 * increased k every time we saved a block into subtractBuf, so
			 * the region of subtractBuf we copy is just [i, k).
			 */
			if (!borrowIn) {
				q.blk[i] |= (Blk(1) << i2);
				while (k > i) {
					k--;
					blk[k] = subtractBuf[k];
				}
			} 
		}
	}
	// Zap possible leading zero in quotient
	if (q.blk[q.len - 1] == 0)
		q.len--;
	// Zap any/all leading zeros in remainder
	zapLeadingZeros();
	// Deallocate subtractBuf.
	// (Thanks to Brad Spencer for noticing my accidental omission of this!)
	delete [] subtractBuf;
}

/* BITWISE OPERATORS
 * These are straightforward blockwise operations except that they differ in
 * the output length and the necessity of zapLeadingZeros. */

void BigUnsigned::bitAnd(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, bitAnd(a, b));
	// The bitwise & can't be longer than either operand.
	len = (a.len >= b.len) ? b.len : a.len;
	allocate(len);
	Index i;
	for (i = 0; i < len; i++)
		blk[i] = a.blk[i] & b.blk[i];
	zapLeadingZeros();
}

void BigUnsigned::bitOr(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, bitOr(a, b));
	Index i;
	const BigUnsigned *a2, *b2;
	if (a.len >= b.len) {
		a2 = &a;
		b2 = &b;
	} else {
		a2 = &b;
		b2 = &a;
	}
	allocate(a2->len);
	for (i = 0; i < b2->len; i++)
		blk[i] = a2->blk[i] | b2->blk[i];
	for (; i < a2->len; i++)
		blk[i] = a2->blk[i];
	len = a2->len;
	// Doesn't need zapLeadingZeros.
}

void BigUnsigned::bitXor(const BigUnsigned &a, const BigUnsigned &b) {
	DTRT_ALIASED(this == &a || this == &b, bitXor(a, b));
	Index i;
	const BigUnsigned *a2, *b2;
	if (a.len >= b.len) {
		a2 = &a;
		b2 = &b;
	} else {
		a2 = &b;
		b2 = &a;
	}
	allocate(a2->len);
	for (i = 0; i < b2->len; i++)
		blk[i] = a2->blk[i] ^ b2->blk[i];
	for (; i < a2->len; i++)
		blk[i] = a2->blk[i];
	len = a2->len;
	zapLeadingZeros();
}

void BigUnsigned::bitShiftLeft(const BigUnsigned &a, int b) {
	DTRT_ALIASED(this == &a, bitShiftLeft(a, b));
	if (b < 0) {
		if (b << 1 == 0)
			throw "BigUnsigned::bitShiftLeft: "
				"Pathological shift amount not implemented";
		else {
			bitShiftRight(a, -b);
			return;
		}
	}
	Index shiftBlocks = b / N;
	unsigned int shiftBits = b % N;
	// + 1: room for high bits nudged left into another block
	len = a.len + shiftBlocks + 1;
	allocate(len);
	Index i, j;
	for (i = 0; i < shiftBlocks; i++)
		blk[i] = 0;
	for (j = 0, i = shiftBlocks; j <= a.len; j++, i++)
		blk[i] = getShiftedBlock(a, j, shiftBits);
	// Zap possible leading zero
	if (blk[len - 1] == 0)
		len--;
}

void BigUnsigned::bitShiftRight(const BigUnsigned &a, int b) {
	DTRT_ALIASED(this == &a, bitShiftRight(a, b));
	if (b < 0) {
		if (b << 1 == 0)
			throw "BigUnsigned::bitShiftRight: "
				"Pathological shift amount not implemented";
		else {
			bitShiftLeft(a, -b);
			return;
		}
	}
	// This calculation is wacky, but expressing the shift as a left bit shift
	// within each block lets us use getShiftedBlock.
	Index rightShiftBlocks = (b + N - 1) / N;
	unsigned int leftShiftBits = N * rightShiftBlocks - b;
	// Now (N * rightShiftBlocks - leftShiftBits) == b
	// and 0 <= leftShiftBits < N.
	if (rightShiftBlocks >= a.len + 1) {
		// All of a is guaranteed to be shifted off, even considering the left
		// bit shift.
		len = 0;
		return;
	}
	// Now we're allocating a positive amount.
	// + 1: room for high bits nudged left into another block
	len = a.len + 1 - rightShiftBlocks;
	allocate(len);
	Index i, j;
	for (j = rightShiftBlocks, i = 0; j <= a.len; j++, i++)
		blk[i] = getShiftedBlock(a, j, leftShiftBits);
	// Zap possible leading zero
	if (blk[len - 1] == 0)
		len--;
}

// INCREMENT/DECREMENT OPERATORS

// Prefix increment
void BigUnsigned::operator ++() {
	Index i;
	bool carry = true;
	for (i = 0; i < len && carry; i++) {
		blk[i]++;
		carry = (blk[i] == 0);
	}
	if (carry) {
		// Allocate and then increase length, as in divideWithRemainder
		allocateAndCopy(len + 1);
		len++;
		blk[i] = 1;
	}
}

// Postfix increment: same as prefix
void BigUnsigned::operator ++(int) {
	operator ++();
}

// Prefix decrement
void BigUnsigned::operator --() {
	if (len == 0)
		throw "BigUnsigned::operator --(): Cannot decrement an unsigned zero";
	Index i;
	bool borrow = true;
	for (i = 0; borrow; i++) {
		borrow = (blk[i] == 0);
		blk[i]--;
	}
	// Zap possible leading zero (there can only be one)
	if (blk[len - 1] == 0)
		len--;
}

// Postfix decrement: same as prefix
void BigUnsigned::operator --(int) {
	operator --();
}


// BIGINTEGER ======================================================================================
class BigInteger {

public:
	typedef BigUnsigned::Blk Blk;
	typedef BigUnsigned::Index Index;
	typedef BigUnsigned::CmpRes CmpRes;
	static const CmpRes
		less    = BigUnsigned::less   ,
		equal   = BigUnsigned::equal  ,
		greater = BigUnsigned::greater;
	// Enumeration for the sign of a BigInteger.
	enum Sign { negative = -1, zero = 0, positive = 1 };

protected:
	Sign sign;
	BigUnsigned mag;

public:
	// Constructs zero.
	BigInteger() : sign(zero), mag() {}

	// Copy constructor
	BigInteger(const BigInteger &x) : sign(x.sign), mag(x.mag) {};

	// Assignment operator
	void operator=(const BigInteger &x);

	// Constructor that copies from a given array of blocks with a sign.
	BigInteger(const Blk *b, Index blen, Sign s);

	// Nonnegative constructor that copies from a given array of blocks.
	BigInteger(const Blk *b, Index blen) : mag(b, blen) {
		sign = mag.isZero() ? zero : positive;
	}

	// Constructor from a BigUnsigned and a sign
	BigInteger(const BigUnsigned &x, Sign s);

	// Nonnegative constructor from a BigUnsigned
	BigInteger(const BigUnsigned &x) : mag(x) {
		sign = mag.isZero() ? zero : positive;
	}

	// Constructors from primitive integer types
	BigInteger(unsigned long  x);
	BigInteger(         long  x);
	BigInteger(unsigned int   x);
	BigInteger(         int   x);
	BigInteger(unsigned short x);
	BigInteger(         short x);

	/* Converters to primitive integer types
	 * The implicit conversion operators caused trouble, so these are now
	 * named. */
	unsigned long  toUnsignedLong () const;
	long           toLong         () const;
	unsigned int   toUnsignedInt  () const;
	int            toInt          () const;
	unsigned short toUnsignedShort() const;
	short          toShort        () const;
protected:
	// Helper
	template <class X> X convertToUnsignedPrimitive() const;
	template <class X, class UX> X convertToSignedPrimitive() const;
public:

	// ACCESSORS
	Sign getSign() const { return sign; }
	/* The client can't do any harm by holding a read-only reference to the
	 * magnitude. */
	const BigUnsigned &getMagnitude() const { return mag; }

	// Some accessors that go through to the magnitude
	Index getLength() const { return mag.getLength(); }
	Index getCapacity() const { return mag.getCapacity(); }
	Blk getBlock(Index i) const { return mag.getBlock(i); }
	bool isZero() const { return sign == zero; } // A bit special

	// COMPARISONS

	// Compares this to x like Perl's <=>
	CmpRes compareTo(const BigInteger &x) const;

	// Ordinary comparison operators
	bool operator ==(const BigInteger &x) const {
		return sign == x.sign && mag == x.mag;
	}
	bool operator !=(const BigInteger &x) const { return !operator ==(x); };
	bool operator < (const BigInteger &x) const { return compareTo(x) == less   ; }
	bool operator <=(const BigInteger &x) const { return compareTo(x) != greater; }
	bool operator >=(const BigInteger &x) const { return compareTo(x) != less   ; }
	bool operator > (const BigInteger &x) const { return compareTo(x) == greater; }

	// OPERATORS -- See the discussion in BigUnsigned.hh.
	void add     (const BigInteger &a, const BigInteger &b);
	void subtract(const BigInteger &a, const BigInteger &b);
	void multiply(const BigInteger &a, const BigInteger &b);
	/* See the comment on BigUnsigned::divideWithRemainder.  Semantics
	 * differ from those of primitive integers when negatives and/or zeros
	 * are involved. */
	void divideWithRemainder(const BigInteger &b, BigInteger &q);
	void negate(const BigInteger &a);
	
	/* Bitwise operators are not provided for BigIntegers.  Use
	 * getMagnitude to get the magnitude and operate on that instead. */

	BigInteger operator +(const BigInteger &x) const;
	BigInteger operator -(const BigInteger &x) const;
	BigInteger operator *(const BigInteger &x) const;
	BigInteger operator /(const BigInteger &x) const;
	BigInteger operator %(const BigInteger &x) const;
	BigInteger operator -() const;

	void operator +=(const BigInteger &x);
	void operator -=(const BigInteger &x);
	void operator *=(const BigInteger &x);
	void operator /=(const BigInteger &x);
	void operator %=(const BigInteger &x);
	void flipSign();

	// INCREMENT/DECREMENT OPERATORS
	void operator ++(   );
	void operator ++(int);
	void operator --(   );
	void operator --(int);
};

// NORMAL OPERATORS
/* These create an object to hold the result and invoke
 * the appropriate put-here operation on it, passing
 * this and x.  The new object is then returned. */
inline BigInteger BigInteger::operator +(const BigInteger &x) const {
	BigInteger ans;
	ans.add(*this, x);
	return ans;
}
inline BigInteger BigInteger::operator -(const BigInteger &x) const {
	BigInteger ans;
	ans.subtract(*this, x);
	return ans;
}
inline BigInteger BigInteger::operator *(const BigInteger &x) const {
	BigInteger ans;
	ans.multiply(*this, x);
	return ans;
}
inline BigInteger BigInteger::operator /(const BigInteger &x) const {
	if (x.isZero()) throw "BigInteger::operator /: division by zero";
	BigInteger q, r;
	r = *this;
	r.divideWithRemainder(x, q);
	return q;
}
inline BigInteger BigInteger::operator %(const BigInteger &x) const {
	if (x.isZero()) throw "BigInteger::operator %: division by zero";
	BigInteger q, r;
	r = *this;
	r.divideWithRemainder(x, q);
	return r;
}
inline BigInteger BigInteger::operator -() const {
	BigInteger ans;
	ans.negate(*this);
	return ans;
}

/*
 * ASSIGNMENT OPERATORS
 * 
 * Now the responsibility for making a temporary copy if necessary
 * belongs to the put-here operations.  See Assignment Operators in
 * BigUnsigned.hh.
 */
inline void BigInteger::operator +=(const BigInteger &x) {
	add(*this, x);
}
inline void BigInteger::operator -=(const BigInteger &x) {
	subtract(*this, x);
}
inline void BigInteger::operator *=(const BigInteger &x) {
	multiply(*this, x);
}
inline void BigInteger::operator /=(const BigInteger &x) {
	if (x.isZero()) throw "BigInteger::operator /=: division by zero";
	/* The following technique is slightly faster than copying *this first
	 * when x is large. */
	BigInteger q;
	divideWithRemainder(x, q);
	// *this contains the remainder, but we overwrite it with the quotient.
	*this = q;
}
inline void BigInteger::operator %=(const BigInteger &x) {
	if (x.isZero()) throw "BigInteger::operator %=: division by zero";
	BigInteger q;
	// Mods *this by x.  Don't care about quotient left in q.
	divideWithRemainder(x, q);
}
// This one is trivial
inline void BigInteger::flipSign() {
	sign = Sign(-sign);
}
//.cc==================================================

void BigInteger::operator =(const BigInteger &x) {
	// Calls like a = a have no effect
	if (this == &x)
		return;
	// Copy sign
	sign = x.sign;
	// Copy the rest
	mag = x.mag;
}

BigInteger::BigInteger(const Blk *b, Index blen, Sign s) : mag(b, blen) {
	switch (s) {
	case zero:
		if (!mag.isZero())
			throw "BigInteger::BigInteger(const Blk *, Index, Sign): Cannot use a sign of zero with a nonzero magnitude";
		sign = zero;
		break;
	case positive:
	case negative:
		// If the magnitude is zero, force the sign to zero.
		sign = mag.isZero() ? zero : s;
		break;
	default:
		/* g++ seems to be optimizing out this case on the assumption
		 * that the sign is a valid member of the enumeration.  Oh well. */
		throw "BigInteger::BigInteger(const Blk *, Index, Sign): Invalid sign";
	}
}

BigInteger::BigInteger(const BigUnsigned &x, Sign s) : mag(x) {
	switch (s) {
	case zero:
		if (!mag.isZero())
			throw "BigInteger::BigInteger(const BigUnsigned &, Sign): Cannot use a sign of zero with a nonzero magnitude";
		sign = zero;
		break;
	case positive:
	case negative:
		// If the magnitude is zero, force the sign to zero.
		sign = mag.isZero() ? zero : s;
		break;
	default:
		/* g++ seems to be optimizing out this case on the assumption
		 * that the sign is a valid member of the enumeration.  Oh well. */
		throw "BigInteger::BigInteger(const BigUnsigned &, Sign): Invalid sign";
	}
}

/* CONSTRUCTION FROM PRIMITIVE INTEGERS
 * Same idea as in BigUnsigned.cc, except that negative input results in a
 * negative BigInteger instead of an exception. */

// Done longhand to let us use initialization.
BigInteger::BigInteger(unsigned long  x) : mag(x) { sign = mag.isZero() ? zero : positive; }
BigInteger::BigInteger(unsigned int   x) : mag(x) { sign = mag.isZero() ? zero : positive; }
BigInteger::BigInteger(unsigned short x) : mag(x) { sign = mag.isZero() ? zero : positive; }

// For signed input, determine the desired magnitude and sign separately.

namespace {
	template <class X, class UX>
	BigInteger::Blk magOf(X x) {
		/* UX(...) cast needed to stop short(-2^15), which negates to
		 * itself, from sign-extending in the conversion to Blk. */
		return BigInteger::Blk(x < 0 ? UX(-x) : x);
	}
	template <class X>
	BigInteger::Sign signOf(X x) {
		return (x == 0) ? BigInteger::zero
			: (x > 0) ? BigInteger::positive
			: BigInteger::negative;
	}
}

BigInteger::BigInteger(long  x) : sign(signOf(x)), mag(magOf<long , unsigned long >(x)) {}
BigInteger::BigInteger(int   x) : sign(signOf(x)), mag(magOf<int  , unsigned int  >(x)) {}
BigInteger::BigInteger(short x) : sign(signOf(x)), mag(magOf<short, unsigned short>(x)) {}

// CONVERSION TO PRIMITIVE INTEGERS

/* Reuse BigUnsigned's conversion to an unsigned primitive integer.
 * The friend is a separate function rather than
 * BigInteger::convertToUnsignedPrimitive to avoid requiring BigUnsigned to
 * declare BigInteger. */
template <class X>
inline X convertBigUnsignedToPrimitiveAccess(const BigUnsigned &a) {
	return a.convertToPrimitive<X>();
}

template <class X>
X BigInteger::convertToUnsignedPrimitive() const {
	if (sign == negative)
		throw "BigInteger::to<Primitive>: "
			"Cannot convert a negative integer to an unsigned type";
	else
		return convertBigUnsignedToPrimitiveAccess<X>(mag);
}

/* Similar to BigUnsigned::convertToPrimitive, but split into two cases for
 * nonnegative and negative numbers. */
template <class X, class UX>
X BigInteger::convertToSignedPrimitive() const {
	if (sign == zero)
		return 0;
	else if (mag.getLength() == 1) {
		// The single block might fit in an X.  Try the conversion.
		Blk b = mag.getBlock(0);
		if (sign == positive) {
			X x = X(b);
			if (x >= 0 && Blk(x) == b)
				return x;
		} else {
			X x = -X(b);
			/* UX(...) needed to avoid rejecting conversion of
			 * -2^15 to a short. */
			if (x < 0 && Blk(UX(-x)) == b)
				return x;
		}
		// Otherwise fall through.
	}
	throw "BigInteger::to<Primitive>: "
		"Value is too big to fit in the requested type";
}

unsigned long  BigInteger::toUnsignedLong () const { return convertToUnsignedPrimitive<unsigned long >       (); }
unsigned int   BigInteger::toUnsignedInt  () const { return convertToUnsignedPrimitive<unsigned int  >       (); }
unsigned short BigInteger::toUnsignedShort() const { return convertToUnsignedPrimitive<unsigned short>       (); }
long           BigInteger::toLong         () const { return convertToSignedPrimitive  <long , unsigned long> (); }
int            BigInteger::toInt          () const { return convertToSignedPrimitive  <int  , unsigned int>  (); }
short          BigInteger::toShort        () const { return convertToSignedPrimitive  <short, unsigned short>(); }

// COMPARISON
BigInteger::CmpRes BigInteger::compareTo(const BigInteger &x) const {
	// A greater sign implies a greater number
	if (sign < x.sign)
		return less;
	else if (sign > x.sign)
		return greater;
	else switch (sign) {
		// If the signs are the same...
	case zero:
		return equal; // Two zeros are equal
	case positive:
		// Compare the magnitudes
		return mag.compareTo(x.mag);
	case negative:
		// Compare the magnitudes, but return the opposite result
		return CmpRes(-mag.compareTo(x.mag));
	default:
		throw "BigInteger internal error";
	}
}

/* COPY-LESS OPERATIONS
 * These do some messing around to determine the sign of the result,
 * then call one of BigUnsigned's copy-less operations. */

// See remarks about aliased calls in BigUnsigned.cc .
#define DTRT_ALIASED(cond, op) \
	if (cond) { \
		BigInteger tmpThis; \
		tmpThis.op; \
		*this = tmpThis; \
		return; \
	}

void BigInteger::add(const BigInteger &a, const BigInteger &b) {
	DTRT_ALIASED(this == &a || this == &b, add(a, b));
	// If one argument is zero, copy the other.
	if (a.sign == zero)
		operator =(b);
	else if (b.sign == zero)
		operator =(a);
	// If the arguments have the same sign, take the
	// common sign and add their magnitudes.
	else if (a.sign == b.sign) {
		sign = a.sign;
		mag.add(a.mag, b.mag);
	} else {
		// Otherwise, their magnitudes must be compared.
		switch (a.mag.compareTo(b.mag)) {
		case equal:
			// If their magnitudes are the same, copy zero.
			mag = 0;
			sign = zero;
			break;
			// Otherwise, take the sign of the greater, and subtract
			// the lesser magnitude from the greater magnitude.
		case greater:
			sign = a.sign;
			mag.subtract(a.mag, b.mag);
			break;
		case less:
			sign = b.sign;
			mag.subtract(b.mag, a.mag);
			break;
		}
	}
}

void BigInteger::subtract(const BigInteger &a, const BigInteger &b) {
	// Notice that this routine is identical to BigInteger::add,
	// if one replaces b.sign by its opposite.
	DTRT_ALIASED(this == &a || this == &b, subtract(a, b));
	// If a is zero, copy b and flip its sign.  If b is zero, copy a.
	if (a.sign == zero) {
		mag = b.mag;
		// Take the negative of _b_'s, sign, not ours.
		// Bug pointed out by Sam Larkin on 2005.03.30.
		sign = Sign(-b.sign);
	} else if (b.sign == zero)
		operator =(a);
	// If their signs differ, take a.sign and add the magnitudes.
	else if (a.sign != b.sign) {
		sign = a.sign;
		mag.add(a.mag, b.mag);
	} else {
		// Otherwise, their magnitudes must be compared.
		switch (a.mag.compareTo(b.mag)) {
			// If their magnitudes are the same, copy zero.
		case equal:
			mag = 0;
			sign = zero;
			break;
			// If a's magnitude is greater, take a.sign and
			// subtract a from b.
		case greater:
			sign = a.sign;
			mag.subtract(a.mag, b.mag);
			break;
			// If b's magnitude is greater, take the opposite
			// of b.sign and subtract b from a.
		case less:
			sign = Sign(-b.sign);
			mag.subtract(b.mag, a.mag);
			break;
		}
	}
}

void BigInteger::multiply(const BigInteger &a, const BigInteger &b) {
	DTRT_ALIASED(this == &a || this == &b, multiply(a, b));
	// If one object is zero, copy zero and return.
	if (a.sign == zero || b.sign == zero) {
		sign = zero;
		mag = 0;
		return;
	}
	// If the signs of the arguments are the same, the result
	// is positive, otherwise it is negative.
	sign = (a.sign == b.sign) ? positive : negative;
	// Multiply the magnitudes.
	mag.multiply(a.mag, b.mag);
}

/*
 * DIVISION WITH REMAINDER
 * Please read the comments before the definition of
 * `BigUnsigned::divideWithRemainder' in `BigUnsigned.cc' for lots of
 * information you should know before reading this function.
 *
 * Following Knuth, I decree that x / y is to be
 * 0 if y==0 and floor(real-number x / y) if y!=0.
 * Then x % y shall be x - y*(integer x / y).
 *
 * Note that x = y * (x / y) + (x % y) always holds.
 * In addition, (x % y) is from 0 to y - 1 if y > 0,
 * and from -(|y| - 1) to 0 if y < 0.  (x % y) = x if y = 0.
 *
 * Examples: (q = a / b, r = a % b)
 *	a	b	q	r
 *	===	===	===	===
 *	4	3	1	1
 *	-4	3	-2	2
 *	4	-3	-2	-2
 *	-4	-3	1	-1
 */
void BigInteger::divideWithRemainder(const BigInteger &b, BigInteger &q) {
	// Defend against aliased calls;
	// same idea as in BigUnsigned::divideWithRemainder .
	if (this == &q)
		throw "BigInteger::divideWithRemainder: Cannot write quotient and remainder into the same variable";
	if (this == &b || &q == &b) {
		BigInteger tmpB(b);
		divideWithRemainder(tmpB, q);
		return;
	}

	// Division by zero gives quotient 0 and remainder *this
	if (b.sign == zero) {
		q.mag = 0;
		q.sign = zero;
		return;
	}
	// 0 / b gives quotient 0 and remainder 0
	if (sign == zero) {
		q.mag = 0;
		q.sign = zero;
		return;
	}

	// Here *this != 0, b != 0.

	// Do the operands have the same sign?
	if (sign == b.sign) {
		// Yes: easy case.  Quotient is zero or positive.
		q.sign = positive;
	} else {
		// No: harder case.  Quotient is negative.
		q.sign = negative;
		// Decrease the magnitude of the dividend by one.
		mag--;
		/*
		 * We tinker with the dividend before and with the
		 * quotient and remainder after so that the result
		 * comes out right.  To see why it works, consider the following
		 * list of examples, where A is the magnitude-decreased
		 * a, Q and R are the results of BigUnsigned division
		 * with remainder on A and |b|, and q and r are the
		 * final results we want:
		 *
		 *	a	A	b	Q	R	q	r
		 *	-3	-2	3	0	2	-1	0
		 *	-4	-3	3	1	0	-2	2
		 *	-5	-4	3	1	1	-2	1
		 *	-6	-5	3	1	2	-2	0
		 *
		 * It appears that we need a total of 3 corrections:
		 * Decrease the magnitude of a to get A.  Increase the
		 * magnitude of Q to get q (and make it negative).
		 * Find r = (b - 1) - R and give it the desired sign.
		 */
	}

	// Divide the magnitudes.
	mag.divideWithRemainder(b.mag, q.mag);

	if (sign != b.sign) {
		// More for the harder case (as described):
		// Increase the magnitude of the quotient by one.
		q.mag++;
		// Modify the remainder.
		mag.subtract(b.mag, mag);
		mag--;
	}

	// Sign of the remainder is always the sign of the divisor b.
	sign = b.sign;

	// Set signs to zero as necessary.  (Thanks David Allen!)
	if (mag.isZero())
		sign = zero;
	if (q.mag.isZero())
		q.sign = zero;

	// WHEW!!!
}

// Negation
void BigInteger::negate(const BigInteger &a) {
	DTRT_ALIASED(this == &a, negate(a));
	// Copy a's magnitude
	mag = a.mag;
	// Copy the opposite of a.sign
	sign = Sign(-a.sign);
}

// INCREMENT/DECREMENT OPERATORS

// Prefix increment
void BigInteger::operator ++() {
	if (sign == negative) {
		mag--;
		if (mag == 0)
			sign = zero;
	} else {
		mag++;
		sign = positive; // if not already
	}
}

// Postfix increment: same as prefix
void BigInteger::operator ++(int) {
	operator ++();
}

// Prefix decrement
void BigInteger::operator --() {
	if (sign == positive) {
		mag--;
		if (mag == 0)
			sign = zero;
	} else {
		mag++;
		sign = negative;
	}
}

// Postfix decrement: same as prefix
void BigInteger::operator --(int) {
	operator --();
}

//ALGORITHMS========================================================================================
/* Some mathematical algorithms for big integers.
 * This code is new and, as such, experimental. */

// Returns the greatest common divisor of a and b.
BigUnsigned gcd(BigUnsigned a, BigUnsigned b);

/* Extended Euclidean algorithm.
 * Given m and n, finds gcd g and numbers r, s such that r*m + s*n == g. */
void extendedEuclidean(BigInteger m, BigInteger n,
		BigInteger &g, BigInteger &r, BigInteger &s);

/* Returns the multiplicative inverse of x modulo n, or throws an exception if
 * they have a common factor. */
BigUnsigned modinv(const BigInteger &x, const BigUnsigned &n);

// Returns (base ^ exponent) % modulus.
BigUnsigned modexp(const BigInteger &base, const BigUnsigned &exponent,
		const BigUnsigned &modulus);

//.cc===============================================================================================
BigUnsigned gcd(BigUnsigned a, BigUnsigned b) {
	BigUnsigned trash;
	// Neat in-place alternating technique.
	for (;;) {
		if (b.isZero())
			return a;
		a.divideWithRemainder(b, trash);
		if (a.isZero())
			return b;
		b.divideWithRemainder(a, trash);
	}
}

void extendedEuclidean(BigInteger m, BigInteger n,
		BigInteger &g, BigInteger &r, BigInteger &s) {
	if (&g == &r || &g == &s || &r == &s)
		throw "BigInteger extendedEuclidean: Outputs are aliased";
	BigInteger r1(1), s1(0), r2(0), s2(1), q;
	/* Invariants:
	 * r1*m(orig) + s1*n(orig) == m(current)
	 * r2*m(orig) + s2*n(orig) == n(current) */
	for (;;) {
		if (n.isZero()) {
			r = r1; s = s1; g = m;
			return;
		}
		// Subtract q times the second invariant from the first invariant.
		m.divideWithRemainder(n, q);
		r1 -= q*r2; s1 -= q*s2;

		if (m.isZero()) {
			r = r2; s = s2; g = n;
			return;
		}
		// Subtract q times the first invariant from the second invariant.
		n.divideWithRemainder(m, q);
		r2 -= q*r1; s2 -= q*s1;
	}
}

BigUnsigned modinv(const BigInteger &x, const BigUnsigned &n) {
	BigInteger g, r, s;
	extendedEuclidean(x, n, g, r, s);
	if (g == 1)
		// r*x + s*n == 1, so r*x === 1 (mod n), so r is the answer.
		return (r % n).getMagnitude(); // (r % n) will be nonnegative
	else
		throw "BigInteger modinv: x and n have a common factor";
}

BigUnsigned modexp(const BigInteger &base, const BigUnsigned &exponent,
		const BigUnsigned &modulus) {
	BigUnsigned ans = 1, base2 = (base % modulus).getMagnitude();
	BigUnsigned::Index i = exponent.bitLength();
	// For each bit of the exponent, most to least significant...
	while (i > 0) {
		i--;
		// Square.
		ans *= ans;
		ans %= modulus;
		// And multiply if the bit is a 1.
		if (exponent.getBit(i)) {
			ans *= base2;
			ans %= modulus;
		}
	}
	return ans;
}

// BIGUNSIGNEDINBASE================================================================================
#include <string>

/*
 * A BigUnsignedInABase object represents a nonnegative integer of size limited
 * only by available memory, represented in a user-specified base that can fit
 * in an `unsigned short' (most can, and this saves memory).
 *
 * BigUnsignedInABase is intended as an intermediary class with little
 * functionality of its own.  BigUnsignedInABase objects can be constructed
 * from, and converted to, BigUnsigneds (requiring multiplication, mods, etc.)
 * and `std::string's (by switching digit values for appropriate characters).
 *
 * BigUnsignedInABase is similar to BigUnsigned.  Note the following:
 *
 * (1) They represent the number in exactly the same way, except that
 * BigUnsignedInABase uses ``digits'' (or Digit) where BigUnsigned uses
 * ``blocks'' (or Blk).
 *
 * (2) Both use the management features of NumberlikeArray.  (In fact, my desire
 * to add a BigUnsignedInABase class without duplicating a lot of code led me to
 * introduce NumberlikeArray.)
 *
 * (3) The only arithmetic operation supported by BigUnsignedInABase is an
 * equality test.  Use BigUnsigned for arithmetic.
 */

class BigUnsignedInABase : protected NumberlikeArray<unsigned short> {

public:
	// The digits of a BigUnsignedInABase are unsigned shorts.
	typedef unsigned short Digit;
	// That's also the type of a base.
	typedef Digit Base;

protected:
	// The base in which this BigUnsignedInABase is expressed
	Base base;

	// Creates a BigUnsignedInABase with a capacity; for internal use.
	BigUnsignedInABase(int, Index c) : NumberlikeArray<Digit>(0, c) {}

	// Decreases len to eliminate any leading zero digits.
	void zapLeadingZeros() { 
		while (len > 0 && blk[len - 1] == 0)
			len--;
	}

public:
	// Constructs zero in base 2.
	BigUnsignedInABase() : NumberlikeArray<Digit>(), base(2) {}

	// Copy constructor
	BigUnsignedInABase(const BigUnsignedInABase &x) : NumberlikeArray<Digit>(x), base(x.base) {}

	// Assignment operator
	void operator =(const BigUnsignedInABase &x) {
		NumberlikeArray<Digit>::operator =(x);
		base = x.base;
	}

	// Constructor that copies from a given array of digits.
	BigUnsignedInABase(const Digit *d, Index l, Base base);

	// Destructor.  NumberlikeArray does the delete for us.
	~BigUnsignedInABase() {}

	// LINKS TO BIGUNSIGNED
	BigUnsignedInABase(const BigUnsigned &x, Base base);
	operator BigUnsigned() const;

	/* LINKS TO STRINGS
	 *
	 * These use the symbols ``0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'' to
	 * represent digits of 0 through 35.  When parsing strings, lowercase is
	 * also accepted.
	 *
	 * All string representations are big-endian (big-place-value digits
	 * first).  (Computer scientists have adopted zero-based counting; why
	 * can't they tolerate little-endian numbers?)
	 *
	 * No string representation has a ``base indicator'' like ``0x''.
	 *
	 * An exception is made for zero: it is converted to ``0'' and not the
	 * empty string.
	 *
	 * If you want different conventions, write your own routines to go
	 * between BigUnsignedInABase and strings.  It's not hard.
	 */
	operator std::string() const;
	BigUnsignedInABase(const std::string &s, Base base);

public:

	// ACCESSORS
	Base getBase() const { return base; }

	// Expose these from NumberlikeArray directly.
	NumberlikeArray<Digit>::getCapacity;
	NumberlikeArray<Digit>::getLength;

	/* Returns the requested digit, or 0 if it is beyond the length (as if
	 * the number had 0s infinitely to the left). */
	Digit getDigit(Index i) const { return i >= len ? 0 : blk[i]; }

	// The number is zero if and only if the canonical length is zero.
	bool isZero() const { return NumberlikeArray<Digit>::isEmpty(); }

	/* Equality test.  For the purposes of this test, two BigUnsignedInABase
	 * values must have the same base to be equal. */ 
	bool operator ==(const BigUnsignedInABase &x) const {
		return base == x.base && NumberlikeArray<Digit>::operator ==(x);
	}
	bool operator !=(const BigUnsignedInABase &x) const { return !operator ==(x); }

};

//.cc======================================================
BigUnsignedInABase::BigUnsignedInABase(const Digit *d, Index l, Base base)
	: NumberlikeArray<Digit>(d, l), base(base) {
	// Check the base
	if (base < 2)
		throw "BigUnsignedInABase::BigUnsignedInABase(const Digit *, Index, Base): The base must be at least 2";

	// Validate the digits.
	for (Index i = 0; i < l; i++)
		if (blk[i] >= base)
			throw "BigUnsignedInABase::BigUnsignedInABase(const Digit *, Index, Base): A digit is too large for the specified base";

	// Eliminate any leading zeros we may have been passed.
	zapLeadingZeros();
}

namespace {
	unsigned int bitLen(unsigned int x) {
		unsigned int len = 0;
		while (x > 0) {
			x >>= 1;
			len++;
		}
		return len;
	}
	unsigned int ceilingDiv(unsigned int a, unsigned int b) {
		return (a + b - 1) / b;
	}
}

BigUnsignedInABase::BigUnsignedInABase(const BigUnsigned &x, Base base) {
	// Check the base
	if (base < 2)
		throw "BigUnsignedInABase(BigUnsigned, Base): The base must be at least 2";
	this->base = base;

	// Get an upper bound on how much space we need
	int maxBitLenOfX = x.getLength() * BigUnsigned::N;
	int minBitsPerDigit = bitLen(base) - 1;
	int maxDigitLenOfX = ceilingDiv(maxBitLenOfX, minBitsPerDigit);
	len = maxDigitLenOfX; // Another change to comply with `staying in bounds'.
	allocate(len); // Get the space

	BigUnsigned x2(x), buBase(base);
	Index digitNum = 0;

	while (!x2.isZero()) {
		// Get last digit.  This is like `lastDigit = x2 % buBase, x2 /= buBase'.
		BigUnsigned lastDigit(x2);
		lastDigit.divideWithRemainder(buBase, x2);
		// Save the digit.
		blk[digitNum] = lastDigit.toUnsignedShort();
		// Move on.  We can't run out of room: we figured it out above.
		digitNum++;
	}

	// Save the actual length.
	len = digitNum;
}

BigUnsignedInABase::operator BigUnsigned() const {
	BigUnsigned ans(0), buBase(base), temp;
	Index digitNum = len;
	while (digitNum > 0) {
		digitNum--;
		temp.multiply(ans, buBase);
		ans.add(temp, BigUnsigned(blk[digitNum]));
	}
	return ans;
}

BigUnsignedInABase::BigUnsignedInABase(const std::string &s, Base base) {
	// Check the base.
	if (base > 36)
		throw "BigUnsignedInABase(std::string, Base): The default string conversion routines use the symbol set 0-9, A-Z and therefore support only up to base 36.  You tried a conversion with a base over 36; write your own string conversion routine.";
	// Save the base.
	// This pattern is seldom seen in C++, but the analogous ``this.'' is common in Java.
	this->base = base;

	// `s.length()' is a `size_t', while `len' is a `NumberlikeArray::Index',
	// also known as an `unsigned int'.  Some compilers warn without this cast.
	len = Index(s.length());
	allocate(len);

	Index digitNum, symbolNumInString;
	for (digitNum = 0; digitNum < len; digitNum++) {
		symbolNumInString = len - 1 - digitNum;
		char theSymbol = s[symbolNumInString];
		if (theSymbol >= '0' && theSymbol <= '9')
			blk[digitNum] = theSymbol - '0';
		else if (theSymbol >= 'A' && theSymbol <= 'Z')
			blk[digitNum] = theSymbol - 'A' + 10;
		else if (theSymbol >= 'a' && theSymbol <= 'z')
			blk[digitNum] = theSymbol - 'a' + 10;
		else
			throw "BigUnsignedInABase(std::string, Base): Bad symbol in input.  Only 0-9, A-Z, a-z are accepted.";

		if (blk[digitNum] >= base)
			throw "BigUnsignedInABase::BigUnsignedInABase(const Digit *, Index, Base): A digit is too large for the specified base";
	}
	zapLeadingZeros();
}

BigUnsignedInABase::operator std::string() const {
	if (base > 36)
		throw "BigUnsignedInABase ==> std::string: The default string conversion routines use the symbol set 0-9, A-Z and therefore support only up to base 36.  You tried a conversion with a base over 36; write your own string conversion routine.";
	if (len == 0)
		return std::string("0");
	// Some compilers don't have push_back, so use a char * buffer instead.
	char *s = new char[len + 1];
	s[len] = '\0';
	Index digitNum, symbolNumInString;
	for (symbolNumInString = 0; symbolNumInString < len; symbolNumInString++) {
		digitNum = len - 1 - symbolNumInString;
		Digit theDigit = blk[digitNum];
		if (theDigit < 10)
			s[symbolNumInString] = char('0' + theDigit);
		else
			s[symbolNumInString] = char('A' + theDigit - 10);
	}
	std::string s2(s);
	delete [] s;
	return s2;
}


// UTILS============================================================================================

#include <string>
#include <iostream>

/* This file provides:
 * - Convenient std::string <-> BigUnsigned/BigInteger conversion routines
 * - std::ostream << operators for BigUnsigned/BigInteger */

// std::string conversion routines.  Base 10 only.
std::string bigUnsignedToString(const BigUnsigned &x);
std::string bigIntegerToString(const BigInteger &x);
BigUnsigned stringToBigUnsigned(const std::string &s);
BigInteger stringToBigInteger(const std::string &s);

// Creates a BigInteger from data such as `char's; read below for details.
template <class T>
BigInteger dataToBigInteger(const T* data, BigInteger::Index length, BigInteger::Sign sign);

// Outputs x to os, obeying the flags `dec', `hex', `bin', and `showbase'.
std::ostream &operator <<(std::ostream &os, const BigUnsigned &x);

// Outputs x to os, obeying the flags `dec', `hex', `bin', and `showbase'.
// My somewhat arbitrary policy: a negative sign comes before a base indicator (like -0xFF).
std::ostream &operator <<(std::ostream &os, const BigInteger &x);

// BEGIN TEMPLATE DEFINITIONS.

/*
 * Converts binary data to a BigInteger.
 * Pass an array `data', its length, and the desired sign.
 *
 * Elements of `data' may be of any type `T' that has the following
 * two properties (this includes almost all integral types):
 *
 * (1) `sizeof(T)' correctly gives the amount of binary data in one
 * value of `T' and is a factor of `sizeof(Blk)'.
 *
 * (2) When a value of `T' is casted to a `Blk', the low bytes of
 * the result contain the desired binary data.
 */
template <class T>
BigInteger dataToBigInteger(const T* data, BigInteger::Index length, BigInteger::Sign sign) {
	// really ceiling(numBytes / sizeof(BigInteger::Blk))
	unsigned int pieceSizeInBits = 8 * sizeof(T);
	unsigned int piecesPerBlock = sizeof(BigInteger::Blk) / sizeof(T);
	unsigned int numBlocks = (length + piecesPerBlock - 1) / piecesPerBlock;

	// Allocate our block array
	BigInteger::Blk *blocks = new BigInteger::Blk[numBlocks];

	BigInteger::Index blockNum, pieceNum, pieceNumHere;

	// Convert
	for (blockNum = 0, pieceNum = 0; blockNum < numBlocks; blockNum++) {
		BigInteger::Blk curBlock = 0;
		for (pieceNumHere = 0; pieceNumHere < piecesPerBlock && pieceNum < length;
			pieceNumHere++, pieceNum++)
			curBlock |= (BigInteger::Blk(data[pieceNum]) << (pieceSizeInBits * pieceNumHere));
		blocks[blockNum] = curBlock;
	}

	// Create the BigInteger.
	BigInteger x(blocks, numBlocks, sign);

	delete [] blocks;
	return x;
}

//.cc===============================================================================================
std::string bigUnsignedToString(const BigUnsigned &x) {
	return std::string(BigUnsignedInABase(x, 10));
}

std::string bigIntegerToString(const BigInteger &x) {
	return (x.getSign() == BigInteger::negative)
		? (std::string("-") + bigUnsignedToString(x.getMagnitude()))
		: (bigUnsignedToString(x.getMagnitude()));
}

BigUnsigned stringToBigUnsigned(const std::string &s) {
	return BigUnsigned(BigUnsignedInABase(s, 10));
}

BigInteger stringToBigInteger(const std::string &s) {
	// Recognize a sign followed by a BigUnsigned.
	return (s[0] == '-') ? BigInteger(stringToBigUnsigned(s.substr(1, s.length() - 1)), BigInteger::negative)
		: (s[0] == '+') ? BigInteger(stringToBigUnsigned(s.substr(1, s.length() - 1)))
		: BigInteger(stringToBigUnsigned(s));
}

std::ostream &operator <<(std::ostream &os, const BigUnsigned &x) {
	BigUnsignedInABase::Base base;
	long osFlags = os.flags();
	if (osFlags & os.dec)
		base = 10;
	else if (osFlags & os.hex) {
		base = 16;
		if (osFlags & os.showbase)
			os << "0x";
	} else if (osFlags & os.oct) {
		base = 8;
		if (osFlags & os.showbase)
			os << '0';
	} else
		throw "std::ostream << BigUnsigned: Could not determine the desired base from output-stream flags";
	std::string s = std::string(BigUnsignedInABase(x, base));
	os << s;
	return os;
}

std::ostream &operator <<(std::ostream &os, const BigInteger &x) {
	if (x.getSign() == BigInteger::negative)
		os << '-';
	os << x.getMagnitude();
	return os;
}