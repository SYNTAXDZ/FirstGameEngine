#pragma once

#include <memory>
#include <iostream>

#include <vector>
#include <string>

/*
 We Will Define Some Macros in This File To Make our Life Easizer
*/

// one shifted by x places in the left side
#define BIT( x ) ( 1 << x )

#define BIND_FN( x ) std::bind( &x, this, std::placeholders::_1 )

#ifdef FGE_ENABLE_ASSERTS
    #define FGE_CORE_ASSERT( x, ... ) { if( !( x ) ) { FGE_CORE_ERROR( "Assertion Failed: {0}", __VA_ARGS__ ); } }
    #define FGE_ASSERT( x, ... ) { if( !( x ) ) { FGE_ERROR( "Assertion Failed: {0}", __VA_ARGS__ ); } }
#else 
    #define FGE_CORE_ASSERT( x, ... )
    #define FGE_ASSERT( x, ... )
#endif

namespace FGE {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	
    template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope( Args&& ... args ) {
		
        return std::make_unique<T>( std::forward<Args>( args )... );
	
    }

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
    template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef( Args&& ... args ) {
		
        return std::make_shared<T>( std::forward<Args>( args )... );
	
    }

}