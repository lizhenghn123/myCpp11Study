#用C++11的std::async代替线程的创建

c++11中增加了线程，使得我们可以非常方便的创建线程，它的基本用法是这样的：

    void f(int n);
    std::thread t(f, n + 1);
    t.join();

但是线程毕竟是属于比较低层次的东西，有时候使用有些不便，比如我希望获取线程函数的返回结果的时候，我就不能直接通过thread.join()得到结果，这时就必须定义一个变量，在线程函数中去给这个变量赋值，然后join,最后得到结果，这个过程是比较繁琐的。c++11还提供了异步接口std::async，通过这个异步接口可以很方便的获取线程函数的执行结果。std::async会自动创建一个线程去调用线程函数，它返回一个std::future，这个future中存储了线程函数返回的结果，当我们需要线程函数的结果时，直接从future中获取，非常方便。但是我想说的是，其实std::async给我们提供的便利可不仅仅是这一点，它首先解耦了线程的创建和执行，使得我们可以在需要的时候获取异步操作的结果；其次它还提供了线程的创建策略（比如可以通过延迟加载的方式去创建线程），使得我们可以以多种方式去创建线程。在介绍async具体用法以及为什么要用std::async代替线程的创建之前，我想先说一说std::future、std::promise和std::packaged_task。

- std::future

std::future是一个非常有用也很有意思的东西，简单说std::future提供了一种访问异步操作结果的机制。从字面意思来理解，它表示未来，我觉得这个名字非常贴切，因为一个异步操作我们是不可能马上就获取操作结果的，只能在未来某个时候获取，但是我们可以以同步等待的方式来获取结果，可以通过查询future的状态（future_status）来获取异步操作的结果。future_status有三种状态：

   deferred：异步操作还没开始

   ready：异步操作已经完成

   timeout：异步操作超时

 
    //查询future的状态
    std::future_status status;
    do {
    status = future.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::deferred) {
    std::cout << "deferred\n";
    } else if (status == std::future_status::timeout) {
    std::cout << "timeout\n";
    } else if (status == std::future_status::ready) {
    std::cout << "ready!\n";
    }
    } while (status != std::future_status::ready); 

获取future结果有三种方式：get、wait、wait_for，其中get等待异步操作结束并返回结果，wait只是等待异步操作完成，没有返回值，wait_for是超时等待返回结果。

- std::promise

std::promise为获取线程函数中的某个值提供便利，在线程函数中给外面传进来的promise赋值，当线程函数执行完成之后就可以通过promis获取该值了，值得注意的是取值是间接的通过promise内部提供的future来获取的。它的基本用法：
    std::promise<int> pr;
    std::thread t([](std::promise<int>& p){ p.set_value_at_thread_exit(9); },std::ref(pr));
    std::future<int> f = pr.get_future();
    auto r = f.get();

- std::packaged_task

std::packaged_task它包装了一个可调用的目标（如function, lambda expression, bind expression, or another function object）,以便异步调用，它和promise在某种程度上有点像，promise保存了一个共享状态的值，而packaged_task保存的是一个函数。它的基本用法：

    std::packaged_task<int()> task([](){ return 7; });
    std::thread t1(std::ref(task)); 
    std::future<int> f1 = task.get_future(); 
    auto r1 = f1.get();


- std::promise、std::packaged_task和std::future的关系

