#include <corecrt_memory.h>
class Memory {
	public:
		unsigned char read(unsigned short address);
		void write(unsigned short address, unsigned char val);
		void clear();

	private:
		unsigned char ram[8192];
};