#ifndef ZL_THREADSAFE_LOOKUPTABLE
#define ZL_THREADSAFE_LOOKUPTABLE
#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include <list>
#include <utility>
#include <mutex>
#include <algorithm>

/// 线程安全的查找表
/// 进一步提高并发性
/// 类似于加锁的map，但锁的粒度更小，只会在Hash<kay>相等时互斥，否则可并发访问
template<typename Key, typename Value, typename Hash = std::hash<Key> >
class threadsafe_lookup_table
{
public:
    typedef Key key_type;
    typedef Value mapped_type;
    typedef Hash hash_type;

    threadsafe_lookup_table(size_t num_buckets = 19, Hash const& hasher_ = Hash())
        : buckets_(num_buckets)
        , hasher_(hasher_)
    {
        for (size_t i = 0; i < num_buckets; ++i)
        {
            buckets_[i].reset(new bucket_type);
        }
    }

    threadsafe_lookup_table(threadsafe_lookup_table const& other) = delete;
    threadsafe_lookup_table& operator=(threadsafe_lookup_table const& other) = delete;

    Value value_for(Key const& key, Value const& default_value = Value()) const
    {
        return get_bucket(key).value_for(key, default_value);
    }

    void add_or_update_mapping(Key const& key, Value const& value)
    {
        get_bucket(key).add_or_update_mapping(key, value);
    }

    void remove_mapping(Key const& key)
    {
        get_bucket(key).remove_mapping(key);
    }

private:
    class bucket_type
    {
    private:
        typedef std::pair<Key, Value> bucket_value;
        typedef std::list<bucket_value> bucket_data;
        typedef typename bucket_data::iterator bucket_iterator;

    public:
        Value value_for(Key const& key, Value const& default_value) const
        {
            std::lock_guard<std::mutex> lock(mutex_);
            bucket_iterator const found_entry = find_entry_for(key);
            return (found_entry == data_.end()) ? default_value : found_entry->second;
        }

        void add_or_update_mapping(Key const& key, Value const& value)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            bucket_iterator const found_entry = find_entry_for(key);
            if (found_entry == data_.end())
            {
                data_.push_back(bucket_value(key, value));
            }
            else
            {
                found_entry->second = value;
            }
        }

        void remove_mapping(Key const& key)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            bucket_iterator const found_entry = find_entry_for(key);
            if (found_entry != data_.end())
            {
                data_.erase(found_entry);
            }
        }
    private:
        bucket_iterator find_entry_for(Key const& key) 
        {
            return std::find_if(data_.begin(), data_.end(),
                [&](bucket_value const& item) { return item.first == key; });
        }
    private:
        bucket_data data_;
        mutable std::mutex mutex_;
    };

private:
    bucket_type& get_bucket(Key const& key) const
    {
        std::size_t const bucket_index = hasher_(key) % buckets_.size();
        return *buckets_[bucket_index];
    }

private:
    std::vector<std::unique_ptr<bucket_type> > buckets_;
    Hash hasher_;
};

#endif  /* ZL_THREADSAFE_LOOKUPTABLE */
