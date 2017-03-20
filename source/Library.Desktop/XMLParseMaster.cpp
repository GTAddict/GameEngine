#include "pch.h"
#include "XMLParseMaster.h"
#include "IXMLParseHelper.h"
#include "expat.h"

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

		XMLParseMaster::SharedData* XMLParseMaster::SharedData::Clone() const
		{
			SharedData* pClone = new SharedData();
			pClone->SetXMLParseMaster(mpParseMaster);
			return pClone;
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
			--mDepth;
		}

		std::uint32_t XMLParseMaster::SharedData::GetDepth() const
		{
			return mDepth;
		}

		XMLParseMaster::XMLParseMaster(SharedData* data)
			: mpSharedData(nullptr)
			, mIsClone(false)
		{
			SetSharedData(data);

			mParser = XML_ParserCreate(nullptr);
			XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
			XML_SetCharacterDataHandler(mParser, CharDataHandler);
			XML_SetUserData(mParser, static_cast<void*>(this));
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
			mHelperList.PushBack(helper);
		}

		void XMLParseMaster::RemoveHelper(IXMLParseHelper* helper)
		{
			mHelperList.Remove(helper);
		}

		void XMLParseMaster::Parse(const char* data, const std::uint32_t length, bool isFinal) const
		{
			XML_Parse(mParser, data, length, isFinal);
		}

		void XMLParseMaster::ParseFromFile(const std::string& filename)
		{
			mFileName = filename;

			FILE* fp;
			fopen_s(&fp, filename.c_str(), "r");
			
			if (fp)
			{
				fseek(fp, 0, SEEK_END);
				long fileSize = ftell(fp);
				rewind(fp);

				char* buffer = new char[fileSize + 1];
				fread(buffer, sizeof(char), fileSize, fp);

				for (IXMLParseHelper* helper : mHelperList)
				{
					helper->Initialize();
				}

				Parse(buffer, fileSize, XML_TRUE);
				fclose(fp);
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
			mpSharedData = data;
			if (mpSharedData)
			{
				mpSharedData->SetXMLParseMaster(this);
			}
		}

		void XMLParseMaster::StartElementHandler(void* data, const char* element, const char** attribute)
		{
			XMLParseMaster* parseMaster = static_cast<XMLParseMaster*>(data);

			if (parseMaster)
			{
				parseMaster->GetSharedData()->IncrementDepth();

				HashMap<std::string, std::string> attributeMap;

				for (std::uint32_t i = 0; attribute[i] != nullptr; i += 2)
				{
					attributeMap.Insert(std::pair<std::string, std::string>(attribute[i], attribute[i + 1]));
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
			XMLParseMaster* parseMaster = static_cast<XMLParseMaster*>(data);

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
			XMLParseMaster* parseMaster = static_cast<XMLParseMaster*>(data);

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