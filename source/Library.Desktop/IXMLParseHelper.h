#pragma once

namespace GameEngine
{
	namespace Library
	{
		class IXMLParseHelper
		{
			void Initialize() {};
			bool StartElementHandler() {};
			bool EndElementHandler() {} ;
			void CharDataHandler() {};
			virtual void Clone() = 0;
			virtual ~IXMLParseHelper() = default;
		};
	}
}