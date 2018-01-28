# SLP-Course-project
PS Move painter is an application that let you draw images using your playstation move controller. It also can save your masterpieces as PNG. Moreover, it can recognize text on pictures that you drawn!  
The application consists of two parts - the JavaFX GUI and the shared library on C for processing controller motion.  
  
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
After that you can just run the [Main](https://github.com/YakYakKruak/SLP-Course-project/blob/master/src/java/frontend/Main.java "Main") class, or you can build an executable jar.  
In case of any troubles mail to golovanev98@mail.ru
