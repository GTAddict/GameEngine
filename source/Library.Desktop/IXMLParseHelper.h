#pragma once

namespace GameEngine
{
	namespace Library
	{
		class IXMLParseHelper
		{
		public:
			void Initialize() {};
			bool StartElementHandler() {};
			bool EndElementHandler() {} ;
			void CharDataHandler() {};
			virtual IXMLParseHelper* Clone() = 0;
			virtual ~IXMLParseHelper() = default;
		};
	}
}