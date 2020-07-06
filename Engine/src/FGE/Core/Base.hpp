#pragma once

#include <memory>
#include <iostream>

/*
 We Will Define Some Macros in This File To Make our Life Easizer
*/

// one shifted by x places in the left side
#define BIT( x ) ( 1 << x )

#ifdef FGE_ENABLE_ASSERTS
    #define FGE_CORE_ASSERT( x, ... ) { if( !( x ) ) { FGE_CORE_ERROR( "Assertion Failed: {0}", __VA_ARGS__ ); } }
    #define FGE_ASSERT( x, ... ) { if( !( x ) ) { FGE_ERROR( "Assertion Failed: {0}", __VA_ARGS__ ); } }
#else 
    #define FGE_CORE_ASSERT( x, ... )
    #define FGE_ASSERT( x, ... )
#endif