#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <exception>    // std::out_of_range
#include <iostream>     // std::cout, std::endl
#include <memory>       // std::unique_ptr
#include <iterator>     // std::advance, std::begin(), std::end(), std::ostream_iterator
#include <algorithm>    // std::copy, std::equal, std::fill
#include <initializer_list> // std::initializer_list
#include <cassert>      // assert()
#include <limits>       // std::numeric_limits<T>
#include <cstddef>      // std::size_t

/// Sequence container namespace.
namespace sc {
  
/// Implements tha infrastrcture to support a bidirectional iterator.
template <class T>
class MyForwardIterator {
 public:
  typedef MyForwardIterator iterator;  //!< Alias to iterator.
  // Below we have the iterator_traits common interface
  typedef std::ptrdiff_t difference_type;  //!< Difference type used to calculated distance between
                        //!< iterators.
  typedef T value_type;              //!< Value type the iterator points to.
  typedef T* pointer;                //!< Pointer to the value type.
  typedef T& reference;              //!< Reference to the value type.
  typedef const T& const_reference;  //!< Reference to the value type.
  typedef std::bidirectional_iterator_tag
      iterator_category;  //!< Iterator category.

  /*! Create an iterator around a raw pointer.
   * \param pt_ raw pointer to the container.
   */
  MyForwardIterator(pointer pt = nullptr) : m_ptr(pt) { /* empty */ }

  /// Access the content the iterator points to.
  reference operator*(void) const {
    assert(m_ptr != nullptr);
    return *m_ptr;
  }

  /// Overloaded `->` operator.
  pointer operator->(void) const {
    assert(m_ptr != nullptr);
    return m_ptr;
  }

  /// Assignment operator.
  iterator& operator=(const iterator& it){
    m_ptr = it.m_ptr;
    return *this;
  }

  /// Copy constructor.
  MyForwardIterator(const iterator&) = default;

  /// Pre-increment operator.
  iterator operator++(void) {
    m_ptr++;
    return *this;
  }

  /// Post-increment operator.
  iterator operator++(int) {
    iterator dummy = *this;
    m_ptr++;
    return dummy;
  }

  /// Pre-decrement operator.
  iterator operator--(void) {
    m_ptr--;
    return *this;
  }

  /// Post-decrement operator.
  iterator operator--(int) {
    iterator dummy = *this;
    m_ptr--;
    return dummy;
  }

  iterator& operator+=(difference_type offset) {
    iterator& it{*this};
    m_ptr += offset;
    return it;
  }
  iterator& operator-=(difference_type offset) {
    iterator& it{*this};
    m_ptr -= offset;
    return it;
  }

  friend bool operator<(const iterator& ita, const iterator& itb) { return ita.m_ptr < itb.m_ptr; }
  
  friend bool operator>(const iterator& ita, const iterator& itb) { return ita.m_ptr > itb.m_ptr; }
	
  friend bool operator>=(const iterator& ita, const iterator& itb) { return ita.m_ptr >= itb.m_ptr; }
	
  friend bool operator<=(const iterator& ita, const iterator& itb) { return ita.m_ptr <= itb.m_ptr; }

  friend iterator operator+(difference_type offset, iterator it) {
    iterator dummy = it += offset;
    return dummy;
  }
  friend iterator operator+(iterator it, difference_type offset) {
    iterator dummy = it += offset;
    return dummy;
  }
  friend iterator operator-(iterator it, difference_type offset) {
    iterator dummy = it -= offset;
    return dummy;
  }

  /// Equality operator.
  bool operator==(const iterator& rhs_) const { return *m_ptr == *rhs_.m_ptr; }

  /// Not equality operator.
  bool operator!=(const iterator& rhs_) const { return *m_ptr != *rhs_.m_ptr; }

  /// Returns the difference between two iterators.
  difference_type operator-(const iterator& rhs_) const { return m_ptr - rhs_.m_ptr; }

  /// Stream extractor operator.
  friend std::ostream& operator<<(std::ostream& os_, const MyForwardIterator& p_){
    os_ << "[@ " << p_.m_ptr << ": " << *p_.m_ptr << " ]";
    return os_;
  }

 private:
  pointer m_ptr; //!< The raw pointer.
};

/// This class implements the ADT list with dynamic array.
/*!
 * sc::vector is a sequence container that encapsulates dynamic size arrays.
 *
 * The elements are stored contiguously, which means that elements can
 * be accessed not only through iterators, but also using offsets to
 * regular pointers to elements.
 * This means that a pointer to an element of a vector may be passed to
 * any function that expects a pointer to an element of an array.
 *
 * \tparam T The type of the elements.
 */
template <typename T>
class vector {
  //=== Aliases
 public:
  using size_type = unsigned long;  //!< The size type.
  using value_type = T;             //!< The value type.
  using pointer = value_type*;  //!< Pointer to a value stored in the container.
  using reference = value_type&;  //!< Reference to a value stored in the container.
  using const_reference = const value_type&; //!< Const reference to a value stored in the container.
  using iterator = MyForwardIterator<value_type>; //!< The iterator, instantiated from a template class.
  using const_iterator = MyForwardIterator<const value_type>; //!< The const_iterator, instantiated from a template class.
  
