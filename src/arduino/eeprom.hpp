#ifndef __ASTL_EEPROM_HPP__
#define __ASTL_EEPROM_HPP__

#include <EEPROM.h>

namespace arduino {
	class eeprom {
	public:
	    template<class T>
		static int write(const T& buf, int addr) {
			const byte* p = (const byte*)(const void*)&buf;
			unsigned int i = 0;
			for ( i = 0; i < sizeof(buf); i++)
				EEPROM.write(addr++, *p++);
			return i;
		}
		template<class T>
		static int read(T& buf, int addr) {
			byte* p = (byte*)(void*)&buf;
			unsigned int i =0;
			for ( i = 0; i < sizeof(buf); i++)
				*p++ = EEPROM.read(addr++);
			return i;
		}
		static void clear() {
			for (int i = 0 ; i < EEPROM.length() ; i++) 
				EEPROM.write(i, 0);
		}
	};
}

#endif