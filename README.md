# Smart Camera

Smart Camera project is the open source app for detect persons on image and moves the camera towards.  

## Video for the project:

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/6XpyfJSzU9Y/0.jpg)](https://youtu.be/6XpyfJSzU9Y)

##  Linux prerequisite

Clone the repository:

```bash
git clone https://github.com/yehosefm/smart_camera.git
```

Install GStreamer globally on your machine:

```bash 
apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
```

Install toolchain and CMake:
```bash 
sudo apt install build-essential cmake
```

In smart_camera directory (from latest clone) make the new  directory named external:
```bash 
cd smart_camera && mkdir external && cd external
```
Clone tensorflow src code to external directory:

```bash
git clone https://github.com/tensorflow/tensorflow.git tensorflow_src
 ```

Download pre-trained tensorflow lite model and save it in the external directory
```bash 
https://tfhub.dev/iree/lite-model/ssd_spaghettinet_edgetpu_large_320/uint8/nms/1?lite-format=tflite
``` 


## Compile 

```bash 
cd camera_app && mkdir build && cd build 
cmake ../app
cmake --build . -j
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

All rights reserved to Yosi Malka, TLV.
mail: yehosefm@gmail.com
