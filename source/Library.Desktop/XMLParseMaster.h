#pragma once
#include "SList.h"
#include <cstdint>
#include <string>

namespace GameEngine
{
	namespace Library
	{
		class IXMLParseHelper;

		class XMLParseMaster
		{
			class SharedData
			{
			public:
				SharedData() {};
				virtual SharedData* Clone() {};
				void SetXMLParseMaster(XMLParseMaster* parseMaster) { mpParseMaster = parseMaster; };
				XMLParseMaster* GetXMLParseMaster() const { return mpParseMaster; };
				void IncrementDepth() {};
				void DecrementDepth() {};
				std::uint32_t GetDepth() const {};

			private:
				XMLParseMaster* mpParseMaster;
			};

		public:
			XMLParseMaster(SharedData* data) { SetSharedData(data); };
			virtual ~XMLParseMaster() = default;
			virtual XMLParseMaster* Clone() {};
			void AddHelper(IXMLParseHelper* helper) { mHelperList.PushBack(helper); };
			void RemoveHelper(IXMLParseHelper* helper) { mHelperList.Remove(helper); };
			void Parse(const char* data, const std::uint32_t count, bool lastChunk) { data; count; lastChunk; };
			void ParseFromFile(std::string filename) { filename; };
			std::string GetFileName() {};
			SharedData* GetSharedData() const { return mpSharedData; };
			void SetSharedData(SharedData* data) { mpSharedData = data; mpSharedData->SetXMLParseMaster(this); };


		private:

			void StartElementHandler() {};
			void EndElementHandler() {};
			void CharDataHandler() {};
			SList<IXMLParseHelper*> mHelperList;
			SharedData* mpSharedData;
		};
	}
}