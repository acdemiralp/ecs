#ifndef ECS_RESOURCE_HPP_
#define ECS_RESOURCE_HPP_

#include <algorithm>

#include <boost/container/flat_map.hpp>

namespace ecs
{
template<typename type>
class resource final
{
public:
  class handle final
  {
  public:
    explicit handle(resource* owner, std::size_t id) : owner_(owner), id_(id)
    {
      
    }
    handle(const handle&  that)            = default;
    handle(      handle&& temp)            = default;
   ~handle()                               = default;
    handle& operator=(const handle&  that) = default;
    handle& operator=(      handle&& temp) = default;
    bool    operator<(const handle&  that) const
    {
      return id_ < that.id_;
    }

    type* get   ()
    {
      return owner_ ? owner_->get(*this) : nullptr;
    }
    bool  valid ()
    {
      return owner_ && owner_->valid(*this);
    }
    void  remove()
    {
      if (!valid()) return;
      owner_->remove(*this);
      owner_ = nullptr;
    }

  private:
    friend class resource;

    resource*   owner_;
    std::size_t id_   ;
  };

  typedef boost::container::flat_map<handle, type> container_type;
  typedef typename container_type::mapped_type     value_type    ;
  typedef typename container_type::iterator        iterator      ;
  typedef typename container_type::const_iterator  const_iterator;

  explicit resource(std::size_t initial_capacity = 1024)
  {
    data_.reserve(initial_capacity);
  }
  resource           (const resource&  that) = default;
  resource           (      resource&& temp) = default;
 ~resource           ()                      = default;
  resource& operator=(const resource&  that) = default;
  resource& operator=(      resource&& temp) = default;
  
  template<typename... argument_types>
  handle add   (argument_types&&... arguments)
  {
    handle key(this, next_id_++);
    data_[key] = type(arguments...);
    return key;
  }
  type*  get   (const handle&       key      )
  {
    assert(key.owner_ == this);
    return valid(key) ? &(data_[key]) : nullptr;
  }
  bool   valid (const handle&       key      )
  {
    assert(key.owner_ == this);
    return std::find_if(data_.begin(), data_.end(), 
    [&key] (const std::pair<handle, type>& iteratee)
    {
      return key.id_ == iteratee.first.id_;
    }) != data_.end();
  }
  void   remove(const handle&       key      )
  {
    assert(key.owner_ == this);
    data_.erase(std::remove_if(data_.begin(), data_.end(), 
    [&key] (const std::pair<handle, type>& iteratee)
    {
      return key.id_ == iteratee.first.id_;
    }));
  }

  iterator       begin()
  {
    return data_.begin();
  }
  const_iterator begin() const
  {
    return data_.begin();
  }
  iterator       end  ()
  {
    return data_.end  ();
  }
  const_iterator end  () const
  {
    return data_.end  ();
  }

private:
  container_type data_    ;
  std::size_t    next_id_ = 0;
};
}

#endif
