#include "pch.h"
#include "Scope.h"
#include <string>

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(Scope);

		Scope::Scope(const std::uint32_t size)
			: mpParent(nullptr)
		{
			mVector.Reserve(size);
		}

		Scope::Scope(const Scope& rhs)
			: mpParent(nullptr)
		{
			operator=(rhs);
		}

		Scope::Scope(Scope&& rhs)
			: mHashMap(std::move(rhs.mHashMap))
			, mVector(std::move(rhs.mVector))
			, mpParent(rhs.mpParent)
		{
			rhs.mpParent = nullptr;
		}

		Scope& Scope::operator=(const Scope& rhs)
		{
			if (this != &rhs)
			{
				Clear();

				mVector.Reserve(rhs.mVector.Capacity());

				HashMapType::Iterator it;

				for (ElementType* element : rhs.mVector)
				{
					// We could call AppendScope here and then Search 
					// immediately after. Consider the tradeoff - reusable
					// code vs. faster code.
					if (element->second.Type() == Datum::DatumType::Table)
					{
						Datum& datum = Append(element->first);

						if (datum.Type() == Datum::DatumType::Unknown)
						{
							datum.SetType(Datum::DatumType::Table);
						}

						if (datum.Type() != Datum::DatumType::Table)
						{
							throw std::runtime_error("Datum with key" + element->first + "is not a scope.");
						}

						for (std::uint32_t i = 0; i < element->second.Size(); ++i)
						{
							Scope* scope = new Scope(element->second[i]);
							scope->mpParent = this;
							datum.PushBack(scope);
						}
					}
					else
					{
						mHashMap.Insert(*element, it);
						mVector.PushBack(&(*it));
					}
				}
			}

			return *this;
		}

		Scope& Scope::operator=(Scope&& rhs)
		{
			if (this != &rhs)
			{
				Clear();

				mHashMap = std::move(rhs.mHashMap);
				mVector = std::move(rhs.mVector);
				mpParent = rhs.mpParent;

				rhs.mpParent = nullptr;

				// You could FindName on the right scope, orphan
				// it, and adopt it back into mpParent. That would
				// be shorter code and code that's reused, but
				// that would do 2 searches. This is more optimized.
				if (mpParent)
				{
					// Update the parent to point to the new moved address
					for (auto entry : mpParent->mVector)
					{
						Datum& datum = entry->second;

						if (datum.Type() == Datum::DatumType::Table)
						{
							for (std::uint32_t i = 0; i < datum.Size(); ++i)
							{
								if (datum.Get<Scope*>(i) == &rhs)
								{
									datum.Set(this, i);
									break;
								}
							}
						}
					}
				}

				// Update all the children to point to the new moved address
				for (ElementType* element : mVector)
				{
					Datum& datum = element->second;

					if (datum.Type() == Datum::DatumType::Table)
					{
						for (std::uint32_t i = 0; i < datum.Size(); ++i)
						{
							datum.Get<Scope*>(i)->mpParent = this;
						}
					}
				}
			}

			return *this;
		}

		Scope::~Scope()
		{
			Clear();
			mpParent = nullptr;
		}

		bool Scope::Equals(const RTTI* rhs) const
		{
			return (*this == *rhs->As<Scope>());
		}

		bool Scope::operator==(const Scope& rhs) const
		{
			std::uint32_t size = mVector.Size();

			if (size == rhs.mVector.Size())
			{
				for (std::uint32_t i = 0; i < size; ++i)
				{
					if (*mVector[i] != *rhs.mVector[i])
					{
						return false;
					}
				}

				return true;
			}

			return false;
		}

		bool Scope::operator!=(const Scope& rhs) const
		{
			return !(*this == rhs);
		}

		Datum& Scope::operator[](const std::string& name)
		{
			return Append(name);
		}

		Datum& Scope::operator[](const std::uint32_t index)
		{
			return mVector.At(index)->second;
		}

		const Datum& Scope::operator[](const std::string& name) const
		{
			Datum* foundDatum = Find(name);

			if (foundDatum == nullptr)
			{
				throw std::out_of_range("Requested key " + name + " does not exist.");
			}

			return *foundDatum;
		}

		const Datum& Scope::operator[](const std::uint32_t index) const
		{
			return mVector.At(index)->second;
		}

		Datum* Scope::Find(const std::string& name) const
		{
			HashMapType::Iterator it = mHashMap.Find(name);
			
			if (it != mHashMap.end())
			{
				return &(it->second);
			}

			return nullptr;
		}

		Datum* Scope::Search(const std::string& name, Scope** outScope)
		{
			Datum* foundDatum = Find(name);

			if (foundDatum != nullptr)
			{
				if (outScope != nullptr)
				{
					*outScope = this;
				}

				return foundDatum;
			}

			if (mpParent)
			{
				return mpParent->Search(name, outScope);
			}
			
			return nullptr;
		}

		Datum& Scope::Append(const std::string& name)
		{
			HashMapType::Iterator it;
			ElementType element = std::pair<std::string, Datum>(name, Datum());
			bool newEntry = mHashMap.Insert(element, it);

			if (newEntry)
			{
				mVector.PushBack(&(*it));
			}

			return it->second;
		}

		Scope& Scope::AppendScope(const std::string& name, Scope* scope)
		{
			Datum& datum = Append(name);

			if (datum.Type() == Datum::DatumType::Unknown)
			{
				datum.SetType(Datum::DatumType::Table); 
			}

			if (datum.Type() != Datum::DatumType::Table)
			{
				throw std::runtime_error("Datum with key" + name + "is not a scope.");
			}

			Scope* newScope = scope ? scope : new Scope();
			newScope->mpParent = this;
			datum.PushBack(newScope);

			return *newScope;
		}

		Scope* Scope::GetParent() const
		{
			return mpParent;
		}

		std::string Scope::FindName(const Scope& scope) const
		{
			for (auto entry : mVector)
			{
				if (entry->second.Type() == Datum::DatumType::Table)
				{
					for (std::uint32_t i = 0; i < entry->second.Size(); ++i)
					{
						if (entry->second.Get<Scope*>(i) == &scope)
						{
							return entry->first;
						}
					}
				}
			}

			return std::string();
		}

		void Scope::Adopt(Scope& child, const std::string& name)
		{
			if (&child == this)
			{
				throw std::runtime_error("A scope instance cannot adopt itself.");
			}

			child.Orphan();
			AppendScope(name, &child);
		}

		void Scope::Clear()
		{
			for (VectorType::Iterator it = mVector.begin(); it != mVector.end(); ++it)
			{
				Datum& datum = (*it)->second;

				if (datum.Type() == Datum::DatumType::Table)
				{
					for (std::uint32_t i = 0; i < datum.Size(); ++i)
					{
						delete datum.Get<Scope*>(i);
					}
				}

				datum.Clear();
			}

			mVector.Clear();
			mHashMap.Clear();
		}

		std::uint32_t Scope::Size() const
		{
			assert(mHashMap.Size() == mVector.Size());
			return mVector.Size();
		}

		Scope::VectorType::Iterator Scope::begin() const
		{
			return mVector.begin();
		}

		Scope::VectorType::Iterator Scope::end() const
		{
			return mVector.end();
		}

		void Scope::Orphan()
		{
			if (mpParent)
			{
				for (VectorType::Iterator it = mpParent->mVector.begin(); it != mpParent->mVector.end(); ++it)
				{
					if ((*it)->second.Type() == Datum::DatumType::Table)
					{
						if ((*it)->second.Remove(this))
						{
							break;
						}
					}
				}

				mpParent = nullptr;
			}
		}
	}
}