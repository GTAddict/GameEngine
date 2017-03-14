#pragma once
#include "SList.h"
#include <cstdint>
#include <string>
#include <expat.h>

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
				SharedData();
				virtual SharedData* Clone() const;
				void SetXMLParseMaster(XMLParseMaster* parseMaster);
				XMLParseMaster* GetXMLParseMaster() const;
				void IncrementDepth();
				void DecrementDepth();
				std::uint32_t GetDepth() const;

			private:
				XMLParseMaster* mpParseMaster;
				std::uint32_t mDepth;
			};

		public:
			XMLParseMaster(SharedData* data);
			virtual ~XMLParseMaster();
			virtual XMLParseMaster* Clone();
			void AddHelper(IXMLParseHelper* helper);
			void RemoveHelper(IXMLParseHelper* helper);
			void Parse(const char* data, const std::uint32_t length, bool isFinal);
			void ParseFromFile(std::string filename);
			std::string GetFileName();
			SharedData* GetSharedData() const;
			void SetSharedData(SharedData* data);


		private:
			static void StartElementHandler(void* data, const char* element, const char** attribute);
			static void EndElementHandler(void* data, const char* element);
			static void CharDataHandler(void* data, const char* content, int length);

			SList<IXMLParseHelper*> mHelperList;
			SharedData* mpSharedData;
			std::string mFileName;
			XML_Parser mParser;
		};
	}
}