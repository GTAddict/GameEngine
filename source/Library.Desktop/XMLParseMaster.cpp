#include "pch.h"
#include "XMLParseMaster.h"
#include "IXMLParseHelper.h"
#include "expat.h"
#include <fstream>

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(XMLParseMaster::SharedData);

		XMLParseMaster::SharedData::SharedData()
			: mpParseMaster(nullptr)
			, mDepth(0)
		{
		}

		void XMLParseMaster::SharedData::SetXMLParseMaster(XMLParseMaster* parseMaster)
		{
			mpParseMaster = parseMaster;
		};

		XMLParseMaster* XMLParseMaster::SharedData::GetXMLParseMaster() const
		{
			return mpParseMaster;
		};

		void XMLParseMaster::SharedData::IncrementDepth()
		{
			++mDepth;
		}

		void XMLParseMaster::SharedData::DecrementDepth()
		{
			if (mDepth > 0)
			{
				--mDepth;
			}
		}

		std::uint32_t XMLParseMaster::SharedData::GetDepth() const
		{
			return mDepth;
		}

		XMLParseMaster::XMLParseMaster(SharedData* data)
			: mpSharedData(nullptr)
			, mParser(XML_ParserCreate(nullptr))
			, mIsClone(false)
		{
			SetSharedData(data);
		}

		XMLParseMaster::~XMLParseMaster()
		{
			XML_ParserFree(mParser);

			if (mIsClone)
			{
				for (IXMLParseHelper* helper : mHelperList)
				{
					delete helper;
				}

				delete mpSharedData;
			}
		}

		XMLParseMaster* XMLParseMaster::Clone() const
		{
			XMLParseMaster* pClone = new XMLParseMaster(mpSharedData->Clone());

			for (IXMLParseHelper* helper : mHelperList)
			{
				pClone->AddHelper(helper->Clone());
			}

			pClone->mIsClone = true;

			return pClone;
		}

		void XMLParseMaster::AddHelper(IXMLParseHelper* helper)
		{
			if (mIsClone)
			{
				throw std::runtime_error("You cannot add a helper to a clone!");
			}

			if (mHelperList.Find(helper) == mHelperList.end())
			{
				mHelperList.PushBack(helper);
			}
			else
			{
				throw std::invalid_argument("You've already added this helper to the list!");
			}

		}

		void XMLParseMaster::RemoveHelper(IXMLParseHelper* helper)
		{
			if (mIsClone)
			{
				throw std::runtime_error("You cannot remove a helper from a clone!");
			}

			mHelperList.Remove(helper);
		}

		void XMLParseMaster::Parse(const char* data, const std::uint32_t length, bool isInitial, bool isFinal)
		{
			if (isInitial)
			{
				ResetParser();
				for (IXMLParseHelper* helper : mHelperList)
				{
					helper->Initialize(mpSharedData);
				}
			}

			if (XML_Parse(mParser, data, length, isFinal) == XML_STATUS_ERROR)
			{
				throw std::runtime_error("Error parsing file: " + std::string(XML_ErrorString(XML_GetErrorCode(mParser))));
			}

			if (isFinal)
			{
				for (IXMLParseHelper* helper : mHelperList)
				{
					helper->Finalize();
				}
			}
		}

		void XMLParseMaster::ParseFromFile(const std::string& filename)
		{
			mFileName = filename;

			std::ifstream fileStream(mFileName, std::ios::binary);

			if (fileStream.good())
			{
				std::string buffer = std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
				Parse(buffer.c_str(), static_cast<std::uint32_t>(buffer.length()), XML_TRUE, XML_TRUE);
				fileStream.close();
			}
			else
			{
				throw std::runtime_error("Could not open file!");
			}
		}

		const std::string& XMLParseMaster::GetFileName() const
		{
			return mFileName;
		}

		XMLParseMaster::SharedData* XMLParseMaster::GetSharedData() const
		{
			return mpSharedData;
		}

		void XMLParseMaster::SetSharedData(SharedData* data)
		{
			if (mIsClone)
			{
				delete mpSharedData;
			}

			mpSharedData = data;
			if (mpSharedData)
			{
				mpSharedData->SetXMLParseMaster(this);
			}
		}

		const SList<IXMLParseHelper*>& XMLParseMaster::GetHelperList()
		{
			return mHelperList;
		}

		void XMLParseMaster::ResetParser()
		{
			XML_ParserReset(mParser, nullptr);
			XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
			XML_SetCharacterDataHandler(mParser, CharDataHandler);
			XML_SetUserData(mParser, reinterpret_cast<void*>(this));
		}

		void XMLParseMaster::StartElementHandler(void* data, const char* element, const char** attribute)
		{
			XMLParseMaster* parseMaster = reinterpret_cast<XMLParseMaster*>(data);

			if (parseMaster)
			{
				parseMaster->GetSharedData()->IncrementDepth();

				HashMap<std::string, std::string> attributeMap;

				for (std::uint32_t i = 0; attribute[i] != nullptr; i += 2)
				{
					attributeMap[attribute[i]] = attribute[i + 1];
				}

				for (IXMLParseHelper* helper : parseMaster->mHelperList)
				{
					if (helper->StartElementHandler(element, attributeMap))
					{
						break;
					}
				}
			}

		}

		void XMLParseMaster::EndElementHandler(void* data, const char* element)
		{
			XMLParseMaster* parseMaster = reinterpret_cast<XMLParseMaster*>(data);

			if (parseMaster)
			{
				for (IXMLParseHelper* helper : parseMaster->mHelperList)
				{
					if (helper->EndElementHandler(element))
					{
						break;
					}
				}

				parseMaster->GetSharedData()->DecrementDepth();
			}
		}

		void XMLParseMaster::CharDataHandler(void* data, const char* content, int length)
		{
			XMLParseMaster* parseMaster = reinterpret_cast<XMLParseMaster*>(data);

			if (parseMaster)
			{
				for (IXMLParseHelper* helper : parseMaster->mHelperList)
				{
					if (helper->CharDataHandler(content, length))
					{
						break;
					}
				}
			}
		}
	}
}