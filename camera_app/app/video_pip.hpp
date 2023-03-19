//extern "C" {
    #include <gst/gst.h>
//}

class VideoPip {
    public:
        VideoPip(int argc,char * argv[]);
        int play();
        ~VideoPip();
    
    private:
        GstElement *pipeline, *source, *sink;
        GstElement * more_element[4];
        GstBus *bus;
        GstMessage *msg;
        GstStateChangeReturn ret;
        void create_pipline(void);
};