  public:
    //Default constructor
    explicit vector(size_type cp = 0) {
      m_storage = new T[cp];
      m_capacity = cp;
      m_end = cp;
    }

   //Destructor
   virtual ~vector(void) {
     if (m_storage) delete[] m_storage;
   }
   //Copy constructor
   vector(const vector& vec){
     m_storage = new T[vec.m_capacity];
     m_capacity = vec.m_capacity;
     m_end = vec.m_end;

     for (int i = 0; i < vec.m_end; i++){ 
       m_storage[i] = vec.m_storage[i];
     }
   }

   //Initializer list constructor 
   vector(const std::initializer_list<T> &il){
     m_capacity = il.size();
     m_storage = new T[m_capacity];
     m_end = m_capacity;
     // Copy the elements from the il into the array.
     std::copy(il.begin(), il.end(), m_storage);
   }

   //Range constructor
   template <typename InputItr>
   vector(InputItr first, InputItr last){
     auto dif = last - first;
     m_capacity = dif;
     m_storage = new T[m_capacity];
     m_end = m_capacity;

    size_type i = 0;
    for (auto it = first; it < last; it++, i++){
      m_storage[i] = *it;
    }
  }

  //Assignment operator
  vector& operator=(const vector& vec){
    if (this == &vec){
      return *this;
    }
    if (vec.m_end <= m_capacity){
      for (int ii = 0; ii < vec.m_end; ii++){
        m_storage[ii] = vec.m_storage[ii];
      }
      m_end = vec.m_end;
      return *this;
    }

    T* m_storage_maior = new T[vec.m_end];

    for(int i = 0; i < vec.m_end; i++){
      m_storage_maior[i] = vec.m_storage[i];
    }
	  
    delete[] m_storage;

    m_end = vec.m_end;
    m_capacity = vec.m_end;
    m_storage = m_storage_maior;

    return *this;
  }

  //=== [II] ITERATORS
    
  //Returns the first position of the vector
  iterator begin(void){ return iterator(&m_storage[0]); }
  
  //Returns the last position of the vector
  iterator end(void){ return iterator(&m_storage[m_end]); }
  
  //Returns a constant reference of the first position of the vector
  const_iterator cbegin( void ) const { return const_iterator(&m_storage[0]); }
  
  //Returns a constant reference of the last position of the vector
  const_iterator cend( void ) const { return const_iterator(&m_storage[m_end]); }

  // [III] Capacity
  size_type size(void) const { return m_end; }
  size_type capacity(void) const { return m_capacity; }
  bool empty(void) const { return m_end == 0; }

  // [IV] Modifiers
  void clear(void){
    for(size_type i{0}; i < m_end; i++)
      m_storage[i].~T();
    m_end = 0;
  }

  void push_front(const_reference st){
    if(m_capacity == 0){
      reserve(10);
    }
    else if(full()){
      reserve(2 * m_capacity);
    }
    for(auto i{m_end}; i>0; i--){
      m_storage[i] = m_storage[i-1];
    }
  
    m_storage[0] = st;
    m_end++;
  }

  void push_back(const_reference st){
    if(m_capacity == 0){
      reserve(10);
    }else if(m_end == m_capacity){
      reserve(2 * m_capacity);
    }

    m_storage[m_end] = st;
    m_end++;
  }
  void pop_back(void){
    if(m_end > 0) m_storage[--m_end].~T();
  }

  void pop_front(void){
    if(m_end > 0){
      for(auto i{0u}; i<m_end; i++){
        m_storage[i] = m_storage[i+1];
      }
      m_end--;
    }
  }

  //Iterator insert
  iterator insert(iterator pos_, const_reference value_){
    if(pos_ < begin() || pos_ > end() )  throw std::out_of_range{ "The method 'insert' cannot access this position" };

    auto dif = pos_ - begin();
    
    if(full()){
      reserve(m_capacity * 2);
    }
    m_end++;

    pos_ = begin()+dif;

    for(iterator it = end()-1; it > pos_; it--){
      *it= *(it-1);
    }

    *pos_ = value_;

    return pos_;
  }
	
