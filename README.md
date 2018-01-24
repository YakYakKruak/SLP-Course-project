# SLP-Course-project
PS Move painter with text recognition, this repository contains part on C.  
Java frontent can be found at repository [SLP-Course-Frontend](https://github.com/YakYakKruak/SPL-course-frontend "SLP-Course-frontend").  
  
  To build it from sources, you need following:  
  
  Dependencies:  
  * [PSMove API](https://github.com/thp/psmoveapi "PSMove API")
  * [Tesseract](https://github.com/tesseract-ocr/tesseract "Tesseract")
  * [Leptonica](https://github.com/DanBloomberg/leptonica "Leptonica")  
  
  You need to specify path to psmoveapi, tesseract and leptonica headers, and also for JNI headers (See [CMakeLists.txt](https://github.com/YakYakKruak/SLP-Course-project/blob/master/CMakeLists.txt "CMakeLists")).  
  
After that to build shared library you need to do following (from directory with CMakeLists.txt) :  

```sh
mkdir build
cd build
cmake ..
make
```
In case of any troubles mail to golovanev98@mail.ru
