enum FLAGS {
	ZERO = 7,
	SUB = 6,
	HALF = 5,
	CARRY = 4
};

class Flag {
private:
	unsigned char flag;

public:
	Flag() {
		flag = 0;
	}

	unsigned char getFlag(int type) {
		return (flag & (1 << type)) >> type;
	}

	unsigned char getFlag() {
		return flag;
	}

	void setFlag(bool set[4]) {
		setFlag(CARRY, set[0]);
		setFlag(HALF, set[1]);
		setFlag(SUB, set[2]);
		setFlag(ZERO, set[3]);
	}
	

	void setFlag(int type, bool set) {
		if (set) {
			flag = flag | (1 << type);
			return;
		}
		flag = flag & ~(1 << type);
	}


};