  //Constant iterator insert
  iterator insert(const_iterator pos_, const_reference value_){
    if(pos_ < begin() || pos_ > end() )  throw std::out_of_range{ "The method 'insert' cannot access this position" };

    auto distancia = pos_ - begin();

    if(full()){
      reserve(m_capacity * 2);
    }
    m_end++;

    pos_ = begin()+distancia;

    for(iterator it = end()-1; it > pos_; it--){
      *it= *(it-1);
    }

    *pos_ = value_;

    return pos_;
  }

  template <typename InputItr>
  iterator insert(iterator pos_, InputItr first_, InputItr last_){
    if(pos_ < begin() || pos_ > end() ) throw std::out_of_range{ "The method 'insert' cannot access this range of positions" };
    
    auto dif = last_ - first_;
    auto distancia = pos_ - begin();

    if(full() || (m_end+dif) > m_capacity) reserve(m_capacity + dif);
    
    m_end+=dif;
    pos_ = begin()+distancia;
    size_type i{m_end-1};

    for(auto it{end()-1}; it>pos_; it--, i--){
      m_storage[i] = *(it-dif);
    }

    for(auto i{0u}; i<dif; i++){
      *(pos_+i) = *(first_+i);
    } 
    return pos_;
  }
 
  template <typename InputItr>
  iterator insert(const_iterator pos_, InputItr first_, InputItr last_){
    if(pos_ < begin() || pos_ > end() )  throw std::out_of_range{ "The method 'insert' cannot access this range of positions" };
    
    auto dif = last_ - first_;
    auto distancia = pos_ - begin();

    if(full() || (m_end+dif) > m_capacity){ 
      reserve(m_capacity + dif);
    }

    m_end+=dif;                                 
    pos_ = begin()+distancia;
    size_type i{m_end-1};
       
    for(auto it{end()-1}; it>pos_; it--, i--){    
      m_storage[i] = *(it-dif);                   
    }

    for(auto i{0u}; i<dif; i++){
      *(pos_+i) = *(first_+i);    
    } 
    return pos_;
  }
 
  iterator insert(iterator pos_, const std::initializer_list<value_type>& ilist_){
    auto distancia = pos_ - begin();
    auto n_elem = ilist_.end() - ilist_.begin();
    if(pos_ < begin() || pos_ > end() )  throw std::out_of_range{ "vector::insert" };

    if(full()){
      reserve(m_capacity + n_elem);
    }
    m_end += n_elem;

    pos_ = begin()+distancia;
    
    for(iterator it = end()-1; it >= pos_; it--){
      *it= *(it-n_elem);
    }

    auto i = 0;
    for(iterator iter = pos_; iter < (pos_+n_elem); iter++, i++){
      *iter= *(ilist_.begin()+i);
      
    }
    
    return pos_;
  }
	
  iterator insert(const_iterator pos_, const std::initializer_list<value_type>& ilist_){
    auto distancia = pos_ - begin();
    auto n_elem = ilist_.end() - ilist_.begin();
    if(pos_ < begin() || pos_ > end() )  throw std::out_of_range{ "vector::insert" };

    if(full()){
      reserve(m_capacity + n_elem);
    }
    m_end += n_elem;

    pos_ = begin()+distancia;
    
    for(iterator it = end()-1; it >= pos_; it--){
      *it= *(it-n_elem);
    }

    auto i = 0;
    for(iterator iter = pos_; iter < (pos_+n_elem); iter++, i++){
      *iter= *(ilist_.begin()+i);
    }
    
    return pos_;
  }

  void reserve(size_type alocar){
    if(alocar <= m_capacity)
      return;

    T* newstorage = new T[alocar];

    for (int i = 0; i < m_end; i++){
      newstorage[i] = m_storage[i];
    }

    delete[] m_storage;

    m_capacity = alocar;
    m_storage = newstorage;

  }
	
  //Requests the removal of unused capacity.
  void shrink_to_fit(void){
    if(m_capacity > m_end){
      T* newstorage = new T[m_end];

      for(int i = 0; i < m_end; i++){
        newstorage[i] = m_storage[i];
      }

      delete[] m_storage;

      m_capacity = m_end;
      m_storage = newstorage;
    }
  }

  void assign(size_type count_, const_reference value_){
    if(count_ <= size()){
      m_end = count_;
      
      for(auto i{0u}; i<count_; i++){
        m_storage[i] = value_;
      }
    }
    else{
      T* newStorage = new T[count_];
      m_capacity = count_;
      m_end = count_;

      delete [] m_storage;

      m_storage = newStorage;

      for(auto i{0u}; i<count_; i++){
        m_storage[i] = value_;
      }
    }
  }

  void assign(const std::initializer_list<T>& ilist){
    if(ilist.size() <= size()){
      m_end = ilist.size();
      std::copy(ilist.begin(), ilist.end(), m_storage);
    }
    else{
      T* newStorage = new T[ilist.size()];
      m_capacity = ilist.size();
      m_end = ilist.size();

      delete [] m_storage;

      m_storage = newStorage;

      std::copy(ilist.begin(), ilist.end(), m_storage);
    }
  }

