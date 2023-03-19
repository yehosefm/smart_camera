
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"
#include <iostream>
#include <cassert>

extern "C" {
    #include "sc_paths.h"
    #include "sc_logger.h"
    #include "detector.h"
}

#define NET_X_PIXEL 320
#define NET_Y_PIXEL 320


class Detector {
    std::unique_ptr<tflite::FlatBufferModel> model;
    tflite::ops::builtin::BuiltinOpResolver resolver;
    std::unique_ptr<tflite::Interpreter> interpreter;

    public:
    Detector(const char *filename): model(tflite::FlatBufferModel::BuildFromFile(filename)), interpreter(){
        tflite::InterpreterBuilder(*model, resolver)(&interpreter);
        interpreter->AllocateTensors();
    }

    void detect(const void *image, ScBox *res){
        auto tens = interpreter->input_tensor(0);
        std::cout << tens->bytes << std::endl;
        unsigned char* input = interpreter->typed_input_tensor<unsigned char>(0);
        memcpy(input, image, NET_X_PIXEL * NET_Y_PIXEL * 3);
        interpreter->Invoke();
        parse_output(res);
    }

    private:
    void parse_output(ScBox *res){
        int num_detection = std::round(*interpreter->typed_output_tensor<float>(3));
        float* classes = interpreter->typed_output_tensor<float>(1);
        float* scores = interpreter->typed_output_tensor<float>(2);
        float* boxes = interpreter->typed_output_tensor<float>(0);
        res->class_num = -1;
        for(int i = 0; i < num_detection; ++i ) {
            if(classes[i] == 0 && scores[i] > 0.5){
                res->class_num = 0;
                res->y_min = boxes[i*4 +0];
                res->x_min = boxes[i*4 +1];
                res->y_max = boxes[i*4 +2];
                res->x_max = boxes[i*4 +3];
                return;
            }
        }
    }

};

extern "C" {

DetectionErrors detector_init(char *path, detector *res){
    std::string str;
    if(res == NULL ){
        LOGGER_LOG(L_ERROR, "Detector got null ptr\n");
        return DETECTION_ERROR_NULL_PTR;
    }
    try {
        str += paths_get_external_path();
        char * filename = "lite-model_ssd_spaghettinet_edgetpu_large_320_uint8_nms_1.tflite";
        str += filename;
        printf("%s \n", str.c_str());
        *res = (detector)new Detector(str.c_str());
        if(*res == NULL){
            LOGGER_LOG(L_ERROR, "cannot create detector\n");
        }
    } catch(...){
        LOGGER_LOG(L_ERROR, "detector catched internal error\n");
        return DETECTION_ERROR_UNKNOWN;
    }
    return DETECTION_ERORR_SUCCESS;
}

DetectionErrors detector_detect(detector d, ScImage *image, ScBox* res){
    if(d == NULL || image == NULL || res == NULL){
        LOGGER_LOG(L_ERROR, "detector got null ptr", d, image, res);
        return DETECTION_ERROR_NULL_PTR;
    }
    if(image->buffer == NULL || image->height != NET_Y_PIXEL || image->width != NET_X_PIXEL){
        LOGGER_LOG(L_ERROR, "detector got unmatched image", d, image, res);
        return DETECTION_ERROR_UNMATCH_IMAGE;
    }
    try {
        ((Detector *)d)->detect(image->buffer, res);
    } catch(...){
        LOGGER_LOG(L_ERROR, "detector catched internal error\n");
        return DETECTION_ERROR_UNKNOWN;
    }
    return DETECTION_ERORR_SUCCESS;
}

DetectionErrors detector_destroy(detector d){
    if(d == NULL){
        return DETECTION_ERROR_NULL_PTR;
    }
    try {
        delete ((Detector *)d);
    } catch(...){
        LOGGER_LOG(L_ERROR, "detector catched internal error\n");
        return DETECTION_ERROR_UNKNOWN;
    }
    return DETECTION_ERORR_SUCCESS;
}

} //end of extern "C"