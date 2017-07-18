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
      if (!owner_) 
        return nullptr;
      return &(owner_->data_[*this]);
    }
    void  remove()
    {
      owner_->remove(*this);
      owner_ = nullptr;
    }

  private:
    friend class resource;

    resource*   owner_;
    std::size_t id_   ;
  };

  typedef type value_type;

  explicit resource(std::size_t initial_capacity = 1024)
  {
    data_.reserve(initial_capacity);
  }
  resource(const resource&  that)            = default;
  resource(      resource&& temp)            = default;
 ~resource()                                 = default;
  resource& operator=(const resource&  that) = default;
  resource& operator=(      resource&& temp) = default;
  
  template<typename... argument_types>
  handle add   (argument_types&&... arguments)
  {
    handle key(this, next_id_++);
    data_[key] = type(arguments...);
    return key;
  }
  void   remove(const handle&       key      )
  {
    assert(key.owner_ == this);
    data_.erase(std::remove_if(data_.begin(), data_.end(), [&key] (const std::pair<handle, type>& iteratee)
    {
      return key.id_ == iteratee.first.id_;
    }));
  }

  typename boost::container::flat_map<handle, type>::iterator       begin()       { return data_.begin(); }
  typename boost::container::flat_map<handle, type>::const_iterator begin() const { return data_.begin(); }
  typename boost::container::flat_map<handle, type>::iterator       end  ()       { return data_.end  (); }
  typename boost::container::flat_map<handle, type>::const_iterator end  () const { return data_.end  (); }

private:
  boost::container::flat_map<handle, type> data_    ;
  std::size_t                              next_id_ = 0;
};
}

#endif
