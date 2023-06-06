#pragma once
#include "BE.h"

#define REFTSTR(str)(\
	[]{\
		constexpr std::basic_string_view v(str);\
        return  BE::BERef::RefTStr<BE::BERef::RefStr<typename decltype(v)::value_type, v.size()>{str}>{};\
	}())

BE_BEGIN

namespace BERef
{

	template <typename C, std::size_t N>
	struct RefStr
	{
		using value_type = C;
		value_type data[N + 1];

		static constexpr std::size_t size = N;
	};

	template<RefStr str>
	struct RefTStr
	{
		using Char = typename decltype(str)::value_type;

		static constexpr auto data()
		{
			return str.data;
		}

		static constexpr auto size()
		{
			return str.size;
		}

		static constexpr std::basic_string_view<Char> view()
		{
			return str.data;
		}
	};

}
BE_END