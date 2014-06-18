#STL 容器#
* [顺序容器](#顺序容器)
  * [vector](#vector)
  * [list](#list)
  * [deque](#deque)
  * [array](#array)
  * [forward_list](#forward_list)
* [容器适配器](容器适配器)
  * [stack](stack)
  * [queue](queue)
  * [priority_queue](priority_queue)
* [关联容器](关联容器)
  * [set](set)
  * [multiset](multiset)
  * [map](map)
  * [multimap](multimap)
* [无序关联容器](无序关联容器)
  * [unordered_set](unordered_set)
  * [unordered_multiset](unordered_multiset)
  * [unordered_map](unordered_map)
  * [unordered_multimap](unordered_multimap)
* [引用](#引用)

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
#### 详细说明
<p>在向量中，所有元素都是连续存储的。也就是说，不仅可以通过迭代器（Iterators）访问各个元素，也可以通过指向元素的指针加上偏移来访问。还意味着，当向任意函数传递向量的一个元素的指针时，这个指针可以直接被认为指向了一个数组中的某个元素。</p>

<p>向量内部的存储调整是自动处理的，按需扩展或压缩。通常，相比静态数组（Static arrays），向量将会占用更多的存储空间，因为额外的内存将被未来增长的部分所使用。就因为这点，当插入元素时，向量不需要太频繁地重分配（Reallocate）内存。当前最大容量可以通过函数&nbsp;<code><a>capacity</a>()</code> 查询。额外的内存可以通过调用 <code><a>shrink_to_fit</a>()</code> 函数返还给操作系统。</p>

<p>当增加向量对象中的序列的长度时，如果超出当前存储容量上限，就会发生内存重分配（Reallocation），即内部将会重新分配一个数组，然后按顺序逐个拷贝元素。其它的插入及删除操作将会修改序列中部分元素的内存地址。在上述所有情况下，指向序列中被修改部分的迭代器或引用将会失效。当未发生内存重分配，仅指向插入或删除点之前元素的迭代器或引用才会保持有效性。</p>

<p>标准库可以执行不同的增长策略来平衡内存的使用量与重分配所耗的性能。但不管哪种情况下，重分配内存的大小必须以指数方式增长，只有这样，才能将在向量末尾逐个插入元素所需的时间复杂度整体分摊（Amortized）为一个恒定值。</p>

<p>内存重分配就性能而言是一个高代价操作。如果在使用向量前知道元素的数量，可以通过&nbsp;<code><a>reserve</a>()</code> 消除内存重分配。</p>

<p>向量支持在序列末尾恒定耗时的插入及删除元素。而在向量的中间插入或删除元素则需要线性的时间。在只涉及向序列起始或未尾插入及删除元素操作时，<code><a>std::deque​</a></code>&nbsp;容器的性能将会高出很多。当涉及向序列中的任意位置进行插入及删除操作时，<code><a>std::list</a></code> 容器的性能将会高出很多。</p>

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
<p><strong>Iterators</strong></p>
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
<p><strong>Capacity</strong></p>
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
<p><strong>Element access</strong></p>
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
<p><strong>Modifiers</strong></p>
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
<p><strong>Allocator</strong></p>
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

### list
类模板声明：

    template < class T, class Alloc = allocator<T> > class list;

<p><big>列表</big>（list）是一个允许在序列中任何一处位置以常量耗时插入或删除元素且可以双向迭代的顺序容器（Sequence container）。</p>

<p><strong>容性特性</strong>：</p>

<p><em>顺序序列</em></p>

<p style="margin-left: 40px; ">顺序容器中的元素按照严格的线性顺序排序。可以通过元素在序列中的位置访问对应的元素。</p>

<p><em>双向链表</em></p>

<p style="margin-left: 40px; ">容器中的每个元素保存了定位前一个元素及后一个元素的信息，允许在任何一处位置以常量耗时进行插入或删除操作，但不能进行直接随机访问（Direct random access）。</p>

<p><em>能够感知内存分配器的</em>（Allocator-aware）</p>

<p style="margin-left: 40px; ">容器使用一个内存分配器对象来动态地处理它的存储需求。</p>

#### 模板参数
<p><em>T</em></p>
<p style="margin-left: 40px; ">存储在容器中的元素的数据类型。</p>
<p style="margin-left: 40px; ">在类模板内部，使用其别名为&nbsp;<code>value_type</code>&nbsp;的成员类型。</p>
<p><em>Alloc</em></p>
<p style="margin-left: 40px; ">容器内部用来管理内存分配及释放的内存分配器的类型。</p>
<p style="margin-left: 40px; ">这个参数是可选的，它的默认值是&nbsp;<code>std::allocator&lt;T&gt;</code>，这个是一个最简单的非值依赖的（Value-independent）内存分配器。 在类模板内部，使用其别名为&nbsp;<code>allocator_type</code>&nbsp;的成员类型。</p>
#### 详细说明
<p>标准模板库（Standard Template Library，简称STL）中的列表容器采用的是双向链表（Doubly-linked lists）数据结构。双向链表可以保存以不同且无关的储存位置容纳的元素。元素间的顺序是通过各个元素中指向前一个元素的链接及指向后一个元素的链接等联系维护的。</p>
该特点跟 <code><a>std::&nbsp;forward_list</a></code> 容器的有点相似：主要的区别就是&nbsp;<code>std::&nbsp;forward_list</code> 是一个单向链表，因此它只能被正向迭代（&nbsp;Iterated forward），以换取更小更高效的特点。</p>

<p>增加或移动列表中的元素不会使指向它们的指针、引用、迭代器失效，只有当对应的元素被销毁时才会如此。</p>

<p>你可能会好奇，为什么STL同时提供列表（<code>std::list</code>）跟向量（<code><a>std::vector</a></code>）及其它等多种容器，原因是它们的底层实现方式是不一样的，每一种实现方式都有各自的消耗（空间或时间）及优点。</p>

<p>相比较于其它的基本标准顺序容器（数组 <code><a>std::array</a></code>、向量 <code><a>std::vector</a></code>、双端队列&nbsp;<code><a>std::deque</a></code> 等），列表通常在容器中已获得迭代器的任意位置处插入、获得（Extracting，提取）、移动元素等操作中表现出更出色的性能，对那些密集使用上述操作的算法，使用列表同样能提升性能，比如排序算法。</p>

<p>双向链表（<code><a>std::list</a></code>）及正向链表（<code><a href="forward_list">std::&nbsp;forward_list(C++11)</a></code>&nbsp;）相比于其它顺序容器的主要缺点是它们不能够通过元素在容器中的位置直接访问（Direct access）元素。举个例子：如果想访问一个列表中的第六个元素，那么就必须从一个已知位置（比如开头或末尾）处开始迭代，这会消耗与两个位置之间距间相关的线性时间。而且它们还为保存各个元素间的链接信息消耗更多额外的内存（这点对由小尺寸元素组成的大列表尤为明显）。</p>

#### 成员类型
<table class="table table-hover table-bordered table-condensed">
	<thead>
		<tr>
			<th scope="col" style="width: 30%; text-align: left; ">成员类型</th>
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
			<td>第二个模板参数&nbsp;<em>Alloc</em></td>
		</tr>
		<tr>
			<td><code>size_type</code></td>
			<td>无符号整数类型（通常为&nbsp;<code><a>size_t</a></code>）</td>
		</tr>
		<tr>
			<td><code>difference_type</code></td>
			<td>有符号整数类型（通常为&nbsp;<code><a>ptrdiff_t</a></code>）</td>
		</tr>
		<tr>
			<td><code>reference</code></td>
			<td><code>Allocator::reference(已弃用)</code>&nbsp;<br />
			<code>value_type&amp(C++11);</code></td>
		</tr>
		<tr>
			<td><code>const_reference</code></td>
			<td><code>Allocator::const_reference(已弃用)</code>&nbsp;<br />
			<code>const value_type&amp(C++11);</code>&nbsp;</td>
		</tr>
		<tr>
			<td><code>pointer</code></td>
			<td><code>Allocator::pointer(已弃用)</code>&nbsp;<br />
			<code><a>std::allocator_traits(C++11)</a>&lt;Allocator&gt;::pointer</code>&nbsp;</td>
		</tr>
		<tr>
			<td><code>const_pointer</code></td>
			<td><code>Allocator::const_pointer(已弃用)</code>&nbsp;<br />
			<code><a>std::allocator_traits(C++11)</a>&lt;Allocator&gt;::const_pointer</code>&nbsp;</td>
		</tr>
		<tr>
			<td><code>iterator</code></td>
			<td>双向迭代器</td>
		</tr>
		<tr>
			<td><code>const_iterator</code></td>
			<td>常双向迭代器</td>
		</tr>
		<tr>
			<td><code>reverse_iterator</code></td>
			<td><code><a>std::reverse_iterator</a>&lt;iterator&gt;</code></td>
		</tr>
		<tr>
			<td><code>const_reverse_iterator</code></td>
			<td><code>std::reverse_iterator&lt;const_iterator&gt;</code></td>
		</tr>
	</tbody>
</table>
#### 成员函数
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><a>(constructor)</a></td>
			<td>创建 <code><a>list</a></code></td>
		</tr>
		<tr>
			<td><a>(destructor)</a></td>
			<td>释放 <code>list</code></td>
		</tr>
		<tr>
			<td><code><a>operator=</a></code></td>
			<td>值赋操作</td>
		</tr>
	</tbody>
</table>
<p><strong>Iterators</strong>:</p>
<table class="table table-hover table-bordered table-condensed">
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
			<td><code><a>rend</a></code></td>
			<td>返回指向容器逆序末尾位置的逆序迭代器</td>
		</tr>
		<tr>
			<td><code><a>cbegin(C++11)</a></code></td>
			<td>返回指向容器起始位置的常迭代器（<code><a>const_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code><a>cend(C++11)</a></code></td>
			<td>返回指向容器末尾位置的常迭代器</td>
		</tr>
		<tr>
			<td><code><a>crbegin(C++11)</a></code></td>
			<td>返回指向容器逆序起始位置的常逆序迭代器（<code><a>const_reverse_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code><a>crend(C++11)</a></code></td>
			<td>返回指向容器逆序末尾位置的常逆序迭代器</td>
		</tr>
	</tbody>
</table>

<p><strong>Capacity</strong>:</p>

<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>empty</a></code></td>
			<td>判断是否为空</td>
		</tr>
		<tr>
			<td><code><a>size</a></code></td>
			<td>返回有效元素个数</td>
		</tr>
		<tr>
			<td><code><a>max_size</a></code></td>
			<td>返回 <code>list</code> 支持的最大元素个数</td>
		</tr>
	</tbody>
</table>

<p><strong>Element access</strong>:</p>

<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>front</a></code></td>
			<td>访问第一个元素</td>
		</tr>
		<tr>
			<td><code><a>back</a></code></td>
			<td>访问最后一个元素</td>
		</tr>
	</tbody>
</table>
<p><strong>Modifiers</strong>：</p>
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>assign</a></code></td>
			<td>将新的内容赋值给容器</td>
		</tr>
		<tr>
			<td><code><a>emplace_front(C++11)</a></code>&nbsp;</td>
			<td>在容器开头构造及插入一个元素</td>
		</tr>
		<tr>
			<td><code><a>push_front</a></code></td>
			<td>在容器开头插入一个元素</td>
		</tr>
		<tr>
			<td><code><a>pop_front</a></code></td>
			<td>删除第一个元素</td>
		</tr>
		<tr>
			<td><code><a>emplace_back(C++11)</a></code></td>
			<td>在容器末尾构造及插入一个元素</td>
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
			<td><code><a>emplace(C++11)</a></code>&nbsp;</td>
			<td>构造及插入一个元素</td>
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
			<td><code><a>resize</a></code></td>
			<td>改变有效元素的个数</td>
		</tr>
		<tr>
			<td><code><a>clear</a></code></td>
			<td>清空内容</td>
		</tr>
	</tbody>
</table>
<p><strong>Operations</strong>:</p>
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>splice</a></code></td>
			<td>使元素从一个列表移动到另一个列表</td>
		</tr>
		<tr>
			<td><code><a>remove</a></code></td>
			<td>删除值为指定值的元素</td>
		</tr>
		<tr>
			<td><code><a>remove_if</a></code></td>
			<td>删除满足指定条件的元素</td>
		</tr>
		<tr>
			<td><code><a>unique</a></code></td>
			<td>删除重复值</td>
		</tr>
		<tr>
			<td><code><a>merge</a></code></td>
			<td>合并已排序的列表</td>
		</tr>
		<tr>
			<td><code><a>sort</a></code></td>
			<td>为容器中的所有元素排序</td>
		</tr>
		<tr>
			<td><code><a>reverse</a></code></td>
			<td>反转元素的顺序</td>
		</tr>
	</tbody>
</table>
<p><strong>Observers</strong>：</p>
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>get_allocator</a></code></td>
			<td>获得内存分配器</td>
		</tr>
	</tbody>
</table>
#### 非成员函数
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; ">operator==、operator!=、operator&lt;、operator&lt;=、operator&gt;、operator&gt;=</td>
			<td>关系操作符</td>
		</tr>
		<tr>
			<td><code><a>std::swap</a></code></td>
			<td>交换两个列表的内容</td>
		</tr>
	</tbody>
</table>

### deque
类模板声明：

    template < class T, class Alloc = allocator<T> > class deque;
<p><big>双端队列</big>（<strong>D</strong>ouble-<strong>e</strong>nded&nbsp;<strong>que</strong>ue，缩写为deque）是一个大小可以动态变化（Dynamic size）且可以在两端扩展或收缩的顺序容器。</p>
<p><strong>容性特性</strong>：</p>
<p><em>顺序序列</em></p>
<p style="margin-left: 40px; ">顺序容器中的元素按照严格的线性顺序排序。可以通过元素在序列中的位置访问对应的元素。</p>
<p><em>动态数组</em></p>
<p style="margin-left: 40px; ">通常采用动态数组这一数据结构。支持对序列中的任意元素进行快速直接访问。操供了在序列末尾相对快速地添加/删除元素的操作。</p>
<p><em>能够感知内存分配器的</em>（Allocator-aware）</p>
<p style="margin-left: 40px; ">容器使用一个内存分配器对象来动态地处理它的存储需求。</p>
#### 模板参数
<p><em>T</em></p>
<p style="margin-left: 40px; ">存储在容器中的元素的数据类型。</p>
<p style="margin-left: 40px; ">在类模板内部，使用其别名为&nbsp;<code>value_type</code>&nbsp;的成员类型。</p>
<p><em>Alloc</em></p>
<p style="margin-left: 40px; ">容器内部用来管理内存分配及释放的内存分配器的类型。</p>
<p style="margin-left: 40px; ">这个参数是可选的，它的默认值是 <code>std::allocator&lt;T&gt;</code>，这个是一个最简单的非值依赖的（Value-independent）内存分配器。在类模板内部，使用其别名为&nbsp;<code>allocator_type</code> 的成员类型。</p>
</div>
#### 详细说明
<p>不同的库可能会按不同的方式来实现双端队列，通常实现为某种形式的动态数组。但不管通过哪种方式，双端队列都允许通过随机迭代器直接访问各个元素，且内部的存储空间会按需求自动地扩展或收缩。</p>
<p>容器实际分配的内存数超过容纳当前所有有效元素所需的，因为额外的内存将被未来增长的部分所使用。就因为这点，当插入元素时，容器不需要太频繁地分配内存。</p>
<p>因此，双端队列提供了类似向量（<code><a>std::vector</a></code>）的功能，且不仅可以在容器末尾，还可以在容器开头高效地插入或删除元素。</p>
<p>但是，相比向量，双端队列不保证内部的元素是按连续的存储空间存储的，因此，不允许对指针直接做偏移操作来直接访问元素。</p>
<p>在内部，双端队列与向量的工作方式完全不同：向量使用单数组数据结构，在元素增加的过程中，需要偶尔的内存重分配，而双端队列中的元素被零散地保存在不同的存储块中，容器内部会保存一些必要的数据使得可以以恒定时间及一个统一的顺序接口直接访问任意元素。因此，双端队列的内部实现比向量的稍稍复杂一点，但这也使得它在一些特定环境下可以更高效地增长，特别是对于非常长的序列，内存重分配的代价是及其高昂的。</p>
<p>对于大量涉及在除了起始或末尾以外的其它任意位置插入或删除元素的操作，相比列表（<code><a href="#list">std::list</a></code>）及正向列表（<code><a href="#forward_list">std::forward_list</a></code>），<code>deque</code> 所表现出的性能是极差的，且操作前后的迭代器、引用的一致性较低。</p>
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
			<td>无符号整数类型（通常为&nbsp;<code><a">size_t</a></code>）</td>
		</tr>
		<tr>
			<td><code>difference_type</code></td>
			<td>有符号整数类型（通常为&nbsp;<span style="color: rgb(0, 0, 0); font-family: DejaVuSansMono, 'DejaVu Sans Mono', courier, monospace; line-height: normal; white-space: nowrap; "><code><a>ptrdiff_t</a></code>）</td>
		</tr>
		<tr>
			<td><code>reference</code></td>
			<td><code>Allocator::reference(已弃用)</code>&nbsp;<br />
			<code>value_type&amp(C++11);</code></td>
		</tr>
		<tr>
			<td><code>const_reference</code></td>
			<td><code>Allocator::const_reference(已弃用)</code>&nbsp;<br/>
			<code>const value_type(C++11)&amp;</code>&nbsp;</td>
		</tr>
		<tr>
			<td><code>pointer</code></td>
			<td><code>Allocator::pointer(已弃用)</code><br />
			<code><a>std::allocator_traits(C++11)</a>&lt;Allocator&gt;::pointer</code>&nbsp;</td>
		</tr>
		<tr>
			<td><code>const_pointer</code></td>
			<td><code>Allocator::const_pointer(已弃用)</code><br />
			<code><a>std::allocator_traits(C++11)</a>&lt;Allocator&gt;::const_pointer</code>&nbsp;</td>
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
			<td>创建 <code><font face="monospace">deque</font></code></td>
		</tr>
		<tr>
			<td><a>(destructor)</a></td>
			<td>释放 <code>deque</code></td>
		</tr>
		<tr>
			<td><code><a>operator=</a></code></td>
			<td>值赋操作</td>
		</tr>
	</tbody>
</table>

<p><strong>​Iterators:</strong></p>

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
			<td>返回指向容器逆序起始位置的逆序迭代器（<code><a href="/cpp/library/iterators/28051_272/">reverse_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code><a>rend</a></code></td>
			<td>返回指向容器逆序末尾位置的逆序迭代器</td>
		</tr>
		<tr>
			<td><code><a>cbegin(C++11)</a></code></td>
			<td>返回指向容器起始位置的常迭代器（<code><a>const_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code><a>cend(C++11)</a></code></td>
			<td>返回指向容器末尾位置的常迭代器</td>
		</tr>
		<tr>
			<td><code><a>crbegin(C++11)</a></code></td>
			<td>返回指向容器逆序起始位置的常逆序迭代器（<code><a href="/cpp/library/iterators/47805_613/">const_reverse_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code><a>crend(C++11)</a></code></td>
			<td>返回指向容器逆序末尾位置的常逆序迭代器</td>
		</tr>
	</tbody>
</table>

<p><strong>Capacity:</strong></p>

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>size</a></code></td>
			<td>返回有效元素个数</td>
		</tr>
		<tr>
			<td><code><a>max_size</a></code></td>
			<td>返回 <code><font face="monospace">deque</font></code>&nbsp;支持的最大元素个数</td>
		</tr>
		<tr>
			<td><code><a>resize</a></code></td>
			<td>改变有效元素的个数</td>
		</tr>
		<tr>
			<td><code><a>empty</a></code></td>
			<td>判断是否为空</td>
		</tr>
		<tr>
			<td><code><a>shrink_to_fit(C++11)</a></code></td>
			<td>请求移除未使用的存储空间</td>
		</tr>
	</tbody>
</table>

<p><strong>Element access:</strong></p>

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
	</tbody>
</table>

<p><strong>Modifiers:</strong></p>

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
			<td><code><a>push_front</a></code></td>
			<td>在开头增加一个元素</td>
		</tr>
		<tr>
			<td><code><a>pop_back</a></code></td>
			<td>删除最后一个元素</td>
		</tr>
		<tr>
			<td><code><a>pop_front</a></code></td>
			<td>删除第一个元素</td>
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
			<td><code><a>emplace_front(C++11)</a></code></td>
			<td>在容器开头构造及插入一个元素</td>
		</tr>
		<tr>
			<td><code><a>emplace_back(C++11)</a></code></td>
			<td>在容器末尾构造及插入一个元素</td>
		</tr>
	</tbody>
</table>

<p><strong>Allocator:</strong></p>

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>get_allocator</a></code></td>
			<td>获得内存分配器</td>
		</tr>
	</tbody>
</table>
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
			<td>交换两个双端队列的内容</td>
		</tr>
	</tbody>
</table>
#### 算法相关
<p>&lt;algorithm&gt头文件中包含大量与 <code>deque</code> 相关的算法，常使用的有：</p>

<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; ">搜索算法</td>
			<td><code><a>std::adjacent_find</a></code>、<code><a>std::count</a>、</code><br />
			<code><a>std::count_if</a></code>、<code><a>std::find</a>、</code><br />
			<code><a>std::find_if</a></code>、<code><a>std::find_end</a>、</code><br />
			<code><a>std::find_first_of</a></code>、<code><a>std::search</a>、</code><br />
			<code><a>std::search_n</a></code>、<code><a>std::equal</a>、</code><br />
			<code><a>std::mismatch</a></code></td>
		</tr>
		<tr>
			<td>分类排序</td>
			<td><code><a>std::sort</a></code>、<code><a>std::partial_sort</a></code>、<br />
			<code><a>std::stable_sort</a></code>、</td>
		</tr>
		<tr>
			<td>二分查找（Binary search）</td>
			<td><code><a>std::lower_bound</a></code>、<code><a>std::upper_bound</a>、</code><br />
			<code><a>std::equal_range</a></code>、<code><a>std::binary_search</a></code></td>
		</tr>
		<tr>
			<td>集合（Set）操作</td>
			<td><code><a>std::includes</a></code>、<code><a>std::set_difference</a>、</code><br />
			<code><a>std::set_intersection</a></code>、<code><a>std::set_union</a>、</code><br />
			<code><a>std::set_symmetric_difference</a></code></td>
		</tr>
		<tr>
			<td>堆（Heap）操作</td>
			<td><code><a>std::make_heap</a></code>、<code><a>std::push_heap</a>、</code><br />
			<code><a>std::pop_heap</a></code>、<code><a>std::sort_heap</a></code></td>
		</tr>
		<tr>
			<td>最大与最小</td>
			<td><code><a>std::min_element</a></code>、<code><a>std::max_element</a></code></td>
		</tr>
		<tr>
			<td>字典序比较</td>
			<td><code><a>std::lexicographical_compare</a></code></td>
		</tr>
		<tr>
			<td>排列生成器</td>
			<td><code><a>std::next_permutation</a></code>、<br />
			<code><a>std::prev_permutation</a></code></td>
		</tr>
		<tr>
			<td>第n个元素</td>
			<td><code><a>std::nth_element</a></code></td>
		</tr>
		<tr>
			<td>其它操作</td>
			<td><code><a>std::all_of</a></code>、<code><a>std::any_of</a></code>、<code><a>std::none_of</a></code>、<br />
			<code><a>std::for_each</a></code>、<code><a>std::copy</a></code>、<code><a>std::copy_if</a></code>、<br />
			<code><a>std::copy_n</a></code>、<code><a>std::copy_backward</a></code>、<br />
			<code>​<a>std::move</a></code>、<code><a>std::move_backward</a></code>、<br />
			<code><a>std::swap_ranges</a></code>、<code><a>std::iter_swap</a></code>、<br />
			<code><a>std::transform</a></code>、<code><a>std::replace</a></code>、<br />
			​<code><a>std::replace_if</a></code>、<code><a>std::replace_copy</a></code>、<br />
			<code><a>std::replace_copy_if</a></code>、<code><a>std::fill</a></code>、<br />
			<code><a>std::fill_n</a></code>、<code><a>std::generate</a></code>、<br />
			<code><a>std::generate_n</a></code>、<code><a>std::remove</a></code>、<br />
			<code><a>std::remove_if</a></code>、<code><a>std::unique</a></code>、<br />
			<code><a>std::unique_copy</a></code>、<code><a>std::reverse</a></code>、<br />
			<code><a>​std::reverse_copy</a></code>、<code><a>std::rotate</a></code>、<br />
			<code><a>std::rotate_copy</a></code>、<code><a>std::random_shuffle</a></code>、<br />
			<code><a>std::shuffle</a></code>、<code><a>std::partition</a></code>、<br />
			<code><a>std::is_partitioned</a></code>、<code><a>std::stable_partition</a></code>、<br />
			​<code><a>std::partition_copy</a></code>、<code><a>std::merge</a></code></td>
		</tr>
	</tbody>
</table>



### array

类模板声明：

    template < class T, size_t N > class array;
<p><big>数组</big><span class="text-muted">（array）</span>是一个固定大小<span class="text-muted">（Fixed-size）</span>的顺序容器<span class="text-muted">（Sequence container）</span>。容器容纳了具体<span class="text-muted">（Specific）</span>数目的元素，这些元素逐个排列在一个严格的线性序列中。</p>
<p><strong>容性特性</strong>：</p>
<p><em>顺序序列</em><span class="text-muted">（Sequence）</span></p>
<p style="margin-left: 40px; ">顺序容器中的元素按照严格的线性顺序排序。可以通过元素在序列中的位置访问对应的元素。</p>
<p><em>连续存储空间</em><span class="text-muted">（Contiguous storage）</span></p>
<p style="margin-left: 40px; ">所有元素存储在一个连续的内存位置处，使得可以以常量时间随机访问元素。指向元素的指针可以通过偏移访问其它元素。</p>
<p><em>固定大小的聚集体</em><span class="text-muted">（Fixed-size aggregate）</span></p>
<p style="margin-left: 40px; ">容器使用<strong>隐式</strong><span class="text-muted">（Implicit）</span>构造函数<span class="text-muted">（Constructor）</span>及析构函数<span class="text-muted">（Destructor）</span>来静态地分配所需的存储空间。它的大小是一个编译时<span class="text-muted">（Compile-time）</span>确定的常量。除了自身所需外，不会消耗额外的内存或时间。</p>
#### 模板参数
<p><em>T</em></p>
<p style="margin-left: 40px; ">容器所包含的元素的类型。</p>
<p style="margin-left: 40px; ">在类模板内部，使用其别名为&nbsp;<code>value_type</code>&nbsp;的成员类型。</p>
<p><em>N</em></p>
<p style="margin-left: 40px; ">数组的大小，以元素的个数为单位。</p>
#### 详细说明
<p>在 <code>array</code> 容器内部，不会保存除了元素的任意其它数据（甚至没保存容器的大小，这个是一个模板参数，在编译时就已固定）。该容器同由言语中的括号语义<span class="text-muted">（[]）</span>定义的普通数组一样高效。<code>array</code> 仅仅是为普通数组添加了一些成员或全局函数，这使得数组能够被当成标准容器来使用。</p>

<p>区别于其它标准容器，<code>array</code> 拥有一个固定的大小，且不需要通过内存分配器<span class="text-muted">（Allocator）</span>管理元素的储存空间。它是一个封装了固定数量元素的数组的聚合类型<span class="text-muted">（Aggregate）</span>。因此，<code>array</code>&nbsp;不能被动态地扩展或压缩。</p>

<p>大小为 <span class="text-info">0</span> 的 <code>array</code> 容器是允许的，但是这样的数组里的元素是不能被解引用的<span class="text-muted">（Dereferenced）</span>（因为没有元素可以被解引用，相关成员函数有&nbsp;<code><a>front</a></code>、<code><a>back</a></code>、及 <code><a>data</a></code>）。</p>

<p>区别于其它标准容器，<a>交换</a><span class="text-muted">（Swap）</span>两个 <code>array</code> 容器是一个线性操作（即时间复杂度为 <em>O(n)</em>），涉及分别交换范围内的所有元素，这通常被认为是一个低效的操作。</p>

<p><code>array</code> 容器唯一具有的另一个特征是：可以把 <code>array</code> 容器当成一个<a>多元组</a><span class="text-muted">（Tuple）</span>对象。在头文件 <a>&lt;array&gt;</a> 中，通过重载全局函数 <code>get</code> 使得通过 <code>get</code> 访问 <code>array</code> 中的元素时，<code>array</code> 容器就像一个多元组。</p>
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
			<td><code>size_type</code></td>
			<td>第二个模板参数 N，无符号整数类型（通常为&nbsp;<code><a>size_t</a></code>）</td>
		</tr>
		<tr>
			<td><code>difference_type</code></td>
			<td>有符号整数类型（通常为&nbsp;<code><a>ptrdiff_t</a></code>）</td>
		</tr>
		<tr>
			<td><code>reference</code></td>
			<td><code>value_type&amp;</code></td>
		</tr>
		<tr>
			<td><code>const_reference</code></td>
			<td><code>const value_type&amp;</code></td>
		</tr>
		<tr>
			<td><code>pointer</code></td>
			<td><code>T*</code></td>
		</tr>
		<tr>
			<td><code>const_pointer</code></td>
			<td><code>const T*</code></td>
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
<h3>迭代器<span class="text-muted">（​Iterators）</span></h3>
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed" style="width: 100%; ">
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
			<td><code><a>rend</a></code></td>
			<td>返回指向容器逆序末尾位置的逆序迭代器</td>
		</tr>
		<tr>
			<td><code><a>cbegin</a></code></td>
			<td>返回指向容器起始位置的常迭代器（<code><a>const_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code><a>cend</a></code></td>
			<td>返回指向容器末尾位置的常迭代器</td>
		</tr>
		<tr>
			<td><code><a>crbegin</a></code></td>
			<td>返回指向容器逆序起始位置的常逆序迭代器（<code><a>const_reverse_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code><a>crend</a></code></td>
			<td>返回指向容器逆序末尾位置的常逆序迭代器</td>
		</tr>
	</tbody>
</table>
<h3>容量<span class="text-muted">（Capacity）</span></h3>
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed" style="width: 100%; ">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>size</a></code></td>
			<td>返回有效元素个数</td>
		</tr>
		<tr>
			<td><code><a>max_size</a></code></td>
			<td>返回 <code>array</code> 支持的最大元素个数</td>
		</tr>
		<tr>
			<td><code><a>empty</a></code></td>
			<td>检测 <code>array</code> 是否为空</td>
		</tr>
	</tbody>
</table>
<h3>元素访问<span class="text-muted">（Element access）</span></h3>
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed" style="width: 100%; ">
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
			<td><code><a>data</a></code></td>
			<td>返回 <code>array</code> 内部数组的指针</td>
		</tr>
	</tbody>
</table>
<h3>修改器<span class="text-muted">（Modifiers）</span></h3>
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed" style="width: 100%; ">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>fill</a></code></td>
			<td>用新的值填充容器</td>
		</tr>
		<tr>
			<td><code><a>swap</a></code></td>
			<td>交换内容</td>
		</tr>
	</tbody>
</table>
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
			<td>交换两个数组的内容</td>
		</tr>
	</tbody>
</table>
</div>
#### 特例化
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code>tuple_element&lt;array&gt;</code></td>
			<td>基于 <code>array</code> 的多元组<span class="text-muted">（Tuple）</span>中的元素类型</td>
		</tr>
		<tr>
			<td><code>tuple_size&lt;array&gt;</code></td>
			<td>基于 <code>array</code> 的多元组的大小</td>
		</tr>
	</tbody>
</table>
#### 算法相关
<p>&lt;algorithm&gt;头文件中包含大量与 <code>array</code> 相关的算法，常使用的有</p>

<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; ">搜索算法</td>
			<td><code><a>std::adjacent_find</a></code>、<code><a>std::count</a>、</code><br />
			<code><a>std::count_if</a></code>、<code><a>std::find</a>、</code><br />
			<code><a>std::find_if</a></code>、<code><a>std::find_end</a>、</code><br />
			<code><a>std::find_first_of</a></code>、<code><a>std::search</a>、</code><br />
			<code><a>std::search_n</a></code>、<code><a>std::equal</a>、</code><br />
			<code><a>std::mismatch</a></code></td>
		</tr>
		<tr>
			<td>分类排序</td>
			<td><code><a>std::sort</a></code>、<code><a>std::partial_sort</a></code>、<br />
			<code><a>std::stable_sort</a></code>、</td>
		</tr>
		<tr>
			<td>二分查找<span class="text-muted">（Binary search）</span></td>
			<td><code><a>std::lower_bound</a></code>、<code><a>std::upper_bound</a>、</code><br />
			<code><a>std::equal_range</a></code>、<code><a>std::binary_search</a></code></td>
		</tr>
		<tr>
			<td>集合<span class="text-muted">（Set）</span>操作</td>
			<td><code><a>std::includes</a></code>、<code><a>std::set_difference</a>、</code><br />
			<code><a>std::set_intersection</a></code>、<code><a>std::set_union</a>、</code><br />
			<code><a>std::set_symmetric_difference</a></code></td>
		</tr>
		<tr>
			<td>堆<span class="text-muted">（Heap）</span>操作</td>
			<td><code><a>std::make_heap</a></code>、<code><a>std::push_heap</a>、</code><br />
			<code><a>std::pop_heap</a></code>、<code><a>std::sort_heap</a></code></td>
		</tr>
		<tr>
			<td>最大与最小</td>
			<td><code><a>std::min_element</a></code>、<code><a>std::max_element</a></code></td>
		</tr>
		<tr>
			<td>字典序比较</td>
			<td><code><a>std::lexicographical_compare</a></code></td>
		</tr>
		<tr>
			<td>排列生成器</td>
			<td><code><a>std::next_permutation</a></code>、<br />
			<code><a>std::prev_permutation</a></code></td>
		</tr>
		<tr>
			<td>第 <em>n</em> 个元素</td>
			<td><code><a>std::nth_element</a></code></td>
		</tr>
		<tr>
			<td>其它操作</td>
			<td><code><a>std::all_of</a></code>、<code><a>std::any_of</a></code>、<code><a>std::none_of</a></code>、<br />
			<code><a>std::for_each</a></code>、<code><a>std::copy</a></code>、<code><a>std::copy_if</a></code>、<br />
			<code><a>std::copy_n</a></code>、<code><a>std::copy_backward</a></code>、<br />
			<code>​<a>std::move</a></code>、<code><a>std::move_backward</a></code>、<br />
			<code><a>std::swap_ranges</a></code>、<code><a>std::iter_swap</a></code>、<br />
			<code><a>std::transform</a></code>、<code><a>std::replace</a></code>、<br />
			​<code><a>std::replace_if</a></code>、<code><a>std::replace_copy</a></code>、<br />
			<code><a>std::replace_copy_if</a></code>、<code><a>std::fill</a></code>、<br />
			<code><a>std::fill_n</a></code>、<code><a>std::generate</a></code>、<br />
			<code><a>std::generate_n</a></code>、<code><a>std::remove</a></code>、<br />
			<code><a>std::remove_if</a></code>、<code><a>std::unique</a></code>、<br />
			<code><a>std::unique_copy</a></code>、<code><a>std::reverse</a></code>、<br />
			<code><a>​std::reverse_copy</a></code>、<code><a>std::rotate</a></code>、<br />
			<code><a>std::rotate_copy</a></code>、<code><a>std::random_shuffle</a></code>、<br />
			<code><a>std::shuffle</a></code>、<code><a>std::partition</a></code>、<br />
			<code><a>std::is_partitioned</a></code>、<code><a>std::stable_partition</a></code>、<br />
			​<code><a>std::partition_copy</a></code>、<code><a>std::merge</a></code></td>
		</tr>
	</tbody>
</table>

### forward_list
类模板声明：

    template < class T, class Container = deque<T> > class queue;
<p><big>正向列表</big>（Forward list）是一个允许在序列中任何一处位置以常量耗时插入或删除元素的顺序容器（Sequence container）。</p>

<p><strong>容性特性</strong>：</p>

<p><em>顺序序列</em></p>

<p style="margin-left: 40px; ">顺序容器中的元素按照严格的线性顺序排序。可以通过元素在序列中的位置访问对应的元素。</p>

<p><em>单链表</em></p>

<p style="margin-left: 40px; ">容器中的每个元素保存了定位前一个元素及后一个元素的信息，允许在任何一处位置以常量耗时进行插入或删除操作，但不能进行直接随机访问（Direct random access）。</p>

<p><em>能够感知内存分配器的（Allocator-aware）</em></p>

<p style="margin-left: 40px; ">容器使用一个内存分配器对象来动态地处理它的存储需求。</p>
#### 模板参数
<p><em>T</em></p>

<p style="margin-left: 40px; ">存储在容器中的元素的数据类型。</p>

<p style="margin-left: 40px; ">在类模板内部，使用其别名为&nbsp;<code>value_type</code>&nbsp;的成员类型。</p>

<p><em>Alloc</em></p>

<p style="margin-left: 40px; ">容器内部用来管理内存分配及释放的内存分配器的类型。</p>

<p style="margin-left: 40px; ">这个参数是可选的，它的默认值是&nbsp;<code>std::allocator&lt;T&gt;</code>，这个是一个最简单的非值依赖的（Value-independent）内存分配器。 在类模板内部，使用其别名为&nbsp;<code>allocator_type</code>&nbsp;的成员类型。</p>
#### 详细说明
<p>标准模板库（Standard Template Library，简称STL）中的正向列表容器采用的是单链表（Singly-linked lists）数据库构。单链表可以保存以不同且无关的储存位置容纳的元素。元素间的顺序是通过各个元素中指向下一个元素的链接这一联系维护的。</p>

<p>该特点跟&nbsp;<code><a href="/cpp/library/containers/list/">std:: list</a></code>&nbsp;容器的有点相似：主要的区别就是&nbsp;<code>std:: list</code>&nbsp;的元素中不仅保存了指向下一个元素的链接，还保存了指向上一个元素的链接，这使得 <code>std::list</code>&nbsp;允许双向迭代，但消耗更多的存储空间且在插入删除元素时会有稍高（Slight higher）的耗时。因此 <code>std::forward_list</code> 对象比 <code>std::list</code> 对象更高效，尽管它们只能正向迭代。</p>

<p>增加或移动正向列表中的元素不会使指向它们的指针、引用、迭代器失效，只有当对应的元素被销毁时才会如此。</p>

<p>相比较于其它的基本标准顺序容器（数组&nbsp;<code><a href="/cpp/library/containers/array/">std::array</a></code>、向量&nbsp;<code><a href="/cpp/library/containers/vector/">std::vector</a></code>、双端队列&nbsp;<code><a href="/cpp/library/containers/deque/">std::deque</a></code>&nbsp;等），正向列表通常在容器中已获得迭代器的任意位置处插入、获得（Extracting，提取）、移动元素等操作中表现出更出色的性能，对那些密集使用上述操作的算法，使用正向列表同样能提升性能，比如排序算法。</p>

<p>双向链表（<code>std::list</code>）及正向链表（<code>std::&nbsp;forward_list</code>）相比于其它顺序容器的主要缺点是它们不能够通过元素在容器中的位置直接访问（Direct access）元素。举个例子：如果想访问一个正向列表中的第六个元素，那么就必须从一个已知位置（比如开头或末尾）处开始迭代，这会消耗与两个位置之间距间相关的线性时间。而且它们还为保存各个元素间的链接信息消耗更多额外的内存（这点对由小尺寸元素组成而元素数较大的正向列表尤为明显）。</p>

<p><code>forward_list</code> 类模板是专为极度考虑性能的程序而设计的，它就跟自实现的C型单链表（C-style singly-linked list）一样高效。甚至为了性能，它是唯一一个缺少 <code>size</code> 成员函数的标准容器：这是出于其单链表的性质，如果拥有 <code>size</code> 成员函数，就必须消耗常量时间来维护一个用于保存当前容器大小的内部计数器，这会消耗更多的存储空间，且使得插入及删除操作略微降低性能。如果想获得 <code>forward_list</code> 的大小，可以使用 <code>std::distance</code> 算法且传递 <code><a>forward_list::begin</a></code> 及 <code><a >forward_list::end</a></code> 参数，该操作的时间复杂度为 <em>O(n)</em>。</p>

<p>对任意列表（std::list）进行插入或删除元素操作需要访问插入位置前的元素，但对 forward_list 来说访问该元素没有常数时间（Constant-time）的方法。因为这个原因，对传递给<a>清除</a>（Erase）、<a>拼接</a>（Splice）等成员函数的范围参数作了修改，这些范围必须为开区间（即不包括末尾元素的同时也不包括起始元素）。</p>
#### 成员类型
<table class="table table-hover table-bordered table-condensed">
	<thead>
		<tr>
			<th scope="col" style="width: 30%; text-align: left; ">成员类型</th>
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
			<td>第二个模板参数&nbsp;<em>Alloc</em></td>
		</tr>
		<tr>
			<td><code>size_type</code></td>
			<td>无符号整数类型（通常为&nbsp;<code><a>size_t</a></code>）</td>
		</tr>
		<tr>
			<td><code>difference_type</code></td>
			<td>有符号整数类型（通常为&nbsp;<code><a>ptrdiff_t</a></code>）</td>
		</tr>
		<tr>
			<td><code>reference</code></td>
			<td><code>value_type&amp;</code></td>
		</tr>
		<tr>
			<td><code>const_reference</code></td>
			<td><code>const value_type&amp;</code></td>
		</tr>
		<tr>
			<td><code>pointer</code></td>
			<td><code><a>std::allocator_traits</a>&lt;Allocator&gt;::pointer</code></td>
		</tr>
		<tr>
			<td><code>const_pointer</code></td>
			<td><code>std::allocator_traits&lt;Allocator&gt;::const_pointer</code></td>
		</tr>
		<tr>
			<td><code>iterator</code></td>
			<td>正向迭代器</td>
		</tr>
		<tr>
			<td><code>const_iterator</code></td>
			<td>常正向迭代器</td>
		</tr>
	</tbody>
</table>
#### 成员函数
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><a>(constructor)</a></td>
			<td>创建 <code><font face="monospace">forward_list</font></code></td>
		</tr>
		<tr>
			<td><a>(destructor)</a></td>
			<td>释放&nbsp;<code>forward_list​</code></td>
		</tr>
		<tr>
			<td><code><a>operator=</a></code></td>
			<td>值赋操作</td>
		</tr>
	</tbody>
</table>
<p><strong>Iterators</strong>:</p>
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>before_begin</a></code></td>
			<td>返回指向容器起始位置前的迭代器（<code><a>iterator</a></code>）</td>
		</tr>
		<tr>
			<td style="width: 30%; "><code><a>begin</a></code></td>
			<td>返回指向容器起始位置的迭代器</td>
		</tr>
		<tr>
			<td><code><a>end</a></code></td>
			<td>返回指向容器末尾位置的迭代器</td>
		</tr>
		<tr>
			<td><code><a>cbefore_begin</a></code></td>
			<td>返回指向容器起始位置前的常迭代器（<code><a>const_iterator</a></code>）</td>
		</tr>
		<tr>
			<td><code><a>cbegin</a></code></td>
			<td>返回指向容器起始位置的常迭代器</td>
		</tr>
		<tr>
			<td><code><a>cend</a></code></td>
			<td>返回指向容器末尾位置的常迭代器</td>
		</tr>
	</tbody>
</table>
<p><strong>Capacity</strong>:</p>
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>empty</a></code></td>
			<td>判断是否为空</td>
		</tr>
		<tr>
			<td><code><a>max_size</a></code></td>
			<td>返回 <code>forward_list</code>&nbsp;支持的最大元素个数</td>
		</tr>
	</tbody>
</table>
<p><strong>Element access</strong>:</p>
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>front</a></code></td>
			<td>访问第一个元素</td>
		</tr>
	</tbody>
</table>
<p><strong>Modifiers</strong>：</p>
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>assign</a></code></td>
			<td>将新的内容赋值给容器</td>
		</tr>
		<tr>
			<td><code><a>emplace_front</a></code>&nbsp;</td>
			<td>在容器开头构造及插入一个元素</td>
		</tr>
		<tr>
			<td><code><apush_front</a></code></td>
			<td>在容器开头插入一个元素</td>
		</tr>
		<tr>
			<td><code><a>pop_front</a></code></td>
			<td>删除第一个元素</td>
		</tr>
		<tr>
			<td><code><a>emplace_after</a></code></td>
			<td>构造及插入一个元素</td>
		</tr>
		<tr>
			<td><code><a>insert_after</a></code></td>
			<td>插入元素</td>
		</tr>
		<tr>
			<td><code><a>erase_after</a></code></td>
			<td>删除元素</td>
		</tr>
		<tr>
			<td><code><a>swap</a></code></td>
			<td>交换内容</td>
		</tr>
		<tr>
			<td><code><a>resize</a></code></td>
			<td>改变有效元素的个数</td>
		</tr>
		<tr>
			<td><code><a>clear</a></code></td>
			<td>清空内容</td>
		</tr>
	</tbody>
</table>
<p><strong>Operations</strong>:</p>
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>splice_after</a></code></td>
			<td>使元素从一个正向列表移动到另一个正向列表</td>
		</tr>
		<tr>
			<td><code><a>remove</a></code></td>
			<td>删除值为指定值的元素</td>
		</tr>
		<tr>
			<td><code><a>remove_if</a></code></td>
			<td>删除满足指定条件的元素</td>
		</tr>
		<tr>
			<td><code><a>unique</a></code></td>
			<td>删除重复值</td>
		</tr>
		<tr>
			<td><code><a>merge</a></code></td>
			<td>合并已排序的正向列表</td>
		</tr>
		<tr>
			<td><code><a>sort</a></code></td>
			<td>为容器中的所有元素排序</td>
		</tr>
		<tr>
			<td><code><a>reverse</a></code></td>
			<td>反转元素的顺序</td>
		</tr>
	</tbody>
</table>
<p><strong>Observers</strong>：</p>
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>get_allocator</a></code></td>
			<td>获得内存分配器</td>
		</tr>
	</tbody>
</table>
#### 非成员函数
<table class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; ">operator==、operator!=、operator&lt;、operator&lt;=、operator&gt;、operator&gt;=</td>
			<td>关系操作符</td>
		</tr>
		<tr>
			<td><code><a>std::swap</a></code></td>
			<td>交换两个正向列表的内容</td>
		</tr>
	</tbody>
</table>

## 容器适配器

### stack
类模板声明：

    template < class T, class Container = deque<T> > class stack;
<p><big>栈</big>（stack）是一个容器适配器（Container adaptor）类型，被特别设计用来运行于<strong>LIFO</strong>（Last-in first-out）场景，在该场景中，只能从容器末尾添加（Insert）或提取（Extract）元素。</p>
</div>
</div>

#### 模板参数
<p><em>T</em></p>

<p style="margin-left: 40px; ">容器所包含的元素的类型。</p>

<p style="margin-left: 40px; ">在类模板内部，使用其别名为&nbsp;<code>value_type</code>&nbsp;的成员类型。</p>

<p><em>Container</em></p>

<p style="margin-left: 40px; ">底层的用于存储元素的容器的类型。</p>

#### 详细说明
<code>stack</code> 通常被实现为容器适配器，即使用一个特定容器类的封装对象作为它的底层容器。<code>stack</code> 提供了一系列成员函数用于操作它的元素，只能从容器&ldquo;后面&rdquo;压进（Push）元素或从容器&ldquo;后面&rdquo;提取（Pop）元素。容器中的&ldquo;后面&rdquo;位置也被称为&ldquo;栈顶&rdquo;。
<p>用来实现栈的底层容器必须满足顺序容器的所有必要条件。同时，它还必须提供以下语义的成员函数：</p>

<ul>
	<li><code>back()</code></li>
	<li><code>push_back()​</code></li>
	<li><code>pop_back()</code></li>
</ul>

<p>满足上述条件的标准容器有 <code><a>std::vector</a></code>、<code><a>std::deque</a></code> 及 <code><a>std::list</a></code>，如果未特别指定 <code>stack</code> 的底层容器，标准容器 <code>std::deque</code> 将被使用。</p>


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
			<td><code>container_type</code></td>
			<td>第二个模板参数&nbsp;<em>Container</em></td>
		</tr>
		<tr>
			<td><code>size_type</code></td>
			<td><code>Container::size_type</code></td>
		</tr>
		<tr>
			<td><code>reference</code></td>
			<td><code>Container::reference</code></td>
		</tr>
		<tr>
			<td><code>const_reference</code></td>
			<td><code>Container::const_reference</code></td>
		</tr>
	</tbody>
</table>
</div>

#### 成员函数
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><a>(constructor)</a></td>
			<td>创建 <code>stack</code></td>
		</tr>
		<tr>
			<td><a>(destructor)</a></td>
			<td>释放 <code>stack</code></td>
		</tr>
		<tr>
			<td><code><a>operator=</a></code></td>
			<td>赋值操作</td>
		</tr>
	</tbody>
</table>

<p><strong>Element access:</strong></p>

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>top</a></code></td>
			<td>访问顶部元素</td>
		</tr>
	</tbody>
</table>

<p><strong>Capacity:</strong></p>

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>empty</a></code></td>
			<td>判断是否为空</td>
		</tr>
		<tr>
			<td><code><a>size</a></code></td>
			<td>返回有效元素个数</td>
		</tr>
	</tbody>
</table>

<p><strong>Modifiers:</strong></p>

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>push</a></code></td>
			<td>在容器顶部插入元素</td>
		</tr>
		<tr>
			<td><code><a>pop</a></code></td>
			<td>移除容器顶部的元素</td>
		</tr>
		<tr>
			<td><code><a>emplace(C++11)</a></code></td>
			<td>在容器顶部放置插入元素</td>
		</tr>
		<tr>
			<td><code><a>swap</a></code></td>
			<td>交换容器的内容</td>
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
			<td>交换两个栈的内容</td>
		</tr>
	</tbody>
</table>
</div>

### queue
类模板声明：

    template < class T, class Container = deque<T> > class queue;
<p><big>队列</big>（queue）是一个容器适配器（Container adaptor）类型，被特别设计用来运行于<strong>FIFO</strong>（First-in first-out）场景，在该场景中，只能从容器一端添加（Insert）元素，而在另一端提取（Extract）元素。</p>
</div>
</div>

#### 模板参数
<p><em>T</em></p>

<p style="margin-left: 40px; ">容器所包含的元素的类型。</p>

<p style="margin-left: 40px; ">在类模板内部，使用其别名为&nbsp;<code>value_type</code>&nbsp;的成员类型。</p>

<p><em>Container</em></p>

<p style="margin-left: 40px; ">底层的用于存储元素的容器的类型。</p>
</div>

#### 详细说明
<code>queue</code>&nbsp;通常被实现为容器适配器，即使用一个特定容器类的封装对象作为它的底层容器。<code>queue</code> 提供了一系列成员函数用于操作它的元素，只能从容器&ldquo;后面&rdquo;<a>压进</a>（Push）元素,从容器&ldquo;前面&rdquo;<a>提取</a>（Pop）元素。
<p>用来实现队列的底层容器必须满足顺序容器的所有必要条件。同时，它还必须提供以下语义的成员函数：</p>
<ul>
	<li><code>front()</code></li>
	<li><code>back()</code></li>
	<li><code>push_back()​</code></li>
	<li><code>pop_front()</code></li>
</ul>
<p>满足上述条件的标准容器有 <code><a>std::deque</a></code> 及 <code><a>std::list</a></code>，如果未特别指定 <code>queue</code> 的底层容器，标准容器 <code>std::deque</code> 将被使用。</p>
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
			<td><code>container_type</code></td>
			<td>第二个模板参数&nbsp;<em>Container</em></td>
		</tr>
		<tr>
			<td><code>size_type</code></td>
			<td><code>Container::size_type</code></td>
		</tr>
		<tr>
			<td><code>reference</code></td>
			<td><code>Container::reference</code></td>
		</tr>
		<tr>
			<td><code>const_reference</code></td>
			<td><code>Container::const_reference</code></td>
		</tr>
	</tbody>
</table>
</div>
#### 成员函数
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><a>(constructor)</a></td>
			<td>创建 <code>queue</code></td>
		</tr>
		<tr>
			<td><a>(destructor)</a></td>
			<td>释放 <code>queue</code></td>
		</tr>
		<tr>
			<td><code><a>operator=</a></code></td>
			<td>赋值操作</td>
		</tr>
	</tbody>
</table>
<p><strong>Element access:</strong></p>
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>front</a></code></td>
			<td>访问第一个元素</td>
		</tr>
		<tr>
			<td style="width: 30%; "><code><a>back</a></code></td>
			<td>访问最后一个元素</td>
		</tr>
	</tbody>
</table>
<p><strong>Capacity:</strong></p>
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>empty</a></code></td>
			<td>判断是否为空</td>
		</tr>
		<tr>
			<td><code><a>size</a></code></td>
			<td>返回有效元素个数</td>
		</tr>
	</tbody>
</table>
<p><strong>Modifiers:</strong></p>
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>push</a></code></td>
			<td>在容器顶部插入元素</td>
		</tr>
		<tr>
			<td><code><a>pop</a></code></td>
			<td>移除容器顶部的元素</td>
		</tr>
		<tr>
			<td><code><a>emplace(C++11)</a></code></td>
			<td>在容器顶部放置插入元素</td>
		</tr>
		<tr>
			<td><code><a>swap</a></code></td>
			<td>交换容器的内容</td>
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
			<td><code><a href="/cpp/library/general-utilities/58569_89/">std::swap</a></code></td>
			<td>交换两个队列的内容</td>
		</tr>
	</tbody>
</table>
</div>
### priority_queue
类模板声明：

    template < class T, class Container = vector<T>,
    class Compare = less<typename Container::value_type> > class priority_queue;
<p><big>优先级队列</big>（priority queue）是一个容器适配器（Container adaptor）类型，被特别设计使其第一个元素总是容器所包含的元素中按特定的严格弱序排序规则排序后最大的一个。</p>

#### 模板参数
<p><em>T</em></p>
<p style="margin-left: 40px; ">容器所包含的元素的类型。</p>
<p style="margin-left: 40px; ">在类模板内部，使用其别名为&nbsp;<code>value_type</code>&nbsp;的成员类型。</p>
<p><em>Container</em></p>
<p style="margin-left: 40px; ">底层的用于存储元素的容器的类型。</p>
<p><em>Compare</em></p>
<p style="margin-left: 40px; ">一个二元谓词，以两个元素为参数返回一个&nbsp;<code>bool</code>&nbsp;值。</p>
<p style="margin-left: 40px; ">可以是函数指针（Function pointer）类型或函数对象（Function object）类型。</p>
#### 详细说明
<p><code>priority_queue</code>的定义使得它类似一个堆（Heap），该堆只能获得它的最大堆元素（在&nbsp;<code>priority_queue</code> 中即为队列头）。</p>
<p><code>priority_queue</code>&nbsp;通常被实现为容器适配器，即使用一个特定容器类的封装对象作为它的底层容器。<code>priority_queue</code>&nbsp;提供了一系列成员函数用于操作它的元素，只能从容器&ldquo;后面&rdquo;提取（Pop）元素，该元素也可认为是 <code>priority_queue</code>&nbsp;的&ldquo;顶部（Top）&rdquo;。</p>
<p>用来实现优先级队列的底层容器必须满足顺序容器的所有必要条件。同时，它还必须提供以下语义的成员函数：</p>
<ul>
	<li><code>front()</code></li>
	<li><code>push_back()​</code></li>
	<li><code>pop_back()</code></li>
</ul>
<p>为了使内部始终保持堆结构，底层容器必须支持随机访问迭代器。这样，容器适配器内部就可以在适当的时候自动调用算法函数 <code><a>std::make_heap</a></code>、<code><a>std::push_heap</a></code>、<code><a>std::pop_heap</a></code>。</p>
<p>满足上述条件的标准容器有 <code><a>std::vector</a></code> 及&nbsp;<code><a>std::deque</a></code>，如果未特别指定&nbsp;<code>priority_queue</code>&nbsp;的底层容器，标准容器 <code>std::vector</code> 将被使用。</p>
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
			<td><code>container_type</code></td>
			<td>第二个模板参数&nbsp;<em>Container</em></td>
		</tr>
		<tr>
			<td><code>size_type</code></td>
			<td><code>Container::size_type</code></td>
		</tr>
		<tr>
			<td><code>reference</code></td>
			<td><code>Container::reference</code></td>
		</tr>
		<tr>
			<td><code>const_reference</code></td>
			<td><code>Container::const_reference</code></td>
		</tr>
	</tbody>
</table>
</div>
#### 成员函数
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><a>(constructor)</a></td>
			<td>创建 <code>priority_queue</code></td>
		</tr>
		<tr>
			<td><a>(destructor)</a></td>
			<td>释放 <code>priority_queue</code></td>
		</tr>
		<tr>
			<td><code><a>operator=</a></code></td>
			<td>赋值操作</td>
		</tr>
	</tbody>
</table>

<p><strong>Element access:</strong></p>

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>top</a></code></td>
			<td>访问顶部元素</td>
		</tr>
	</tbody>
</table>

<p><strong>Capacity:</strong></p>

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>empty</a></code></td>
			<td>判断是否为空</td>
		</tr>
		<tr>
			<td><code><a>size</a></code></td>
			<td>返回有效元素个数</td>
		</tr>
	</tbody>
</table>

<p><strong>Modifiers:</strong></p>

<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>push</a></code></td>
			<td>在容器顶部插入元素</td>
		</tr>
		<tr>
			<td><code><a>pop</a></code></td>
			<td>移除容器顶部的元素</td>
		</tr>
		<tr>
			<td><code><a>emplace(C++11)</a></code></td>
			<td>在容器顶部放置插入元素</td>
		</tr>
		<tr>
			<td><code><a>swap</a></code></td>
			<td>交换容器的内容</td>
		</tr>
	</tbody>
</table>
</div>
#### 非成员函数
<table border="0" cellpadding="0" cellspacing="0" class="table table-hover table-bordered table-condensed">
	<tbody>
		<tr>
			<td style="width: 30%; "><code><a>std::swap</a></code></td>
			<td>交换两个优先级队列的内容</td>
		</tr>
	</tbody>
</table>
</div>

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

## 引用
+ [http://classfoo.cn/cpp/library/](http://classfoo.cn/cpp/library/)
