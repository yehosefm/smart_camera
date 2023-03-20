#include "video_pip.hpp"

int VideoPip::play() {
    /* Start playing */
    ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE)
    {
        g_printerr("Unable to set the pipeline to the playing state.\n");
        gst_object_unref(pipeline);
        return -1;
    }
    /* Wait until error or EOS */
    bus = gst_element_get_bus(pipeline);
    msg =
        gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                    (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
    /* Parse message */
    if (msg != NULL)
    {
        GError *err;
        gchar *debug_info;

        switch (GST_MESSAGE_TYPE(msg))
        {
        case GST_MESSAGE_ERROR:
        gst_message_parse_error(msg, &err, &debug_info);
        g_printerr("Error received from element %s: %s\n",
                    GST_OBJECT_NAME(msg->src), err->message);
        g_printerr("Debugging information: %s\n",
                    debug_info ? debug_info : "none");
        g_clear_error(&err);
        g_free(debug_info);
        break;
        case GST_MESSAGE_EOS:
        g_print("End-Of-Stream reached.\n");
        break;
        default:
        /* We should not reach here because we only asked for ERRORs and EOS */
        g_printerr("Unexpected message received.\n");
        break;
        }
        gst_message_unref(msg);
    }
    return 0;
}


void VideoPip::create_pipline(){
    /* Create the elements */
    source = gst_element_factory_make ("v4l2src", "source");
    g_object_set (source, "device", "/dev/video0", NULL);
    sink = gst_element_factory_make ("autovideosink", "sink");
    more_element[0] = gst_element_factory_make ("videoconvert", "videoconert0");
    more_element[1] = gst_element_factory_make ("videoconvert", "videoconert1");
    more_element[2] = gst_element_factory_make ("videoscale", "scale");
    more_element[3] = gst_element_factory_make ("my_filter", "myfilter");

    /* Create the empty pipeline */
    pipeline = gst_pipeline_new ("smart_camera_pipe");

    if (!pipeline || !source || !sink || ! more_element[0] || !more_element[1] || !more_element[2] || !more_element[3]) {
        g_printerr ("Not all elements could be created.\n");
    }
    if(!more_element[3]){
        g_printerr("my_filter not created\n");
    }
    /* Build the pipeline */
    gst_bin_add_many(GST_BIN(pipeline), source, more_element[0], more_element[2], more_element[3], more_element[1], sink, NULL);
    if (gst_element_link_many(source, more_element[0], more_element[2], more_element[3], more_element[1], sink, NULL) != TRUE)
    {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(pipeline);
    }
}

VideoPip::VideoPip(int argc, char * argv[]){
    gst_init (&argc, &argv);
    GstRegistry *registry;
    registry = gst_registry_get();
    gst_registry_scan_path(registry, "./detection_plugin/");
    create_pipline();
}

VideoPip::~VideoPip(){
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
}