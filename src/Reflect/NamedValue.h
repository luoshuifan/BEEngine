#pragma once
#include "BE.h"
#include "RefStr.h"

BE_BEGIN

namespace BERef
{
	//template<typename Name,typename T>
	//struct NamedValue;

	template<typename Name, typename T>
		requires requires { Name::data(); }
	struct NamedValueBase
	{
		using TName = Name;
		static constexpr std::string_view name = TName::view();
		static constexpr bool has_value = !std::is_void_v<T>;

		template<typename Str>
		static constexpr bool NameIs(Str = {}) noexcept
		{
			return std::is_same_v<Str, Name>;
		}

		template<typename U>
		static constexpr bool ValueTypeIs()noexcept
		{
			return std::is_same_v<T, U>;
		}

		template<typename U>
		static constexpr bool ValueTypeIsSameWith(U)noexcept
		{
			return ValueTypeIs<U>();
		}

	};

	template<typename Name, typename T>
	struct NamedValue : NamedValueBase<Name,T>
	{
		T value;

		constexpr NamedValue(Name, T value) : value{ value } {}

		template<typename U>
		constexpr bool operator==(const U& v)const
		{
			if constexpr (std::is_same_v<T, U>)
				return v == value;
			else
				return false;
		}
	};

	template<typename Name>
	struct NamedValue<Name,void> : NamedValueBase<Name, void>
	{
		constexpr NamedValue(Name){}

		template<typename U>
		constexpr bool operator==(U)
		{
			return false;
		}
	};

	template<typename Name>
	NamedValue(Name) -> NamedValue<Name, void>;

	template<typename T, typename Name>
	NamedValue(Name, T) -> NamedValue<Name, T>;

	//template<typename C>
	//RefTStr(const C* ch) -> RefTStr<REFSTR(ch)>;
}

BE_END

