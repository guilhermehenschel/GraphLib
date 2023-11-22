# GraphLib
This Library Provides a templated graph, able to store relation between any type or class. 


Usage:
> class MyClass;  
> class MyAnnotation;  
>  
><br></br>
> Graph<MyClass, MyAnnotation> graph{};  
> graph.addNode(MyClass{0});  
> graph.addNode(MyClass{1});  
> graph.addEdge(MyClass{0}, MyClass{1}, MyAnnotation{"A"})  
