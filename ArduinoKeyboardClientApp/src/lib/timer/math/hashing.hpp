#pragma once

#include <string>

namespace shared::math {

	inline constexpr unsigned int fnv(const char* str) {
		constexpr unsigned int fnv_prime = 0x811C9DC5;
		unsigned int hash = 0;
		unsigned int i = 0;
		std::size_t len = std::char_traits<char>::length(str);

		for (i = 0; i < len; i++)
		{
			hash *= fnv_prime;
			hash ^= (str[i]);
		}

		return hash;
	}
}