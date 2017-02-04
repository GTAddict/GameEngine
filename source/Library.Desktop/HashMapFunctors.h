#pragma once
#include <cstdint>
#include <string>

namespace GameEngine
{
	namespace Library
	{
		struct DefaultHashFunctor
		{
			template <typename T>
			std::uint32_t operator()(const T key)
			{
				static_assert(false, "Provide template T specialization for your class.");
			}
			
			// http://web.archive.org/web/20071223173210/http://www.concentric.net/~Ttwang/tech/inthash.htm
			template <typename T = std::int32_t>
			std::uint32_t operator()(const std::int32_t key)
			{
				std::int32_t prime = 0x27d4eb2d; // a prime or an odd constant
				std::int32_t hash = key;

				hash = (hash ^ 61) ^ (hash >> 16);
				hash = hash + (hash << 3);
				hash = hash ^ (hash >> 4);
				hash = hash * prime;
				hash = hash ^ (hash >> 15);

				return hash;
			}

			template <typename T = int32_t*>
			std::uint32_t operator()(const std::int32_t* key)
			{
				return operator()(*key);
			}

			template <typename T = float>
			std::uint32_t operator()(const float key)
			{
				return operator()(reinterpret_cast<int*>(&key));
			}

			template <typename T = float*>
			std::uint32_t operator()(const float* key)
			{
				return operator()(*key);
			}

			// http://www.cse.yorku.ca/~oz/hash.html
			// djb2
			template <typename T = char*>
			std::uint32_t operator()(const char* key)
			{
				unsigned long hash = 5381;
				int c;

				while (c = *key++)
					hash = ((hash << 5) + hash) + c;

				return hash;
			}

			template <typename T = std::string>
			std::uint32_t operator()(const std::string key)
			{
				return operator()(key.c_str());
			}
		};
	}
}