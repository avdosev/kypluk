#pragma once

#include <kyplukSmartPtr.h>

template <typename resType, typename ... argsType>
class function <resType (argsType ...)> {
	public:
		function(functionT f) : func(new free_function_holder<FunctionT>(f)) {}
		
		resType operator () (argsType ... args) {
			return func->invoke(args);
		}
	private:
		class function_holder_base {
			public:
				function_holder_base() {}
				virtual ~function_holder_base() {}
				virtual resType invoke(argsType ... args) = 0;
		};
		
		using invoker_t = UniquePtr<function_holder_base>;
	
		template <typename FunctionT>
		class free_function_holder : public function_holder_base {
			public:
				free_function_holder(FunctionT func) : function_holder_base(), mFunction(func) {}
		
				virtual resType invoke(argsType ... args) {
					return mFunction(args ...);
				}
			private:
				FunctionT mFunction;
		};
		
		invoker_t func;
};
