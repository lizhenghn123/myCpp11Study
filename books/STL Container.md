#STL 容器#
* [顺序容器](sequence_containers)
  * [vector](vector)
  * [list](list)
  * [deque](deque)
  * [array](array)
  * [forward_list](forward_list)
* [容器适配器](container_adaptors)
  * [stack](stack)
  * [queue](queue)
  * [priority_queue](priority_queue)
* [关联容器](associative_containers)
  * [set](set)
  * [multiset](multiset)
  * [map](map)
  * [multimap](multimap)
* [无序关联容器](unordered_associative_containers)
  * [unordered_set](unordered_set)
  * [unordered_multiset](unordered_multiset)
  * [unordered_map](unordered_map)
  * [unordered_multimap](unordered_multimap)

## 顺序容器

### vector
类模板声明：

    template < class T, class Alloc = allocator<T> > class vector;
vector是一个封装了动态大小数组的顺序容器（sequence container）。跟任意其它类型容器一样，它能够存放各种类型的对象。可以简单的认为，向量是一个能够存放任意类型的动态数组。

容性特性：

	顺序序列
		顺序容器中的元素按照严格的线性顺序排序。可以通过元素在序列中的位置访问对应的元素。	
	动态数组	
	   支持对序列中的任意元素进行快速直接访问，甚至可以通过指针算述进行该操作。操供了在序列末尾相对快速地添加/删除元素的操作。	
	能够感知内存分配器的（Allocator-aware）	
	   容器使用一个内存分配器对象来动态地处理它的存储需求。

### list

### deque

### array

### forward_list

## 容器适配器

### stack

### queue

### priority_queue

## 关联容器

### set

### multiset

### map

### multimap

## 无序关联容器

### unordered_set

### unordered_multiset

### unordered_map

### unordered_multimap