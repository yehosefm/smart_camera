/*********************************************
* File - gstMyfilter.h
* Decpiption - gstreamer plugin for detection presons.
* Project - Smart Camera
* Author - Yosi Malka, yehosefm@gmail.com
*********************************************/

#ifndef __GST_MYFILTER_H__
#define __GST_MYFILTER_H__


#include <gst/gst.h>
#include "detection_thread.h"

#define GST_PACKAGE "myfilter"
#define GST_PACKAGE_ORIGIN "notexist@yet"
#define PACKAGE_VERSION "1"
#define GST_LICENSE "LGPL"
#define GST_PACKAGE_NAME "myfilter"


int resizer(char *image, int width, int height,char *output);

G_BEGIN_DECLS

#define GST_TYPE_MYFILTER (gst_my_filter_get_type())
G_DECLARE_FINAL_TYPE (GstMyFilter, gst_my_filter,
    GST, MYFILTER, GstElement)

struct _GstMyFilter
{
  GstElement element;

  GstPad *sinkpad, *srcpad;
  detector_thread_s detector;
  ScBox boxes;
  gboolean silent;
};

G_END_DECLS

#endif /* __GST_MYFILTER_H__ */