  template <typename InputItr>
  void assign(InputItr first, InputItr last){
    size_type dif = last - first;

    if(dif <= size()){
      m_end = dif;
      
      size_type i = 0;
      for (auto it = first; it < last; it++, i++){
        m_storage[i] = *it;
      }
    }
    else{
      T* newStorage = new T[dif];
      m_capacity = dif;
      m_end = dif;

      delete [] m_storage;

      m_storage = newStorage;

      size_type i = 0;
      for (auto it = first; it < last; it++, i++){
        m_storage[i] = *it;
      }
    }
  }

  iterator erase(iterator first, iterator last){
    auto dif = last - first;

    if((first > last) || (first < begin() || last > end()))  throw std::out_of_range{ "The method 'erase' cannot access this range of positions" };

    for (iterator it = first; it < end()-dif; it++){
      *it = *(it+dif);
    }

    m_end -= dif;
    return first;
  }

  iterator erase(const_iterator first, const_iterator last){
    auto dif = last - first;

    if((first > last) || (first < begin() || last > end()))  throw std::out_of_range{ "The method 'erase' cannot access this range of positions" };


    for (iterator it = first; it < end()-dif; it++){
      *it = *(it+dif);
    }

    m_end -= dif;
    return first;
  }

  iterator erase(const_iterator pos){
    if (pos >= begin() && pos < end()){
      for (iterator it = pos; it < end()-1; ++it){
        *it = *(it+1);
      }
      m_end--; 
	    
      return pos;
    }
    else throw std::out_of_range{ "The method 'erase' cannot access this position" }; 
  }

  iterator erase(iterator pos){
    if (pos >= begin() && pos < end()){
      for (iterator it = pos; it < end()-1; ++it){
        *it = *(it+1);
      }
      m_end--; 
      return pos;
   }
   else throw std::out_of_range{ "The method 'erase' cannot access this position" }; 
  }

  // [V] Element access
  const_reference back(void) const { 
    if(m_end > 0)
      return m_storage[m_end - 1];
    else throw std::out_of_range { "The method 'back' cannot access the index of last position" };
  }

  const_reference front(void) const {
    if(m_end > 0)
      return m_storage[0];
    else throw std::out_of_range { "The method 'front' cannot access the index of first position" };
  }

  reference back(void){
    if(m_end > 0)
      return m_storage[m_end - 1];
    else throw std::out_of_range { "The method 'back' cannot access the index of last position" };
  }

  reference front(void){
    if(m_end > 0)
      return m_storage[0];
    else throw std::out_of_range { "The method 'front' cannot access the index of first position" };
  }

  const_reference operator[](size_type idx) const{ return m_storage[idx];}
  reference operator[](size_type idx){ return m_storage[idx];}

  const_reference at(size_type idx) const{
    if (idx < size() && idx >= 0)
      return m_storage[idx]; 
    else throw std::out_of_range { "The method 'at' cannot access this index" };
  }

  reference at(size_type idx){
    if (idx < size() && idx >= 0)
        return m_storage[idx]; 
    else throw std::out_of_range { "The method 'at' cannot access this index" };
  }
	
  pointer data(void){ return m_storage; }

  const_reference data(void) const{return m_storage;}

  // [VII] Friend functions.
  friend std::ostream& operator<<(std::ostream& os_, const vector<T>& v_) {
    os_ << "{ ";
    for (auto i{0u}; i < v_.m_capacity; ++i) {
      if (i == v_.m_end) os_ << "| ";
      os_ << v_.m_storage[i] << " ";
    }
    os_ << "}, m_end=" << v_.m_end << ", m_capacity=" << v_.m_capacity;

    return os_;
  }
  friend void swap(vector<T>& first_, vector<T>& second_) {
    // enable ADL
    using std::swap;

    // Swap each member of the class.
    swap(first_.m_end, second_.m_end);
    swap(first_.m_capacity, second_.m_capacity);
    swap(first_.m_storage, second_.m_storage);
  }

 private:
  bool full(void) const{ return m_capacity == m_end; }
  
  size_type m_end;        //!< The list's current size (or index past-last valid element).
  size_type m_capacity;   //!< The list's storage capacity.
  T* m_storage;           //!< The list's data storage area.
};

// [VI] Operators
template <typename T>
bool operator==(const vector<T>& a, const vector<T>& b){
  if (a.size() == b.size()) {
        for (auto i = 0; i < b.size(); i++)
        {
          if (a.at(i) != b.at(i)) 
            return false;
        }         
        return true;
    } else return false;
}
template <typename T>
bool operator!=(const vector<T>& a, const vector<T>& b){
  return a == b ? false : true;
}

} // namespace sc.

#endif
