#pragma once
#include <cstdint>
#include <string>

// Resources used:
// http://web.archive.org/web/20071223173210/http://www.concentric.net/~Ttwang/tech/inthash.htm
// http://www.cse.yorku.ca/~oz/hash.html


namespace GameEngine
{
	namespace Library
	{
		struct DefaultHashFunctor
		{
			template <typename T>
			std::uint32_t operator()(const T& key) const
			{
				static_assert(false, "Provide template T specialization for your class "__FUNCSIG__".");
			}

			template <typename T>
			std::uint32_t operator()(const T* key) const
			{
				return operator()(reinterpret_cast<const std::int32_t*>(key));
			}
			
			template <typename T>
			std::uint32_t operator()(T* key) const
			{
				return operator()(const_cast<const T*>(key));
			}
			
			template <>
			std::uint32_t operator()(const std::int32_t& key) const
			{
				std::int32_t prime = 0x27d4eb2d;
				std::int32_t hash = key;

				hash = (hash ^ 61) ^ (hash >> 16);
				hash = hash + (hash << 3);
				hash = hash ^ (hash >> 4);
				hash = hash * prime;
				hash = hash ^ (hash >> 15);

				return hash;
			}

			template <> std::uint32_t operator()(const char& key)			const	{ return operator()((std::int32_t) key); }
			template <> std::uint32_t operator()(const bool& key)			const	{ return operator()((std::int32_t) key); }
			template <> std::uint32_t operator()(const float& key)			const	{ return operator()(reinterpret_cast<const int*>(&key)); }
			template <> std::uint32_t operator()(const std::string& key)	const	{ return operator()(key.c_str()); }

			template <> std::uint32_t operator()(const std::int32_t* key)	const	{ return operator()(*key); }
			template <> std::uint32_t operator()(const bool* key)			const	{ return operator()(*key); }
			template <> std::uint32_t operator()(const float* key)			const	{ return operator()(*key); }
			template <> std::uint32_t operator()(const std::string* key)	const	{ return operator()(key->c_str()); }

#pragma warning (disable : 4706)
			template <>
			std::uint32_t operator()(const char* key) const
			{
				unsigned long hash = 5381;
				int c;

				while (c = *key++)
					hash = ((hash << 5) + hash) + c;
			
				return hash;
			}
		};
	}
}