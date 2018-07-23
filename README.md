# Traffic-Lights-Detection <br>
-----------
This project is aimed to realize the relative algorithms about traffic lights. I will complete it by two methods ,the  traditional computer vision algorithms and deep learning method based on tensorflow objection API.I am a graduate student from UESTC, Chengdu, China.

## 项目简介：<br>
  正如题目所说的，这个项目的主要工作实际上就是实现交通灯的检测。在智能交通领域关于交通标志，车道线，车辆前向碰撞预警，后向碰撞预警，车距检测等已经有比较广泛的研究。这些交通相关的计算机视觉方向也是目前自动驾驶汽车正在解决或者已经解决的经典问题。相比于这几个方向，对于交通灯的检测的研究相对较少。交通灯的检测在自动驾驶汽车的安全行驶中至关重要。传统CV的研究中，更多的是针对比较简单的高空架空的交通灯的识别。在复杂的城市环境中，交通灯的检测和识别仍然是一个比较困难的问题。虽然目前借助于Deep Learning 的技术，交通灯的识别效果有了很大的进步。但是复杂城市环境道路中的交通灯检测仍然达不到很高的精度。开设这个项目的目的在于梳理自己的知识，同时提升自己的C++的能力以及基于tensorflow框架的编程和项目搭建能力。这个项目将在github开源。欢迎大家共同进行项目维护。提出宝贵意见。<br>
    
以下是github地址:<br>
   https://github.com/Gavinic/Traffic-Lights-Detection   <br>

## (1)项目整体设计：<br>
     整个项目主要分为三大部分:Traffic lights locate; Traffic lights detect; Traffic lights recognize;
     Traffic lights locate: 交通灯定位部分主要是对项目所使用的图片进行预处理等操作，准确找到交通灯区域；
     Traffic lights detect: 交通灯检测部分主要是对定位部分得到的交通灯区域进行精确筛选；
     Traffic lights recognize: 交通灯识别部分主要是对检测到的交通灯进行红，黄，绿的颜色区分。 
 
## (2)项目相关数据集：<br>
Bosch Small Traffic Lights Dataset<br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/b1.png)  <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/b2.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/b3.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/b4.png)  <br> 

## (3)传统CV检测效果：<br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/1.png)  
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/2.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/3.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/4.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/5.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/e1.png) <br>

## (4)基于Tensorflow深度学习框架的交通灯识别效果：<br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/t1.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/t2.png) <br>
 
## (5)参考资料：<br>
  1，Traffic Light Mapping and Detection <br>
  2，Traffic Light Detection: A Learning Algorithm and Evaluations on Challenging Dataset <br>
  3，A Tlreshold Selection Method from Gray-Level Histograms  <br>
  4，城市环境中交通对象检测与识别研究  <br>
  5，复杂场景下交通灯的检测与识别方法研究  <br>
  以上只列出了主要的参考文献，整体算法主要是借助各个文章的部分思想，进行整体算法方案的设计和实现。   <br>

## (6)Code overview:<br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/7.png)  <br>
 <br>
## (7)tensorflow objection API
   https://github.com/tensorflow/models/blob/master/research/object_detection/g3doc/installation.md<br>
   基于tensorflow的object detection API的代码也已经开源。代码运行需要按照上述网址进行环境配置。由于笔者非object detection方向。所以这部分的网络直接调用的Google Tensorflow API后续会有项目组成员进行这部分的代码改写。欢迎实时关注。<br>
   
   这是一个持久的project，后续会逐部分分析和讲解相关的代码和算法原理。整个项目的代码除了少部分引用外，其他的全部来源于笔者原创。由于本人比能力有限，代码结构和质量可能存在一些瑕疵，希望各位可以提出宝贵意见，以及在github上contribute，共同完善这个工程。目前实现了算法部分，后续计划加上软件界面。最终形成一个完整的产品。<br>
   笔者目前就读于电子科技大学，对project有任何疑问请发送邮件至：Gavinzmail@163.com，同时我也会在国内的CSDN博客平台 https://blog.csdn.net/gavinv/article/details/81016064 进行整个项目的介绍。不过目前科研任务繁重，我会尽力把这个工程做好。希望大家多多支持！
 