至此, 我们介绍了std::async相关的几个对象std::future、std::promise和std::packaged_task，其中std::promise和std::packaged_task的结果最终都是通过其内部的future返回出来的，不知道读者有没有搞糊涂，为什么有这么多东西出来，他们之间的关系到底是怎样的？且听我慢慢道来，std::future提供了一个访问异步操作结果的机制，它和线程是一个级别的属于低层次的对象，在它之上高一层的是std::packaged_task和std::promise，他们内部都有future以便访问异步操作结果，std::packaged_task包装的是一个异步操作，而std::promise包装的是一个值，都是为了方便异步操作的，因为有时我需要获取线程中的某个值，这时就用std::promise，而有时我需要获一个异步操作的返回值，这时就用std::packaged_task。那std::promise和std::packaged_task之间又是什么关系呢？说他们没关系也关系，说他们有关系也有关系，都取决于你了，因为我可以将一个异步操作的结果保存到std::promise中。如果读者还没搞清楚他们的关系的话，我就用更通俗的话来解释一下。比如，一个小伙子给一个姑娘表白真心的时候也许会说：”我许诺会给你一个美好的未来“或者”我会努力奋斗为你创造一个美好的未来“。姑娘往往会说：”我等着“。现在我来将这三句话用c++11来翻译一下：

小伙子说：我许诺会给你一个美好的未来等于c++11中"std::promise a std::future"; 
小伙子说：我会努力奋斗为你创造一个美好的未来等于c++11中"std::packaged_task a future"; 
姑娘说：我等着等于c++11中"future.get()/wait()";

小伙子两句话的个中差异，自己琢磨一下，这点差异也是std::promise和std::packaged_task的差异。现实中的山盟海誓靠不靠得住我不知道，但是c++11中的许诺和未来是一定可靠的，发起来了许诺就一定有未来。细想起来c++11标准的制定者选定的关键字真是贴切而有意思！好了，插科打诨到此了，现在言归正传，回过头来说说std::async。

- 为什么要用std::async代替线程的创建

std::async又是干啥的，已经有了td::future、std::promise和std::packaged_task，够多的了，真的还要一个std::async来凑热闹吗，std::async表示很委屈：我不是来凑热闹的，我是来帮忙的。是的，std::async是为了让用户的少费点脑子的，它让这三个对象默契的工作。大概的工作过程是这样的：std::async先将异步操作用std::packaged_task包装起来，然后将异步操作的结果放到std::promise中，这个过程就是创造未来的过程。外面再通过future.get/wait来获取这个未来的结果，怎么样，std::async真的是来帮忙的吧，你不用再想到底该怎么用std::future、std::promise和std::packaged_task了，std::async已经帮你搞定一切了！

现在来看看std::async的原型async(std::launch::async | std::launch::deferred, f, args...)，第一个参数是线程的创建策略，有两种策略，默认的策略是立即创建线程：

	std::launch::async：在调用async就开始创建线程。
	std::launch::deferred：延迟加载方式创建线程。调用async时不创建线程，直到调用了future的get或者wait时才创建线程。

第二个参数是线程函数，第三个参数是线程函数的参数。

- std::async基本用法

示例：
    
	std::future<int> f1 = std::async(std::launch::async, [](){ 
    return 8;  
    }); 
    
    cout<<f1.get()<<endl; //output: 8
    
    std::future<int> f2 = std::async(std::launch::async, [](){ 
    cout<<8<<endl;
    }); 
    
    f2.wait(); //output: 8
    
    std::future<int> future = std::async(std::launch::async, [](){ 
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 8;  
    }); 
     
    std::cout << "waiting...\n";
    std::future_status status;
    do {
    status = future.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::deferred) {
    std::cout << "deferred\n";
    } else if (status == std::future_status::timeout) {
    std::cout << "timeout\n";
    } else if (status == std::future_status::ready) {
    std::cout << "ready!\n";
    }
    } while (status != std::future_status::ready); 
     
    std::cout << "result is " << future.get() << '\n';

	可能的结果：
	waiting...
	timeout
	timeout
	ready!
	result is 8

- 总结

std::async是更高层次上的异步操作，使我们不用关注线程创建内部细节，就能方便的获取异步执行状态和结果，还可以指定线程创建策略，应该用std::async替代线程的创建，让它成为我们做异步操作的首选。

来源：[http://www.cnblogs.com/qicosmos/p/3534211.html](http://www.cnblogs.com/qicosmos/p/3534211.html)