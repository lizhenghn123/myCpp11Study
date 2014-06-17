#STL 容器#
* [顺序容器](#sequence_containers)
  * [vector](#vector)
  * [list](#list)
  * [deque](#deque)
  * [array](#array)
  * [forward_list](#forward_list)
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

#### 容性特性

	顺序序列
		顺序容器中的元素按照严格的线性顺序排序。可以通过元素在序列中的位置访问对应的元素。	
	动态数组	
	   支持对序列中的任意元素进行快速直接访问，甚至可以通过指针算述进行该操作。操供了在序列末尾相对快速地添加/删除元素的操作。	
	能够感知内存分配器的（Allocator-aware）	
	   容器使用一个内存分配器对象来动态地处理它的存储需求。

#### 模板参数

<p><em>T</em></p>

<p style="margin-left: 40px; ">存储在容器中的元素的数据类型。</p>

<p style="margin-left: 40px; ">必须保证在执行移动操作时不会抛出异常，因为在重分配时，实现者（标准库内部）可以进行优化使仅仅移动元素而不是拷贝所有。</p>

<p style="margin-left: 40px; ">在类模板内部，使用其别名为&nbsp;<code>value_type</code>&nbsp;的成员类型。</p>

<p><em>Alloc</em></p>

<p style="margin-left: 40px; ">容器内部用来管理内存分配及释放的内存分配器的类型。</p>

<p style="margin-left: 40px; ">这个参数是可选的，它的默认值是 <code>std::allocator&lt;T&gt;</code>，这个是一个最简单的非值依赖的（Value-independent）内存分配器。在类模板内部，使用其别名为&nbsp;<code>allocator_type</code> 的成员类型。</p>
</div>

#### 详细说明
<p>在向量中，所有元素都是连续存储的。也就是说，不仅可以通过迭代器（Iterators）访问各个元素，也可以通过指向元素的指针加上偏移来访问。还意味着，当向任意函数传递向量的一个元素的指针时，这个指针可以直接被认为指向了一个数组中的某个元素。</p>

<blockquote>
<p>The elements of a&nbsp;vector are stored contiguously, meaning that if v is a vector&lt;T, Allocator&gt; where T is some type&nbsp;other than bool, then it obeys the identity &amp;v[n] == &amp;v[0] + n for all 0 &lt;= n &lt; v.size().</p>

<p><small>C++编程语言国际标准：<a href="/cpp-sd/">ISO/IEC 14882:2011</a></small></p>
</blockquote>

<p>向量内部的存储调整是自动处理的，按需扩展或压缩。通常，相比静态数组（Static arrays），向量将会占用更多的存储空间，因为额外的内存将被未来增长的部分所使用。就因为这点，当插入元素时，向量不需要太频繁地重分配（Reallocate）内存。当前最大容量可以通过函数&nbsp;<code><a href="/cpp/library/containers/vector/20022_535/">capacity</a>()</code> 查询。额外的内存可以通过调用 <code><a href="/cpp/library/containers/vector/47634_536/">shrink_to_fit</a>()</code> 函数返还给操作系统。</p>

<blockquote>
<p>Storage&nbsp;management is handled automatically, though hints can be given to improve efficiency.</p>

<p><small>C++编程语言国际标准：<a href="/cpp-sd/">ISO/IEC 14882:2011</a></small></p>
</blockquote>

<p>当增加向量对象中的序列的长度时，如果超出当前存储容量上限，就会发生内存重分配（Reallocation），即内部将会重新分配一个数组，然后按顺序逐个拷贝元素。其它的插入及删除操作将会修改序列中部分元素的内存地址。在上述所有情况下，指向序列中被修改部分的迭代器或引用将会失效。当未发生内存重分配，仅指向插入或删除点之前元素的迭代器或引用才会保持有效性。</p>

<p>标准库可以执行不同的增长策略来平衡内存的使用量与重分配所耗的性能。但不管哪种情况下，重分配内存的大小必须以指数方式增长，只有这样，才能将在向量末尾逐个插入元素所需的时间复杂度整体分摊（Amortized）为一个恒定值。</p>

<p>内存重分配就性能而言是一个高代价操作。如果在使用向量前知道元素的数量，可以通过&nbsp;<code><a href="/cpp/library/containers/vector/82230_537/">reserve</a>()</code> 消除内存重分配。</p>

<p>向量支持在序列末尾恒定耗时的插入及删除元素。而在向量的中间插入或删除元素则需要线性的时间。在只涉及向序列起始或未尾插入及删除元素操作时，<code><a href="/cpp/library/containers/deque/">std::deque​</a></code>&nbsp;容器的性能将会高出很多。当涉及向序列中的任意位置进行插入及删除操作时，<code><a href="/cpp/library/containers/list/">std::list</a></code> 容器的性能将会高出很多。</p>

<blockquote>
<p>In addition, it supports (amortized)&nbsp;constant time insert and erase operations at the end; insert and erase in the middle take linear time.</p>

<p><small>C++编程语言国际标准：<a href="/cpp-sd/">ISO/IEC 14882:2011</a></small></p>
</blockquote>

<p>常用操作的算法复杂度（性能相关）如下：</p>

<ul>
	<li>随机访问，时间复杂度为&nbsp;<em>O(1)</em></li>
	<li>在未尾插入或删除元素，整体分摊的时间复杂度为&nbsp;<em>O(1)</em></li>
	<li>其它位置插入或删除元素，与当前位置至向量末尾的距离有关，时间复杂度&nbsp;<em>O(n)</em><em>​​</em></li>
</ul>
</div>

#### 成员类型

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<thead>
		<tr>
			<th scope="col" style="text-align: left; width: 30%; ">成员类型</th>
			<th scope="col" style="text-align: left; ">定义</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><code>value_type</code></td>
			<td>第一个模板参数&nbsp;<em>T</em></td>
		</tr>
		<tr>
			<td><code>allocator_type</code></td>
			<td>第二个模板参数 <em>Alloc</em></td>
		</tr>
		<tr>
			<td><code>size_type</code></td>
			<td>无符号整数类型（通常为&nbsp;<code><a>size_t</a></code>）</td>
		</tr>
		<tr>
			<td><code>difference_type</code></td>
			<td>有符号整数类型（通常为&nbsp;<span style="color: rgb(0, 0, 0); font-family: DejaVuSansMono, 'DejaVu Sans Mono', courier, monospace; line-height: normal; white-space: nowrap; "><code><a>ptrdiff_t</a></code>）</span></td>
		</tr>
		<tr>
			<td><code>reference</code></td>
			<td><code>Allocator::reference</code>&nbsp;<span class="label label-info">已弃用</span><br />
			<code>value_type&amp; (C++11)</code></td>
		</tr>
		<tr>
			<td><code>const_reference</code></td>
			<td><code>Allocator::const_reference</code>&nbsp;<span class="label label-info">已弃用</span><br />
			<code>const value_type&amp;(C++11)</code></td>
		</tr>
		<tr>
			<td><code>pointer</code></td>
			<td><code>Allocator::pointer</code> <span class="label label-info">已弃用</span><br />
			<code><a>std::allocator_traits</a>&lt;Allocator&gt;::pointer (C++11)</code></td>
		</tr>
		<tr>
			<td><code>const_pointer</code></td>
			<td><code>Allocator::const_pointer</code> <span class="label label-info">已弃用</span><br />
			<code><a>std::allocator_traits</a>&lt;Allocator&gt;::const_pointer(C++11)</code></td>
		</tr>
		<tr>
			<td><code>iterator</code></td>
			<td>随机访问迭代器</td>
		</tr>
		<tr>
			<td><code>const_iterator</code></td>
			<td>常量随机访问迭代器</td>
		</tr>
		<tr>
			<td><code>reverse_iterator</code></td>
			<td><code><a>std::reverse_iterator</a>&lt;iterator&gt;</code></td>
		</tr>
		<tr>
			<td><code>const_reverse_iterator</code></td>
			<td><code><a>std::reverse_iterator</a>&lt;const_iterator&gt;</code></td>
		</tr>
	</tbody>
</table>

#### 成员函数
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><a>(constructor)</a></td>
			<td>创建 <code>vector</code></td>
		</tr>
		<tr>
			<td><a>(destructor)</a></td>
			<td>释放 <code>vector</code></td>
		</tr>
		<tr>
			<td><code><a>operator=</a></code></td>
			<td>值赋操作</td>
		</tr>
	</tbody>
</table>

#### ​Iterators

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>begin</a></code></td>
			<td>返回指向容器起始位置的迭代器（<code><a>iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code><a>end</a></code></td>
			<td>返回指向容器末尾位置的迭代器</td>
		</tr>
		<tr>
			<td><code><a>rbegin</a></code></td>
			<td>返回指向容器逆序起始位置的逆序迭代器（<code><a>reverse_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code>rend</a></code></td>
			<td>返回指向容器逆序末尾位置的逆序迭代器</td>
		</tr>
		<tr>
			<td><code><a>cbegin(C++11)</a></code></td>
			<td>返回指向容器起始位置的常迭代器（<code><a>const_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code>cend(C++11)</a></code></td>
			<td>返回指向容器末尾位置的常迭代器</td>
		</tr>
		<tr>
			<td><code>crbegin(C++11)</a></code></td>
			<td>返回指向容器逆序起始位置的常逆序迭代器（<code><a>const_reverse_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code>crend(C++11)</a></code></td>
			<td>返回指向容器逆序末尾位置的常逆序迭代器</td>
		</tr>
	</tbody>
</table>

#### Capacity

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>size</a></code></td>
			<td>返回有效元素个数</td>
		</tr>
		<tr>
			<td><code><a>max_size</a></code></td>
			<td>返回 <code>vector</code> 支持的最大元素个数</td>
		</tr>
		<tr>
			<td><code><a>resize</a></code></td>
			<td>改变有效元素的个数</td>
		</tr>
		<tr>
			<td><code><a>capacity</a></code></td>
			<td>返回当前可使用的最大元素内存块数（即存储容量）</td>
		</tr>
		<tr>
			<td><code><a>empty</a></code></td>
			<td>判断是否为空</td>
		</tr>
		<tr>
			<td><code>reserve</code></td>
			<td>请求改变存储容量</td>
		</tr>
		<tr>
			<td><code>shrink_to_fit(C++11)</code></td>
			<td>请求移除未使用的存储空间</td>
		</tr>
	</tbody>
</table>

#### Element access

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>operator[]</a></code></td>
			<td>访问元素</td>
		</tr>
		<tr>
			<td><code><a>at</a></code></td>
			<td>访问元素</td>
		</tr>
		<tr>
			<td><code><a>front</a></code></td>
			<td>访问第一个元素</td>
		</tr>
		<tr>
			<td><code><a>back</a></code></td>
			<td>访问最后一个元素</td>
		</tr>
		<tr>
			<td><code><a>data(C++11)</a></code></td>
			<td>返回当前向量内部数组的指针</td>
		</tr>
	</tbody>
</table>

#### Modifiers

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>assign</a></code></td>
			<td>将新的内容赋值给容器</td>
		</tr>
		<tr>
			<td><code><a>push_back</a></code></td>
			<td>在末尾增加一个元素</td>
		</tr>
		<tr>
			<td><code><a>pop_back</a></code></td>
			<td>删除最后一个元素</td>
		</tr>
		<tr>
			<td><code><a>insert</a></code></td>
			<td>插入元素</td>
		</tr>
		<tr>
			<td><code><a>erase</a></code></td>
			<td>删除元素</td>
		</tr>
		<tr>
			<td><code><a>swap</a></code></td>
			<td>交换内容</td>
		</tr>
		<tr>
			<td><code><a>clear</a></code></td>
			<td>清空内容</td>
		</tr>
		<tr>
			<td><code><a>emplace(C++11)</a></code></td>
			<td>构造及插入一个元素</td>
		</tr>
		<tr>
			<td><code><a>emplace_back(C++11)</a></code></td>
			<td>在容器末尾构造及插入一个元素</td>
		</tr>
	</tbody>
</table>

#### Allocator

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>get_allocator</a></code></td>
			<td>获得内存分配器</td>
		</tr>
	</tbody>
</table>
</div>

#### 非成员函数
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; ">
			<p>operator==、operator!=、operator&lt;、operator&lt;=、operator&gt;、operator&gt;=&nbsp;</p>
			</td>
			<td>关系操作符</td>
		</tr>
		<tr>
			<td><code><a>std::swap</a></code></td>
			<td>交换两个向量的内容</td>
		</tr>
	</tbody>
</table>
</div>



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
