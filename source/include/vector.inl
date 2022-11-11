#include "vector.h"

/// Iterator accessor methods.

namespace sc {
    /// Returns a regular iterator to the begining of the list.
    template < typename T >
    typename vector<T>::iterator  vector<T>::begin( void )
    {
        return iterator{ &m_storage[ 0 ] };
    }
}
