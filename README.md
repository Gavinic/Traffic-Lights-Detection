# Traffic Lights Detection <br>
-----------
This project is aimed to realize the relative algorithms about traffic lights. I will complete it by two methods ,the classical computer vision algorithms and deep learning method based on tensorflow objection API.I am a graduate student from UESTC, Chengdu, China.

## Summary：<br>
  As the title says, the main job of this project is to achieve the detection of traffic lights. In the field of intelligent transportation, there have been extensive researches on traffic signs, lane lines, vehicle forward collision warning, backward collision warning, and distance detection. These traffic-related computer vision directions are also classic issues that autopilot cars are currently addressing or have solved. Compared to these directions, there are relatively few studies on the detection of traffic lights. The detection of traffic lights is crucial in the safe driving of autonomous vehicles. In the study of traditional CV, more is the identification of relatively simple overhead light traffic lights. In complex urban environments, the detection and identification of traffic lights is still a difficult problem. Although the technology of Deep Learning is currently used, the recognition effect of traffic lights has been greatly improved. However, traffic light detection in complex urban environmental roads still does not achieve high accuracy. The purpose of this project is to sort out the relevant knowledge of the object detection while improving its C++ coding ability and programming and project building capabilities based on the tensorflow framework.I hope that interested friends can maintain this project together.<br>
    
Here is the github link:<br>
   https://github.com/Gavinic/Traffic-Lights-Detection   <br>

## (1)Overall design of the project：<br>
   The whole project is mainly divided into three parts:Traffic lights locate; Traffic lights detect; Traffic lights recognize;<br>
1,Traffic lights locate: <br>
   The traffic light positioning part mainly performs pre-processing operations on the pictures used by the project to accurately find the traffic light area.<br>
2,Traffic lights detection: <br>
   The traffic light detection part mainly focuses on the precise screening of the traffic light    area obtained by the positioning part.<br>
3,Traffic lights recognize: <br>
   The traffic light recognition part mainly distinguishes the detected traffic lights by red,  yellow and green colors. <br>
 
## (2)DataSet：<br>
Bosch Small Traffic Lights Dataset<br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/b1.png)  <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/b2.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/b3.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/b4.png)  <br> 

## (3)The results of conventional cv algorithm：<br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/1.png)  
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/2.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/3.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/4.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/5.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/e1.png) <br>

## (4)The results of faster r-cnn based on Tensorflow：<br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/image_0424.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/image_0577.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/image_1949.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/image_8314.png) <br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/image_8321.png) <br>
 
## (5)Reference：<br>
  1，Traffic Light Mapping and Detection <br>
  2，Traffic Light Detection: A Learning Algorithm and Evaluations on Challenging Dataset <br>
  3，A Tlreshold Selection Method from Gray-Level Histograms  <br>
  4，Research on Traffic Object Detection and Recognition in Urban Environment  <br>
  5，Research on Detection and Recognition Method of Traffic Lights in Complex Scenes  <br>
  The above only lists the main references. The overall algorithm mainly uses the ideas of each article to design and        implement the overall algorithm.   <br>

## (6)Code overview:<br>
![image](https://github.com/Gavinic/Traffic-Lights-Detection/blob/master/image/7.png)  <br>
 <br>
## (7)tensorflow objection API
   https://github.com/tensorflow/models/blob/master/research/object_detection/g3doc/installation.md<br>
   The code based on object detection API  of tensorflow is also open source. Code running needs to be configured according to the above URL. Because the author is not major in the object detection direction. So this part of the network directly calls the Google Tensorflow API. Subsequent project team members will perform this part of the code rewriting. Welcome to pay attention in real time. At present, the DL-based traffic light detection algorithm is modified and implemented. The 1024*720 picture takes about 150ms, and the accuracy on the test data set reaches 98%. Since the effect of directly using the API is not satisfactory, the team designed a new detection algorithm. And has applied for a patent, and there is a paper in the investment, after which will give the relevant paper link.<br>
   
   This is a persistent project and the subsequent analysis and explanation of the relevant code and algorithm principles. The code of the whole project is all from the author's original, except for a small number of references. Due to my limited ability, there may be some flaws in the structure and quality of the code. I hope that you can make valuable comments and contribute on Github to improve the project. The algorithm part is currently implemented, and the subsequent plan plus the software interface. The result is a complete product.<br>
   I am currently studying at the University of Electronic Science and Technology of China. If you have any questions about the project, please send an email to：Gavinzmail@163.com，At the same time, I will also introduce the whole project in the domestic CSDN blog platform. https://blog.csdn.net/gavinv/article/details/81016064.However. However, the current scientific research task is heavy, I will try my best to make this project a good job. I hope everyone can support!
   
   <a href="https://996.icu"><img src="https://img.shields.io/badge/link-996.icu-red.svg" alt="996.icu" /></a>
 
