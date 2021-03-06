#ifndef GRID_ALIGNED_ALLOCATOR_H
#define GRID_ALIGNED_ALLOCATOR_H

#include <immintrin.h>
#ifdef HAVE_MM_MALLOC_H
#include <mm_malloc.h>
#endif

namespace Grid {

////////////////////////////////////////////////////////////////////
// A lattice of something, but assume the something is SIMDized.
////////////////////////////////////////////////////////////////////
template<typename _Tp>
class alignedAllocator {
public: 
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef _Tp        value_type;

  template<typename _Tp1>  struct rebind { typedef alignedAllocator<_Tp1> other; };

  alignedAllocator() throw() { }

  alignedAllocator(const alignedAllocator&) throw() { }

  template<typename _Tp1> alignedAllocator(const alignedAllocator<_Tp1>&) throw() { }

  ~alignedAllocator() throw() { }

  pointer       address(reference __x)       const { return &__x; }
  const_pointer address(const_reference __x) const { return &__x; }

  size_type  max_size() const throw() { return size_t(-1) / sizeof(_Tp); }

  pointer allocate(size_type __n, const void* = 0)
  { 
#ifdef HAVE_MM_MALLOC_H
    _Tp * ptr = (_Tp *) _mm_malloc(__n*sizeof(_Tp),128);
#else
    _Tp * ptr = (_Tp *) memalign(128,__n*sizeof(_Tp));
#endif
    return ptr;
  }

  void deallocate(pointer __p, size_type) { 
#ifdef HAVE_MM_MALLOC_H
    _mm_free(__p); 
#else
    free(__p);
#endif
  }
  void construct(pointer __p, const _Tp& __val) { };
  void construct(pointer __p) { };

  void destroy(pointer __p) { };
};

template<typename _Tp>  inline bool
operator==(const alignedAllocator<_Tp>&, const alignedAllocator<_Tp>&){ return true; }

template<typename _Tp>  inline bool
operator!=(const alignedAllocator<_Tp>&, const alignedAllocator<_Tp>&){ return false; }

    
}; // namespace Grid
#endif
