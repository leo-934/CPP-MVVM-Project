# CPP-MVVM-Project

a GUI project implemented with C++17 and Qt, using MVVM(Model-View-ViewModel) design.

I coded this alone for practice in 2021.

鉴于项目的目标是实现mvvm三者之间的动态绑定，使得三部分的编写者互相之间不需要知道对方的api即可完成代码编写。考虑到需要对私有成员进行封装，有两方式可以完成model、viewmodel、view之间的绑定。

第一种：将绑定函数写在三个类中，即可访问私有workfunction进行绑定，但是这样就无法满足三个类互相独立的要求（即三部分的编写者互相之间不需要知道对方的接口即可完成代码编写）。

第二种：因为三个类的绑定由上层App类主导，所以考虑将绑定函数写在App中，只需简单设置App类为三者友元即可。