#pragma
#include <iostream>

enum FLAGS {
	ZERO = 7,
	SUB = 6,
	HALF = 5,
	CARRY = 4
};

//Class for F Register
class FlagRegister {
private:
	unsigned char F;

public:
	FlagRegister() {
		F = 0;
	}

	unsigned char getFlag(int type) {
		return (F >> type) & 1;
	}

	unsigned char& getFlag() {
		return F;
	}

	void setFlag(bool set[4]) {
		setFlag(CARRY, set[0]);
		setFlag(HALF, set[1]);
		setFlag(SUB, set[2]);
		setFlag(ZERO, set[3]);
	}
	

	void setFlag(int type, bool set) {
		if (set) {
			F = F | (1 << type);
			return;
		}
		F = F & ~(1 << type);
	}

	operator unsigned char() const {
		return F;
	}

	operator unsigned char&() {
		return F;
	}
	
	void operator=(const unsigned short val) {
		F = val;
	}
	

};


class Register16 {
private:
	unsigned char& high;
	unsigned char& low;

public:
	Register16(unsigned char& high, unsigned char& low) : high(high), low(low) {}

	unsigned short read() {
		return (high << 8) | low;
	}

	void write(unsigned short val) {
		high = (val & 0xFF00) >> 8;
		low = val & 0xFF;
	}

	operator unsigned short() {
		return read();
	}

	void operator=(const unsigned short val) {
		write(val);
	}

	unsigned char& getHigh() {
		return high;
	}

	unsigned char& getLow() {
		return low;
	}

	unsigned short operator+=(const unsigned short val) {
		write(read() + val);
		return read();
	}

	//Post fix increment operator
	unsigned short operator++(int) {
		unsigned short temp = read();
		write(read() + 1);
		return temp;
	}

	//Prefix increment operator 
	unsigned short operator++() {
		write(read() + 1);
		return read();
	}

	unsigned short operator-=(const unsigned short val) {
		write(read() - val);
		return read();
	}

	//Postfix decrement operator
	unsigned short operator--(int) {
		unsigned short temp = read();
		write(read() - 1);
		return temp;
	}

	//Prefix decrement operator
	unsigned short operator--() {
		write(read() - 1);
		return read();
	}
};