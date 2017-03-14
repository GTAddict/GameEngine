#include "pch.h"
#include "XMLParseMaster.h"
#include <expat.h>

namespace GameEngine
{
	namespace Library
	{
		XMLParseMaster::SharedData::SharedData()
			: mpParseMaster(nullptr)
			, mDepth(0)
		{

		}

		XMLParseMaster::SharedData* XMLParseMaster::SharedData::Clone() const
		{
			return new SharedData(*this);
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
		{
			SetSharedData(data);

			mParser = XML_ParserCreate(NULL);
			XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
			XML_SetCharacterDataHandler(mParser, CharDataHandler);
		}

		XMLParseMaster::~XMLParseMaster()
		{
			XML_ParserFree(mParser);
		}

		XMLParseMaster* XMLParseMaster::Clone()
		{
			return new XMLParseMaster(*this);
		}

		void XMLParseMaster::AddHelper(IXMLParseHelper* helper)
		{
			mHelperList.PushBack(helper);
		}

		void XMLParseMaster::RemoveHelper(IXMLParseHelper* helper)
		{
			mHelperList.Remove(helper);
		}

		void XMLParseMaster::Parse(const char* data, const std::uint32_t length, bool isFinal)
		{
			XML_Parse(mParser, data, length, isFinal);
		}

		void XMLParseMaster::ParseFromFile(std::string filename)
		{
			mFileName = filename;

			FILE* fp;
			fp = fopen(filename.c_str(), "r");
			
			if (fp)
			{
				fseek(fp, 0, SEEK_END);
				long fileSize = ftell(fp);
				rewind(fp);

				char* buffer = new char[fileSize + 1];
				fread(buffer, sizeof(char), fileSize, fp);
				Parse(buffer, fileSize, XML_TRUE);

				fclose(fp);
			}
		}

		std::string XMLParseMaster::GetFileName()
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
			
		}

		void XMLParseMaster::EndElementHandler(void* data, const char* element)
		{
		}

		void XMLParseMaster::CharDataHandler(void* data, const char* content, int length)
		{
		}


	}
}